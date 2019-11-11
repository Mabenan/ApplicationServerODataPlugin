#include "odatawebhandler.h"
#include <QDebug>
#include "ODataServiceDocument.h"
#include <QJsonDocument>

ODataWebHandler::ODataWebHandler(QObject *parent)
    : WebInterface(parent)
{
    this->urlParser = new ODataURLParser(this);
}

QString ODataWebHandler::getName() const
{
    return "odata";
}

QHttpServerResponse ODataWebHandler::execute(const QHttpServerRequest *request, ApplicationServerInterface *app)
{
    if (request->url().path() == "/odata/")
    {

        ODataServiceDocument * serviceDoc = new ODataServiceDocument(this);
        serviceDoc->context = request->url().topLevelDomain() + "/odata/$metadata";
        return serviceDoc->getJson();
    }else if(request->url().path().toLower() == "/odata/$metadata"){
        
    }
    else
    {
        this->urlParser->splitUpURL(request->url());
    }
    return "It Works:" + request->query().toString();
}

QString ODataWebHandler::getRoute(ApplicationServerInterface *app)
{
    return "/odata/.*";
}
