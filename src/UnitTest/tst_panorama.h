/*! \file tst_panorama.h
 *
 * \defgroup panorama Panorama unit tests.
 *
 * \defgroup metadata Metadata unit tests.
 *
 * \defgroup tile Tile unit tests.
 *
 * \addtogroup panorama
 * @{
 */
#ifndef TST_panorama_H
#define TST_panorama_H

#include <QDebug>
#include <QObject>
#include <QtTest>

#include "panorama.h"

/******************************************************************************/
class Tst_panorama : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    // Initializers
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    /*! \ingroup metadata
     * \brief Test Description: Uses a valid xml string to check that internal
     *  data structures are updated correctly
     * \return PASS if correct metadata is stored, FAIL otherwise
     */
    void ut_1();

    /*! \ingroup metadata
     * \brief Test Description: check's that all information related to panorama
     * is decoded correctly and stored on correct places. 0 links are present.
     */
    void ut_2();

    /*! \ingroup metadata
     * \brief Test Description: Checks that encoded link data is decoded
     * correctly and stored to a correct place. Empty string in case of number
     * of links indicates that 0 links are present.
     * \return PASS if data fields are updated and linklist is empty, FAIL
     * otherwise
     */
    void ut_3();

    /*! \ingroup metadata
     * \brief Test Description: check's that all information related to panorama
     * is decoded correctly and stored on correct places. 1 link is present.
     * \return PASS if data fields are set correctly and 1 link is added, FAIL
     * otherwise
     */
    void ut_4();

    /*! \ingroup metadata
     * \brief Test Description: check's that all information related to panorama
     * is decoded correctly and stored on correct places. 3 links are present.
     * \return PASS if data fields are set correctly and 3 links are added, FAIL
     * otherwise
     */
    void ut_5();

    /*! \ingroup metadata
     * \brief Test Description: check's that all information related to panorama
     * is decoded correctly and stored on correct places. 3 links are present
     * but two of those have same Panoid so only 2 links are stored.
     * \return PASS if data fields are set correctly and 2 links are added, FAIL
     * otherwise
     */
    void ut_6();

    /*! \ingroup metadata
     * \brief Test Description: Checks that right number with correct content
     * is returned.
     * \return PASS if right links are returned, FAIL otherwise
     */
    void ut_7();

    /*! \ingroup metadata
     * \brief Test Description: Uses incorrectly encoded metadata to check that
     *  internal data structures are not updated.
     * \return PASS if internal datastructures are not updated, FAIL otherwise
     */
    void ut_8();

private:
    Panorama panorama;
};

#endif // TST_panorama_H
/*
 * @}
 */
