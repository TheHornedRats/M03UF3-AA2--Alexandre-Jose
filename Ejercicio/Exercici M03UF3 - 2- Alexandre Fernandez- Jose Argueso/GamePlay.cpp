#include "gameplay.h"
#include "bottles.h"
#include "scores.h"
#include "backstage.h"
#include <iostream>
#include <vector>

const int MAX_MOVES = 10;

void playGame() {
    std::vector<std::vector<char>> bottles(NUM_BOTTLES);
    initializeBottles(bottles);

    int movesLeft = MAX_MOVES;
    std::string playerName;

    while (true) {
        printBottles(bottles);

        int score = calculateScore(bottles, movesLeft);
        std::cout << "\nMovimientos restantes: " << movesLeft << "\nPuntuacion: " << score << "\n";

        std::cout << "Selecciona la botella de origen (1-" << NUM_BOTTLES << ") o 0 para plantarte: ";
        int from = getValidInput(0, NUM_BOTTLES) - 1;
        if (from == -1) {
            std::cout << "Te has plantado. Fin del juego.\n";
            std::cout << "Ingresa tu nombre: ";
            std::cin >> playerName;
            saveScore(playerName, score);
            break;
        }

        std::cout << "Selecciona la botella de destino (1-" << NUM_BOTTLES << "): ";
        int to = getValidInput(1, NUM_BOTTLES) - 1;

        if (pourLiquid(bottles, from, to)) {
            movesLeft--;
        }

        if (checkGameOver(bottles, movesLeft)) {
            std::cout << "¡Fin del juego! Ingresa tu nombre: ";
            std::cin >> playerName;
            saveScore(playerName, score);
            break;
        }
    }
}

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
        std::cout << "¡Todas las botellas estan organizadas correctamente!\n";
        return true;
    }
    return false;
}
