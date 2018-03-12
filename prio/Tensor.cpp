#include "Tensor.h"
#include <string>
#include <stdio.h>
#include <new>
#include <cmath>
Tensor::Tensor()	//konstruktor
{
	start=NULL;
}
void Tensor::init(double data[CHUNKSIZE], int crdx, int crdy, int crdz)	//dodawanie wartosci do istniejacego obiektu
{
	if (start==NULL)	//jezeli nie bylo wczesniej obiektu
	{
		start=new chunk;
		start->next=NULL;
		start->crdx=0;
		start->crdy=0;
		start->crdz=0;
	}
	chunk* temp; //tymczasowy pointer
	for(temp=start; (temp->crdx!=crdx)||(crdy<temp->crdy)||(crdy>temp->crdy+CHUNKSIZE)||(crdz<temp->crdz)||(crdz>temp->crdz+CHUNKSIZE); temp=temp->next)	//znajdujemy na liscie chunk o odpowiednich wspolrzednych
	{
		if (temp->next==NULL)	//odpowiedniej wspolrzednej moze nie byc wogole
		{
			temp=new chunk;
			temp->next=NULL;
			temp->crdx=crdx;
			temp->crdy=crdy;
			temp->crdz=crdz;
			break;
		}	
	}
	int i;	//counter
	for(i=0; i<CHUNKSIZE;(temp->values[crdz%4][crdy%4][i])=data[i],std::cout<<temp->values[crdz%4][crdy%4][i]<<" ", i++); //assignujemy nowe dane
	std::cout<<std::endl;
	return;
}
void Tensor::show()
{
	std::cout<<start->values[0];
}
std::istream &operator>>(std::istream &input, Tensor &tensor)	//wczytanie z klawiatury
{
	double data[CHUNKSIZE];	//przechowywanie pojedynczego wprowadzonego wektora
	int crdx, crdy, crdz, read, dimx, dimy, i;	//obecne wspolrzedna x,y,z jakie czytamy, ilosc wczytanych liczb, maxymalna wspolrzedna w wymiarze x, y, counter 
	for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);	//ustawiamy nany
	dimx=dimy=crdx=crdy=crdz=read=0;
	bool flagx, flagy;	//czy maxymalna wspolrzedna wymiaru juz byla ustalona
	flagx=flagy=false;
	char space;	//przechowywanie znakow innych niz liczby
	do
	{
		std::cout<<"for z="<<crdz<<std::endl;	//na jakiej wspolrzednej z jestesmy obecnie
		do
		{
			do
			{
				while(1)	//czy akceptowalny znak
				{
					space=input.get();
					if((!isdigit(space))&&(space!='\n')&&(space!='-'))	//jezeli nie akcpetowalny
					{
						std::cin.ignore(INT_MAX,'\n');
						std::cout<<"Unexpected input data. Input the vector again, starting with x="<<crdx<<std::endl;
						read=0;
						for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);	//ustawienie wektora danych na NAN-y
						continue;
					}
					input.putback(space);	//jezeli dobry to wraca do bufora
					break;
				}
				if((flagx==true)&&(crdx+read==dimx))	//jezeli ktos wpisal za duzo to obcinamy
				{
					if (read!=0) tensor.init(data, crdx, crdy, crdz);	//zapisujemy jezeli cos bylo wpisane prawidlowo
					crdx=dimx;
					read=0;
					fseek(stdin,1,SEEK_END);	//o reszcie zapominamy
					break;
				}
				input>>data[read];	//pobor liczby
				read++;
				if(read==CHUNKSIZE)	//jezeli jest gotowy do zapisu
				{
					if(!flagx) dimx+=CHUNKSIZE;	//powiekszenie maxymalnej wspolrzednej, jezeli jeszcze nie jest zablokowana
					tensor.init(data, crdx, crdy, crdz);	//wpisanie danych
					for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);	//tablica danych na NAN
					read=0;
					crdx+=CHUNKSIZE;	//przeczytalismy wiecej wspolrzednych
				}
				space=input.get();	//pobieramy znak rozdielajacy badz enter
			}
			while(space!='\n');	//jezeli enter, przechodzimy do nizszej kolumny
			if((crdx+read!=dimx)&&(flagx==true))	//za malo rzeczy bylo wpisane, assume 0s
			{
				for(;read<dimx-crdx;)	//iteruje tyle razy ile wejsc brakuje
				{
					data[read]=0;	//symulacja inputowania 0
					read++;
					if(read==CHUNKSIZE)
					{
						tensor.init(data, crdx, crdy, crdz);
						for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
						read=0;
						crdx+=CHUNKSIZE;
					}
				}
			}
			if(read!=0)	//nie zostalo cos zapisane (nie pasowalo do CHUNKSIZE)
			{
				if(!flagx) dimx+=read;
				tensor.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
				read=0;
			}
			flagx=true;	//juz zmienilismy maksymalna wspolrzedna x
			crdx=0;
			read=0;
			if((crdy==dimy)&&(flagy==true))	//jezeli ktos by probowal dac za duzo linijek, niech nie probuje
			{
				input.putback(space);
				break;
			}
			crdy++;	//nizsza kolumna
			while(1)	//czy isc nizej, czy juz do nastepnego z
			{
				space=input.get();
				if((!isdigit(space))&&(space!='\n')&&(space!='-'))
				{
					std::cin.ignore(INT_MAX,'\n');
					std::cout<<"Unexpected input data. Input the vector again."<<std::endl;
					continue;
				}
				input.putback(space);
				break;
			}
		}
		while(space!='\n');
		input.get();	//zerujemy wejscie
		if((crdy<=dimy)&&(flagy==true))	//ktos dal za malo linijek
		{
			for(;crdy-1<dimy;crdy++)	//read staje sie sentinelem dla petli
			{	
				crdx=0;						
				for(read=0;crdx+read<dimx;read++)
				{
					data[read]=0;
					if(read==CHUNKSIZE)
					{
						tensor.init(data, crdx, crdy, crdz);
						for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
						crdx+=CHUNKSIZE;
						read=0;
					}
				}
				if(read!=0)
				{
					if(!flagx) dimx+=read;
					tensor.init(data, crdx, crdy, crdz);
					for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
					read=0;
				}	
			}
		}
		if(flagy==false) dimy=crdy-1;	//lockujemy maxymalna wspolrzedna y
		flagy=true;
		crdx=0;
		crdy=0;
		crdz++;
		while(1)
		{
			std::cout<<"Continue to z="<<crdz<<" y/n"<<std::endl;
			space=input.get();
			if((space!='y')&&(space!='n'))
			{
				std::cin.ignore(INT_MAX,'\n');
				std::cout<<"Unexpected input data. Input the vector again."<<std::endl;
				continue;
			}
			if(space=='n') space='\n';
			break;
		}
	}
	while(space!='\n');
	std::cout<<"Tensor accepted."<<std::endl;
	return input;
}

