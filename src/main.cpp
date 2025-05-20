#include <iostream>
#include "Serra.h"    //Collega il .cpp al .h
#include "Automatico.h"
#include "Manuale.h"
#include "Adattivo.h"
#include "UserInterface.h"

int main() {
    Serra serra;
    bool exit = true;
    std::string command;
    char c;

    do {
        std::cout<<"Write a command"<<std::endl;
        std::cin>>command;
        //processCommand(command);

        std::cout<<"Do you want to leave?"<<std::endl;
        std::cin>>c;
        if (c=='y'||c=='Y')
            exit=false;

    }while (exit);

    Automatico* automatico = new Automatico("Impianto", 1, 20);
    automatico->SetAccensione(Time(1, 2));

    serra.AggiungiImpianto(automatico);  // <<< questa riga è fondamentale

    serra.AggiornaOrario(2, 0);
    serra.AggiornaOrario(4, 0);

    return 0;
}
