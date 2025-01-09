#include "riga.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;


//costruttore con numero di colonne
riga::riga(size_t numero_colonne) : vec_elementi(numero_colonne, 0.0) {}

//costruttore con valori iniziali
riga::riga(const vector<double> vec_valori) : vec_elementi(vec_valori) {}

size_t riga::get_numero_colonne() const{
    return vec_elementi.size();
}

void riga::set_valore(size_t colonna, double valore) {
    if(colonna >= vec_elementi.size()) {
        throw out_of_range("indice  della colonna fuori dal range");
    }
    vec_elementi.at(colonna) = valore;
}

double riga::get_valore(size_t colonna) const {
    if(colonna >= vec_elementi.size()) {
        throw out_of_range("indice della colonna fuori dal range");
    }
    return vec_elementi.at(colonna);
}

void riga::stampa() {
    for(int i=0; i<vec_elementi.size(); i++) {
        cout << vec_elementi.at(i) << "  " << endl;
    }
    cout << endl;
}
