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
		vector<vector<vector<char>>> karty;  //1. wymiar wektora - rzêdy, 2. wymiar wektora - kokumny, 3. wymiar wektora - 2 znaki 
		int rozmiar;                         //Maksymalnie 99
		int iloscOdgadnietych = 0;
		bool turaGracza1 = true;             //true jeœli tura pierwszego gracza, przechowujemy tu po za³adowaniu z pliku
		int odkryte1 = 0, odkryte2 = 0;      //Iloœæ kart odkrytych przez gracza 1 i gracza2

	public:
		explicit Plansza();                                                            //Tylko po to, aby nie trzeba by³o podawaæ parametrów przy deklaracji zmiennej
		Plansza(int rozmiar, bool losujKarty = true, bool pokazKarty = false);         //Zape³nianie znakami X
		Plansza(int rozmiar, vector<vector<vector<char>>> k, bool pokazKarty = false); //Przez rozmiar rozumiemy iloœæ kart w jednym rzêdzie (w kolumnie jest oczywiœcie taka sama), natomiast rozmiar wektora wynosi 2 * rozmiar + 2, albowiem dodajemy znaki -, | oraz numery kolumn/rzêdów
		Plansza(string src);                                                           //£adowanie z pliku
		Plansza operator=(Plansza);												       

		void losujKarty();
		std::string doTekstu(bool turaGracza1);
		bool odkryjKarte(int rzad, int kol);   //Zwraca true gdy mo¿na odkryæ kartê, czyli gdy nie jest jeszcze odkryta
		bool zakryjKarte(int rzad, int kol);   //Zwraca true gdy mo¿na zakryæ kartê, czyli gdy nie jest jeszcze zakryta
		bool porownajKarty(int rzad1, int kol1, int rzad2, int kol2);    //Sprawdza czy karty s¹ sobie równe
		void wypisz(int kolor = 7, vector<vector<int>> wyroznione = {}, int kolorWyroznienia = 7);  //Kolor ustawiamy dla wszystkich znaków poza odkrytymi kartami, mo¿emy wybraæ karty które bêd¹ innego koloru (wyroznione, kolorWyroznienia), gdzie wyroznione to pozycja karty
		void zapisz(bool turaGracza1, bool blednaNazwa = false);   //Zapis do pliku, zwraca true jeœli uda³o siê zapisaæ

		int getRozmiar();
		int getIloscOdgadnietych();
		bool getTuraGracza();              //Zwraca true jeœli tura gracza 1  
		int getOdkryte(unsigned int num);  //Zwraca iloœæ odkrytych kart gracza num
		void zwiekszIloscOdgadnietych(unsigned int n);                //Zwiêkszamy iloœæ odgadnietych o n
		void zwiekszIloscOdkrytych(unsigned int num, unsigned int n); //Zwiêkszamy iloœæ odkrytych gracza num o n
};