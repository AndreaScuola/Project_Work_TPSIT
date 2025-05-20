#include <iostream>
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


void processCommand(const std::string &command, Time &now) {
    logMessage(now, "L'orario attuale è " + now.GetTime());
    std::vector<std::string> tokens = commandParser(command);

    if (tokens.empty()) {
        throw std::invalid_argument("Errore: comando vuoto.");
    }

    const std::string &action = tokens[0];

    if (action == "set") {
        if (tokens.size() < 2) {
            throw std::invalid_argument("Errore: comando 'set' incompleto.");
        }

        const std::string &deviceName = tokens[1];

        if (deviceName == "time") {
            if (tokens.size() != 3) {
                throw std::invalid_argument("Errore: formato per 'set time' non valido. Usa: set time HH:MM");
            }
            Time time{tokens[2]};
            //Metodo per settare il timer
            serra.AggiornaOrario(time.GetHour() ,time.GetMinute());
        } else {
            if (tokens.size() < 3) {
                throw std::invalid_argument("Errore: comando 'set' incompleto per dispositivo.");
            }

            const std::string &operation = tokens[2];

            if (operation == "on") {
                //metodo per accendere il dispositivo {deviceName};


            } else if (operation == "off") {
                //metodo per spegnere il dispositivo {deviceName};
                //serra.SpegniImpiantoManuale(tokens[3]);
            } else {
                Time start{operation};
                if (tokens.size() == 4) {
                    Time stop{tokens[3]};
                    //metodo per settare il timer {start} e {stop} per il dispositivo {deviceName};
                   /* for (auto it = serra.getImpianti().begin(); it != serra.getImpianti().end(); ++it) {
                        if ((*it)->GetID() == tokens[4]) {
                            (*it)->Spegni(stop);
                        }
                    }*/
                } else {
                    //metodo per settare il timer {start} per il dispositivo {deviceName};
                    /*for (auto it = serra.getImpianti().begin(); it != serra.getImpianti().end(); ++it) {
                        if ((*it)->GetID() == tokens[4]) {
                            (*it)->Accendi(start);
                        }
                    }*/
                }

            }
        }

    } else if (action == "rm") {
        if (tokens.size() != 2) {
            throw std::invalid_argument("Errore: comando 'rm' non valido. Usa: rm ${DEVICENAME}");
        }
        //metodo per rimuovere il timer
    } else if (action == "show") {
        if (tokens.size() == 1) {
        //metodo per mostrare tutti impianti
        } else if (tokens.size() == 2) {
            //metodo per mostrare impianto specifico
            /*for (auto it = serra.getImpianti().begin(); it != serra.getImpianti().end(); ++it) {
                       if ((*it)->GetID() == tokens[4]) {
                            //In base a come viene gesito il metodo toString da chi lo farà
                           (*it)->toString();
                       }
             }*/
        } else {
            throw std::invalid_argument("Errore: comando 'show' non valido. Usa: show oppure show ${DEVICENAME}");
        }

    } else if (action == "reset") {
        if (tokens.size() != 2) {
            throw std::invalid_argument("Errore: comando 'reset' non valido.");
        }

        const std::string &resetType = tokens[1];
        if (resetType == "time") {
            //metodo per resettare il tempo
            //manca il metodo per resettare il tempo a 0
        } else if (resetType == "timers") {
            //metodo per resettare i timer
            //stessa cosa
        } else if (resetType == "all") {
            //metodo per resettare tempo e timer
            //stessa cosa
        } else {
            throw std::invalid_argument(
                    "Errore: opzione 'reset' non valida. Usa: reset time | reset timers | reset all");
        }
    } else {
        throw std::invalid_argument("Errore: comando '" + action + "' non riconosciuto.");
    }
}