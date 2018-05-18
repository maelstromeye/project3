#include "klasy.h"
using namespace std;
int stop(string command)
{
    if(command=="non") return 0;
    if(command=="lic") return 1;
    if(command=="eng") return 2;
    if(command=="mag") return 3;
    if(command=="dok") return 4;
    if(command=="dhb") return 5;
    if(command=="pro") return 6;
    return -1;
}
int praca(string command)
{
    if(command=="lkt") return 0;
    if(command=="asy") return 1;
    if(command=="wyk") return 2;
    if(command=="adu") return 3;
    if(command=="stw") return 4;
    if(command=="pnz") return 5;
    if(command=="doc") return 6;
    if(command=="prz") return 7;
    return -1;
}
bool dosc(int x, int y)
{
    if(!x) return true;
    if((x<=3)&&(y>=3)) return true;
    if((x==4)&&((y==5)||(y==7))) return true;
    if((x==5)&&(y==7)) return true;
    return false;
}
void klik(void)
{
    string temp;
    cout<<"Kliknij enter aby kontynuowac."<<endl;
    getline(cin,temp);
    system("CLS");
}
void Instytut::inicjuj(void)
{
    string command;
    int numer,i,j;
    while(1)
    {
        system("CLS");
        cout<<"Zastepca - wpisz 'z'"<<endl<<"Dyrektor - wpisz 'd'"<<endl;
        getline(cin,command);
        if((command=="z")||(command=="d"))
        {
            if(command=="z") numer=1;
            if(command=="d") numer=0;
            system("CLS");
            cout<<"Wpisz profesje naukowa"<<endl<<"non - brak dyplomu"<<endl<<"lic - licencjat"<<endl<<"eng - inzynier"<<endl<<"mag - magister"<<endl<<"dok - doktor"<<endl<<"dhb - doktor habilitowany"<<endl<<"pro - profesor"<<endl;
            getline(cin,command);
            j=stop(command);
            if(!(j+1))
            {
                system("CLS");
                cout<<"Nieznany stopien. Powtorz krok."<<endl;
                klik();
                continue;
            }
            system("CLS");
            cout<<"Wpisz imie pracownika."<<endl;
            getline(cin,command);
            this->dodaj(j,command, numer);
            system("CLS");
            cout<<"Dodano pracownika:"<<endl;
            this->ostatni(numer);
            cout<<"W instytucie:"<<endl;
            cout<<this->coto()<<endl;
            klik();
            return;
        }
    }
}
//enum Stopien {non, lic, eng, mag, dok, dhb, pro};
//enum Praca_n {lkt, asy, wyk, adu, stw, pnz, doc, prz};
//enum Praca_a {kza, dzi, prd, din, zdi};
void Zaklad::dodaj(void)
{
    int i,j;
    string command;
    while(1)
    {
        system("CLS");
        cout<<"Wpisz profesje naukowa"<<endl<<"non - brak dyplomu"<<endl<<"lic - licencjat"<<endl<<"eng - inzynier"<<endl<<"mag - magister"<<endl<<"dok - doktor"<<endl<<"dhb - doktor habilitowany"<<endl<<"pro - profesor"<<endl;
        getline(cin,command);
        i=stop(command);
        if(!(i+1))
        {
            cout<<"Nieznany stopien. Powtorz krok."<<endl;
            klik();
            continue;
        }
        system("CLS");
        cout<<"Sprecyzuj prace pracownika"<<endl<<"kza - kierownik zakladu"<<endl<<"lkt - lektor"<<endl<<"asy - asystent"<<endl<<"wyk - wykladowca"<<endl<<"adu - adiunkt"<<endl<<"stw - starszy wykladowca"<<endl<<"pnz - profesor nadzwyczajny"<<endl<<"doc - docent"<<endl<<"prz - profesor zwyczajny"<<endl;
        getline(cin,command);
        if(command=="kza")
        {
            system("CLS");
            cout<<"Wpisz imie pracownika"<<endl;
            getline(cin,command);
            kierownik=Pracownik_a(i,0,command);
            system("CLS");
            cout<<"Dodano pracownika:"<<endl;
            kierownik.druk();
            cout<<"W zakladzie:"<<endl<<imie<<endl;
            klik();
            return;
        }
        j=praca(command);
        if(!(j+1))
        {
            system("CLS");
            cout<<"Nieznana praca. Powtorz krok."<<endl;
            klik();
            continue;
        }
        if(dosc(i,j))
        {
            system("CLS");
            cout<<"Pracownik nie spelnia wymagan zeby otrzymac wyznaczona pozycje. Powtorz krok."<<endl;
            klik();
            continue;
        }
        system("CLS");
        cout<<"Wpisz imie pracownika"<<endl;
        getline(cin, command);
        this->push_back(Pracownik_n(i,j,command));
        system("CLS");
        cout<<"Dodano pracownika:"<<endl;
        this->at(this->size()-1).druk();
        cout<<"W zakladzie:"<<endl<<imie<<endl;
        return;
    }
}
