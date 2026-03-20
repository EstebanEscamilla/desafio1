#include <iostream>
#include <cstdint> // Esta es para los unitx_t
#include <ctime> // Para generar la semilla (Número aleatorio)
#include "validaciones.h" // Modulo para validar entradas
#include "piezas.h" // Modulo para generar piezas y sus máscaras
#include "tablero.h"
#include "juego.h"

using namespace std;

int main(){
    int ancho = 0, alto = 0, *ptr_ancho = NULL, *ptr_alto = NULL; // Dimensiones tablero
    uint8_t **tablero_juego = NULL; // para el tablero


    srand(time(NULL)); // Para generar una semilla con los segundos del reloj de la hora actual

    cout << "=== BIEVENIDO A TETRIS ===" << endl;

    cout << "Ingrese el ancho del tablero: "; cin >> ancho;
    cout << "Ingrese el alto del tablero: "; cin >> alto;

    //Asignamos todos los punteros a sus variables correspondientes
    ptr_ancho = &ancho; ptr_alto = &alto;

    // Verificamos que las dimensiones del tablero sean correctas
    VerificarDimensiones(ptr_ancho, ptr_alto);

    // Generamos el tablero con las dimensiones requeridas (se le pide al heap)
    tablero_juego = InicializarTablero(ancho, alto);

    // Entramos al loop infinito
    IniciarJuego(tablero_juego, ancho, alto);

    // Liberamos la memoria al terminar el juego
    LimpiarTablero(tablero_juego, alto);

    return 0;
}
