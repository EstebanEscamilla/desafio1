#include <iostream>
#include <cstdint> // Esta es para los unitx_t
#include <ctime> // Para generar la semilla (Número aleatorio)

#include "validaciones.h" // Modulo para validar entradas
#include "piezas.h" // Modulo para generar piezas y sus máscaras

using namespace std;

int main(){
    int ancho = 0, alto = 0, *ptr_ancho = NULL, *ptr_alto = NULL;
    int pieza_actual = 0 , *dir_pieza_actual = NULL;
    uint16_t mascara_actual = 0;

    srand(time(NULL)); // Para generar una semilla con los segundos del reloj de la hora actual

    cout << "=== BIEVENIDO A TETRIS ===" << endl;

    cout << "Ingrese el ancho del tablero: "; cin >> ancho;
    cout << "Ingrese el alto del tablero: "; cin >> alto;

    //Asignamos todos los punteros a sus variables correspondientes
    ptr_ancho = &ancho; ptr_alto = &alto;
    dir_pieza_actual = &pieza_actual;

    // Verificamos que las dimensiones del tablero sean correctas
    VerificarDimensiones(ptr_ancho, ptr_alto);

    // Ahora generamos nuestra pieza de forma aleatoria (en su posición natural)
    mascara_actual = GenerarPiezaAleatoria(dir_pieza_actual);

    return 0;
}
