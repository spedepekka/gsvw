/*
 */
/*!
 * \file filehandler.cpp
 * \weakgroup filehandler
 *
 * @{
 */

#include "filehandler.h"

/******************************************************************************/
/*!
  * \brief Checks whether the cache directory exists, and if not, creates it
  */
/******************************************************************************/
FileHandler::FileHandler(QObject *parent):
        QObject(parent)
{
    path = QDir::homePath() + "/GSVWrapperCache";

    QDir cache(path);
    if (!cache.exists()) {
        cache.setPath(".");
        if (!cache.mkdir(path))
            emit fileHandlerError(IOError, QString("FileHandler::FileHandler(): Couldn't create directory %1").arg(path));
    }
}

/******************************************************************************/
/*!
  * Overwritten function that moves GSVWrapper-object to given thread.
  * \param thread Pointer to thread where to move this object.
  * \note This function just calls QObject::moveToThread(), but one can write
  *       own code here.
  */
/******************************************************************************/
void FileHandler::moveToThread(QThread *thread)
{
    QObject::moveToThread(thread);
}

/******************************************************************************/
/*!
  * \brief Forms the filename of a tile based on the given coordinates
  * \param lat Latitude
  * \param lng Longitude
  * \param xCoord x-coordinate of tile in panorama
  * \param yCoord y-coordinate of tile in panorama
  * \param zoomLevel Zoom level of the tile
  * \returns Filename of tile
  */
/******************************************************************************/
QString FileHandler::formTileFileName(double lat, double lng, int xCoord, int yCoord,
                                      int zoomLevel)
{
    QString fileName = QString("%6/%1_%2_%3_%4_%5.jpg")
                       .arg(QString::number(lat, 'f'))
                       .arg(QString::number(lng, 'f'))
                       .arg(QString::number(xCoord))
                       .arg(QString::number(yCoord))
                       .arg(QString::number(zoomLevel))
                       .arg(path);

    return fileName;
}

/******************************************************************************/
/*!
  * \brief Forms the filename of XML metadata -file based on the given coordinates
  * \param lat Latitude
  * \param lng Longitude
  * \returns Filename of metadata file
  */
/******************************************************************************/
QString FileHandler::formXMLFileName(double lat, double lng)
{
    QString fileName = QString("%3/%1_%2.xml")
                       .arg(QString::number(lat, 'f'))
                       .arg(QString::number(lng, 'f'))
                       .arg(path);

    return fileName;
}

/******************************************************************************/
/*!
  * \brief Returns stored metadata based on given coordinates
  * \param lat Latitude
  * \param lng Longitude
  * \returns The stored metadata as a QString.
             If file is not found, empty QString is returned.
  */
/******************************************************************************/
QString FileHandler::getMetadata(double lat, double lng)
{
    QString fileName = formXMLFileName(lat, lng);
    QString xml;
    QFile file(fileName);

    if (!file.exists()) {
        emit fileHandlerError(NotFound, QString("FileHandler::FileHandler(): Metadata file %1 not found").arg(fileName));
        return QString("");
    }

    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        QString line;
        do {
            line = stream.readLine();
            xml.append(line);
            xml.append("\r\n");
        } while (!line.isNull());
        file.close();
    } else {
        qDebug() << QString("FileHandler::getMetadata(): Unable to open %1").arg(fileName);
        emit fileHandlerError(IOError, QString("FileHandler::getMetadata(): Unable to open %1").arg(fileName));
        return QString("");
    }

    return xml;
}

/******************************************************************************/
/*!
  * \brief Returns a stored tile based on the given coordinates
  * \param lat Latitude
  * \param lng Longitude
  * \param xCoord x-coordinate of tile in panorama
  * \param yCoord y-coordinate of tile in panorama
  * \param zoomLevel Zoom level of the tile
  * \returns The requested tile as a QImage.
             If something went wrong or image is not found null QImage is returned
  */
/******************************************************************************/
QImage FileHandler::getTile(double lat, double lng, int xCoord, int yCoord, int zoomLevel)
{
    QString fileName = formTileFileName(lat, lng, xCoord, yCoord, zoomLevel);
    QImage tile;
    QFile file(fileName);

    if (!file.exists()) {
        emit fileHandlerError(NotFound, QString("FileHandler::FileHandler(): Tile file %1 not found").arg(fileName));
        return QImage(); // Return null-image
    }

    if (!tile.load(fileName)) {
        emit fileHandlerError(IOError, QString("FileHandler::getTile(): Unable to open %1").arg(fileName));
        return QImage(); // Return null-image
    }

    return tile;
}

/******************************************************************************/
/*!
  * \brief Stores the provided metadata as a file in the cache directory
  * \param lat Latitude
  * \param lng Longitude
  * \param xml The data to be stored
  * \returns A boolean indicating success or failure
  */
/******************************************************************************/
bool FileHandler::writeXML(double lat, double lng, QString xml)
{
    QString fileName = formXMLFileName(lat, lng);
    QFile file(fileName);

    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&file);
        out << xml << endl;
        file.close();
        emit metadataAvailable(lat, lng);
        return true;
    } else {
        qDebug() << QString("FileHandler::writeXML(): Unable to open %1").arg(fileName);
        emit fileHandlerError(IOError, QString("FileHandler::writeXML(): Unable to open %1").arg(fileName));
        return false;
    }
}

/******************************************************************************/
/*!
  * \brief Stores the provided QImage as a file in the cache directory
  * \param tile The tile to be stored
  * \param lat Latitude
  * \param lng Longitude
  * \param xCoord x-coordinate of tile in panorama
  * \param yCoord y-coordinate of tile in panorama
  * \param zoomLevel Zoom level of the tile
  * \returns A boolean indicating success or failure
  */
/******************************************************************************/
bool FileHandler::writeTile(QImage tile, double lat, double lng,
                            int xCoord, int yCoord, int zoomLevel)
{
    QString fileName = formTileFileName(lat, lng, xCoord, yCoord, zoomLevel);

    if (tile.save(fileName, 0, 100)) {
        emit tileAvailable(lat, lng, xCoord, yCoord, zoomLevel);
        return true;
    } else {
        qDebug() << QString("FileHandler::writeTile(): saving tile %1 failed").arg(fileName);
        emit fileHandlerError(IOError, QString("FileHandler::writeTile(): saving tile %1 failed").arg(fileName));
        return false;
    }
}

/******************************************************************************/
/*!
  * \brief Deletes all .jpg and .xml files from the cache directory
  */
/******************************************************************************/
void FileHandler::clearCache()
{
    QDir cache(path);
    QStringList filters;
    filters << "*.jpg" << "*.xml";
    cache.setNameFilters(filters);
    cache.setFilter(QDir::Files);
    cache.setSorting(QDir::Size);

    QFileInfoList list = cache.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (!cache.remove(fileInfo.fileName()))
            emit fileHandlerError(IOError,
                                  QString("FileHandler::clearCache(): Could not delete file %1")
                                  .arg(fileInfo.absoluteFilePath()));
    }
}

/*!
 * @}
 */
