#include <iostream>
#include "validaciones.h"

using namespace std;

int main(){
    int ancho = 0, alto = 0, *ptr_ancho = NULL, *ptr_alto = NULL;

    cout << "=== BIEVENIDO A TETRIS ===" << endl;

    cout << "Ingrese el ancho del tablero: "; cin >> ancho;
    cout << "Ingrese el alto del tablero: "; cin >> alto;

    ptr_ancho = &ancho; ptr_alto = &alto;

    // Verificamos que las dimensiones del tablero sean correctas
    VerificarDimensiones(ptr_ancho, ptr_alto);

    // Una vez se genere la pieza debemos verificar que sea una de las permitidas


    return 0;
}
