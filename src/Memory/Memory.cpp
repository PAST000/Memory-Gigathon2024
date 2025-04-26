#include <iostream>
#include <string>
#include <vector>
#include <locale.h>
#include <conio.h>
#include "Plansza.h"
#include "funkcjePoboczne.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;

Plansza plansza;
bool turaGracza1; //true - tura gracza 1, false - tura gracza 2
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);       //Do ustawienia koloru

vector<int> wyborKarty(Plansza plansza, bool blednyWybor, bool drugiWybor, vector<int> pozycja1, bool taSama) {
    SetConsoleTitle(L"Memory");
    if (blednyWybor) cout << "Wybrano nie prawid�ow� warto��." << endl;
    if (taSama) cout << "Druga pozycja musi by� r�na od pierwszej." << endl;

    vector<int> pozycja = vector<int>(2, -1);
    string rzad, kol; //Tymczasowe tekstu b�d�cego numerem rz�du i kolumny

    if(!drugiWybor)   //Mo�liwo�� zapisu dajemy tylko przy pierwszej karcie
        cout << "Podaj rz�d i kolumn� karty w formacie \"NumerRz�du NumerKolumny\". Naci�nij \'Z\', aby zapisa� gr�." << endl;
    else 
        cout << "Podaj rz�d i kolumn� drugiej karty w formacie \"NumerRz�du NumerKolumny\"." << endl;

    cin >> rzad;
    if (rzad.size() > 0 && !drugiWybor && (rzad[0] == 'z' || rzad[0] == 'Z')) {   //Zapisywanie 
        plansza.zapisz(turaGracza1);
        cout << "Naci�nij klawisz Escape aby wyj�� lub dowolny przycisk aby gra� dalej." << endl;
        if (_getch() == 27) return pozycja;   //Je�li chcemy wyj�� to zwracamy wektor z warto�ciami -1
        else return wyborKarty(plansza, blednyWybor, drugiWybor, pozycja1, taSama);
    }
    else {
        cin >> kol;
        try {
            pozycja[0] = stoi(rzad);
            pozycja[1] = stoi(kol);
            if (pozycja[0] < 1 || pozycja[1] < 1) throw("Zbyt ma�a warto��");
            if (pozycja[0] > plansza.getRozmiar() || pozycja[1] > plansza.getRozmiar()) throw("Zbyt du�a warto��");
        }
        catch (...) { return wyborKarty(plansza, true, drugiWybor, pozycja1); }
    }
    if (pozycja1.size() >= 2)    //Sprawdzamy czy podany wektor ma minimum 2 elementy, aby nie spowodowa� b��du dost�pu
        if (pozycja[0] == pozycja1[0] + 1 && pozycja[1] == pozycja1[1] + 1) return wyborKarty(plansza, blednyWybor, drugiWybor, pozycja1, true);
    return pozycja;
}

vector<int> wyborPozycji(Plansza& plansza, bool druga, vector<int> pierwsza = {}, bool odkryta = false) {  //pierwsza - pozycja wybrana jako pierwsza, w przypadku wybierania drugiej pozycji
    SetConsoleTitle(L"Memory");
    vector<int> pozycja = vector<int>(2, -1);  //Przechowywanie wybranego rz�du i kolumny karty
    if (odkryta) cout << "Ta karta ju� jest odkryta." << endl;

    pozycja = wyborKarty(plansza, false, druga, pierwsza);
    if (pozycja[0] == -1) return pozycja;
    pozycja[0]--;   //Podawana pozycja jest z zakresu 1 - rozmiar, wi�c musimy odj�c 1
    pozycja[1]--;   //
    if (!plansza.odkryjKarte(pozycja[0], pozycja[1])) return wyborPozycji(plansza, druga, pierwsza, true);
    system("cls");
    if (pierwsza.empty()) {
        plansza.wypisz((turaGracza1 ? 9 : 12), vector<vector<int>>(1, pozycja), 5);
    }
    else {
        vector<vector<int>> zlaczone = vector<vector<int>>(2, pierwsza);
        zlaczone[1] = pozycja;
        plansza.wypisz((turaGracza1 ? 9 : 12), zlaczone, 5);
    }
    return pozycja;
}

