#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "Plansza.h"

void wyborNazwyPliku(Plansza& plansza, bool blednywybor = false);
char wyborOpcji(bool blednyWybor);
int wyborRozmiaru(bool blednyWybor);
std::vector<int> wyborKarty(Plansza plansza, bool blednyWybor, bool drugiWybor = false, vector<int> pozycja1 = {}, bool taSama = false);  //Zwracany wektor to wybrana pozycja karty 
vector<string> dzielZnakiem(string str, char c);    //Dzieli ci¹g znaków weg³ug wybranego znaku
int znajdzWWektorze(vector<int> wektor, int szukana);
bool znajdzWWyroznionych(vector<vector<int>> wyroznione, int rzad, int kol);