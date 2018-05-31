#include "Instytut.h"
using namespace std;
void klik(void);
int stop(istream &inp, bool d);
int praca(string command);

template <typename type>
void sortuj(vector<type> &stringi)  //sortowanie przez prosty wybor, identyczne do tego zdefiniowanego w mainie
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
    }
    return;
}

void Instytut::druk(void)   //druk do cout
{
    int i;  //counter
    if(!(dyrektor.pusty())) dyrektor.druk();    //najpierw dyrektor
    cout<<endl;
    for(i=0;i<zastepcy.size();zastepcy[i].druk(),cout<<endl,i++);   //potem zastepcy
    if(imie=="Dziekanat") return;   //w dziekanacie nie ma nikogo innego
    cout<<"Pracownicy naukowi to:"<<endl<<endl; //reszta pracownikow
    for(i=0;i<this->size();this->at(i).druk(),cout<<endl,i++);
    if(!(zaklady.empty())) cout<<"Zaklady i ich kierownicy to:"<<endl<<endl;
    for(i=0;i<zaklady.size();i++)   //i zaklady na koncu
    {
        cout<<"W zakladzie:"<<endl<<zaklady[i].coto()<<endl<<endl;
        zaklady[i].druk();
        cout<<endl;
    }
    return;
}

void Instytut::prom(string command) //promuj zastepce o imieniu command do dyrektora
{
    int i;  //counter
    for(i=0;i<zastepcy.size();i++)  //szukamy
    {
        if(command==zastepcy[i].coto()) break;
    }
    if(i==zastepcy.size()) return;  //nic nie mamy
    dyrektor=zastepcy[i];   //cos mamy
    zastepcy.erase(zastepcy.begin()+i); //usuwamy to co bylo
    return;
}

bool Instytut::zwolnij(string command)  //zwolnienie pracownika o imieniu command
{
    int i, flag=0;  //counter, czy znaleziono
    for(i=0;i<this->size();i++) //znajdz instancje w glownym wektorze
    {
        if(this->at(i).coto()==command)
        {
            this->erase(this->begin()+i);
            flag=1; //cos znaleziono
            break;
        }
    }
    for(i=0;i<zaklady.size();i++)   //znajdz instancje w zakladach
    {
        if(zaklady[i].toon()->coto()==command)
        {
            zaklady.erase(zaklady.begin()+i);
            return true;    //juz nigdzie indziej nie bedzie
        }
    }
    for(i=0;i<zastepcy.size();i++)  //znajdz instancje w zastepcah
    {
        if(zastepcy[i].coto()==command)
        {
            zastepcy.erase(zastepcy.begin()+i);
            return true;    //juz nigdzie indziej nie bedzie
        }
    }
    if(dyrektor.coto()==command)    //moze dyrektor?
    {
        dyrektor=Pracownik_a();
        return true;    //nigdzie indziej nie bedzie
    }
    if (flag) return true;  //jezeli tylko w glownym bylo
    return false;   //nigdzie
}

Naukowiec* Instytut::znajdz(std::string command, bool d)    //znajdujemy pracownika o imieniu, d==1 - w wektorze glownym, d==0 w pobocznych
{
    int i;  //counter
    if(d)   //czy w glownym
    {
        for(i=0;i<this->size();i++) //szukamy
        {
            if(this->at(i).coto()==command) return &(this->at(i));
        }
        return NULL;    //nikogo nie ma
    }
    if(dyrektor.coto()==command) return &dyrektor;  //moze dyrektor?
    for(i=0;i<zastepcy.size();i++)  //moze zastepca?
    {
        if(zastepcy[i].coto()==command) return &(zastepcy[i]);
    }
    for(i=0;i<zaklady.size();i++)   //moze w zakladzie?
    {
        if(zaklady[i].toon()->coto()==command) return zaklady[i].toon();
    }
    return NULL;    //nigdzie
}

void Instytut::pisz(fstream &out)   //pisz do pliku
{
    int i;  //counter
    if(this->coto()!="Dziekanat") out<<"+"<<endl;   //jezeli nie dziekanat to musimy najpierw dodac
    out<<imie<<endl;    //nazwa instytutu
    dyrektor.pisz(out); //dyrektor
    for(i=0;i<zastepcy.size();i++)  //potem zastepcy
    {
        out<<imie<<endl;    //z nazwa koniecznie, zebysmy przeczytali
        zastepcy[i].pisz(out);
    }
    for(i=0;i<zaklady.size();i++)   ////potem zaklady
    {
        out<<imie<<endl<<"kza"<<endl<<zaklady[i].coto()<<endl;  //tu trzeba troche obejsc, zeby wpisac w sroduku nazwe zakladu
        zaklady[i].pisz(out);
    }
    for(i=0;i<this->size();i++) //potem wektor glowny
    {
        out<<imie<<endl;    //najpierw nazwa
        this->at(i).pisz(out);  //potem oosba
    }
    return;
}

