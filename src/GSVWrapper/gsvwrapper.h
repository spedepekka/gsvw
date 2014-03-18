/*
 * Author: Jarno Tuovinen
 */
#ifndef GSVWRAPPER_H
#define GSVWRAPPER_H

/*!
 * \defgroup gsvwrapper GSVWrapper
 * @{
 */

#include <QObject>
#include <QDebug>
#include <QImage>
#include <QList>
#include <QMap>
#include <QSharedPointer>
#include <QThread>
#include <QtNetwork>
#include <QUuid>
#include <QVector2D>

#include "filehandler.h"
#include "networkhandler.h"
#include "panorama.h"
#include "request.h"
#include "xmlparser.h"

#ifdef OFFLINE
#include "offlinenetworkhandler.h"
#endif

#ifdef Q_WS_WIN
#define MY_EXPORT
#else
#define MY_EXPORT
#endif

namespace GSV {
    class GSVWrapper;
}

/*! Maximum X and Y coordinate values is each zoom level. */
static const QVector2D zoomLevels[] = {
    QVector2D(1,   1), // Zoomlevel 0 has 1x1   grid
    QVector2D(2,   1), // Zoomlevel 1 has 2x1   grid
    QVector2D(4,   2), // Zoomlevel 2 has 4x2   grid
    QVector2D(6,   3), // Zoomlevel 3 has 7x4   grid
    QVector2D(13,  7), // Zoomlevel 4 has 13x7  grid
    QVector2D(26, 13)  // Zoomlevel 5 has 26x13 grid
};

/*! Function returns maximum coordinate values from zoomLevels array.
    \param i Give values [0,5]. If i < 0 -> using i = 0. If i > 0 -> using i = 5.
*/
static QVector2D getZoomLevel(int i)
{
    if(i < 0)
        i = 0;
    if(i > 5)
        i = 5;
    return zoomLevels[i];
}

/******************************************************************************/
/*!
  * \class GSVWrapper
  * \brief GSVWrapper Main class of whole GSVWrapper.
  * \todo Comment this class.
*/
/******************************************************************************/
class GSVWrapper: public QObject
{
    Q_OBJECT

public:
    GSVWrapper(QObject *parent = 0);
    ~GSVWrapper();

    // TODO: Should this be something else
    enum GSVError {
        Undefined = 0,
        RequestNotFound,
        XmlParseError,
        UnknownNetworkState,
        NullTile,
        UnknownRequestType,
        EmptyPanoID,
        DuplicateRequest
    };

    /*! \ingroup metadata
     * \brief This enum defines in which order individual data fields need to
     *  be de/coded when a link is added or read.
     */
    enum GSVLinkCodingOrder {
        GSVLinkYawDeg, //!< GSVLinkYawDeg
        GSVLinkPanoId, //!< GSVLinkPanoId
        GSVLinkRoadArgb, //!< GSVLinkRoadArgb
        GSVLinkScene, //!< GSVLinkScene
        GSVLinkText //!< GSVLinkText
    };

    void setVerbose(bool val);
    void moveToThread(QThread *thread);
    void printThreads();

#ifndef UNIT_TEST
private:
#else
public:
#endif

    bool verbose;

    FileHandler filehandler; //!< File handler
#ifndef OFFLINE
    NetworkHandler networkhandler; //!< Network handler
#else
    OfflineNetworkHandler networkhandler;
#endif
    XMLParser xmlParser; //!< Xml parser

    QList<QSharedPointer<Request> > requestQueue; //!< Request queue
    QMap<QString, QSharedPointer<Request> > requestMap;
    Panorama currentPanorama; //!< Current panorama

    QThread* myThread; //!< Pointer to thread

    void insertRequest(QSharedPointer<Request> request);
    void organizeRequests();
    void printRequests(); //!< Debug-function

public slots:
    void clearCache();
    void getMeta(double lat,
                 double lng,
                 QString fieldName);
    void getPano(double lat,
                 double lng,
                 int zoomLevel,
                 int priority = 5);
    void reset();

private:
    void getMeta(QSharedPointer<Request> r);

private slots:
    void networkStateChanged(int type, QString statusMsg);

    void handleGSVError(int type, QString error);
    void handleFileError(int type, QString error);
    void handleNetworkError(int type, QString error);
    void handleXmlError(int type, QString error);
    void handleMetadata(QString xmlStr, QString requestId);
    void imageDataReady(QImage image, QString requestId, int x, int y);
    void panoramasZoomLevelReady(int zoomLevel);

    void processQueue();
    void removeFromQueue(QString id);
    void removeReadyRequests();

signals:
    /*! \brief Signaled when some error happens.
      \param type Type of error.
      \param error Error string that tells more about error.
       */
    void gsvWrapperError(int type,
                         QString error);

    /*! \brief Signaled when medata is ready.
      \param tile Tile data.
      \param lat Latitude.
      \param lng Longitude.
      \param xCoord X coordinate.
      \param yCoord Y coordinate.
      \param zoomLevel Zoom level.
      */
    void tileReady(QImage tile,
                   double lat,
                   double lng,
                   int xCoord,
                   int yCoord,
                   int zoomLevel);

    /*! \brief Signaled when medata is ready.
      \param lat Latitude.
      \param lng Longitude.
      \param fieldName Name of the asked field.
      \param data Data.
      */
    void metaReady (double lat,
                    double lng,
                    QString fieldName,
                    QString data);

    /*! \brief Signal that reports network state.
      \param QAbstractSocket::SocketState state State.
      \note I we use QNetworkAccessManager, this signal is not available.
            We must then use QNetworkAccessManager::networkAccessibleChanged.
      */
    void networkState(int state, QString statusMsg);

    /*! \brief Signal which commands GSVWrapper to process request queue.
      \note This is private signal.
    */
    void newRequest();

    void getTile(QString requestId,
                 QString pid,
                 int zoomLevel,
                 int x,
                 int y,
                 int priority);
};

//the exported function
extern "C" MY_EXPORT
{
    GSVWrapper* getInstance();
}

/*!
 * @}
 */

#endif // GSVWRAPPER_H
