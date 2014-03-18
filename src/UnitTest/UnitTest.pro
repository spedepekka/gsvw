# -------------------------------------------------
# -------------------------------------------------

include(../GSVWrapper/GSVWrapper.pri)
include(UnitTest.pri)

QT += testlib \
    core \
    gui \
    xml \
    xmlpatterns \
    network

TARGET = tst_gsvwrapper

CONFIG += console \
    debug

CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ./

SOURCES +=     main.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = executable
UI_DIR = ui
DEFINES += UNIT_TEST

