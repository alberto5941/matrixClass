#ifndef MATRICE_H_
#define MATRICE_H_
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
#include "riga.h"
using namespace std;

class matrice {
    private:
    vector<riga> righe; //vettore di oggetti riga che rappresenta la matrice

    public:
    //costruttori
    matrice(size_t numero_righe, size_t numero_colonne); //matrice vuota
    matrice(vector<vector<double> > valori); //matrice con valori iniziali
    matrice(const vector<riga> righe);//costruttore con vector<riga>

    //metodi
    void set_riga(size_t index, const riga& nuova_riga); //metodo per settare il contenuto di una riga della matrice
    void set_elemento(size_t index_riga, size_t index_colonna, double value);
    void stampa(); // metodo per stampare la matrice su schermo
    size_t get_numero_righe() const;
    size_t get_numero_colonne() const;
    double get(size_t riga, size_t colonna) const;
    double calcola_traccia();
    bool verifica_simmetria();
    bool verifica_antisimmetria();
    matrice elimina_riga_copia(size_t index);
    matrice elimina_colonna_copia(size_t index);
    matrice calcola_trasposta_copia();
    matrice elimina_riga_colonna_copia(size_t r, size_t c);
    double get_determinante();
    matrice get_inversa();
    bool verifica_invertibilita();



    //operatori
    matrice operator+(const matrice& other) const;
    matrice operator*(double scalar) const;
    friend matrice operator*(double scalar, const matrice& M);
    matrice operator-(const matrice& other) const;
    matrice operator*(const matrice& other) const;
};


#endif // MATRICE_H_
