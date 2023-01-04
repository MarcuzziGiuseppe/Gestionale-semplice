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
#include <filesystem>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

#define startTag "<"
#define endTag "/>\n"
#define marcheFile "marche.txt"
#define fileTemp "temp.txt"

vector<string> ordineNelFile = {"Codice: ","Quantita': ", "Descrizione: "};

// funzioni "inutili"
void fermaStampa();
void clearScreen();
int randomNumber(int max, int min);

// gestione file
bool controlloDeiFile(string nomeFile);

// gestione prodotti
void stampaProdotti(vector<string> marche); // ci sto lavorandos
void inserisciProdotto(vector<string> *marche, bool togliere);
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
            // << "--> 4) Informazioni riguardo ad un prodotto in particolare" << endl
             << "--> 0) Esci dal programma" << endl
             << "Premi il numero corrispondente" << endl;
        sceltaPlayer = getch();
        clearScreen();
        switch (sceltaPlayer) {
        case '1':
            stampaProdotti(marche);
            break;
        case '2':
            inserisciProdotto(&marche, false);
            break;
        case '3':
            inserisciProdotto(&marche, true);
            break;
        // case '4':
        //     infoProdotto(&marche);
        //     break;
        case '0':
            break;
        default:
            clearScreen();
            cout << "Scelta errata" << endl;
            fermaStampa();
            break;
        }

        //clearScreen();
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
    system("@clear||cls");
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
    clearScreen();
    if (inputUtente == '1') {
        // stampo tutti i prodotti
        for (size_t i = 0; i < marche.size(); i++) {
            cout << "Marca: " << marche.at(i).substr(0, marche.at(i).find(".")) << endl;
            string temp;
            ifstream file (marche.at(i));
            getline(file, temp);
            while (!file.eof()) {
                for (size_t i = 0; i < 4; i++) {
                    getline(file, temp);
                    if (temp != "/>") {
                        if (temp == "a") {
                            temp = "";
                        }
                        cout << ordineNelFile.at(i);
                        cout << temp + " ";
                    }
                }
                cout << endl;
                getline(file, temp);
            }
            file.close();
            cout << endl;
        }
    } else {
        string marca;
        // stampo tutti i prodotti di una marca esistente
        cout << "Quale marca stai cercando?" << endl
             << "(ti ricordo di NON inserire spazi nel nome della marca)" << endl;
        cin >> marca;
        if (find(marche.begin(), marche.end(), marca+".txt") != marche.end()) {
            // marca esistente
            string temp;
            ifstream file (marca + ".txt");
            getline(file, temp);
            while (!file.eof()) {
                for (size_t i = 0; i < 4; i++) {
                    getline(file, temp);
                    if (temp != "/>") {
                        if (temp == "a") {
                            temp = "";
                        }
                        cout << ordineNelFile.at(i);
                        cout << temp + " ";
                    }
                }
                cout << endl;
                getline(file, temp);
            }
            file.close();
        } else {
            cout << "La marca non esiste" << endl;
            fermaStampa();
            return;
        }
    }
    fermaStampa();
}

