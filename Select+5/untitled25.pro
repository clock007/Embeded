QT += quick
QT +=serialport
QT +=sql
CONFIG += c++11
QT += sql
QT += qml quick widgets sql
QT += multimedia
#CONFIG +=lang-all
CONFIG+="lang-en_EN lang-fa_FA"
QT       += core gui widgets sql
QT +=multimedia multimediawidgets
QT += xml
include(/root/QtWebApp/httpserver/httpserver.pri)
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    fingersign.cpp \
    listmodel.cpp \
    database.cpp \
    verify.cpp \
    spi.cpp \
    qdateconvertor.cpp \
    systemproperties.cpp \
    requestmapper.cpp \
    listdatacontroller.cpp \
    myhomecontroler.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.



HEADERS += \
    fingersign.h \
    listmodel.h \
    database.h \
    verify.h \
    spi.h \
    qdateconvertor.h \
    systemproperties.h \
    requestmapper.h \
    listdatacontroller.h \
    httplistener.h \
    myhomecontroler.h

DISTFILES +=


#LIBS += -L/usr/local/lib -lwiringPi



INCLUDEPATH += /usr/local/include
#INCLUDEPATH += /usr/local/include/raspicam
INCLUDEPATH += /usr/local/lib


#LIBS += -lwiringPi



INCLUDEPATH += /usr/local/include
#INCLUDEPATH += /usr/local/include/raspicam
#INCLUDEPATH += /usr/local/lib


INCLUDEPATH += /usr/local/include/opencv2
INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv4
INCLUDEPATH += /usr/local/include/opencv4/opencv2
#INCLUDEPATH += /usr/local/include/raspicam
INCLUDEPATH += /usr/local/lib


LIBS += -lwiringPi -lraspicam -lraspicam_cv -lwiringPi -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_video -lopencv_videoio  -lopencv_flann -lopencv_highgui -lopencv_features2d -lopencv_photo -lopencv_video -lopencv_objdetect -lopencv_videostab -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_dnn -lopencv_ml -lopencv_face




INSTALLS +=target
target.path=/home/pi
