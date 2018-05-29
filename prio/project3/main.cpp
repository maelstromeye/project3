#include "klasy.h"
using namespace std;

void pomoc(void);   //wyswietl instrukcje

void pokaz(vector<Instytut> &wydzial);  //wyswietl zawartosc pamieci

void klik(void);    //kaze uzytkownikowi kliknac aby kontynuowac

void operacja(vector<Instytut> &wydzial, int n);    //operacja wymagajaca uzycia pracownikow

template <typename type>
void sortuj(vector<type> &stringi); //sortowanie alfabetyczne przez proste wybieranie

bool dodaj(vector<Instytut> &wydzial, istream& inp, bool d);    //dodawanie nowego pracownika (d - czy wyswietlac klik() przy funkcji)

int wykryj(string command); //determinuje jaka komenda byla wpisana

int stop(istream & inp, bool d);    //determinuje jaki stopien zostal zostal wpisany (definicja w klasy.cpp)

int praca(string command);  //determinuje jaka praca zostala wpisana (definicja w klasy.cpp)

Naukowiec * lokalizuj(Instytut &instytut, bool d);  //inicjalizuje znalezienie pracownika w instytucie (d==true - naukowego, d==false - administracyjnego)

Instytut * znajdz(vector<Instytut> &wydzial);   //znajduje instytut na wydziale

int main()
{
    vector<Instytut> wydzial;   //glowny vector danych
    wydzial.push_back(Instytut("Dziekanat",1)); //Dziekanat jest instytutem na miejscu 0
    string command; //string pomocniczy
    int i;  //counter
    fstream file;   //plik do czytania
    Instytut* instytut; //pomocniczy pointer
    Naukowiec* n1,* n2; //pomocnicze pointery
    while(1)
    {
        pomoc();    //instrukcje
        getline(cin, command);
        system("CLS");
        i=wykryj(command);  //co zrobic
        switch (i)
        {
            case 1: //inicjalizowac danymi z elka.txt
                file.open("elka.txt", fstream::in);
                while(1)
                {
                    try
                    {
                        dodaj(wydzial, file, 0);    //ladowanie danych z filestreama, bez pomocniczych klikow()
                    }
                    catch(int)  //jak znajdzie exit
                    {
                        break;
                    }
                    catch(bad_alloc)
                    {
                        cout<<"Niewystarczajaco pamieci. Powrot do menu."<<endl;
                        klik();
                        break;
                    }
                }
                file.close();
                system("CLS");
                break;
            case 2: //dodawanie z cin
                try
                {
                    dodaj(wydzial, cin, 1);   //ladowanie danych z cin, z pomocniczymi klikami()
                }
                catch(int)  //wpisane exit
                {
                    break;
                }
                catch(bad_alloc)
                {
                    cout<<"Niewystarczajaco pamieci. Powrot do menu."<<endl;
                    klik();
                    break;
                }
                break;
            case 3: //zwolnienie
                try
                {
                instytut=znajdz(wydzial);
                }
                catch(int)  //wpisane exit
                {
                    break;
                }
                cout<<"Wpisz imie pracownika."<<endl;
                getline(cin, command);
                system("CLS");
                if(command=="exit") break;  //wyjscie
                if(instytut->zwolnij(command))     //usuwanie pracownika
                {
                    wydzial[0].zwolnij(command);    //i jeszcze z dziekanatu, jezeli byly dwie instancje
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
            case 9: //degradacja, promocja, promocja naukowa, zmiana pracy naukowej, zmiana stopnia naukowego, szukanie
                try
                {
                operacja(wydzial,i);    //jak wyzej
                }
                catch(int)
                {
                    break;  //wpisane exit
                }
                break;
            case 10:
                pokaz(wydzial); //wyswietlanie
                break;
            case 11:    //zapis do pliku
                file.open("elka.txt", fstream::out);
                for(i=0;i<wydzial.size();i++)
                {
                    wydzial[i].pisz(file);
                }
                file<<"exit"<<endl;
                file.close();
                break;
            case 12:
                return 0;
            default:
                cout<<"Nieznana komenda"<<endl;
                klik();
                break;
        }
    }
    return 0;
}

void pomoc(void)    //instrukcje
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
    cout<<"-'zapisz' zeby zapisac dane do pliku elkat.txt"<<endl;
    cout<<"-'zabij' zeby zakonczyc dzialanie programu"<<endl;
    return;
}

int wykryj(string command)  //jaka komenda
{
    if(command=="elka") return 1;
    if(command=="dodaj") return 2;
    if(command=="zwolnij") return 3;
    if(command=="degraduj") return 4;
    if(command=="promuj") return 5;
    if(command=="promuj_n") return 6;
    if(command=="zmien") return 7;
    if(command=="zmien_n") return 8;
    if(command=="znajdz") return 9;
    if(command=="pokaz") return 10;
    if(command=="zapisz") return 11;
    if(command=="zabij") return 12;
    return 0;
}

