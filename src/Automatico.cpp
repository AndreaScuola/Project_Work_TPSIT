#include "Automatico.h"
#include <sstream>

// Costruttore: delega a Impianto e azzera il contatore del tempo acceso
Automatico::Automatico(const std::string& nome)
    : Impianto(nome)
    , tempoAcceso()    // inizializza a zero tramite default di Time
{}

// Accendi: imposta lo stato, registra orario e restituisce messaggio
std::string Automatico::Accendi(const Time& t) {
    if (acceso) {
        return "Impianto già acceso alle " + t.toString();
    }
    acceso = true;
    accensione = t;
    ultimaAccensione = t;
    std::ostringstream oss;
    oss << "Automatico \"" << Nome << "\" acceso alle " << t.toString();
    return oss.str();
}

// Spegni: calcola durata, aggiorna tempoAcceso, cambia stato e restituisce messaggio
std::string Automatico::Spegni(const Time& t) {
    if (!acceso) {
        return "Impianto già spento alle " + t.toString();
    }
    acceso = false;
    // supponiamo Time supporti operatore- e +=
    Time durata = t - accensione;
    tempoAcceso += durata;
    std::ostringstream oss;
    oss << "Automatico \"" << Nome
        << "\" spento alle " << t.toString()
        << " (durata sessione: " << durata.toString()
        << ", tempo totale acceso: " << tempoAcceso.toString() << ")";
    return oss.str();
}

Time Automatico::GetTempoAcceso() const {
    return tempoAcceso;
}