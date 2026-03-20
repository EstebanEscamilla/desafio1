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
    // de backend.
    return NuevoTablero;
}


void ImprimirTablero(uint8_t **tablero, int ancho, int alto, uint16_t mascara_actual, int PosX, int PosY){
    /*
    Recibe: El tablero directamnete desde el backend para procesarlo y dejarlo listo para imprimir.
    Tambien recibe el ancho y alto, para definir las dimensiones. y recibe parametros usados para usar
    los movimientos de la mascara y la posicion de la pieza.
    Hace: Recorre cada celda del tablero y dibuja la pieza sobre los espacios vacios o muestar los espacios
    vacios y adicionamete el fondo congelado
    Retorna: Retorna el tablero recorrido completo imprimiendo la ocupacion de cada celda, al no hacer ninguna
    modificacion a las estructuras de destos esta funcion pertenece al frontend.
    */

    // Inicializacion de variables usadas
    int BytesPorFila = 0;

    // Calcula cuántos bytes caben en una fila: cada byte representa 8 columnas.
    BytesPorFila = ancho / 8;

    //Titulo para inicio del tablero
    cout << "\n---- TABLERO ACTUAL ----" << endl;

    // For para recorrer las columnas (de arriba hacia abajo)
    for(int i = 0; i < alto; i++){

        // Itera sobre cada bytes de la fila actual (de izquierda a derecha)
        for(int j = 0; j < BytesPorFila; j++){

            // Recorrido por bits dentro de cada bytes desde el mas siginicativo al menos significativo
            for (int bit = 7; bit >= 0; bit--){

                // Se calcula la columna global desde 0 hasta ancho - 1.
                int X_tablero = (j*8) + (7-bit);

                // Se extrae el bit correpondiente del fondo y se desplaza el byte a la derecha bit
                //posiciones y se obtiene 1 o 0.
                int ValorBit = (tablero [i][j] >> bit) & 1;

                // Se inicializa esta variable encargada de dibujar (sobreescribiendo lo que haya en el fondo).
                int DibujarPieza = 0;

                // Verifica si la celda actual "cae" dentro del espacio 4x4 bits de la pieza.
                // Si no cae no hace nada (No tiene movimiento hacia abajo de castigo).
                if ((X_tablero >= PosX) && (X_tablero < PosX + 4) && (i >= PosY) && i < (PosY + 4)){

                    // Convierte de las coordenadas globales a reativas dentro de la matriz 4x4 bits
                    // de la pieza.
                    int Fila_pieza = i - PosY;
                    int Columna_pieza = X_tablero - PosX;

                    // Verificacion adicional de que pieza esta dentro de las filas correspondientes.
                    if(Fila_pieza >= 0 && Fila_pieza < 4) {

                        //Se calcula la posicion del bit dentro de la mascara.
                        int bit_pieza = 15 - (Fila_pieza * 4 + Columna_pieza);

                        //Se extare el bit de la pieza.
                        DibujarPieza = (mascara_actual >> bit_pieza) & 1;
                    }
                }

                // Usamos '@' para diferenciar la pieza que cae del fondo '#'.
                if (DibujarPieza == 1) {
                    cout << "@ ";
                }
                // Bloque de fondo congelado.
                else if (ValorBit == 1) {
                    cout << "# ";
                }
                // Espacio vacío
                else {
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
