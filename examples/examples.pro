#-------------------------------------------------
#
# Project created by QtCreator 2009-11-07T11:36:25
#
#-------------------------------------------------

QT       += testlib

TARGET = qtfindreplacedialog_example
TEMPLATE = app

# -------------------------------------------------
# Auto select compiler
# -------------------------------------------------
win32-g++:      COMPILER = mingw
win32-msvc*:    COMPILER = msvc
linux-g++:      COMPILER = gcc

INCLUDEPATH += . ../dialogs ../lib
DEPENDPATH += ../lib .

LIBS += -L../lib -lqtfindreplacedialog

QTFINDREPLACE_LIB = ../lib/libqtfindreplacedialog.a
contains(COMPILER, msvc) {
    QTFINDREPLACE_LIB = ../lib/qtfindreplacedialog.lib
}
TARGETDEPS += $$QTFINDREPLACE_LIB

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
