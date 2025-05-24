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
    void Help();
    void AggiornaOrario(int hour,int minutes);
    void AggiungiImpianto(Impianto* impianto);
    void RimuoviImpianto(int ID);
    void StampaStato();
    void StampaStato(int ID);
    void AccendiImpiantoManuale(int ID);
    void SpegniImpiantoManuale(int ID);
    std::vector<Impianto*> getImpianti();
    Time getTime();
    void SetTimer(int ID, Time start);
    void SetTimer(int ID, Time start, Time stop);

    void RemoveTimer(int ID);   //Resetta il timer dell'impianto scelto
    void ResetTime();   //Imposta il tempo a 00:00
    void ResetTimers();    //Mette le accensioni a 00:00 (e anche lo spegnimento a 00:00 se è Automatico)
    void ResetAll();    //Chiama ReserTime e ResetTimers
};

#endif //SERRA_H
