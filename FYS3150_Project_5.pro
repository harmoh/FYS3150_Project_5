TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vec3.cpp \
    verlet.cpp \
    unitconverter.cpp

HEADERS += \
    vec3.h \
    verlet.h \
    unitconverter.h
