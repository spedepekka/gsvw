/*
 * Author: Veijo Pesonen
 */
#ifndef TST_GSVWRAPPER_H
#define TST_GSVWRAPPER_H

/*!
 * \defgroup gsvwrapper_valid GSVWrapper validation tests.
 *
 * @{
 */

#include <QDebug>
#include <QLibrary>
#include <QObject>
#include <QtTest>


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
    void libraryIncluded();

private:
};

/*
 * @}
 */
#endif // TST_GSVWRAPPER_H
