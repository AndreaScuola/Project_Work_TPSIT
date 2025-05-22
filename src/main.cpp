#include <iostream>
#include "Serra.h"    //Collega il .cpp al .h
#include "Automatico.h"
#include "Manuale.h"
#include "Adattivo.h"
#include "UserInterface.h"
#include "UserInterface.cpp"
int main() {

    bool exit = true;
    std::string command;
    char c;
    Automatico* automatico = new Automatico("Impianto", 1, 20);
    automatico->SetAccensione(Time(1, 2));
    Manuale* manuale = new Manuale("Impianto1");
    manuale->SetAccensione(Time(1, 2));

    do {
        std::cout<<"Write a command"<<std::endl;
        std::cin>>command;
        try {
            processCommand(command);
        }
        catch (std::invalid_argument& e) {
            std::cout<<e.what()<<std::endl;
        }


        std::cout<<"Do you want to leave?"<<std::endl;
        std::cin>>c;
        if (c=='y'||c=='Y')
            exit=false;

    }while (exit);

    delete manuale;
    delete automatico;
    serra.AggiungiImpianto(automatico);  // <<< questa riga è fondamentale

    serra.AggiornaOrario(2, 0);
    serra.AggiornaOrario(4, 0);

    return 0;
}
