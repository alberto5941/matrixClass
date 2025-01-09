#include "matrice.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

matrice::matrice(size_t numero_righe, size_t numero_colonne) {
    righe = vector<riga>(numero_righe, riga(numero_colonne));
}

matrice::matrice(const vector<vector<double> > valori) {
    for (int i=0; i<valori.size(); i++) {
        riga riga(valori.at(i));
        righe.emplace_back(riga);
    }
}

void matrice::set_riga(size_t index, const riga& nuova_riga) {
    if(index >= 0 && index <righe.size()) {
        righe[index] = nuova_riga;
    } else {
        cout << "indice fuori dal range! " << endl;
    }
}

void matrice::stampa() {
    for(int i=0; i<righe.size(); i++) {
        riga riga(righe.at(i));
        for(int j=0; j<riga.get_numero_colonne(); j++) {
            cout << riga.get_valore(j) << " ";
        }
        cout << endl;
    }
}

size_t matrice::get_numero_righe() const {
    return righe.size();
}

size_t matrice::get_numero_colonne() const{
    return righe[0].get_numero_colonne();
}

double matrice::get(size_t riga, size_t colonna) const {
    return righe.at(riga).get_valore(colonna);
}

matrice matrice::operator+(const matrice& other) const {
    //verifica se le matrici hanno le stesse dimensioni
    if(get_numero_righe() != other.get_numero_righe() || get_numero_colonne() != other.get_numero_colonne()) {
        throw invalid_argument("le matrice devono avere le stesse dimensioni per essere sommate");
    }
    //crea un nuovo vettore per memorizzare i valori della matrice risultante
    vector<vector<double> > valori_risultati;
    for(size_t i=0; i<get_numero_righe(); i++) {
        vector<double> nuova_riga;
        for(size_t j=0; j<get_numero_colonne(); j++) {
            nuova_riga.push_back(get(i, j) + other.get(i, j));
        }
        valori_risultati.push_back(nuova_riga);
    }
    return matrice(valori_risultati);
}

matrice matrice::operator*(double scalar) const {
     vector<vector<double> > valori_risultati;
     for(size_t i=0; i<get_numero_righe(); i++) {
        vector<double> nuova_riga;
        for(size_t j=0; j<get_numero_colonne(); j++) {
            nuova_riga.push_back((get(i, j)*scalar));
        }
        valori_risultati.push_back(nuova_riga);
    }
    return matrice(valori_risultati);
}

matrice operator*(double scalar, const matrice& M) {
    vector<vector<double> > valori_risultati;
     for(size_t i=0; i<M.get_numero_righe(); i++) {
        vector<double> nuova_riga;
        for(size_t j=0; j<M.get_numero_colonne(); j++) {
            nuova_riga.push_back((M.get(i, j)*scalar));
        }
        valori_risultati.push_back(nuova_riga);
    }
    return matrice(valori_risultati);
}

matrice matrice::operator-(const matrice& other) const {
    //verifica se le matrici hanno le stesse dimensioni
    if(get_numero_righe() != other.get_numero_righe() || get_numero_colonne() != other.get_numero_colonne()) {
        throw invalid_argument("le matrici devono avere le stesse dimensioni per essere sottratte");
    }
    //crea un nuovo vettore per memorizzare i valori della matrice risultante
    vector<vector<double> > valori_risultati;
    for(size_t i=0; i<get_numero_righe(); i++) {
        vector<double> nuova_riga;
        for(size_t j=0; j<get_numero_colonne(); j++) {
            nuova_riga.push_back(get(i, j) - other.get(i, j));
        }
        valori_risultati.push_back(nuova_riga);
    }
    return matrice(valori_risultati);
}

void matrice::set_elemento(size_t index_riga, size_t index_colonna, double value) {
    if(index_riga >= 0 && index_riga < get_numero_righe() && index_colonna >= 0 && index_colonna < get_numero_colonne()) {
        righe.at(index_riga).set_valore(index_colonna, value);
    } else {
        cerr << "indici fuori dai limiti " << endl;
    }
}

matrice matrice::calcola_trasposta() {
    size_t n = get_numero_righe();
    vector<double> riga;
    matrice trasposta(n, n);
    if(get_numero_righe() != get_numero_colonne()) {
        throw invalid_argument("la matrice deve essere quadrata per poterne calcolare la trasposta");
    } else {
        for(size_t i=0; i<n; i++) {
            for(size_t j=0; j<n; j++) {
                double value = get(i, j);
                trasposta.set_elemento(j, i, value);
            }
        }
    }
    return trasposta;
}

double matrice::calcola_traccia() {
    double traccia;
    for(size_t i=0; i<get_numero_righe(); i++) {
        traccia += get(i, i);
    }
    return traccia;
}

bool matrice::verifica_simmetria() {
    bool simmetria = true;
    if(get_numero_righe() != get_numero_colonne()) {
        simmetria = false;
    } else {
        size_t n = get_numero_righe();
        for(size_t i=0; i<n; i++) {
            for(size_t j=0; j<n; j++) {
                if(get(i, j) != get(j, i)) {
                    simmetria = false;
                }
            }
        }
    }
    return simmetria;
}

bool matrice::verifica_antisimmetria() {
    bool antisimmetria = true;
    if(get_numero_righe() != get_numero_colonne()) {
        antisimmetria = false;
    } else {
        size_t n = get_numero_righe();
        for(size_t i=0; i<n; i++) {
            for(size_t j=0; j<n; j++) {
                if(get(i, j) != -get(j, i)) {
                    antisimmetria = false;
                }
            }
        }
    }
    return antisimmetria;
}

matrice matrice::operator*(const matrice& other) const {
    //verifica se le matrici hanno le giuste dimensioni
    if(get_numero_colonne() != other.get_numero_righe()) {
        throw invalid_argument("il numero di colonne della prima matrice deve essere uguale al numero di righe della seconda per poterle moltiplicare tra loro");
    }
    //crea un nuovo vettore per memorizzare i valori della matrice risultante
    vector<vector<double> > valori_risultato(get_numero_righe(), vector<double>(other.get_numero_colonne()));
    for(size_t i=0; i<get_numero_righe(); i++) {
        for(size_t j=0; j<other.get_numero_colonne(); j++) {
            for(size_t k=0; k<get_numero_colonne(); k++) {
                valori_risultato[i][j] += get(i, k) * other.get(k, j);
            }
        }
    }
    return matrice(valori_risultato);
}
