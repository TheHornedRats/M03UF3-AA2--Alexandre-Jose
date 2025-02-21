#include "gameplay.h"
#include "bottles.h"
#include "scores.h"
#include "backstage.h"
#include <iostream>
#include <vector>

//Creamos una variable constante porque no tenemos pensado cambiar el valor, esta variable ser� la que haga la cuenta de los movimientos restantes
const int MAX_MOVES = 10; 

//Funci�n que se activa cuando en el men� se escribe 1
void playGame() {
    //Creamos las variables donde guardaremos los vectores de las botellas
    std::vector<std::vector<char>> bottles(NUM_BOTTLES);
    //Llamamos a la funci�n de "initializeBottles" que se encarga de generar el contenido de las botellas, le mandamos el vector para que lo almacene ah�
    initializeBottles(bottles);
    
    //Creamos la variable que gestionara la cuenta atr�s de los movimientos disponibles
    int movesLeft = MAX_MOVES;

    //Creamos la variable que almacenar� el nombre de usuario una vez acabe el juego y guardarlo junto a la puntuaci�n
    std::string playerName;

    //Creamos una variable que gestione si se sigue ejecutando el bucle o no
    bool Programa = true;

    //En este bucle se executa el juego en s�.
    while (Programa) {

        //Llamamos a la funci�n de "printBottles" para mostrar las botellas
        printBottles(bottles);

        //Creamos una variable de puntuaci�n donde llamamos a "calculateScore ya que tiene toda la gesti�n de puntuaci�n
        int score = calculateScore(bottles, movesLeft);
        
        //Imprimimos la cantidad de movimientos restantes actuales y la puntuaci�n que tenemos
        std::cout << "\nMovimientos restantes: " << movesLeft << "\nPuntuacion: " << score << "\n";

        //Luego pedimos un input de la botella que quiere usar.
        std::cout << "Selecciona la botella de origen (1-" << NUM_BOTTLES << ") o 0 para plantarte: ";

        //Miramos si el numero �s valido y lo restamos 1 para hacer la comparaci�n que viene despu�s
        int from = getValidInput(0, NUM_BOTTLES) - 1;

        //Si escribimos 0 har� que se acabe el juego directamente
        if (from == -1) {
            std::cout << "Te has plantado. Fin del juego.\n";

            //Preguntas el nombre
            std::cout << "Ingresa tu nombre: ";

            //Guardas el nombre en la variable string anterior
            std::cin >> playerName;

            //Llamamos a la funci�n de "saveScore" y les mandamos en nombre que hemos insertado y la puntuaci�n que hemos conseguido antes de salir 
            saveScore(playerName, score);

            //Cerramos programa
            Programa = false;
        }

        //Luego del primer input el usuario escribe un segundo input para elegir la botella destino, donde acabar� el l�quido m�s arriba
        std::cout << "Selecciona la botella de destino (1-" << NUM_BOTTLES << "): ";

        //Validamos que entra en el rango que ponemos
        int to = getValidInput(1, NUM_BOTTLES) - 1;

        //Si podemos colocal el l�quido a la botella objetivo, se ejecuta esta condici�n
        if (pourLiquid(bottles, from, to)) {
            //Bajamos los movimientos restantes ya que se ha podido efectuar el movimiento
            movesLeft--;
        }

        //Esta condici�n sirve para comprobar si sa ha acabado la partida por falta de movimientos restantes o porque y est�n correctamente puestas las botellas
        if (checkGameOver(bottles, movesLeft)) {
            std::cout << "�Fin del juego! Ingresa tu nombre: ";

            //Al acabar le pide al usuario un nombre para guardarlo
            std::cin >> playerName;
            //Llamamos a la funci�n de "saveScore" donde le mandamos el nombre puesto anteriormente y la puntuaci�n que ha conseguido
            saveScore(playerName, score);
            //Cerramos el programa
            Programa = false;
        }
    }
}
//Esto es una funci�n donde se comprueba si la partida acaba o no, de parametros lleva las botellas para comprobar si est�n bien puestas y se lleva los movimientos restantes
bool checkGameOver(const std::vector<std::vector<char>>& bottles, int movesLeft) {
    //Si no quedan movimiento directamente sale un mensaje de derrota y se cierra el programa
    if (movesLeft <= 0) {
        std::cout << "Se agotaron los movimientos.\n";
        return true;
    }
    //Cremamos una variable de booleano para saber si todas las botellas est�n llenas con el mismo l�quido i/o est�n completamente vac�as
    bool allSameOrEmpty = true;
    //En este bucle for usamos el "const auto" para ejecutar el bucle las veces como tama�o del vector de botellas, evitando que cambie datos de este mismo
    for (const auto& bottle : bottles) {
        //Mientras las botella tenga algo se executa este codigo
        if (!bottle.empty()) {
            //Creamos la variable de firstLiquid para luego comprobar si se ha vaciado o no
            char firstLiquid = bottle[0];

            //Creamos un bucle donde se executara tantas veces como l�quidos contengan en la botella
            for (char liquid : bottle) {
                //Si siguen habiendo liquidos en la botella, la variable booleana ser� false y se cierra el bucle
                if (liquid != firstLiquid) {
                    allSameOrEmpty = false;
                    break;
                }
            }
        }
    }
    //Cuando se cumpla el booleano de que est�n bien puestos los l�quidos, ganaras la partida
    if (allSameOrEmpty) {
        std::cout << "�Todas las botellas estan organizadas correctamente!\n";
        return true;
    }
    return false;
}
