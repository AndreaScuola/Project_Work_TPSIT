#include <iostream>
#include <string>
#include "Serra.h"
#include "Automatico.h"
#include "Manuale.h"
#include "Adattivo.h"
#include "UserInterface.h"

extern Serra serra;         //dichiarato in UserInterface.cpp

int main() {

    serra.AggiungiImpianto(new Automatico("Impianto1"));
    serra.AggiungiImpianto(new Manuale("Impianto2"));
    serra.AggiungiImpianto(new Adattivo("Impianto3"));


    std::string command;
    std::cout << "Scrivi 'help' per la lista dei comandi eseguibili" << std::endl;
    while (true) {
        std::cout << "Scrivi un comando: ";
        std::getline(std::cin, command);

        try {
            //processCommand di userInterface --> return false se si digita 'exit' e chiude il programma
            if (!processCommand(command)) {
                std::cout << "Chiusura del programma.\n";
                break;
            }
        }
        catch (const std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
