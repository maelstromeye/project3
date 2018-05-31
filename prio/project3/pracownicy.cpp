#include "pracownicy.h"
using namespace std;

void Pracownik_n::pisz(fstream &out)    //zapis do pliku
{
    switch(praca)   //co zapisac
    {
        case lkt:
            out<<"lkt"<<endl;
            break;
        case asy:
            out<<"asy"<<endl;
            break;
        case wyk:
            out<<"wyk"<<endl;
            break;
        case adu:
            out<<"adu"<<endl;
            break;
        case stw:
            out<<"stw"<<endl;
            break;
        case pnz:
            out<<"pnz"<<endl;
            break;
        case doc:
            out<<"doc"<<endl;
            break;
        case prz:
            out<<"prz"<<endl;
            break;
        default:
            break;
    }
    switch(stop)    //co zapisac
    {
        case non:
            out<<"non"<<endl;
            break;
        case lic:
            out<<"lic"<<endl;
            break;
        case eng:
            out<<"eng"<<endl;
            break;
        case mag:
            out<<"mag"<<endl;
            break;
        case dok:
            out<<"dok"<<endl;
            break;
        case dhb:
            out<<"dhb"<<endl;
            break;
        case pro:
            out<<"pro"<<endl;
            break;
        default:
            break;
    }
    out<<imie<<endl;    //imie
    return;
}

void Pracownik_n::druk(void)    //druk do cout, analogiczny do zapisu do pliku
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

void Pracownik_a::pisz(fstream &out)    //zapis do pliku, analoggicznie do pracownika naukowego...
{
    switch(praca)
    {
        case kza:   //...oprocz tutaj, tu trzeba zapisac jeszcze zaklad, wiec dokonuje sie to z zewnatrz
            break;
        case dzi:
            out<<"dzi"<<endl;
            break;
        case prd:
            out<<"prd"<<endl;
            break;
        case din:
            out<<"din"<<endl;
            break;
        case zdi:
            out<<"zdi"<<endl;
            break;
        default:
            break;
    }
    switch(stop)
    {
        case non:
            out<<"non"<<endl;
            break;
        case lic:
            out<<"lic"<<endl;
            break;
        case eng:
            out<<"eng"<<endl;
            break;
        case mag:
            out<<"mag"<<endl;
            break;
        case dok:
            out<<"dok"<<endl;
            break;
        case dhb:
            out<<"dhb"<<endl;
            break;
        case pro:
            out<<"pro"<<endl;
            break;
        default:
            break;
    }
    out<<imie<<endl;
    return;
}

void Pracownik_a::druk(void)    //wypisz do cout, analogicznie do pracownika naukowego
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

