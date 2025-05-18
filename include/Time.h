#ifndef TIME_H
#define TIME_H

#include <ostream>
#include <string>
#include <stdexcept>   //Necessario per std::invalid_argument
#include "Impianto.h"
#include <vector>

class Time {
private:
    int hour;
    int minute;

public:
    Time() {hour = 0; minute = 0;}  //Costruttore di default
    Time(int h, int m) : hour{h}, minute{m} {}  //Costruttore valorizzato

    void Setter(int h, int m, std::vector<Impianto*>* impianti = nullptr);
    Time operator++(int); //MODIFICARE
    bool operator==(const Time &other) const;   //Parametri da confrontare, const perché non vanno modificati
    std::string GetTime() const;
    int get_hour() const {return hour;} //Getter per operator <<
    int get_minute() const {return minute;}
};

std::ostream & operator<<(std::ostream &os, const Time &obj);

#endif // TIME_H