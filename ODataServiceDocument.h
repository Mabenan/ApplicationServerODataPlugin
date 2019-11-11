#ifndef ODATA_SERVICE_DOCUMENT_H
#define ODATA_SERVICE_DOCUMENT_H

#include "ApplicationServerODataPlugin_global.h"
#include <QString>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QJsonValue>

class APPLICATIONSERVERODATAPLUGIN_EXPORT ODataServiceDocumentEntry : public QObject{

    Q_OBJECT

public:

    explicit ODataServiceDocumentEntry(QObject * parent = nullptr ) : QObject(parent){

    };

public:
    QString name;
    QString title;
    QString url;
    QString kind;

    QJsonObject getJson(){
        QJsonObject json = QJsonObject();
        json["name"] = QJsonValue(this->name);
        json["title"] = QJsonValue(this->title);
        json["url"] = QJsonValue(this->url);
        json["kind"] = QJsonValue(this->kind);
        return json;
    };

};

class APPLICATIONSERVERODATAPLUGIN_EXPORT ODataServiceDocument : public QObject{

    Q_OBJECT

public:

    explicit ODataServiceDocument(QObject * parent = nullptr ) : QObject(parent){

    };

public:
    QString context;
    QList<ODataServiceDocumentEntry *> value;

    QJsonObject getJson(){
        QJsonObject json = QJsonObject();
        json["@context"] = QJsonValue(context);
        QJsonArray jsonValue;
        foreach(ODataServiceDocumentEntry * entry, this->value){
            jsonValue.push_back(QJsonValue(entry->getJson()));
        }
        json["value"] = jsonValue;
        return json;
    };

};

#endif // !ODATA_SERVICE_DOCUMENT_H