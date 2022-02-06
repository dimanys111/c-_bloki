#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T20:31:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bloki
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    blokmodel.cpp \
    treeitem.cpp

HEADERS  += mainwindow.h \
    blokmodel.h \
    treeitem.h

FORMS    += mainwindow.ui
