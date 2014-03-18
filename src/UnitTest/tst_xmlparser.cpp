/*
 * Author Mikko Saavinen
 */

/*!
 * \defgroup xmlparser XmlParser unit tests.
 */
#include <QString>
#include "tst_xmlparser.h"
#include "metadata.h"

/******************************************************************************/
/*!
 * \brief Configure some initial settings.
 * \return PASS
 */
/******************************************************************************/
void Tst_xmlparser::initTestCase()
{
}

/******************************************************************************/
/*!
 * \brief Do some cleanup if necessary.
 *
 * \return PASS
 */
/******************************************************************************/
void Tst_xmlparser::cleanupTestCase()
{
}

/******************************************************************************/
/*!
 * \brief This will be executed before every test.
 */
/******************************************************************************/
void Tst_xmlparser::init()
{
}

/******************************************************************************/
/*!
 * \brief This will be executed after every test.
 */
/******************************************************************************/
void Tst_xmlparser::cleanup()
{
}
/******************************************************************************/
/*!
 * \ingroup xmlparser
 * \brief Feeds valid metadata for the XmlParser object.
 *
 * <b>Testdata: xml_jamie_valid.xml</b>
 *
 * \return PASS if the data was recognized as valid, FAIL otherwise
 *
 * \sa XmlParser
 */
/******************************************************************************/
void Tst_xmlparser::XmlValid1()
{
	/*Preconditions*/
	bool isValid = false;

	QString tstStr;
	QFile jamieFile( "./tstdata/xml_jamie_valid.xml" );

	/* Preconditions */
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
	//Variables
	QString xmlSchema = xmlParser.loadSchema();
	//Code
	isValid = xmlParser.xmlValidation(tstStr, xmlSchema);

    /* Postconditions */
    QVERIFY(isValid);

    //TODO Read error signal here

    //Check result
    //TODO Check for correct error signal also
    //QVERIFY(emptyStr.compare(resultStr) == 0);
}
/******************************************************************************/
/*!
 * \ingroup xmlparser
 * \brief Feeds valid metadata for the XmlParser object. Valid data is
 * constructed from valid data field in random order
 *
 * <b>Testdata: xml_jamie_valid2.xml</b>
 *
 * \return PASS if the data was recognized as valid, FAIL otherwise
 *
 * \sa XmlParser
 */
/******************************************************************************/
void Tst_xmlparser::XmlValid2()
{
	/*Preconditions*/
	bool isValid = false;

	QString tstStr;
	QFile jamieFile( "./tstdata/xml_jamie_valid2.xml" );

	/* Preconditions */
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
	//Variables
	QString xmlSchema = xmlParser.loadSchema();
	//Code
	isValid = xmlParser.xmlValidation(tstStr, xmlSchema);

    /* Postconditions */
    QVERIFY(isValid);

    //TODO Read error signal here

    //Check result
    //TODO Check for correct error signal also
    //QVERIFY(emptyStr.compare(resultStr) == 0);
}
/******************************************************************************/
/*!
 * \ingroup xmlparser
 * \brief Feeds invalid metadata for the XmlParser object.
 *
 * <b>Testdata: Empty string</b>
 *
 * \return PASS if the data was recognized as invalid, FAIL otherwise
 *
 * \sa XmlParser
 */
/******************************************************************************/
void Tst_xmlparser::XmlInvalid1()
{
    //Variables
    QString emptyStr = "";
    QString resultStr = "";

    //Code
    resultStr = xmlParser.setMetadataStr(emptyStr);

    //TODO Read error signal here

    //Check result
    //TODO Check for correct error signal also
    QVERIFY(emptyStr.compare(resultStr) == 0);
}

/******************************************************************************/
/*!
 * \ingroup xmlparser
 * \brief Feeds invalid metadata for the XmlParser object to be parsed.
 * In XML data projection properties element missing
 *
 * <b>Testdata: "xml_jamie_invalid.xml"</b>
 *
 * \return PASS if the data was recognized as invalid, FAIL otherwise
 *
 * \sa XmlParser
 */
