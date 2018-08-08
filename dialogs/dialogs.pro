# -------------------------------------------------
# Project created by QtCreator 2009-11-07T11:39:43
# -------------------------------------------------
QT *= core gui
greaterThan(QT_MAJOR_VERSION,4):QT*=widgets
TARGET = qtfindreplacedialog
TEMPLATE = lib
DEFINES += FINDREPLACE_LIBRARY
SOURCES += findform.cpp \
    finddialog.cpp \
    findreplaceform.cpp \
    findreplacedialog.cpp
HEADERS += findreplaceform.h \
    findreplacedialog.h \
    findform.h \
    finddialog.h \
    findreplace_global.h
FORMS += findreplaceform.ui \
    findreplacedialog.ui
DESTDIR = ../lib
DEPENDPATH += .
target.path = /lib
headers.files = $$HEADERS
headers.path = /include
INSTALLS += target \
    headers
