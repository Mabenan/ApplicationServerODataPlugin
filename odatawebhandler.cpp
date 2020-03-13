#include "odatawebhandler.h"
#include <QDebug>
#include <QJsonDocument>
#include <QtXml>
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
        QList<QObject *> schemas = app->getValues("ODATA_SCHEMA_MAP");
        QMap<QString, ODataSchema *> schemaMap;
        for(QObject * schemaGeneric: schemas){
        	ODataSchema * schema = static_cast<ODataSchema *>(schemaGeneric);
        	schemaMap.insert(schema->_namespace, schema);
        }
        this->requestHandlers.insert(request->url().host(), new ODataRequestHandler(request->url().host(), "/odata/", schemaMap, this));
    }

    ODataRequestHandler *requestHandler = this->requestHandlers[request->url().host()];
    QVariant result = requestHandler->handleRequest(request->url(), request->query(), request->body(), request->headers(), static_cast<ODataRequestHandler::Method>(request->method()));
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
    QHttpServerResponse resp = QHttpServerResponse(response->mimeType(), response->data(),response->statusCode());
    resp.addHeader("OData-Version", "4.0");
    return resp;
}

QString ODataWebHandler::getRoute(ApplicationServerInterface *app)
{
    return "/odata/.*";
}
