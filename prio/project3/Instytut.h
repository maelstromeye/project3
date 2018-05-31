#ifndef ADDD
#define ADDD
#include "pracownicy.h"
#include "zaklad.h"
class Instytut : private std::vector<Pracownik_n>   //instytut/dziekanat ma wektor pracownikow naukowych
{
    private:
        Pracownik_a dyrektor;   //ma dyrektora/dziekana
        std::vector<Pracownik_a> zastepcy;  //ma zastepcow/dziekanow
        std::string imie;   //ma nazwe
        std::vector<Zaklad> zaklady;    //ma wektor zakladow
    public:
        Instytut(void) {dyrektor=Pracownik_a(0,3,"?");imie="?";return;} //konstruktor bazowy
        Instytut(std::string nazwa) {dyrektor=Pracownik_a(0,3,"?");imie=nazwa;return;}  //konstruktor z nazwa
        Instytut(std::string nazwa, bool d) {dyrektor=Pracownik_a(0,1,"?");imie=nazwa;return;}  //konstruktor dla dziekanatu
        Instytut(int x, std::string nazwi, std::string nazwa) {dyrektor=Pracownik_a(x,3,nazwi);imie=nazwa;return;}  //konstruktor z danymi dyrektora
        ~Instytut(void) {this->clear();zastepcy.clear();zaklady.clear(); return;}   //destruktor
        void druk(void);    //druk do cout
        void pisz(std::fstream &out);   //druk do pliku
        void zmien_n(int x, int y) {if(!(y++)) dyrektor.zmien_n(x);else zastepcy[y].zmien(x); return;}  //zmiana stopnia dyrektora/dziekana
        void dodaj(std::istream &inp, bool d);  //dodanie pracownika
        void deg(void) {zastepcy.push_back(dyrektor); dyrektor=Pracownik_a(); return;}  //degraduje dyrektora do zastepcy
        void prom(std::string command); //promuje zastepce do dyrektora
        bool pusty(void) {if(dyrektor.pusty()) return true; return false;}  //czy jest dyrektor
        bool zwolnij(std::string command);  //zwalnia
        Naukowiec* znajdz(std::string command, bool d); //znajduje pointer do naukowca 1 - przeszukuje wektor glowny, 0 - przeszukuje wektory poboczne
        std::string coto(void) {return imie;}   //getter nazwy
};
#endif
