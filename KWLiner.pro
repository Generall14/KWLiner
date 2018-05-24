#-------------------------------------------------
#
# Project created by QtCreator 2018-05-23T21:22:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KWLiner
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    src/mainwindow.cpp \
    src/core.cpp \
    src/FileList.cpp \
    src/resFile.cpp \
    src/set.cpp \
    src/sets/setCpp.cpp \
    src/sets/setMSP.cpp \
    src/import/GlobalXmlFile.cpp \
    src/import/pugixml.cpp \
    src/import/Restorable.cpp \
    src/sets/setJava.cpp \
    src/sets/setPIC.cpp \
    src/sets/setPython.cpp

HEADERS += \
    src/mainwindow.h \
    src/core.hpp \
    src/FileList.hpp \
    src/resFile.hpp \
    src/set.hpp \
    src/sets/setCpp.hpp \
    src/sets/setMSP.hpp \
    src/import/GlobalXmlFile.hpp \
    src/import/pugiconfig.hpp \
    src/import/pugixml.hpp \
    src/import/Restorable.hpp \
    src/sets/setJava.hpp \
    src/sets/setPIC.hpp \
    src/sets/setPython.hpp
