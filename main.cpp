#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

//#include "szyfr.h"
//#include "liczaca.h"

using namespace std;

// Klasa
class litera {
private:
    char znak;
    int* kody;
    int dlugosc;
public:
    litera(char, int*, int);
    ~litera();
    void setZnak(char z);
    void setDlugosc(int n);
    void setKody (int* tab);
    char getZnak ();
    char zwrocZnak(int kod);
    int getDlugosc();
    int* getKod();
    int zwrocKod();
};

// Deklaracje
char odkodujZnak(int kod, litera* kolekcja, int dlugosc);
string zakoduj(string tekst, litera* klucz, int dlugosc);
string odkoduj(string tekst, litera* klucz, int dlugosc);
int* powieksz (int* tab, int rozmiar, int n);
int* zrobTablice(string tekst);
litera* baza(int alfabet);

int main() {
    srand (time(NULL));
    int alfabet = 26;
    litera* klucz = baza(alfabet);
    int i, j;

    /*
    for (i = 0; i < alfabet; i++) {
        cout << "\nLiterze: " << klucz[i].getZnak() << " odpowiadaja kody: ";
        for (j = 0; j < klucz[i].getDlugosc(); j++) {
            cout << klucz[i].getKod()[j] << " ";
        }
    }
    */

    string tekst2;
    cout << "Podaj tekst do zaszyfrowania: "; cin >> tekst2;
    //cout << "Podaj klucz: "; cin >> klucz2;

    string tekst = "24 114 64 78 73 82 15 10 57 86 104 46 20 10 121 37 112 80 113 41 33 10 64 78 118";
    string odkodowany = odkoduj(tekst, klucz, alfabet);

    string zakodowany = zakoduj(tekst2, klucz, alfabet);
    cout << "Odkodowany tekst: " << odkodowany << ".\n";
    cout << "Zakodowany tekst: " << zakodowany << ".\n";
    // Danke vom Berg.
    return 0;
}

    litera::litera(char znak = 0, int* tab = 0, int n = 0) {
        setZnak(znak);
        setDlugosc(n);
        setKody(tab);
    }

    litera::~litera(){
        delete kody;
    }

    void litera::setZnak(char z) {
        znak = z;
    }

    void litera::setDlugosc(int n) {
        dlugosc = n;
    }

    void litera::setKody (int* tab) {
        kody = new int [dlugosc];
        int i = 0;
        for (i = 0; i < dlugosc; i++) {
            kody[i] = tab[i+1];
        }
    }

    char litera::getZnak() {
        return znak;
    }

    char litera::zwrocZnak(int kod) {
        int i = 0;
        char zwrot = 0;
        for (i = 0; i < dlugosc; i++) {
            if (kod == kody[i]) {
                zwrot = znak+32;
                break;
            }
        }
        return zwrot;
    }

    int litera::getDlugosc() {
        return dlugosc;
    }

    int* litera::getKod() {
        return kody;
    }

    int litera::zwrocKod() {
        int s = rand()%(dlugosc);
        return kody[s];
    }

    char odkodujZnak(int kod, litera* kolekcja, int dlugosc) {
        char zwrot = 0;
        int i = 0;
        while (zwrot == 0 && i != 26) {
            for (i = 0; i < dlugosc; i++) {
                zwrot = kolekcja[i].zwrocZnak(kod);
                if (zwrot != 0) {
                    i = 26;
                    break;
                }
            }
        }
        return zwrot;
    }

    // dlugosc = 26 = alfabet !!!
    string odkoduj(string tekst, litera* kolekcja, int dlugosc) {
        string kot = ""; // perski
        int i = 0;
        int* kody = zrobTablice(tekst);
        int wielkosc = kody[0];
        for (i = 1; i <= wielkosc; i++) {
            kot += odkodujZnak(kody[i], kolekcja, dlugosc);
        }
        return kot;
    }

    string zakoduj(string tekst, litera* klucz, int dlugosc) {
        int i = 0;
        char znak;
        int* kody;
        int liczba;
        int temp;
        string slowo = "";
        string zwrot = "";
        while (tekst[i]) { //|| tekst[i] != 32) {
            znak = tekst[i];
            cout << znak << " = ";;
            if ((znak <= 90 && znak >= 65 ) || (znak <= 122 && znak >= 97)) {
                if (znak <= 122 && znak >= 97) {
                    znak-=32;
                }
            znak-=65; //indeks
            liczba = klucz[znak].zwrocKod();
            cout << liczba << "\n";
            if(liczba / 100) {
                slowo += char((liczba / 100) + 48);
            }

            if(((liczba+100)%100) / 10) {
                slowo += char(((liczba+100)%100) / 10 + 48);
            } else if (liczba > 100) {
                slowo += char(48);
            } // jezeli 0 jest na 2 miejscu

            slowo += char(((liczba+10) % 10) + 48);
            zwrot+=slowo;
            zwrot+=" ";
            slowo = "";
            }
            i++;
        }
        return zwrot;
    }

    int* powieksz (int* tab, int rozmiar) {
        int* tab2 = new int [rozmiar+1];
        for (int i = 0; i < rozmiar; i++) {
            tab2[i] = tab[i];
        }
        free (tab);
        //tab = tab2;
        return tab2;
    }

    int* zrobTablice(string tekst) {
        int i = 0;
        int j = 0;
        int* tab = new int [1];
        int licznik = 0;
        int wielkosc = 0;
        int suma = 0;
        while(tekst[i] || licznik) {
            if(tekst[i] >= 48 && tekst[i] <= 57) {
                licznik++;
            } else if (licznik) {
                for (j = licznik; j > 0; j--) {
                    suma += (tekst[i-j]-48)*pow(10,(j-1));
                }
                if (suma > 98) {suma++;} // disclaimer
                licznik = 0;
                wielkosc++;
                tab = powieksz(tab, wielkosc);
                tab[wielkosc] = suma;
                suma = 0;
            }
            i++;
        }
        tab[0] = wielkosc;
        return tab;
    }


litera* baza(int alfabet) {
    ifstream plik;
    litera* kolekcja = 0;
    plik.open("tekst.txt", std::ios::in | std::ios::out );
    if(plik.good() == true ) {
        cout << "Wczytano plik.";
        // Wczytywanie pliku
        string temp;
        int i = 0;
        int j = 0;
        int* tablica;
        kolekcja = new litera [alfabet];
        while(!plik.eof()) {
	        getline(plik, temp);
            tablica = zrobTablice(temp);
            kolekcja[i].setDlugosc(tablica[0]);
            kolekcja[i].setKody(tablica);
            kolekcja[i].setZnak(temp[0]);

            i++;
        }
        plik.close();
    }
    return kolekcja;
}
