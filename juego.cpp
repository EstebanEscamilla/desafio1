#include <iostream>
#include "juego.h"
#include "piezas.h"
#include "tablero.h"
#include "validaciones.h"

using namespace std;

void IniciarJuego(uint8_t **tablero, int ancho, int alto){
    int PosX = 0, PosY = 0, Bandera_JuegoActivo = 1;
    int pieza_actual = 0 , *dir_pieza_actual = NULL; // Piezas
    uint16_t mascara_actual = 0; // Máscara de bits en cada turno
    char tecla;

    dir_pieza_actual = &pieza_actual;
    PosX = (ancho / 2) - 2;

    // Ahora generamos nuestra pieza de forma aleatoria (en su posición natural)
    mascara_actual = GenerarPiezaAleatoria(dir_pieza_actual);

    cout << "Comienza el Juego!" << endl;

    while(Bandera_JuegoActivo){

        // Imprimimos el tablero
        ImprimirTablero(tablero, ancho, alto);

        // Mensaje temporal para ver dónde está la pieza "invisible"
        cout << "Pieza actual ID: " << pieza_actual << " | Posicion: (" << PosX << ", " << PosY << ")" << endl;

        tecla = CapturarAccion();

        if (tecla == 'A' || tecla == 'a') {
            PosX--;
        }
        else if (tecla == 'D' || tecla == 'd') {
            PosX++;
        }
        else if (tecla == 'S' || tecla == 's') {
            PosY++;
        }
        else if (tecla == 'W' || tecla == 'w') {
            cout << "[Aviso] Funcion de rotar pendiente por conectar..." << endl;
        }
        else if (tecla == 'Q' || tecla == 'q') {
            Bandera_JuegoActivo = 0;
        }

        // (Aquí más adelante validaremos colisiones y si la pieza tocó fondo)
    }
}
