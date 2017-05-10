#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T11:28:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SndBackendSim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    CommandInterfaceProxy.h

FORMS    += mainwindow.ui

DISTFILES += \
    CommandInterface.xml
