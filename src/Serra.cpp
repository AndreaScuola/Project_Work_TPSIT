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
                Impianto* imp = new Automatico("DummyImpianto");  // Assumendo costruttore valido
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
                StampaStato();
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
    for (auto it = Impianti.begin(); it != Impianti.end(); it++) {
        if ((*it)->GetID() == ID) {
            Impianti.erase(it);
            std::cout << "Impianto rimosso con successo" << std::endl;
            return;
        }
    }
    std::cout << "ERRORE! Impianto non trovato" << std::endl;
}

void Serra::StampaStato() {
    std::ostringstream oss;

    if (Impianti.empty()) {
        oss << "Nessun impianto presente.\n";
    } else {
        for (Impianto* imp : Impianti) {
            if (imp != nullptr)
                oss << imp->toString();
        }
    }

    logMessage(now, oss.str(), 0);
}

void Serra::StampaStato(int ID) {
    std::ostringstream oss;
    for (auto it = Impianti.begin(); it != Impianti.end(); it++) {
        if ((*it)->GetID() == ID) {   //Se l'ID è quello cercato  --> Stampa
            logMessage(now, (*it)->toString(), 0);
            return;
        }
    }
    //Se non trova l'impianto
    logMessage(now, "Errore nella stampa dell'impianto", 1);
}

void Serra::AccendiImpiantoManuale(int ID) {    //Accende sul momento l'impianto manuale scelto
    for (auto it = Impianti.begin(); it != Impianti.end(); it++) {
        if ((*it)->GetID() == ID) {   //Se l'ID è quello cercato e l'impianto è manuale
            if (auto m = dynamic_cast<Manuale*>(*it)) {     //Prova a fare il cast in una classe Manuale
                m->AccendiAdesso(now);  //Accende l'impianto da comando
                return;
            }
        }
    }
    //Se non trova l'impianto
    logMessage(now, "Errore nell'accensione' dell'impianto", 1);
}

void Serra::SpegniImpiantoManuale(int ID) {
    std::ostringstream oss;
    for (auto it = Impianti.begin(); it != Impianti.end(); it++) {
        if ((*it)->GetID() == ID && typeid(*it) == typeid(Manuale)) {   //Se l'ID è quello cercato e l'impianto è manuale
            (*it)->Spegni(now);
            return;
        }
    }
    //Se non trova l'impianto
    logMessage(now, "Errore nello spegnimento dell'impianto", 1);
}

std::vector<Impianto*> Serra::getImpianti() {
    return Impianti;
}

Time Serra::getTime() {
    return now;
}

void Serra::SetTimer(int ID, Time start) {  //Accensione impianto Manuale
    for (auto imp : Impianti) {
        if (imp->GetID() == ID) {
            if (auto m = dynamic_cast<Manuale*>(imp)) {     //Prova a fare il cast in una classe Manuale
                logMessage(now, m->SetAccensione(start), 0);
                return;
            }

            //L'impianto esiste ma non è Manuale
            logMessage(now, "Errore: l'impianto non e' di tipo manuale", 1);
            return;
        }
    }
    //ID non trovato
    logMessage(now, "Errore: nessun impianto con ID " + std::to_string(ID), 1);
}

void Serra::SetTimer(int ID, Time start, Time stop) {   //Accensione impianto Automatico
    for (auto imp : Impianti) {
        if (imp->GetID() == ID) {
            if (auto a = dynamic_cast<Automatico*>(imp)) {     //Prova a fare il cast in una classe Automatico
                logMessage(now, a->SetAccensione(start, stop), 0);
                return;
            }

            //L'impianto esiste ma non è Automatico
            logMessage(now, "Errore: l'impianto non e' di tipo automatico", 1);
            return;
        }
    }
    //ID non trovato
    logMessage(now, "Errore: nessun impianto con ID " + std::to_string(ID), 1);
}

//RESET TIMER

void Serra::RemoveTimer(int ID) {       //Setta a 00:00 accensione e spegnimento dell'impianto cercato
    for (auto imp : Impianti) {
        if (imp->GetID() == ID) {
            if (auto m = dynamic_cast<Manuale*>(imp)) {     //Prova a fare il cast in una classe Automatico
                m->SetAccensione(Time(0, 0));
                return;
            }

            else if (auto a = dynamic_cast<Automatico*>(imp)) {    //Prova a fare il cast in una classe Automatico
                a->SetAccensione(Time(0, 0), Time(0, 0));
                return;
            }
        }
    }

    logMessage(now, "Errore, impianto da resettare non trovato", 1);
}

void Serra::ResetTime() {   //Imposta il tempo a 00:00
    now.ResetTime();
    logMessage(now, "Timer della serra resettato", 0);
}


void Serra::ResetTimers() {     //Setta a 00:00 accensione e spegnimento di tutti gli impianti
    for (auto imp : Impianti) {
        if (auto m = dynamic_cast<Manuale*>(imp))     //Prova a fare il cast in una classe Automatico
            m->SetAccensione(Time(0, 0));

        else if (auto a = dynamic_cast<Automatico*>(imp))     //Prova a fare il cast in una classe Automatico
            a->SetAccensione(Time(0, 0), Time(0, 0));
    }

    logMessage(now, "Tutti i timer degli impianti sono stati resettati", 0);
}

void Serra::ResetAll() {    //Chiama ReserTime e ResetTimers
    ResetTimers();
    ResetTime();
    logMessage(now, "Tutti i timer sono stati resettati", 0);
}