/******************************************************************************/
void Tst_xmlparser::XmlInvalid2()
{
	/*Preconditions*/
	bool isValid = false;

	QString tstStr;
	QFile jamieFile( "./tstdata/xml_jamie_invalid.xml" );

	/* Preconditions */
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
	//Variables
	QString xmlSchema = xmlParser.loadSchema();
	//Code
	isValid = xmlParser.xmlValidation(tstStr, xmlSchema);

    /* Postconditions */
    QVERIFY(!isValid);

    //TODO Read error signal here

    //Check result
    //TODO Check for correct error signal also
    //QVERIFY(emptyStr.compare(resultStr) == 0);
}
/******************************************************************************/
/*!
 * \ingroup xmlparser
 * \brief Feeds invalid metadata for the XmlParser object to be parsed.
 * In XML data image height attribute missing in data_properties element
 *
 * <b>Testdata: "xml_jamie_invalid2.xml"</b>
 *
 * \return PASS if the data was recognized as invalid, FAIL otherwise
 *
 * \sa XmlParser
 */
/******************************************************************************/
void Tst_xmlparser::XmlInvalid3()
{
	/*Preconditions*/
	bool isValid = false;

	QString tstStr;
	QFile jamieFile( "./tstdata/xml_jamie_invalid2.xml" );

	/* Preconditions */
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

	QString xmlSchema = xmlParser.loadSchema();

	//Variables

	//Code

	isValid = xmlParser.xmlValidation(tstStr, xmlSchema);

    /* Postconditions */
    QVERIFY(!isValid);

    //TODO Read error signal here

    //Check result
    //TODO Check for correct error signal also
    //QVERIFY(emptyStr.compare(resultStr) == 0);
}
/******************************************************************************/
/*!
 * \ingroup xmlparser
 * \brief Feeds invalid metadata for the XmlParser object to be parsed.
 *
 * <b>Testdata: "xml_jamie_invalid4.xml"</b>
 *
 * \return PASS if the data was recognized as invalid, FAIL otherwise
 *
 * \sa XmlParser
 */
/******************************************************************************/
void Tst_xmlparser::XmlInvalid4()
{
	/*Preconditions*/
	bool isValid = false;

	QString tstStr;
	QFile jamieFile( "./tstdata/xml_jamie_invalid4.xml" );

	/* Preconditions */
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

	QString xmlSchema = xmlParser.loadSchema();

	//Variables

	//Code

	isValid = xmlParser.xmlValidation(tstStr, xmlSchema);

    /* Postconditions */
    QVERIFY(!isValid);

    //TODO Read error signal here

    //Check result
    //TODO Check for correct error signal also
    //QVERIFY(emptyStr.compare(resultStr) == 0);
}
/******************************************************************************/
/*!
 * \ingroup xmlparser
 * \brief Feeds XMLParser::setMetadataStr function to test if it parses data correctly.
 *
 *
 * \sa XmlParser
 */
/******************************************************************************/
void Tst_xmlparser::XmlParserValid1()
{
	/* Variables */

	QString resultStr;
    QString tstStr;
    QString expStr = "© 2010 Google;"				//copyright
			"Eccleston Pl;" 			//text
			"London, England;" 		//region
			"United Kingdom;"			//country
			"1;" 						//data_flag
			"6656;" 					//image_height
			"13312;" 					//image_width
			"51.495090;" 				//lat
			"-0.146971;" 				//lng
			"3;" 						//num_zoom_levels
			"51.495098;" 				//original_lat
			"-0.147000;" 				//original_lng
			"sLaiF6Jex7mJmNol7tdOoA;" 	//pano_id
			"512;"						//tile_height
			"512;" 						//tile_width
			"201.78;" 					//pano_yaw_deg
			"spherical;" 				//projection_type
			"1.75;" 					//tilt_pitch_deg
			"92.06;"					//tilt_yaw_deg
			"2;"						//number of GSV links
    		"204.7;"
    		"CeutxcyB2V74lfN_fJwRww;"
    		"0x80ffffff;"
    		"0;"
    		"Eccelston Pl;"
			"24.7;"
			"t_mnKSugTLrQTEnJplXQ3A;"
			"0x80ffffff;"
			"0;"
			"Eccleston Pl";

    QFile jamieFile( "./tstdata/xml_jamie_valid.xml" );

    /* Preconditions */
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
    resultStr = xmlParser.setMetadataStr(tstStr);
    QString resultStr2 = resultStr.toUtf8();

    //QString merkki = "©";
    //qDebug() << "copymerkki" << merkki;
    //QByteArray ba_merkki = merkki.toUtf8();
    //QString merkki2 = QString::fromUtf8(ba_merkki);
    //qDebug() << "merkki: " << merkki;
    //qDebug() << "merkki2: " << merkki2;
    //qDebug() << "ba_merkki: " << ba_merkki;


    //qDebug() << "tstStr >>>" << tstStr;
    //qDebug() << "expStr >>>" << expStr;
    //qDebug() << "resStr >>>" << resultStr2;

    /* Postconditions */

    QVERIFY(expStr.compare(resultStr) == 0);
}