/// @brief Questa funzione mi serve per inserire o togliere un certà quantità da un prodotto Inoltere mi fa altri controlli come verificare se la marca è già presente, se non è presente la crea e ti chiedere di inserire un prodotto se sia la marca che il codice esistno chiede di quanto bisogna aggiungere o togliere la quantità di un determinato Prodotto
/// @param marche è un vector che tiene traccia di tutte le marche che sono state inserite (le marche sono presenti nel file marche.txt)
/// @param togliere mi serve per sapere se voglio togliere o aggiungere un prodotto false = aggiungo una quantità true = tolgo una quantità
void inserisciProdotto(vector<string> *marche, bool togliere) {
    // inserisce un prodotto di una marca o ne aggiunge una certa quantità
    string temp;
    if (togliere==false) {
        cout << "Di quale marca vuoi inserire una quantita'?" << endl;
    } else {
        cout << "Di quale marca vuoi togliere una quantita'?" << endl;
    }
    cout << "(ti ricordo di NON inserire spazi nel nome della marca)" << endl;
    cin >> temp;
    if (find(marche->begin(), marche->end(), temp+".txt") != marche->end()) {
        // marca esistente
        // cout << "Marca Trovata" << endl;
        // fermaStampa();
    } else {
        if (togliere==true) {
            cout << "Marca non trovata" <<  endl;
            fermaStampa();
            return;
        }
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
    string marca = temp;
    clearScreen();
    cout << "Inserisci il codice del prodotto" << endl
         << "Il codice deve essere un numero" << endl;
    int codiceProdotto;
    cin >> codiceProdotto;
    // controllo se esiste il prodotto
    bool codiceTrovato = false;
    ifstream file(marca+".txt");
    file >> temp;
    while (!file.eof() && codiceTrovato==false) {
        if (temp == startTag+to_string(codiceProdotto)) {
            codiceTrovato=true;
        }
        file >> temp;
    }
    file.close();

    int quantita = 0;
    if (codiceTrovato==false) {
        if (togliere==true) {
            cout << "Codice non trovato" <<  endl;
            fermaStampa();
            return;
        }
        ofstream inserisciDti(marca + ".txt", ios::app);
        inserisciDti << startTag + to_string(codiceProdotto);
        inserisciDti << "\n";
        inserisciDti << codiceProdotto;
        inserisciDti << "\n";
        cout << "Inserisci la quantita'" << endl;
        cin >> quantita;
        inserisciDti << quantita; // quantità
        inserisciDti << "\n";
        cout << "Inserisci una descrizione: " << endl
             << "Se non hai una descrizione scrivi a" << endl;
        getline(cin >> ws, temp);
        inserisciDti << temp;
        inserisciDti << "\n";
        inserisciDti << endTag;
        inserisciDti.close();
    } else {
        // riscrivo il file in un file temporaneo
        // fin quando non trovo il valore che devo modificare
        // lo modifico e continuo a scrivere cosa mi interessa
        // poi cancello il file temporaneo
        if (togliere==true) {
            cout << "Inseriscimi di quando vuoi togliere" << endl;
        } else {
            cout << "Inseriscimi di quando vuoi aumentare" << endl;
        }
        cin >> quantita;
        if (togliere==true) {
            quantita = quantita * -1;
        }
        string stringaLetta;
        bool toltoPiuDelMassimo = false;
        ifstream fileDaLeggere(marca + ".txt", ios::in);
        ofstream fileTemporaneo(fileTemp);
        fileDaLeggere >> stringaLetta;
        codiceTrovato = false;
        while (!fileDaLeggere.eof()) {
            if (codiceTrovato==true) {
                fileTemporaneo << stringaLetta;
                fileTemporaneo << "\n";
                fileDaLeggere >> stringaLetta;
                temp = to_string(stoi(stringaLetta) + quantita);
                if (stoi(temp) < 0) {
                    toltoPiuDelMassimo = true;
                    break;
                }
                stringaLetta = temp;
                codiceTrovato=false;
            }
            if (stringaLetta == (startTag+to_string(codiceProdotto))) {
                codiceTrovato=true;
            }
            fileTemporaneo << stringaLetta;
            fileTemporaneo << "\n";
            fileDaLeggere >> stringaLetta;
        }
        fileTemporaneo.close();
        fileDaLeggere.close();
        if (toltoPiuDelMassimo == true) {
            cout << "Stai cercando di togliere piu' di quanto hai" << endl;
            fermaStampa();
            return;
        }
        // cancello il vecchio file e rinomino il temp
        // con lo stesso nome di quello vecchio
        const char* nomeFile = (marca + ".txt").c_str();
        remove(nomeFile); // cancello i vecchio file
        rename(fileTemp, nomeFile); // rinomino il file temp con lo stesso nome della marca
    }
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
