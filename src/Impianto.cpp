#include "Impianto.h"    //Collega il .cpp al .h
#include "UserInterface.h" //Per logMessage
#include "Time.h"

int Impianto::prossimoID = 1;

//Costruttore dell'impianto
Impianto::Impianto(const std::string& n) : ID(prossimoID++), Nome(n), acceso(false), ultimaAccensione() {}
