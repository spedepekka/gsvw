/*
 * Author: Jarno Tuovinen
 */
#ifndef OFFLINENETWORKHANDLER_H
#define OFFLINENETWORKHANDLER_H

#include <QFile>
#include <QDebug>

#include "networkhandler.h"

class OfflineNetworkHandler: public NetworkHandler
{
    Q_OBJECT

public:
    OfflineNetworkHandler();

    void getMeta(QString requestId,
                 double lat,
                 double lng);

    void getTile(QString requestId,
                 QString pid,
                 int zoomLevel,
                 int x,
                 int y,
                 int priority = 5);
};

#endif // OFFLINENETWORKHANDLER_H
