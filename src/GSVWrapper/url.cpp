/*
 * 2011
 * Author: Tommi Käsmä
 */

#include "url.h"

Url::Url():
        x(-1), y(-1), reply(0), id("")
{
}

Url::Url(double lat, double lng, QString id):
    x(-1), y(-1), reply(0), id(id)
{
    this->request.setUrl(Url::formXMLUrl(lat, lng));
}

Url::Url(QString pid, int zoomLevel, int x, int y,
         QNetworkRequest::Priority priority, QString id):
    x(x), y(y), reply(0), id(id)
{
    this->request.setUrl(Url::formTileUrl(pid, zoomLevel, x, y));
    this->request.setPriority(priority);
}

QNetworkReply* Url::get(QNetworkAccessManager *nam)
{
    this->reply = nam->get(this->request);
    return this->reply;
}

void Url::setReply(QNetworkReply *reply)
{
    this->reply = reply;
}

QNetworkReply* Url::getReply()
{
    return this->reply;
}

QUuid Url::getId()
{
    return this->id;
}

QUrl Url::formTileUrl(const QString pid, const int zoomLevel, const int x,
                         const int y)
{
    // Make urlStr
    QString urlStr = QString("http://cbk0.google.com/cbk?output=tile&panoid=%1&zoom=%2&x=%3&y=%4")
                     .arg(pid)
                     .arg(zoomLevel)
                     .arg(x)
                     .arg(y);
    qDebug() << "Formed tile url" << urlStr;
    return QUrl(urlStr);
}

QUrl Url::formXMLUrl(const double lat, const double lng)
{
    QString urlStr = QString("http://cbk0.google.com/cbk?output=xml&ll=%1,%2")
                     .arg(QString::number(lat))
                     .arg(QString::number(lng));
    qDebug() << "Formed xml url" << urlStr;
    return QUrl(urlStr);
}
