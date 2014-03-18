#include <QtGui/QApplication>

#include <QDebug>

#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Main thread is" << a.thread();

    MainWidget w;
    w.show();

    return a.exec();
}
