/*
 * Author Jarno Tuovinen
 */
#ifndef TST_FILEHANDLER_H
#define TST_FILEHANDLER_H

/*!
 * \defgroup filehandler FileHandler unit tests.
 * \ingroup test
 *
 * @{
 */

#include <QDebug>
#include <QObject>
#include <QtTest>

#include "filehandler.h"

/******************************************************************************/
class Tst_filehandler : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    // Initializers
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    // Tests itself
    void writeXMLTest1();
    void clearCacheTest1();

private:
    FileHandler filehandler;
};

/*
 * @}
 */

#endif // TST_FILEHANDLER_H
