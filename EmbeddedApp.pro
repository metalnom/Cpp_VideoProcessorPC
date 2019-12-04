QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoProcessor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        btn_func.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib -lopencv_shape -lopencv_videoio -lopencv_objdetect -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_shape -lopencv_videoio -lopencv_calib3d -lopencv_face -L/usr/local/lib -L/usr/lib64 -L/usr/lib

#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /home/pi
#!isEmpty(target.path): INSTALLS += target
