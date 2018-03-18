TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    khello.c


DEFINES += __KERNEL__
DEFINES += MODULE
INCLUDEPATH = /lib/modules/4.10.0-42-generic/build \
/lib/modules/4.10.0-42-generic/build/include \
/lib/modules/4.10.0-42-generic/build/arch/x86 \
/lib/modules/4.10.0-42-generic/build/arch/x86/include

DISTFILES += \
    Makefile
