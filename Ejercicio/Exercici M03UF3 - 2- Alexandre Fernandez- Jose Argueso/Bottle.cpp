#include "bottles.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Backstage.h"
//Esta función crea las botellas con líquidos aleatorios 
void initializeBottles(std::vector<std::vector<char>>& bottles) {
    //Creamos una array con todos los tipos de líquidos que pueden haber en una botella
    char liquids[] = { 'X', 'O', '#', 'S' };

    //Creamos una "seed" para poder generar numeros aleatorios
    srand(time(0));

    //En este bucle insertamos valores de la array de liquidos de manera aleatoria y solo 2 a cada botella
    for (int i = 0; i < NUM_BOTTLES; ++i) {
        bottles[i].push_back(liquids[rand() % 4]);
        bottles[i].push_back(liquids[rand() % 4]);
    }

    //Creamos dos variable para hacer que dos de las 6 botellas tengan 3 líquidos en vez de 2
    int extra1 = rand() % NUM_BOTTLES;
    int extra2;

    //Creamos un bucle para añadir a la segunda botella el tercer liquido
    do {
        extra2 = rand() % NUM_BOTTLES;
    } while (extra2 == extra1);

    //Finalmente agregamos los nuevos cambios al vector
    bottles[extra1].push_back(liquids[rand() % 4]);
    bottles[extra2].push_back(liquids[rand() % 4]);
}

//Esta función imprime todas las posiciones para que quede como 6 botellas con su contenido
void printBottles(const std::vector<std::vector<char>>& bottles) {
    std::cout << "\n";

   //Este bucle sirve para hacer el "tapón" de la botella
    for (size_t i = 0; i < bottles.size(); ++i) {
        std::cout << "  \\_/  ";
    }
    std::cout << "\n";
    //En esta variable se pone los valores de cada botella y su separación con "|" para que parezca que són botellas
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
    //Este bucle és para hacer la parte de abajo de la botella
    for (size_t i = 0; i < bottles.size(); ++i) {
        std::cout << "  ```  ";
    }
    std::cout << "\n";

    //Este bucle es para separar las botellas
    for (size_t i = 0; i < bottles.size(); ++i) {
        std::cout << "   " << i + 1 << "   ";
    }
    std::cout << "\n";
}
//Esta función verifica si se puede poner el líquido a la botella destino
bool pourLiquid(std::vector<std::vector<char>>& bottles, int from, int to) {
    //Esta condición se activa si no es valido el movimiento
    if (from < 0 || from >= NUM_BOTTLES || to < 0 || to >= NUM_BOTTLES) {
        std::cout << "Movimiento invalido: No hay ninguna botella en el rango.\n";
        std::cin.get();
        pause();
        return false;
    }
    //Esta condición se aplica cuando puedas poner el líquido en la botella destino
    if (bottles[from].empty()) {
        std::cout << "La botella " << from + 1 << " esta vacia.\n";
        std::cin.get();
        pause();
        return false;
    }

    //Creamos una variable que guardará el valor más arriba del todo que en teoria és el que se moverá de botella
    char liquidToMove = bottles[from].back();
   //Creamos un contador
    int count = 1;

    //Este bucle comprueba si el líquido cabe en la botella
    for (int i = bottles[from].size() - 2; i >= 0; --i) {
        if (bottles[from][i] == liquidToMove) {
            //si cabe aumenta el tamaño de la botella
            count++;
        }
        else {
            break;
        }
    }
    //Esta condición se activa si no hay espacio en la botella
    if (bottles[to].size() + count > MAX_LIQUIDS) {
        std::cout << "No hay suficiente espacio en la botella " << to + 1
            << " para mover " << count << " liquidos.\n";
        //Llamamos a la función de "pause" y pausamos para que sepa el usuario que no puede
        pause();
        //Luego limpiamos la pantalla
        system("cls");
        return false;
    }
    //En este bucle hacemos la acción de mover un líquido de un lado a otro
    for (int i = 0; i < count; ++i) {
        bottles[to].push_back(liquidToMove);
        bottles[from].pop_back();
    }
    //Avisamos de que se ha podido mover
    std::cout << "Se han transferido " << count << " unidades de " << liquidToMove
        << " de la botella " << from + 1 << " a la botella " << to + 1 << ".\n";
    //Pausamos para que lo pueda ver
    pause();
    //Y limpiamos la pantalla
    system("cls");
    return true;
}
//Esta función comprueba si la botella está vacía
bool isBottleEmpty(const std::vector<char>& bottle) {
    return bottle.empty();
}
//Esta función comprueba si la botella está llena
bool isBottleFull(const std::vector<char>& bottle) {
    return bottle.size() >= MAX_LIQUIDS;
}
//Esta función crea los vectores de botellas
std::vector<std::vector<char>> createBottles() {
    std::vector<std::vector<char>> bottles(NUM_BOTTLES);
    initializeBottles(bottles);
    return bottles;
}
