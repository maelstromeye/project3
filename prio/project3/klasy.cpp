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
void klik(void)
{
    string temp;
    cout<<"Kliknij enter aby kontynuowac."<<endl;
    getline(cin,temp);
    system("CLS");
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
    dyrektor.druk();
    cout<<endl;
    for(i=0;i<zastepcy.size();zastepcy[i].druk(),cout<<endl,i++);
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
void Instytut::dodaj(istream &inp, bool d)
{
    int i,j,k;
    i=j=k=0;
    string command,nazwa;
    while(1)
    {
        cout<<"Sprecyzuj prace pracownika"<<endl<<"din - dyrektor instytutu"<<endl<<"zdi - zastepca dyrektora"<<endl<<"kza - kierownik zakladu"<<endl<<"lkt - lektor"<<endl<<"asy - asystent"<<endl<<"wyk - wykladowca"<<endl<<"adu - adiunkt"<<endl<<"stw - starszy wykladowca"<<endl<<"pnz - profesor nadzwyczajny"<<endl<<"doc - docent"<<endl<<"prz - profesor zwyczajny"<<endl;
        getline(inp,command,'\n');
        if(command=="exit") throw 1;
        if(command=="kza")
        {
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
            cout<<"Wpisz profesje naukowa"<<endl<<"non - brak dyplomu"<<endl<<"lic - licencjat"<<endl<<"eng - inzynier"<<endl<<"mag - magister"<<endl<<"dok - doktor"<<endl<<"dhb - doktor habilitowany"<<endl<<"pro - profesor"<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            i=stop(command);
            if(!(i+1))
            {
                system("CLS");
                cout<<"Nieznany stopien. Powtorz krok."<<endl;
                if(d) klik();
                continue;
            }
            system("CLS");
            cout<<"Wpisz imie pracownika"<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            zaklady.push_back(Zaklad(i,command,nazwa));
            system("CLS");
            cout<<"Dodano pracownika:"<<endl;
            zaklady[zaklady.size()-1].druk();
            cout<<"W instytucie:"<<endl<<imie<<endl<<"W zakladzie:"<<endl<<zaklady[zaklady.size()-1].coto()<<endl;
            sortuj(zaklady);
            if(d) klik();
            return;
        }
        if((command=="din")||(command=="zdi"))
        {
            if (command=="din") k=1;
            else k=0;
            if((!dyrektor.pusty()&&(k)))
            {
                system("CLS");
                cout<<"Instytut posiada dyrektora. Powtorz krok."<<endl;
                if(d) klik();
                continue;
            }
            system("CLS");
            cout<<"Wpisz profesje naukowa"<<endl<<"non - brak dyplomu"<<endl<<"lic - licencjat"<<endl<<"eng - inzynier"<<endl<<"mag - magister"<<endl<<"dok - doktor"<<endl<<"dhb - doktor habilitowany"<<endl<<"pro - profesor"<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            i=stop(command);
            if(!(i+1))
            {
                system("CLS");
                cout<<"Nieznany stopien. Powtorz krok."<<endl;
                if(d) klik();
                continue;
            }
            system("CLS");
            cout<<"Wpisz imie pracownika"<<endl;
            getline(inp,command,'\n');
            if(command=="exit") throw 1;
            if(!k)
            {
                for(k=0;k<zastepcy.size();k++)
                {
                    if(zastepcy[k].coto()==command) break;
                }
                if(k!=zastepcy.size())
                {
                    system("CLS");
                    cout<<"Istnieje pracownik o podanym imieniu. Powtorz krok."<<endl;
                    if(d) klik();
                    continue;
                }
                zastepcy.push_back(Pracownik_a(i,4,command));
                system("CLS");
                cout<<"Dodano pracownika:"<<endl;
                zastepcy[zastepcy.size()-1].druk();
                cout<<"W instytucie:"<<endl<<imie<<endl;
                sortuj(zastepcy);
                if(d) klik();
                return;
            }
            else
            {
                dyrektor=Pracownik_a(i,3,command);
                system("CLS");
                cout<<"Dodano pracownika:"<<endl;
                dyrektor.druk();
                cout<<"W instytucie:"<<endl<<imie<<endl;
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
        cout<<"Wpisz profesje naukowa"<<endl<<"non - brak dyplomu"<<endl<<"lic - licencjat"<<endl<<"eng - inzynier"<<endl<<"mag - magister"<<endl<<"dok - doktor"<<endl<<"dhb - doktor habilitowany"<<endl<<"pro - profesor"<<endl;
        getline(inp,command,'\n');
        if(command=="exit") throw 1;
        i=stop(command);
        if(!(i+1))
        {
            system("CLS");
            cout<<"Nieznany stopien. Powtorz krok."<<endl;
            if(d) klik();
            continue;
        }
        system("CLS");
        cout<<"Wpisz imie pracownika"<<endl;
        getline(inp,command,'\n');
        if(command=="exit") throw 1;
        for(k=0;k<this->size();k++)
        {
            if(this->at(k).coto()==command) break;
        }
        if(k!=this->size())
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

