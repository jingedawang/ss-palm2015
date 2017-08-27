TEMPLATE = app

QT += qml quick network

SOURCES += main.cpp \
    communicationmanager.cpp \
    communication.cpp \
    commandmanager.cpp \
    uiadapter.cpp \
    command.cpp \
    device.cpp \
    action.cpp \
    devicelsr.cpp \
    actionrun.cpp \
    devicescn.cpp \
    devicestg.cpp \
    devicetsk.cpp \
    devicecmr.cpp \
    deviceucm.cpp \
    actionstp.cpp \
    actionask.cpp \
    devicedmi.cpp \
    actionbrk.cpp \
    devicepst.cpp \
    devicepcm.cpp \
    devicepdt.cpp \
    queryservice.cpp \
    deviceldr.cpp \
    deviceenv.cpp \
    devicecfg.cpp \
    messagereceiveservice.cpp \
    actionrpt.cpp \
    datareceiveservice.cpp \
    remoteservice.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    communicationmanager.h \
    communication.h \
    commandmanager.h \
    uiadapter.h \
    command.h \
    device.h \
    action.h \
    devicelsr.h \
    actionrun.h \
    devicescn.h \
    devicestg.h \
    devicetsk.h \
    devicecmr.h \
    deviceucm.h \
    actionstp.h \
    actionask.h \
    devicedmi.h \
    actionbrk.h \
    devicepst.h \
    devicepcm.h \
    devicepdt.h \
    queryservice.h \
    deviceldr.h \
    deviceenv.h \
    devicecfg.h \
    messagereceiveservice.h \
    actionrpt.h \
    datareceiveservice.h \
    remoteservice.h



ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

DISTFILES += \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle
