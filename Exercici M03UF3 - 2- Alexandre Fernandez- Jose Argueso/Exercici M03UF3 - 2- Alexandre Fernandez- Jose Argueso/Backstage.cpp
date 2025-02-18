#include "backstage.h"
#include <iostream>
#include <limits>

// Funci�n para limpiar la pantalla
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Funci�n para hacer una pausa
void pause() {
    std::cout << "Presione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Funci�n para validar la entrada del usuario dentro de un rango
int getValidInput(int min, int max) {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail() || input < min || input > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inv�lida. Intente de nuevo: ";
        }
        else {
            break;
        }
    }
    return input;
}
