#include <iostream>
#include "validaciones.h"

using namespace std;

void VerificarDimensiones(int *ptr_ancho, int *ptr_alto){

    /*
    Recibe: 2 apuntadores que me van a definir las margenes de la matriz (Alto y ancho).
    Hace: Verificar que los altos y anchos sean correctos, es decir, validar que sean multiplos de 8.
    Retorna: Mensaje en consola confirmando dimensiones.
    */

    while (1) {
        if (*ptr_ancho >= 8 && *ptr_alto >= 8 && (*ptr_ancho % 8 == 0)){
            break;
        }
        else{
            // Se valida por debajo de 8, ya que el ancho debe de ser >= 8.
            if (*ptr_ancho < 8) {
                cout << "El ancho minimo debe ser de 8. Por favor ingrese nuevamente: "; cin >> *ptr_ancho;
            }
            // Se valida para el alto lo mismo que para el ancho, ya que debe ser >=8.
            else if (*ptr_alto < 8) {
                cout << "El alto minimo debe ser de 8. Por favor ingrese nuevamente: "; cin >> *ptr_alto;
            }
            // Se valida si se ingresa un NO multiplo de 8, ya que el ancho debe ser >= 8 y n veces 8.
            else if (*ptr_ancho % 8 != 0) {
                cout << "El ancho debe ser multiplo de 8. Por favor ingrese nuevamente: "; cin >> *ptr_ancho;
            }
        }
    }

    // Confirmamos que las dimensiones son correctas
    cout << "Dimensiones aceptadas!" << endl;
    cout << "El tablero se creara con: " << *ptr_ancho << " de ancho y " << *ptr_alto << " de alto." << endl;
}

char CapturarAccion(){
    char tecla_ingresada;
    // Se captura la tecla ingresada.

    cout << "\nAccion (A=Izq, D=Der, S=Bajar, W=Rotar, Q=Salir): ";
    cin >> tecla_ingresada;

    return tecla_ingresada;
}

void VerificarPiezas(){

}
