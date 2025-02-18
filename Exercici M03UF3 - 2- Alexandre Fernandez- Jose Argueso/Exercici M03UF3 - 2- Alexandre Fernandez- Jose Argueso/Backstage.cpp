#include "backstage.h"
#include <iostream>
#include <limits>

// Función para limpiar la pantalla
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Función para hacer una pausa
void pause() {
    std::cout << "Presione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Función para validar la entrada del usuario dentro de un rango
int getValidInput(int min, int max) {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail() || input < min || input > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Intente de nuevo: ";
        }
        else {
            break;
        }
    }
    return input;
}
