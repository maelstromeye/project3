#include "Tensor.h"
#include <string>
#include <new>
Tensor::Tensor()	//konstruktor
{
	start=NULL;
}
Tensor::addvalue(double values[CHUNKSIZE], int crdx, int crdy, int crdz)	//dodawanie wartosci do istniejacego obiektu
{
	if (start==NULL) start=new chunk;	//jezeli nie bylo wczesniej obiektu
	chunk* temp;
	for(temp=start;(((crdx<temp->crdx)||(crdx>temp->crdx+CHUNKSIZE))&&((crdy<temp->crdy)||(crdy>temp->crdy+CHUNKSIZE))&&((crdz<temp->crdz)||(crdz>temp->crdz+CHUNKSIZE)));temp=temp->next);	//znajdujemy na liscie chunk o odpowiednich wspolrzednych
	
}
