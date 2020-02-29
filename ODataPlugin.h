#ifndef ODataPlugin_H
#define ODataPlugin_H

#include <ApplicationServerPluginInterface.h>

class ODataPlugin : public ApplicationServerPluginInterface
{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID ApplicationServerPluginInterface_iid FILE "ApplicationServerODataPlugin.json")
    Q_INTERFACES(ApplicationServerPluginInterface)

public:
    explicit ODataPlugin(QObject *parent = nullptr);

private:
    // CommandInterface interface
public:
    void init(ApplicationServerInterface *app);
	virtual void install(ApplicationServerInterface *app);
};

#endif // ODataPlugin_H
