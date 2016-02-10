#-------------------------------------------------
#
# Project created by QtCreator 2016-02-09T17:31:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += c++11

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

win32 {
    INCLUDEPATH += "$${PWD}"
}

win32-g++ {
    LIBS += "$${PWD}/win_deps/win32/libcryptopp.dll.a"

    dynamiclibrary.files = "libcryptopp.dll"
    dynamiclibrary.path = "$${PWD}/win_deps/win32"

    DEPLOYMENT += dynamicfiles
    DEFINES += NO_OS_DEPENDENCE OS_RNG_AVAILABLE NDEBUG
}

win32-msvc2013 {
    #LIBS += "$${PWD}/win_deps/win64/cryptopp.lib"
    DEFINES += OS_RNG_AVAILABLE NDEBUG
    #DEFINES += CRYPTOPP_IMPORTS
}

linux:!android: LIBS += -ldl -lcrypto++

