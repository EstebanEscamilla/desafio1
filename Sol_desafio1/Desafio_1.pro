TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        piezas.cpp \
        tablero.cpp \
        validaciones.cpp

HEADERS += \
    piezas.h \
    tablero.h \
    validaciones.h
