#include <ostream>
#include <sstream>
#include "UserInterface.h"
#include "Time.h"
#include "Impianto.h"

#define MIN_HOUR 0
#define MAX_HOUR 23
#define MIN_MINUTE 0
#define MAX_MINUTE 59

#include "Time.h"
#include <iostream>

Time::Time(std::string strOra) {    //Costruttore: a partire da una stringa crea il Time
    if (strOra.size() == 5 && strOra[2] == ':') {
        try {
            hour = std::stoi(strOra.substr(0, 2));
            minute = std::stoi(strOra.substr(3, 2));

            if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
                hour = 0;
                minute = 0;
                logMessage(*this, "Errore nella creazione di Time: orario non valido", 1);
            }
        } catch (...) {
            hour = 0;
            minute = 0;
            logMessage(*this, "Errore nella creazione di Time", 1);
        }
    } else {
        hour = 0;
        minute = 0;
        logMessage(*this, "Formato non valido, deve essere hh:mm", 1);
    }
}

void Time::Setter(int h, int m, std::vector<Impianto*>* impianti) {
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


Time Time::operator++(int) {  //MODIFICARE
    minute++;

    if (minute > MAX_MINUTE) {  //Controlla che min non sia >= 60
        minute = 0;
        hour++;

        if (hour > MAX_HOUR)    //Controlla che h non sia >= 24
            hour = 0;
    }

    return *this;
}

bool Time::operator==(const Time &other) const {
    return hour == other.hour && minute == other.minute;
}

std::string Time::GetTime() const {
    //Usa due cifre per hour e minute
    std::string hh = (hour < 10 ? "0" : "") + std::to_string(hour);
    std::string mm = (minute < 10 ? "0" : "") + std::to_string(minute);
    return hh + ":" + mm;
}

std::ostream & operator<<(std::ostream &os, const Time &t) {
    return os << t.GetTime();
}
int Time::GetHour() const {
    return hour;
}
int Time::GetMinute() const {
    return minute;
}