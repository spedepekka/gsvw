/*
 * Author Tommi Käsmä
 */
#ifndef TST_NETWORKHANDLER_H
#define TST_NETWORKHANDLER_H

/*!
 * \defgroup networkhandler NetworkHandler unit tests.
 * \ingroup test
 *
 * @{
 */

#include <QDebug>
#include <QObject>
#include <QtTest>
#include <QString>
#include <QUuid>

#include "networkhandler.h"
#include "url.h"

/******************************************************************************/
class Tst_networkhandler : public QObject
{
    Q_OBJECT

private:
    NetworkHandler networkhandler;

private Q_SLOTS:
    // Initializers
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    /*! \ingroup networkhandler
     * \brief Test Description: Creates Url objects which are then inserted in
     *  the urlList with pushUrl.
     * \return PASS if Url's are pushed properly, FAIL otherwise.
     */
    void testPushUrl1();

    /*! \ingroup networkhandler
     * \brief Test Description: Populates urlList with valid Url objects and
     *  attempts to pop them with popUrl.
     * \return PASS if Url's are popped correctly, FAIL otherwise.
     */
    void testPopUrl1();

    /*! \ingroup metadata
     * \brief Test Description: Populate and then clear urlList with reset.
     * \return PASS if urlList emptied successfully, FAIL otherwise.
     */
    void testReset1();

};


/*
 * @}
 */
#endif // TST_NETWORKHANDLER_H
