#include "odatawebhandler.h"
#include <QDebug>
#include <QJsonDocument>
#include <QtXml>
#include <OData.h>
ODataWebHandler::ODataWebHandler(QObject *parent)
    : WebInterface(parent)
{
}

QString ODataWebHandler::getName() const
{
    return "odata";
}

QHttpServerResponse ODataWebHandler::execute(const QHttpServerRequest *request, ApplicationServerInterface *app)
{
	QHttpServerResponse * response = nullptr;
    if (!this->requestHandlers.contains(request->url().host()))
    {
        qDebug() << "create request handler: " + request->url().host();
        QList<QObject *> entityContainers = app->getValues("ODATA_ENTITY_MAP");
        QMap<QString, ODataSchema *> schemaMap;
        ODataEntityContainer * mergedEntityContainer = new ODataEntityContainer();
        for(QObject * entityContainerGeneric: entityContainers){
        	ODataEntityContainer * entityContainer = static_cast<ODataEntityContainer *>(entityContainerGeneric);
        		mergedEntityContainer->actionImports.unite(entityContainer->actionImports);
        		mergedEntityContainer->functions.unite(entityContainer->functions);
        		mergedEntityContainer->entitySets.unite(entityContainer->entitySets);
        }
    	ODataSchema * schema = new ODataSchema("Default", mergedEntityContainer);
    	schemaMap.insert(schema->_namespace, schema);
        this->requestHandlers.insert(request->url().host(), new ODataRequestHandler(request->url().host(), "/odata/", schemaMap, this));
    }

    ODataRequestHandler *requestHandler = this->requestHandlers[request->url().host()];
    QVariant result;
    QHttpServerResponse::StatusCode statusCode = QHttpServerResponse::StatusCode::Ok;
    try{
    result = requestHandler->handleRequest(request->url(), request->query(), request->body(), request->headers(), static_cast<ODataRequestHandler::Method>(request->method()));

    }catch (ODataException &oex){

    	qDebug() << oex.what();
    	result = oex.errorBody;
    	statusCode = QHttpServerResponse::StatusCode::NotFound;
    }
    switch (result.type())
    {
    case QMetaType::QJsonObject:
    	response = new QHttpServerResponse(result.toJsonObject());
        break;
    default:
    	QString resultString = result.toString();
    	if(resultString.startsWith("XML:")){
    		resultString = resultString.remove(0,4);
        	response = new QHttpServerResponse(QByteArrayLiteral("application/xml"), resultString.toUtf8());
    	}else{
        	response = new QHttpServerResponse(resultString);
    	}
        break;
    }
    QHttpServerResponse resp = QHttpServerResponse(response->mimeType(), response->data(),statusCode);
    resp.addHeader("OData-Version", "4.0");
    return resp;
}

QString ODataWebHandler::getRoute(ApplicationServerInterface *app)
{
    return "/odata/.*";
}
