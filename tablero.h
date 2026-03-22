#ifndef TABLERO_H
#define TABLERO_H

#include <cstdint>

uint8_t **InicializarTablero(int ancho, int alto);
void ImprimirTablero(uint8_t **tablero, int ancho, int alto, uint16_t mascara_actual, int PosX, int PosY);
void LimpiarTablero(uint8_t **tablero, int alto);

#endif // TABLERO_H
