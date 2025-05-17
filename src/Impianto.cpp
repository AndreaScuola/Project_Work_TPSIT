#include "../include/Impianto.h"    //Collega il .cpp al .h

int Impianto::prossimoID = 1;


Impianto::Impianto(const std::string n) : ID(prossimoID++), Nome(n),
acceso(false), accensione(), ultimaAccensione(), tempoSpegni() {}