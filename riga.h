#ifndef RIGA_H_
#define RIGA_H_

#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class riga {
    private:
    vector<double> vec_elementi; //vettore che contiene gli elementi della riga;

    public:
    //costruttori
    riga(size_t numero_colonne);
    riga(vector<double> vec_valori);


    //metodi
    size_t get_numero_colonne() const; //metodo per ottenere il numero di colonne
    void set_valore(size_t colonna, double valore); //imposta un valore in una colonna
    double get_valore(size_t colonna) const; //restiuisce il valore indicato della riga
    void stampa(); //stampa la riga
};


#endif // RIGA_H_
