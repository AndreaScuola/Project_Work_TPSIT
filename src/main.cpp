#include <iostream>
#include "Serra.h"    //Collega il .cpp al .h
#include "Automatico.h"
#include "Manuale.h"
#include "Adattivo.h"

int main() {
    Serra serra;

    Automatico* automatico = new Automatico("Impianto", 1, 20);
    automatico->SetAccensione(Time(1, 2));

    serra.AggiungiImpianto(automatico);  // <<< questa riga è fondamentale

    serra.AggiornaOrario(2, 0);
    serra.AggiornaOrario(4, 0);

    return 0;
}
