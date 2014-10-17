#-------------------------------------------------
#
# Project created by QtCreator 2014-05-16T14:47:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CardPreview
TEMPLATE = app
DESTDIR = ../bin

SOURCES += main.cpp \
    qtroundedrectitem.cpp \
    cardid1.cpp \
    designtitem.cpp \
    designcardmodel.cpp \
    Window.cpp \
    fullcardid1.cpp \
    edittextdesign.cpp \
    editimagedesign.cpp

HEADERS  += \
    qtroundedrectitem.h \
    cardid1.h \
    designtitem.h \
    designcardmodel.h \
    Window.h \
    fullcardid1.h \
    edittextdesign.h \
    editimagedesign.h

FORMS += \
    Window.ui \
    edittextdesign.ui \
    editimagedesign.ui
