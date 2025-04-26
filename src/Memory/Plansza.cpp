#include "Plansza.h"
#include "funkcjePoboczne.h"
using std::string;
using std::vector;
using std::fstream;
using std::cout;
using std::cin;
using std::endl;

Plansza::Plansza(){}

Plansza::Plansza(int rozm, bool losujKarty, bool pokazKarty) {
    this->rozmiar = rozm;
    this->plansza = vector<vector<char>>(2 * rozm + 2, vector<char>(3 * rozm + 3, ' '));
    this->losujKarty();

    for (int i = 1; i <= rozm; i++) {               // Ustawiamy numer kolumny 
        plansza[0][i * 3] = char(i / 10) + '0';     // Ustawiamy numer dziesi¹tek 
        plansza[0][i * 3 + 1] = char(i % 10) + '0'; // Ustawiamy numer jednoœci
    }

    for (int i = 1; i <= rozm; i++) {            // Ustawiamy numer rzêdu 
        plansza[i * 2][0] = char(i / 10) + '0';  // Ustawiamy numer dziesi¹tek 
        plansza[i * 2][1] = char(i % 10) + '0';  // Ustawiamy numer jednoœci
    }

    for (int i = 1; i < 2 * rozm + 2; i += 2)
        for (int j = 2; j < 3 * rozm + 3; j++)
            plansza[i][j] = '-';
      
    for (int i = 2; i < 3 * rozm + 3; i += 3)
        for (int j = 2; j < 2 * rozm + 1; j++)
            plansza[j][i] = '|';
   
    for (int i = 2; i < 2 * rozm + 2; i++)       // Wolne miejsca zastêpujemy znakami X lub kartami, w zale¿noœci od parametru pokazKarty
        for (int j = 2; j < 3 * rozm + 3; j++)
            if (plansza[i][j] == ' ') {
                if (pokazKarty && losujKarty) {
                    plansza[i][j] = this->karty[(i - 2) / 2][(j - 3) / 3][0];
                    if (j + 1 < 3 * rozmiar + 3)
                        plansza[i][j + 1] = this->karty[(i - 2) / 2][(j - 3) / 3][1];
                }
                else plansza[i][j] = 'X';
            }
}

Plansza::Plansza(int rozm, vector<vector<vector<char>>> k, bool pokazKarty) {
    this->rozmiar = rozm;
    this->plansza = vector<vector<char>>(2 * rozm + 2, vector<char>(3 * rozm + 3, ' '));
    this->karty = k;

    if (k.size() < rozm) {
        cout << "Zbyt ma³a iloœæ kart";
        return;
    }

    for (int i = 1; i <= rozm; i++) {               // Ustawiamy numer kolumny 
        plansza[0][i * 3] = char(i / 10) + '0';     // Ustawiamy numer dziesi¹tek 
        plansza[0][i * 3 + 1] = char(i % 10) + '0'; // Ustawiamy numer jednoœci
    }

    for (int i = 1; i <= rozm; i++) {            // Ustawiamy numer rzêdu 
        plansza[i * 2][0] = char(i / 10) + '0';  // Ustawiamy numer dziesi¹tek 
        plansza[i * 2][1] = char(i % 10) + '0';  // Ustawiamy numer jednoœci
    }

    for (int i = 1; i < 2 * rozm + 2; i += 2)
        for (int j = 2; j < 3 * rozm + 3; j++)
            plansza[i][j] = '-';

    for (int i = 2; i < 3 * rozm + 3; i += 3)
        for (int j = 2; j < 2 * rozm + 1; j++)
            plansza[j][i] = '|';

    for (int i = 2; i < 2 * rozm + 2; i++)     // Wolne miejsca zastêpujemy znakami X lub kartami, w zale¿noœci od parametru pokazKarty
        for (int j = 2; j < 3 * rozm + 3; j++)
            if (plansza[i][j] == ' ') 
                if (pokazKarty) {
                    plansza[i][j] = this->karty[(i - 2) / 2][(j - 3) / 3][0];
                    plansza[i][j + 1] = this->karty[(i - 2) / 2][(j - 3) / 3][1];
                }
                else plansza[i][j] = 'X';
}

