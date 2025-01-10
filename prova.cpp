#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "riga.h"
#include "matrice.h"
using namespace std;

int main() {
    int n; //dimensioni della matrice
    cout << "inserisci le dimensioni della matrice " << endl;
    cin >> n;

    double elemento;
    matrice matrice1(n, n);
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

    double determinante = matrice1.get_determinante();
    cout << "determinante = " << determinante << endl;
    matrice inversa = matrice1.get_inversa();
    inversa.stampa();
    return 0;
}
