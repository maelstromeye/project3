#include "Tensor.h"
#include <string>
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
	}
	chunk* temp;
	for(temp=start;((temp->crdx==crdx)&&((crdy<temp->crdy)||(crdy>temp->crdy+CHUNKSIZE))&&((crdz<temp->crdz)||(crdz>temp->crdz+CHUNKSIZE)));temp=temp->next)	//znajdujemy na liscie chunk o odpowiednich wspolrzednych
	{
		if (temp->next==NULL)	//odpowiedniej wspolrzednej moze nie byc wogole
		{
			temp=new chunk;
			temp->next=NULL;
			temp->crdx=crdx/4-crdx%4;
			temp->crdy=crdy/4-crdy%4;
			temp->crdz=crdz/4-crdz%4;
		}	
	}
	int i;	//counter
	for(i=0; i<CHUNKSIZE; temp->values[crdz%4][crdy%4][i]=data[i], i++); //assignujemy nowe dane
	return;
}
void Tensor::show()
{
	std::cout<<start->values;
}
