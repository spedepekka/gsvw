/*
 * Author Tommi Käsmä
 */
#include "networkhandler.h"

/******************************************************************************/

NetworkHandler::NetworkHandler()
{
    QObject::connect(&nam,
                     SIGNAL(networkAccessibleChanged(
                             QNetworkAccessManager::NetworkAccessibility)),
                     this,
                     SLOT(networkAccessibleChangedSlot(
                             QNetworkAccessManager::NetworkAccessibility)));
}

/******************************************************************************/
/*!
  * Overwritten function that moves GSVWrapper-object to given thread.
  * \param thread Pointer to thread where to move this object.
  */
/******************************************************************************/
void NetworkHandler::moveToThread(QThread *thread)
{
    QObject::moveToThread(thread);
    nam.moveToThread(thread);
}

/******************************************************************************/
/*!
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) Loop through all the Url objects in the urlList if it isn't empty.
 *    <ul>
 *    <li>(0110) Pop Url object that was associated with the current reply
 *               object.
 *    <li>(0120) Leave loop.
 *    </ul>
 * <li>(0200) Return desired Url object.
 * </ul>
 */
/******************************************************************************/
Url NetworkHandler::popUrl(QNetworkReply *reply)
{
    Url url;

    /*0100*/
    if (!urlList.isEmpty()){
        for(int i = 0; i<urlList.size(); i++) {
            /*0110*/
            if (urlList[i].getReply() == reply){
                url = urlList.takeAt(i);
                /*0120*/
                break;
            }
        }
    } else {
        qDebug() << "no requests in list";
    }

    /*0200*/
    return url;
}

/******************************************************************************/

void NetworkHandler::pushUrl(Url url)
{
    urlList.append(url);
}


/******************************************************************************/
/*!
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) Create Url object with received parameters.
 * <li>(0200) Ask Url to get the network resource. Get reference to the reply.
 * <li>(0300) Connect the reply's signals to the right slots.
 * <li>(0400) Store Url object in the list.
 * </ul>
 */
/******************************************************************************/
void NetworkHandler::getMeta(QString requestId, double lat, double lng) {

    qDebug() << "NetworkHandler receieved metadata request:";
    qDebug() << "lat: " << lat << "lng: " << lng;
    qDebug() << "request id:" << requestId;

    /*0100*/
    Url url(lat, lng, requestId);

    /*0200*/
    QNetworkReply *reply = url.get(&nam);

    /*0300*/
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(downloadProgressChanged(qint64,qint64)));
    connect(reply, SIGNAL(finished()),
            this, SLOT(metaReceived()));

    /*0400*/
    pushUrl(url);
}



/******************************************************************************/
/*!
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) Map the request's priority to a priority level understood by the
 *            NetworkAccessManager.
 * <li>(0200) Create Url object with received parameters and the translated
              priority.
 * <li>(0300) Ask Url to get the network resource. Get reference to the reply.
 * <li>(0400) Connect the reply's signals to the right slots.
 * <li>(0500) Store Url object in the list.
 * </ul>
 */
