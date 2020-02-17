#include "ODataPlugin.h"
#include "odatawebhandler.h"
#include <QDebug>

ODataPlugin::ODataPlugin(QObject *parent)
    : ApplicationServerPluginInterface(parent)
{
}

void ODataPlugin::init(ApplicationServerInterface *app)
{
    app->registerWebInterface(new ODataWebHandler(this));
}

