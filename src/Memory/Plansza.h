#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>
using std::vector;
using std::string;

class Plansza {
	private:
		vector<vector<char>> plansza;
		vector<vector<vector<char>>> karty;  //1. wymiar wektora - rz�dy, 2. wymiar wektora - kokumny, 3. wymiar wektora - 2 znaki 
		int rozmiar;                         //Maksymalnie 99
		int iloscOdgadnietych = 0;
		bool turaGracza1 = true;             //true je�li tura pierwszego gracza, przechowujemy tu po za�adowaniu z pliku
		int odkryte1 = 0, odkryte2 = 0;      //Ilo�� kart odkrytych przez gracza 1 i gracza2

	public:
		explicit Plansza();                                                            //Tylko po to, aby nie trzeba by�o podawa� parametr�w przy deklaracji zmiennej
		Plansza(int rozmiar, bool losujKarty = true, bool pokazKarty = false);         //Zape�nianie znakami X
		Plansza(int rozmiar, vector<vector<vector<char>>> k, bool pokazKarty = false); //Przez rozmiar rozumiemy ilo�� kart w jednym rz�dzie (w kolumnie jest oczywi�cie taka sama), natomiast rozmiar wektora wynosi 2 * rozmiar + 2, albowiem dodajemy znaki -, | oraz numery kolumn/rz�d�w
		Plansza(string src);                                                           //�adowanie z pliku
		Plansza operator=(Plansza);												       

		void losujKarty();
		std::string doTekstu(bool turaGracza1);
		bool odkryjKarte(int rzad, int kol);   //Zwraca true gdy mo�na odkry� kart�, czyli gdy nie jest jeszcze odkryta
		bool zakryjKarte(int rzad, int kol);   //Zwraca true gdy mo�na zakry� kart�, czyli gdy nie jest jeszcze zakryta
		bool porownajKarty(int rzad1, int kol1, int rzad2, int kol2);    //Sprawdza czy karty s� sobie r�wne
		void wypisz(int kolor = 7, vector<vector<int>> wyroznione = {}, int kolorWyroznienia = 7);  //Kolor ustawiamy dla wszystkich znak�w poza odkrytymi kartami, mo�emy wybra� karty kt�re b�d� innego koloru (wyroznione, kolorWyroznienia), gdzie wyroznione to pozycja karty
		void zapisz(bool turaGracza1, bool blednaNazwa = false);   //Zapis do pliku, zwraca true je�li uda�o si� zapisa�

		int getRozmiar();
		int getIloscOdgadnietych();
		bool getTuraGracza();              //Zwraca true je�li tura gracza 1  
		int getOdkryte(unsigned int num);  //Zwraca ilo�� odkrytych kart gracza num
		void zwiekszIloscOdgadnietych(unsigned int n);                //Zwi�kszamy ilo�� odgadnietych o n
		void zwiekszIloscOdkrytych(unsigned int num, unsigned int n); //Zwi�kszamy ilo�� odkrytych gracza num o n
};