/*
 * Author Mikko Saavinen
 */
#ifndef XMLPARSER_H
#define XMLPARSER_H

/*!
 * \defgroup xmlparser XmlParser
 *  @{
 */
#include <QDebug>
#include <QDomElement>
#include <QDomDocument>
#include <QObject>
#include <QThread>

#include "metadata.h"

namespace GSVXML {
    class XMLParser;
}

/******************************************************************************/
/*!
 * \brief Object offering services to manipulate and validate metadata
 *
 * An object defines the valid syntax and semantics for handled metadata files.
 * The XML Schema used follows the definition of unofficial GSV API.
 *
 */
/******************************************************************************/
class XMLParser: public QObject
{
    Q_OBJECT

public:
    XMLParser(); //!< A constructor
    ~XMLParser(); //!< A destructor

    void moveToThread(QThread *thread);

    //TODO: return a metadata object if valid, emit error otherwise
    /*!
     * \fn parse
     * \brief Takes a xml string as input and check the semantics against
     * defined GSV API.
     *
     *  \param xmlStr Metadata in xml format.
     *
     *  \return Metadata which is allocated with new. Remember to delete allocated memory.
     *
     *  \sa xmlparser
     */
    Metadata *parse(QString xmlStr);

    QString getPid(QString xmlStr); //!< Test function, remove from final

private:

#ifndef UNIT_TEST
private:
#else
public:
#endif
    QDomDocument doc;

    /*! \ingroup xmlparser
     * \brief This function validates XML data against the schema. Both, XML data and schema
     *  are given as an input attribute. Returns False, if error occurs. True otherwise.
     * \param xmlStr
     * \param schemaStr
     *
     * \return TRUE if XML data is valid, FALSE otherwise
     *
     */
    bool xmlValidation(QString xmlStr, QString schemaStr);

    /*! \ingroup xmlparser
     * \brief This function validates given XML schema. Returns False, if error occurs. True otherwise.
     * \param xmlSchema
     *
     * \return TRUE if Schema is valid, FALSE otherwise
     *
     */
    bool schemaValidation(QString xmlSchema);
    /*! \ingroup xmlparser
         * \brief This function returns predefined Schema.
         *  Includes XML schema as a string.
         *
         * \return Schema
         *
         */
    QString loadSchema();
    /*! \ingroup xmlparser
         * \brief Parses fiven XML string to the encoded metadata string. First parser
         * includes all data fields to string list. Final string is constructed from
         * the list. Semicolon is used on a final string as a
         * delimiter between different fields.
         *
         * \param xmlStr
         * \return Encoded metadata string
         *
         */
    QString setMetadataStr(QString xmlStr);
};

/*!
 * @}
 */

#endif // XMLPARSER_H
