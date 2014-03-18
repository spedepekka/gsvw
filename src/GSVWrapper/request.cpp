#include "request.h"

#include <QDebug>

/******************************************************************************/
/*!
  * \brief Constructor with values.
  * \param lat Latitude.
  * \param lng Longitude.
  * \param zoomLevel Zoom level.
  * \param priority Priority of this request. If not given it will be default 5.
*/
/******************************************************************************/
Request::Request(Type t,
                 QString reqId,
                 double lat,
                 double lng,
                 int zoomLevel,
                 QString fieldName,
                 int priority):
        id(reqId),
        lat(lat),
        lng(lng),
        zoomLevel(zoomLevel),
        fieldName(fieldName),
        priority(priority),
        friendRequest(0),
        reqType(t),
        reqState(Unready)
{
    panorama = QSharedPointer<Panorama>(new Panorama());
    QObject::connect(panorama.data(), SIGNAL(zoomLevelReady(int)),
                     this, SLOT(panoramasZoomLevelReady(int)));

    timeoutTimer.setSingleShot(true);
    timeoutTimer.setInterval(REQUEST_TIMEOUT);
    QObject::connect(&timeoutTimer, SIGNAL(timeout()),
                     this, SLOT(timedOut()));

    elapsedTime.start();
    timeoutTimer.start();
}

/******************************************************************************/
/*! \brief Destructor. */
/******************************************************************************/
Request::~Request()
{
}

/******************************************************************************/
/*! Function that returns requests type. */
/******************************************************************************/
Request::Type Request::type()
{
    return reqType;
}

/******************************************************************************/
/*! Function that returns requests state. */
/******************************************************************************/
Request::State Request::state()
{
    return reqState;
}

void Request::setState(State state)
{
    reqState = state;
}

/******************************************************************************/
/*! This is helper function for qSort. */
/******************************************************************************/
bool Request::requestCompareRef(const Request& r1, const Request& r2)
{
    if (r1.priority < r2.priority)
        return true;
    return false;
}

/******************************************************************************/
/*! This is helper function for qSort. */
/******************************************************************************/
bool Request::requestComparePtr(const Request* r1, const Request* r2)
{
    if (r1->priority < r2->priority)
        return true;
    return false;
}

/******************************************************************************/
/*! This is helper function for qSort. */
/******************************************************************************/
bool Request::requestCompareSharedPtr(const QSharedPointer<Request> r1,
                                      const QSharedPointer<Request> r2)
{
    if (r1->priority < r2->priority)
        return true;
    return false;
}

/******************************************************************************/
/*! Set metadata. */
/******************************************************************************/
void Request::setMetadata(QSharedPointer<Metadata> md)
{
    if (!metaData.isNull()) {
        qDebug() << "Warning: Overwriting metadata";
//        delete metaData;
    }
    metaData = md;
}

/******************************************************************************/
/*! Returns pointer to metadata. */
/******************************************************************************/
QSharedPointer<Metadata> Request::getMetadata()
{
    return metaData;
}

/******************************************************************************/
/*! Returns pointer to panorama. */
/******************************************************************************/
QSharedPointer<Panorama> Request::getPanorama()
{
    return panorama;
}

/******************************************************************************/
/*! Function that handles time outs. */
/******************************************************************************/
void Request::timedOut()
{
    setState(Ready);

    qDebug() << QString("Request %1 timed out").arg(id);
}

/******************************************************************************/
/*! Slot connected to this->panorama::zoomLevelReady(int zoomLevel)-signal. */
/******************************************************************************/
void Request::panoramasZoomLevelReady(int zoomLevel)
{
    timeoutTimer.stop();
    setState(Ready);

    qDebug() << QString("Request %1 zoom level %2 ready").arg(id).arg(zoomLevel);
    qDebug() << QString("Request %1 elapsed %2 ms").arg(id).arg(elapsedTime.elapsed());

    emit zoomLevelReady(zoomLevel);
}
