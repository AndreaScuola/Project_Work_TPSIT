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
    void RimuoviImpianto(int ID) {
        for (auto it = Impianti.begin(); it != Impianti.end(); ++it) {
            if ((*it)->getID() == ID) {
                Impianti.erase(it);
                break;
            }
        }
    }
    void AggiungiImpianto(Impianto* impianto) {
        if (impianto==NULL)
            return;
        else
            Impianti.push_back(impianto);
    }
    string StampaStato();
    string SpegniImpiantoManuale();

};


#endif //SERRA_H
