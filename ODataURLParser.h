#ifndef ODATAURLPARSER_H
#define ODATAURLPARSER_H

#include <QObject>
#include "ApplicationServerODataPlugin_global.h"

class APPLICATIONSERVERODATAPLUGIN_EXPORT ODataURLParser : public QObject
{
    Q_OBJECT

public:
    explicit ODataURLParser(QObject *parent = nullptr);

private:
    // WebInterface interface
public:
     QStringList splitUpURL(QUrl url);
};

#endif // ODATAURLPARSER_H