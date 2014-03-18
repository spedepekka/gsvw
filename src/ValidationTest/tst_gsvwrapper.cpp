/*
 * Author: Veijo Pesonen
 */
#include <QDebug>
#include <QLibrary>


#include "gsvwrapper.h"

#include "tst_gsvwrapper.h"


/******************************************************************************/
/*!
 * \ingroup gsvwrapper_valid
 * \brief Configure some initial settings.
 * \return PASS
 */
/******************************************************************************/
void Tst_gsvwrapper::initTestCase()
{
}

/******************************************************************************/
/*!
 * \ingroup gsvwrapper_valid
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
 * \ingroup gsvwrapper_valid
 * \brief This will be executed before every test.
 */
/******************************************************************************/
void Tst_gsvwrapper::init()
{
}

/******************************************************************************/
/*!
 * \ingroup gsvwrapper_valid
 * \brief This will be executed after every test.
 */
/******************************************************************************/
void Tst_gsvwrapper::cleanup()
{
}

/******************************************************************************/
/*!
 * \ingroup gsvwrapper_valid
 * \brief This will be executed after every test.
 */
/******************************************************************************/
void Tst_gsvwrapper::libraryIncluded()
{
    bool libLinked = false;
    GSVWrapper* gsvworker;
    QLibrary gsvwLib("gsvwrapper");

    typedef GSVWrapper* (*GSVWrapperFunction)();

     GSVWrapperFunction getInstance = (GSVWrapperFunction) gsvwLib.resolve("getInstance");

     qDebug() << "lib loaded:"<<gsvwLib.isLoaded();
     /* Library loaded and we are capable of getting handle to a GSVWrapper object */
     if(gsvwLib.isLoaded() == true && getInstance) {
         libLinked = true;

         gsvworker = getInstance();

         delete gsvworker;
     }


    QVERIFY(libLinked == true);
}
