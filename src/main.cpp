#include <iostream>
#include <string>
#include <fstream> //Per cancellare il file all'inzio di ogni esecuzione
#include "Serra.h"
#include "Automatico.h"
#include "Manuale.h"
#include "Adattivo.h"
#include "UserInterface.h"

extern Serra serra;         //Dichiarato in UserInterface.cpp

void clearLog() {   //Fa il clear del file di log
    std::ofstream ofs("../log/logFile.txt", std::ios::out | std::ios::trunc);
}

int main() {
    clearLog();

    //Impianti sample per testing più veloce
    std::cout << "Impianti di sample per testing piu' veloce:" << std::endl;
    serra.AggiungiImpianto(new Automatico("Automatico1"));
    serra.AggiungiImpianto(new Manuale("Manuale1"));
    serra.AggiungiImpianto(new Adattivo("Adattivo1"));


    std::string command;
    std::cout << "\n==============================================\nScrivi 'help' per la lista dei comandi eseguibili \nAlcuni dei comandi hanno scritto {campo}, bisogna scrivere il valore del campo richiesto \n(es. 'set time 1:30' o 'set 2 on')\n==============================================\n"<< std::endl;
    while (true) {
        std::cout << "Scrivi un comando:";
        std::getline(std::cin, command);

        try {
            //processCommand di userInterface --> return false se si digita 'exit' e chiude il programma
            if (!processCommand(command)) {
                std::cout << "Chiusura del programma\n";
                break;
            }
        }
        catch (const std::invalid_argument &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
