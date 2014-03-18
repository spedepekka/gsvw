/*
 * Author: Jarno Tuovinen
 */
#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QTime>
#include <QTimer>

#include "metadata.h"
#include "panorama.h"

#define REQUEST_TIMEOUT 15000 // ms // 15 sec

/******************************************************************************/
/*!
  * \class Request
  * \brief This class has one request.
*/
/******************************************************************************/
class Request: public QObject
{
    Q_OBJECT

public:

    enum State {
        Unready,        //!< Request not served
        Running,        //!< Request is going on
        Ready           //!< Request served
    };

    enum Type {
        Init,   //!< Initial type for request
        Meta,   //!< Request is metadata-type
        Pano    //!< Request is panorama-type
    };

    Request(Type t,
            QString reqId,
            double lat,
            double lng,
            int zoomLevel = 0,
            QString fieldName = QString(""),
            int priority = 5);
    ~Request();

    static bool requestCompareRef(const Request& r1, const Request& r2);
    static bool requestComparePtr(const Request* r1, const Request* r2);
    static bool requestCompareSharedPtr(const QSharedPointer<Request> r1,
                                        const QSharedPointer<Request> r2);

    QString id; //!< Request id (QUuid)
    double lat; //!< Latitude
    double lng; //!< Longitude
    int zoomLevel; //!< Zoom level
    QString fieldName;
    int priority; //!< Priority [0,9]. Default = 5.

    Type type();
    State state();
    void setState(State state);

    void setMetadata(QSharedPointer<Metadata> md);
    QSharedPointer<Metadata> getMetadata();

    QSharedPointer<Panorama> getPanorama();

    QSharedPointer<Request> friendRequest;

    QTime elapsedTime;

private:
    Type reqType;       //!< Type of this request
    State reqState;     //!< State of this request

    QSharedPointer<Metadata> metaData;
    QSharedPointer<Panorama> panorama;

    QTimer timeoutTimer;

private slots:
    void timedOut();
    void panoramasZoomLevelReady(int zoomLevel);

signals:
    void zoomLevelReady(int zoomLevel);
};

#endif // REQUEST_H
