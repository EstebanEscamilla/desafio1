#include <iostream>
#include "tablero.h"

using namespace std;

uint8_t **InicializarTablero(int ancho, int alto){
    int BytesPorFila = 0;
    uint8_t **NuevoTablero = NULL;

    BytesPorFila = ancho / 8;

    // Pedimos la memoria suficiente para el número de filas (alto)
    NuevoTablero = new uint8_t *[alto];

    // Ahora pasamos por cada fila pidiendo espacio para las columnas y así formar la matriz
    for(int i = 0; i < alto; i++){
        NuevoTablero[i] = new uint8_t [BytesPorFila];

        // Poner todo en cero (vacío y disponible)
        for(int j = 0; j < BytesPorFila; j++){
            NuevoTablero[i][j] = 0;
        }
    }

    return NuevoTablero;
}


void ImprimirTablero(uint8_t **tablero, int ancho, int alto){
    int BytesPorFila = 0;

    BytesPorFila = ancho / 8;

    cout << "\n--- TABLERO ACTUAL ---" << endl;

    // For para las columnas (de arriba hacia abajo)
    for(int i = 0; i < alto; i++){
        // For para las filas en bytes (de izquierda a derecha)
        for(int j = 0; j < BytesPorFila; j++){
            // Ahora tenemos que recorrer los bits de cada bloque (byte)
            // Empezamos en 7 porque empezamos en el más significativo (de izquierda a derecha)
            for (int bit = 7; bit >= 0; bit--){
                int ValorBit = (tablero [i][j] >> bit) & 1;

                if (ValorBit == 1){
                    cout << "# ";
                }
                else{
                    cout << ". ";
                }
            }
        }
        // Tenemos que saltar de línea cuando ya se terminó de leer todos los bytes
        cout << endl;
    }
    cout << "----------------------\n" << endl;
}


void LimpiarTablero(uint8_t **tablero, int alto){
    for(int i = 0; i < alto; i++){
        delete[] tablero[i];
    }

    delete[] tablero;

    cout << "Memoria del tablero liberada." << endl;
}
