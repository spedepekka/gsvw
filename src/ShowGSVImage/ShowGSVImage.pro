#-------------------------------------------------
#
#-------------------------------------------------

include(../GSVWrapper/GSVWrapper.pri)

QT       += core gui network xml xmlpatterns
CONFIG += qt debug_and_release debug
TARGET = ShowGSVImage
TEMPLATE = app

SOURCES += main.cpp \
    mainwidget.cpp

HEADERS  += mainwidget.h

FORMS    += mainwidget.ui

MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = executable
UI_DIR = ui

RESOURCES += \
    ./resources/resources.qrc

DEFINES += UNIT_TEST

# TODO: Remove
#DEFINES += OFFLINE
HEADERS += ../GSVWrapper/offlinenetworkhandler.h
SOURCES += ../GSVWrapper/offlinenetworkhandler.cpp
