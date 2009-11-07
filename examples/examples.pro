#-------------------------------------------------
#
# Project created by QtCreator 2009-11-07T11:36:25
#
#-------------------------------------------------

QT       += testlib

TARGET = qtfindreplacedialog_example
TEMPLATE = app

#unix:!macx {
#qtfindreplacedialog_example.depends += ../lib/libqtfindreplacedialog.a
#}

INCLUDEPATH += . ../lib
DEPENDPATH += . ../lib
LIBS += -L../lib -lqtfindreplacedialog

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
