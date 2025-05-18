#include "Automatico.h"
#include <sstream>
#include "UserInterface.h" //Per logMessage

Automatico::Automatico(const std::string& n, int oreAcceso, int minutiAcceso) : Impianto(n), oreAcceso(oreAcceso), minutiAcceso(minutiAcceso) {}

void Automatico::SetAccensione(const Time& t) {   //Imposta l'ora a cui accendere l'impianto (quella passata) e calcola l'ora di spegnimento
    std::ostringstream oss;

    if (acceso){
        //Se è già acceso dà errore
        oss << "Impianto automatico: " << Nome << " con ID: " << ID << " è già acceso" << std::endl;
        logMessage(t, oss.str(), 1);
        return;
    }

    tempoAccensione = t; //Imposta l'ora in cui dovrà accendersi
    //Calcola l'ora a cui dovrà spegnersi
    tempoSpegnimento = t;
    OraSpegnimento();   //Calcolo l'ora a cui si deve spegnere a partire da quella di accensione

    oss << "Accensione dell'impianto automatico: " << Nome << " con ID: " << ID << " impostata alle"/* <<AGGIUNGI STAMPA ORA << */ << std::endl;
    logMessage(t, oss.str(), 0);
}

void Automatico::Accendi(const Time& t) {   //Accende l'impianto se è l'ora di farlo, altrimenti non fa niente
    if (tempoAccensione == t) {
        std::ostringstream oss;

        acceso = true;
        ultimaAccensione = t;
        oss << "Impianto automatico: " << Nome << " con ID: " << ID << " è stato acceso" << std::endl;
        logMessage(t, oss.str(), 0);
    }
}

void Automatico::OraSpegnimento() {   //Calcola a partire dai parametri passati l'ora a cui l'impianto deve spegnersi
    for (int i = 0; i < minutiAcceso; i++)
        tempoSpegnimento++;

    for (int i = 0; i < oreAcceso; i++) //Aggiunge minuto per minuto un'ora per evitare eccezioni
        for (int j = 0; j < 60; j++)
            tempoSpegnimento++;
}

void Automatico::Spegni(const Time& t) {    //Se è arrivata l'ora di spegnersi si spegne, altrimenti non stampa nulla
    if (tempoSpegnimento == t) {
        std::ostringstream oss;

        if (!acceso) {  //Controlla che l'impianto non sia già spento
            oss << "Impianto automatico: " << Nome << " con ID: " << ID << " è già spento" << std::endl;
            logMessage(t, oss.str(), 1);
            return;
        }

        acceso = false;
        oss << "Impianto automatico: " << Nome << " con ID: " << ID << " è stato spento" << std::endl;
        logMessage(t, oss.str(), 0);
    }
}

//COMPLETARE CON STAMPA DELL'ORA (forse usare operator << di Time)
std::string Automatico::toString() const{
    std::ostringstream oss;
    oss << "Impianto automatico: " << Nome << ", ID: " << ID
    /*<< ", tempo accensione: " << AGGIUNGERE  << ", tempo spegnimento: " << AGGIUNGERE*/;

    if (acceso)
        oss << ", stato impianto: acceso" << std::endl;
    else
        oss << ", stato impianto: spento" << std::endl;

    return oss.str();
}
