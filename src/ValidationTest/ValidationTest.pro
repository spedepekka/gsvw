# ###############################################################################
# ###############################################################################
QT += testlib \
    core \
    gui \
    xml \
    xmlpatterns \
    network

TARGET = validate_gsvwrapper
CONFIG += console \
    debug
CONFIG -= app_bundle
TEMPLATE = app

INCLUDEPATH += ./
INCLUDEPATH += ../include/

SOURCES += main.cpp \
    tst_gsvwrapper.cpp
HEADERS += tst_gsvwrapper.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"

MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = executable
UI_DIR = ui

# ###############################################################################
# Library to be tested
# ###############################################################################
LIBS += -L../lib/ -lgsvwrapper
