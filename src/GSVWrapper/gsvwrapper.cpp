/*!
 * \weakgroup gsvwrapper
 * @{
 */

#include "gsvwrapper.h"
#include "data.h"

/******************************************************************************/
/*!
  * \brief Default constructor.
  */
/******************************************************************************/
GSVWrapper::GSVWrapper(QObject *parent):
        QObject(parent)
{
    setVerbose(false);
    myThread = new QThread();
    moveToThread(myThread);
    printThreads();
    myThread->start();

    // Connect signals

    QObject::connect(&currentPanorama, SIGNAL(zoomLevelReady(int)),
                     this, SLOT(panoramasZoomLevelReady(int)));

    QObject::connect(this, SIGNAL(newRequest()), this, SLOT(processQueue()), Qt::QueuedConnection);

    QObject::connect(&networkhandler, SIGNAL(networkState(int,QString)),
                     this, SLOT(networkStateChanged(int,QString)),
                     Qt::QueuedConnection);
    QObject::connect(&networkhandler, SIGNAL(tileReady(QImage, QString, int, int)),
                     this, SLOT(imageDataReady(QImage, QString, int, int)));
    QObject::connect(&networkhandler, SIGNAL(metaReady(QString, QString)),
                     this, SLOT(handleMetadata(QString, QString)),
                     Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(getTile(QString,QString,int,int,int,int)),
                     &networkhandler, SLOT(getTile(QString,QString,int,int,int,int)),
                     Qt::QueuedConnection);

    // Error signals
    QObject::connect(&filehandler, SIGNAL(fileHandlerError(int,QString)),
                     this, SLOT(handleFileError(int,QString)),
                     Qt::QueuedConnection);
    QObject::connect(&networkhandler, SIGNAL(networkHandlerError(int,QString)),
                     this, SLOT(handleNetworkError(int,QString)),
                     Qt::QueuedConnection);
}

/******************************************************************************/
/*!
  * \brief Default desctructor.
  */
/******************************************************************************/
GSVWrapper::~GSVWrapper()
{
}

/*!
  * Sets verbose on or off.
  * \param val True sets verbose ON and false sets it OFF.
  */
void GSVWrapper::setVerbose(bool val)
{
    verbose = val;
}

/******************************************************************************/
/*!
  * Overwritten function that moves GSVWrapper-object to given thread.
  * \param thread Pointer to thread where to move this object.
  */
/******************************************************************************/
void GSVWrapper::moveToThread(QThread *thread)
{
    QObject::moveToThread(thread);
    filehandler.moveToThread(thread);
    networkhandler.moveToThread(thread);
    xmlParser.moveToThread(thread);
}

/******************************************************************************/
/*!
  * Debug-funtion.
  * \todo Remove this.
  */
/******************************************************************************/
void GSVWrapper::printThreads()
{
    qDebug() << "Printing threads";
    qDebug() << "myThread" << myThread;
    qDebug() << "GSVWrapper thread" << thread();
    qDebug() << "FileHandler thread" << filehandler.thread();
    qDebug() << "NetworkHandler thread" << networkhandler.thread();
    qDebug() << "NetworkHandler nam thread" << networkhandler.nam.thread();
    qDebug() << "XmlParse thread" << xmlParser.thread();

    // Check that they are the same thread
    QList<QThread*> threads;
    threads.append(myThread);
    threads.append(thread());
    threads.append(filehandler.thread());
    threads.append(networkhandler.thread());
    threads.append(networkhandler.nam.thread());
    threads.append(xmlParser.thread());
    if (threads.size() != threads.count(myThread))
        qDebug() << "GSVWrapper: Warning: Threads are not the same thread.";
}

/******************************************************************************/
/*!
  * Function that handles GSVWrapper errors. When needed this emits error
  * outside GSVWrapper.
  * \note File and network errors have own slots.
  * \param type Type of error.
  * \param error Error string that tells more about error.
  * \todo Finish this function
  */
