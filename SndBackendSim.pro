#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T11:28:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SndBackendSim
TEMPLATE = app


SOURCES += \
    main.cpp\
    mainwindow.cpp \
    CommandInterface/CommandInterfaceConverter.cpp \
    CommandInterface/CommandInterface.cpp

HEADERS  += mainwindow.h \
    CommandInterface/CommandInterface.h \
    CommandInterface/CommandInterfaceConverter.h \
    CommandInterface/CommandInterfaceProxy.h

FORMS    += mainwindow.ui

DISTFILES += \
    CommandInterface/CommandInterface.xml

INCLUDEPATH += \
    /usr/include/dbus-c++-1 \
    CommandInterface/

unix|win32: LIBS += -ldbus-c++-1
