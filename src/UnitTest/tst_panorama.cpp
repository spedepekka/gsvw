/*
 * Author: Veijo Pesonen
 */

/*! \file tst_panorama.cpp
 * \weakgroup tile
 * \weakgroup metadata
 *
 * \weakgroup panorama
 *
 * @{
 */
#include "tst_panorama.h"

#include "metadata.h"
#include "gsvwrapper.h"


/******************************************************************************/
void Tst_panorama::initTestCase()
{
}

/******************************************************************************/
void Tst_panorama::cleanupTestCase()
{
}

/******************************************************************************/
void Tst_panorama::init()
{
}

/******************************************************************************/
void Tst_panorama::cleanup()
{
}

/******************************************************************************/
/*! \ingroup metadata
 */
/******************************************************************************/
void Tst_panorama::ut_1()
{
    /* Variables */
    QString tstStr;
    QFile jamieFile("./tstdata/xml_jamie_valid.xml");
    Metadata Metadata;
    bool statusOk;
    QString dummyStr = ";" //copyright
                            ";" //text
                            ";" //region
                            ";"    //country
                            ";" //data_flag
                            ";" //image_height
                            ";" //image_width
                            ";" //lat
                            ";" //lng
                            ";" //num_zoom_levels
                            ";" //original_lat
                            ";" //original_lng
                            ";" //pano_id
                            ";"    //tile_height
                            ";" //tile_width
                            ";" //pano_yaw_deg
                            ";" //projection_type
                            ";" //tilt_pitch_deg
                            ";"    //tilt_yaw_deg
                            "0";//number of GSV links

    /* Preconditions */

#ifndef Q_OS_UNIX
        QSKIP("This test uses unix style path naming conventions.", SkipAll);
#endif

    if (!jamieFile.exists()) {
        qDebug() << "tstError: file %s missing", jamieFile.fileName();

        QVERIFY(false);
    }

    if (!jamieFile.open(QIODevice::ReadOnly)) {
        qDebug() << "tstError: file %s failed to open", jamieFile.fileName();

        QVERIFY(false);
    }

    QTextStream textStream(&jamieFile);
    tstStr = textStream.readAll();

    /* Execute */
    statusOk = Metadata.setGSVMetadata(dummyStr, tstStr);

    /* Postconditions */
    QVERIFY(Metadata.xmlData.compare(tstStr) == 0 &&
            statusOk == TRUE);
}


/******************************************************************************/
/*! \ingroup metadata
 */
/******************************************************************************/
void Tst_panorama::ut_2()
{
    /* Variables */
    QString dummyStr;
    bool statusOk;
    QString tstStr = "© 2011 Google;"                //copyright
                        "Eccleston Place;"             //text
                        "Westminster, London;"         //region
                        "United Kingdom;"            //country
                        "1;"                         //data_flag
                        "6656;"                     //image_height
                        "13312;"                     //image_width
                        "51.495072;"                 //lat
                        "-0.146984;"                 //lng
                        "3;"                         //num_zoom_levels
                        "51.495073;"                 //original_lat
                        "-0.146987;"                 //original_lng
                        "sLaiF6Jex7mJmNol7tdOoA;"     //pano_id
                        "512;"                        //tile_height
                        "512;"                         //tile_width
                        "204.15;"                     //pano_yaw_deg
                        "spherical;"                 //projection_type
                        "0.75;"                     //tilt_pitch_deg
                        "-17.61;"                    //tilt_yaw_deg
                        "0";                        //number of GSV links

    /* Preconditions */
    Metadata *md = new Metadata;
    /* Execute */
    statusOk = md->setGSVMetadata(tstStr, dummyStr);


    /* Postconditions */
    QVERIFY(statusOk == TRUE &&
            md->copyright.compare("© 2011 Google") == 0 &&
            md->text.compare("Eccleston Place") == 0 &&
            md->region.compare("Westminster, London") == 0 &&
            md->country.compare("United Kingdom") == 0 &&
            md->data_flag.compare("1") == 0 &&
            md->image_height.compare("6656") == 0 &&
            md->image_width.compare("13312") == 0 &&
            md->lat.compare("51.495072") == 0 &&
            md->lng.compare("-0.146984") == 0 &&
            md->num_zoom_levels.compare("3") == 0 &&
            md->original_lat.compare("51.495073") == 0 &&
            md->original_lng.compare("-0.146987") == 0 &&
            md->pano_id.compare("sLaiF6Jex7mJmNol7tdOoA") == 0 &&
            md->tile_height.compare("512") == 0 &&
            md->tile_width.compare("512") == 0 &&
            md->pano_yaw_deg.compare("204.15") == 0 &&
            md->projection_type.compare("spherical") == 0 &&
            md->tilt_pitch_deg.compare("0.75") == 0 &&
            md->tilt_yaw_deg.compare("-17.61") == 0 &&
            md->linkList.isEmpty() == true);

    delete md;

}


