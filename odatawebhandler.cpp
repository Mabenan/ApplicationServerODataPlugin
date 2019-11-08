#include "odatawebhandler.h"
#include <QDebug>

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
    
    return "It Works:" + request->query().toString();
}

QString ODataWebHandler::getRoute(ApplicationServerInterface *app){
    return "/odata/.*";
}

