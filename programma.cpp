#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "riga.h"
#include "matrice.h"
using namespace std;

int main() { //programma per testare alcuni metodi della classe matrice
    int n; //dimensioni della matrice
    cout << "inserisci le dimensioni della matrice " << endl;
    cin >> n;

    double elemento;
    matrice matrice1(n, n), matrice2(n, n);
    for(int i=0; i<n; i++) {
        riga riga(n);
        cout << "riga numero " << i+1 << endl;
        for(int j=0; j<n; j++) {
            cout << "inserisci l'elemento numero " << j+1 << " della riga " << i+1 << endl;
            cin >> elemento;
            riga.set_valore(j, elemento);
        }
        matrice1.set_riga(i, riga);
    }

    for(int i=0; i<n; i++) {
        riga riga(n);
        cout << "riga numero " << i+1 << endl;
        for(int j=0; j<n; j++) {
            cout << "inserisci l'elemento numero " << j+1 << " della riga " << i+1 << endl;
            cin >> elemento;
            riga.set_valore(j, elemento);
        }
        matrice2.set_riga(i, riga);
    }

    double scalare;

    cout << "inserisci uno scalare " << endl;
    cin >> scalare;

    cout << endl;
    cout << endl;

    cout << "matrice 1: " << endl;
    matrice1.stampa();
    cout << "matrice 2: " << endl;
    matrice2.stampa();

    matrice matrice_somma(n, n);
    matrice_somma = matrice1 + matrice2;
    cout << "matrice somma: " << endl;
    matrice_somma.stampa();

    matrice matrice_differenza(n, n);
    matrice_differenza = matrice1 - matrice2;
    cout << "matrice differenza: " << endl;
    matrice_differenza.stampa();

    matrice  matrice_scalare_1(n, n);
    matrice_scalare_1 = scalare*matrice1;

    matrice  matrice_scalare_2(n, n);
    matrice_scalare_2 = matrice1*scalare;

    cout << endl;
    cout << "scalare * matrice1:" << endl;
    matrice_scalare_1.stampa();
    cout << endl;
    cout << "matrice1 * scalare:" << endl;
    matrice_scalare_2.stampa();

    cout << endl;
    double traccia = matrice1.calcola_traccia();
    cout << "la traccia della matrice 1 vale " << traccia << endl;

    bool simmetria = matrice1.verifica_simmetria();
    if(simmetria == true) {
        cout << "matrice 1 simmetrica " << endl;
    } else {
        cout << "matrice 1 non simmetrica " << endl;
    }

    bool antisimmetria = matrice1.verifica_antisimmetria();
    if(antisimmetria == true) {
        cout << "matrice 1 antisimmetrica " << endl;
    } else {
        cout << "matrice 1 non antisimmetrica " << endl;
    }

    matrice matrice_prodotto(n, n);
    matrice_prodotto = matrice1*matrice2;
    cout<< "matrice1 * matrice2: " << endl;
    matrice_prodotto.stampa();
    cout << endl;


    matrice copia(n-1, n);
    copia = matrice1.elimina_riga_copia(1);
    cout << "matrice1 senza una riga: " << endl;
    copia.stampa();

   matrice copia_colonna(n, n-1);
   copia_colonna = matrice1.elimina_colonna_copia(1);
   cout << "matrice1 senza una colonna: " << endl;
   copia_colonna.stampa();

   matrice trasposta(n, n);
   trasposta = matrice1.calcola_trasposta_copia();
   cout << "traposta della matrice1: " << endl;
   trasposta.stampa();

   return 0;
}
