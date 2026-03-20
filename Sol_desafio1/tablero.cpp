#include <iostream>
#include "tablero.h"

using namespace std;

uint8_t **InicializarTablero(int ancho, int alto){
    /*
    Recibe: Recibe el ancho y el alto dados por el usuario
    Hace: Contruye un apuntador a apuntador que a su vez tiene dentro de sí 8 bits (uint8_t)
          y se recorre cada byte y se limpia la memoria y se ponen puros ceros
    Retorna: retorna el tablero con las dimensionens pedidas y limpio
    */
    int BytesPorFila = 0;
    uint8_t **NuevoTablero = NULL;

    BytesPorFila = ancho / 8;

    // Pedimos memoria (al heap) suficiente para el número de filas (alto)
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


void ImprimirTablero(uint8_t **tablero, int ancho, int alto, uint16_t mascara_actual, int PosX, int PosY){
    int BytesPorFila = 0, bit_pieza = 0;

    BytesPorFila = ancho / 8;

    cout << "\n--- TABLERO ACTUAL ---" << endl;

    // For para las columnas (de arriba hacia abajo)
    for(int i = 0; i < alto; i++){
        // For para las filas en bytes (de izquierda a derecha)
        for(int j = 0; j < BytesPorFila; j++){

            for (int bit = 7; bit >= 0; bit--){
                int X_tablero = (j*8) + (7-bit);
                int ValorBit = (tablero [i][j] >> bit) & 1;
                int DibujarPieza = 0; // Para dibujar la pieza en la pantalla

                if ((X_tablero >= PosX) && (X_tablero < PosX + 4) && (i >= PosY) && i < (PosY + 4)){

                    int Fila_pieza = i - PosY;
                    int Columna_pieza = X_tablero - PosX;

                    if(Fila_pieza >= 0 && Fila_pieza < 4) {
                        int bit_pieza = 15 - (Fila_pieza * 4 + Columna_pieza);
                        DibujarPieza = (mascara_actual >> bit_pieza) & 1;
                    }
                }

                if (DibujarPieza == 1) {
                    cout << "@ "; // Usamos '@' para diferenciar la pieza que cae del fondo '#'
                }
                else if (ValorBit == 1) {
                    cout << "# "; // Bloque de fondo congelado
                }
                else {
                    cout << ". "; // Espacio vacío
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
