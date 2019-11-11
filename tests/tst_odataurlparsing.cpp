#include <QtTest>
#include <QCoreApplication>
#include <application.h>
#include <QList>
#include <QString>
#include <ODataURLParser.h>
// add necessary includes here

class ODataURLParsingTest : public QObject
{
    Q_OBJECT

private:
    ODataURLParser * urlParser;
public:
    ODataURLParsingTest();
    ~ODataURLParsingTest();

public:
private slots:
    void initTestCase()
    {
        this->urlParser = new ODataURLParser(this);
    }
    void encodesURLCorrect();

    void cleanupTestCase()
    {
    }
};

ODataURLParsingTest::ODataURLParsingTest()
{
}

ODataURLParsingTest::~ODataURLParsingTest()
{
}

void ODataURLParsingTest::encodesURLCorrect()
{
    QStringList segments = this->urlParser->splitUpURL(QUrl("http://host/service/People('O''Neil')"));
    QVERIFY(segments.count() == 1);
    QVERIFY(segments.contains("People('O''Neil')"));
    segments = this->urlParser->splitUpURL(QUrl("http://host/service/People(%27O%27%27Neil%27)"));
    QVERIFY(segments.count() == 1);
    QVERIFY(segments.contains("People('O''Neil')"));
    segments = this->urlParser->splitUpURL(QUrl("http://host/service/People%28%27O%27%27Neil%27%29"));
    QVERIFY(segments.count() == 1);
    QVERIFY(segments.contains("People('O''Neil')"));
    segments = this->urlParser->splitUpURL(QUrl("http://host/service/Categories('Smartphone%2FTablet')"));
    QVERIFY(segments.count() == 1);
    QVERIFY(segments.contains("Categories('Smartphone/Tablet')"));
}

QTEST_APPLESS_MAIN(ODataURLParsingTest)

#include "tst_odataurlparsing.moc"
