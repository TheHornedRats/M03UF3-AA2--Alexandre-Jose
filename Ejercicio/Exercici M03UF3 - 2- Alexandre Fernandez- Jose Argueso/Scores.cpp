#include "scores.h"
#include <iostream>
#include <fstream>
#include <vector>

//Creamos la variable que contendr� el nombre del archivo de guardado
const std::string SCORE_FILE = "scores.wcs";

//Esta funci�n �s para guardar la puntuaci�n y el nombre del usuario
void saveScore(const std::string& playerName, int score) {
    //Creamos el vector de la tabla de puntuaciones
    std::vector<std::pair<std::string, int>> scores = loadScores();

    //Creamos una variable para ver si hemos encontrado el archivo
    bool found = false;

    //Este bucle se executa la misma cantidad de veces como puntuaciones incluidos en este archivo
    for (auto& entry : scores) {
        //Esta condici�n se efectuar� cuando insertes el nombre de usuario
        if (entry.first == playerName) {
            //Si la puntuaci�n �s mayor a la que hizo anteriormente, se va a sobrescribir con el que ya estaba
            if (score > entry.second) {
                //Cambia la puntuaci�n por la nueva ya que �s mejor
                entry.second = score;
                std::cout << "Nueva puntuacion guardada para " << playerName << ".\n";
            }
            //si la puntuaci�n �s peor, simplemente la consola dir� que has hehco menos puntos y que no se va a guardar
            else {
                std::cout << "La nueva puntuacion es menor. No se actualizara.\n";
            }
            //Se ha completado el bucle, entonces significa que la variable es true
            found = true;
            break;
        }
    }
    //Si no se encuentra, se ejecuta esta condicion
    if (!found) {
        scores.emplace_back(playerName, score);
    }
    //Creamos la variable para leer archivos binarios
    std::ofstream file(SCORE_FILE, std::ios::binary | std::ios::trunc);
    //Si no consigues abrir el archivo para leer las puntuaciones, se ejecuta esta condicion
    if (!file) {
        std::cerr << "Error al abrir el archivo de puntuaciones.\n";
        return;
    }
    //Creamos un bucle for que se repite por cada usuario con puntuaci�n puesta en el archivo
    for (const auto& entry : scores) {
        size_t nameLength = entry.first.size();
        //Escribimos el nuevo usuario i/o la nueva puntuaci�n
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(entry.first.c_str(), nameLength);
        file.write(reinterpret_cast<const char*>(&entry.second), sizeof(entry.second));
    }
    //Cerramos el archivo de lectura
    file.close();
}
//Creamos el vector para comprobar si hay puntuaciones guardadas
std::vector<std::pair<std::string, int>> loadScores() {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream file(SCORE_FILE, std::ios::binary);
    //Si la variable que lee archivos falla, se ejecuta este programa
    if (!file) {
        std::cerr << "No se encontraron puntuaciones guardadas.\n";
        return scores;
    }

    while (file.peek() != EOF) {
        //Leemos cada uno de las puntuaciones en binario para mostrarlo como nombre de usuario y puntuaci�n
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

        std::string playerName(nameLength, ' ');
        file.read(&playerName[0], nameLength);

        int score;
        file.read(reinterpret_cast<char*>(&score), sizeof(score));

        scores.emplace_back(playerName, score);
    }
    //Cerramos el archivo de lectura
    file.close();
    return scores;
}
//Esta funci�n permite mostrar por consola la tabla de puntuaciones
void displayScores() {
    //Creamos el vector para tratar con �l a la hora de mostrar por pantalla las puntuaciones
    std::vector<std::pair<std::string, int>> scores = loadScores();
    //Si no hay puntuaciones registradas, se ejecuta esta condici�n
    if (scores.empty()) {
        std::cout << "No hay puntuaciones registradas.\n";
        return;
    }
    //Si la condici�n de arriba no se ejecuta, significa que por lo menos hay una puntuaci�n, con lo cual creamos un bucle que se repite tantas veces como puntuaciones haya en la tabla
    //y mostramos por pantalla las puntuaciones
    std::cout << "\nHigh Scores:\n";
    for (const auto& entry : scores) {
        std::cout << "Jugador: " << entry.first << " - Puntuacion: " << entry.second << "\n";
    }
}
//Funcion para calcular la puntuacion del jugador actual
int calculateScore(const std::vector<std::vector<char>>& bottles, int movesLeft) {
    //Empezamos creando una variable para contar y que empiece en 0
    int score = 0;
    //Este bucle se ejecuta tantas veces como botellas hayan en el juego
    for (const auto& bottle : bottles) {
        //Cuando una botella se encuentra vac�a, directamente se lleva 50 puntos el jugador
        if (bottle.empty()) {
            score += 50;
        }
        //Si no est� vac�a se empieza a comprobar si la botella est� llena
        else {
            //Creamos la variable para decir si la botella est� llena
            bool isFull = true;
            char firstLiquid = bottle[0];
            //Creamos un bucle que se repite tantas veces como huecos en la botella ya sean llenos o vac�os
            for (char liquid : bottle) {
                //Si en cualquier momento no se encuentra un l�quido, significa que no est� lleno
                if (liquid != firstLiquid) {
                    isFull = false;
                    break;
                }
            }
            //Si la comprovaci�n de antes no se ejecuta en ningun momento, significa que la botella est� llena
            if (isFull) {
                score += 30;
            }
        }
    }
    //Por cada movimiento restante que ha sobrado al terminar, otrorgar� 3 puntos
    score += movesLeft * 3;
    //Una vez acabamos, mandamos la puntuaci�n final
    return score;
}


