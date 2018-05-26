#include "klasy.h"
using namespace std;
void klik(void)
{
    string temp;
    cout<<"Kliknij enter aby kontynuowac."<<endl;
    getline(cin,temp);
    system("CLS");
}
int stop(istream &inp, bool d)
{
    string command;
    cout<<"Wpisz profesje naukowa"<<endl<<"non - brak dyplomu"<<endl<<"lic - licencjat"<<endl<<"eng - inzynier"<<endl<<"mag - magister"<<endl<<"dok - doktor"<<endl<<"dhb - doktor habilitowany"<<endl<<"pro - profesor"<<endl;
    getline(inp,command,'\n');
    system("CLS");
    if(command=="exit") throw 1;
    if(command=="non") return 0;
    if(command=="lic") return 1;
    if(command=="eng") return 2;
    if(command=="mag") return 3;
    if(command=="dok") return 4;
    if(command=="dhb") return 5;
    if(command=="pro") return 6;
    cout<<"Nieznany stopien. Powtorz krok."<<endl;
    if(d) klik();
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
void Instytut::prom(string command)
{
    int i;
    for(i=0;i<zastepcy.size();i++)
    {
        if(command==zastepcy[i].coto()) break;
    }
    dyrektor=zastepcy[i];
    zastepcy.erase(zastepcy.begin()+i);
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
    }
    return;
}
void Pracownik_a::druk(void)
{
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

void Pracownik_n::druk(void)
{
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
void Instytut::druk(void)
{
    int i;
    if(!(dyrektor.pusty())) dyrektor.druk();
    cout<<endl;
    for(i=0;i<zastepcy.size();zastepcy[i].druk(),cout<<endl,i++);
    if(imie=="Dziekanat") return;
    cout<<"Pracownicy naukowi to:"<<endl<<endl;
    for(i=0;i<this->size();this->at(i).druk(),cout<<endl,i++);
    cout<<"Zaklady i ich kierownicy to:"<<endl<<endl;
    for(i=0;i<zaklady.size();i++)
    {
        cout<<"W zakladzie:"<<endl<<zaklady[i].coto()<<endl<<endl;
        zaklady[i].druk();
        cout<<endl;
    }
    return;
}
bool Instytut::zwolnij(string command)
{
    int i, flag=0;
    for(i=0;i<this->size();i++)
    {
        if(this->at(i).coto()==command)
        {
            this->erase(this->begin()+i);
            flag=1;
            break;
        }
    }
    for(i=0;i<zaklady.size();i++)
    {
        if(zaklady[i].ktorzadzi()==command)
        {
            zaklady.erase(zaklady.begin()+i);
            return true;
        }
    }
    for(i=0;i<zastepcy.size();i++)
    {
        if(zastepcy[i].coto()==command)
        {
            zastepcy.erase(zastepcy.begin()+i);
            return true;
        }
    }
    if(dyrektor.coto()==command)
    {
        dyrektor=Pracownik_a();
        return true;
    }
    if (flag) return true;
    return false;
}
Naukowiec* Instytut::znajdz(std::string command, bool d)
{
    int i;
    if(d)
    {
        for(i=0;i<this->size();i++)
        {
            if(this->at(i).coto()==command) return &(this->at(i));
        }
        return NULL;
    }
    if(dyrektor.coto()==command) return &dyrektor;
    for(i=0;i<zastepcy.size();i++)
    {
        if(zastepcy[i].coto()==command) return &(zastepcy[i]);
    }
    for(i=0;i<zaklady.size();i++)
    {
        if(zaklady[i].ktorzadzi()==command) return zaklady[i].toon();
    }
    return NULL;
}
void Instytut::dodaj(istream &inp, bool d)
{
    int i,j,k;
    i=j=k=0;
    string command,nazwa;
    while(1)
    {
        if(imie=="Dziekanat") cout<<"Sprecyzuj prace pracownika:"<<endl<<"dzi - dziekan"<<endl<<"prd - prodziekan"<<endl;
        else cout<<"Sprecyzuj prace pracownika"<<endl<<"din - dyrektor instytutu"<<endl<<"zdi - zastepca dyrektora"<<endl<<"kza - kierownik zakladu"<<endl<<"lkt - lektor"<<endl<<"asy - asystent"<<endl<<"wyk - wykladowca"<<endl<<"adu - adiunkt"<<endl<<"stw - starszy wykladowca"<<endl<<"pnz - profesor nadzwyczajny"<<endl<<"doc - docent"<<endl<<"prz - profesor zwyczajny"<<endl;
        getline(inp,command,'\n');
        if(command=="exit") throw 1;
        if(command=="kza")
        {
            if(imie=="Dziekanat")
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
            for(k=0;k<zaklady.size();k++)
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
            nazwa=command;
            system("CLS");
            i=stop(inp, d);
            if(!(i+1)) continue;
            cout<<"Wpisz imie pracownika"<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            if(this->znajdz(command, 0))
            {
                system("CLS");
                cout<<"Istnieje pracownik o podanym imieniu. Powtorz krok."<<endl;
                if(d) klik();
                continue;
            }
            zaklady.push_back(Zaklad(i,command,nazwa));
            system("CLS");
            cout<<"Dodano pracownika:"<<endl;
            zaklady[zaklady.size()-1].druk();
            cout<<"W instytucie:"<<endl<<imie<<endl<<"W zakladzie:"<<endl<<zaklady[zaklady.size()-1].coto()<<endl;
            sortuj(zaklady);
            if(d) klik();
            return;
        }
        if((command=="din")||(command=="zdi")||(command=="prd")||(command=="dzi"))
        {
            if((command=="din")||(command=="dzi")) k=1;
            else k=0;
            if((!dyrektor.pusty()&&(k)))
            {
                system("CLS");
                if(imie=="Dziekanat") cout<<"Wydzial posiada dziekana. Powtorz krok."<<endl;
                else cout<<"Instytut posiada dyrektora. Powtorz krok."<<endl;
                if(d) klik();
                continue;
            }
            system("CLS");
            i=stop(inp, d);
            if(!(i+1)) continue;
            cout<<"Wpisz imie pracownika"<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            if(!k)
            {
                if(this->znajdz(command, 0))
                {
                    system("CLS");
                    cout<<"Istnieje pracownik o podanym imieniu. Powtorz krok."<<endl;
                    if(d) klik();
                    continue;
                }
                if(imie=="Dziekanat") zastepcy.push_back(Pracownik_a(i,2,command));
                else zastepcy.push_back(Pracownik_a(i,4,command));
                system("CLS");
                cout<<"Dodano pracownika:"<<endl;
                zastepcy[zastepcy.size()-1].druk();
                if(imie=="Dziekanat") cout<<"W Dziekanacie"<<endl;
                else cout<<"W instytucie:"<<endl<<imie<<endl;
                sortuj(zastepcy);
                if(d) klik();
                return;
            }
            else
            {
                if(imie=="Dziekanat") dyrektor=Pracownik_a(i,1,command);
                else dyrektor=Pracownik_a(i,3,command);
                system("CLS");
                cout<<"Dodano pracownika:"<<endl;
                dyrektor.druk();
                if(imie=="Dziekanat") cout<<"W Dziekanacie"<<endl;
                else cout<<"W instytucie:"<<endl<<imie<<endl;
                if(d) klik();
                return;
            }
        }
        j=praca(command);
        if(!(j+1))
        {
            system("CLS");
            cout<<"Nieznana praca. Powtorz krok."<<endl;
            if(d) klik();
            continue;
        }
        system("CLS");
        if(imie=="Dziekanat")
        {
            system("CLS");
            cout<<"W dziekanacie nie moga istniec pracownicy naukowi. Powtorz krok.";
            if(d) klik();
            continue;
        }
        i=stop(inp, d);
        if(!(i+1)) continue;
        cout<<"Wpisz imie pracownika"<<endl;
        getline(inp,command,'\n');
        if(command=="exit") throw 1;
        if(this->znajdz(command,1))
        {
            system("CLS");
            cout<<"Istnieje pracownik o podanym imieniu. Powtorz krok."<<endl;
            if(d) klik();
            continue;
        }
        this->push_back(Pracownik_n(i,j,command));
        system("CLS");
        cout<<"Dodano pracownika:"<<endl;
        this->at(this->size()-1).druk();
        cout<<"W instytucie:"<<endl<<imie<<endl;
        sortuj(*this);
        if(d) klik();
        return;
    }
}