/******************************************************************************/
/*! \ingroup metadata
 */
/******************************************************************************/
void Tst_panorama::ut_3()
{
    /* Variables */
    bool statusOk;
    QString dummyStr;
    QString tstStr = "© 2011 Google;"                //copyright
                        "Eccleston Place;"             //text
                        "Westminster, London;"         //region
                        "United Kingdom;"            //country
                        "1;"                         //data_flag
                        "6656;"                     //image_height
                        "13312;"                     //image_width
                        "51.495072;"                 //lat
                        "-0.146984;"                 //lng
                        "3;"                         //num_zoom_levels
                        "51.495073;"                 //original_lat
                        "-0.146987;"                 //original_lng
                        "sLaiF6Jex7mJmNol7tdOoA;"     //pano_id
                        "512;"                        //tile_height
                        "512;"                         //tile_width
                        "204.15;"                     //pano_yaw_deg
                        "spherical;"                 //projection_type
                        "0.75;"                     //tilt_pitch_deg
                        "-17.61;"                    //tilt_yaw_deg
                        "";    //number of GSV links is missing

    /* Preconditions */
    Metadata *md = new Metadata;
    /* Execute */
    statusOk = md->setGSVMetadata(tstStr, dummyStr);

    /* Postconditions */
    QVERIFY(statusOk == true &&
            md->copyright.compare("© 2011 Google") == 0 &&
            md->text.compare("Eccleston Place") == 0 &&
            md->region.compare("Westminster, London") == 0 &&
            md->country.compare("United Kingdom") == 0 &&
            md->data_flag.compare("1") == 0 &&
            md->image_height.compare("6656") == 0 &&
            md->image_width.compare("13312") == 0 &&
            md->lat.compare("51.495072") == 0 &&
            md->lng.compare("-0.146984") == 0 &&
            md->num_zoom_levels.compare("3") == 0 &&
            md->original_lat.compare("51.495073") == 0 &&
            md->original_lng.compare("-0.146987") == 0 &&
            md->pano_id.compare("sLaiF6Jex7mJmNol7tdOoA") == 0 &&
            md->tile_height.compare("512") == 0 &&
            md->tile_width.compare("512") == 0 &&
            md->pano_yaw_deg.compare("204.15") == 0 &&
            md->projection_type.compare("spherical") == 0 &&
            md->tilt_pitch_deg.compare("0.75") == 0 &&
            md->tilt_yaw_deg.compare("-17.61") == 0 &&
            md->linkList.isEmpty() == true);

    delete md;
}


/******************************************************************************/
/*! \ingroup metadata
 */
