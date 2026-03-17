#ifndef TABLERO_H
#define TABLERO_H

#include <cstdint>

uint8_t **InicializarTablero(int ancho, int alto); // Se va a encargar de crear el tablero con las
                                                   // dimensiones requeridas pidiendo memoria al heap

void ImprimirTablero(uint8_t **tablero, int ancho, int alto); // Para dibujar el tablero (matriz)

void LimpiarTablero(uint8_t **tablero, int alto); // No necesitamos saber cuantos bloques de bytes hay
                                                  // porque vamos a borrar las filas, que a su vez, borran
                                                  // las columnas (arreglos con sus datos)

#endif // TABLERO_H
