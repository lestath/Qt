#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T16:50:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Warcaby_2_0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    pawn.cpp

HEADERS  += mainwindow.h \
    board.h \
    pawn.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