/******************************************************************************/
void Tst_panorama::ut_4()
{
    /* Variables */
    bool statusOk;
    QString dummyStr;
    QString tstStr = "© 2011 Google;"                //copyright
                        "Eccleston Place;"             //text
                        "Westminster, London;"         //region
                        "United Kingdom;"            //country
                        "1;"                         //data_flag
                        "6656;"                     //image_height
                        "13312;"                     //image_width
                        "51.495072;"                 //lat
                        "-0.146984;"                 //lng
                        "3;"                         //num_zoom_levels
                        "51.495073;"                 //original_lat
                        "-0.146987;"                 //original_lng
                        "sLaiF6Jex7mJmNol7tdOoA;"     //pano_id
                        "512;"                        //tile_height
                        "512;"                         //tile_width
                        "204.15;"                     //pano_yaw_deg
                        "spherical;"                 //projection_type
                        "0.75;"                     //tilt_pitch_deg
                        "-17.61;"                    //tilt_yaw_deg
                        "1;"                        //number of GSV links
                        "204.7;CeutxcyB2V74lfN_fJwRww;0x80ffffff;0;Eccleston Pl";

    /* Preconditions */
    Metadata *md = new Metadata;
    /* Execute */
    statusOk = md->setGSVMetadata(tstStr, dummyStr);


    /* Postconditions */
    QVERIFY(statusOk == TRUE &&
            md->copyright.compare("© 2011 Google") == 0 &&
            md->text.compare("Eccleston Place") == 0 &&
            md->region.compare("Westminster, London") == 0 &&
            md->country.compare("United Kingdom") == 0 &&
            md->data_flag.compare("1") == 0 &&
            md->image_height.compare("6656") == 0 &&
            md->image_width.compare("13312") == 0 &&
            md->lat.compare("51.495072") == 0 &&
            md->lng.compare("-0.146984") == 0 &&
            md->num_zoom_levels.compare("3") == 0 &&
            md->original_lat.compare("51.495073") == 0 &&
            md->original_lng.compare("-0.146987") == 0 &&
            md->pano_id.compare("sLaiF6Jex7mJmNol7tdOoA") == 0 &&
            md->tile_height.compare("512") == 0 &&
            md->tile_width.compare("512") == 0 &&
            md->pano_yaw_deg.compare("204.15") == 0 &&
            md->projection_type.compare("spherical") == 0 &&
            md->tilt_pitch_deg.compare("0.75") == 0 &&
            md->tilt_yaw_deg.compare("-17.61") == 0 &&
            md->linkList.count() == 1);

    delete md;

}


/******************************************************************************/
/*! \ingroup metadata
 */
/******************************************************************************/
void Tst_panorama::ut_5()
{
    /* Variables */
    bool statusOk;
    QString dummyStr;
    QString tstStr = "© 2011 Google;"                //copyright
                        "Eccleston Place;"             //text
                        "Westminster, London;"         //region
                        "United Kingdom;"            //country
                        "1;"                         //data_flag
                        "6656;"                     //image_height
                        "13312;"                     //image_width
                        "51.495072;"                 //lat
                        "-0.146984;"                 //lng
                        "3;"                         //num_zoom_levels
                        "51.495073;"                 //original_lat
                        "-0.146987;"                 //original_lng
                        "sLaiF6Jex7mJmNol7tdOoA;"     //pano_id
                        "512;"                        //tile_height
                        "512;"                         //tile_width
                        "204.15;"                     //pano_yaw_deg
                        "spherical;"                 //projection_type
                        "0.75;"                     //tilt_pitch_deg
                        "-17.61;"                    //tilt_yaw_deg
                        "3;"                        //number of GSV links
                        "204.7;1_CeutxcyB2V74lfN_fJwRww;0x80ffffff;0;Eccleston Pl;"
                        "204.7;2_CeutxcyB2V74lfN_fJwRww;0x80ffffff;0;Eccleston Pl;"
                        "204.7;3_CeutxcyB2V74lfN_fJwRww;0x80ffffff;0;Eccleston Pl";

    /* Preconditions */
    Metadata *md = new Metadata;
    /* Execute */
    statusOk = md->setGSVMetadata(tstStr, dummyStr);


    /* Postconditions */
    QVERIFY(statusOk == TRUE &&
            md->copyright.compare("© 2011 Google") == 0 &&
            md->text.compare("Eccleston Place") == 0 &&
            md->region.compare("Westminster, London") == 0 &&
            md->country.compare("United Kingdom") == 0 &&
            md->data_flag.compare("1") == 0 &&
            md->image_height.compare("6656") == 0 &&
            md->image_width.compare("13312") == 0 &&
            md->lat.compare("51.495072") == 0 &&
            md->lng.compare("-0.146984") == 0 &&
            md->num_zoom_levels.compare("3") == 0 &&
            md->original_lat.compare("51.495073") == 0 &&
            md->original_lng.compare("-0.146987") == 0 &&
            md->pano_id.compare("sLaiF6Jex7mJmNol7tdOoA") == 0 &&
            md->tile_height.compare("512") == 0 &&
            md->tile_width.compare("512") == 0 &&
            md->pano_yaw_deg.compare("204.15") == 0 &&
            md->projection_type.compare("spherical") == 0 &&
            md->tilt_pitch_deg.compare("0.75") == 0 &&
            md->tilt_yaw_deg.compare("-17.61") == 0 &&
            md->linkList.count() == 3);

    delete md;

}


