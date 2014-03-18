/*!
 * \file metadata.h
 * \defgroup metadata Metadata
 * \ingroup panorama
 *
 * @{
 *
 *  Created on: Mar 30, 2011
 *      Author: Veijo Pesonen
 */

#ifndef METADATA_H
#define METADATA_H

#include <QMutex>
#include <QObject>
#include <QString>
#include <QVector>

#define LINK_ELEMENT_CNT 5 /* Number of elements in a link */


/******************************************************************************/
/*!
 * \ingroup metadata
 * \brief Object storing metadata of a panorama.
 *
 * This object stores a validated metadata. The object is capable of returning
 * either individual fields or the whole metadata in xml format.
 *
 * Validation of metadata is responsibility of a XMLParser object.
 *
 * \sa xmlparser
 */
/******************************************************************************/
class Metadata
{

public:

    /*! \enum GSVMetaCodingOrder
     * \ingroup metadata
     * \brief This enum defines in which order individual data fields need to
     * be coded when a link is added.
     */
    enum GSVMetaCodingOrder {GSVCopyright,         //!<GSVCopyright,
                             GSVText,              //!<GSVText
                             GSVRegion,            //!<GSVRegion
                             GSVCountry,        //!<GSVCountry
                             GSVDataFlag,        //!<GSVDataFlag
                             GSVImageHeight,    //!<GSVImageHeight
                             GSVImageWidth,        //!<GSVImageWidth
                             GSVLat,            //!<GSVLat
                             GSVLng,            //!<GSVLng
                             GSVNumZoomeLevels, //!<GSVNumZoomeLevels
                             GSVOriginalLat,    //!<GSVOriginalLat
                             GSVOriginalLng,    //!<GSVOriginalLng
                             GSVPanoId,            //!<GSVPanoId
                             GSVTileHeight,        //!<GSVTileHeight
                             GSVTileWidth,        //!<GSVTileWidth
                             GSVPanoYawDeg,        //!<GSVPanoYawDeg
                             GSVProjectionType, //!<GSVProjectionType
                             GSVTiltPitchDeg,    //!<GSVTiltPitchDeg
                             GSVTiltYawDeg,        //!<GSVTiltYawDeg
                             IndexNmOfGSVLinks        //!<IndexNmOfGSVLinks
                             /* Links are added after these obligatory fields */
    };

    Metadata(); //!< A constructor \ingroup metadata
    virtual ~Metadata(); //!< A destructor \ingroup metadata

    /*! \ingroup metadata
     * \brief Returns metadata in xml format.
     * \return metadata Metadata in xml format
     */
    QString getRawXml();


    /*! \ingroup metadata
     * \brief This function takes metadata encoded to a string. Semicolon is
     *     used on a string as a delimiter between different fields.
     * \param codedData
     *
     * \return TRUE if data was updated correctly, FALSE otherwise
     * \sa xmlparser
     */
    bool setGSVMetadata(const QString &codedData, const QString &rawXmlData);

    /*! \ingroup metadata
     * \brief This function takes metadata encoded to a string. Semicolon is
     *     used on a string as a delimiter between different fields.
     * \param codedData
     *
     * \return QString() (isNull = true) when cannot find variable by given name.
     * \return When variable is found, QString(VALUE) is returned. Returned string
               might be empty or not.
     * \sa xmlparser
     */
    QString getFieldByName(const QString fieldName);


    /*! \ingroup metadata
     * \brief Returns all links stored as metadata of this panorama.
     * \return links Links as a list.
     * \sa GSVLinkCodingOrder
     */
    QList<QStringList> getLinks();

    QMutex mdLock; //!< A lock

    QString xmlData; //!< Metadata in xml format

    /* Data properties */
    QString copyright; //!< Copyright owner
    QString text; //!< Text
    QString region; //!< Region
    QString country; //!< Country
    QString data_flag; //!< Data flag

    QString image_height; //!< Image height
    QString image_width; //!< Image width
    QString lat; //!< Latitude
    QString lng; //!< Longitude
    QString num_zoom_levels; //!< Zoom level
    QString original_lat; //!< Original latitude
    QString original_lng; //!< Original longitude
    QString pano_id; //!< GSVLinkPanoId
    QString tile_height; //!< Tile height
    QString tile_width; //!< Tile width

    /* Projection properties */
    QString pano_yaw_deg;
    QString projection_type;
    QString tilt_pitch_deg;
    QString tilt_yaw_deg;

    /* Annonation properties. */
    struct GsvLink {
        QString pano_id;
        QString yaw_deg;
        QString road_argb;
        QString scene;
        QString link_text;
    };

    /* An array of Links */
    QList<GsvLink> linkList;

    bool setGSVMetadataLink(QString &encodedLink);    
};

#endif /* METADATA_H */
/*!
 * @}
 */
