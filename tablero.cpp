#include <iostream>
#include "tablero.h"

using namespace std;

uint8_t **InicializarTablero(int ancho, int alto){
    /*
    Recibe: Recibe el ancho y el alto dados por el usuario los cuales son previamente validado
    en validaciones.
    Hace: Contruye un apuntador a apuntador que a su vez tiene dentro de sí 8 bits (uint8_t)
          y se recorre cada byte para limpiar la "basura" a la que inicialnnete apunta y la reemplaza con
          ceros logicos "0".
    Retorna: retorna el tablero con las dimensionens pedidas (n*8) relleno de ceros.
    */

    // Inicializacion de "BytesPorFila", alto de la matriz.
    int BytesPorFila = 0;

    //Inicializacion del puntero a punteros donde alojaremos la matriz que representara el tablero.
    uint8_t **NuevoTablero = NULL;

    // Calcula cuántos bytes caben en una fila: cada byte representa 8 columnas.
    BytesPorFila = ancho / 8;

    // Pedimos memoria (al heap) suficiente para el número de filas (alto).
    NuevoTablero = new uint8_t *[alto];

    // Ahora pasamos por cada fila pidiendo espacio para las columnas y así formar la matriz
    for(int i = 0; i < alto; i++){
        NuevoTablero[i] = new uint8_t [BytesPorFila];

        // Pasamos recorriendo cada columna y poniendo ceros, de esta manera "limpiamos" la matriz
        for(int j = 0; j < BytesPorFila; j++){
            NuevoTablero[i][j] = 0;
        }
    }

    // Devolvemos el tablero completlo con ceros en cada posicion para ser usado mas adelante por la capa
    // de frontend.
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
