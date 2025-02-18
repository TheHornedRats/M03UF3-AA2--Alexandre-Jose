#include "bottles.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Genera las botellas con l�quidos aleatorios
void initializeBottles(std::vector<std::vector<char>>& bottles) {
    char liquids[] = { 'X', 'O', '#', 'S' };
    srand(time(0));  // Seed para aleatoriedad

    for (int i = 0; i < NUM_BOTTLES; ++i) {
        // Primer l�quido
        bottles[i].push_back(liquids[rand() % 4]);
        // Segundo l�quido
        bottles[i].push_back(liquids[rand() % 4]);
    }

    // Se seleccionan dos botellas aleatorias para agregar un tercer l�quido
    int extra1 = rand() % NUM_BOTTLES;
    int extra2;
    do {
        extra2 = rand() % NUM_BOTTLES;
    } while (extra2 == extra1);

    bottles[extra1].push_back(liquids[rand() % 4]);
    bottles[extra2].push_back(liquids[rand() % 4]);
}

// Imprime el estado de las botellas en pantalla
void printBottles(const std::vector<std::vector<char>>& bottles) {
    std::cout << "\nEstado actual de las botellas:\n";
    for (size_t i = 0; i < bottles.size(); ++i) {
        std::cout << "Botella " << i + 1 << ": ";
        for (char liquid : bottles[i]) {
            std::cout << liquid << " ";
        }
        std::cout << "\n";
    }
}

// Mueve l�quidos de una botella a otra sin restricciones de mezcla
bool pourLiquid(std::vector<std::vector<char>>& bottles, int from, int to) {
    // Validar si las botellas est�n dentro del rango permitido
    if (from < 0 || from >= NUM_BOTTLES || to < 0 || to >= NUM_BOTTLES) {
        std::cout << "Movimiento inv�lido: no hay ninguna botella en el rango.\n";
        return false;
    }

    // Validar que la botella origen no est� vac�a y la destino no est� llena
    if (bottles[from].empty()) {
        std::cout << "La botella " << from + 1 << " est� vac�a.\n";
        return false;
    }
    if (bottles[to].size() >= MAX_LIQUIDS) {
        std::cout << "La botella " << to + 1 << " ya est� llena.\n";
        return false;
    }

    // Obtener el l�quido a transferir
    char liquidToMove = bottles[from].back();

    // Realizar la transferencia (sin restricciones de mezcla)
    bottles[to].push_back(liquidToMove);
    bottles[from].pop_back();
    std::cout << "L�quido " << liquidToMove << " transferido de botella " << from + 1
        << " a botella " << to + 1 << ".\n";

    return true;
}
