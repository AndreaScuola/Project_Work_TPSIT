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
    Time ultimaAccensione;
    static int prossimoID;

    //AGGIUNGERE

public:
    //dichiarazione del costruttore
    explicit Impianto(const std::string& n);
    int GetID() const { return ID; }

    //metodi da implementare/ridefinire
    virtual void Accendi(const Time& t) = 0;
    virtual void Spegni(const Time& t) = 0;
    virtual std::string toString() const;
};

#endif //IMPIANTO_H