void pokaz(vector<Instytut> &wydzial)   //wypisz wszystko
{
    int i;  //counter
    system("CLS");
    cout<<"W Dziekanacie pracownicy to:"<<endl<<endl;
    wydzial[0].druk();  //wypisz dziekanat
    klik();
    for(i=1;i<wydzial.size();i++)   //wypisanie reszty
    {
        cout<<"W instytucie:"<<endl<<wydzial[i].coto()<<endl<<endl<<"Pracownicy administracyjni to:"<<endl<<endl;
        wydzial[i].druk();
        klik();
    }
    return;
}

template <typename type>
void sortuj(vector<type> &stringi)  //sortowanie vectorow majacych metode coto() przez prosty wybor
{
    int i,j,numer;  //countery
    string temp;    //pomocniczy string
    type obiekt;    //pomocniczy obiekt
    temp="~";   //zeby na pewno sie przesuwalo
    for(j=0;j<stringi.size();j++)   //prosty wybor
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

bool dodaj(vector<Instytut> &wydzial, istream &inp, bool d) //dodawanie pracownika z inputu
{
    int numer,i,j;  //countery
    string command; //pomocniczy string
    system("CLS");
    cout<<"Do jakiego instytutu ma nalezec pracownik?"<<endl<<"Aby utworzyc nowy instytut, wpisz '+'."<<endl<<"Aby dodac dziekana, badz prodziekana, wpisz 'Dziekanat'."<<endl<<"Aby wrocic do menu, wpisz 'exit'."<<endl;
    while(1)
    {
        if(wydzial.size()>1)    //wypisanie obecnych
        {
            cout<<"Obecne instytuty:"<<endl;
            for(i=1;i<wydzial.size();i++)
            {
                cout<<wydzial[i].coto()<<endl;
            }
        }
        getline(inp,command,'\n');
        if(command=="exit") throw 1;
        if(command=="+")    //dodanie nowego
        {
            system("CLS");
            cout<<"Wpisz nazwe nowego instytutu."<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            for(i=0;i<wydzial.size();i++)   //imie moze byc zajete
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
            wydzial.push_back(Instytut(command));   //dodawanie
            system("CLS");
            try
            {
                wydzial[i].dodaj(inp, d);   //dodawanie pracownika
            }
            catch(int)  //sprzatamy jezeli ktos wyszedl
            {
                wydzial.erase(wydzial.begin()+i);
                throw 1;
            }
            sortuj(wydzial);    //alfabetycznie
            return true;
        }
        for(i=0;i<wydzial.size();i++)   //czy istnieje
        {
            if(wydzial[i].coto()==command) break;
        }
        if(i==wydzial.size())
        {
            system("CLS");  //nie istnieje
            cout<<"Instytut nie znaleziony. Wpisz nazwe instytutu jeszcze raz, badz '+' zeby dodac nowy instytut, badz 'Dziekanat' aby dodac dziekana lub prodziekana"<<endl;
            continue;
        }
        system("CLS");
        wydzial[i].dodaj(inp, d);
        return true;
    }
}

Instytut* znajdz(vector<Instytut> &wydzial) //odnajdywanie instytutu w wydziele
{
    int i;  //counter
    string command; //pomocniczy string
    system("CLS");
    cout<<"Z jakim instytutem zwiazany jest pracownik?"<<endl<<"Jezeli pracownik jest zwiazany tylko z dziekanatem, wpisz 'Dziekanat'."<<endl<<"Aby wrocic do menu, wpisz 'exit'."<<endl;
    while(1)
    {
        if(wydzial.size()>1)    //wypisz obecne
        {
            cout<<"Obecne instytuty:"<<endl;
            for(i=1;i<wydzial.size();i++)
            {
                cout<<wydzial[i].coto()<<endl;
            }
        }
        getline(cin, command);
        system("CLS");
        if(command=="exit") throw 1;
        for(i=0;i<wydzial.size();i++)   //szukamy
        {
            if(wydzial[i].coto()==command) return &wydzial[i];
        }
        if(i==wydzial.size())
        {
            system("CLS");  //nie ma
            cout<<"Instytut nie znaleziony. Wpisz nazwe instytutu jeszcze raz, badz 'Dziekanat' zeby zlokalizowac pracownika zwiazanego z dziekanatem."<<endl;
            continue;
        }
    }
    return NULL;
}

void operacja(vector<Instytut> &wydzial, int n) //zajmowanie sie operacjami na pracownikach
{
    Instytut* instytut; //pointer pomocniczy
    Naukowiec* n1,* n2; //pointery pomocnicze
    string command; //string do przechowywania inputu
    int i;  //counter
    instytut=znajdz(wydzial);   //znajdz jaki instytut
    cout<<"Wpisz imie pracownika."<<endl;
    getline(cin, command);
    if(command=="exit") throw 1;    //exit
    n1=instytut->znajdz(command, 1);    //pracownik naukowy
    n2=instytut->znajdz(command, 0);    //i administracyjny
    if(n2==NULL) n2=wydzial[0].znajdz(command, 0);  //jeszcze moze w dziekanacie?
    if((n1==NULL)&&(n2==NULL))  //nic nie znalazlo
    {
        system("CLS");
        cout<<"Nie znaleziono pracownika. Powrot do menu."<<endl;
        klik();
        return;
    }
    if((n1)&&(n2))  //2 instancje
    {
        system("CLS");
        cout<<"Odnaleziono dwie instancje pracownika:"<<endl<<endl;
        n1->druk();
        cout<<endl;
        n2->druk();
        klik();
    }
    else if(n1) n1->druk(); //1 instancja
    else n2->druk();
    switch(n)   //co zrobic
    {
        case 4: //degradacja
            if((n1)&&(n2))  //2 instancje
            {
                cout<<"Dokonac degradacji stanowiska naukowego czy administracyjnego?"<<endl<<"a - administracyjne"<<endl<<"n - naukowe"<<endl;
                getline(cin, command);
                if(command=="exit") throw 1;
                if(command=="a") n1==NULL;  //po prostu zerujemy jeden jak drugiej chcemy dokomncac
                else if(command=="n") n2==NULL;
                else
                {
                    cout<<"Nieznana komenda. Powrot do menu."<<endl;
                    return;
                }
            }
            system("CLS");
            if(n1)  //naukowa
            {
                if(!(n1->deg()))
                {
                    cout<<"Degradacja niemozliwa."<<endl;
                    klik();
                    return;
                }
            }
            if(n2)  //administracyjna
            {
                if(!(n2->deg()))
                {
                    cout<<"Degradacja niemozliwa."<<endl;
                    klik();
                    return;
                }
                instytut->deg();    //dodatkowa operacje (przesunieie dyrektora do zastepcow)
            }
            system("CLS");
            cout<<"Dokonano degradacji."<<endl;
            klik();
            return;
        case 5: //promocja
            if((n1)&&(n2))  //2 instancje
            {
                cout<<"Dokonac promocji stanowiska naukowego czy administracyjnego?"<<endl<<"a - administracyjne"<<endl<<"n - naukowe"<<endl;
                getline(cin, command);
                if(command=="exit") throw 1;
                if(command=="a") n1==NULL;  //jak w degradacji
                else if(command=="n") n2==NULL;
                else
                {
                    cout<<"Nieznana komenda. Powrot do menu."<<endl;
                    return;
                }
            }
            system("CLS");
            if(n1)  //naukowa
            {
                if(!(n1->prom()))
                {
                    cout<<"Promocja niemozliwa."<<endl;
                    klik();
                    return;
                }
            }   //administracyjna
            if(n2)
            {
                if(!(instytut->pusty())||(!(n2->prom())))
                {
                    cout<<"Promocja niemozliwa."<<endl;
                    klik();
                    return;
                }
                instytut->prom(n2->coto()); //dodatkowa operacja (przesuniacia zastepcy do dyrektora)
            }
            system("CLS");
            cout<<"Dokonano Promocji."<<endl;
            klik();
            return;
        case 6: //promocja naukowa
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
            }   //nie trzeba poprawiac nic w tym ifie bo zawsze beda mieli te same stopnie
            cout<<"Promocja naukowa dokonana."<<endl;
            klik();
        case 7: //zmiana pracy naukowej
            if(n1)  //naukowy pracownik
            {
                cout<<"Sprecyzuj nowa prace naukowa pracownika"<<endl<<"lkt - lektor"<<endl<<"asy - asystent"<<endl<<"wyk - wykladowca"<<endl<<"adu - adiunkt"<<endl<<"stw - starszy wykladowca"<<endl<<"pnz - profesor nadzwyczajny"<<endl<<"doc - docent"<<endl<<"prz - profesor zwyczajny"<<endl;
                getline(cin, command);
                system("CLS");
                if(command=="exit") throw 1;
                i=praca(command);   //rozpoznanie inputu
                if(!(i+1))
                {
                    cout<<"Nieznana praca. Powrot do menu."<<endl;
                    klik();
                    return;
                }
                n1->zmien(i);   //zmiana pracy
                cout<<"Praca zmieniona."<<endl;
                klik();
            }
            if(n2)  //administracyjny pracownik
            {
                cout<<"Nie mozna zmienic pracy pracownika administracyjnego. Powrot do menu."<<endl;
                klik();
                return;
            }
            return;
        case 8: //zmiana stopnia naukowego
            i=stop(cin, 1); //rozpoznanie inputu
            if(!(i+1)) break;   //zla praca
            if(n1) n1->zmien_n(i);  //zmiana
            if(n2) n2->zmien_n(i);
            cout<<"Stopien naukowy zmieniony."<<endl;
            klik();
            return;
        case 9: //znalezienie (juz sie dokonalo)
            klik();
        default:
            return;;
    }
}