/******************************************************************************/
void GSVWrapper::handleGSVError(int type, QString error)
{
    switch (type) {
    case RequestNotFound:
        qDebug() << QString("GSV error: %1").arg(error);
        break;
    case UnknownNetworkState:
        qDebug() << QString("GSV error: %1").arg(error);
        emit gsvWrapperError(type, error);
        break;
    case NullTile:
        qDebug() << QString("GSV error: %1").arg(error);
        break;
    case UnknownRequestType:
        qDebug() << QString("GSV error: %1").arg(error);
        break;
    case EmptyPanoID:
        qDebug() << QString("GSV error: %1").arg(error);
        break;
    case DuplicateRequest:
        qDebug() << QString("GSV error: %1").arg(error);
        break;

    default:
        qDebug() << QString("Unknown GSV error: %1, %2").arg(type).arg(error);
        emit gsvWrapperError(type, error);
        break;
    }
}

/******************************************************************************/
/*!
  * Function that handles file errors. When needed this emits error
  * outside GSVWrapper.
  * \param type Type of error.
  * \param error Error string that tells more about error.
  */
/******************************************************************************/
void GSVWrapper::handleFileError(int type, QString error)
{
    switch (type) {
    case FileHandler::Undefined:
        qDebug() << QString("Undefined file error: %1").arg(error);
        emit gsvWrapperError(type, error);
        break;
    case FileHandler::IOError:
        qDebug() << QString("IOError: %1").arg(error);
        emit gsvWrapperError(type, error);
        break;
    case FileHandler::NotFound: // This happens a lot and this is not an error
        // qDebug() << QString("%1").arg(error);
        //emit gsvWrapperError(type, error);
        break;
    default:
        qDebug() << QString("Unknown file error: %1").arg(error);
        emit gsvWrapperError(type, error);
        break;
    }
}

/******************************************************************************/
/*!
  * Function that handles network errors. When needed this emits error
  * outside GSVWrapper.
  * \param type Type of error.
  * \param error Error string that tells more about error.
  * \todo Finish this function
  */
/******************************************************************************/
void GSVWrapper::handleNetworkError(int type, QString error)
{
    switch (type) {
    case NetworkHandler::ImageLoadError:
        qDebug() << QString("Network error: %1").arg(error);
        break;
    default:
        qDebug() << QString("Unknown network error: %1").arg(error);
        emit gsvWrapperError(type, error);
        break;
    }
}

/******************************************************************************/
/*!
  * Function that handles xml errors. When needed this emits error
  * outside GSVWrapper.
  * \param type Type of error.
  * \param error Error string that tells more about error.
  * \todo Finish this function
  */
/******************************************************************************/
void GSVWrapper::handleXmlError(int type, QString error)
{
    switch (type) {
    case XmlParseError:
        qDebug() << QString("%1").arg(error);
        emit gsvWrapperError(type, error);
        break;
    default:
        qDebug() << QString("Unknown xml error: %1").arg(error);
        emit gsvWrapperError(type, error);
        break;
    }
}

/******************************************************************************/
/*!
  * Function that handles ready metadata xml string.
  * \param xmlStr Xml string that includes metadata.
  * \param requestId Unique string for metadata.
  */
/******************************************************************************/
void GSVWrapper::handleMetadata(QString xmlStr, QString requestId)
{
    qDebug() << "GSVWrapper::handleMetadata: Request id:" << requestId;

    QSharedPointer<Request> req = requestMap.value(requestId, QSharedPointer<Request>());
    if (req.isNull()) {
        handleGSVError(int(RequestNotFound), tr("Could not find request for id %1").arg(requestId));
        return;
    }

    qDebug() << QString("GSVWrapper::handleMetadata: request is for lat %1 and lng %2")
            .arg(req->lat).arg(req->lng);

    // Parse XML
    Metadata *meta = xmlParser.parse(xmlStr);
    if (meta == 0) {
        handleXmlError(int(XmlParseError), "GSVWrapper::handleMetadata: Parsing XML failed.");
        removeFromQueue(requestId);
        return;
    }

    QSharedPointer<Metadata> sharedMeta = QSharedPointer<Metadata>(meta);

    // Set metadata for this request
    req->setMetadata(sharedMeta);

    // There must be pano_id
    if (sharedMeta->getFieldByName("pano_id").isEmpty()) {
        handleGSVError(int(EmptyPanoID), tr("pano_id is empty"));
        removeFromQueue(requestId);
        return;
    }

    // If this request is meta request for pano request
    if (req->friendRequest != 0) {
        qDebug() << QString("Setting metadata from %1 to request %2")
                .arg(req->id).arg(req->friendRequest->id);
        req->friendRequest->setMetadata(sharedMeta); // Panorama request now knows pano_id
        req->friendRequest->setState(Request::Unready); // Fetch panorama
        emit newRequest();
    }

    // Write metadata to file
    if (!filehandler.writeXML(sharedMeta->lat.toDouble(),
                              sharedMeta->lng.toDouble(),
                              xmlStr)) {
        // This error is handled through fileHandlerError-signal
        removeFromQueue(requestId);
        return;
    }

    switch (req->type()) {
    case Request::Pano:
        break;
    case Request::Meta:
        if (req->friendRequest == 0)
            emit metaReady(req->lat, req->lng, req->fieldName,
                           sharedMeta->getFieldByName(req->fieldName));
        break;
    default:
        handleGSVError(UnknownRequestType, tr("Unkown request type"));
        break;
    }

    req->setState(Request::Ready);
    printRequests(); // Debug // TODO: Remove
//    removeFromQueue(requestId);
}

