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
bool zmien_n(vector<Instytut> &wydzial);
void pokaz(vector<Instytut> &wydzial);
void klik(void);
bool lokalizuj(vector<Instytut> &wydzial,int &i,int &j,int &k);
template <typename type>
void sortuj(vector<type> &stringi);
int main()
{
    Pracownik_a dziekan;
    vector<Pracownik_a> prodziekani;
    vector<Instytut> wydzial;
    string command;
    int numer, i;
    bool d;
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
                d=dodaj(wydzial);  //czy dodac dziekana
                if(!d)
                {
                    while(1)    //dodawanie dziekana
                    {
                        system("CLS");
                        cout<<"Dziekan - d"<<endl<<"Prodziekan - p"<<endl;
                        getline(cin,command);
                        if(command=="d") numer=0;
                        else if(command=="p") numer=1;
                        else
                        {
                            cout<<"Nieoczekiwana komenda. Wybierz jeszcze raz."<<endl;
                            klik();
                            continue;
                        }
                        system("CLS");
                        if((!numer)&&(!dziekan.pusty()))
                        {
                            cout<<"Uwaga: Wydzial posiada dziekana. Kontynuacja doprowadzi do zwolnienia obecnego dziekana. Aby jednak dodac prodziekana, wpisz 'p'. Aby dodac dziekana mimo to, kliknij enter."<<endl;
                            getline(cin,command);
                            if(command=="p") numer=1;
                            system("CLS");
                        }
                        cout<<"Wpisz profesje naukowa"<<endl<<"non - brak dyplomu"<<endl<<"lic - licencjat"<<endl<<"eng - inzynier"<<endl<<"mag - magister"<<endl<<"dok - doktor"<<endl<<"dhb - doktor habilitowany"<<endl<<"pro - profesor"<<endl;
                        getline(cin,command);
                        i=stop(command);
                        if(!(i+1))
                        {
                            system("CLS");
                            cout<<"Nieznany stopien. Powtorz krok."<<endl;
                            klik();
                            continue;
                        }
                        system("CLS");
                        cout<<"Wpisz imie pracownika."<<endl;
                        getline(cin,command);
                        if(numer) prodziekani.push_back(Pracownik_a(i,2,command));
                        else dziekan=Pracownik_a(i,1,command);
                        system("CLS");
                        cout<<"Dodano pracownika:"<<endl;
                        if(numer) prodziekani[prodziekani.size()-1].druk();
                        else dziekan.druk();
                        if(numer) sortuj(prodziekani);
                        klik();
                        system("CLS");
                        break;
                    }
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
                d=zmien_n(wydzial);
                if(!d)
                {

                }
                break;
            case 9:
                pokaz(wydzial);
                break;
            default:
                cout<<"Nieznana komenda"<<endl;
                klik();
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
    vector<string> stringi;
    vector<int> kolej;
    char b;
    system("CLS");
    cout<<"Do jakiego instytutu ma nalezec pracownik?"<<endl;
    cout<<"Aby utworzyc nowy instytut, wpisz '+'."<<endl;
    cout<<"Aby dodac dziekana, badz prodziekana, wpisz '++'."<<endl;
    while(1)
    {
        if(!wydzial.empty())
        {
            cout<<"Obecne instytuty:"<<endl;
            for(i=0;i<wydzial.size();i++)
            {
                cout<<wydzial[i].coto()<<endl;
            }
        }
        getline(cin,command);
        if(command=="++") return false;
        if(command=="+")
        {
            system("CLS");
            cout<<"Wpisz nazwe nowego instytutu."<<endl;
            getline(cin,command);
            for(i=0;i<wydzial.size();i++)
            {
                if(wydzial[i].identyfikuj(command)) break;
            }
            if(i!=wydzial.size())
            {
                system("CLS");
                cout<<"Nazwa instytutu zajeta. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac nowy zaklad, badz '++' aby dodac dziekana lub prodziekana."<<endl;
                continue;
            }
            i=wydzial.size();
            wydzial.push_back(Instytut(command));
            system("CLS");
            cout<<"Wpisz nazwe zakladu w nowym instytucie."<<endl;
            cout<<"Aby dodac dyrektora instytutu, badz jego zastepce wpisz '+'"<<endl;
            getline(cin,command);
            if(command=="+")
            {
                wydzial[i].inicjuj();
                sortuj(wydzial);
                return true;
            }
            else
            {
                wydzial[i].push_back(Zaklad(command));
                wydzial[i][wydzial[i].size()-1].dodaj();
                cout<<"W instytucie:"<<endl<<wydzial[i].coto()<<endl;
                klik();
                sortuj(wydzial);
                return true;
            }
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
            system("CLS");
                cout<<"Do jakiego zakladu ma nalezec pracownik?"<<endl<<"Aby utworzyc nowy zaklad, wpisz '+'."<<endl<<"Aby dodac dyrektora instytutu, badz jego zastepce wpisz '++'"<<endl;
            while(1)
            {
                if(!wydzial[i].empty())
                {
                    cout<<"Obecne zaklady:"<<endl;
                    for(j=0;j<wydzial[i].size();j++)
                    {
                        cout<<wydzial[i][j].coto()<<endl;
                    }
                }
                getline(cin,command);
                if(command=="+")
                {
                    system("CLS");
                    cout<<"Wpisz nazwe nowego zakladu."<<endl;
                    getline(cin,command);
                    for(j=0;j<wydzial[i].size();j++)
                    {
                        if(wydzial[i][j].identyfikuj(command)) break;
                    }
                    if(j!=wydzial[i].size())
                    {
                        system("CLS");
                        cout<<"Nazwa zakladu zajeta. Wpisz nazwe zakladu jeszcze raz, badz '+' zeby dodac nowy zaklad, badz '++' aby dodac dyrektora instytutu lub jego zastepce."<<endl;
                        continue;
                    }
                    wydzial[i].push_back(Zaklad(command));
                    wydzial[i][wydzial[i].size()-1].dodaj();
                    cout<<"W instytucie:"<<endl<<wydzial[i].coto()<<endl;
                    klik();
                    sortuj(wydzial[i]);
                    return true;
                }
                if(command=="++")
                {
                    wydzial[i].inicjuj();
                    return true;
                }
                for(j=0;j<wydzial[i].size();j++)
                {
                    if(wydzial[i][j].identyfikuj(command)) break;
                }
                if(j==wydzial[i].size())
                {
                    system("CLS");
                    cout<<"Zaklad nie znaleziony. Wpisz nazwe zakladu jeszcze raz, badz '+' zeby dodac nowy zaklad, badz '++' aby dodac dyrektora instytutu lub jego zastepce."<<endl;
                    continue;
                }
                wydzial[i][j].dodaj();
                cout<<"W instytucie:"<<endl<<wydzial[i].coto()<<endl;
                klik();
                sortuj(wydzial[i][j]);
                return true;
            }
        }
    }
}

bool zwolnij(void){}
bool degraduj(void){}
bool promuj(void){}
bool promuj_n(void){}
bool zmien(void){}
bool lokalizuj(vector<Instytut> &wydzial,int &i,int &j,int &k)
{
    string command;
    bool d;
    system("CLS");
    cout<<"Na jakim instytucie pracuje pracownik?"<<endl<<"Jezeli pracownik nie jest zwiazany z zadnym instytutem, wpisz '+'."<<endl;
    while(1)
    {
        i=j=k=-1;
        getline(cin, command);
        if(command=="+") return false;
        for(i=0;i<wydzial.size();i++)
        {
            if(wydzial[i].identyfikuj(command)) break;
        }
        if(i==wydzial.size())
        {
            system("CLS");
            cout<<"Instytut nie znaleziony. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac zlokalizowac pracownika niezwiazanego z zadnym instytutem."<<endl;
            continue;
        }
        system("CLS");
        cout<<"W jakim zakladzie pracuje pracownik?"<<endl<<"Jezeli pracownik nie jest zwiazany z zadnym zakladem wpisz '+'."<<endl;
        getline(cin, command);
        if(command=="+")
        {
            system("CLS");
            cout<<"Wpisz imie pracownika."<<endl;
            getline(cin,command);
            d=wydzial[i].istnieje(command,k);
            if(!d)
            {
                system("CLS");
                cout<<"Nie znaleziono pracownika. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac zlokalizowac pracownika niezwiazanego z zadnym instytutem."<<endl;
                continue;
            }
            return false;
        }
        for(j=0;j<wydzial[i].size();j++)
        {
            if(wydzial[i][j].identyfikuj(command)) break;
        }
        if(j==wydzial[i].size())
        {
            system("CLS");
            cout<<"Zaklad nie znaleziony. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac zlokalizowac pracownika niezwiazanego z zadnym instytutem."<<endl;
            continue;
        }
        system("CLS");
        cout<<"Wpisz imie pracownika."<<endl;
        getline(cin,command);
        if(command==wydzial[i][j].ktorzadzi()) return false;
        for(k=0;k<wydzial[i][j].size();k++)
        {
            if(wydzial[i][j][k].coto()==command) break;
        }
        if(k==wydzial[i][j].size())
        {
            system("CLS");
            cout<<"Nie znaleziono pracownika. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac zlokalizowac pracownika niezwiazanego z zadnym instytutem."<<endl;
            continue;
        }
        return true;
    }
}
bool zmien_n(vector<Instytut> &wydzial)
{
    string command;
    int i,j,k,o;
    bool d;
    system("CLS");
    d=lokalizuj(wydzial,i,j,k);
    if((!d)&&(i==-1)) return false;
    if((!d)&&(j==-1))
    {
        while(1)
        {
            system("CLS");
            cout<<"Wpisz nowa profesje naukowa"<<endl<<"non - brak dyplomu"<<endl<<"lic - licencjat"<<endl<<"eng - inzynier"<<endl<<"mag - magister"<<endl<<"dok - doktor"<<endl<<"dhb - doktor habilitowany"<<endl<<"pro - profesor"<<endl;
            getline(cin,command);
            o=stop(command);
            if(!(o+1))
            {
                cout<<"Nieznany stopien. Powtorz krok."<<endl;
                klik();
                system("CLS");
                continue;
            }
            wydzial[i].zmien_n(o,k);
            system("CLS");
            cout<<"Stopien naukowy zmieniony."<<endl;
            klik();
            return true;
        }
    }
    if((!d)&&(k==-1))
    {
        while(1)
        {
            system("CLS");
            cout<<"Wpisz nowa profesje naukowa"<<endl<<"non - brak dyplomu"<<endl<<"lic - licencjat"<<endl<<"eng - inzynier"<<endl<<"mag - magister"<<endl<<"dok - doktor"<<endl<<"dhb - doktor habilitowany"<<endl<<"pro - profesor"<<endl;
            getline(cin,command);
            o=stop(command);
            if(!(o+1))
            {
                cout<<"Nieznany stopien. Powtorz krok."<<endl;
                klik();
                continue;
            }
            wydzial[i][j].zmien_n(o);
            system("CLS");
            cout<<"Stopien naukowy zmieniony."<<endl;
            klik();
            return true;
        }
    }
    system("CLS");
    while(1)
    {
        system("CLS");
        cout<<"Wpisz nowa profesje naukowa"<<endl<<"non - brak dyplomu"<<endl<<"lic - licencjat"<<endl<<"eng - inzynier"<<endl<<"mag - magister"<<endl<<"dok - doktor"<<endl<<"dhb - doktor habilitowany"<<endl<<"pro - profesor"<<endl;
        getline(cin,command);
        o=stop(command);
        if(!(o+1))
        {
            system("CLS");
            cout<<"Nieznany stopien. Powtorz krok."<<endl;
            klik();
            system("CLS");
            continue;
        }
        wydzial[i][j][k].zmien_n(o);
        system("CLS");
        cout<<"Stopien naukowy zmieniony."<<endl;
        klik();
        return true;
    }
}
void pokaz(vector<Instytut> &wydzial)
{
    int i,j;
    for(i=0;i<wydzial.size();i++)
    {
        system("CLS");
        cout<<"W instytucie:"<<endl<<wydzial[i].coto()<<endl<<"Pracownicy administracyjni to:"<<endl;
        wydzial[i].druk();
        klik();
        for(j=0;j<wydzial[i].size();j++)
        {
            cout<<"W zakladzie:"<<endl<<wydzial[i][j].coto()<<endl<<"Pracownicy to:"<<endl;
            wydzial[i][j].druk();
            klik();
        }
        system("CLS");
    }
    return;
}
template <typename type>
void sortuj(vector<type> &stringi)
{
    int i,j,numer;
    string temp;
    type obiekt;
    temp="~";
    for(j=0;j<stringi.size();j++)
    {
        for(i=j;i<stringi.size();i++)
        {
            if(stringi[i].coto()<temp)
            {
                temp=stringi[i].coto();
                numer=i;
            }
        }
        obiekt=stringi[numer];
        stringi[numer]=stringi[j];
        stringi[j]=obiekt;
        temp="~";
        numer=0;
    }
    return;
}
