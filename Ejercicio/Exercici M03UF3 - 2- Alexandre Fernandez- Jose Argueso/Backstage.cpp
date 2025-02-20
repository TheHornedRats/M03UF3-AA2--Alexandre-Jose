#include "backstage.h"
#include <iostream>
#include <limits>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    std::cout << "Presione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    system("cls");

}

int getValidInput(int min, int max) {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail() || input < min || input > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida. Intente de nuevo: ";
        }
        else {
            break;
        }
    }
    return input;
}
