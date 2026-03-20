#include <iostream>
#include "juego.h"
#include "piezas.h"
#include "tablero.h"
#include "validaciones.h"

using namespace std;

void LimpiarLineas(uint8_t **tablero, int ancho, int alto) {
    int BytesPorFila = ancho / 8;

    for (int i = alto - 1; i >= 0; i--) {

        bool fila_llena = true;

        for (int j = 0; j < BytesPorFila; j++) {

            if (tablero[i][j] != 255) {
                fila_llena = false;
                break;
            }
        }

        if (fila_llena) {

            uint8_t *CajonVacio = tablero[i];

            for (int k = i; k > 0; k--) {
                tablero[k] = tablero[k - 1];
            }

            for (int j = 0; j < BytesPorFila; j++) {
                CajonVacio[j] = 0;
            }

            tablero[0] = CajonVacio;
            i++;

            cout << "¡LINEA COMPLETADA Y LIMPIADA!" << endl;
        }
    }
}

void IniciarJuego(uint8_t **tablero, int ancho, int alto){
    int PosX = 0, PosY = 0, Bandera_JuegoActivo = 1;
    int pieza_actual = 0 , *dir_pieza_actual = NULL; // Piezas
    uint16_t mascara_actual = 0; // Máscara de bits en cada turno
    char tecla;
    int rotacion_actual = 0;

    dir_pieza_actual = &pieza_actual;
    PosX = (ancho / 2) - 2;
    PosY = -3;

    // Ahora generamos nuestra pieza de forma aleatoria (en su posición natural)
    mascara_actual = GenerarPiezaAleatoria(dir_pieza_actual);

    cout << "Comienza el Juego!" << endl;

    while(Bandera_JuegoActivo){

        // Imprimimos el tablero antes de que se ingrese la pieza
        ImprimirTablero(tablero, ancho, alto, mascara_actual, PosX, PosY);

        // Capturamos la letra ingresada
        tecla = CapturarAccion();

        int NuevaPosX = PosX;
        int NuevaPosY = PosY;
        int NuevaRotacion = rotacion_actual;
        uint16_t NuevaMascara = mascara_actual;

        if (tecla == 'a' || tecla == 'A') {
            NuevaPosX--;
        }
        else if (tecla == 'd' || tecla == 'D') {
            NuevaPosX++;
        }
        else if (tecla == 's' || tecla == 'S') {
            NuevaPosY++;
        }
        else if (tecla == 'w' || tecla == 'W') {
            NuevaRotacion = (rotacion_actual + 1) % 4;
            NuevaMascara = ObtenerMascara(pieza_actual, NuevaRotacion);
        }
        else if (tecla == 'q' || tecla == 'Q') {
            Bandera_JuegoActivo = 0;
        }

        if (tecla != 'q' && tecla != 'Q') {

            int choque = HayColision(tablero, ancho, alto, NuevaMascara, NuevaPosX, NuevaPosY);

            if (choque == 0) {
                PosX = NuevaPosX;
                PosY = NuevaPosY;
                rotacion_actual = NuevaRotacion;
                mascara_actual = NuevaMascara;
            }
            else {

                if (tecla == 's' || tecla == 'S') {

                    FundirPieza(tablero, mascara_actual, PosX, PosY);
                    LimpiarLineas(tablero, ancho, alto);
                    if (PosY < 0) {

                        ImprimirTablero(tablero, ancho, alto, mascara_actual, PosX, PosY);

                        cout << "\n=======================================" << endl;
                        cout << "           G A M E   O V E R           " << endl;
                        cout << "         La torre llego al limite.       " << endl;
                        cout << "=======================================" << endl;

                        Bandera_JuegoActivo = 0; // Esto es para que se salga del while
                    }
                    else {
                        PosX = (ancho / 2) - 2;
                        PosY = -3;
                        rotacion_actual = 0;
                        mascara_actual = GenerarPiezaAleatoria(dir_pieza_actual);
                    }
                }
            }
        }
    }
}


int HayColision(uint8_t **tablero, int ancho, int alto, uint16_t mascara, int NuevaPosX, int NuevaPosY) {

    for (int fila = 0; fila < 4; fila++) {
        for (int col = 0; col < 4; col++) {

            int bit_pieza = 15 - (fila * 4 + col);
            int valorPieza = (mascara >> bit_pieza) & 1;

            if (valorPieza == 1) {

                int absX = NuevaPosX + col;
                int absY = NuevaPosY + fila;

                if (absX < 0 || absX >= ancho || absY >= alto) {
                    return 1; //
                }

                if (absY >= 0) {
                    int ByteActual = absX / 8;
                    int BitActual = 7 - (absX % 8);

                    int valorFondo = (tablero[absY][ByteActual] >> BitActual) & 1;

                    if (valorFondo == 1) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}


void FundirPieza(uint8_t **tablero, uint16_t mascara, int PosX, int PosY) {

    for (int fila = 0; fila < 4; fila++) {
        for (int col = 0; col < 4; col++) {

            int bit_pieza = 15 - (fila * 4 + col);
            int valorPieza = (mascara >> bit_pieza) & 1;

            if (valorPieza == 1) {
                int absX = PosX + col;
                int absY = PosY + fila;

                if (absY >= 0) {
                    int ByteActual = absX / 8;
                    int BitActual = 7 - (absX % 8);

                    tablero[absY][ByteActual] |= (1 << BitActual);
                }
            }
        }
    }
}
