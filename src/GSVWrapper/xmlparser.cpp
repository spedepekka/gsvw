/*!
 * \file xmlparser.h
 * \weakgroup xmlparser
 * @{
 *  Created on: Mar 30, 2011
 *  Author: Mikko Saavinen
 */
/* Qt includes */
#include <QByteArray>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QtXmlPatterns>
#include <QUrl>
#include <QXmlSchema>

/* Own headers */
#include "metadata.h"
#include "xmlparser.h"


/******************************************************************************/
XMLParser::XMLParser()
{
}



/******************************************************************************/
XMLParser::~XMLParser()
{
}

/******************************************************************************/
/*!
  * Overwritten function that moves GSVWrapper-object to given thread.
  * \param thread Pointer to thread where to move this object.
  */
/******************************************************************************/
void XMLParser::moveToThread(QThread *thread)
{
    QObject::moveToThread(thread);
}


/******************************************************************************/
/*!
 * \brief Function parses all data field from the given XML string and
 * stores parsed data to the metadata class member.
 * Pseudocode for XMLParser::parse function:
 *
 * <b>Pseudocode</b>
 * Metadata * XMLParser::parse(QString xmlStr):
 * 	<ul>
 * 		<li>(0100) Loads predefined schema to "QString xmlSchema".
 * 		<li>(0200) Validates xmlSchema and returns "0" if schema is invalid.
 * 		<li>(0300) Validates XML data string against the schema and returns "0" if it is invalid.
 * 		<li>(0400) Calls "setMetadataStr" function that parses data to "QString enMetadata" in order, which is defined in metadata class.
 * 		<li>(0500) Sets parsed data and original XML string to the Metadata object.
 * 		<li>(0600) Returns pointer to produced Metadata object.
 * 	</ul>
 *
 *\sa metadata
 */
/******************************************************************************/


Metadata * XMLParser::parse(QString xmlStr)
{
	bool validationOK = true;

    Metadata *newMetadata = 0;
    QString enMetadata;
    // qDebug() << QString("XMLParser::parse(QString xmlStr): '%1'").arg(xmlStr);

	/*0100*/
	QString xmlSchema = loadSchema();

	/*0200*/
	validationOK = schemaValidation(xmlSchema);
	if (!validationOK){
		//qDebug() << "schema validation ERROR";
        return 0;
	}

	/*0300*/
	validationOK = xmlValidation(xmlStr, xmlSchema);
	if (!validationOK) {
		//qDebug() << "xmlvalidation ERROR";
        return 0;
	} else {

		/*qDebug() << "panoId's in list;";

		 foreach (QString str, strList){
		 qDebug() << QString(" [%1] ").arg(str);
		 }*/

		/*0400*/
		enMetadata = setMetadataStr(xmlStr);
		//qDebug() << enMetadata;

		/*0500*/
        newMetadata = new Metadata(); // Note: Remember to remove this
        newMetadata->setGSVMetadata(enMetadata, xmlStr);
	}

	/*0600*/
	return newMetadata;
}

/******************************************************************************/
/*!
  * \brief Parses fiven XML string to the encoded metadata string. First parser
  * includes all data fields to string list. Final string is constructed from
  * the list. Semicolon is used on a final string as a
 * delimiter between different fields.
  */
