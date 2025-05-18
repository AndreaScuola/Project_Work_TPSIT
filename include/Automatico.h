#ifndef AUTOMATICO_H
#define AUTOMATICO_H

#include "Impianto.h"

class Automatico : public Impianto {
private:
    int oreAcceso;  //Ore e minuti che l'impianto automatico aspetta prima di spegnersi
    int minutiAcceso;
    Time tempoAccensione;    //Ora a cui si deve accendere
    Time tempoSpegnimento;  //Ora a cui deve essere spento
    void OraSpegnimento(); //Calcola l'ora a cui deve essere spento

public:
    explicit Automatico(const std::string& n, int oreAcceso, int minutiAcceso);
    void SetAccensione(const Time& t);

    //Implementazione dei metodi puri
    void Accendi(const Time& t) override;
    void Spegni(const Time& t) override;
    std::string toString() const override;
};


#endif //AUTOMATICO_H
