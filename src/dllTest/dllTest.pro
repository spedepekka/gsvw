#-------------------------------------------------
#
# Project created by QtCreator 2011-04-26T19:35:32
#
#-------------------------------------------------

QT       += core \
            gui \
            xml \
            xmlpatterns \
            network

INCLUDEPATH += . \
                ../GSVWrapper/
LIBS += -L../lib/ -lgsvwrapper


TARGET = dllTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
