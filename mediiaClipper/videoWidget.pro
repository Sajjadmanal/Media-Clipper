#-------------------------------------------------
#
# Project created by QtCreator 2015-09-04T12:04:35
#
#-------------------------------------------------

QT += widgets
QT += core gui
QT += multimediawidgets
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videoWidget
TEMPLATE = app


SOURCES += main.cpp \
    videoPlayer.cpp

HEADERS  += \
    videoplayer.h

FORMS    += \
    videoWidget.ui
