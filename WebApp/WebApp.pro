QT -= gui
QT += network
QT +=sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
TARGET=WebApp
include(/root/WebApp/QtWebApp/httpserver/httpserver.pri)

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INSTALLS +=target
target.path=/home/pi

SOURCES += \
        main.cpp \
    myhomecontroler.cpp \
    listdatacontroller.cpp \
    rm.cpp \
    logincontroller.cpp \
    requestmapper.cpp \
    errorhandler.cpp \
    cookiecontroller.cpp \
    dbcontext.cpp \
    filterresponse.cpp \
    getlog.cpp


OTHER_FILES += etc/webapp1.ini

HEADERS += \
    myhomecontroler.h \
    listdatacontroller.h \
    rm.h \
    logincontroller.h \
    requestmapper.h \
    errorhandler.h \
    cookiecontroller.h \
    dbcontext.h \
    filterresponse.h \
    getlog.h
