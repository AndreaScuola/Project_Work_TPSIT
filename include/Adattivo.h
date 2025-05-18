#ifndef ADATTIVO_H
#define ADATTIVO_H

#include "Impianto.h"

class Adattivo : public Impianto {
private:
    float temperatura;
    int minutiAcceso;
    float randomFloat(float min, float max);

public:
    explicit Adattivo(const std::string& n);
    explicit Adattivo(const std::string& n, float temperaturaIniziale);
    void gestioneAdattivo(const Time& t);    //Richiamato ogni minuto --> gestisce accensione, spegnimento, ecc...

    //Implementazione dei metodi puri
    void Avanza(const Time& now) override;  //Deve chiamare Accendi e Spegni per l'adattivo
    void Accendi(const Time& now) override;
    void Spegni(const Time& now) override;
    std::string toString() const override;
};

#endif //ADATTIVO_H
