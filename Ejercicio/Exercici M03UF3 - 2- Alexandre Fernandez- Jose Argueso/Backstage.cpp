#include "backstage.h"
#include <iostream>
#include <limits>
//Creamos la funci�n para limpiar pantalla cuando lo nombremos
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
//Creamos la funci�n de pausa para cuando lo nombremos
void pause() {
    //Le decimos al usuario que para continuar pulse "Enter" y cuando lo haga, limpiar� la pantalla
    std::cout << "Presione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    system("cls");

}
//Creamos la funci�n para comprobar si el input indicado �s valido
int getValidInput(int min, int max) {
    //Creamos la variable del input
    int input;
    //Creamos la variable para controlar cuando acabamos el siguiente bucle
    bool Programa = true;
    while (Programa) {
        //Pedimos el input y lo guardamos en "input"
        std::cin >> input;
        //Si el input puesto es mayor o menor al l�mite, se ejecuta este codigo
        if (std::cin.fail() || input < min || input > max) {
            //Limpiamos la pantalla y decimos que la entrada escrita no es valida
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Intente de nuevo: ";
        }
        //Si esta dentro del margen disponible, se cierra el bucle
        else {
            Programa = false;
        }
    }
    //Devolvemos el input
    return input;
}