/******************************************************************************/
QString XMLParser::setMetadataStr(QString xmlStr)
{
	QStringList strList;
	QString enMetadata;

	doc.setContent(xmlStr);

	//qDebug() << "incoming string: " << xmlStr;

	QDomElement root = doc.documentElement();
	if (root.tagName() != "panorama") {
		//qDebug() << "Unknown root element in xml.";
        return 0;
	}

	QDomElement data_properties = root.firstChildElement("data_properties");
	if (data_properties.isNull()) {
		//qDebug() << "no data_properties found";
        return 0;
	} else {
		//qDebug() << "data_properties found";
	}

	QDomElement copyright_el = data_properties.firstChildElement("copyright");
	if (!copyright_el.isNull()) {
		//qDebug() << "copyrihti found";
		strList << copyright_el.text();
		//qDebug() << "copyright: " << copyright_el.text();
	} else {
        return 0;
	}

	QDomElement text_el = data_properties.firstChildElement("text");
	if (!text_el.isNull()) {
		//qDebug() << "teksti found";
		strList << QString(text_el.text());
	} else {
        return 0;
	}

	QDomElement region_el = data_properties.firstChildElement("region");
	if (!region_el.isNull()) {
		//qDebug() << "region found";
		strList << QString(region_el.text());
	} else {
        return 0;
	}

	QDomElement country_el = data_properties.firstChildElement("country");
	if (!country_el.isNull()) {
		//qDebug() << "country found";
		strList << QString(country_el.text());
	} else {
        return 0;
	}

	QDomElement data_flag_el = data_properties.firstChildElement("data_flag");
	if (!data_flag_el.isNull()) {
		//qDebug() << "teksti found";
		strList << QString(data_flag_el.text());
	} else {
        return 0;
	}

	strList << QString(data_properties.attribute("image_height"));
	strList << QString(data_properties.attribute("image_width"));
	strList << QString(data_properties.attribute("lat"));
	strList << QString(data_properties.attribute("lng"));
	strList << QString(data_properties.attribute("num_zoom_levels"));
	strList << QString(data_properties.attribute("original_lat"));
	strList << QString(data_properties.attribute("original_lng"));
	strList << QString(data_properties.attribute("pano_id"));
	strList << QString(data_properties.attribute("tile_height"));
	strList << QString(data_properties.attribute("tile_width"));

	QDomElement projection_properties = root.firstChildElement(
			"projection_properties");
	if (projection_properties.isNull()) {
		qDebug() << "no projection_properties found";
        return 0;
	} else {
		//qDebug() << "projection_properties found";
	}

	strList << QString(projection_properties.attribute("pano_yaw_deg"));
	strList << QString(projection_properties.attribute("projection_type"));
	strList << QString(projection_properties.attribute("tilt_pitch_deg"));
	strList << QString(projection_properties.attribute("tilt_yaw_deg"));

	QDomElement annotation_properties = root.firstChildElement(
			"annotation_properties");
	if (annotation_properties.isNull()) {
		qDebug() << "no annotation_properties found";
        return 0;
	} else {
		//qDebug() << "annotation_properties found";
	}

	//Number of the links
	int link_no = 0;
	for (QDomNode n = annotation_properties.firstChild(); !n.isNull(); n
			= n.nextSibling()) {
		link_no += 1;
	}//for
	strList << QString::number(link_no);

	for (QDomNode n = annotation_properties.firstChild(); !n.isNull(); n
			= n.nextSibling()) {
		QDomElement link = n.toElement();
		strList << QString(link.attribute("yaw_deg"));
		strList << QString(link.attribute("pano_id"));
		strList << QString(link.attribute("road_argb"));
		strList << QString(link.attribute("scene"));

		QDomElement link_text_el = link.firstChildElement("link_text");
		if (!link_text_el.isNull()) {
			//qDebug() << "link_text found";
			strList << QString(link_text_el.text());
		}
	}//for

	/*if there is not any link fields prints "0" in the end of the list
	if (annotation_properties.firstChild().isNull()) {
		strList << "0";
	}*/

	enMetadata = strList.join(";");
	//qDebug() << "1. metadata" << enMetadata;
	return enMetadata;
}
/******************************************************************************/

/******************************************************************************/
bool XMLParser::schemaValidation(QString schemaStr)
{
	bool validationOK = true;

	const QByteArray schemaArray(schemaStr.toUtf8());
	QXmlSchema schema;
	schema.load(schemaArray);

	if (schema.isValid()) {
		//qDebug() << "schema is valid";
	} else {
		//qDebug() << "schema is invalid";
		validationOK = false;
	}
	return validationOK;
}
/******************************************************************************/

/*! \brief Something.
  * \todo Remove debug-prints.
  */
bool XMLParser::xmlValidation(QString xmlStr, QString schemaStr)
{
    //qDebug() << "xmlValidation...";

	bool validationOK = true;
	QByteArray xmlArray;

    xmlArray.append(xmlStr.toUtf8());

    const QByteArray schemaArray(schemaStr.toUtf8());
    QXmlSchema schema;
    bool valid = schema.load(schemaArray);

    if (valid) {
		//qDebug() << "schema is valid";
	} else {
		//qDebug() << "schema is invalid";
		validationOK = false;
	}
	QXmlSchemaValidator validator(schema);
	if (validator.validate(xmlArray)) {
		//qDebug() << "instance document is valid";
	} else {
		//qDebug() << "instance document is invalid";
		validationOK = false;
	}

	return validationOK;
}

