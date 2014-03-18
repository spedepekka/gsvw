#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QtTest>

#include "tst_filehandler.h"
#include "tst_gsvwrapper.h"
#include "tst_networkhandler.h"
#include "tst_panorama.h"
#include "tst_xmlparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    int ret = 0;

    Tst_filehandler tst_filehandler;
    ret += QTest::qExec(&tst_filehandler, argc, argv);

    Tst_networkhandler tst_networkhandler;
    ret += QTest::qExec(&tst_networkhandler, argc, argv);

    Tst_xmlparser tst_xmlparser;
    ret += QTest::qExec(&tst_xmlparser, argc, argv);

    Tst_panorama tst_panorama;
    ret += QTest::qExec(&tst_panorama, argc, argv);

    // This should be tested last
    Tst_gsvwrapper tst_gsvwrapper;
    ret += QTest::qExec(&tst_gsvwrapper, argc, argv);

    if(ret == 0)
        qDebug() << "ALL TESTS PASSED";
    else
        qDebug() << QString("%1 TESTS FAILED!").arg(ret);

    return ret;
}
