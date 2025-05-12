//Qui bisogna dichiarare costanti e metodi

#ifndef IMPIANTO_H
#define IMPIANTO_H

class Impianto {    //CLASSE VIRTUALE
protected:
    int ID;
    //AGGIUNGERE

public:
    explicit Impianto(int id /*AGGIUNGERE*/) : ID{id} {}; //explicit --> blocca il costruttore "Impianto imp = "10"; " (Blocca conversioni implicite)
                                                    //permette solo --> "Impianto imp(10);"
    //AGGIUNGERE METODI
    int getID() { return ID; };
};

#endif //IMPIANTO_H
