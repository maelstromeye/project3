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
	std::cout<<"at: "<<crdx<<" "<<crdy<<" "<<crdz<<" "<<std::endl;
	return;
}
int Tensor::change(double data, int crdx, int crdy, int crdz)
{
	if((crdx>=dimx())||(crdy>=dimy())||(crdz>=dimz)||(crdx<0)||(crdy<0)||(crdz<0)) return 0;
	chunk* temp;
	for(temp=start; !(((crdx>=temp->crdx)&&(crdx<temp->crdx+CHUNKSIZE))&&((crdy>=temp->crdy)&&(crdy<temp->crdy+CHUNKSIZE))&&((crdz>=temp->crdz)&&(crdz<temp->crdz+CHUNKSIZE))); temp=temp->next);
	temp->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][crdx%CHUNKSIZE]=data;
	return 1;
}
int Tensor::reveal(int crdx, int crdy, int crdz)
{
	if((crdx>=dimx())||(crdy>=dimy())||(crdz>=dimz)||(crdx<0)||(crdy<0)||(crdz<0)) return 0;
	chunk* temp;
	for(temp=start; !(((crdx>=temp->crdx)&&(crdx<temp->crdx+CHUNKSIZE))&&((crdy>=temp->crdy)&&(crdy<temp->crdy+CHUNKSIZE))&&((crdz>=temp->crdz)&&(crdz<temp->crdz+CHUNKSIZE))); temp=temp->next);
	std::cout<<temp->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][crdx%CHUNKSIZE]<<std::endl;
	return 1;
}
Tensor::~Tensor()
{
	chunk* temp1;
	chunk* temp2;
	if (start==NULL) return;
	temp1=start;
	temp2=start;
	while(temp1->next!=NULL)
	{
		temp1=temp1->next;
		delete temp2;
		temp2=temp1;
	}
	delete temp1;
}
Tensor& Tensor::operator+=(Tensor &tensor)
{
	Tensor empty;
	if ((this->dimx()!=tensor.dimx())||(this->dimy()!=tensor.dimy())||(this->dimz!=tensor.dimz)) 
	{
		std::cout<<"Dimensions mismatch, aborting."<<std::endl;
		return empty;
	}
	chunk* tensptr;
	chunk* thisptr;
	tensptr=tensor.start;
	thisptr=this->start;
	int crdz, crdy, crdx, i, iy, ix;
	ix=this->dimx();
	iy=this->dimy();
	for(crdz=0;crdz<tensor.dimz;crdz++)
	{	
		for(crdy=0;crdy<iy;crdy++)
		{
			for(crdx=0, i=0;crdx+i<ix;i++)
			{
				(thisptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i])+=(tensptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]);
				if(i==CHUNKSIZE-1) 
				{
				tensptr=tensptr->next;
				thisptr=thisptr->next;
				i=-1;
				}
			}
			if(crdy!=iy-1) for(tensptr=tensor.start, thisptr=this->start;!(((crdy+1>=tensptr->crdy)&&(crdy+1<tensptr->crdy+CHUNKSIZE))&&((crdz>=tensptr->crdz)&&(crdz<tensptr->crdz+CHUNKSIZE)));tensptr=tensptr->next, thisptr=thisptr->next);
		}
		if(crdz!=tensor.dimz-1) for(tensptr=tensor.start, thisptr=this->start;!((crdz+1>=tensptr->crdz)&&(crdz+1<tensptr->crdz+CHUNKSIZE));tensptr=tensptr->next, thisptr=thisptr->next);
		else return *this;
	}
	return *this;
}
Tensor& Tensor::operator+(Tensor &tensor)
{
	Tensor empty;
	if ((this->dimx()!=tensor.dimx())||(this->dimy()!=tensor.dimy())||(this->dimz!=tensor.dimz)) 
	{
		std::cout<<"Dimensions mismatch, aborting."<<std::endl;
		return empty;
	}
	chunk* tensptr;
	chunk* thisptr;
	tensptr=tensor.start;
	thisptr=this->start;
	int crdz, crdy, crdx, i, iy, ix;
	ix=this->dimx();
	iy=this->dimy();
	double data[CHUNKSIZE];
	for(crdz=0;crdz<tensor.dimz;crdz++)
	{	
		for(crdy=0;crdy<iy;crdy++)
		{
			for(crdx=0, i=0;crdx+i<ix;i++)
			{
				data[i]=((thisptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i])+(tensptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]));
				if (i==CHUNKSIZE-1) 
				{
				empty.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
				crdx+=CHUNKSIZE;
				tensptr=tensptr->next;
				thisptr=thisptr->next;
				i=-1;
				}
			}
			if(i!=0)	
			{
				std::cout<<i;
				empty.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			}
			if(crdy!=iy-1) for(tensptr=tensor.start, thisptr=this->start;!(((crdy+1>=tensptr->crdy)&&(crdy+1<tensptr->crdy+CHUNKSIZE))&&((crdz>=tensptr->crdz)&&(crdz<tensptr->crdz+CHUNKSIZE)));tensptr=tensptr->next, thisptr=thisptr->next);
		}
		if(crdy%CHUNKSIZE!=0)
		{
			for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			empty.init(data, ix-((ix%CHUNKSIZE==0)?CHUNKSIZE:ix%CHUNKSIZE), crdy, crdz);
		}
		if(crdz!=tensor.dimz-1) for(tensptr=tensor.start, thisptr=this->start;!((crdz+1>=tensptr->crdz)&&(crdz+1<tensptr->crdz+CHUNKSIZE));tensptr=tensptr->next, thisptr=thisptr->next);
		else break;
	}
	empty.dimz=tensor.dimz;
	std::cout<<"Dimx="<<empty.dimx()<<" Dimy="<<empty.dimy()<<std::endl;
	std::cout<<empty;
	return empty;
}	


/*FRIENDS*/
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
			for(crdx=0, i=0;crdx+i<ix;i++)
			{
				output<<temp->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]<<" ";
				if(i==CHUNKSIZE-1) 
				{
				temp=temp->next;
				i=-1;
				crdx+=CHUNKSIZE;
				}
			}
			output<<std::endl;
			if(crdy!=iy-1) for(temp=tensor.start;!(((crdy+1>=temp->crdy)&&(crdy+1<temp->crdy+CHUNKSIZE))&&((crdz>=temp->crdz)&&(crdz<temp->crdz+CHUNKSIZE)));temp=temp->next);
		}
		if(crdz!=tensor.dimz-1) for(temp=tensor.start;!((crdz+1>=temp->crdz)&&(crdz+1<temp->crdz+CHUNKSIZE));temp=temp->next);
		else return output;
	}
	return output;
}

