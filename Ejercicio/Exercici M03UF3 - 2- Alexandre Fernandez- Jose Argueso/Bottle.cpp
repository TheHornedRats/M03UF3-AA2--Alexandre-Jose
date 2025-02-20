#include "bottles.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Backstage.h"

void initializeBottles(std::vector<std::vector<char>>& bottles) {
    char liquids[] = { 'X', 'O', '#', 'S' };
    srand(time(0));

    for (int i = 0; i < NUM_BOTTLES; ++i) {
        bottles[i].push_back(liquids[rand() % 4]);
        bottles[i].push_back(liquids[rand() % 4]);
    }

    int extra1 = rand() % NUM_BOTTLES;
    int extra2;
    do {
        extra2 = rand() % NUM_BOTTLES;
    } while (extra2 == extra1);

    bottles[extra1].push_back(liquids[rand() % 4]);
    bottles[extra2].push_back(liquids[rand() % 4]);
}

void printBottles(const std::vector<std::vector<char>>& bottles) {
    std::cout << "\n";

    for (size_t i = 0; i < bottles.size(); ++i) {
        std::cout << "  \\_/  ";
    }
    std::cout << "\n";

    for (int level = MAX_LIQUIDS - 1; level >= 0; --level) {
        for (size_t i = 0; i < bottles.size(); ++i) {
            if (bottles[i].size() > level) {
                std::cout << "  |" << bottles[i][level] << "|  ";
            }
            else {
                std::cout << "  | |  ";
            }
        }
        std::cout << "\n";
    }

    for (size_t i = 0; i < bottles.size(); ++i) {
        std::cout << "  ```  ";
    }
    std::cout << "\n";

    for (size_t i = 0; i < bottles.size(); ++i) {
        std::cout << "   " << i + 1 << "   ";
    }
    std::cout << "\n";
}

bool pourLiquid(std::vector<std::vector<char>>& bottles, int from, int to) {
    if (from < 0 || from >= NUM_BOTTLES || to < 0 || to >= NUM_BOTTLES) {
        std::cout << "Movimiento invalido: No hay ninguna botella en el rango.\n";
        std::cin.get();
        pause();
        return false;
    }

    if (bottles[from].empty()) {
        std::cout << "La botella " << from + 1 << " esta vacia.\n";
        std::cin.get();
        pause();
        return false;
    }

    char liquidToMove = bottles[from].back();
    int count = 1;

    for (int i = bottles[from].size() - 2; i >= 0; --i) {
        if (bottles[from][i] == liquidToMove) {
            count++;
        }
        else {
            break;
        }
    }

    if (bottles[to].size() + count > MAX_LIQUIDS) {
        std::cout << "No hay suficiente espacio en la botella " << to + 1
            << " para mover " << count << " liquidos.\n";
        pause();
        system("cls");
        return false;
    }

    for (int i = 0; i < count; ++i) {
        bottles[to].push_back(liquidToMove);
        bottles[from].pop_back();
    }

    std::cout << "Se han transferido " << count << " unidades de " << liquidToMove
        << " de la botella " << from + 1 << " a la botella " << to + 1 << ".\n";
    pause();

    system("cls");
    return true;
}

bool isBottleEmpty(const std::vector<char>& bottle) {
    return bottle.empty();
}

bool isBottleFull(const std::vector<char>& bottle) {
    return bottle.size() >= MAX_LIQUIDS;
}

std::vector<std::vector<char>> createBottles() {
    std::vector<std::vector<char>> bottles(NUM_BOTTLES);
    initializeBottles(bottles);
    return bottles;
}