Plansza::Plansza(string src) {
    std::ifstream plik("zapisy\\" + src + ".cfg");
    if (!plik.is_open()) {
        plik.close();
        cout << "Nie uda³o siê otworzyæ pliku." << endl;
        return;
    }
    else {
        string txt, tekstPlanszy, tekstKart;     // txt - tekst odczytany z pliku, tekstKart - karty z pliku oddzielone przecinkami
        string tekstRozmiaru, tekstOdgagnietych; // tekstRozmiaru - musimy daæ do ci¹gu albowiem mog¹ byæ 2 znaki, tekstOdgadniêtych tak samo
        string tekstOdkryte1, tekstOdkryte2;     // teksty numerów odkrytych kart
        getline(plik, txt);                                                    
        vector<string> rozdzielone = dzielZnakiem(txt, ';');

        if (rozdzielone.size() < 5 || rozdzielone[0].size() < 6 || rozdzielone[1].size() < 4 || rozdzielone[2].size() < 1 || 
            rozdzielone[3].size() < 1 || rozdzielone[4].size() < 1 || rozdzielone[5].size() < 1 || rozdzielone[6].size() < 1) {
            plik.close();
            cout << "Niew³aœciwie zapisany plik." << endl;
            return;
        }

        tekstPlanszy = rozdzielone[0];
        tekstKart = rozdzielone[1];
        tekstRozmiaru = rozdzielone[2];
        tekstOdgagnietych = rozdzielone[3];
        tekstOdkryte1 = rozdzielone[5];
        tekstOdkryte2 = rozdzielone[6];


        try {
            rozmiar = stoi(tekstRozmiaru);
            iloscOdgadnietych = stoi(tekstOdgagnietych);
            odkryte1 = stoi(tekstOdkryte1);
            odkryte2 = stoi(tekstOdkryte2);
            if (rozmiar < 2 || iloscOdgadnietych < 0 || iloscOdgadnietych > rozmiar * rozmiar || odkryte1 < 0 || odkryte2 < 0) throw("Niew³aœciwie zapisany plik.");
        }
        catch(...){
            plik.close();
            cout << "Niew³aœciwie zapisany plik." << endl;
            return;
        }

        this->plansza = vector<vector<char>>(2 * rozmiar + 2, vector<char>(3 * rozmiar + 3, ' '));
        this->karty = vector<vector<vector<char>>>(rozmiar, vector<vector<char>>(rozmiar, vector<char>(2, ' ')));
        vector<string> wierszePlanszy = dzielZnakiem(tekstPlanszy,','); // Tekst reprezentuj¹cy wiersze planszy
        vector<string> rozdzieloneKarty = dzielZnakiem(tekstKart, ','); // Tekst reprezentuj¹cy wiersze kart

        for (int i = 0; i < wierszePlanszy.size(); i++)
            for (int j = 0; j < wierszePlanszy[0].size(); j++) {
                plansza[i][j] = wierszePlanszy[i][j];
            }

        for (int i = 0; i < rozdzieloneKarty.size(); i++) {
            karty[i / rozmiar][i % rozmiar][0] = rozdzieloneKarty[i][0];
            karty[i / rozmiar][i % rozmiar][1] = rozdzieloneKarty[i][1];
        }    

        if (rozdzielone[4] == "1") turaGracza1 == true;
        else turaGracza1 == false;
    }
}

Plansza Plansza::operator=(Plansza nowa) {
	this->plansza = nowa.plansza;
    this->karty = nowa.karty;
    this->rozmiar = nowa.rozmiar;
    this->iloscOdgadnietych = nowa.getIloscOdgadnietych();
    this->turaGracza1 = nowa.getTuraGracza();
    this->odkryte1 = nowa.getOdkryte(1);
    this->odkryte2 = nowa.getOdkryte(2);
    return *this;
}

