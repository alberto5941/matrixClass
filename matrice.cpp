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

matrice::matrice(const vector<riga> vec_righe) {
    for(int i=0; i<vec_righe.size(); i++) {
        righe.push_back(vec_righe.at(i));
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

matrice matrice::calcola_trasposta_copia() {
    size_t n = get_numero_righe();
    vector<riga> righe_trasposte;
    riga riga_trasposta(n);
    for(size_t i=0; i<get_numero_colonne(); i++) {
        for(size_t j=0; j<n; j++) {
            riga_trasposta.set_valore(j, righe.at(j).get_valore(i));
        }
        righe_trasposte.push_back(riga_trasposta);
    }
    matrice copia(righe_trasposte);
    return copia;
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

matrice matrice::elimina_riga_copia(size_t index) {
    if(index < 0 || index>righe.size()) {
        throw out_of_range("indice fuori dai limiti: puoi eliminare solo una riga che appartiene alla matrice ");
    }
    matrice copia = *this;
    copia.righe.erase(copia.righe.begin() + index);
    return copia;
}

matrice matrice::elimina_colonna_copia(size_t index) {
    if(index < 0 || index>righe.size()) {
        throw out_of_range("indice fuori dai limiti: puoi eliminare solo una riga che appartiene alla matrice ");
    }
    matrice trasposta_copia = calcola_trasposta_copia();
    matrice senza_riga = trasposta_copia.elimina_riga_copia(index);
    matrice senza_colonna(get_numero_righe(), get_numero_colonne()-1);
    senza_colonna = senza_riga.calcola_trasposta_copia();
    return senza_colonna;
}

matrice matrice::elimina_riga_colonna_copia(size_t r, size_t c) {
    if(r < 0 || r>righe.size() || c<0 || c>get_numero_colonne()) {
        throw out_of_range("indice fuori dai limiti: puoi eliminare solo una riga che appartiene alla matrice ");
    }
    matrice nuova1 = *this;
    matrice nuova2 = *this;
    nuova1 = elimina_riga_copia(r);
    nuova2 = nuova1.elimina_colonna_copia(c);

    return nuova2;
}

double matrice::get_determinante() {
    if(get_numero_righe() != get_numero_colonne()) {
        throw invalid_argument("puoi calcolare il determinante solo di una matrice quadrata");
    }
    double determinante;
    if(get_numero_righe() == 1) {
        determinante = get(0,0);
    }
    if(get_numero_righe() == 2) {
        determinante = get(0, 0)*get(1, 1) - get(0, 1)*get(1, 0);
    }
    if(get_numero_righe() > 2) {
        double sommatoria = 0;
        for(size_t i=0; i<get_numero_righe(); i++) {
                matrice tagliata = elimina_riga_colonna_copia(i, 0);
                double elemento = tagliata.get_determinante()*get(i, 0);
                sommatoria = sommatoria + elemento*pow(-1, i);
            }
        determinante = sommatoria;
    }
    return determinante;
}

bool matrice::verifica_invertibilita() {
    bool invertibile;
    if(get_numero_righe() != get_numero_colonne()) {
        throw invalid_argument("non esiste inversa: la matrice deve essere quadrata");
    }
    if(get_determinante() == 0) {
        invertibile = false;
    } else {
        invertibile = true;
    }
    return invertibile;
}

matrice matrice::get_inversa() {
    if(get_numero_righe() != get_numero_colonne()) {
        throw invalid_argument("non esiste inversa: la matrice deve essere quadrata");
    }
    bool invertibile = verifica_invertibilita();
    if(invertibile==false) {
        throw invalid_argument("la matrice non ammette inversa");
    }
    vector<riga> righe_cofattori;
    size_t n = get_numero_righe();
    riga riga_cofattori(n);
    for(size_t i=0; i<n; i++) {
        for(size_t j=0; j<n; j++) {
            matrice tagliata = elimina_riga_colonna_copia(i, j);
            double value = tagliata.get_determinante();
            riga_cofattori.set_valore(j, value);
        }
        righe_cofattori.push_back(riga_cofattori);
    }
    matrice cofattori(righe_cofattori);
    matrice inversa(n, n);
    inversa = (1/get_determinante())*cofattori.calcola_trasposta_copia();
    return inversa;
}
