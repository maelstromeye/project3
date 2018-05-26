#include "klasy.h"
using namespace std;
//enum Stopien {non, lic, eng, mag, dok, dhb, pro};
//enum Praca_n {lkt, asy, wyk, adu, stw, pnz, doc, prz};
//enum Praca_a {kza, dzi, prd, din, zdi};
void pomoc(void);
int wykryj(string command);
int stop(istream & inp, bool d);
void elka(void);
bool dodaj(vector<Instytut> &wydzial, istream& inp, bool d);
void pokaz(vector<Instytut> &wydzial);
void klik(void);
void operacja(vector<Instytut> &wydzial, int n);
Naukowiec * lokalizuj(Instytut &instytut, bool d);
Instytut * znajdz(vector<Instytut> &wydzial);
template <typename type>
void sortuj(vector<type> &stringi);
int main()
{
    Pracownik_a dziekan;
    vector<Pracownik_a> prodziekani;
    vector<Instytut> wydzial;
    wydzial.push_back(Instytut("Dziekanat",1));
    string command;
    int numer, i;
    bool d;
    fstream file;
    Instytut* instytut;
    Naukowiec* n1,* n2;
    while(1)
    {
        pomoc();
        getline(cin, command);
        system("CLS");
        i=wykryj(command);
        switch (i)
        {
            case 1:
                file.open("elka.txt", fstream::in);
                while(file.peek())
                {
                    try
                    {
                        dodaj(wydzial, file, 0);
                    }
                    catch(int)
                    {
                        break;
                    }
                    i++;
                }
                file.close();
                system("CLS");
                break;
            case 2:
                try
                {
                    d=dodaj(wydzial, cin, 1);
                }
                catch(int)
                {
                    break;
                }
                break;
            case 3:
                try
                {
                instytut=znajdz(wydzial);
                }
                catch(int)
                {
                    break;
                }
                cout<<"Wpisz imie pracownika."<<endl;
                getline(cin, command);
                system("CLS");
                if(command=="exit") break;
                if(instytut->zwolnij(command))
                {
                    wydzial[0].zwolnij(command);
                    cout<<"Pracownik zwolniony"<<endl;
                    klik();
                    break;
                }
                cout<<"Pracownik nie odnaleziony. Powrot do menu."<<endl;
                klik();
                break;
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                try
                {
                operacja(wydzial,i);
                }
                catch(int)
                {
                    break;
                }
                break;
            case 9:
                pokaz(wydzial);
                break;
            case 10:
                return 0;
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
    if(command=="zabij") return 10;
    return 0;
}
void operacja(vector<Instytut> &wydzial, int n)
{
    Instytut* instytut;
    Naukowiec* n1,* n2;
    string command;
    int i;
    instytut=znajdz(wydzial);
    cout<<"Wpisz imie pracownika."<<endl;
    getline(cin, command);
    if(command=="exit") throw 1;
    n1=instytut->znajdz(command, 1);
    n2=instytut->znajdz(command, 0);
    if(n2==NULL) n2=wydzial[0].znajdz(command, 0);
    if((n1==NULL)&&(n2==NULL))
    {
        system("CLS");
        cout<<"Nie znaleziono pracownika. Powrot do menu."<<endl;
        klik();
        return;
    }
    if((n1)&&(n2))
    {
        system("CLS");
        cout<<"Odnaleziono dwie instancje pracownika:"<<endl<<endl;
        n1->druk();
        cout<<endl;
        n2->druk();
        klik();
    }
    switch(n)
    {
        case 4:
            if((n1)&&(n2))
            {
                cout<<"Dokonac degradacji stanowiska naukowego czy administracyjnego?"<<endl<<"a - administracyjne"<<endl<<"n - naukowe"<<endl;
                getline(cin, command);
                if(command=="exit") throw 1;
                if(command=="a") n1==NULL;
                else if(command=="n") n2==NULL;
                else
                {
                    cout<<"Nieznana komenda. Powrot do menu."<<endl;
                    return;
                }
            }
            system("CLS");
            if(n1)
            {
                if(!(n1->deg()))
                {
                    cout<<"Degradacja niemozliwa."<<endl;
                    klik();
                    return;
                }
            }
            if(n2)
            {
                if(!(n2->deg()))
                {
                    cout<<"Degradacja niemozliwa."<<endl;
                    klik();
                    return;
                }
                instytut->deg();
            }
            system("CLS");
            cout<<"Dokonano degradacji."<<endl;
            klik();
            return;
        case 5:
            if((n1)&&(n2))
            {
                cout<<"Dokonac promocji stanowiska naukowego czy administracyjnego?"<<endl<<"a - administracyjne"<<endl<<"n - naukowe"<<endl;
                getline(cin, command);
                if(command=="exit") throw 1;
                if(command=="a") n1==NULL;
                else if(command=="n") n2==NULL;
                else
                {
                    cout<<"Nieznana komenda. Powrot do menu."<<endl;
                    return;
                }
            }
            system("CLS");
            if(n1)
            {
                if(!(n1->prom()))
                {
                    cout<<"Promocja niemozliwa."<<endl;
                    klik();
                    return;
                }
            }
            if(n2)
            {
                if(!(instytut->pusty())||(!(n2->prom())))
                {
                    cout<<"Promocja niemozliwa."<<endl;
                    klik();
                    return;
                }
                instytut->prom(n2->coto());
            }
            system("CLS");
            cout<<"Dokonano Promocji."<<endl;
            klik();
            return;
        case 6:
            if(n1)
            {
                if(!(n1->prom_n()))
                {
                    cout<<"Promocja niemozliwa."<<endl;
                    klik();
                    return;
                }
            }
            if(n2)
            {
                if(!(n2->prom_n()))
                {
                    cout<<"Promocja niemozliwa."<<endl;
                    klik();
                    return;
                }
            }
            cout<<"Promocja naukowa dokonana."<<endl;
            klik();
        case 7:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 8:
            i=stop(cin, 1);
            if(!(i+1)) break;
            if(n1) n1->zmien_n(i);
            if(n2) n2->zmien_n(i);
            cout<<"Stopien naukowy zmieniony."<<endl;
            klik();
            return;
        default:
            return;;
    }
}
bool dodaj(vector<Instytut> &wydzial, istream &inp, bool d)
{
    int numer,i,j;
    string command;
    system("CLS");
    cout<<"Do jakiego instytutu ma nalezec pracownik?"<<endl<<"Aby utworzyc nowy instytut, wpisz '+'."<<endl<<"Aby dodac dziekana, badz prodziekana, wpisz 'Dziekanat'."<<endl<<"Aby wrocic do menu, wpisz 'exit'."<<endl;
    while(1)
    {
        if(wydzial.size()>1)
        {
            cout<<"Obecne instytuty:"<<endl;
            for(i=1;i<wydzial.size();i++)
            {
                cout<<wydzial[i].coto()<<endl;
            }
        }
        getline(inp,command,'\n');
        if(command=="exit") throw 1;
        if(command=="+")
        {
            system("CLS");
            cout<<"Wpisz nazwe nowego instytutu."<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            for(i=0;i<wydzial.size();i++)
            {
                if(wydzial[i].coto()==command) break;
            }
            if(i!=wydzial.size())
            {
                system("CLS");
                cout<<"Nazwa instytutu zajeta. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac nowy zaklad, badz 'Dziekanat' aby dodac dziekana lub prodziekana."<<endl;
                continue;
            }
            i=wydzial.size();
            wydzial.push_back(Instytut(command));
            system("CLS");
            wydzial[i].dodaj(inp, d);
            sortuj(wydzial);
            return true;
        }
        for(i=0;i<wydzial.size();i++)
        {
            if(wydzial[i].coto()==command) break;
        }
        if(i==wydzial.size())
        {
            system("CLS");
            cout<<"Instytut nie znaleziony. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac nowy instytut, badz 'Dziekanat' aby dodac dziekana lub prodziekana"<<endl;
            continue;
        }
        system("CLS");
        wydzial[i].dodaj(inp, d);
        return true;
    }
}
Instytut* znajdz(vector<Instytut> &wydzial)
{
    int i;
    string command;
    system("CLS");
    cout<<"Z jakim instytutem zwiazany jest pracownik?"<<endl<<"Jezeli pracownik jest zwiazany tylko z dziekanatem, wpisz 'Dziekanat'."<<endl<<"Aby wrocic do menu, wpisz 'exit'."<<endl;
    if(wydzial.size()>1)
    {
        cout<<"Obecne instytuty:"<<endl;
        for(i=1;i<wydzial.size();i++)
        {
            cout<<wydzial[i].coto()<<endl;
        }
    }
    while(1)
    {
        getline(cin, command);
        system("CLS");
        if(command=="exit") throw 1;
        for(i=0;i<wydzial.size();i++)
        {
            if(wydzial[i].coto()==command) return &wydzial[i];
        }
        if(i==wydzial.size())
        {
            system("CLS");
            cout<<"Instytut nie znaleziony. Wpisz nazwe instytutu jeszcze raz, badz 'Dziekanat' zeby zlokalizowac pracownika zwiazanego z dziekanatem."<<endl;
            continue;
        }
    }
}
bool zmien_n(vector<Instytut> &wydzial)
{
    /*string command;
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
    }*/
}
void pokaz(vector<Instytut> &wydzial)
{
    int i;
    system("CLS");
    cout<<"W Dziekanacie pracownicy to:"<<endl<<endl;
    wydzial[0].druk();
    klik();
    for(i=1;i<wydzial.size();i++)
    {
        cout<<"W instytucie:"<<endl<<wydzial[i].coto()<<endl<<endl<<"Pracownicy administracyjni to:"<<endl<<endl;
        wydzial[i].druk();
        klik();
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

