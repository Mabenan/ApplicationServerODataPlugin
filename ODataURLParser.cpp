#include "ODataURLParser.h"
#include <QUrl>
#include <QDebug>

ODataURLParser::ODataURLParser(QObject *parent): QObject(parent)
{

}

QStringList ODataURLParser::splitUpURL(QUrl url){


    QUrl reducedURL = url.adjusted(QUrl::RemoveScheme |
                                   QUrl::RemovePassword |
                                   QUrl::RemoveUserInfo |
                                   QUrl::RemovePort |
                                   QUrl::RemoveAuthority |
                                   QUrl::RemoveQuery |
                                   QUrl::RemoveFragment |
                                   QUrl::StripTrailingSlash);

    QString urlString = reducedURL.toString();
    QStringList segments = urlString.split("/");
    segments.removeAt(0);
    segments.removeAt(0);
    QStringList encodedSegements;
    foreach (QString segment, segments)
    {
        QString decodedSegment = QUrl::fromPercentEncoding(segment.toUtf8());
        encodedSegements.push_back(decodedSegment);
    }
    foreach (QString segment, encodedSegements)
    {
        qDebug() << segment;
    }
    return encodedSegements;
}