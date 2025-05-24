#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <vector>
#include "Time.h"


void logMessage(const Time& time, const std::string& message, const int& errorLevel = 0);     //Logga un messaggio con un livello di errore (0 = std::cout, 1 = std::cerr)
std::vector<std::string> commandParser(const std::string& command);    //Parsea un comando in sottostringhe/token
bool processCommand(const std::string& command);    //Gestisce un comando testuale completo (verifica, parsing, azioni)

#endif //USERINTERFACE_H