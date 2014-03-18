#include "offlinenetworkhandler.h"

OfflineNetworkHandler::OfflineNetworkHandler()
{
}

void OfflineNetworkHandler::getMeta(QString requestId,
                                    double lat,
                                    double lng)
{
    qDebug() << "OfflineNetworkHandler";
    QString filename = QString(":/51.495072_-0.146984.xml");
    qDebug() << "***" << filename;
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QString xml = QString(file.readAll());
    emit metaReady(xml, requestId);
}

void OfflineNetworkHandler::getTile(QString requestId,
                                    QString pid,
                                    int zoomLevel,
                                    int x,
                                    int y,
                                    int priority)
{
    qDebug() << "OfflineNetworkHandler";
    QString filename = QString(":/%1_%2_%3_%4.jpeg")
                       .arg(pid).arg(zoomLevel)
                       .arg(x).arg(y);
    QImage tile(filename);
    qDebug() << "Tile size" << tile.size();
    emit tileReady(tile, requestId, x, y);
}
