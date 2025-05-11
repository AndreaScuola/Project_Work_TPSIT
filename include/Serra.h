//Qui bisogna dichiarare costanti e metodi
#ifndef SERRA_H
#define SERRA_H
#include <Impianto.h>
#include <vector>
#include <Time.h>
#include <string>

class Serra{

private:
    vector<Impianto*> Impianti;
    Time now;

public:
    void Menu();
    void AggiornaOrario(int hour,int minutes);
    void AggiungiImpianto(Impianto* impianto);
    void RimuoviImpianto(int ID);
    string StampaStato();
    string SpegniImpiantoManuale();
};


#endif //SERRA_H
