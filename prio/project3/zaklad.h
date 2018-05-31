#ifndef AD
#define AD
#include "pracownicy.h"
class Zaklad    //zaklad
{
    private:
        std::string imie;   //nazwa zakladu
        Pracownik_a kierownik;  //kierownik zakladu
    public:
        Zaklad(void) {kierownik=Pracownik_a(0,0,"?");imie="?"; return;} //konstruktor bazowy
        Zaklad(std::string nazwa) {kierownik=Pracownik_a(0,0,"?");imie=nazwa;return;}   //konstruktor tylko z nazwa
        Zaklad(int x,std::string nazwi, std::string nazwa) {kierownik=Pracownik_a(x,0,nazwi);imie=nazwa; return;}   //konstruktor z danymi kierownika
        void druk(void) {if(kierownik.pusty()) return;else kierownik.druk();return;}    //druk do cout
        void pisz(std::fstream &out) {kierownik.pisz(out); return;} //druk do pliku
        Naukowiec* toon(void) {return &kierownik;}  //getter pointera do kierownika
        std::string coto(void) {return imie;}   //getter nazwy
};
#endif
