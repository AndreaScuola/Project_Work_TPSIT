#include "Manuale.h"
#include <sstream>
#include "UserInterface.h" //Per logMessage

Manuale::Manuale(const std::string& n) : Impianto(n) {}

void Manuale::SetAccensione(const Time& t) {   //Imposta l'ora a cui accendere l'impianto (quella passata)
    std::ostringstream oss;

    if (acceso){
        //Se è già acceso dà errore
        oss << "Impianto manuale: " << Nome << " con ID: " << ID << " è già acceso";
        logMessage(t, oss.str(), 1);
        return;
    }

    tempoAccensione = t; //Imposta l'ora in cui dovrà accendersi
    oss << "Accensione dell'impianto manuale: " << Nome << " con ID: " << ID << " impostata alle " << tempoAccensione;
    logMessage(t, oss.str(), 0);
}

void Manuale::Avanza(const Time &now) { //Nella classe manuale ogni minuto bisogna controllare se è l'ora di accendere l'impianto (spegnimento gestito con comando)
    Accendi(now);
}


void Manuale::Accendi(const Time& now) {  //Compara l'orario della serra (quello passato) e controlla se accendere l'impianto
    if (tempoAccensione == now) {
        std::ostringstream oss;

        acceso = true;
        ultimaAccensione = now;
        oss << "Impianto manuale: " << Nome << " con ID: " << ID << " è stato acceso";
        logMessage(now, oss.str(), 0);
    }
}

void Manuale::Spegni(const Time& now) {   //Se da comando viene spento --> Spegne l'impianto
    std::ostringstream oss;

    if (!acceso) {  //Controlla che l'impianto non sia già spento
        oss << "Impianto manuale: " << Nome << " con ID: " << ID << " è già spento";
        logMessage(now, oss.str(), 1);
        return;
    }

    acceso = false;
    oss << "Impianto manuale: " << Nome << " con ID: " << ID << " è stato spento";
    logMessage(now, oss.str(), 0);
}

std::string Manuale::toString() const{
    std::ostringstream oss;
    oss << "Impianto manuale: " << Nome << ", ID: " << ID;

    if (acceso)
        oss << ", stato impianto: acceso";
    else
        oss << ", stato impianto: spento";

    return oss.str();
}
