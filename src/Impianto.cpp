#include "Impianto.h"    //Collega il .cpp al .h

int Impianto::prossimoID = 1;

//Costruttore dell'impianto
Impianto::Impianto(const std::string& n) : ID(prossimoID++), Nome(n), acceso(false), ultimaAccensione() {}