/******************************************************************************/
void NetworkHandler::getTile(QString requestId,
                             QString pid,
                             int zoomLevel,
                             int x,
                             int y,
                             int priority)
{
    qDebug() << "NetworkHandler receieved tile request:";
    qDebug() << "   pano_id: " << pid;
    qDebug() << "   zoom: " << zoomLevel << "x,y: " << x << ","<<y;
    qDebug() << "   priority: " << priority;
    qDebug() << "   request id:" << requestId;

    /*0100*/
    QNetworkRequest::Priority networkPrio;

    // Priority should be [0,9] but if not its forced to these values
    if (priority > 5)
        networkPrio = QNetworkRequest::HighPriority;
    else if (priority == 5)
        networkPrio = QNetworkRequest::NormalPriority;
    else if (priority < 5 )
        networkPrio = QNetworkRequest::LowPriority;

    /*0200*/
    Url url(pid, zoomLevel, x, y, networkPrio, requestId);

    /*0300*/
    QNetworkReply *reply = url.get(&nam);

    /*0400*/
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(downloadProgressChanged(qint64,qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(networkErrorOccured(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()),
            this, SLOT(tileReceived()));

    /*0500*/
    pushUrl(url);
}



/******************************************************************************/
/*!
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) Loop through all the Url objects in the urlList.
 *    <ul>
 *    <li>(0110) Get reference to the reply object associated to the Url
 *    <li>(0110) Disconnect signals, abort network request and ask to delete
 *               the reply object when safely possible.
 *    </ul>
 * <li>(0200) Purge all Url objects from the list.
 * <li>(0300) Emit signal informing of reset.
 * </ul>
 */
/******************************************************************************/
void NetworkHandler::reset()
{
    QNetworkReply *reply;

    /*0100*/
    for (int i = 0; i < urlList.size(); i++){

        /*0110*/
        reply = urlList[i].getReply();

        /*0120*/
        if (reply != NULL) {
            reply->disconnect();
            reply->abort();
            reply->deleteLater();
        }
    }

    /*0200*/
    urlList.clear();

    /*0300*/
    emit NetworkHandler::networkState(int(NetworkHandler::ConnectionsReset),
                                      tr("All connections have been aborted"));
}


/******************************************************************************/
/*!
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) Get a reference to the QNetworkReply object that emitted the
 *            signal.
 * <li>(0200) Read the received data.
 * <li>(0300) Ask to delete the reply object.
 * <li>(0400) Pop Url associated to the reply from the urlList.
 * <li>(0500) Emit the received data along with the request identifier.
 * </ul>
 */
/******************************************************************************/
void NetworkHandler::metaReceived()
{
    QByteArray incomingData;
    Url url;

    /*0100*/
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

    qint64 byteCount = reply->bytesAvailable();
    if(byteCount == 0)
        qDebug() << "Warning: Metadata byte count is zero.";

    /*0200*/
    if(reply != 0){
        incomingData = reply->readAll();
    }

    /*0300*/
    reply->deleteLater();

    /*0400*/
    url = popUrl(reply);

    /*0500*/
    QString xmlStr(incomingData);
    emit metaReady(xmlStr, url.getId());
}


/******************************************************************************/
/*!
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) Get a reference to the QNetworkReply object that emitted the
 *            signal.
 * <li>(0200) Read the received data.
 * <li>(0300) Ask to delete the reply object.
 * <li>(0400) Pop Url associated to the reply from the urlList.
 * <li>(0500) Emit the received data along with the request identifier or emit
 *            an error message in case image could not be loaded from received
 *            data.
 * </ul>
 */
/******************************************************************************/
void NetworkHandler::tileReceived()
{
    qDebug() << "NetworkHandler::tileReceived()";

    QImage image;
    QByteArray incomingData;
    Url url;

    /*0100*/
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

    qint64 byteCount = reply->bytesAvailable();
    if(byteCount == 0)
        qDebug() << "Warning: Image byte count is zero.";

    /*0200*/
    if(reply != 0){
        incomingData = reply->readAll();
    }
    else
        qDebug() << "tileReceived(): reply was null";

    /*0300*/
    reply->deleteLater();

    /*0400*/
    url = popUrl(reply);

    /*0500*/
    if ( image.loadFromData(incomingData) )
        emit tileReady(image, url.getId(), url.x, url.y);
    else
        emit networkHandlerError(int(NetworkHandler::ImageLoadError),
                             tr("GSV could not load image from network."));
}


/******************************************************************************/
/*!
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) Get a reference to the QNetworkReply object that emitted the
 *            signal.
 * <li>(0200) Form the appropriate download progress message string.
 * <li>(0300) Emit signal that informs of the download progress change.
 * </ul>
 */
/******************************************************************************/
void NetworkHandler::downloadProgressChanged(qint64 received, qint64 total)
{
    QString statusMsg;

    /*0100*/
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

    /*0200*/
    if (total != 0){
        if (total == -1)
            statusMsg = tr("Downloading %1. %2 bytes")
                    .arg((reply->url()).toString()).arg(received);
        else
            statusMsg = tr("Downloading %1. %2 bytes out of %3")
                    .arg((reply->url()).toString()).arg(received).arg(total);

        /*0300*/
        emit networkState(int(NetworkHandler::DownloadProgress), statusMsg);
    }
}


/******************************************************************************/
/*!
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) Get a reference to the QNetworkReply object that emitted the
 *            signal.
 * <li>(0200) Get the error message string.
 * <li>(0300) Emit the error forwards.
 * </ul>
 */
/******************************************************************************/
void NetworkHandler::networkErrorOccured(QNetworkReply::NetworkError errorCode)
{
    QString errorMsg;

    /*0100*/
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());

    /*0200*/
    errorMsg = reply->errorString();

    /*0300*/
    emit networkHandlerError(int(errorCode), errorMsg);
}


/******************************************************************************/
/*!
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) Emit a networkState signal with the new accessibility status, or
 * <li>(0200) Emit an error signal in case the accessibility update was faulty.
 * </ul>
 */
/******************************************************************************/
void NetworkHandler::networkAccessibleChangedSlot(
        QNetworkAccessManager::NetworkAccessibility accessible)
{
    /*0100*/
    if (accessible == QNetworkAccessManager::Accessible)
        emit networkState(int(NetworkHandler::Accessible),
                          tr("Network available"));
    else if (accessible == QNetworkAccessManager::NotAccessible)
        emit networkState(int(NetworkHandler::NotAccessible),
                          tr("Network unavailable"));
    else // accessible == QNetworkAccessManager::UnknownAccessibility
        emit networkState(int(NetworkHandler::UnknownAccessibility),
                          tr("Network availability unknown"));
}
