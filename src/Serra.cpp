#include "Serra.h"
#include "UserInterface.h"
#include "Time.h"
#include "Automatico.h"
#include "Manuale.h"
#include "Adattivo.h"
#include <iostream>
#include <sstream>

void Serra::Menu() {    //CODICE PROVVISORIO
    int scelta;
    bool esci = false;

    while (!esci) {
        std::cout << "\n--- Menu Serra ---\n";
        std::cout << "1) Aggiungi Impianto (dummy)\n";
        std::cout << "2) Rimuovi Impianto\n";
        std::cout << "3) Aggiorna orario\n";
        std::cout << "4) Stampa stato impianti\n";
        std::cout << "5) Esci\n";
        std::cout << "Scelta: ";
        std::cin >> scelta;

        switch (scelta) {
            case 1: {
                // Esempio: aggiunge un impianto fittizio (da sostituire con factory o input reale)
                std::cout << "Aggiunta impianto dummy...\n";
                Impianto* imp = new Automatico("DummyImpianto", 1, 20);  // Assumendo costruttore valido
                AggiungiImpianto(imp);
                break;
            }
            case 2: {
                int id;
                std::cout << "Inserisci ID impianto da rimuovere: ";
                std::cin >> id;
                RimuoviImpianto(id);
                break;
            }
            case 3: {
                int h, m;
                std::cout << "Inserisci ora (0-23): ";
                std::cin >> h;
                std::cout << "Inserisci minuti (0-59): ";
                std::cin >> m;
                AggiornaOrario(h, m);
                break;
            }
            case 4: {
                std::cout << StampaStato();
                break;
            }
            case 5:
                esci = true;
            break;
            default:
                std::cout << "Scelta non valida.\n";
        }
    }
}


void Serra::AggiornaOrario(int hour,int minutes) {
    now.Setter(hour, minutes, &Impianti);   //Passo l'ora da raggiungere al Setter --> Scorre minuto per minuto ed invoca i metodi degli impianti
}

void Serra::AggiungiImpianto(Impianto* impianto) {
    if (impianto == NULL)
        return;

    Impianti.push_back(impianto);
}


void Serra::RimuoviImpianto(int ID) {
    for (auto it = Impianti.begin(); it != Impianti.end(); ++it) {
        if ((*it)->GetID() == ID) {
            Impianti.erase(it);
            std::cout << "Impianto rimosso con successo" << std::endl;
            return;
        }
    }
    std::cout << "ERRORE! Impianto non trovato" << std::endl;
}

std::string Serra::StampaStato() {
    std::ostringstream oss;

    if (Impianti.empty()) {
        oss << "Nessun impianto presente.\n";
    } else {
        for (Impianto* imp : Impianti) {
            if (imp != nullptr)
                oss << imp->toString();
        }
    }

    return oss.str();
}

//MODIFICARE
void Serra::SpegniImpiantoManuale(int ID) {
    //CODICE DA AGGIUNGERE
    std::ostringstream oss;
    for (auto it = Impianti.begin(); it != Impianti.end(); ++it) {
        if ((*it)->GetID() == ID&&typeid(*it)==typeid(Manuale)) {

            (*it)->Spegni(now);
            std::cout << "Impianto rimosso con successo" << std::endl;
            return;
        }else if ((*it)->GetID() == ID&&typeid(*it)!=typeid(Manuale))
            std::cout << "Errore nella rimozione dell'impianto" << std::endl;
        return;
    }

}

std::vector<Impianto*> Serra::getImpianti() {
    return Impianti;
}