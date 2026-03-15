#include <iostream>
#include "validaciones.h"

using namespace std;

void VerificarDimensiones(int *ptr_ancho, int *ptr_alto){

    while (1) {
        if (*ptr_ancho >= 8 && *ptr_alto >= 8 && (*ptr_ancho % 8 == 0)){
            break;
        }
        else{
            if (*ptr_ancho < 8) {
                cout << "El ancho minimo debe ser de 8. Por favor ingrese nuevamente: "; cin >> *ptr_ancho;
            }
            else if (*ptr_alto < 8) {
                cout << "El alto minimo debe ser de 8. Por favor ingrese nuevamente: "; cin >> *ptr_alto;
            }
            else if (*ptr_ancho % 8 != 0) {
                cout << "El ancho debe ser multiplo de 8. Por favor ingrese nuevamente: "; cin >> *ptr_ancho;
            }
        }
    }

    // Confirmamos que las dimensiones son correctas
    cout << "Dimensiones aceptadas!" << endl;
    cout << "El tablero se creara con: " << *ptr_ancho << " de ancho y " << *ptr_alto << " de alto." << endl;
}

void VerificarPiezas(){

}
