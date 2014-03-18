#include <QtCore/QCoreApplication>

#include "tst_gsvwrapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    int ret = 0;

    Tst_gsvwrapper tst_gsvwrapper;
    ret += QTest::qExec(&tst_gsvwrapper, argc, argv);

    if(ret == 0)
        qDebug() << "ALL TESTS PASSED";
    else
        qDebug() << QString("%1 TESTS FAILED!").arg(ret);

    return ret;
}
