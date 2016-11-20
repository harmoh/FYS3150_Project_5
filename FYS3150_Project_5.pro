TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vec3.cpp \
    verlet.cpp \
    unitconverter.cpp \
    system.cpp \
    particle.cpp \
    lennardjones.cpp \
    io.cpp \
    statisticssampler.cpp

HEADERS += \
    vec3.h \
    random.h \
    verlet.h \
    unitconverter.h \
    system.h \
    particle.h \
    lennardjones.h \
    io.h \
    statisticssampler.h
