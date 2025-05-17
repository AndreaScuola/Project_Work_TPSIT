#ifndef AUTOMATICO_H
#define AUTOMATICO_H

#include "Impianto.h"

class Automatico : public Impianto {
private:
    Time tempoAcceso;  // totale tempo di funzionamento

public:
    explicit Automatico(const std::string n, int oreAcceso, int minutiAcceso);

    // implementazione dei metodi puri
    std::string Accendi(const Time t) override;
    std::string Spegni(const Time t) override;

    // (opzionale) getter per tempoAcceso
    Time GetTempoAcceso() const;
    std::string toString() const;
};


#endif //AUTOMATICO_H