/******************************************************************************/
/*!
  * \brief Read image when data is available
  */
/******************************************************************************/
void GSVWrapper::imageDataReady(QImage image, QString requestId, int x, int y)
{
    qDebug() << QString("Received tile data from networkHandler. Request id %1, x %2, y %3")
            .arg(requestId).arg(x).arg(y);

    QSharedPointer<Request> req = requestMap.value(requestId, QSharedPointer<Request>());

    if (req.isNull()) {
        handleGSVError(int(RequestNotFound), QString("Can't find request %1").arg(requestId));
        return;
    }

    // Check null tile
    // TODO: This comparison should be better
    if (image != QImage(GSVData::nullTile)) { // TODO: Does this comparison work?
        qDebug() << QString("Tile is for lat %1, lng %2, zoom %3")
                .arg(req->lat).arg(req->lng).arg(req->zoomLevel);
        filehandler.writeTile(image, req->getMetadata()->lat.toDouble(),
                              req->getMetadata()->lng.toDouble(),
                              x, y, req->zoomLevel);

        // Save tile to current panorama
        Tile *t = new Tile(x, y, req->zoomLevel, image);
        req->getPanorama()->addTile(*t);

        emit tileReady(image, req->lat, req->lng, x, y, req->zoomLevel);
    } else {
        handleGSVError(int(NullTile), "Got null tile");
    }

    req->setState(Request::Ready);
    printRequests(); // Debug // TODO: Remove
//    removeFromQueue(requestId);
}

/******************************************************************************/
/*!
  * Current panorama emits signals every time when zoom level is ready.
  * This slot catches that signal.
  */
/******************************************************************************/
void GSVWrapper::panoramasZoomLevelReady(int zoomLevel)
{
    qDebug() << QString("Current panoramas zoom level %1 ready").arg(zoomLevel);
}

/******************************************************************************/
/*!
  * Slot that process queue. Connect this allways as Qt::QueuedConnection.
  * This function doesn't need mutexes because its called as QueuedConnection.
  */
/******************************************************************************/
void GSVWrapper::processQueue()
{
    if (requestQueue.isEmpty()) {
        qDebug() <<  "GSVWrapper::processQueue(): requestQueue is empty";
        return;
    } else {
        qDebug() << "GSVWrapper::processQueue()";
        printRequests(); // Debug
    }

    foreach(QSharedPointer<Request> req, requestQueue) {
        switch (req->state()) {
        case Request::Unready:
            req->setState(Request::Running);
            switch (req->type()) {
            case Request::Pano: {
                    qDebug() << "Requesting panorama" << req->lat << req->lng;
                    if (req->getMetadata() != 0) {
                        // Metadata is already fetched
                        QVector2D v = getZoomLevel(req->zoomLevel);
                        qDebug() << QString("Zoomlevel %1 max x = %2 and max y = %3").arg(req->zoomLevel).arg(v.x()).arg(v.y());

                        // Here is tile logic
                        for (int x = 0; x < v.x(); x++) {
                            for (int y = 0; y < v.y(); y++) {

                                QImage tile = filehandler.getTile(req->getMetadata()->lat.toDouble(),
                                                                  req->getMetadata()->lng.toDouble(),
                                                                  x, y, req->zoomLevel);
                                if (tile.isNull()) { // Must get tile from network
                                    networkhandler.getTile(req->id,
                                                           req->getMetadata()->pano_id,
                                                           req->zoomLevel,
                                                           x, y, req->priority);
                                } else { // Tile found from cache
                                    // Save tile to current panorama
                                    Tile *t = new Tile(x, y, req->zoomLevel, tile);
                                    req->getPanorama()->addTile(*t);

                                    emit tileReady(tile, req->lat, req->lng, x, y, req->zoomLevel);
                                }
                            }
                        }

                    } else { // Panorama request, but must fetch first metadata
                        qDebug() << "Get metadata first for" << req->id;
                        getMeta(req);
                    }
                }
                break;
            case Request::Meta:
                qDebug() << "Requesting metafield" << req->fieldName;
                networkhandler.getMeta(req->id, req->lat, req->lng);
                break;
            default:
                qDebug() << "GSVWrapper::handleMetadata: Error: Unkown request type";
                break;
            }
            break;
            case Request::Running:
            break;
            case Request::Ready:
            break;
            default:
            qDebug() << "Unknown request state";
            break;
        }
    }

    removeReadyRequests();
}

