#include <ostream>
#include <sstream>
#include "UserInterface.h"
#include "Time.h"
#include "Impianto.h"
#include <iostream>

#define MIN_HOUR 0
#define MAX_HOUR 23
#define MIN_MINUTE 0
#define MAX_MINUTE 59


Time::Time(const std::string& strOra) {    //Costruttore: a partire da una stringa crea il Time
    auto pos = strOra.find(':');    //Trova la posizione dei ':'

    if (pos == std::string::npos) {
        logMessage(*this, "Formato non valido, deve essere h:mm o hh:mm", 1);
        hour = 0;
        minute = 0;
        return;
    }

    //Prende ora e minuti, poi fa i controlli che siano validi
    int h = std::stoi(strOra.substr(0, pos));
    int m = std::stoi(strOra.substr(pos + 1));

    if (h < 0 || h > 23 || m < 0 || m > 59) {
        logMessage(*this, "Errore nella creazione di Time: orario non valido", 1);
        hour = 0;
        minute = 0;
        return;
    }

    //Imposta l'ora scelta
    hour = h;
    minute = m;
}

void Time::Setter(int h, int m, std::vector<Impianto*>* impianti) { //Setter per l'ora
    if (h < MIN_HOUR || h > MAX_HOUR || m < MIN_MINUTE || m > MAX_MINUTE) {
        logMessage(*this, "Ora non valida", 1);
        return;
    }

    while (hour != h || minute != m) {
        (*this)++;  //Avanza di un minuto alla volta

        if (impianti != nullptr)
            for (Impianto* impianto : *impianti) {
                if (impianto != nullptr)
                    impianto->Avanza(*this); //Avanza è un metodo virtuale gestito in modo diverso in base alla classe figlio
            }
    }

    logMessage(*this, "Ora impostata raggiunta con successo", 0);
}


Time Time::operator++(int) {  //Operator per lo scorrere del tempo
    minute++;

    if (minute > MAX_MINUTE) {  //Controlla che min non sia >= 60
        minute = 0;
        hour++;

        if (hour > MAX_HOUR)    //Controlla che h non sia >= 24
            hour = 0;
    }

    return *this;
}

bool Time::operator==(const Time &other) const {    //Operator per il confronto tra orari
    return hour == other.hour && minute == other.minute;
}

std::ostream & operator<<(std::ostream &os, const Time &t) {    //Operator per la stampa di orari
    return os << t.GetTime();
}

std::string Time::GetTime() const { //Returna l'orario in formato hh:mm
    //Usa due cifre per hour e minute
    std::string hh = (hour < 10 ? "0" : "") + std::to_string(hour);
    std::string mm = (minute < 10 ? "0" : "") + std::to_string(minute);
    return hh + ":" + mm;
}

int Time::GetHour() const { //Returna le ore
    return hour;
}
int Time::GetMinute() const {   //Returna i minuti
    return minute;
}