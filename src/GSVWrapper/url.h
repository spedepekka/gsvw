#ifndef URL_H
#define URL_H

#include <QDebug>
#include <QtNetwork>
#include <QString>
#include <QUrl>
#include <QUuid>

class Url
{
public:
    Url();
    Url(double lat, double lng, QString id);
    Url(QString pid, int zoomLevel, int x, int y,
        QNetworkRequest::Priority priority, QString id);

    QNetworkReply* get(QNetworkAccessManager *nam);
    void setReply(QNetworkReply *reply);
    QNetworkReply* getReply();
    QUuid getId();

    static QUrl formTileUrl(const QString pid,
                        const int zoomLevel,
                        const int x,
                        const int y);
    static QUrl formXMLUrl(const double lat, const double lng);

    int x;
    int y;

#ifndef UNIT_TEST
private:
#else
public:
#endif
    QNetworkRequest request;
    QNetworkReply *reply;
    QString id;
};

#endif // URL_H
