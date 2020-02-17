#ifndef ODATAWEBHANDLER_H
#define ODATAWEBHANDLER_H

#include <WebInterface.h>
#include <request/odatarequesthandler.h>

class ODataWebHandler : public WebInterface
{
    Q_OBJECT
public:
    explicit ODataWebHandler(QObject *parent = nullptr);

private:
    QMap<QString, ODataRequestHandler *> requestHandlers;
    // WebInterface interface
public:
     QString getName() const;
     QString getRoute(ApplicationServerInterface * app);
     QHttpServerResponse execute(const QHttpServerRequest * request, ApplicationServerInterface * app);
};

#endif // ODATAWEBHANDLER_H
