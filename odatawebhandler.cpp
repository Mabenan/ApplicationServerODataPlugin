#include "odatawebhandler.h"
#include <QDebug>
#include <QJsonDocument>

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
    QVariant result = requestHandler->handleRequest(request->url(), request->query(), request->body(), static_cast<ODataRequestHandler::Method>(request->method()));
    switch (result.type())
    {
    case QMetaType::QJsonObject:
        return result.toJsonObject();
        break;
    default:
        return result.toString();
        break;
    }
}

QString ODataWebHandler::getRoute(ApplicationServerInterface *app)
{
    return "/odata/.*";
}
