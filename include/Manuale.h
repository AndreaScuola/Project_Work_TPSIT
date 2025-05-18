#ifndef MANUALE_H
#define MANUALE_H

#include "Impianto.h"

class Manuale : public Impianto {
private:
    Time tempoAccensione;    //Ora a cui si deve accendere --> Lo spegnimento va fatto con comando

public:
    explicit Manuale(const std::string& n);
    void SetAccensione(const Time& t);

    //Implementazione dei metodi puri
    void Avanza(const Time& now) override;  //In manuale la gestione è richiamare Accendi
    void Accendi(const Time& now) override;
    void Spegni(const Time& now) override;
    std::string toString() const override;
};

#endif //MANUALE_H