/******************************************************************************/
/*!
  * Remove request from requestQueue and requestMap.
  * \param id Request ID to remove.
  */
/******************************************************************************/
void GSVWrapper::removeFromQueue(QString id)
{
    QSharedPointer<Request> req = requestMap.value(id, QSharedPointer<Request>());
    qDebug() << QString("Removing %1 request %2")
            .arg(int(req->type())).arg(id);

    requestMap.remove(id);
    requestQueue.removeAll(req);
}

/******************************************************************************/
/*!
  * Remove requests that are ready.
  */
/******************************************************************************/
void GSVWrapper::removeReadyRequests()
{
    QStringList ids;
    foreach(QSharedPointer<Request> req, requestQueue) {
        if(req->state() == Request::Ready)
            ids.append(req->id);
    }
    foreach(QString str, ids)
        removeFromQueue(str);
}

/******************************************************************************/
/*!
  * \brief Insert request to appropriate position in requestQueue.
  * \note This function emits newRequest-signal that process queue.
          Signal must be connected as queued connection.
  */
/******************************************************************************/
void GSVWrapper::insertRequest(QSharedPointer<Request> request)
{
    qDebug() << QString("Inserting %1 request %2")
            .arg(int(request->type())).arg(request->id);

    bool duplicate = false;
    foreach(QSharedPointer<Request> r, requestQueue) {
        if (r->id == request->id)
            duplicate = true;
    }

    if (!duplicate)
        requestQueue.append(request);
    else
        handleGSVError(int(DuplicateRequest), tr("Warning: Inserting duplicate request to requestQueue."));

    if(!requestMap.contains(request->id))
        requestMap.insert(request->id, request);
    else
        handleGSVError(int(DuplicateRequest), tr("Warning: Inserting duplicate request to requestMap."));

    organizeRequests();
    emit newRequest(); // Must be connected as queued connection
}

/******************************************************************************/
/*!
  * \brief Organize requests smallest priority first.
  */
/******************************************************************************/
void GSVWrapper::organizeRequests()
{
    qSort(requestQueue.begin(), requestQueue.end(), Request::requestCompareSharedPtr);
}

/******************************************************************************/
/*! Debug-function. */
/******************************************************************************/
void GSVWrapper::printRequests()
{
    QStringList ids;
    foreach(QSharedPointer<Request>r, requestQueue) {
        ids.append(QString("(%1): ").arg(int(r->type())));
        ids.append(QString("%1  ").arg(r->id));
    }
    qDebug() << QString("There is %1 requests in queue").arg(ids.size()/2) << ids;
}

/******************************************************************************/
/*!
  * \brief Clear cache.
  */
/******************************************************************************/
void GSVWrapper::clearCache()
{
    filehandler.clearCache();
}

/******************************************************************************/
/*!
  * \brief Get panorama.

  * This slot commands GSVWrapper to get metadata from GSV. If metadata is already
  * in cache, its returned from there. Metadata will be returned via
  * metaReady-signal. Errors are signaled via gsvWrapperError-signal.

  * \param lat Latitude.
  * \param lng Longitude.
  * \param zoomLevel Zoom level.
  * \note Returns immediately.
  * \note Priority 1 is always used for meta request.
  */
