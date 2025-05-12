#include "time.h"
#include <sstream>
#include <iomanip>  //Per GetTime che ritorni "02:08" se h = 2 e m = 8

#define MIN_HOUR 0
#define MAX_HOUR 23
#define MIN_MINUTE 0
#define MAX_MINUTE 59

void Time::Setter(int h, int m) {
    if (h < MIN_HOUR || h > MAX_HOUR || m < MIN_MINUTE || m > MAX_MINUTE)
        throw std::invalid_argument("Orario non valido");

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
            //FORSE INTERROMPERE ESECUZIONE
    }

    return *this;
}

bool Time::operator==(const Time &other) const {
    return hour == other.hour && minute == other.minute;
}

std::string Time::GetTime() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour    //Se h < 10 scrive "0n"
        << ":"
        << std::setw(2) << std::setfill('0') << minute; //Se m < 10 scrive "0n"
    return oss.str();
}