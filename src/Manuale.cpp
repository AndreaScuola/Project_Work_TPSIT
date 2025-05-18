#include "Manuale.h"
#include <sstream>
#include <../src/UserInterface.cpp> //per logMessage

Manuale::Manuale(const std::string& n) : Impianto(n) {}

//FINIRE STAMPA
void Manuale::SetAccensione(const Time& t) {   //Imposta l'ora a cui accendere l'impianto (quella passata)
    std::ostringstream oss;

    if (acceso){
        //Se è già acceso dà errore
        oss << "Impianto manuale: " << Nome << " con ID: " << ID << "è già acceso" << std::endl;
        logMessage(t, oss.str(), 1);
        return;
    }

    tempoAccensione = t; //Imposta l'ora in cui dovrà accendersi
    oss << "Accensione dell'impianto manuale: " << Nome << " con ID: " << ID << "impostata alle"/* <<AGGIUNGI STAMPA ORA << */ << std::endl;
    logMessage(t, oss.str(), 0);
}

void Manuale::Accendi(const Time& t) {  //Compara l'orario della serra (quello passato) e controlla se accendere l'impianto
    if (tempoAccensione == t) {
        std::ostringstream oss;

        acceso = true;
        ultimaAccensione = t;
        oss << "Impianto manuale: " << Nome << " con ID: " << ID << "è stato acceso" << std::endl;
        logMessage(t, oss.str(), 0);
    }
}

void Manuale::Spegni(const Time& t /*t-->Ora della serra*/) {   //Se da comando viene spento --> Spegne l'impianto
    std::ostringstream oss;

    if (!acceso) {  //Controlla che l'impianto non sia già spento
        oss << "Impianto manuale: " << Nome << " con ID: " << ID << "è già spento" << std::endl;
        logMessage(t, oss.str(), 1);
        return;
    }

    acceso = false;
    oss << "Impianto manuale: " << Nome << " con ID: " << ID << "è stato spento" << std::endl;
    logMessage(t, oss.str(), 0);
}

std::string Manuale::toString() const{
    std::ostringstream oss;
    oss << "Impianto manuale: " << Nome << ", ID: " << ID;

    if (acceso)
        oss << ", stato impianto: acceso" << std::endl;
    else
        oss << ", stato impianto: spento" << std::endl;

    return oss.str();
}
