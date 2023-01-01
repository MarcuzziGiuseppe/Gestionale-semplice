/*
 * Marcuzzi Giuseppe
 * marcuzzi.giuseppe10@gmail.com
 * 01/01/2023
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
#include <algorithm>

using namespace std;

#define startTag "<"
#define endTag "/>\n"
#define marcheFile "marche.txt"

// funzioni "inutili"
void fermaStampa();
void clearScreen();
int randomNumber(int max, int min);

// gestione file
bool controlloDeiFile(string nomeFile);

// gestione prodotti
void stampaProdotti(vector<string> marche);
void inserisciProdotto(vector<string> *marche); // ci sto lavorando
void rimuoviQuantitaDaProdotto (vector<string> *marche);
void infoProdotto (vector<string> *marche);

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    char sceltaPlayer;
    vector<string> marche;
    if (controlloDeiFile(marcheFile)==false) {
        ofstream creafile(marcheFile);
        creafile.close();
    } else {
        string temp;
        ifstream file(marcheFile);
        file >> temp;
        while (!file.eof()) {
            marche.push_back(temp+".txt");
            file >> temp;
        }
        file.close();
    }

    do {
        clearScreen();
        cout << "Menu'" << endl
             << "--> 1) Stampa tutti i prodotti" << endl
             << "--> 2) Inserisci un nuovo prodotto o aumenta la quantita' di uno gia' ppresente" << endl
             << "--> 3) Rimuovi quantita'" << endl
             << "--> 4) Informazioni riguardo ad un prodotto in particolare" << endl
             << "--> 0) Esci dal programma" << endl
             << "Premi il numero corrispondente" << endl;
        sceltaPlayer = getch();
        clearScreen();
        switch (sceltaPlayer) {
        case '1':
            stampaProdotti(marche);
            break;
        case '2':
            inserisciProdotto(&marche);
            break;
        case '3':
            rimuoviQuantitaDaProdotto(&marche);
            break;
        case '4':
            infoProdotto(&marche);
            break;
        case '0':
            break;
        default:
            clearScreen();
            cout << "Scelta errata" << endl;
            fermaStampa();
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

void stampaProdotti(vector<string> marche) {
    // stampa tutti i prodotti di tutte le marche (suddivisi per marca)
    cout << "Vuoi stampare tutti i prodotti o solo i prodotti di una marca in particolare?" << endl
         << "--> 1) Tutti" << endl
         << "--> 2) Solo una marca" << endl;
    char inputUtente = getch();
    if (inputUtente == '1') {
        // stampo tutti i prodotti
    } else {
        
    }
    
    
    
    
    cout << endl << "Funizone Terminata" << endl;
    fermaStampa();
}

void inserisciProdotto(vector<string> *marche) {
    // inserisce un prodotto di una marca o ne aggiunge una certa quantità
    string temp;
    cout << "Di quale marca vuoi inserire un prodotto?" << endl
         << "(ti ricordo di NON inserire spazi nel nome della marca)" << endl;
    cin >> temp;
    if (find(marche->begin(), marche->end(), temp+".txt") != marche->end()) {
        // marca esistente
        cout << "Marca Trovata" << endl;
        fermaStampa();
    } else {
        // marca non esistente
        // vuole inserirla? Si, NO 
        // se si la inseriamo e andimao avanti se no lo facciamo tornare al menù principale
        clearScreen();
        cout << "Marca non trovata, la marca inserita e': " << temp << endl
             << "Vuoi inserirla?: " << endl
             << "--> 1) Si" << endl
             << "--> 2) No" << endl
             << "Premi il numero corrispondente" << endl;
        char scelta = getch();
        if (scelta == '1') {
            // inserisco la marca
            ofstream creafile(marcheFile, ios::app);
            creafile << temp + "\n";
            creafile.close();
            marche->push_back(temp+".txt");
            creafile.open(marche->back());
            creafile.close();
        } else {
            return;
        }
    }
    // inserisco gli ulteriori Dati nel seguente ordine: (come viene visualizzato nel file)
    // <codiceProdotto
    // marca del prodotto
    // codiceProdotto
    // quantità del prodotto
    // descrizioneDelProdotto
    // \>\n
    clearScreen();
    cout << "Inserisci il codice del prodotto" << endl
         << "Il codice deve essere un numero" << endl;
    int codiceProdotto;
    cin >> codiceProdotto;
    // controllo se esiste il prodotto
    ofstream inserisciDti(temp + ".txt", ios::app);
    
    inserisciDti.close();

    cout << endl << "Funizone Terminata" << endl;
    fermaStampa();
}

void rimuoviQuantitaDaProdotto (vector<string> *marche) {
    // rimuove una certa quantità da un prodotto
    cout << "3" << endl;
    fermaStampa();
}

void infoProdotto (vector<string> *marche) {
    // mi stampa delle informazioni riguardo ad un prodotto in particolare
    cout << "4" << endl;
    fermaStampa();
}

bool controlloDeiFile(string nomeFile) {
    // ritorna true se il file esiste altrimenti ritorna false
    ifstream file(nomeFile);
    if (file) {
        file.close();
        return true;
    }
    file.close();
    return false;
}
