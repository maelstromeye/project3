#include "Tensor.h"
#include <string>
#include <stdio.h>
#include <new>
Tensor::Tensor()	//konstruktor
{
	start=NULL;
}
void Tensor::init(double data[CHUNKSIZE], int crdx, int crdy, int crdz)	//dodawanie wartosci do istniejacego obiektu
{
	if (start==NULL)	//jezeli nie bylo wczesniej obiektu
	{
		std::cout<<"new chunk"<<std::endl;
		start=new chunk;
		start->next=NULL;
		start->crdx=0;
		start->crdy=0;
		start->crdz=0;
	}
	chunk* temp1;
	chunk* temp2; //tymczasowe pointeru
	for(temp1=start; !((temp1->crdx==crdx)&&((crdy>=temp1->crdy)&&(crdy<temp1->crdy+CHUNKSIZE))&&((crdz>=temp1->crdz)&&(crdz<temp1->crdz+CHUNKSIZE))); temp1=temp1->next)	//znajdujemy na liscie chunk o odpowiednich wspolrzednych
	{
		if (temp1->next==NULL)	//odpowiedniej wspolrzednej moze nie byc wogole
		{
			std::cout<<"new chunk"<<std::endl;
			temp2=temp1;
			temp1=new chunk;
			temp1->next=NULL;
			temp1->crdx=crdx;
			temp1->crdy=crdy;
			temp1->crdz=crdz;
			temp2->next=temp1;
			break;
		}	
	}
	int i;	//counter
	for(i=0; i<CHUNKSIZE;(temp1->values[crdz%4][crdy%4][i])=data[i],std::cout<<temp1->values[crdz%4][crdy%4][i]<<" ", i++); //assignujemy nowe dane
	std::cout<<"at: "<<temp1->crdx<<" "<<temp1->crdy<<" "<<temp1->crdz<<" "<<std::endl;
	return;
}
std::istream &operator>>(std::istream &input, Tensor &tensor)	//wczytanie z klawiatury
{
	double data[CHUNKSIZE];	//przechowywanie pojedynczego wprowadzonego wektora
	int crdx, crdy, crdz, read, dimx, dimy, i;	//obecne wspolrzedna x,y,z jakie czytamy, ilosc wczytanych liczb, maxymalna wspolrzedna w wymiarze x, y, counter 
	for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);	//ustawiamy nany
	dimx=dimy=crdx=crdy=crdz=read=0;
	int flagx, flagy;	//czy maxymalna wspolrzedna wymiaru juz byla ustalona
	flagx=flagy=0;
	char space;	//przechowywanie znakow innych niz liczby
	do
	{
		std::cout<<"for z="<<crdz<<std::endl;	//na jakiej wspolrzednej z jestesmy obecnie
		do
		{
			do
			{
				//std::cout<<"read x"<<std::endl;
				while(1)	//czy akceptowalny znak
				{
					space=input.get();
					if((!isdigit(space))&&(space!='\n')&&(space!='-'))	//jezeli nie akcpetowalny
					{
						std::cout<<"Unexpected input data. Input the vector again, starting with x="<<crdx<<std::endl;
						read=0;
						fseek(stdin, 0, SEEK_END);
						for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);	//ustawienie wektora danych na NAN-y
						continue;
					}
					input.putback(space);	//jezeli dobry to wraca do bufora
					break;
				}
				//std::cout<<"a fine char"<<std::endl;
				if((flagx==1)&&(crdx+read==dimx))	//jezeli ktos wpisal za duzo to obcinamy
				{
					//std::cout<<"katto"<<std::endl;
					if (read!=0) tensor.init(data, crdx, crdy, crdz);	//zapisujemy jezeli cos bylo wpisane prawidlowo
					crdx=dimx;
					read=0;
					fseek(stdin,1,SEEK_END);	//o reszcie zapominamy
					break;
				}
				//std::cout<<"a fine number"<<std::endl;
				input>>data[read];	//pobor liczby
				read++;
				//std::cout<<"I read "<<read<<std::endl;
				if(read==CHUNKSIZE)	//jezeli jest gotowy do zapisu
				{
					//std::cout<<"saved!"<<std::endl;
					if(flagx==0) dimx+=CHUNKSIZE;	//powiekszenie maxymalnej wspolrzednej, jezeli jeszcze nie jest zablokowana
					tensor.init(data, crdx, crdy, crdz);	//wpisanie danych
					for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);	//tablica danych na NAN
					read=0;
					crdx+=CHUNKSIZE;	//przeczytalismy wiecej wspolrzednych
				}
				space=input.get();	//pobieramy znak rozdielajacy badz enter
			}
			while(space!='\n');	//jezeli enter, przechodzimy do nizszej kolumny
			//std::cout<<crdx+read<<" "<<dimx<<" "<<flagx<<std::endl;
			if((crdx+read!=dimx)&&(flagx==1))	//za malo rzeczy bylo wpisane, assume 0s
			{
				//std::cout<<"assuming 0s"<<std::endl;
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
				//std::cout<<"finishing saving"<<std::endl;
				if(flagx==0) dimx+=read;
				tensor.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
				read=0;
			}
			flagx=1;	//juz zmienilismy maksymalna wspolrzedna x
			crdx=0;
			read=0;
			//std::cout<<"nexty yes"<<std::endl;
			if((crdy+1==dimy)&&(flagy==1))	//jezeli ktos by probowal dac za duzo linijek, niech nie probuje
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
					fseek(stdin, 0, SEEK_END);
					std::cout<<"Unexpected input data. Input the vector again."<<std::endl;
					continue;
				}
				input.putback(space);
				break;
			}
		}
		while(space!='\n');
		//std::cout<<"nextz"<<std::endl;
		input.get();	//zerujemy wejscie
		if((crdy<=dimy)&&(flagy==1))	//ktos dal za malo linijek
		{
			//std::cout<<"assuming 0s"<<std::endl;
			for(;crdy<dimy;crdy++)	//read staje sie sentinelem dla petli
			{						
				for(crdx=0;read<dimx-crdx;)	//iteruje tyle razy ile wejsc brakuje
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
				if(read!=0)	//nie zostalo cos zapisane (nie pasowalo do CHUNKSIZE)
				{
					//std::cout<<"finishing saving"<<std::endl;
					if(flagx==0) dimx+=read;
					tensor.init(data, crdx, crdy, crdz);
					for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
					read=0;
				}
			}
		}
		if(crdy%CHUNKSIZE!=0)	//inicjalizujemy nastepny rzad do NAN-ow (przydatne do rozpoznawania maksymalnych wymiarow)
		{
			for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			tensor.init(data, dimx-((dimx%CHUNKSIZE==0)?CHUNKSIZE:dimx%CHUNKSIZE), crdy, crdz);
		}
		if(flagy==0) dimy=crdy;	//lockujemy maxymalna wspolrzedna y
		flagy=1;
		read=0;
		crdx=0;
		crdy=0;
		crdz++;
		while(1)
		{
			std::cout<<"Continue to z="<<crdz<<" y/n"<<std::endl;
			space=input.get();
			if((space!='y')&&(space!='n'))
			{
				fseek(stdin, 0, SEEK_END);
				std::cout<<"Unexpected input data. Input the vector again."<<std::endl;
				continue;
			}
			if(space=='n') space='\n';
			input.get();
			tensor.dimz=crdz;
			break;
		}
	}
	while(space!='\n');
	std::cout<<"Tensor accepted. Dimx="<<tensor.dimx()<<" Dimy="<<tensor.dimy()<<std::endl;
	return input;
}
std::ostream &operator<<(std::ostream &output, Tensor &tensor)
{
	if(tensor.start==NULL) return output;
	Tensor::chunk* temp;
	int crdx,crdy,crdz, ix, iy, i;
	iy=tensor.dimy();
	ix=tensor.dimx();
	temp=tensor.start;
	for(crdz=0;crdz<tensor.dimz;crdz++)
	{	
		output<<"z="<<crdz<<std::endl;
		for(crdy=0;crdy<iy;crdy++)
		{
			for(crdx=0, i=0;crdx<ix;crdx++, i++)
			{
				if((crdx%CHUNKSIZE==0)&&(crdx!=0)) 
				{
				temp=temp->next;
				i=0;
				}
				output<<temp->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]<<" ";
			}
			output<<std::endl;
			temp=tensor.start;
			if(crdy>=CHUNKSIZE-1) 
			{
				for(;!(((crdy+1>=temp->crdy)&&(crdy+1<temp->crdy+CHUNKSIZE))&&((crdz>=temp->crdz)&&(crdz<temp->crdz+CHUNKSIZE)));temp=temp->next);	//error
			}
		}
		output<<"tri";
		temp=tensor.start;
		output<<"xd";
		if(crdz>=CHUNKSIZE-1) 
		{
			for(;!((crdz+1>=temp->crdz)&&(crdz+1<temp->crdz+CHUNKSIZE));temp=temp->next)
			{
				output<<"raz";
			}
			;	//faulty
		}
		output<<"dwa";
	}
	return output;
}

