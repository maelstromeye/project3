#include "klasy.h"
using namespace std;
//enum Stopien {non, lic, eng, mag, dok, dhb, pro};
//enum Praca_n {lkt, asy, wyk, adu, stw, pnz, doc, prz};
//enum Praca_a {kza, dzi, prd, din, zdi};
void pomoc(void);
int wykryj(string command);
int stop(string command);
void elka(void);
bool dodaj(vector<Instytut> &wydzial, istream& inp, bool d);
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
    wydzial.push_back(Instytut("Dziekanat",1));
    string command;
    int numer, i;
    bool d;
    fstream file;
    while(1)
    {
        pomoc();
        getline(cin, command);
        switch (wykryj(command))
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
                cout<<wydzial[0].size()<<endl<<wydzial[1].size();
                break;
            case 2:
                try
                {
                    d=dodaj(wydzial, cin, 1);
                }  //czy dodac dziekana
                catch(int)
                {
                    break;
                }
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
                            cout<<"Wydzial posiada dziekana. Powtorz krok."<<endl;
                            klik();
                            continue;
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
bool dodaj(vector<Instytut> &wydzial, istream &inp, bool d)
{
    int numer,i,j;
    string command;
    vector<string> stringi;
    vector<int> kolej;
    char b;
    system("CLS");
    cout<<"Do jakiego instytutu ma nalezec pracownik?"<<endl;
    cout<<"Aby utworzyc nowy instytut, wpisz '+'."<<endl;
    cout<<"Aby dodac dziekana, badz prodziekana, wpisz 'dziekanat'."<<endl;
    cout<<"Aby wrocic do menu, wpisz 'exit'."<<endl;
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
        getline(inp,command,'\n');
        if(command=="dziekanat") return false;
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
                cout<<"Nazwa instytutu zajeta. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac nowy zaklad, badz '++' aby dodac dziekana lub prodziekana."<<endl;
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
            cout<<"Instytut nie znaleziony. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac nowy instytut, badz '++' aby dodac dziekana lub prodziekana"<<endl;
            continue;
        }
        system("CLS");
        wydzial[i].dodaj(inp, d);
        return true;
    }
}

bool zwolnij(void){}
bool degraduj(void){}
bool promuj(void){}
bool promuj_n(void){}
bool zmien(void){}
bool lokalizuj(vector<Instytut> &wydzial,int &i,int &j,int &k)
{
    /*string command;
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
            if(wydzial[i].coto()==command) break;
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
    }*/
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
    for(i=0;i<wydzial.size();i++)
    {
        system("CLS");
        cout<<"W instytucie:"<<endl<<wydzial[i].coto()<<endl<<endl<<"Pracownicy administracyjni to:"<<endl<<endl;
        wydzial[i].druk();
        klik();
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

