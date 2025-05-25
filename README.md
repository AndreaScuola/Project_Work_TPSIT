========================================
      PROJECT WORK TPSIT - SERRA
========================================

Gruppo: Bassan, Favero, Ye, Zanfardini

1. DESCRIZIONE DEL PROGETTO
---------------------------
Sviluppo di una libreria in C++ per monitorare e controllare impianti di irrigazione in una serra.
Tipologie di impianti gestiti:
  - Manuale
  - Automatico
  - Adattivo

Funzionalità principali:
  * Creazione, eliminazione e gestione di impianti
  * Accensione/spegnimento manuale
  * Programmazione temporizzata (start/stop)
  * Reset di orario e timer
  * Tracciamento dello stato e log su file

2. ORGANIZZAZIONE DEL LAVORO
----------------------------

Bassan:
  - Modifiche della classe UserInterface
  - Revisione e ampliamento della classe Time
  - Implementazione parziale di Serra
  - Stesura di Impianto e delle classi derivate (Automatico, Manuale, Adattivo)
  - Bozza del main e configurazione CMake

Zanfardini:
  - Completamento di UserInterface
  - Debug e test di progetto
  - Scrittura dell’header Serra
  - Correzione messaggi di output
  - Scrittura di parte dei commenti e testing finale

Favero:
  - Versione base di Time
  - Implementazione log su file
  - Testing finale

Ye:
  - Definizione dell’header Impianto
  - Correzione messaggi di output
  - Stesura del README
  - Testing finale

3. PROBLEMI RISCONTRATI
-----------------------
  - Complessità iniziale nella comprensione della logica di UserInterface
  - Conflitti di librerie e namespace in C++
  - Configurazione CMake di CLion
  - Aggiornamenti IDE/CMake richiesti da nuove versioni del progetto

4. FUNZIONALITÀ E COMANDI
--------------------------
Il comando help elenca tutti i comandi disponibili; le parentesi graffe indicano i valori da sostituire con i valori richiesti.

Le classi derivate da Impianto si comportano così:
Manuale:
  - set {ID} on -> accende immediatamente
  - set {ID} off -> spegne immediatamente
  - set {ID} {oraAccensione} -> programma l'accensione all’ora indicata

Automatico:
  - set {ID} {oraAccensione} {oraSpegnimento} -> programma accensione e spegnimento automatici

Adattivo:
gestisce accensione e spegnimento dinamicamente in base alla temperatura, che varia nel tempo

========================================
