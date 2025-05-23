#include <iostream>
#include <fstream> // per scrivere nel file
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Time.h"
#include "UserInterface.h"

#include "Serra.h"

void logMessage(const Time &time, const std::string &message, const int &errorLevel) {
    if (errorLevel == 0)
        std::cout << "[" << time << "]\t" << message << std::endl;
    else if (errorLevel == 1)
        std::cerr << "[" << time << "]\t" << message << std::endl;

    std::ofstream logFile("log.txt", std::ios::app);
    if (logFile)
        logFile << "[" << time << "]\t" << message << std::endl;
}


Serra serra;
std::vector<std::string> commandParser(const std::string &command) {
    std::vector<std::string> tokens;
    std::istringstream ss(command);
    std::string token;

    bool isDeviceName = false;
    std::string deviceName;

    while (ss >> token) {
        if (isDeviceName) {
            if (token == "on" || token == "off" || token.find(':') != std::string::npos) {
                if (!deviceName.empty()) {
                    tokens.push_back(deviceName);
                    deviceName.clear();
                }
                isDeviceName = false;
            }
        }

        if (token == "set" || token == "rm" || token == "show") {
            tokens.push_back(token);
            isDeviceName = true;
            continue;
        }

        if (isDeviceName) {
            if (!deviceName.empty()) {
                deviceName += " ";
            }
            deviceName += token;
        } else {
            tokens.push_back(token);
        }
    }

    if (!deviceName.empty()) {
        tokens.push_back(deviceName);
    }

    return tokens;
}


void processCommand(const std::string &command) {
    //Log sull'orario corrente
    logMessage(serra.getTime(), "L'orario attuale e' " + serra.getTime().GetTime(), 0);

    auto tokens = commandParser(command);
    if (tokens.empty())
        throw std::invalid_argument("Errore: comando vuoto.");

    const std::string &action = tokens[0];

    //----------- SET -----------
    if (action == "set") {
        if (tokens.size() < 2)
            throw std::invalid_argument("Errore: comando 'set' incompleto.");
        const std::string &target = tokens[1];

        //set time HH:MM
        if (target == "time") {
            if (tokens.size() != 3)
                throw std::invalid_argument("Errore: formato per 'set time' non valido. Usa: set time HH:MM");
            Time t(tokens[2]);
            serra.AggiornaOrario(t.GetHour(), t.GetMinute());
        }
        //set ID on  --> Per impianti manuali
        else if (tokens.size() == 3 && tokens[2] == "on") {
            int id = std::stoi(target);
            serra.AccendiImpiantoManuale(id);
        }
        //set ID off  --> Per impianti manuali
        else if (tokens.size() == 3 && tokens[2] == "off") {
            int id = std::stoi(target);
            serra.SpegniImpiantoManuale(id);
        }
        //set ID START STOP --> Per impianti automatici
        else if (tokens.size() == 4) {
            int id = std::stoi(target);
            Time start(tokens[2]);
            Time stop(tokens[3]);
            serra.SetTimer(id, start, stop);
        }
        //set ID START --> Per impianti manuali
        else if (tokens.size() == 3) {
            int id = std::stoi(target);
            Time start(tokens[2]);
            serra.SetTimer(id, start);
        }
        else {
            throw std::invalid_argument("Errore: formato comando 'set' non riconosciuto.");
        }
    }

    //----------- RM -----------   --> Reset del timer di un impianto
    else if (action == "rm") {
        if (tokens.size() != 2)
            throw std::invalid_argument("Errore: comando 'rm' non valido. Usa: rm ${ID}");
        int id = std::stoi(tokens[1]);
        serra.RemoveTimer(id);
    }

    //----------- SHOW -----------
    else if (action == "show") {
        if (tokens.size() == 1) {
            // Mostra tutti gli impianti con stato e consumo
            serra.StampaStato();
        } else if (tokens.size() == 2) {
            int id = std::stoi(tokens[1]);
            serra.StampaStato(id);
        } else {
            throw std::invalid_argument("Errore: comando 'show' non valido. Usa: show oppure show ${ID}");
        }
    }

    //----------- RESET -----------
    else if (action == "reset") {
        if (tokens.size() != 2)
            throw std::invalid_argument("Errore: comando 'reset' non valido.");
        const std::string &opt = tokens[1];
        if (opt == "time") {
            serra.ResetTime();
        } else if (opt == "timers") {
            serra.ResetTimers();
        } else if (opt == "all") {
            serra.ResetAll();
        } else {
            throw std::invalid_argument(
                "Errore: opzione 'reset' non valida. Usa: reset time | reset timers | reset all");
        }
    }

    else {
        throw std::invalid_argument("Errore: comando '" + action + "' non riconosciuto.");
    }
}