void Plansza::losujKarty() {
    this->karty.clear();
    this->karty = vector<vector<vector<char>>>(rozmiar, vector<vector<char>>(rozmiar, vector<char>(2, ' ')));

    std::srand(std::time(NULL));
    int nNumeru, nKoloru;        // Zmienne tymczasowe dla wylosowanego numeru karty i numeru koloru karty
    char numer, kolor;           // To co powy¿ej tylko skonwertowane na znak
    int indeksWolnych;           // Przechowujemy indeks wylosowanej pozycji dla wektora wolne
    int pozycjaDrugiej;          // Przechowywanie indeksu wylosowanego dla drugiej pary 

    vector<int> wolne = vector<int>(rozmiar*rozmiar, -1);    // Dla zwiêkszenia prêdkoœci zapisujemy wolne miejsca
    for (int i = 0; i < wolne.size(); i++) wolne[i] = i;

    for (int i = 0; i < rozmiar; i++)
        for (int j = 0; j < rozmiar; j++) {
            if (karty[i][j][0] != ' ') continue; // Sprawdzamy czy tu ju¿ wylosowano kartê
            nNumeru = (rand() % 13) + 1;         // Losujemy numer karty 
            nKoloru = (rand() % 4) + 1;          // Losujemy kolor karty

            if (nNumeru > 10) {
                switch (nNumeru){
                    case 11: numer = 'W'; break;
                    case 12: numer = 'Q'; break;
                    case 13: numer = 'K'; break;
                    default: numer = 'E'; break; // B³¹d
                }
            }
            else numer = (nNumeru % 10) + '0';    // Konwersja na znak, 10 zamieniamy na 0
         
            switch (nKoloru) {
                case 1: kolor = 'K'; break;   // Karo
                case 2: kolor = 'S'; break;   // Serca (Nie kier, bo K zajête)  
                case 3: kolor = 'T'; break;   // Trefl
                case 4: kolor = 'P'; break;   // Pik
                default: kolor = 'E';  break; // B³¹d
            }

            this->karty[i][j][0] = numer;    // Przypisujemy wartoœci pierwszej karcie
            this->karty[i][j][1] = kolor;
            wolne.erase(wolne.begin() + znajdzWWektorze(wolne, i * rozmiar + j), wolne.begin() + znajdzWWektorze(wolne, i * rozmiar + j) + 1); //Usuwamy obecn¹ pozycje z listy wolnych

            if (wolne.size() == 0)   // Jeœli rozmiar jest nieparzysty i dotarliœmy do ostatniej iteracji to losujemy tylko jedn¹ kartê, czyli przerywamy pêtle przed ustawieniem drugiej karty
                continue;

            indeksWolnych = rand() % wolne.size();
            pozycjaDrugiej = wolne[indeksWolnych];  // Losujemy pozycje drugiej karty
            this->karty[pozycjaDrugiej / rozmiar][pozycjaDrugiej % rozmiar][0] = numer;
            this->karty[pozycjaDrugiej / rozmiar][pozycjaDrugiej % rozmiar][1] = kolor;

            wolne.erase(wolne.begin() + indeksWolnych, wolne.begin() +  indeksWolnych + 1);  // Usuwamy wylosowanê pozycje z listy wolnych
        }
}

string Plansza::doTekstu(bool turaGracza1) {  
    string txt; 
    for (int i = 0; i < plansza.size(); i++) {
        txt += string(plansza[i].begin(), plansza[i].end()); // Dodajemy wiersze planszy
        txt += ',';                                          // Wiersze oddzielamy przecinkiem 
    }
    txt.pop_back(); // Na koñcu znajduje siê nadmiarowy przecinek który nale¿y usun¹æ
    txt += ';';     // Ca³¹ plansze oddzielamy œrednikiem od nastêpnych danych

    for (int i = 0; i < karty.size(); i++)
        for (int j = 0; j < karty[0].size(); j++) {
            txt += karty[i][j][0];  // Numer karty
            txt += karty[i][j][1];  // Kolor karty
            txt += ',';             // Karty oddzielamy przecinkiem
        }
    txt.pop_back(); // Na koñcu znajduje siê nadmiarowy przecinek który nale¿y usun¹æ
    txt += ';';
    txt += std::to_string(rozmiar);
    txt += ';';
    txt += std::to_string(iloscOdgadnietych);
    txt += ';';
    txt += (turaGracza1 ? '1' : '0');
    txt += ';';
    txt += std::to_string(odkryte1);
    txt += ';';
    txt += std::to_string(odkryte2);
    return txt;
}

