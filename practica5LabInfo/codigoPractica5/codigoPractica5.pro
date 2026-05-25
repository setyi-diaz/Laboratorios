TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        caja.cpp \
        main.cpp \
        obstaculo.cpp \
        pared.cpp \
        particula.cpp

HEADERS += \
    caja.h \
    obstaculo.h \
    pared.h \
    particula.h
