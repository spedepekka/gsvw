/*
 * Author: Tommi Käsmä
 */
#include "tst_networkhandler.h"

/******************************************************************************/
void Tst_networkhandler::initTestCase()
{
}

/******************************************************************************/
void Tst_networkhandler::cleanupTestCase()
{
}

/******************************************************************************/
void Tst_networkhandler::init()
{
}

/******************************************************************************/
void Tst_networkhandler::cleanup()
{
    networkhandler.urlList.clear();
}

/******************************************************************************/
/*! \ingroup networkhandler
 */
/******************************************************************************/
void Tst_networkhandler::testPushUrl1()
{
    /* Variables */
    Url url1(1,1, QUuid::createUuid().toString());
    Url url2(2,2, QUuid::createUuid().toString());
    Url url3(3,3, QUuid::createUuid().toString());
    Url url4(4,4, QUuid::createUuid().toString());

    /* Preconditions */
    QVERIFY2(networkhandler.urlList.isEmpty(), "urlList should be empty");

    /* Execute */
    networkhandler.pushUrl(url1);
    networkhandler.pushUrl(url2);
    networkhandler.pushUrl(url3);
    networkhandler.pushUrl(url4);

    /* Postconditions */
    QVERIFY2(!(networkhandler.urlList.isEmpty()), "urlList should not be empty");

    QVERIFY2(networkhandler.urlList[0].request == url1.request, "NetworkRequest objects do not match");
    QVERIFY2(networkhandler.urlList[0].reply == url1.reply, "NetworkReply pointers do not match");
    QVERIFY2(networkhandler.urlList[0].id == url1.id, "Request IDs do not match");

    QVERIFY2(networkhandler.urlList[1].request == url2.request, "NetworkRequest objects do not match");
    QVERIFY2(networkhandler.urlList[1].reply == url2.reply, "NetworkReply pointers do not match");
    QVERIFY2(networkhandler.urlList[1].id == url2.id, "Request IDs do not match");

    QVERIFY2(networkhandler.urlList[2].request == url3.request, "NetworkRequest objects do not match");
    QVERIFY2(networkhandler.urlList[2].reply == url3.reply, "NetworkReply pointers do not match");
    QVERIFY2(networkhandler.urlList[2].id == url3.id, "Request IDs do not match");

    QVERIFY2(networkhandler.urlList[3].request == url4.request, "NetworkRequest objects do not match");
    QVERIFY2(networkhandler.urlList[3].reply == url4.reply, "NetworkReply pointers do not match");
    QVERIFY2(networkhandler.urlList[3].id == url4.id, "Request IDs do not match");
}


/******************************************************************************/
/*! \ingroup networkhandler
 */
/******************************************************************************/void Tst_networkhandler::testPopUrl1()
{
    /* Variables */
    Url tempUrl;
    Url url1(1,1, QUuid::createUuid().toString());
    url1.setReply(reinterpret_cast<QNetworkReply*>(&url1));
    Url url2(2,2, QUuid::createUuid().toString());
    url1.setReply(reinterpret_cast<QNetworkReply*>(&url2));
    Url url3(3,3, QUuid::createUuid().toString());
    url1.setReply(reinterpret_cast<QNetworkReply*>(&url3));
    Url url4(4,4, QUuid::createUuid().toString());
    url1.setReply(reinterpret_cast<QNetworkReply*>(&url4));

    /* Preconditions */
    networkhandler.urlList.append(url1);
    networkhandler.urlList.append(url2);
    networkhandler.urlList.append(url3);
    networkhandler.urlList.append(url4);

    /* Execute */
    tempUrl = networkhandler.popUrl(url1.reply);

    /* Postconditions */
    QVERIFY2(tempUrl.reply == url1.reply, "NetworkReply pointers do not match");
    QVERIFY2(tempUrl.id == url1.id, "Request IDs do not match");
    foreach(Url u, networkhandler.urlList) {
        if(u.id == url1.id)
            QFAIL("Popped Url object is still in the urlList");
    }
    QVERIFY2((networkhandler.urlList.size() == 3),
             "Url object did not get removed from urlList properly");

    /* Execute */
    tempUrl = networkhandler.popUrl(url2.reply);

    /* Postconditions */
    QVERIFY2(tempUrl.reply == url2.reply, "NetworkReply pointers do not match");
    QVERIFY2(tempUrl.id == url2.id, "Request IDs do not match");
    foreach(Url u, networkhandler.urlList) {
        if(u.id == url2.id)
            QFAIL("Popped Url object is still in the urlList");
    }
    QVERIFY2((networkhandler.urlList.size() == 2),
             "Url object did not get removed from urlList properly");

    /* Execute */
    tempUrl = networkhandler.popUrl(url3.reply);

    /* Postconditions */
    QVERIFY2(tempUrl.reply == url3.reply, "NetworkReply pointers do not match");
    QVERIFY2(tempUrl.id == url3.id, "Request IDs do not match");
    foreach(Url u, networkhandler.urlList) {
        if(u.id == url3.id)
            QFAIL("Popped Url object is still in the urlList");
    }
    QVERIFY2((networkhandler.urlList.size() == 1),
             "Url object did not get removed from urlList properly");

    /* Execute */
    tempUrl = networkhandler.popUrl(url4.reply);

    /* Postconditions */
    QVERIFY2(tempUrl.reply == url4.reply, "NetworkReply pointers do not match");
    QVERIFY2(tempUrl.id == url4.id, "Request IDs do not match");
    foreach(Url u, networkhandler.urlList) {
        if(u.id == url4.id)
            QFAIL("Popped Url object is still in the urlList");
    }
    QVERIFY2((networkhandler.urlList.size() == 0),
             "Url object did not get removed from urlList properly");
}


/******************************************************************************/
/*! \ingroup networkhandler
 */
/******************************************************************************/
void Tst_networkhandler::testReset1()
{
    /* Variables */
    Url url1(1,1, QUuid::createUuid().toString());
    Url url2(2,2, QUuid::createUuid().toString());
    Url url3(3,3, QUuid::createUuid().toString());
    Url url4(4,4, QUuid::createUuid().toString());

    /* Preconditions */
    networkhandler.urlList.append(url1);
    networkhandler.urlList.append(url2);
    networkhandler.urlList.append(url3);
    networkhandler.urlList.append(url4);

    /* Execute */
    networkhandler.reset();

    /* Postconditions */
    QVERIFY2(networkhandler.urlList.isEmpty(), "urlList didn't get cleared");
}
