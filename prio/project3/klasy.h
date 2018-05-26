#ifndef ADD
#define ADD
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
enum Stopien {non, lic, eng, mag, dok, dhb, pro};
enum Praca_n {lkt, asy, wyk, adu, stw, pnz, doc, prz};
enum Praca_a {kza, dzi, prd, din, zdi};
class Naukowiec
{
    private:
        Stopien stop;
        std::string imie;
    public:
        Naukowiec(void) {stop=non; imie="?"; return;}
        Naukowiec(int x, std::string nazwa) {stop=Stopien(x); imie=nazwa; return;}
        bool pusty(void) {if(imie=="?") return true; return false;}
        bool prom_n(void)
        {
            if(stop==pro) return false;
            else stop=Stopien(stop+1);
            return true;
        }
        bool zmien_n(int x)
        {
            if(x>6) return false;
            else stop=Stopien(x);
            return true;
        }
        std::string coto(void) {return imie;}
        virtual void druk(void) {return;}
        virtual bool prom(void) {return false;}
        virtual bool deg(void) {return false;}
        virtual bool zmien(int x) {return false;}
        friend class Pracownik_n;
        friend class Pracownik_a;
};

class Pracownik_n : public Naukowiec
{
    private:
        Praca_n praca;
    public:
        Pracownik_n(void) {praca=lkt; Naukowiec(); return;}
        Pracownik_n(int x, int y, std::string nazwa) : Naukowiec(x, nazwa) {praca=Praca_n(y); return;}
        virtual bool prom(void) {if((praca==prz)||(praca==doc)) return false; praca=Praca_n(praca+2);return true;}
        virtual bool deg(void) {if((praca%2!=1)||(praca==prz)) return false; else praca=Praca_n(praca+1); return true;}
        virtual bool zmien(int x) {if(x>7) return false; else praca=Praca_n(x); return true;}
        virtual void druk(void);
};

class Pracownik_a : public Naukowiec
{
    private:
        Praca_a praca;
    public:
        Pracownik_a(void) {praca=kza; Naukowiec();return;}
        Pracownik_a(int x, int y, std::string nazwa) : Naukowiec(x, nazwa) {praca=Praca_a(y); return;}
        bool prom(void) {if((praca%2!=0)||(praca==kza)) return false; praca=Praca_a(praca-1); return true;}
        bool deg(void) {if(praca%2==0) return false; praca=Praca_a(praca+1); return true;}
        bool zmien(int x) {if(x>4) return false; else praca=Praca_a(x); return true;}
        virtual void druk(void);
};

class Zaklad
{
    private:
        std::string imie;
        Pracownik_a kierownik;
    public:
        Zaklad(void) {kierownik=Pracownik_a(0,0,"?");imie="?"; return;}
        Zaklad(std::string nazwa) {kierownik=Pracownik_a(0,0,"?");imie=nazwa;return;}
        Zaklad(int x,std::string nazwi, std::string nazwa) {kierownik=Pracownik_a(x,0,nazwi);imie=nazwa; return;}
        void druk(void) {if(kierownik.pusty()) return;else kierownik.druk();return;}
        Naukowiec* toon(void) {return &kierownik;}
        std::string coto(void) {return imie;}
        std::string ktorzadzi(void) {return kierownik.coto();}
        bool pusty(void) {if(kierownik.pusty()) return true; return false;}
        void zmien_n(int x) {kierownik.zmien_n(x);return;}
};

class Instytut : private std::vector<Pracownik_n>
{
    private:
        Pracownik_a dyrektor;
        std::vector<Pracownik_a> zastepcy;
        std::string imie;
        std::vector<Zaklad> zaklady;
    public:
        void dodaj(std::istream &inp, bool d);
        std::string coto(void) {return imie;}   //nazwa instytutu
        void druk(void);
        void zmien_n(int x, int y) {if(!(y++)) dyrektor.zmien_n(x);else zastepcy[y].zmien(x); return;}
        Naukowiec* znajdz(std::string command, bool d);
        void deg(void) {zastepcy.push_back(dyrektor); dyrektor=Pracownik_a(); return;}
        bool pusty(void) {if(dyrektor.pusty()) return true; return false;}
        void prom(std::string command);
        bool zwolnij(std::string command);
        Instytut(void) {dyrektor=Pracownik_a(0,3,"?");imie="?";return;}
        Instytut(std::string nazwa) {dyrektor=Pracownik_a(0,3,"?");imie=nazwa;return;}
        Instytut(std::string nazwa, bool d) {dyrektor=Pracownik_a(0,1,"?");imie=nazwa;return;}
        Instytut(int x, std::string nazwi, std::string nazwa) {dyrektor=Pracownik_a(x,3,nazwi);imie=nazwa;return;}
        ~Instytut(void) {this->clear();zastepcy.clear();zaklady.clear(); return;}
};










#endif