/******************************************************************************/
/*! \ingroup metadata
 */
/******************************************************************************/
void Tst_panorama::ut_6()
{
    /* Variables */
    bool statusOk;
    Metadata *md;
    QString dummyStr;
    QString tstStr;

    /* Preconditions */
    md = new Metadata;

    tstStr = "© 2011 Google;"                //copyright
                            "Eccleston Place;"             //text
                            "Westminster, London;"         //region
                            "United Kingdom;"            //country
                            "1;"                         //data_flag
                            "6656;"                     //image_height
                            "13312;"                     //image_width
                            "51.495072;"                 //lat
                            "-0.146984;"                 //lng
                            "3;"                         //num_zoom_levels
                            "51.495073;"                 //original_lat
                            "-0.146987;"                 //original_lng
                            "sLaiF6Jex7mJmNol7tdOoA;"     //pano_id
                            "512;"                        //tile_height
                            "512;"                         //tile_width
                            "204.15;"                     //pano_yaw_deg
                            "spherical;"                 //projection_type
                            "0.75;"                     //tilt_pitch_deg
                            "-17.61;"                    //tilt_yaw_deg
                            "3;"                        //number of GSV links
                            "1;1_CeutxcyB2V74lfN_fJwRww;3;4;5;"
                            "1;2_CeutxcyB2V74lfN_fJwRww;3;4;5;"
                            "1;2_CeutxcyB2V74lfN_fJwRww;3;4;5";

    /* Execute */
    statusOk = md->setGSVMetadata(tstStr, dummyStr);


    /* Postconditions */
    QVERIFY(statusOk == TRUE &&
            md->copyright.compare("© 2011 Google") == 0 &&
            md->text.compare("Eccleston Place") == 0 &&
            md->region.compare("Westminster, London") == 0 &&
            md->country.compare("United Kingdom") == 0 &&
            md->data_flag.compare("1") == 0 &&
            md->image_height.compare("6656") == 0 &&
            md->image_width.compare("13312") == 0 &&
            md->lat.compare("51.495072") == 0 &&
            md->lng.compare("-0.146984") == 0 &&
            md->num_zoom_levels.compare("3") == 0 &&
            md->original_lat.compare("51.495073") == 0 &&
            md->original_lng.compare("-0.146987") == 0 &&
            md->pano_id.compare("sLaiF6Jex7mJmNol7tdOoA") == 0 &&
            md->tile_height.compare("512") == 0 &&
            md->tile_width.compare("512") == 0 &&
            md->pano_yaw_deg.compare("204.15") == 0 &&
            md->projection_type.compare("spherical") == 0 &&
            md->tilt_pitch_deg.compare("0.75") == 0 &&
            md->tilt_yaw_deg.compare("-17.61") == 0 &&
            md->linkList.count() == 2);

    delete md;

}


/******************************************************************************/
/*! \ingroup metadata
 */
