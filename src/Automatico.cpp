#include "Automatico.h"
#include <sstream>
#include "UserInterface.h" //Per logMessage

Automatico::Automatico(const std::string& n) : Impianto(n) {}

std::string Automatico::SetAccensione(const Time& oraAccensione, const Time& oraSpegnimento) {   //Imposta l'ora a cui accendere e spegnere l'impianto
    std::ostringstream oss;

    if (acceso){
        //Se è già acceso dà errore
        oss << "Impianto automatico: '" << Nome << "', ID: '" << ID << "' e' gia' acceso";
        return oss.str();
    }

    //Imposta l'ora in cui dovrà accendersi e spegnersi
    tempoAccensione = oraAccensione;
    tempoSpegnimento = oraSpegnimento;

    oss << "Accensione dell'impianto automatico: '" << Nome << "', ID: '" << ID << "' impostata alle " << oraAccensione;
    return oss.str();
}

void Automatico::Avanza(const Time& now) {  //Ad ogni minuto controlla se deve accendere/spegnere l'impianto
    Accendi(now);
    Spegni(now);
}

void Automatico::Accendi(const Time& now) {   //Accende l'impianto se è l'ora di farlo, altrimenti non fa niente
    if (tempoAccensione == now) {
        std::ostringstream oss;

        acceso = true;
        ultimaAccensione = now;
        oss << "Impianto automatico: '" << Nome << "', ID: '" << ID << "' e' stato acceso e continuera' fino alle [" << tempoSpegnimento << "]";
        logMessage(now, oss.str(), 0);
    }
}

void Automatico::Spegni(const Time& now) {    //Se è arrivata l'ora di spegnersi si spegne, altrimenti non stampa nulla
    if (tempoSpegnimento == now) {
        std::ostringstream oss;

        if (!acceso) {  //Controlla che l'impianto non sia già spento
            oss << "Impianto automatico: '" << Nome << "', ID: '" << ID << "' e' gia' spento";
            logMessage(now, oss.str(), 1);
            return;
        }

        acceso = false;
        oss << "Impianto automatico: '" << Nome << "' con ID: '" << ID << "' e' stato spento";
        logMessage(now, oss.str(), 0);
    }
}

std::string Automatico::toString() const{
    std::ostringstream oss;
    oss << "Impianto automatico: '" << Nome << "', ID: '" << ID
    << "', tempo accensione: " << tempoAccensione  << ", tempo spegnimento: " << tempoSpegnimento;

    if (acceso)
        oss << ", acceso" << std::endl;
    else
        oss << ", spento" << std::endl;

    return oss.str();
}
