#include "Manuale.h"
#include <sstream>
#include "UserInterface.h" //Per logMessage

Manuale::Manuale(const std::string& n) : Impianto(n) {}

std::string Manuale::AccendiAdesso(const Time& now) {  //Accende l'impianto
    std::ostringstream oss;

    if (acceso) {
        oss << "L'impianto manuale con ID: '"<< ID << "' e' gia' acceso";
        return oss.str();
    }

    acceso = true;
    ultimaAccensione = now;
    oss << "L'impianto manuale con ID: '"<< ID << "' e' stato acceso con successo";
    return oss.str();
}

std::string Manuale::SetAccensione(const Time& t) {   //Imposta l'ora a cui accendere l'impianto (quella passata)
    std::ostringstream oss;

    if (acceso){
        //Se è già acceso dà errore
        oss << "Impianto manuale: '" << Nome << "' , ID: '" << ID << "' e' gia' acceso";
        return oss.str();
    }

    tempoAccensione = t; //Imposta l'ora in cui dovrà accendersi
    oss << "Accensione dell'impianto manuale: '" << Nome << "' con ID: '" << ID << "' impostata alle " << tempoAccensione;
    return oss.str();
}

void Manuale::Avanza(const Time &now) { //Nella classe manuale ogni minuto bisogna controllare se è l'ora di accendere l'impianto (spegnimento gestito con comando)
    Accendi(now);
}

void Manuale::Accendi(const Time& now) {  //Compara l'orario della serra (quello passato) e controlla se accendere l'impianto
    if (tempoAccensione == now) {
        std::ostringstream oss;

        if (acceso) {
            oss << "L'impianto manuale con ID: '" << ID << "' e' gia' acceso";
            logMessage(now, oss.str(), 1);
            return;
        }

        acceso = true;
        ultimaAccensione = now;
        oss << "Impianto manuale: '" << Nome << "', ID: '" << ID << "' e' stato acceso";
        logMessage(now, oss.str(), 0);
    }
}

void Manuale::Spegni(const Time& now) {   //Se da comando viene spento --> Spegne l'impianto
    std::ostringstream oss;

    if (!acceso) {  //Controlla che l'impianto non sia già spento
        oss << "Impianto manuale: '" << Nome << "', ID: '" << ID << "' e' già spento";
        logMessage(now, oss.str(), 1);
        return;
    }

    acceso = false;
    oss << "Impianto manuale: '" << Nome << "', ID: '" << ID << "' e' stato spento";
    logMessage(now, oss.str(), 0);
}

std::string Manuale::toString() const{
    std::ostringstream oss;
    oss << "Impianto manuale: '" << Nome << "', ID: " << ID;

    if (acceso)
        oss << ", acceso" << std::endl;
    else
        oss << ", spento" << std::endl;

    return oss.str();
}
