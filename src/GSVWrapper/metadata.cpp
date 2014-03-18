/*!
 * \file metadata.cpp
 * \weakgroup metadata
 *
 * @{
 *
 *  Created on: Mar 30, 2011
 *      Author: Veijo Pesonen
 */
/* Qt includes */
#include <QDebug>
#include <QMutexLocker>
#include <QObject>
#include <QStringList>
#include <QStringListModel>

/* Own headers */
#include "gsvwrapper.h"
#include "metadata.h"


/******************************************************************************/
Metadata::Metadata() : xmlData(""),
    copyright(""),
    text(""),
    region(""),
    country(""),
    data_flag(""),
    image_height(""),
    image_width(""),
    lat(""),
    lng(""),
    num_zoom_levels(""),
    original_lat(""),
    original_lng(""),
    pano_id(""),
    tile_height(""),
    tile_width(""),
    pano_yaw_deg(""),
    projection_type(""),
    tilt_pitch_deg(""),
    tilt_yaw_deg("")
{
}


/******************************************************************************/
Metadata::~Metadata() {
}


/******************************************************************************/
QString Metadata::getRawXml() {

    return this->xmlData;
}

/******************************************************************************/
/*!
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) Create a list of all individual items.
 * <li>(0200) Check that at least all mandatory fields are present, rest is up
 *         to the number of links.
 * <li>(0300) Get number of links, abort if data is not valid.
 * <li>(0400) Write all simple data fields.
 * <li>(0500) Get a list of all links.
 * <li>(0600) Repeat for all links
 *     <ul>
 *     <li>(0610) Form an encoded link string, use semicolon as delimiter
 *     <li>(0620) Add the last element on the string without semicolon
 *     <li>(0630) Update link data
 *  </ul>
 * <li> Update also metadata presented in an xml format.
 * </ul>
 */
/******************************************************************************/
bool Metadata::setGSVMetadata(const QString &codedData,
        const QString &rawXmlData) {

    QStringList gsvMetadata = codedData.split(";", QString::KeepEmptyParts);
    int nmOfLinks;
    int i;
    bool conversionOk = false;
    QString encodedLink;
    bool statusOk = FALSE;

    QMutexLocker locker(&mdLock);


    /*0100*/
    QStringListModel strmodel(gsvMetadata);

    /*0200*/
    if (strmodel.rowCount() < (IndexNmOfGSVLinks + 1)) {
        qDebug() << "error:" << __FILE__ << ", line" << __LINE__
                << ": decoding metadata failed!";
        goto EXIT;
    }

    /*0300*/
    nmOfLinks = gsvMetadata.at(IndexNmOfGSVLinks).toInt(&conversionOk, 10);

    if (conversionOk == false) {
        if (gsvMetadata.at(IndexNmOfGSVLinks).compare("") == 0) {
            nmOfLinks = 0;
        }
        else {
            qDebug() << "error:" << __FILE__ << ", line" << __LINE__
                    << ": decoding metadata failed!";
            goto EXIT;
        }
    }

    statusOk = TRUE;

    /*0400*/
    this->copyright = gsvMetadata.at(GSVCopyright);
    this->text = gsvMetadata.at(GSVText);
    this->region = gsvMetadata.at(GSVRegion);
    this->country = gsvMetadata.at(GSVCountry);
    this->data_flag = gsvMetadata.at(GSVDataFlag);
    this->image_height = gsvMetadata.at(GSVImageHeight);
    this->image_width = gsvMetadata.at(GSVImageWidth);
    this->lat = gsvMetadata.at(GSVLat);
    this->lng = gsvMetadata.at(GSVLng);
    this->num_zoom_levels = gsvMetadata.at(GSVNumZoomeLevels);
    this->original_lat = gsvMetadata.at(GSVOriginalLat);
    this->original_lng = gsvMetadata.at(GSVOriginalLng);
    this->pano_id = gsvMetadata.at(GSVPanoId);
    this->tile_height = gsvMetadata.at(GSVTileHeight);
    this->tile_width = gsvMetadata.at(GSVTileWidth);
    this->pano_yaw_deg = gsvMetadata.at(GSVPanoYawDeg);
    this->projection_type = gsvMetadata.at(GSVProjectionType);
    this->tilt_pitch_deg = gsvMetadata.at(GSVTiltPitchDeg);
    this->tilt_yaw_deg = gsvMetadata.at(GSVTiltYawDeg);

    /*0500*/
    for (i = 0; i <= IndexNmOfGSVLinks; i++)
        gsvMetadata.removeFirst();

    /*0600*/
    for(i = 0; i < nmOfLinks; i++) {
        encodedLink = "";

        /*0610*/
        for (int j = 0; j < LINK_ELEMENT_CNT-1; j++)
            encodedLink.append(gsvMetadata.takeFirst() + ";");

        /*0620*/
        encodedLink.append(gsvMetadata.takeFirst());

        /*0630*/
        statusOk = setGSVMetadataLink(encodedLink);

    }

    /*0700*/
    this->xmlData = rawXmlData;

EXIT:
    return statusOk;
}

