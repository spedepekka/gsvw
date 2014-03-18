#ifndef TST_GSVWRAPPER_H
#define TST_GSVWRAPPER_H

/*!
 * \defgroup gsvwrapper GSVWrapper unit tests.
 *
 * @{
 */

#include <QDebug>
#include <QObject>
#include <QtTest>

#include "gsvwrapper.h"

/******************************************************************************/
class Tst_gsvwrapper : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    // Initializers
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    // Tests
    void organizeRequestsTest1();
    void insertRequestTest1();
    void insertRequestTest2();

private:
    GSVWrapper gsvwrapper;
};

/*
 * @}
 */
#endif // TST_GSVWRAPPER_H
