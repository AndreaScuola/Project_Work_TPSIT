#include "Adattivo.h"
#include "UserInterface.h"

//Librerie per il random
#include <random>    //Per std::mt19937, std::random_device, std::uniform_real_distribution
#include <sstream>   //Per std::ostringstream

Adattivo::Adattivo(const std::string& n) : Impianto(n), temperatura(28), minutiAcceso(0) {}
Adattivo::Adattivo(const std::string& n, float temperaturaIniziale) : Impianto(n), temperatura(temperaturaIniziale), minutiAcceso(0) {}

void Adattivo::gestioneAdattivo(const Time& t) {
    if (acceso) {   //Se è acceso --> ogni ora +(0.75-1) --> se temp >= 28 --> Spegni
        minutiAcceso++;

        if (minutiAcceso == 60) {   //Aumento di temperatura ogni ora
            minutiAcceso = 0;
            temperatura += randomFloat(0.75f, 1.0f);
            Spegni(t);  //Verifica se è neccessario spegnere l'impianto in base alla temperatura
        }
    }
    else {  //Se è spento --> ogni ora -(0.01-0.05) --> se temp < 25 --> Accendi
        temperatura -= randomFloat(0.01f, 0.05f);   //Ogni minuto sottrae un valore random
        Accendi(t); //Verifica se è neccessaria l'accensione dell'impianto in base alla temperatura
    }
}

float Adattivo::randomFloat(float min, float max) { //Random
    //Inizializza una volta solo grazie allo staic
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

void Adattivo::Avanza(const Time &now) {
    gestioneAdattivo(now);  //Ad ogni minuto viene chiamato gestione adattivo --> Aumento/diminuzione temperatura e accensione/spegnimento impianto
}


void Adattivo::Accendi(const Time& now) {   //Accende l'impianto se la temperatura cala sotto una certa soglia
    if (temperatura < 25.0f && !acceso) {
        acceso = true;

        //Stampo il messaggio per l'accensione
        std::ostringstream oss;
        oss << "Impianto adattivo: '" << Nome << "', ID: '" << ID << "' si e' acceso, temperatura: " << temperatura << "C";
        logMessage(now, oss.str(), 0);
    }
}

void Adattivo::Spegni(const Time& now) { //Spegne l'impianto se la temperatura supera una certa soglia
    if (temperatura > 28.0f && acceso) {
        acceso = false;

        //Stampo il messaggio per lo spegnimento
        std::ostringstream oss;
        oss << "Impianto adattivo: '" << Nome << "', ID: '" << ID << "' si e' spento, temperatura: " << temperatura << "C";
        logMessage(now, oss.str(), 0);
    }
}

std::string Adattivo::toString() const{ //Returna tutte le informazioni dell'impianto
    std::ostringstream oss;
    oss << "Impianto adattivo: '" << Nome << "', ID: '" << ID << "', temperatura: " << temperatura;

    if (acceso)
        oss << "C, acceso" << std::endl;
    else
        oss << "C, spento" << std::endl;

    return oss.str();
}