/******************************************************************************/
void GSVWrapper::getMeta(double lat, double lng, QString fieldName)
{
    qDebug() << "GSVWrapper::getMeta(double lat, double lng, QString fieldName):"
            << lat << lng << fieldName;

    // First try to find metadata from file
    QString metaXml = filehandler.getMetadata(lat, lng);
    if (metaXml.isEmpty()) {
        // Metadata is not in cache
        QString requestId = QUuid::createUuid().toString();
        // Priority 1 is used always for meta requests
        QSharedPointer<Request> req = QSharedPointer<Request>
                                      (new Request(Request::Meta, requestId, lat, lng, 0, fieldName, 1));
        qDebug() << "Requesting metadata from networkHandler. Request id:" << requestId;
        insertRequest(req);
    } else { // Metadata found from file
        qDebug() << "Metadata found from file";
        Metadata *meta = xmlParser.parse(metaXml);
        if (meta) {
            QString data = meta->getFieldByName(fieldName);
            qDebug() << QString("Field %1 = %2").arg(fieldName).arg(data);
            emit metaReady(lat, lng, fieldName, data);
        } else {
            handleXmlError(int(XmlParseError), "GSVWrapper::handleMetadata: Parsing XML failed.");
        }
    }
}

/******************************************************************************/
/*!
  * \brief Get panorama.
  * \param lat Latitude.
  * \param lng Longitude.
  * \param zoomLevel Zoom level.
  * \param priority Priority [0,9].
  *
  * This slot commands GSVWrapper to get whole panorama from GSV. Panorama will
  * be returned via tileReady-signals. Errors are signaled via
  * gsvWrapperError-signal.
  *
  * \note Returns immediately.
  */
/******************************************************************************/
void GSVWrapper::getPano(double lat, double lng, int zoomLevel, int priority)
{
    qDebug() << "GetPano" << lat << lng << zoomLevel << priority;

    // Reset old requests
    networkhandler.reset();
    currentPanorama.clear();

    QString requestId = QUuid::createUuid().toString();
    QSharedPointer<Request> req = QSharedPointer<Request>
                                  (new Request(Request::Pano, requestId, lat, lng, zoomLevel, "", priority));
    insertRequest(req);
}

/******************************************************************************/
/*!
  * \brief Reset GSVWrapper.
  *
  * Resets GSWrapper. Empties queues and all previous commands. This don't
  * clear cache.
  *
  */
/******************************************************************************/
void GSVWrapper::reset()
{
    networkhandler.reset();
    requestMap.clear();

//    for(int i = 0; i < requestQueue.size(); i++)
//        delete requestQueue[i];

    requestQueue.clear();
}

/******************************************************************************/
/*! \brief Get metadata for given request.

  * This function is used to get metadata for panorama request.
  * \param r Pointer to panorama request.
  */
/******************************************************************************/
void GSVWrapper::getMeta(QSharedPointer<Request> r)
{
    qDebug() << "GSVWrapper::getMeta(Request *r):" << r->id;

    // First try to find metadata from file
    QString metaXml = filehandler.getMetadata(r->lat, r->lng);
    if (metaXml.isEmpty()) {
        // Metadata is not in cache
        QString requestId = QUuid::createUuid().toString();
        QSharedPointer<Request> req = QSharedPointer<Request>
                                      (new Request(Request::Meta, requestId, r->lat, r->lng, 0, ""));
        req->friendRequest = r;
        qDebug() << "Requesting metadata from networkHandler. Request id:" << requestId;
        insertRequest(req);
    } else { // Metadata found from file
        qDebug() << "Metadata found from file";
        handleMetadata(metaXml, r->id);
    }
}

/******************************************************************************/
/*!
  *
  */
void GSVWrapper::networkStateChanged(int type, QString statusMsg)
{
    if (type == int(NetworkHandler::Accessible))
        emit networkState(int(NetworkHandler::Accessible),
                          statusMsg);
    else if (type == int(NetworkHandler::NotAccessible))
        emit networkState(int(NetworkHandler::NotAccessible),
                          statusMsg);
    else if (type == int(NetworkHandler::UnknownAccessibility))
        emit networkState(int(NetworkHandler::UnknownAccessibility),
                          statusMsg);
    else if (type == int(NetworkHandler::DownloadProgress)) {} // Do nothing

    else if (type == int(NetworkHandler::ConnectionsReset)) {} // Do nothing

    else
        handleGSVError(UnknownNetworkState, statusMsg);
}

/******************************************************************************/
/*!
  * \brief Get a handle to an instance of this class.
  */
/******************************************************************************/
GSVWrapper* getInstance()
{
    GSVWrapper* instance = new GSVWrapper;

    return instance;
}

/*!
 * @}
 */
