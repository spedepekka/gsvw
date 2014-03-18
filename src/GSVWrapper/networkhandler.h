/*
 * Author: Tommi Käsmä
 */
#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QDebug>
#include <QImage>
#include <QList>
#include <QObject>
#include <QtNetwork>

#include "url.h"

namespace GSVNetwork {
    class NetworkHandler;
}

/******************************************************************************/
/*!
  * \ingroup networkhandler
  * \class NetworkHandler
  * \brief NetworkHandler handles communication to GSV.
  *
  * This class handles the networking functionality needed to communicate with
  * Google Street View static API. Enables retrieval of GSV metadata based on
  * coordinates and retrieval of image tiles based on panorama id.
*/
/******************************************************************************/
class NetworkHandler: public QObject
{
    Q_OBJECT
public:

    /*! \enum NetworkStatus
     * \ingroup networkhandler
     * \brief This enum defines the types of the different networkstatus
     * messages.
     */
    enum NetworkStatus {
        UnknownAccessibility = 0,//!<UnknownAccessibility,
        NotAccessible,          //!<NotAccessible,
        Accessible,             //!<Accessible,
        DownloadProgress,       //!<DownloadProgress,
        ConnectionsReset        //!<ConnectionsReset
    };

    NetworkHandler();//!< A constructor \ingroup networkhandler

    void moveToThread(QThread *thread);

#ifndef UNIT_TEST
//private: // TODO: Remove comment
#else
public:
#endif
    QList<Url> urlList;//!< List of Url objects \ingroup networkhandler

    QNetworkAccessManager nam;//!< QNetworkAccessManager instance \ingroup networkhandler

    enum NetworkError {
        UndefinedError = 0,
        ImageLoadError
    };


    /*! \ingroup networhandler
     * \brief Returns an instance of Url from urlList based on the reply it
     * corresponds to. The Url is popped from the urlList.
     * \param *reply A pointer to the instance of QNetworkReply the desired Url
     *               corresponds to.
     * \return Url Desired instance of Url
     * \sa urlList
     * \sa Url
     */
    Url popUrl(QNetworkReply *reply);

    /*! \ingroup networhandler
     * \brief Appends the Url object to the urlList.
     * \param url The Url instance to push.
     * \sa urlList
     * \sa Url
     */
    void pushUrl(Url url);

public slots:

    /*! \ingroup networhandler
     * \brief Slot to iniate a network retrieval of metadata from GSV based on
     * coordinates.
     * \param requestId Unique identifier for this retrieval request.
     * \param lat Latitude
     * \param lng Longitude
     */
    void getMeta(QString requestId,
                 double lat,
                 double lng);

    /*! \ingroup networhandler
     * \brief Slot to iniate a network retrieval of an image tile from GSV
     * based on panorama id, zoomlevel and tile's indexes.
     * \param requestId Unique identifier for this retrieval request.
     * \param pid Panorama id
     * \param zoomLevel The zoom level
     * \param x X index of the desired tile
     * \param y Y index of the desired tile
     * \param priority Processing priority suggestion.
     */
    void getTile(QString requestId,
                 QString pid,
                 int zoomLevel,
                 int x,
                 int y,
                 int priority = 5);

    /*! \ingroup networhandler
     * \brief Slot to reset and abort current network requests. Currently
     * queued requests are ignored and already initiated requests are aborted.
     */
    void reset();

#ifndef UNIT_TEST
private slots:
#endif

    /*! \ingroup networhandler
     * \brief Slot to handle incoming metadata from GSV.
     * metaReady signal is emitted as a result.
     * \sa metaReady
     */
    void metaReceived();

    /*! \ingroup networhandler
     * \brief Slot to handle incoming tile data from GSV.
     * tileReady signal is emitted as a result.
     * \sa tileReady
     */
    void tileReceived();

    /*! \ingroup networhandler
     * \brief Slot to update download progress status of a download being
     * processed. networkState signal is emitted as a result.
     * \param received Number of bytes received.
     * \param total Number of total bytes.
     * \sa networkState
     */
    void downloadProgressChanged(qint64 received, qint64 total);

    /*! \ingroup networhandler
     * \brief Slot to handle errors in the processing of a download request.
     * networkHandlerError signal is emitted as a result.
     * \param code Error code.
     * \sa networkHandlerError
     */
    void networkErrorOccured(QNetworkReply::NetworkError code);

    /*! \ingroup networhandler
     * \brief Slot to update network accessibility status when it changes.
     * networkState signal is emitted as a result.
     * \param accessible New network accessibility.
     * \sa networkState
     */
    void networkAccessibleChangedSlot(
        QNetworkAccessManager::NetworkAccessibility accessible);

signals:

    /*! \ingroup networhandler
     * \brief Signal that contains the results of a metadata request.
     * \param metaXML metadata
     * \param requestId Unique identifier of the request this is a response to.
     * \sa getMeta
     * \sa metaReceived
     */
    void metaReady(QString metaXML, QString requestId);

    /*! \ingroup networhandler
     * \brief Signal that contains the results of a tile request.
     * \param tile Image tile data.
     * \param requestId Unique identifier of the request this is a response to.
     * \sa getTile
     * \sa tileReceived
     */
    void tileReady(QImage tile, QString requestId, int x, int y);

    /*! \ingroup networhandler
     * \brief Signal emitted on a change in the network status. Emitted when
     * a change occurs in accessibility, download progress or when reset slot
     * has been called.
     * \param type Status message type
     * \param statusMsg Human readable status change message.
     * \sa NetworkStatus
     */
    void networkState(int type, QString statusMsg);

    /*! \ingroup networhandler
     * \brief Signal emitted when an error in the processing of a request
     * occurs.
     * \param type Error type as defined in QNetworkReply::NetworkError
     * \param statusMsg Error message
     * \sa QNetworkReply::NetworkError
     */
    void networkHandlerError(int type, QString errorMsg);
};

#endif // NETWORKHANDLER_H