void gra() {  //W oddzielnej funkcji aby mo�na by�o u�y� rekurencji do �adowania nowej gry
    SetConsoleTitle(L"Memory");
    if (wyborOpcji(false) == '2') wyborNazwyPliku(plansza); 
    else plansza = Plansza(wyborRozmiaru(false), true, false);
    turaGracza1 = plansza.getTuraGracza();
    vector<vector<int>> pozycje = vector<vector<int>>(2, vector<int>(2));  //Przechowywanie wybranych rz�d�w i kolumn karty

    if (plansza.getIloscOdgadnietych() < (plansza.getRozmiar() % 2 == 1 ? plansza.getRozmiar() * plansza.getRozmiar() - 1 : plansza.getRozmiar() * plansza.getRozmiar())) { //Sprawdzamy czy na pewno rozmiar jest poprawny
        do {
            system("cls");
            plansza.wypisz((turaGracza1 ? 9 : 12));
            cout << "Tura gracza " << (turaGracza1 ? '1' : '2') << endl;

            pozycje[0] = wyborPozycji(plansza, false);
            if (pozycje[0][0] == -1) return;
            pozycje[1] = wyborPozycji(plansza, true, pozycje[0]);
            if (pozycje[1][0] == -1) return;

            cout << "Naci�nij dowolny klawisz aby przej�� do nast�pnej tury." << endl;
            _getch();

            if (!plansza.porownajKarty(pozycje[0][0], pozycje[0][1], pozycje[1][0], pozycje[1][1])) {  //Je�li karty s� r�ne to je zakrywamy
                turaGracza1 = !turaGracza1;                                                            //Zmiana gracza kt�ry obecnie ma ture
                plansza.zakryjKarte(pozycje[0][0], pozycje[0][1]);
                plansza.zakryjKarte(pozycje[1][0], pozycje[1][1]);
            }
            else {
                plansza.zwiekszIloscOdgadnietych(2); //Je�li karty s� sobie r�wne to zwi�kszamy ilo�� odgadnietych o 2
                plansza.zwiekszIloscOdkrytych((turaGracza1 ? 1 : 2), 2);
            }
        } while (plansza.getIloscOdgadnietych() < (plansza.getRozmiar() % 2 == 1 ? plansza.getRozmiar() * plansza.getRozmiar() - 1 : plansza.getRozmiar() * plansza.getRozmiar()));

        SetConsoleTextAttribute(hConsole, 7);
        if (plansza.getOdkryte(1) == plansza.getOdkryte(2)) {
            cout << "Remis!" << endl;
            cout << "Obydwaj gracze odkryli po " << plansza.getOdkryte(1) << " kart." << endl;
        }
        else {
            cout << "Gratulacje! Wygra� gracz ";
            SetConsoleTextAttribute(hConsole, (plansza.getOdkryte(1) > plansza.getOdkryte(2) ? 9 : 12));  //Ustawiamy kolor dla cyfry symbolizuj�cej numer gracza
            cout << (plansza.getOdkryte(1) > plansza.getOdkryte(2) ? '1' : '2') << endl;
            SetConsoleTextAttribute(hConsole, 7);
            cout << "Odkrywaj�c " << (plansza.getOdkryte(1) > plansza.getOdkryte(2) ? plansza.getOdkryte(1) : plansza.getOdkryte(2)) << " kart." << endl;
        }
        cout << "Naci�nij klawisz Escape aby wyj�� lud dowolny przycisk aby zagra� jeszcze raz." << endl;
        if (_getch() == 27) return;
        else gra();
    }
}

int main() {
    SetConsoleTitle(L"Memory");
    setlocale(LC_CTYPE, "Polish");  //Ustawienie polskich znak�w w konsoli
    gra();
    return 0;
}
