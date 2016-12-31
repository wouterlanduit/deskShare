#-------------------------------------------------
#
# Project created by QtCreator 2016-05-25T09:22:26
#
#-------------------------------------------------

QT       += core gui\
         network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeskShare
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        followmouse.cpp \
        mouseeventhandler.cpp \
        mousepoller.cpp \
    socketlistener.cpp \
    connection.cpp \
    network.cpp \
    event.cpp \
    fileevent.cpp \
    chatevent.cpp \
    transferwindow.cpp \
    abstractfile.cpp \
    singlefile.cpp \
    folder.cpp \
    httpsocketlistener.cpp \
    fileenvelope.cpp \
    eventenvelope.cpp \
    addressdialog.cpp \
    ipcontrol.cpp \
    dropbox.cpp

HEADERS  += mainwindow.h \
        followmouse.h \
    mouseeventhandler.h \
    mousepoller.h \
    socketlistener.h \
    connection.h \
    network.h \
    event.h \
    fileevent.h \
    chatevent.h \
    transferwindow.h \
    constants.h \
    abstractfile.h \
    singlefile.h \
    folder.h \
    fileenvelope.h \
    eventenvelope.h \
    addressdialog.h \
    ipcontrol.h \
    httpsocketlistener.h \
    dropbox.h

FORMS    += mainwindow.ui
