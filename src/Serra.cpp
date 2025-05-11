#include "../include/Serra.h"    //Collega il .cpp al .h

void Serra :: Menu() {
    //CODICE
    //SPECIFICARE COSA FA MENU --> "Cosa vuoi fare: 1)Crea 2)Elimina 3)..." --> Richiamare il metodo in base alla scelta
}

void Serra :: AggiornaOrario(int hour,int minutes) {
    //CODICE
}

void Serra :: AggiungiImpianto(Impianto* impianto) {
    if (impianto == NULL)
        return;

    Impianti.push_back(impianto);
}

void Serra :: RimuoviImpianto(int ID) {
    for (auto it = Impianti.begin(); it != Impianti.end(); ++it) {
        if ((*it)->getID() == ID) {
            Impianti.erase(it);
            break;
        }
    }
}

string Serra :: StampaStato() {
    //CODICE
}

string Serra :: SpegniImpiantoManuale() {
    //CODICE
}