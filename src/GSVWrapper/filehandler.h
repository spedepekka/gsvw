/*
 */
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

/*!
 * \defgroup filehandler Filehandler
 * @{
 */

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QObject>
#include <QThread>

/******************************************************************************/
/*! \class FileHandler
  \brief Class that handles files.
  \todo Comment this class.
  */
/******************************************************************************/
class FileHandler : public QObject
{
    Q_OBJECT

public:
    /*! \brief This enum defines possible errors for file handler
     */
    enum FileHandlerError {
        Undefined,
        IOError,
        NotFound
    };

    explicit FileHandler(QObject *parent = 0); //!< A Constructor

    void moveToThread(QThread *thread);

    QString getMetadata(double lat, double lng);
    QImage getTile(double lat, double lng, int xCoord, int yCoord, int zoomLevel);
    void clearCache();

    QString path; //!< Path to cache directory

signals:
    /*! \ingroup filehandler
    * \brief Indicates that a tile is available for reading
    * \param lat Latitude
    * \param lng Longitude
    * \param xCoord x-coordinate of tile in panorama
    * \param yCoord y-coordinate of tile in panorama
    * \param zoomLevel Zoom level of the tile
    */
    void tileAvailable(double lat, double lng, int xCoord, int yCoord, int zoomLevel);
    /*! \ingroup filehandler
    * \brief Indicates that metadata is available for reading
    * \param lat Latitude
    * \param lng Longitude
    */
    void metadataAvailable(double lat, double lng);
    /*! \ingroup filehandler
    * \brief Indicates an error
    * \param type Type of error
    * \param error Textual description of error
    */
    void fileHandlerError(int type, QString error);

public slots:
    bool writeXML(double lat, double lng, QString xml);
    bool writeTile(QImage tile, double lat, double lng, int xCoord, int yCoord, int zoomLevel);

#ifndef UNIT_TEST
private:
#else
public:
#endif
    QString formTileFileName(double lat, double lng, int xCoord, int yCoord, int zoomLevel);
    QString formXMLFileName(double lat, double lng);
};

#endif // FILEHANDLER_H

/*!
 * @}
 */
