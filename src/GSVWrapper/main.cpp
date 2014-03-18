#include <QtCore/QCoreApplication>

#include "gsvwrapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GSVWrapper gsv;

    return a.exec();
}
