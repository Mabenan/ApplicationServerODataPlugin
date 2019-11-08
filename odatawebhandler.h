#ifndef ODATAWEBHANDLER_H
#define ODATAWEBHANDLER_H

#include <WebInterface.h>

class ODataWebHandler : public WebInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID WebInterface_iid FILE "ApplicationServerODataPlugin.json")
    Q_INTERFACES(WebInterface)

public:
    explicit ODataWebHandler(QObject *parent = nullptr);

private:
    // WebInterface interface
public:
     QString getName() const;
     QString getRoute(ApplicationServerInterface * app);
     QHttpServerResponse execute(const QHttpServerRequest * request, ApplicationServerInterface * app);
};

#endif // ODATAWEBHANDLER_H
