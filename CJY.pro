QT       += core gui
QT       += charts
QT       += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    comset1.cpp \
    comset2.cpp \
    comset3.cpp \
    main.cpp \
    spcdev1.cpp \
    spcdev2.cpp \
    spcdev3.cpp \
    widget.cpp

HEADERS += \
    comset1.h \
    comset2.h \
    comset3.h \
    spcdev1.h \
    spcdev2.h \
    spcdev3.h \
    widget.h

FORMS += \
    comset1.ui \
    comset2.ui \
    comset3.ui \
    spcdev1.ui \
    spcdev2.ui \
    spcdev3.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
