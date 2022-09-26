QT       += core gui charts widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data_mem.cpp \
    devicesdr.cpp \
    main.cpp \
    mainwindow.cpp \
    mytimer.cpp

HEADERS += \
    data_mem.h \
    devicesdr.h \
    mainwindow.h \
    mytimer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /home/vitalik/SoapySDR/SoapySDR/build/lib
LIBS += -L/home/vitalik/SoapySDR/SoapySDR/build/lib -lSoapySDR
