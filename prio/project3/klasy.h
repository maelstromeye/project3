#ifndef ADD
#define ADD
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <exception>
enum Stopien {non, lic, eng, mag, dok, dhb, pro};   //stopien naukowy
enum Praca_n {lkt, asy, wyk, adu, stw, pnz, doc, prz};  //praca naukowa
enum Praca_a {kza, dzi, prd, din, zdi}; //praca dministracyjna
class Naukowiec //bazowa klasa pracownika
{
    private:
        Stopien stop;   //jaki ma stopien naukowy
        std::string imie;   //imie
    public:
        Naukowiec(void) {stop=non; imie="?"; return;}   //konstruktor bazowy
        Naukowiec(int x, std::string nazwa) {stop=Stopien(x); imie=nazwa; return;}  //inicjalizuje ze wszystkim
        bool pusty(void) {if(imie=="?") return true; return false;} //czy sa w nim dane
        bool prom_n(void)   //promocja naukowa
        {
            if(stop==pro) return false;
            else stop=Stopien(stop+1);
            return true;
        }
        bool zmien_n(int x) //zmiana stopnia naukowego
        {
            if(x>6) return false;
            else stop=Stopien(x);
            return true;
        }
        std::string coto(void) {return imie;}   //getter imienia
        virtual void druk(void) {return;}   //wydrukuj
        virtual bool prom(void) {return false;} //promuj
        virtual bool deg(void) {return false;}  //degraduj
        virtual bool zmien(int x) {return false;}   //zmien prace
        friend class Pracownik_n;   //pracownik naukowy
        friend class Pracownik_a;   //pracownik administracyjny
};

class Pracownik_n : public Naukowiec    //pracownik naukowy
{
    private:
        Praca_n praca;  //praca naukowa
    public:
        Pracownik_n(void) {praca=lkt; Naukowiec(); return;} //konstruktor bazowy
        Pracownik_n(int x, int y, std::string nazwa) : Naukowiec(x, nazwa) {praca=Praca_n(y); return;}  //konstruktor z danymi
        virtual bool prom(void) //promocja pracy naukowej
        {
            if((praca==prz)||(praca==doc)) return false;
            praca=Praca_n(praca+2);
            return true;
        }
        virtual bool deg(void)  //degradacja pracy naukowej
        {
            if((praca%2!=1)||(praca==prz)) return false;
            else praca=Praca_n(praca+1);
            return true;
        }
        virtual bool zmien(int x)   //zmiana pracy naukowej
        {
            if(x>7) return false;
            else praca=Praca_n(x);
            return true;
        }
        virtual void druk(void);    //druk do cout
        void pisz(std::fstream &out);   //druk do fstream
};

class Pracownik_a : public Naukowiec    //pracownik naukowy
{
    private:
        Praca_a praca;  //praca dministracyjna
    public:
        Pracownik_a(void) {praca=kza; Naukowiec();return;}  //konstruktor bazowy
        Pracownik_a(int x, int y, std::string nazwa) : Naukowiec(x, nazwa) {praca=Praca_a(y); return;}  //konstruktor z danymi
        bool prom(void) {if((praca%2!=0)||(praca==kza)) return false; praca=Praca_a(praca-1); return true;}
        bool deg(void)  //degradacja administracyjna
        {
            if(praca%2==0) return false;
            praca=Praca_a(praca+1);
            return true;
        }
        bool zmien(int x)   //zmiana pracy administracyjnej
        {
            if(x>4) return false;
            else praca=Praca_a(x);
            return true;
        }
        virtual void druk(void);    //druk do cout
        void pisz(std::fstream &out);   //druk do pliku
};

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
