#include "Serra.h"
#include "UserInterface.h"
#include "Time.h"
#include "Automatico.h"
#include "Manuale.h"
#include "Adattivo.h"
#include <iostream>
#include <sstream>

void Serra::Help() {
    std::cout << R"(

    ================== COMANDI DISPONIBILI ==================

      help                     - Mostra questo output
      exit                     - Chiude il programma

      set <ID> on              - Accende l'impianto manuale
      set <ID> off             - Spegne l'impianto manuale
      set <ID> <START>         - Accensione automatica impianto manuale
      set <ID> <START> <STOP>  - Accensione automatica impianto automatico

      rm <ID>                  - Rimuove i timer dell'impianto (reset a [00:00])
      remove <ID>              - Rimuove completamente l'impianto

      add manuale <Nome>       - Aggiunge un impianto manuale con nome <Nome>
      add automatico <Nome>    - Aggiunge un impianto automatico con nome <Nome>
      add adattivo <Nome>      - Aggiunge un impianto adattivo con nome <Nome>

      show                     - Mostra lo stato e consumo di tutti gli impianti
      show <ID>                - Mostra lo stato e i dettagli di un impianto

      set time <HH:MM>         - Imposta l'orario attuale della serra
      reset time               - Resetta l'orario a [00:00] e spegne tutti gli impianti
      reset timers             - Rimuove tutti i timer mantenendo lo stato attuale
      reset all                - Resetta orario, timer e spegne tutti gli impianti

    ==========================================================

    )" << std::endl;
}

void Serra::AggiornaOrario(int hour,int minutes) {
    now.Setter(hour, minutes, &Impianti);   //Passo l'ora da raggiungere al Setter --> Scorre minuto per minuto ed invoca i metodi degli impianti
}

void Serra::AggiungiImpianto(Impianto* impianto) {
    if (impianto == NULL)
        return;

    Impianti.push_back(impianto);
    logMessage(now, "Impianto aggiunto con successo", 0);
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
        oss << "Stato serra:" << std::endl;
        for (Impianto* imp : Impianti) {
            if (imp != nullptr)
                oss << imp->toString();
        }
    }

    logMessage(now, oss.str(), 0);
}

void Serra::StampaStato(int ID) {
    for (auto it = Impianti.begin(); it != Impianti.end(); it++) {
        if ((*it)->GetID() == ID) {   //Se l'ID è quello cercato  --> Stampa
            logMessage(now, (*it)->toString(), 0);
            return;
        }
    }
    //Se non trova l'impianto
    logMessage(now, "Errore nella stampa dell'impianto", 1);
}

void Serra::AccendiImpiantoManuale(int ID) {    // Accende sul momento l'impianto manuale scelto
    for (Impianto* imp : Impianti) {
        if (imp->GetID() == ID) {
            if (auto m = dynamic_cast<Manuale*>(imp)) {
                // Chiamiamo il metodo specifico di Manuale per l'accensione “adesso”
                // Supponendo che ti restituisca una stringa di log:
                std::string msg = m->AccendiAdesso(now);
                logMessage(now, msg, 0);
                return;
            } else {
                // Il dispositivo esiste ma non è manuale
                logMessage(now, "Errore: l'impianto non e' di tipo Manuale", 1);
                return;
            }
        }
    }
    // Se non trova l'impianto con quell'ID
    logMessage(now, "Errore: impianto non trovato", 1);
}


void Serra::SpegniImpiantoManuale(int ID) {
    for (auto imp : Impianti) {
        if (imp->GetID() == ID) {
            if (auto m = dynamic_cast<Manuale*>(imp)) {
                m->Spegni(now);
                return;
            } else {
                // l'ID c'è ma non è un Manuale
                logMessage(now, "Errore: l'impianto non e' di tipo Manuale", 1);
                return;
            }
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
    logMessage(now, "Errore: nessun impianto con ID '" + std::to_string(ID)+"'", 1);
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
    logMessage(now, "Errore: nessun impianto con ID '" + std::to_string(ID)+"'", 1);
}

//RESET TIMER

void Serra::RemoveTimer(int ID) {       //Setta a 00:00 accensione e spegnimento dell'impianto cercato
    for (auto imp : Impianti) {
        if (imp->GetID() == ID) {
            if (auto m = dynamic_cast<Manuale*>(imp)) {     //Prova a fare il cast in una classe Automatico
                m->SetAccensione(Time(0, 0));
                logMessage(now, "Timer dell'impianto scelto resettato", 0);
                return;
            }

            else if (auto a = dynamic_cast<Automatico*>(imp)) {    //Prova a fare il cast in una classe Automatico
                a->SetAccensione(Time(0, 0), Time(0, 0));
                logMessage(now, "Timer dell'impianto scelto resettato", 0);
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