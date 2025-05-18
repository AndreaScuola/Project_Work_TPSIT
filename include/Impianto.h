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
    virtual void Avanza(const Time& now) = 0;  //Metodo che viene richiamato in modo diverso in base alla classe figlia per diverse gestioni
    virtual void Accendi(const Time& now) = 0;
    virtual void Spegni(const Time& now) = 0;
    virtual std::string toString()const = 0;
};

#endif //IMPIANTO_H
