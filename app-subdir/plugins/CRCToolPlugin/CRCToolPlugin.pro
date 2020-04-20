include(../plugins.pri)

QT += widgets

DEFINES += CRCTOOLPLUGIN_LIBRARY

LIBS += \
    $$APP_OUTPUT_PATH/../libs/utils.lib \
    $$APP_OUTPUT_PATH/../libs/extensionsystem.lib\
    $$APP_OUTPUT_PATH/../libs/core.lib

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    crcpage.cpp \
    crctoolplugin.cpp \
    crcwidget.cpp \
    floatbox.cpp \
    systemconversionbox.cpp

HEADERS += \
    CRCToolPlugin_global.h \
    crcpage.h \
    crctoolplugin.h \
    crcwidget.h \
    floatbox.h \
    systemconversionbox.h

OTHER_FILES += crctoolplugin.json
