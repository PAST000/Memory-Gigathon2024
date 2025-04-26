#include "funkcjePoboczne.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void wyborNazwyPliku(Plansza& plansza, bool blednywybor){
    if (blednywybor) cout << "Podano nieprawid�ow� nazw� pliku." << endl;
    string nazwaPliku;

    cout << "Podaj nazw� pliku z kt�rego mam za�adowa� gr�." << endl;
    getline(cin, nazwaPliku);
    if (nazwaPliku.size() < 1 || nazwaPliku.find('\"') != string::npos|| nazwaPliku.find('\\') != string::npos || nazwaPliku.find('/') != string::npos || 
        nazwaPliku.find(':') != string::npos || nazwaPliku.find('|') != string::npos || nazwaPliku.find('<') != string::npos 
        || nazwaPliku.find('>') != string::npos || nazwaPliku.find('*') != string::npos || nazwaPliku.find('?') != string::npos)   //Sprawdzamy czy nazwa pliku zgadza si� z wymogami Windows'a
        return wyborNazwyPliku(plansza, true);
    plansza = Plansza(nazwaPliku);
}

char wyborOpcji(bool blednyWybor) {
    system("cls");

    cout << "Memory - Adam Stachowicz 2024\n\n";
    if (blednyWybor) cout << "B��dny wyb�r opcji\n";
    cout << "Co chcesz zrobi�?\n";
    cout << "[1] Nowa gra\n";
    cout << "[2] Wczytaj plik\n";
    cout << "Opcja: ";
    char opcja = _getch();
    cout << std::endl;

    if (opcja != '1' && opcja != '2') return wyborOpcji(true);
    else return opcja;
}

int wyborRozmiaru(bool blednyWybor) {
    system("cls");
    int rozmiar;
    string tmpRozmiar; //Tymczasowe przechowywanie wprowadzonego rozmiaru

    if (blednyWybor) cout << "Wybrano nie prawid�ow� warto��.\n";
    cout << "Wprowad� rozmiar planszy: ";
    cin >> tmpRozmiar;

    try {
        rozmiar = stoi(tmpRozmiar);
        if (rozmiar < 2) throw("Zbyt ma�y rozmiar");
    }
    catch (...) { return wyborRozmiaru(true); }

    if (rozmiar > 99) {
        cout << "Maksymalny rozmiar to 99. Ustawiam rozmiar na 99.";
        rozmiar = 99;
    }
    return rozmiar;
}

void wczytajZPliku(bool blednyWybor) {
    string nazwaPliku;
    cout << "Podaj nazw� pliku z kt�rego wczyta� zapis: " << endl;
    getline(cin, nazwaPliku);
}

vector<string> dzielZnakiem(string str, char c) {   //Dzieli ci�g str wed�ug znak�w c
    vector<std::string> podzielone;
    string token;
    string znak = std::string(1, c);
    size_t pos = 0;

    while ((pos = str.find(znak)) != string::npos) {
        token = str.substr(0, pos);
        podzielone.push_back(token);
        str.erase(0, pos + znak.length());
    }
    podzielone.push_back(str);
    return podzielone;
}

bool znajdzWWyroznionych(vector<vector<int>> wyroznione, int rzad, int kol) {
    if (wyroznione.size() <= 0) return false;
    for (int i = 0; i < wyroznione.size(); i++) {
        if (wyroznione[i][0] == rzad && wyroznione[i][1] == kol) return true;
    }
    return false;
}

int znajdzWWektorze(vector<int> wektor, int szukana) {
    for (int i = 0; i < wektor.size(); i++)
        if (wektor[i] == szukana) return i;
    return -1;
}