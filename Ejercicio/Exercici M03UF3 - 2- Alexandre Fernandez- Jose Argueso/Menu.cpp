#include "menu.h"
#include "gameplay.h"
#include "scores.h"
#include "backstage.h"
#include <iostream>

void showMenu() {
    //Creo una variable para que seleccionar opciones
    int option;

    //Creamos un bucle do while porque la primera vez siempre queremos que se ejecute
    do { 
        std::cout << "\n--- Hola Profe, apruebanos ---\n";
        std::cout << "1. Nueva partida\n";
        std::cout << "2. Ver puntuaciones\n";
        std::cout << "3. Salir\n";
        std::cout << "Seleccione una opcion: ";
        
        //Pedimos input y hacemos una validación de entre 1 y 3
        option = getValidInput(1, 3); 

        //Dependiendo de lo que salga el input del usuario hacemos las siguientes cosas:
        switch (option) {
        case 1:
            //Si escribe "1" significa que quiere comenzar una partida y se ejecuta la función "playGame"
            playGame();
            break;
        case 2:
            //Si escribe "2" significa que quiere ver las puntuaciones, asi que llamamos a la función de "displayScores"
            displayScores(); 
            break;
        case 3:
            //Y si escribe "3" significa que quiere cerrar el juego, asi que mandamos un mensaje de que salimos del juego
            std::cout << "Saliendo del juego...\n"; 
            break;
        default:
            //Si no se activa ninguno de los casos, salta un mensaje de error
            std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
        //Cuando la opción escrita sea "3" este bucle terminará y se acabará el programa
    } while (option != 3); 
}