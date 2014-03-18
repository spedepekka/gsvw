/*
 * Author Mikko Saavinen
 */
#ifndef TST_XMLPARSER_H
#define TST_XMLPARSER_H

/*!
 * \defgroup xmlparser XmlParser unit tests.
 *
 * @{
 */

#include <QDebug>
#include <QFile>
#include <QObject>
#include <QString>
#include <QtTest>
#include <QTextStream>

#include "xmlparser.h"

/******************************************************************************/
class Tst_xmlparser : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    // Initializers
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    // Tests itself
    void XmlValid1();
    void XmlValid2();
    void XmlInvalid1();
    void XmlInvalid2();
    void XmlInvalid3();
    void XmlInvalid4();
    void SchemaValidation();
    void SchemaInvalidValidation();
    void XmlParserValid1();
    //void XmlParserValid2();

private:
    XMLParser xmlParser;
};

/*!
 * @}
 */
#endif // TST_XMLPARSER_H
