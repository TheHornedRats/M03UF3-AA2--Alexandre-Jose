#include "menu.h"
#include "gameplay.h"
#include "scores.h"
#include "backstage.h"
#include <iostream>

void showMenu() {
    int option;
    do {
        std::cout << "\n--- Water Color Sort by Alexandre y Jose ---\n";
        std::cout << "1. Nueva partida\n";
        std::cout << "2. Ver puntuaciones\n";
        std::cout << "3. Salir\n";
        std::cout << "Seleccione una opción: ";
        option = getValidInput(1, 3);

        switch (option) {
        case 1:
            playGame();
            break;
        case 2:
            displayScores();
            break;
        case 3:
            std::cout << "Saliendo del juego...\n";
            break;
        default:
            std::cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (option != 3);
}