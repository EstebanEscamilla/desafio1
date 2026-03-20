TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        juego.cpp \
        main.cpp \
        piezas.cpp \
        tablero.cpp \
        validaciones.cpp

HEADERS += \
    juego.h \
    piezas.h \
    tablero.h \
    validaciones.h
