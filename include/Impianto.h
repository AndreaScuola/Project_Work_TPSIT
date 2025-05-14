//Qui bisogna dichiarare costanti e metodi
#ifndef IMPIANTO_H
#define IMPIANTO_H

using namespace std;

#include <string>
#include "Time.h"

int GetID(int id) {

}
string Accendi(Time accensione) {

}
string Spegni(Time spegni) {

}
string Stampa(string frase) {

}

class Impianto {    //CLASSE VIRTUALE
protected:
    int ID;
    string TipoPianta;
    string Nome;
    bool accesso;
    Time accensione;
    Time ultimaAccensione;
    Time tempospegni;

    //AGGIUNGERE

public:
    explicit Impianto(int id /*AGGIUNGERE*/) : ID{id} {}; //explicit --> blocca il costruttore "Impianto imp = "10"; " (Blocca conversioni implicite)
                                                    //permette solo --> "Impianto imp(10);"
    //AGGIUNGERE METODI
    int GetID(int id) { return ID; };
    string Accendi(Time accensione);
    string Spegni(Time spegni);
    string Stampa(string frase);
};

#endif //IMPIANTO_H
