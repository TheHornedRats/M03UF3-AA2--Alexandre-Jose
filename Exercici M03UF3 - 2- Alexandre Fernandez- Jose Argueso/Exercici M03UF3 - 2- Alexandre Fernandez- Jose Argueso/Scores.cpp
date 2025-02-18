#include "scores.h"
#include <iostream>
#include <fstream>
#include <vector>

const std::string SCORE_FILE = "scores.wcs";

// Guarda la puntuación en un archivo binario
void saveScore(const std::string& playerName, int score) {
    std::ofstream file(SCORE_FILE, std::ios::binary | std::ios::app);
    if (!file) {
        std::cerr << "Error al abrir el archivo de puntuaciones.\n";
        return;
    }

    size_t nameLength = playerName.size();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(playerName.c_str(), nameLength);
    file.write(reinterpret_cast<const char*>(&score), sizeof(score));
    file.close();
}

// Carga las puntuaciones desde el archivo binario
std::vector<std::pair<std::string, int>> loadScores() {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream file(SCORE_FILE, std::ios::binary);
    if (!file) {
        std::cerr << "No se encontraron puntuaciones guardadas.\n";
        return scores;
    }

    while (file.peek() != EOF) {
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

        std::string playerName(nameLength, ' ');
        file.read(&playerName[0], nameLength);

        int score;
        file.read(reinterpret_cast<char*>(&score), sizeof(score));

        scores.emplace_back(playerName, score);
    }

    file.close();
    return scores;
}

// Muestra las puntuaciones en pantalla
void displayScores() {
    std::vector<std::pair<std::string, int>> scores = loadScores();
    if (scores.empty()) {
        std::cout << "No hay puntuaciones registradas.\n";
        return;
    }

    std::cout << "\nHigh Scores:\n";
    for (const auto& entry : scores) {
        std::cout << "Jugador: " << entry.first << " - Puntuación: " << entry.second << "\n";
    }
}