bool Plansza::odkryjKarte(int rzad, int kol) {
    if (rzad >= plansza.size() || kol >= plansza[0].size() || rzad < 0 || kol < 0) return false;
    if (plansza[2 * rzad + 2][3 * kol + 3] != 'X') return false;
    if (plansza[2 * rzad + 2][3 * kol + 4] != 'X') return false;

    plansza[2 * rzad + 2][3 * kol + 3] = karty[rzad][kol][0];
    plansza[2 * rzad + 2][3 * kol + 4] = karty[rzad][kol][1];
    return true;
}

bool Plansza::zakryjKarte(int rzad, int kol) {
    if (rzad >= plansza.size() || kol >= plansza[0].size() || rzad < 0 || kol < 0) return false;
    if (plansza[2 * rzad + 2][3 * kol + 3] == 'X') return false;
    if (plansza[2 * rzad + 2][3 * kol + 4] == 'X') return false;

    plansza[2 * rzad + 2][3 * kol + 3] = 'X';
    plansza[2 * rzad + 2][3 * kol + 4] = 'X';
    return true;
}

bool Plansza::porownajKarty(int rzad1, int kol1, int rzad2, int kol2) {
    if (karty[rzad1][kol1][0] == karty[rzad2][kol2][0] && karty[rzad1][kol1][1] == karty[rzad2][kol2][1]) return true;
    else return false;
}

void Plansza::wypisz(int kolor, vector<vector<int>> wyroznione, int kolorWyroznienia) {
    if (this->plansza.size() <= 2) return;
    if (this->plansza[0].size() <= 2) return;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);       // Do ustawienia koloru
    for (int i = 0; i < this->plansza.size(); i++) {         // Wiersz planszy
        for (int j = 0; j < this->plansza[0].size(); j++) {  // Kolumna planszy
            if (i >= 2 && j >= 3 && plansza[i][j] != '-' && plansza[i][j] != '|' && plansza[i][j] != 'X')  // Sprawdzamy czy obecne pole to karta
                if (znajdzWWyroznionych(wyroznione, (i - 2) / 2, (j - 3) / 3))                             // Jeœli karta jest w wyroznionych zmieniamy na kolorWyroznienia
                    SetConsoleTextAttribute(hConsole, kolorWyroznienia);
                else
                    SetConsoleTextAttribute(hConsole, 7);
            else
                SetConsoleTextAttribute(hConsole, kolor);
            cout << this->plansza[i][j];
        }
        cout << endl;
    }
}

void Plansza::zapisz(bool turaGracza1, bool blednaNazwa) {
    std::string nazwaPliku;
    if (blednaNazwa) cout << "Podano b³êdn¹ nazwê pliku.";
    cout << "WprowadŸ nazwê pliku: " << endl;
    cin.get();
    getline(cin, nazwaPliku);

    if (nazwaPliku.size() < 1 || nazwaPliku.find('\"') != string::npos || nazwaPliku.find('\\') != string::npos || nazwaPliku.find('/') != string::npos ||
        nazwaPliku.find(':') != string::npos || nazwaPliku.find('|') != string::npos || nazwaPliku.find('<') != string::npos
        || nazwaPliku.find('>') != string::npos || nazwaPliku.find('*') != string::npos || nazwaPliku.find('?') != string::npos)   // Sprawdzamy czy nazwa pliku zgadza siê z wymogami Windows'a
        return zapisz(turaGracza1, blednaNazwa);      

    std::ofstream plik("zapisy/" + nazwaPliku + ".cfg");
    if (!plik.is_open()) {
        plik.close();
        return zapisz(turaGracza1, blednaNazwa);
    }
    plik << this->doTekstu(turaGracza1);
    plik.close();
}

int Plansza::getRozmiar() { return rozmiar; }
int Plansza::getIloscOdgadnietych() { return iloscOdgadnietych; }
bool Plansza::getTuraGracza() { return turaGracza1; }
int Plansza::getOdkryte(unsigned int num) {
    if (num == 1) return odkryte1;
    else return odkryte2;
}
void Plansza::zwiekszIloscOdgadnietych(unsigned int n) { iloscOdgadnietych += n; }

void Plansza::zwiekszIloscOdkrytych(unsigned int num, unsigned int n) {
    if (num == 1) odkryte1 += n;
    else odkryte2 += n;
}