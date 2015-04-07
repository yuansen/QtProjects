#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T11:50:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImReadShow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

# OpenCV setting for Ubuntu
# Requirement:
#     Compiled OpenCV
#     Ref: "Installing OpenCV 3.0.0 beta on Ubuntu 14.04"
#           http://rodrigoberriel.com/2014/10/installing-opencv-3-0-0-on-ubuntu-14-04/

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_core -lopencv_features2d
LIBS += -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc
LIBS += -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape
LIBS += -lopencv_stitching -lopencv_superres -lopencv_videoio
LIBS += -lopencv_video -lopencv_videostab
