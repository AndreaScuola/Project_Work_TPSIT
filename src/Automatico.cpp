#include "Automatico.h"
#include <sstream>
#include "UserInterface.h" //Per logMessage

Automatico::Automatico(const std::string& n, int oreAcceso, int minutiAcceso) : Impianto(n), oreAcceso(oreAcceso), minutiAcceso(minutiAcceso) {}

void Automatico::SetAccensione(const Time& t) {   //Imposta l'ora a cui accendere l'impianto (quella passata) e calcola l'ora di spegnimento
    std::ostringstream oss;

    if (acceso){
        //Se è già acceso dà errore
        oss << "Impianto automatico: " << Nome << " con ID: " << ID << " e' già acceso";
        logMessage(t, oss.str(), 1);
        return;
    }

    tempoAccensione = t; //Imposta l'ora in cui dovrà accendersi
    //Calcola l'ora a cui dovrà spegnersi
    tempoSpegnimento = t;
    OraSpegnimento();   //Calcolo l'ora a cui si deve spegnere a partire da quella di accensione

    oss << "Accensione dell'impianto automatico: " << Nome << " con ID: " << ID << " impostata alle " << t;
    logMessage(t, oss.str(), 0);
}

void Automatico::Avanza(const Time& now) {
    Accendi(now);
    Spegni(now);
}

void Automatico::Accendi(const Time& now) {   //Accende l'impianto se è l'ora di farlo, altrimenti non fa niente
    if (tempoAccensione == now) {
        std::ostringstream oss;

        acceso = true;
        ultimaAccensione = now;
        oss << "Impianto automatico: " << Nome << " con ID: " << ID << " e' stato acceso e continuera' fino alle [" << tempoSpegnimento << "]";
        logMessage(now, oss.str(), 0);
    }
}

void Automatico::OraSpegnimento() {   //Calcola a partire dai parametri passati l'ora a cui l'impianto deve spegnersi
    for (int i = 0; i < minutiAcceso; i++)
        tempoSpegnimento++;

    for (int i = 0; i < oreAcceso; i++) //Aggiunge minuto per minuto un'ora per evitare eccezioni
        for (int j = 0; j < 60; j++)
            tempoSpegnimento++;
}

void Automatico::Spegni(const Time& now) {    //Se è arrivata l'ora di spegnersi si spegne, altrimenti non stampa nulla
    if (tempoSpegnimento == now) {
        std::ostringstream oss;

        if (!acceso) {  //Controlla che l'impianto non sia già spento
            oss << "Impianto automatico: " << Nome << " con ID: " << ID << " e' già spento";
            logMessage(now, oss.str(), 1);
            return;
        }

        acceso = false;
        oss << "Impianto automatico: " << Nome << " con ID: " << ID << " e' stato spento";
        logMessage(now, oss.str(), 0);
    }
}

std::string Automatico::toString() const{
    std::ostringstream oss;
    oss << "Impianto automatico: " << Nome << ", ID: " << ID
    << ", tempo accensione: " << tempoAccensione  << ", tempo spegnimento: " << tempoSpegnimento;

    if (acceso)
        oss << ", stato impianto: acceso";
    else
        oss << ", stato impianto: spento";

    return oss.str();
}
