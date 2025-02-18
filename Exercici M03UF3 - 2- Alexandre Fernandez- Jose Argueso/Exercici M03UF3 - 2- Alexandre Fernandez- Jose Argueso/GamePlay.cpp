#include "gameplay.h"
#include "bottles.h"
#include "scores.h"
#include "backstage.h"
#include <iostream>
#include <vector>

const int MAX_MOVES = 10;

// Función principal del juego
void playGame() {
    std::vector<std::vector<char>> bottles(NUM_BOTTLES);
    initializeBottles(bottles);

    int score = 0;
    int movesLeft = MAX_MOVES;
    std::string playerName;

    while (true) {
        clearScreen();
        printBottles(bottles);
        std::cout << "\nMovimientos restantes: " << movesLeft << "\nPuntuación: " << score << "\n";

        // Verificar condiciones de game over
        if (checkGameOver(bottles, movesLeft)) {
            std::cout << "¡Fin del juego! Ingresa tu nombre: ";
            std::cin >> playerName;
            saveScore(playerName, score);
            break;
        }

        // Obtener selección de botellas
        std::cout << "Selecciona la botella de origen (1-" << NUM_BOTTLES << "): ";
        int from = getValidInput(1, NUM_BOTTLES) - 1;

        std::cout << "Selecciona la botella de destino (1-" << NUM_BOTTLES << "): ";
        int to = getValidInput(1, NUM_BOTTLES) - 1;

        // Intentar mover líquido
        if (pourLiquid(bottles, from, to)) {
            movesLeft--;
            score += 3; // +3 puntos por movimiento
        }
    }
}

// Verifica si se ha alcanzado el estado de Game Over
bool checkGameOver(const std::vector<std::vector<char>>& bottles, int movesLeft) {
    if (movesLeft <= 0) {
        std::cout << "Se agotaron los movimientos.\n";
        return true;
    }

    bool allSameOrEmpty = true;
    for (const auto& bottle : bottles) {
        if (!bottle.empty()) {
            char firstLiquid = bottle[0];
            for (char liquid : bottle) {
                if (liquid != firstLiquid) {
                    allSameOrEmpty = false;
                    break;
                }
            }
        }
    }

    if (allSameOrEmpty) {
        std::cout << "¡Todas las botellas están organizadas correctamente!\n";
        return true;
    }
    return false;
}
