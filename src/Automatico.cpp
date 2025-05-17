#include "Automatico.h"
#include <sstream>

Automatico::Automatico(const std::string nome, int oreAcceso, int minutiAcceso) : Impianto(nome), tempoAcceso(oreAcceso, minutiAcceso) {}

//Accendi: imposta lo stato, registra orario e restituisce messaggio
std::string Automatico::Accendi(const Time t) {
  //RIGUARDA
    std::ostringstream oss;

    if (acceso)
    {
        oss << "L'impianto" << Nome << " è già acceso";
        return oss.str();
    }

    acceso = true;
    accensione = t;
    ultimaAccensione = t;
    oss << "Automatico '" << Nome << "' acceso alle " << t.GetTime();
    return oss.str();
}

//Spegni: calcola durata, aggiorna tempoAcceso, cambia stato e restituisce messaggio
std::string Automatico::Spegni(const Time t) {
    std::ostringstream oss;

    if (!acceso) {
        return "Impianto già spento alle " + t.GetTime();
    }
    acceso = false;
    oss <<  "L'impianto " << Nome << " si è spento";
}