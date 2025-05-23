#ifndef AUTOMATICO_H
#define AUTOMATICO_H

#include "Impianto.h"

class Automatico : public Impianto {
private:
    Time tempoAccensione;    //Ora a cui si deve accendere
    Time tempoSpegnimento;  //Ora a cui deve essere spento

public:
    explicit Automatico(const std::string& n);
    std::string SetAccensione(const Time& oraAccensione, const Time& oraSpegnimento);

    //Implementazione dei metodi puri
    void Avanza(const Time& now) override;  //Nella classe automatico deve chiamare Accendi e Spegni
    void Accendi(const Time& now) override;
    void Spegni(const Time& now) override;
    std::string toString() const override;
};

#endif //AUTOMATICO_H
