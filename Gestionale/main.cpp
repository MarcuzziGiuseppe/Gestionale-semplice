/*
 * Marcuzzi Giuseppe
 * marcuzzi.giuseppe10@gmail.com
 * TO DO:
 * --> fare le 3 voci del menù
 * --> ricordasi di dire che quando si inserisce una marca non bisogna mettre spazi
*/

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <time.h>
#include <vector>

using namespace std;

#define marcheFile "marche.txt"


// funzioni "inutili"
void fermaStampa();
void clearScreen();
int randomNumber(int max, int min);

// gestione file
bool controlloDeiFile(string nomeFile);

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    char sceltaPlayer;
    vector<string> marche;
    if (controlloDeiFile(marcheFile)==false) {
        ofstream creafile(marcheFile);
        creafile.close();
    } else {
        string temp;
        ifstream file;
        file.open(marcheFile);
        file >> temp;
        while (!file.eof()) {
            marche.push_back(temp+".txt");
            file >> temp;
        }
        file.close();

        for (size_t i = 0; i < marche.size(); i++) {
            cout << marche.at(i) << endl;
        }
        fermaStampa();
    }

    do {
        clearScreen();
        cout << "Menu'" << endl
             << "--> 1) Stampa tutti i prodotti" << endl
             << "--> 2) Inserisci un nuovo prodotto" << endl
             << "--> 3) Rimuovi quantita'" << endl
             << "--> 0) Esci dal programma" << endl
             << "Premi il numero corrispondente" << endl;
        sceltaPlayer = getch();
        clearScreen();
        switch (sceltaPlayer) {
        case '1':
            cout << "1" << endl;
            break;
        case '2':
            cout << "2" << endl;
            break;
        case '3':
            cout << "3" << endl;
            break;
        case '0':
            cout << "0" << endl;
            break;
        default:
            clearScreen();
            cout << "scelta errata" << endl;
            break;
        }
    
        // clearScreen();
        // fermaStampa();
    
    } while (sceltaPlayer!='0');
    return 0;
}

void fermaStampa() {
    // getch mi peremette di non dover premere invio dopo aver scritto ma ovviamnete prende solo il primo carattere
    cout << "Premi un tasto" << endl;
    getch();
}

void clearScreen() {
    system("cls");
}

int randomNumber(int max, int min) {
    return rand() % (max - min + 1) + min;
}

void stampaProdotti() {

}

void inserisciProdotto() {

}

void rimuoviQuantitaDaProdotto () {

}

bool controlloDeiFile(string nomeFile) {
    // ritorna true se il file esiste altrimenti ritorna false
    ifstream file;
    file.open(nomeFile);
    if (file) {
        file.close();
        return true;
    }
    file.close();
    return false;
}
