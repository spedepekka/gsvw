/*
 * Author: Jarno Tuovinen
 */

/*!
 * \weakgroup filehandler
 *
 * @{
 */

#include "tst_filehandler.h"

#include <QDir>

/******************************************************************************/
/*!
 * \brief Configure some initial settings.
 * \return PASS
 */
/******************************************************************************/
void Tst_filehandler::initTestCase()
{
}

/******************************************************************************/
/*!
 * \brief Do some cleanup if necessary.
 *
 * \return PASS
 */
/******************************************************************************/
void Tst_filehandler::cleanupTestCase()
{
}

/******************************************************************************/
/*!
 * \brief This will be executed before every test.
 */
/******************************************************************************/
void Tst_filehandler::init()
{
}

/******************************************************************************/
/*!
 * \brief This will be executed after every test.
 */
/******************************************************************************/
void Tst_filehandler::cleanup()
{
    filehandler.clearCache();
}

/******************************************************************************/
/*!
 * \brief Test XML writing.
 * Writes trash to file and checks if file exists.
 * \return PASS
 */
/******************************************************************************/
void Tst_filehandler::writeXMLTest1()
{
    filehandler.writeXML(123.0, 321.0, "FooBar");
    QString filepath = filehandler.formXMLFileName(123.0, 321.0);

    QVERIFY2(QFile::exists(filepath),
             "File does not exist as it should.");
}

/******************************************************************************/
/*!
 * \brief Test cache clearing.
 * Writes trash to file and checks file is gone after clearCache-function.
 * \return PASS
 */
/******************************************************************************/
void Tst_filehandler::clearCacheTest1()
{
    filehandler.writeXML(123.0, 321.0, "FooBar");
    QString filepath = QDir::currentPath() + "/tmp/"
                      + filehandler.formXMLFileName(123.0, 321.0);
    filehandler.clearCache();
    QVERIFY2(!QFile::exists(filepath),
             "File exists, but it should not.");
}

/*!
 * @}
 */