//void Tst_xmlparser::XmlParserValid2()
//{
//	/* Variables */
//	QStringList resultList;
//	QStringList expList;
//
//	QString resultStr;
//	QByteArray tstArray;
//    QString tstStr;
//    QString expStr = "© 2010 Google;"				//copyright
//			"Eccleston Pl;" 			//text
//			"London, England;" 		//region
//			"United Kingdom;"			//country
//			"1;" 						//data_flag
//			"6656;" 					//image_height
//			"13312;" 					//image_width
//			"51.495090;" 				//lat
//			"-0.146971;" 				//lng
//			"3;" 						//num_zoom_levels
//			"51.495098;" 				//original_lat
//			"-0.147000;" 				//original_lng
//			"sLaiF6Jex7mJmNol7tdOoA;" 	//pano_id
//			"512;"						//tile_height
//			"512;" 						//tile_width
//			"201.78;" 					//pano_yaw_deg
//			"spherical;" 				//projection_type
//			"1.75;" 					//tilt_pitch_deg
//			"92.06;"					//tilt_yaw_deg
//			"2;"						//number of GSV links
//    		"204.7;"
//    		"CeutxcyB2V74lfN_fJwRww;"
//    		"0x80ffffff;"
//    		"0;"
//    		"Eccleston Pl;"
//			"24.7;"
//			"t_mnKSugTLrQTEnJplXQ3A;"
//			"0x80ffffff;"
//			"0;"
//			"Eccleston Pl";
//
//    QFile jamieFile( "./tstdata/xml_jamie_valid.xml" );
//
//    /* Preconditions */
//    if (!jamieFile.exists()) {
//        qDebug() << "tstError: file %s missing", jamieFile.fileName();
//
//        QVERIFY(false);
//    }
//
//    if (!jamieFile.open(QIODevice::ReadOnly)) {
//        qDebug() << "tstError: file %s failed to open", jamieFile.fileName();
//
//        QVERIFY(false);
//    }
//
//    QTextStream textStream(&jamieFile);
//    tstStr = textStream.readAll();
//
//    expList = expStr.split(";");
//
//    /* Execute */
//    resultStr = xmlParser.setMetadataStr(tstStr);
//
//    /* Postconditions */
//    resultList = resultStr.split(";");
//
//    for (int n = 0; n < expList.size(); n++){
//    	qDebug() << expList[n] << "=" << resultList[n];
//    	QVERIFY(expList[n].compare(resultList[n]) == 0);
//    }
//}


/******************************************************************************/
/*!
 * \ingroup xmlparser
 * \brief Calls schemaValidation function to ensure that XML schema is valid
 *
 *
 * \return PASS if the schema was recognized as valid, FAIL otherwise
 *
 * \sa XmlParser
 */
/******************************************************************************/
void Tst_xmlparser::SchemaValidation()
{
    //Variables
	bool isValid = false;    //Code
    QString tstSchema = xmlParser.loadSchema();

    isValid = xmlParser.schemaValidation(tstSchema);
    QVERIFY(isValid);

    //TODO Read error signal here

    //Check result
    //TODO Check for correct error signal also
    //QVERIFY(emptyStr.compare(resultStr) == 0);
}
/******************************************************************************/
/*!
 * \ingroup xmlparser
 * \brief Calls schemaValidation function to ensure that XML schema really is invalid
 *
 *
 * \return PASS if the schema was recognized as invalid, FAIL otherwise
 *
 * \sa XmlParser
 */
/******************************************************************************/
void Tst_xmlparser::SchemaInvalidValidation()
{
    //Variables
	bool isValid = false;    //Code
    QString tstSchema = xmlParser.loadSchema();
    tstSchema += "fuubar";

    isValid = xmlParser.schemaValidation(tstSchema);
    QVERIFY(!isValid);

    //TODO Read error signal here

    //Check result
    //TODO Check for correct error signal also
    //QVERIFY(emptyStr.compare(resultStr) == 0);
}
/*!
  * \todo Comment.
  */

///******************************************************************************/
///*!
// * \ingroup
// * \brief
// *
// * \return PASS if
// *
// * \sa
// */
///******************************************************************************/
//void Tst_xmlparser::ModuleNameValid/InvalidNumber()
//{
//	//Variables
//
//
//	//Code
//
//
//	//Check result
//  QVERIFY();
//}