/******************************************************************************/
void Tst_panorama::ut_7()
{
    /* Variables */
    Metadata::GsvLink newLn;
    QList<QStringList> tstLinks;
    Metadata *md;
    QList<Metadata::GsvLink>::Iterator it;

    /* Preconditions */
    md = new Metadata;

    md->linkList.append(newLn);
    md->linkList.append(newLn);
    md->linkList.append(newLn);

    it = md->linkList.begin();

    it->yaw_deg = "a";
    it->pano_id = "b_CeutxcyB2V74lfN_fJwRww";
    it->road_argb = "c";
    it->scene = "d";
    it->link_text = "e";
    it++;
    it->yaw_deg = "f";
    it->pano_id = "g_CeutxcyB2V74lfN_fJwRww";
    it->road_argb = "h";
    it->scene = "i";
    it->link_text = "j";
    it++;
    it->yaw_deg = "k";
    it->pano_id = "l_CeutxcyB2V74lfN_fJwRww";
    it->road_argb = "m";
    it->scene = "n";
    it->link_text = "o";


    /* Execute */
    tstLinks = md->getLinks();


    /* Postconditions */
    QVERIFY(md->linkList.count() == 3 &&
            tstLinks.at(0).at(GSVWrapper::GSVLinkYawDeg).compare("a") == 0 &&
            tstLinks.at(0).at(GSVWrapper::GSVLinkPanoId).compare("b_CeutxcyB2V74lfN_fJwRww") == 0 &&
            tstLinks.at(0).at(GSVWrapper::GSVLinkRoadArgb).compare("c") == 0 &&
            tstLinks.at(0).at(GSVWrapper::GSVLinkScene).compare("d") == 0 &&
            tstLinks.at(0).at(GSVWrapper::GSVLinkText).compare("e") == 0 &&

            tstLinks.at(1).at(GSVWrapper::GSVLinkYawDeg).compare("f") == 0 &&
            tstLinks.at(1).at(GSVWrapper::GSVLinkPanoId).compare("g_CeutxcyB2V74lfN_fJwRww") == 0 &&
            tstLinks.at(1).at(GSVWrapper::GSVLinkRoadArgb).compare("h") == 0 &&
            tstLinks.at(1).at(GSVWrapper::GSVLinkScene).compare("i") == 0 &&
            tstLinks.at(1).at(GSVWrapper::GSVLinkText).compare("j") == 0 &&

            tstLinks.at(2).at(GSVWrapper::GSVLinkYawDeg).compare("k") == 0 &&
            tstLinks.at(2).at(GSVWrapper::GSVLinkPanoId).compare("l_CeutxcyB2V74lfN_fJwRww") == 0 &&
            tstLinks.at(2).at(GSVWrapper::GSVLinkRoadArgb).compare("m") == 0 &&
            tstLinks.at(2).at(GSVWrapper::GSVLinkScene).compare("n") == 0 &&
            tstLinks.at(2).at(GSVWrapper::GSVLinkText).compare("o") == 0
    );

    delete md;

}


/******************************************************************************/
/*! \ingroup metadata
 */
/******************************************************************************/
void Tst_panorama::ut_8()
{
    /* Variables */
    bool statusOk;
    QString dummyStr;
    QString tstStr = "© 2011 Google;"                //copyright
                        "Eccleston Place;"             //text
                        "Westminster, London;"         //region
                        "United Kingdom;"            //country
                        "1;"                         //data_flag
                        "6656;"                     //image_height
                        "13312;"                     //image_width
                        "51.495072;"                 //lat
                        "-0.146984;"                 //lng
                        "3;"                         //num_zoom_levels
                        "51.495073;"                 //original_lat
                        "-0.146987;"                 //original_lng
                        "sLaiF6Jex7mJmNol7tdOoA;"     //pano_id
                        "512;"                        //tile_height
                        "512;"                         //tile_width
                        "204.15;"                     //pano_yaw_deg
                        "spherical;"                 //projection_type
                        "0.75;"                     //tilt_pitch_deg
                        ""                    //tilt_yaw_deg is missing
                        "";    //number of GSV links is missing

    /* Preconditions */
    Metadata *md = new Metadata;
    /* Execute */
    statusOk = md->setGSVMetadata(tstStr, dummyStr);

    /* Postconditions */
    QVERIFY(statusOk == FALSE &&
            md->copyright.compare("") == 0 &&
            md->text.compare("") == 0 &&
            md->region.compare("") == 0 &&
            md->country.compare("") == 0 &&
            md->data_flag.compare("") == 0 &&
            md->image_height.compare("") == 0 &&
            md->image_width.compare("") == 0 &&
            md->lat.compare("") == 0 &&
            md->lng.compare("") == 0 &&
            md->num_zoom_levels.compare("") == 0 &&
            md->original_lat.compare("") == 0 &&
            md->original_lng.compare("") == 0 &&
            md->pano_id.compare("") == 0 &&
            md->tile_height.compare("") == 0 &&
            md->tile_width.compare("") == 0 &&
            md->pano_yaw_deg.compare("") == 0 &&
            md->projection_type.compare("") == 0 &&
            md->tilt_pitch_deg.compare("") == 0 &&
            md->tilt_yaw_deg.compare("") == 0 &&
            md->linkList.isEmpty() == true);

    delete md;
}

/******************************************************************************/
/*! \ingroup
 * \brief Test Description:
 */
/******************************************************************************/
//{
    /* Variables */

    /* Preconditions */

    /* Execute */

    /* Postconditions */
//}

/*!
 * @}
 */
