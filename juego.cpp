#include <iostream>
#include "juego.h"
#include "piezas.h"
#include "tablero.h"
#include "validaciones.h"

using namespace std;

void LimpiarLineas(uint8_t **tablero, int ancho, int alto) {

    /*
    Recibe: El tablero (Puntero a punteros), ancho y alto
    Hace:Recorre las filas de abajo hacia arriba. Si encuentra una fila donde todos los bits de
    todos los bytes son 1 (0xFF), la elimina: mueve los punteros de las filas superiores hacia
    abajo, limpia la memoria de la fila eliminada y la coloca como nueva fila superior.
    Retorna: El tablero sin filas llenas
    */

    //Calcular los bytes que ocupa cada fila.
    int BytesPorFila = ancho / 8;

    // Recorrer las filas desde la mas abajo a la mas arriba.
    for (int i = alto - 1; i >= 0; i--) {

        //Asumir que la fila esta llena.
        bool fila_llena = true;

        //Recorremos byte por fila.
        for (int j = 0; j < BytesPorFila; j++) {

            // Si ese byte esta lleno no esta lleno (0xFF) convertimos la variable fila_llena en false y rompemos.
            if (tablero[i][j] != 255) {
                fila_llena = false;
                break;
            }
        }

        // Evaluamos  si la fila esta llena se procede a eliminarla.
        if (fila_llena) {

            //guardamos el puntero de la fila que vamos a eliminar porque después
            //de mover las filas, ese puntero seguirá apuntando a la memoria de la fila original.
            //La usaremos como "cajón vacío" para la nueva fila superior.
            uint8_t *CajonVacio = tablero[i];

            //desplaza los punteros de las filas hacia abajo.
            for (int k = i; k > 0; k--) {
                tablero[k] = tablero[k - 1];
            }

            //limpia la memoria que antes era la fila eliminada, llenándola de ceros.
            for (int j = 0; j < BytesPorFila; j++) {
                CajonVacio[j] = 0;
            }

            //coloca ese bloque de memoria vacío en la posición superior (fila 0). Así, el tablero
            //sigue teniendo alto filas, pero ahora una fila vacía está arriba.
            tablero[0] = CajonVacio;

            // después de eliminar una fila, se incrementa i para que el bucle for
            //vuelva a examinar la misma posición esto permite verificar la nueva fila
            // que bajó, porque puede estar llena tambien.
            i++;

            //Mensaje de confirmacion.
            cout << "¡LINEA COMPLETADA Y LIMPIADA!" << endl;
        }
    }
}

void IniciarJuego(uint8_t **tablero, int ancho, int alto){

    /*
    Recibe:El tablero, el ancho y el alto.
    Hace:Maneja la entrada del usuario, actualiza la posición y rotación de la pieza,
    detecta colisiones, fija piezas, limpia filas y finaliza el juego (GAME OVER).
    Retorna: flujo infinito del juego hasta que tecla q se aprete o haya un game over
    */

    // Definicion de variables usadas durante el juego.
    int PosX = 0, PosY = 0, Bandera_JuegoActivo = 1;
    int pieza_actual = 0 , *dir_pieza_actual = NULL; // Piezas
    uint16_t mascara_actual = 0; // Máscara de bits en cada turno
    char tecla;
    int rotacion_actual = 0;

    //Establece el puntero para que generarpiezaaleatoria pueda modificar pieza_actual
    dir_pieza_actual = &pieza_actual;
    //Centra la pieza en la parte superior
    PosX = (ancho / 2) - 2;
    //Colocar la pieza 3 filas por arriba del tablero.
    PosY = -3;

    // Ahora generamos nuestra pieza de forma aleatoria (en su posición natural)
    mascara_actual = GenerarPiezaAleatoria(dir_pieza_actual);

    cout << "Comienza el Juego!" << endl;

    while(Bandera_JuegoActivo){

        // Imprimimos el tablero antes de que se ingrese la pieza.
        ImprimirTablero(tablero, ancho, alto, mascara_actual, PosX, PosY);

        // Capturamos la letra ingresada
        tecla = CapturarAccion();

        //Se guardan posibles nuevas posiciones, rotación y máscara, inicialmente iguales a las actuales.
        int NuevaPosX = PosX;
        int NuevaPosY = PosY;
        int NuevaRotacion = rotacion_actual;
        uint16_t NuevaMascara = mascara_actual;

        //Según la tecla, se modifican los valores temporales.
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

        // Si la tecla no es Q o q se verifica la colisión.
        if (tecla != 'q' && tecla != 'Q') {

            //Colision
            int choque = HayColision(tablero, ancho, alto, NuevaMascara, NuevaPosX, NuevaPosY);

            //Si no hay colision choque sera igual a 0
            if (choque == 0) {
                PosX = NuevaPosX;
                PosY = NuevaPosY;
                rotacion_actual = NuevaRotacion;
                mascara_actual = NuevaMascara;
            }
            else {
                // Si hay colision y la tecla era s es que ya no puede bajar mas.
                if (tecla == 's' || tecla == 'S') {

                    //Se funde la pieza en el tablero.
                    FundirPieza(tablero, mascara_actual, PosX, PosY);
                    //Se limpian las filas que apliquen.
                    LimpiarLineas(tablero, ancho, alto);
                    //La pieza se fijo cuando aun estaba parcialmnete afuera
                    if (PosY < 0) {

                        ImprimirTablero(tablero, ancho, alto, mascara_actual, PosX, PosY);

                        cout << "\n=======================================" << endl;
                        cout << "           G A M E   O V E R           " << endl;
                        cout << "         La torre llego al limite.       " << endl;
                        cout << "=======================================" << endl;

                        Bandera_JuegoActivo = 0; // Esto es para que se salga del while
                    }
                    //Si no se genera una nueva pieza en la parte superior
                    else {
                        PosX = (ancho / 2) - 2;
                        PosY = -3;
                        rotacion_actual = 0;
                        mascara_actual = GenerarPiezaAleatoria(dir_pieza_actual);

                    // El juego continua hasta que el jugador salga o termine el juego.
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