void Instytut::dodaj(istream &inp, bool d)  //dodanie pracownika, d - czy wyswietlac kliki
{
    int i,j,k;  //countery
    i=j=k=0;
    string command,nazwa;   //stringi pomocnicze
    while(1)
    {
        if(imie=="Dziekanat") cout<<"Sprecyzuj prace pracownika:"<<endl<<"dzi - dziekan"<<endl<<"prd - prodziekan"<<endl;   //jezeli dodajemy do dziekanatu
        else cout<<"Sprecyzuj prace pracownika"<<endl<<"din - dyrektor instytutu"<<endl<<"zdi - zastepca dyrektora"<<endl<<"kza - kierownik zakladu"<<endl<<"lkt - lektor"<<endl<<"asy - asystent"<<endl<<"wyk - wykladowca"<<endl<<"adu - adiunkt"<<endl<<"stw - starszy wykladowca"<<endl<<"pnz - profesor nadzwyczajny"<<endl<<"doc - docent"<<endl<<"prz - profesor zwyczajny"<<endl;
        getline(inp,command,'\n');
        if(command=="exit") throw 1;
        if(command=="kza")  //jezeli dodajemy kierownika
        {
            if(imie=="Dziekanat")   //jak w coucie ponizej
            {
                system("CLS");
                cout<<"W dziekanacie nie moga istniec zaklady. Powtorz krok.";
                if(d) klik();
                continue;
            }
            system("CLS");
            cout<<"Wpisz nazwe nowego zakladu ktorego pracownik ma byc kierownikiem."<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            for(k=0;k<zaklady.size();k++)   //szukamy czy istnieje
            {
                if(zaklady[k].coto()==command) break;
            }
            if(k!=zaklady.size())
            {
                system("CLS");
                cout<<"Istnieje zaklad o podanym imieniu. Powtorz krok."<<endl;
                if(d) klik();
                continue;
            }
            nazwa=command;  //zapisujemy nazwe
            system("CLS");
            i=stop(inp, d); //jaki stopien kierownika
            if(!(i+1)) continue;    //moze nieprawidlowy?
            cout<<"Wpisz imie pracownika"<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            if(this->znajdz(command, 0))    //szukamy pracownika o podanym imieniu... jak w coucie ponizej anyway
            {
                system("CLS");
                cout<<"Istnieje pracownik o podanym imieniu. Powtorz krok."<<endl;
                if(d) klik();
                continue;
            }
            zaklady.push_back(Zaklad(i,command,nazwa)); //nowy zaklad
            system("CLS");
            cout<<"Dodano pracownika:"<<endl;
            zaklady[zaklady.size()-1].druk();
            cout<<"W instytucie:"<<endl<<imie<<endl<<"W zakladzie:"<<endl<<zaklady[zaklady.size()-1].coto()<<endl;
            sortuj(zaklady);    //sortujemy alfabetycznie
            if(d) klik();
            return;
        }
        if((command=="din")||(command=="zdi")||(command=="prd")||(command=="dzi"))  //rzeczy do zapisania w dyrektorze badz zastepcach
        {
            if((command=="din")||(command=="dzi")) k=1; //rzecz do zapisania w wektorze
            else k=0;   //badz w zastepcach
            if((!dyrektor.pusty()&&(k)))    //nie mozna dodac nikogo na pozycji dyrektora
            {
                system("CLS");
                if(imie=="Dziekanat") cout<<"Wydzial posiada dziekana. Powtorz krok."<<endl;
                else cout<<"Instytut posiada dyrektora. Powtorz krok."<<endl;
                if(d) klik();
                continue;
            }
            system("CLS");
            i=stop(inp, d); //jaki stopien pracownika
            if(!(i+1)) continue;
            cout<<"Wpisz imie pracownika"<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            if(!k)  //jezeli do zapisania w zastepcah
            {
                if(this->znajdz(command, 0))    //czy juz taki ktos jest
                {
                    system("CLS");
                    cout<<"Istnieje pracownik o podanym imieniu. Powtorz krok."<<endl;
                    if(d) klik();
                    continue;
                }
                if(imie=="Dziekanat") zastepcy.push_back(Pracownik_a(i,2,command)); //zapisujemy prodziekana
                else zastepcy.push_back(Pracownik_a(i,4,command));  //zapisujemy zastepce
                system("CLS");
                cout<<"Dodano pracownika:"<<endl;
                zastepcy[zastepcy.size()-1].druk();
                if(imie=="Dziekanat") cout<<"W Dziekanacie"<<endl;
                else cout<<"W instytucie:"<<endl<<imie<<endl;
                sortuj(zastepcy);   //sortujemy
                if(d) klik();
                return;
            }
            else    //ktos do zapisania w dyrektorze
            {
                if(imie=="Dziekanat") dyrektor=Pracownik_a(i,1,command);    //dziekan
                else dyrektor=Pracownik_a(i,3,command); //dyrektor
                system("CLS");
                cout<<"Dodano pracownika:"<<endl;
                dyrektor.druk();
                if(imie=="Dziekanat") cout<<"W Dziekanacie"<<endl;
                else cout<<"W instytucie:"<<endl<<imie<<endl;
                if(d) klik();
                return;
            }
        }
        j=praca(command);   //rozpoznajemy prace (teraz juz na pewno naukowa)
        if(!(j+1))  //jak nizej w coucie
        {
            system("CLS");
            cout<<"Nieznana praca. Powtorz krok."<<endl;
            if(d) klik();
            continue;
        }
        system("CLS");
        if(imie=="Dziekanat")   //jak nizej w coucie
        {
            system("CLS");
            cout<<"W dziekanacie nie moga istniec pracownicy naukowi. Powtorz krok.";
            if(d) klik();
            continue;
        }
        i=stop(inp, d); //jaki stopien pracownika
        if(!(i+1)) continue;
        cout<<"Wpisz imie pracownika"<<endl;
        getline(inp,command,'\n');
        if(command=="exit") throw 1;
        if(this->znajdz(command,1)) //istnieje juz moze?
        {
            system("CLS");
            cout<<"Istnieje pracownik o podanym imieniu. Powtorz krok."<<endl;
            if(d) klik();
            continue;
        }
        this->push_back(Pracownik_n(i,j,command));  //zapisujemy
        system("CLS");
        cout<<"Dodano pracownika:"<<endl;
        this->at(this->size()-1).druk();
        cout<<"W instytucie:"<<endl<<imie<<endl;
        sortuj(*this);  //sortujemy
        if(d) klik();
        return;
    }
}
