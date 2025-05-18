#include <ostream>
#include <sstream>
#include <stdexcept>  //Per std::invalid_argument
#include "Time.h"

#define MIN_HOUR 0
#define MAX_HOUR 23
#define MIN_MINUTE 0
#define MAX_MINUTE 59

void Time::Setter(int h, int m) {
    if (h < MIN_HOUR || h > MAX_HOUR || m < MIN_MINUTE || m > MAX_MINUTE)
        throw std::invalid_argument("Orario non valido");       //CONSIDERARE SE MODIFICARE CON LOGMESSAGE

    while (hour != h || minute != m)  //Fa scatti di minuto in minuto fino a quando non raggiunge l'ora desiderata
        (*this)++;
}

Time Time::operator++(int) {  //MODIFICARE
    minute++;

    if (minute > MAX_MINUTE) {  //Controlla che min non sia >= 60
        minute = 0;
        hour++;

        if (hour > MAX_HOUR)    //Controlla che h non sia >= 24
            hour = 0;
            //FORSE INTERROMPERE ESECUZIONE  --> Vedere come gestire le 24:00
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

//CAPIRE A COSA SERVE OPERATOR << PER USERINTERFACE.cpp E SISTEMARLO
std::ostream & operator<<(std::ostream &os, const Time &obj) {
    /*
    return os
           << "hour: " << obj.hour
           << " minute: " << obj.minute;
    */
    return os;  //COMMENTATA AL MOMENTO, MODIFICARE TUTTO L'OPERATOR <<
}