#-------------------------------------------------
#
# Project created by QtCreator 2016-02-09T17:31:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GoGo40-keygen
TEMPLATE = app


SOURCES += main.cpp\
        keygen_widget.cpp \
    keygen.cpp \
    tests.cpp

HEADERS  += keygen_widget.h \
    keygen.h \
    tests.h

FORMS    += keygen_widget.ui


linux:!android: LIBS += -ldl -lcrypto++
