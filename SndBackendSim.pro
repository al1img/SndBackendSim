#-------------------------------------------------
#
# Project created by QtCreator 2017-05-10T11:28:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = SndBackendSim
TEMPLATE = app

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    CommandInterface/CommandInterfaceConverter.cpp \
    CommandInterface/CommandInterface.cpp \
    PulsePlayer/PulsePlayer.cpp \
    AudioManager/AudioManager.cpp

HEADERS  += mainwindow.h \
    CommandInterface/CommandInterface.h \
    CommandInterface/CommandInterfaceConverter.h \
    CommandInterface/CommandInterfaceProxy.h \
    PulsePlayer/PulsePlayer.h \
    AudioManager/AudioManager.h

FORMS    += mainwindow.ui

DISTFILES += \
    CommandInterface/CommandInterface.xml

INCLUDEPATH += \
    CommandInterface/ \
    PulsePlayer \
    AudioManager

unix|win32: LIBS += -lpulse-simple -lpulse -ldbus-1

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += dbus-c++-1
