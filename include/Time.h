#ifndef TIME_H
#define TIME_H

#include <ostream>
#include <string>
#include <vector>

class Impianto;        // <-- forward declaration

class Time {
private:
    int hour;
    int minute;

public:
    Time() {hour = 0; minute = 0;}  //Costruttore di default
    Time(int h, int m) : hour{h}, minute{m} {}  //Costruttore valorizzato
    Time(std::string strOra);

    void Setter(int h, int m, std::vector<Impianto*>* impianti = nullptr);
    Time operator++(int); //MODIFICARE
    bool operator==(const Time &other) const;   //Parametri da confrontare, const perché non vanno modificati
    std::string GetTime() const;
};

std::ostream & operator<<(std::ostream &os, const Time &t);

#endif // TIME_H