/******************************************************************************/
QString XMLParser::loadSchema() {
    QString schemaData("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" "
        "elementFormDefault=\"qualified\">"

        "<xs:element name=\"panorama\">"
        "<xs:complexType>"
        "<xs:all>"
        "<xs:element ref=\"data_properties\" minOccurs=\"1\"/>"
        "<xs:element ref=\"projection_properties\" minOccurs=\"1\"/>"
        "<xs:element ref=\"annotation_properties\" minOccurs=\"1\"/>"
        "</xs:all>"
        "</xs:complexType>"
        "</xs:element>"

        "<xs:element name=\"data_properties\">"
        "<xs:complexType>"
        "<xs:all>"
        "<xs:element ref=\"copyright\" minOccurs=\"0\"/>"
        "<xs:element ref=\"text\" minOccurs=\"0\"/>"
        "<xs:element ref=\"region\" minOccurs=\"0\"/>"
        "<xs:element ref=\"country\" minOccurs=\"0\"/>"
        "<xs:element ref=\"data_flag\" minOccurs=\"0\"/>"
        "</xs:all>"
        "<xs:attribute name=\"image_height\" use=\"required\" type=\"xs:integer\"/>"
        "<xs:attribute name=\"image_width\" use=\"required\" type=\"xs:integer\"/>"
        "<xs:attribute name=\"lat\" use=\"required\" type=\"xs:decimal\"/>"
        "<xs:attribute name=\"lng\" use=\"required\" type=\"xs:decimal\"/>"
        "<xs:attribute name=\"num_zoom_levels\" use=\"required\" type=\"xs:integer\"/>"
        "<xs:attribute name=\"original_lat\" use=\"required\" type=\"xs:decimal\"/>"
        "<xs:attribute name=\"original_lng\" use=\"required\" type=\"xs:decimal\"/>"
        "<xs:attribute name=\"pano_id\" use=\"required\" type=\"xs:NCName\"/>"
        "<xs:attribute name=\"tile_height\" use=\"required\" type=\"xs:integer\"/>"
        "<xs:attribute name=\"tile_width\" use=\"required\" type=\"xs:integer\"/>"
        "<xs:anyAttribute/>"
        "</xs:complexType>"
        "</xs:element>"

        "<xs:element name=\"copyright\" type=\"xs:string\"/>"
        "<xs:element name=\"text\" type=\"xs:string\"/>"
        "<xs:element name=\"region\" type=\"xs:string\"/>"
        "<xs:element name=\"country\" type=\"xs:string\"/>"
        "<xs:element name=\"data_flag\" type=\"xs:integer\"/>"

        "<xs:element name=\"projection_properties\">"
        "<xs:complexType>"
        "<xs:attribute name=\"pano_yaw_deg\" use=\"required\" type=\"xs:decimal\"/>"
        "<xs:attribute name=\"projection_type\" use=\"required\" type=\"xs:NCName\"/>"
        "<xs:attribute name=\"tilt_pitch_deg\" use=\"required\" type=\"xs:decimal\"/>"
        "<xs:attribute name=\"tilt_yaw_deg\" use=\"required\" type=\"xs:decimal\"/>"
        "<xs:anyAttribute/>"
        "</xs:complexType>"
        "</xs:element>"

        "<xs:element name=\"annotation_properties\">"
        "<xs:complexType>"
        "<xs:sequence>"
        "<xs:element minOccurs=\"0\" maxOccurs=\"unbounded\" ref=\"link\"/>"
        "</xs:sequence>"
        "</xs:complexType>"
        "</xs:element>"

        "<xs:element name=\"link\">"
        "<xs:complexType>"
        "<xs:sequence>"
        "<xs:element ref=\"link_text\"/>"
        "</xs:sequence>"
        "<xs:attribute name=\"yaw_deg\" use=\"required\" type=\"xs:decimal\"/>"
        "<xs:attribute name=\"pano_id\" use=\"required\" type=\"xs:NCName\"/>"
        "<xs:attribute name=\"road_argb\" use=\"required\" type=\"xs:NMTOKEN\"/>"
        "<xs:attribute name=\"scene\" use=\"required\" type=\"xs:integer\"/>"
        "<xs:anyAttribute/>"
        "</xs:complexType>"
        "</xs:element>"

        "<xs:element name=\"link_text\" type=\"xs:string\"/>"
        "</xs:schema>");

    const QByteArray schemaArray(schemaData.toUtf8());

    QXmlSchema schema;
    schema.load(schemaArray);

    if (schema.isValid()) {
        //qDebug() << "schema is valid";
    } else {
        qDebug() << "schema is invalid";
        return "schema invalid";
    }

    return schemaData;
}
/*
void XMLParser::schemaValidation(QString xmlSchema) {
    //qDebug() << "schemaValidation...";

    const QByteArray data(xmlSchema.toUtf8());

    QXmlSchema schema;
    schema.load(data);

    if (schema.isValid()) {
        qDebug() << "schema is valid";
    } else
        qDebug() << "schema is invalid";

}
*/

/* \todo Remove from final verision of GSVWrapper, but not before it. */
QString XMLParser::getPid(QString xmlStr)
{
    // qDebug() << QString("XMLParser::parse(QString xmlStr): '%1'").arg(xmlStr);

    QString panoID;

    doc.setContent(xmlStr);

    QDomElement root = doc.documentElement();
    if (root.tagName() != "panorama") {
        qDebug() << "Unknown root element in xml.";
        return QString();
    }

    QDomElement data_properties = root.firstChildElement("data_properties");
    if(data_properties.hasAttribute("pano_id")) {
        panoID = data_properties.attribute("pano_id");
    } else {
        qDebug() << "Can't find pano_id from xml.";
        return QString();
    }

    return panoID;
}

/*!
 * @}
 */
