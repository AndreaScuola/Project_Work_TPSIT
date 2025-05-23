#include <iostream>
#include "Serra.h"    //Collega il .cpp al .h
#include "Automatico.h"
#include "Manuale.h"
#include "Adattivo.h"
#include "UserInterface.h"
#include "UserInterface.cpp"
int main() {

    bool continuare = true;
    std::string command;
    std::string c;
    Automatico* automatico = new Automatico("Impianto1");
    Manuale* manuale = new Manuale("Impianto2");
    Adattivo* adattivo = new Adattivo("Impianto3");

    serra.AggiungiImpianto(automatico);
    serra.AggiungiImpianto(manuale);
    serra.AggiungiImpianto(adattivo);

    std::cout << "COMANDI ESEGUIBILI: "
    "\n-set ${ID} on   //Solo per Manuali"
    "\n-set ${ID} off   //Solo per Manuali"
    "\n-set ${ID} ${START}   //Solo per Manuali"
    "\n-set ${ID} ${START} ${STOP}   //Solo per Automatici"
    "\n-rm ${ID}   //Setta i timer a [00:00]"
    "\n-show   //Stampa i dati di tutto"
    "\n-show {ID}   //Stampa i dati di un impianto"
    "\n-set time ${TIME}   //Imposta l'ora attuale a quella scelta"
    "\n-reset time   //Resetta l'ora della serra a [00:00]"
    "\n-reset timers   //Resetta i timer degli impianti a [00:00]"
    "\n-reset timers   //Resetta tutti i timer \n\n";


    //MODIFICARE I TIMER E I LORO RESET

    do {
        std::cout<<"Scrivi un comando: ";
        std::getline(std::cin,command);

        try {
            processCommand(command);
        }
        catch (std::invalid_argument& e) {
            std::cout<<e.what()<<std::endl;
        }


        std::cout<<"\nVuoi uscire? (Y/y):";
        std::getline(std::cin,c);

        if (c == "y" || c == "Y")
            continuare = false;

    }while (continuare);

    return 0;
}
