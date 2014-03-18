/*
 * Author: Jarno Tuovinen
 */

#include "tst_gsvwrapper.h"

/******************************************************************************/
/*!
 * \ingroup test
 * \brief Configure some initial settings.
 * \return PASS
 */
/******************************************************************************/
void Tst_gsvwrapper::initTestCase()
{
}

/******************************************************************************/
/*!
 * \ingroup test
 * \brief Do some cleanup if necessary.
 *
 * \return PASS
 */
/******************************************************************************/
void Tst_gsvwrapper::cleanupTestCase()
{
}

/******************************************************************************/
/*!
 * \ingroup test
 * \brief This will be executed before every test.
 */
/******************************************************************************/
void Tst_gsvwrapper::init()
{
}

/******************************************************************************/
/*!
 * \ingroup test
 * \brief This will be executed after every test.
 */
/******************************************************************************/
void Tst_gsvwrapper::cleanup()
{
    gsvwrapper.requestQueue.clear();
}

/******************************************************************************/
/*!
 * \ingroup test
 * \brief Test request inserting.
 *
 * If requests are in priority order (smallest first), then PASS.
 */
/******************************************************************************/
void Tst_gsvwrapper::organizeRequestsTest1()
{
//    Request r1(0.0, 0.0, 1, "", 1);
//    Request r2(0.0, 0.0, 2, "", 2);
//    Request r3(0.0, 0.0, 3, "", 5);
//    Request r4(0.0, 0.0, 4, "", 5);
//    Request r5(0.0, 0.0, 5, "", 7);
//    Request r6(0.0, 0.0, 6, "", 9);

//    gsvwrapper.requestQueue.append(r3);
//    gsvwrapper.requestQueue.append(r5);
//    gsvwrapper.requestQueue.append(r2);
//    gsvwrapper.requestQueue.append(r6);
//    gsvwrapper.requestQueue.append(r3);
//    gsvwrapper.requestQueue.append(r1);
//    gsvwrapper.requestQueue.append(r4);

//    gsvwrapper.organizeRequests();

//    int prio = 0;
//    int old_prio = 0;
//    foreach(Request r, gsvwrapper.requestQueue) {
//        prio = r.priority;
//        if(prio < old_prio) {
//            QList<int> list;
//            foreach(Request re, gsvwrapper.requestQueue)
//                list.append(re.priority);
//            qDebug() << "Priorities are" << list;
//            QFAIL("Requests are not in smallest priority first.");
//        }
//        old_prio = prio;
//    }

    // Passed
}

/******************************************************************************/
/*!
 * \ingroup test
 * \brief Test request inserting.
 *
 * If requests are in priority order (smallest first), then PASS.
 */
/******************************************************************************/
void Tst_gsvwrapper::insertRequestTest1()
{
//    Request r1(0.0, 0.0, 1, "", 1);
//    Request r2(0.0, 0.0, 2, "", 2);
//    Request r3(0.0, 0.0, 3, "", 5);
//    Request r4(0.0, 0.0, 4, "", 5);
//    Request r5(0.0, 0.0, 5, "", 7);
//    Request r6(0.0, 0.0, 6, "", 9);

//    gsvwrapper.requestQueue.append(r3);
//    gsvwrapper.requestQueue.append(r5);
//    gsvwrapper.requestQueue.append(r2);
//    gsvwrapper.requestQueue.append(r6);
//    gsvwrapper.requestQueue.append(r3);
//    gsvwrapper.requestQueue.append(r1);
//    gsvwrapper.requestQueue.append(r4);

//    Request rTest1(123.0, 123.0, 0, "", 4);
//    gsvwrapper.insertRequest(rTest1);

//    int prio = 0;
//    int old_prio = 0;
//    foreach(Request r, gsvwrapper.requestQueue) {
//        prio = r.priority;
//        if(prio < old_prio) {
//            QList<int> list;
//            foreach(Request re, gsvwrapper.requestQueue)
//                list.append(re.priority);
//            qDebug() << "Priorities are" << list;
//            QFAIL("Requests are not in smallest priority first.");
//        }
//        old_prio = prio;
//    }

    // Passed
}

/******************************************************************************/
/*!
 * \ingroup test
 * \brief Test request inserting.
 *
 * If requests are in priority order (smallest first), then PASS.
 */
/******************************************************************************/
void Tst_gsvwrapper::insertRequestTest2()
{
//    Request r1(0.0, 0.0, 1, "", 1);
//    Request r2(0.0, 0.0, 2, "", 2);
//    Request r3(0.0, 0.0, 3, "", 5);
//    Request r4(0.0, 0.0, 4, "", 5);
//    Request r5(0.0, 0.0, 5, "", 7);
//    Request r6(0.0, 0.0, 6, "", 9);

//    gsvwrapper.requestQueue.append(r3);
//    gsvwrapper.requestQueue.append(r5);
//    gsvwrapper.requestQueue.append(r2);
//    gsvwrapper.requestQueue.append(r6);
//    gsvwrapper.requestQueue.append(r3);
//    gsvwrapper.requestQueue.append(r1);
//    gsvwrapper.requestQueue.append(r4);

//    Request rTest1(123.0, 123.0, 0, "", 4);
//    Request rTest2(123.0, 123.0, 0, "", 8);
//    Request rTest3(123.0, 123.0, 0, "", 5);

//    gsvwrapper.insertRequest(rTest1);
//    gsvwrapper.insertRequest(rTest2);
//    gsvwrapper.insertRequest(rTest3);

//    int prio = 0;
//    int old_prio = 0;
//    foreach(Request r, gsvwrapper.requestQueue) {
//        prio = r.priority;
//        if(prio < old_prio) {
//            QList<int> list;
//            foreach(Request re, gsvwrapper.requestQueue)
//                list.append(re.priority);
//            qDebug() << "Priorities are" << list;
//            QFAIL("Requests are not in smallest priority first.");
//        }
//        old_prio = prio;
//    }
}