/******************************************************************************/
QString Metadata::getFieldByName(const QString fieldName)
{
    if (QString("copyright") == fieldName)
        return copyright;
    if (QString("text") == fieldName)
        return text;
    if (QString("region") == fieldName)
        return region;
    if (QString("country") == fieldName)
        return country;
    if (QString("data_flag") == fieldName)
        return data_flag;
    if (QString("image_height") == fieldName)
        return image_height;
    if (QString("image_width") == fieldName)
        return image_width;
    if (QString("lat") == fieldName)
        return lat;
    if (QString("lng") == fieldName)
        return lng;
    if (QString("num_zoom_levels") == fieldName)
        return num_zoom_levels;
    if (QString("original_lat") == fieldName)
        return original_lat;
    if (QString("original_lng") == fieldName)
        return original_lng;
    if (QString("pano_id") == fieldName)
        return pano_id;
    if (QString("tile_height") == fieldName)
        return tile_height;
    if (QString("tile_width") == fieldName)
        return tile_width;
    if (QString("pano_yaw_deg") == fieldName)
        return pano_yaw_deg;
    if (QString("projection_type") == fieldName)
        return projection_type;
    if (QString("tilt_pitch_deg") == fieldName)
        return tilt_pitch_deg;
    if (QString("tilt_yaw_deg") == fieldName)
        return tilt_yaw_deg;

    return QString();
}

/******************************************************************************/
QList<QStringList> Metadata::getLinks() {

    QList<QStringList> links;

    int i;

    for (i = 0; i < this->linkList.count(); i++) {

        QStringList link;

        link.append(this->linkList.at(i).yaw_deg);
        link.append(this->linkList.at(i).pano_id);
        link.append(this->linkList.at(i).road_argb);
        link.append(this->linkList.at(i).scene);
        link.append(this->linkList.at(i).link_text);

        links.append(link);
    }

    return links;
}


/******************************************************************************/
/*******************************************************************************
 *
 * Private members
 *
 ******************************************************************************/
/******************************************************************************/


/******************************************************************************/
/*!
 *
 * \brief Stores a GSV link and all needed information is encoded to a
 * string which is given as a parameter. Semicolon is used on a string as a
 * delimiter between different fields.
 *
 * <br>
 * <b>Example:</b> Adding a following link:
 * \verbatim
 <link yaw_deg="204.7" pano_id="CeutxcyB2V74lfN_fJwRww" road_argb="0x80ffffff">
 <link_text>Eccleston Pl</link_text>
 </link>

 -->>

 setGSVMetadataLink("204.7;CeutxcyB2V74lfN_fJwRww;0x80ffffff;0;Eccleston Pl");
 \endverbatim
 * <br>
 *
 * \param encodedLink All information related to a link coded to a single string
 *
 * <b>Pseudocode</b>
 * <ul>
 * <li>(0100) If right number of data fields exists
 *     <ul>
 *     <li>(0110) Check if a link with same Panoid exists.
 *     <li>(0120) Append a new link to the list IF one with same GSVLinkPanoId
 *                doesn't exist.
 *     <li>(0130)Update the link according to the given parameters.
 *     </ul>
 * <li>(0200) Otherwise report error.
 * </ul>
 *
 * \sa xmlparser
 *
 */
/******************************************************************************/
bool Metadata::setGSVMetadataLink(QString &encodedLink) {

    QStringList newLnCont = encodedLink.split(";");
    QStringListModel strModel(newLnCont);
    bool lnExists = false;
    QList<GsvLink>::Iterator it = this->linkList.begin();
    bool statusOk = TRUE;

    /*0100*/
    if (strModel.rowCount() == LINK_ELEMENT_CNT) {

        /*0110*/
        while (it != linkList.end()) {
            /* Link already exists, update */
            if (it->pano_id.compare(newLnCont.at(GSVWrapper::GSVLinkPanoId)) == 0) {
                lnExists = true;
                break;
            }
            it++;
        }

        /*0120*/
        if (lnExists == false) {
            GsvLink newLn;

            linkList.append(newLn);
            it = linkList.end() - 1;
        }

        /*0130*/
        it->pano_id = newLnCont.at(GSVWrapper::GSVLinkPanoId);
        it->yaw_deg = newLnCont.at(GSVWrapper::GSVLinkYawDeg);
        it->road_argb = newLnCont.at(GSVWrapper::GSVLinkRoadArgb);
        it->scene = newLnCont.at(GSVWrapper::GSVLinkScene);
        it->link_text = newLnCont.at(GSVWrapper::GSVLinkText);
    }
    /*0200*/
    else {
        statusOk = FALSE;
        qDebug() << "error: " << __FILE__ << ", line " << __LINE__
                << ": decoding metadata failed!";
    }

    return statusOk;
}


/*!
 * @}
 */
