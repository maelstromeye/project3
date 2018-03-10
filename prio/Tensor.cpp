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
	for(i=0; i<CHUNKSIZE;(temp->values[crdz%4][crdy%4][i])=data[i], i++); //assignujemy nowe dane
	return;
}
void Tensor::show()
{
	std::cout<<start->values[0];
}
std::istream &operator>>(std::istream &input, Tensor &tensor)
{
	double data[CHUNKSIZE];
	int crdx, crdy, crdz, read, dimx, dimy;
	dimx=dimy=crdx=crdy=crdz=read=0;
	bool flagx, flagy;
	flagx=flagy=0;
	char space;
	do
	{
		std::cout<<"for z="<<crdz<<std::endl;
		do
		{
			do
			{
				if((flagx)&&(crdx+read==dimx))
				{
					std::cout<<std::endl;
					if(read==0) break;
					tensor.init(data, crdx, crdy, crdz);
					read=0;
					break;
				}
				std::cin>>data[read];
				read++;
				if(read==CHUNKSIZE)
				{
					if(!flagx) dimx+=CHUNKSIZE;
					tensor.init(data, crdx, crdy, crdz);
					read=0;
					crdx+=CHUNKSIZE;
				}
				space=std::cin.get();
			}
			while(space!='\n');
			if(crdx+read!=dimx)
			{
				for(;crdx+read<dimx;read++)
				{
					data[read]=0;
					if(read==CHUNKSIZE)
					{
						tensor.init(data, crdx, crdy, crdz);
						read=0;
						crdx+=CHUNKSIZE;
					}
				}
			}
			if(read!=0)
			{
				if(!flagx) dimx+=read;
				tensor.init(data, crdx, crdy, crdz);
				read=0;
			}
			flagx=1;
			crdx=0;
			crdy++;
			std::cin>>data[0];
			space=std::cin.get();
		}
		while(space!='\n');
		if(!flagy) dimy=crdy-1;
		flagy=1;
		crdx=0;
		crdy=0;
		crdz++;
		std::cout<<"Continue? (anything if yes, enter if no)";
		space=std::cin.get();
	}
	while(space!='\n');
	while(std::cin.get()!='\n');
	std::cout<<"Tensor accpeted.";
	return input;
}

