TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpmemobj

SOURCES += \
    btree.cpp \
    os_mmap.cpp

HEADERS += \
    ex_common.h
