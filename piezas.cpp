#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

/*
    Hace: Se guarda la pieza bajo esta estructura las mascaras rotadas y sin rotación. Cada 4 bits representan
    cada fila y la concatenacion es la siguiente rotacion.
    */
uint16_t Piezas_Guardadas[7][4] = uint16_t Piezas_Guardadas[7][4] = {
    /*
    Hace: Se guarda la pieza bajo esta estructura las mascaras rotadas y sin rotación. Cada 4 bits representan
    cada fila y la concatenacion es la siguiente rotacion.
    */

    // 0: I (1x4)
    {0b0000111100000000,  // rotación 0: forma horizontal
     0b0010001000100010,  // rotación 90°
     0b0000000011110000,  // rotación 180°
     0b0100010001000100}, // rotación 270°
    // 1: O (2x2)
    {0b0000011001100000,
     0b0000011001100000,
     0b0000011001100000,
     0b0000011001100000},
    // 2: T
    {0b0000111001000000,
     0b0100110001000000,
     0b0100111000000000,
     0b0100011001000000},
    // 3: S
    {0b0000011011000000,
     0b1000110001000000,
     0b0000011011000000,
     0b1000110001000000},
    // 4: Z
    {0b0000110001100000,
     0b0100110010000000,
     0b0000110001100000,
     0b0100110010000000},
    // 5: J
    {0b0100010011000000,
     0b0000111000100000,
     0b0110010001000000,
     0b1000111000000000},
    // 6: L
    {0b0100010001100000,
     0b0010111000000000,
     0b1100010001000000,
     0b0000111010000000}
};


uint16_t GenerarPiezaAleatoria(int *dir_pieza_actual){
    /*
    Recibe: Un puntero que almacena la dirección de memoria de la variable donde se
            guardará el índice de la pieza elegida.
    Hace: Genera número aleatorio entre 0 y 6.
    Retorna: La máscara de bits (estado original, columna 0) correspondiente a
             la pieza aleatoria seleccionada desde la matriz Piezas_Guardadas
             en su posición inicial (sin rotar).
    */

    *dir_pieza_actual = rand() % 7;

    cout << *dir_pieza_actual;

    return Piezas_Guardadas[*dir_pieza_actual][0];
}


uint16_t ObtenerMascara(int id_pieza, int rotacion){
    // Retorna la máscara de la pieza pedida en la rotación pedida (0, 1, 2 o 3)
    return Piezas_Guardadas[id_pieza][rotacion];
}
