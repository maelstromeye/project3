#include "klasy.h"
using namespace std;
//enum Stopien {non, lic, eng, mag, dok, dhb, pro};
//enum Praca_n {lkt, asy, wyk, adu, stw, pnz, doc, prz};
//enum Praca_a {kza, dzi, prd, din, zdi};
void pomoc(void);
int wykryj(string command);
int stop(string command);
void elka(void);
bool dodaj(vector<Instytut> &wydzial);
bool zwolnij(void);
bool degraduj(void);
bool promuj(void);
bool promuj_n(void);
bool zmien(void);
bool zmien_n(void);
bool pokaz(void);
void klick(void);
int main()
{
    Pracownik_a dziekan=Pracownik_a(0,1,"");
    vector<Pracownik_a> prodziekani;
    vector<Instytut> wydzial;
    string command;
    while(1)
    {
        pomoc();
        getline(cin, command);
        switch (wykryj(command))
        {
            case 1:
                elka();
                break;
            case 2:
                if(!(dodaj(wydzial)));
                {

                }
                break;
            case 3:
                zwolnij();
                break;
            case 4:
                degraduj();
                break;
            case 5:
                promuj();
                break;
            case 6:
                promuj_n();
                break;
            case 7:
                zmien();
                break;
            case 8:
                zmien_n();
                break;
            case 9:
                pokaz();
                break;
            default:
                cout<<"Nieznana komenda"<<endl;
                klick();
                break;
        }
    }
    return 0;
}

void pomoc(void)
{
    cout<<"MENU"<<endl;
    cout<<"Wpisz:"<<endl;
    cout<<"-'elka' zeby zainicjalizowac dane EiTi"<<endl;
    cout<<"-'dodaj' zeby dodac pracownika, instytut, badz zaklad"<<endl;
    cout<<"-'zwolnij' zeby zwolnic pracownika"<<endl;
    cout<<"-'degraduj' zeby zdegradowac pracownika"<<endl;
    cout<<"-'promuj' zeby dokonac promocji pracownika na stanowisku naukowym (np. wykladowca->starszy wykladowca)"<<endl;
    cout<<"-'promuj_n' zeby dokonac promocji naukowej (np. inzynier->magister)"<<endl;
    cout<<"-'zmien' zeby zmienic stanowisko zajmowane przez pracownika recznie"<<endl;
    cout<<"-'zmien_n' zeby zmienic tytul naukowy pracownika"<<endl;
    cout<<"-'pokaz' zeby wydrukowac obecny stan kadry"<<endl;
    return;
}

int wykryj(string command)
{
    if(command=="elka") return 1;
    if(command=="dodaj") return 2;
    if(command=="zwolnij") return 3;
    if(command=="degraduj") return 4;
    if(command=="promuj") return 5;
    if(command=="promuj_n") return 6;
    if(command=="zmien") return 7;
    if(command=="zmien_n") return 8;
    if(command=="pokaz") return 9;
    return 0;
}
void elka(void){};
bool dodaj(vector<Instytut> &wydzial)
{
    int numer,i,j;
    string command;
    char b;
    system("CLS");
    cout<<"Do jakiego instytutu ma nalezec pracownik?"<<endl;
    cout<<"Aby utworzyc nowy instytut, wpisz '+'."<<endl;
    cout<<"Aby dodac dziekana, badz prodziekana, wpisz '++'."<<endl;
    while(1)
    {
        getline(cin,command);
        if(command=="+")
        {
            system("CLS");
            cout<<"Wpisz nazwe nowego instytutu."<<endl;
            getline(cin,command);
            i=wydzial.size();
            wydzial.push_back(Instytut(command));
            system("CLS");
            cout<<"Wpisz nazwe zakladu w nowym instytucie."<<endl;
            cout<<"Aby dodac dyrektora instytutu, badz jego zastepce wpisz '+'"<<endl;
            getline(cin,command);
            if(command=="+")
            {
                wydzial[i].inicjuj();
                return true;
            }
            else
            {
                wydzial[i].push_back(Zaklad(command));
                wydzial[i][wydzial[i].size()-1].dodaj();
                cout<<"W instytucie:"<<endl<<wydzial[i].coto()<<endl;
                klick();
                return true;
            }
            if(command=="++") return false;
        }
        else
        {
            for(i=0;i<wydzial.size();i++)
            {
                if(wydzial[i].identyfikuj(command)) break;
            }
            if(i==wydzial.size())
            {
                system("CLS");
                cout<<"Instytut nie znaleziony. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac nowy instytut, badz '++' aby dodac dziekana lub prodziekana"<<endl;
                continue;
            }
            while(1)
            {
                system("CLS");
                cout<<"Do jakiego zakladu ma nalezec pracownik?"<<endl;
                cout<<"Aby utworzyc nowy zaklad, wpisz '+'."<<endl;
            }
        }
    }
}
void klick(void)
{
    string temp;
    cout<<"Kliknij enter aby kontynuowac."<<endl;
    getline(cin,temp);
    system("CLS");
}
bool zwolnij(void){}
bool degraduj(void){}
bool promuj(void){}
bool promuj_n(void){}
bool zmien(void){}
bool zmien_n(void){}
bool pokaz(void){}
