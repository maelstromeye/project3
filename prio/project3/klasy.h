#ifndef ADD
#define ADD
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
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
        virtual void druk(void)
        {
            using namespace std;
            switch (stop)
            {
                case non:
                    cout<<imie<<endl;
                    break;
                case lic:
                    cout<<"Licencjat"<<endl;
                    cout<<imie<<endl;
                    break;
                case eng:
                    cout<<"Inzynier"<<endl;
                    cout<<imie<<endl;
                    break;
                case mag:
                    cout<<"Magister"<<endl;
                    cout<<imie<<endl;
                    break;
                case dok:
                    cout<<"Doktor"<<endl;
                    cout<<imie<<endl;
                    break;
                case dhb:
                    cout<<"Doktor habilitowany"<<endl;
                    cout<<imie<<endl;
                    break;
                case pro:
                    cout<<"Profesor"<<endl;
                    cout<<imie<<endl;
                default:
                    break;
            }
            return;
        }
        friend class Pracownik_n;
        friend class Pracownik_a;
};

class Pracownik_n : public Naukowiec
{
    private:
        Praca_n praca;
        bool dosc(void)
        {
            if(stop==non) return true;
            if((praca==prz)||(praca==stw)||(praca==doc)) return true;
            if((praca==wyk)&&(stop<dok)) return true;
            if ((praca==asy)&&(stop<dok)) return true;
            if ((praca==adu)&&(stop<dhb)) return true;
            if ((praca==pnz)&&(stop<pro)) return true;
            return false;
        }
    public:
        Pracownik_n(void) {praca=lkt; Naukowiec(); return;}
        Pracownik_n(int x, int y, std::string nazwa) : Naukowiec(x, nazwa) {praca=Praca_n(y); return;}
        bool prom(void)
        {
            if(this->dosc()) return false;
            praca=Praca_n(praca+2);
            return true;
        }
        bool deg(void)
        {
            if((praca%2!=1)||(praca==prz)) return false;
            else praca=Praca_n(praca+1);
            return true;
        }
        bool zmien(int x)
        {
            if(x>7) return false;
            else praca=Praca_n(x);
            return true;
        }
        void druk(void)
        {
            using namespace std;
            switch (stop)
            {
                case non:
                    cout<<imie<<endl;
                    break;
                case lic:
                    cout<<"Licencjat"<<endl;
                    cout<<imie<<endl;
                    break;
                case eng:
                    cout<<"Inzynier"<<endl;
                    cout<<imie<<endl;
                    break;
                case mag:
                    cout<<"Magister"<<endl;
                    cout<<imie<<endl;
                    break;
                case dok:
                    cout<<"Doktor"<<endl;
                    cout<<imie<<endl;
                    break;
                case dhb:
                    cout<<"Doktor habilitowany"<<endl;
                    cout<<imie<<endl;
                    break;
                case pro:
                    cout<<"Profesor"<<endl;
                    cout<<imie<<endl;
                default:
                    break;
            }
            switch (praca)
            {
                case lkt:
                    cout<<"Lektor"<<endl;
                    break;
                case asy:
                    cout<<"Asystent"<<endl;
                    break;
                case wyk:
                    cout<<"Wykladowca"<<endl;
                    break;
                case adu:
                    cout<<"Adiunkt"<<endl;
                    break;
                case stw:
                    cout<<"Starszy Wykladowca"<<endl;
                    break;
                case pnz:
                    cout<<"Profesor Nadzwyczajny"<<endl;
                    break;
                case doc:
                    cout<<"Docent"<<endl;
                    break;
                case prz:
                    cout<<"Profesor Zwyczajny"<<endl;
                    break;
                default:
                    break;
            }
            return;
        }
};

class Pracownik_a : public Naukowiec
{
    private:
        Praca_a praca;
    public:
        bool deg(void)
        {
            if(praca%2==0) return false;
            praca=Praca_a(praca+1);
            return true;
        }
        bool prom(void)
        {
            if((praca%2!=0)||(praca==kza)) return false;
            praca=Praca_a(praca-1);
            return true;
        }
        bool zmien(int x)
        {
            if(x>4) return false;
            else praca=Praca_a(x);
            return true;
        }
        void druk(void)
        {
            using namespace std;
            switch (stop)
            {
                case non:
                    cout<<imie<<endl;
                    break;
                case lic:
                    cout<<"Licencjat"<<endl;
                    cout<<imie<<endl;
                    break;
                case eng:
                    cout<<"Inzynier"<<endl;
                    cout<<imie<<endl;
                    break;
                case mag:
                    cout<<"Magister"<<endl;
                    cout<<imie<<endl;
                    break;
                case dok:
                    cout<<"Doktor"<<endl;
                    cout<<imie<<endl;
                    break;
                case dhb:
                    cout<<"Doktor habilitowany"<<endl;
                    cout<<imie<<endl;
                    break;
                case pro:
                    cout<<"Profesor"<<endl;
                    cout<<imie<<endl;
                default:
                    break;
            }
            switch (praca)
            {
                case kza:
                    cout<<"Kierownik zakladu"<<endl;
                    break;
                case dzi:
                    cout<<"Dziekan"<<endl;
                    break;
                case prd:
                    cout<<"Prodziekan"<<endl;
                    break;
                case din:
                    cout<<"Dyrektor Instytutu"<<endl;
                    break;
                case zdi:
                    cout<<"Zastepca Dyrektora Instytutu"<<endl;
                    break;
                default:
                    break;
            }
            return;
        }
        Pracownik_a(void) {praca=kza; Naukowiec(); return;}
        Pracownik_a(int x, int y, std::string nazwa) : Naukowiec(x, nazwa) {praca=Praca_a(y); return;}
};

class Zaklad : public std::vector<Pracownik_n>
{
    private:
        std::string imie;
        Pracownik_a kierownik;
    public:
        Zaklad(void) {kierownik=Pracownik_a(0,0,"?");imie="?"; return;}
        Zaklad(std::string nazwa) {imie=nazwa;return;}
        Zaklad(int x,std::string nazwi, std::string nazwa) {kierownik=Pracownik_a(x,0,nazwi);imie=nazwa; return;}
        ~Zaklad(void) {this->clear(); return;};
        void dodaj(void);
        bool identyfikuj(std::string czyto) {if(czyto==imie) return true; return false;}
};

class Instytut : public std::vector<Zaklad>
{
    private:
        Pracownik_a dyrektor;
        std::vector<Pracownik_a> zastepcy;
        std::string imie;
    public:
        bool identyfikuj(std::string czyto) {if(czyto==imie) return true; return false;}    //czy to jest ten instytut
        void dodaj(int x, std::string nazwa, bool kto) {if(kto) zastepcy.push_back(Pracownik_a(x,4,nazwa)); else dyrektor=Pracownik_a(x,3,nazwa); return;}   //dodaj zastepce badz dyrektora
        void ostatni(bool kto) {if(kto) zastepcy[zastepcy.size()-1].druk(); else dyrektor.druk(); return;}  //drukuj ostatnio dodanego zastepce(true) badz dyrektora (false)
        std::string coto(void) {return imie;}   //nazwa instytutu
        void inicjuj(void);
        Instytut(void) {dyrektor=Pracownik_a(0,3,"?");imie="?";return;}
        Instytut(std::string nazwa) {imie=nazwa;return;}
        Instytut(int x, std::string nazwi, std::string nazwa) {dyrektor=Pracownik_a(0,3,nazwi);imie=nazwa;return;}
        ~Instytut(void) {this->clear(); return;}
};










#endif
