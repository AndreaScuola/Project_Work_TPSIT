//Qui bisogna dichiarare costanti e metodi
#ifndef SERRA_H
#define SERRA_H
#include "Impianto.h"
#include <vector>
#include <Time.h>
#include <string>

class Serra{

private:
    std::vector<Impianto*> Impianti;
    Time now;

public:
    Serra() : now(0, 0), Impianti{} {} //Costruttore
    void Menu();
    void AggiornaOrario(int hour,int minutes);
    void AggiungiImpianto(Impianto* impianto);
    void RimuoviImpianto(int ID);
    std::string StampaStato();
    void SpegniImpiantoManuale();
};

#endif //SERRA_H
