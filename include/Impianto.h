//Qui bisogna dichiarare costanti e metodi
#ifndef IMPIANTO_H
#define IMPIANTO_H

#include <string>
#include "Time.h"

class Impianto {    //CLASSE VIRTUALE
protected:
    int ID;
    std::string Nome;
    bool acceso;
    Time accensione;
    Time ultimaAccensione;
    Time tempoSpegni;
    static int prossimoID;

    //AGGIUNGERE

public:
    //dichiarazione del costruttore
    explicit Impianto(const std::string n);

    //metodi da implementare/ridefinire
    virtual std::string Accendi(Time t) = 0;
    virtual std::string Spegni(Time t) = 0;
    virtual std::string Stampa(std::string frase) const;

    int GetID() const { return ID; }

/*
    explicit Impianto(std::string n) n(Nome), id(prossimoID++) {};//explicit --> blocca il costruttore "Impianto imp = "10"; " (Blocca conversioni implicite)
                                                    //permette solo --> "Impianto imp(10);"
    //AGGIUNGERE METODI
    int GetID(int id) { return ID; };
    std::string Accendi(Time accensione);
    std::string Spegni(Time spegni);
    std::string Stampa(std::string frase);
*/
};

#endif //IMPIANTO_H
