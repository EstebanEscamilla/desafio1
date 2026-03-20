#ifndef PIEZAS_H
#define PIEZAS_H
#include <cstdint>

uint16_t GenerarPiezaAleatoria(int *dir_pieza_actual);

// Debajo de tu otra función
uint16_t ObtenerMascara(int id_pieza, int rotacion);

#endif // PIEZAS_H
