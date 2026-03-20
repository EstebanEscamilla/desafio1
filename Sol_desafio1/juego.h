#ifndef JUEGO_H
#define JUEGO_H

#include <cstdint>

void IniciarJuego(uint8_t **tablero, int ancho, int alto);

void FundirPieza(uint8_t **tablero, uint16_t mascara, int PosX, int PosY);

int HayColision(uint8_t **tablero, int ancho, int alto, uint16_t mascara, int NuevaPosX, int NuevaPosY);

void LimpiarLineas(uint8_t **tablero, int ancho, int alto);

#endif // JUEGO_H
