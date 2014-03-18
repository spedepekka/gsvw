# -------------------------------------------------
#
# -------------------------------------------------

include(./GSVWrapper.pri)

INCLUDEPATH += ./

SOURCES += main.cpp

# TODO: Remove
HEADERS += offlinenetworkhandler.h
SOURCES += offlinenetworkhandler.cpp

QT += core \
    gui \
    network \
    xml \
    xmlpatterns
TARGET = gsvwrapper

# Create makefiles for both builds and set the debug as default
CONFIG += debug_and_release \
    debug
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

MOC_DIR = moc
OBJECTS_DIR = obj
DESTDIR = executable
UI_DIR = ui

# uncomment to build static lib
#TEMPLATE = lib
#CONFIG -= dll plugin
#CONFIG += staticlib

# uncomment to build dynamic lib
TEMPLATE = lib
CONFIG -= staticlib plugin
CONFIG += dll
SOURCES -= main.cpp
DESTDIR = "../lib"
library_headers.files = *.h
library_headers.path = "../include"
INSTALLS += library_headers

# TODO: Remove
#DEFINES += OFFLINE
