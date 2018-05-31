#ifndef ADD
#define ADD
#include <iostream>
#include <string>
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
#endif
