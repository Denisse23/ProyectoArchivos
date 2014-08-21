#-------------------------------------------------
#
# Project created by QtCreator 2014-08-20T13:17:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProyectoArch
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    nuevo.cpp \
    campos.cpp \
    registros.cpp

HEADERS  += window.h \
    nuevo.h \
    campos.h \
    registros.h

FORMS    += window.ui \
    nuevo.ui \
    registros.ui
