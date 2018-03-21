#include "Tensor.h"
#include <string>
#include <stdio.h>
#include <new>
Tensor::Tensor()	//konstruktor
{
	start=NULL;
	dimz=0;
}
int Tensor::dimy()  //znajduje dlugosc wspolrzednej y
{
	if (start==NULL) return 0;
	chunk* temp;    //pointer pomocniczy
	int i;  //counter
	for(temp=start;temp->next!=NULL;temp=temp->next);   //szukamy konca listy
	for(i=0;i<CHUNKSIZE;i++)
	{
		if(std::isnan(temp->values[0][i][0])!=0) return temp->crdy+i;   //na koncu listy umieszczam marker zlozony z NANow, wykrywany jest tutaj
	}
	return i+temp->crdy;    //jezeli marker nie istnial (dimy%CHUNKSIZE==0)
}
int Tensor::dimx()	//znajduje dlugosc wspolrzednej x
{
	if (start==NULL) return 0;
	chunk* temp;    //pointer pomocniczy
	int i;  //counter
	for(temp=start;temp->next!=NULL;temp=temp->next);   //szukamy konca listy
	for(i=0;i<CHUNKSIZE;i++)
	{
		if(std::isnan(temp->values[0][0][i])!=0) return temp->crdx+i;   //na koncu wersu sa markery NAN, wykrywamy je
	}
	return i+temp->crdx; //jezeli dimx%CHUNKSIZE==0
}
void Tensor::setz(int crdz) //ustalenie dlugosci wspolrzednej z
{
    dimz=crdz;
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
	chunk* temp1;
	chunk* temp2; //tymczasowe pointeru
	for(temp1=start; !((temp1->crdx==crdx)&&((crdy>=temp1->crdy)&&(crdy<temp1->crdy+CHUNKSIZE))&&((crdz>=temp1->crdz)&&(crdz<temp1->crdz+CHUNKSIZE))); temp1=temp1->next)	//znajdujemy na liscie chunk o odpowiednich wspolrzednych
	{
		if (temp1->next==NULL)	//odpowiedniej wspolrzednej moze nie byc wogole
		{
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
	for(i=0; i<CHUNKSIZE;(temp1->values[crdz%4][crdy%4][i])=data[i], i++); //assignujemy nowe dane
	return;
}
int Tensor::change(double data, int crdx, int crdy, int crdz)   //zmiana wartosci na wspolrzednej
{
	if((crdx>=dimx())||(crdy>=dimy())||(crdz>=dimz)||(crdx<0)||(crdy<0)||(crdz<0)) return 0;    //ktos podal nieprawidlowa wspolrzedna
	chunk* temp;    //pointer pomocniczy
	for(temp=start; !(((crdx>=temp->crdx)&&(crdx<temp->crdx+CHUNKSIZE))&&((crdy>=temp->crdy)&&(crdy<temp->crdy+CHUNKSIZE))&&((crdz>=temp->crdz)&&(crdz<temp->crdz+CHUNKSIZE))); temp=temp->next);   //znadujemy chunk o odpowiednich wspolrzednych
	temp->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][crdx%CHUNKSIZE]=data;  //zmieniamy dana
	return 1;
}
int Tensor::reveal(int crdx, int crdy, int crdz)    //pokazanie wartosci na danej wspolrzednej
{
	if((crdx>=dimx())||(crdy>=dimy())||(crdz>=dimz)||(crdx<0)||(crdy<0)||(crdz<0)) return 0;    //ktos podal nieprawidlowe wspolrzedne
	chunk* temp;    //pointer pomocniczy
	for(temp=start; !(((crdx>=temp->crdx)&&(crdx<temp->crdx+CHUNKSIZE))&&((crdy>=temp->crdy)&&(crdy<temp->crdy+CHUNKSIZE))&&((crdz>=temp->crdz)&&(crdz<temp->crdz+CHUNKSIZE))); temp=temp->next);   //znajdujemy chunk o odpowiednich wspolrzednych
	std::cout<<temp->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][crdx%CHUNKSIZE]<<std::endl; //wypisanie danej
	return 1;
}
void Tensor::cleanse(void)  //niszczenie wyciekow pamieci
{
    chunk* temp1;   //pointery pomocnicze
	chunk* temp2;
	if (start==NULL) return;    //nie ma danych
	temp1=start;
	temp2=start;
	while(temp1->next!=NULL)    //az do konca
	{
		temp1=temp1->next;  //usuwanie danych
		delete temp2;
		temp2=temp1;
	}
	delete temp1;   //usuwanie ostatniej danej
	start=NULL; //powrot do stanu 0
	dimz=0;
}
Tensor::~Tensor()   //destruktor
{
	start=NULL;
	dimz=0;
}
Tensor& Tensor::operator+=(Tensor &tensor) //+=
{
    Tensor zero;    //tensor pusty. do zwrocenia jezeli nieprawidlowe dane
	if ((this->dimx()!=tensor.dimx())||(this->dimy()!=tensor.dimy())||(this->dimz!=tensor.dimz)||(tensor.start==NULL))  //niekompatybilne tensory
	{
		std::cout<<"Dimensions mismatch, aborting."<<std::endl;
		return zero;
	}
	chunk* tensptr; //pointery pomocnicze
	chunk* thisptr;
	tensptr=tensor.start;
	thisptr=this->start;
	int crdz, crdy, crdx, i, iy, ix;    //wspolrzedne na ktorych jestesmy, counter, wspolrzedne maksymalne, jakich nie mozemy osiagnac
	ix=tensor.dimx();   //przypisujemy wspolrzedne nieosiagalne
	iy=tensor.dimy();
	for(crdz=0;crdz<tensor.dimz;crdz++) //petla dla wymiaru z
	{
		for(crdy=0;crdy<iy;crdy++)  //petla dla wymiaru y
		{
			for(crdx=0, i=0;crdx+i<ix;i++)  //petla dla wymiaru x
			{
				(thisptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i])+=(tensptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]); //dodanie
				if (i==CHUNKSIZE-1) //jezeli dodalismy caly jeden wektor
				{
				crdx+=CHUNKSIZE;
				tensptr=tensptr->next;  //przeskakujemy na nastepny pointer
				thisptr=thisptr->next;
				i=-1;
				}
			}
			if(crdy!=iy-1) for(tensptr=tensor.start, thisptr=this->start;!(((crdy+1>=tensptr->crdy)&&(crdy+1<tensptr->crdy+CHUNKSIZE))&&((crdz>=tensptr->crdz)&&(crdz<tensptr->crdz+CHUNKSIZE)));tensptr=tensptr->next, thisptr=thisptr->next); //wybor pointera o odpowiednim y
		}
		if(crdz!=tensor.dimz-1) for(tensptr=tensor.start, thisptr=this->start;!((crdz+1>=tensptr->crdz)&&(crdz+1<tensptr->crdz+CHUNKSIZE));tensptr=tensptr->next, thisptr=thisptr->next);   //wybor pointera o odpowiednimk z
		else break;
	}
	return *this;
}
Tensor& Tensor::operator-=(Tensor &tensor)  //analogiccznie do +=
{
    Tensor zero;
	if ((this->dimx()!=tensor.dimx())||(this->dimy()!=tensor.dimy())||(this->dimz!=tensor.dimz)||(tensor.start==NULL))
	{
		std::cout<<"Dimensions mismatch, aborting."<<std::endl;
		return zero;
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
				((thisptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i])-=(tensptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]));
				if (i==CHUNKSIZE-1)
				{
				crdx+=CHUNKSIZE;
				tensptr=tensptr->next;
				thisptr=thisptr->next;
				i=-1;
				}
			}
			if(crdy!=iy-1) for(tensptr=tensor.start, thisptr=this->start;!(((crdy+1>=tensptr->crdy)&&(crdy+1<tensptr->crdy+CHUNKSIZE))&&((crdz>=tensptr->crdz)&&(crdz<tensptr->crdz+CHUNKSIZE)));tensptr=tensptr->next, thisptr=thisptr->next);
		}
		if(crdz!=tensor.dimz-1) for(tensptr=tensor.start, thisptr=this->start;!((crdz+1>=tensptr->crdz)&&(crdz+1<tensptr->crdz+CHUNKSIZE));tensptr=tensptr->next, thisptr=thisptr->next);
		else break;
	}
	return *this;
}
Tensor& Tensor::operator*=(Tensor &tensor) //analogicznie do +=
{
	Tensor zero;
	if ((this->dimx()!=tensor.dimx())||(this->dimy()!=tensor.dimy())||(this->dimz!=tensor.dimz)||(tensor.start==NULL))
	{
		std::cout<<"Dimensions mismatch, aborting."<<std::endl;
		return zero;
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
				((thisptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i])*=(tensptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]));
				if (i==CHUNKSIZE-1)
				{
				crdx+=CHUNKSIZE;
				tensptr=tensptr->next;
				thisptr=thisptr->next;
				i=-1;
				}
			}
			if(crdy!=iy-1) for(tensptr=tensor.start, thisptr=this->start;!(((crdy+1>=tensptr->crdy)&&(crdy+1<tensptr->crdy+CHUNKSIZE))&&((crdz>=tensptr->crdz)&&(crdz<tensptr->crdz+CHUNKSIZE)));tensptr=tensptr->next, thisptr=thisptr->next);
		}
		if(crdz!=tensor.dimz-1) for(tensptr=tensor.start, thisptr=this->start;!((crdz+1>=tensptr->crdz)&&(crdz+1<tensptr->crdz+CHUNKSIZE));tensptr=tensptr->next, thisptr=thisptr->next);
		else break;
	}
	return *this;
}
Tensor Tensor::operator+(Tensor &tensor)    //+
{
	Tensor zero;    //pusty pointer, ew go zwrocimy
	if ((this->dimx()!=tensor.dimx())||(this->dimy()!=tensor.dimy())||(this->dimz!=tensor.dimz)||(tensor.start==NULL))  //niekompatybilne tensory
	{
		std::cout<<"Dimensions mismatch, aborting."<<std::endl;
		return zero;
	}
	chunk* tensptr; //pointer tymczasowy
	chunk* thisptr;
	tensptr=tensor.start;
	thisptr=this->start;
	int crdz, crdy, crdx, i, iy, ix;    //wspolrzende obecne, counter, wspolrzedne nieosiagalne
	ix=this->dimx();    //ustaiwamy wspolrzedne nieosiagalne
	iy=this->dimy();
	double data[CHUNKSIZE]; //holder danych
	for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);  //inicjalizujemy do NAN
	for(crdz=0;crdz<tensor.dimz;crdz++) //PETLA DLA WYMIARU Z
	{
		for(crdy=0;crdy<iy;crdy++)  //petla dla wymiaru y
		{
			for(crdx=0, i=0;crdx+i<ix;i++)  //petla dla wmiaru x
			{
				data[i]=((thisptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i])+(tensptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]));    //przypisanie dnaych
				if (i==CHUNKSIZE-1) //jezeli wektor gotowy do zapisania
				{
				zero.init(data, crdx, crdy, crdz);  //inicjalizujemy do tensora zero
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);  //NANujemy dane
				crdx+=CHUNKSIZE;    //nastepna wspolrzedna
				tensptr=tensptr->next;  //anstepny pointer
				thisptr=thisptr->next;
				i=-1;
				}
			}
			if(i!=0)    //jezeli zostalo cos do zapisania po petli to zapisujemy
			{
				zero.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			}
			if(crdy!=iy-1) for(tensptr=tensor.start, thisptr=this->start;!(((crdy+1>=tensptr->crdy)&&(crdy+1<tensptr->crdy+CHUNKSIZE))&&((crdz>=tensptr->crdz)&&(crdz<tensptr->crdz+CHUNKSIZE)));tensptr=tensptr->next, thisptr=thisptr->next); //lokalizujemy odpowiednie miejsce na liscie
		}
		if(crdy%CHUNKSIZE!=0)   //ustawiamy marker NAN dla funkcji dimy()
		{
			for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			zero.init(data, ix-((ix%CHUNKSIZE==0)?CHUNKSIZE:ix%CHUNKSIZE), crdy, crdz);
		}
		if(crdz!=tensor.dimz-1) for(tensptr=tensor.start, thisptr=this->start;!((crdz+1>=tensptr->crdz)&&(crdz+1<tensptr->crdz+CHUNKSIZE));tensptr=tensptr->next, thisptr=thisptr->next);   //lokalizujemy odpowiednie miejsce na liscie
		else break;
	}
	zero.dimz=tensor.dimz; //ustawiamy dimz
	return zero;    //zwracay gotowy pointer, uzytkownik musi usunac zallokowana pamiec gotowa funkcja cleanse();
}
Tensor Tensor::operator-(Tensor &tensor)    //analogicznie do +
{
	Tensor zero;
	if ((this->dimx()!=tensor.dimx())||(this->dimy()!=tensor.dimy())||(this->dimz!=tensor.dimz)||(tensor.start==NULL))
	{
		std::cout<<"Dimensions mismatch, aborting."<<std::endl;
		return zero;
	}
	chunk* tensptr;
	chunk* thisptr;
	tensptr=tensor.start;
	thisptr=this->start;
	int crdz, crdy, crdx, i, iy, ix;
	ix=this->dimx();
	iy=this->dimy();
	double data[CHUNKSIZE];
	for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
	for(crdz=0;crdz<tensor.dimz;crdz++)
	{
		for(crdy=0;crdy<iy;crdy++)
		{
			for(crdx=0, i=0;crdx+i<ix;i++)
			{
				data[i]=((thisptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i])-(tensptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]));
				if (i==CHUNKSIZE-1)
				{
				zero.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
				crdx+=CHUNKSIZE;
				tensptr=tensptr->next;
				thisptr=thisptr->next;
				i=-1;
				}
			}
			if(i!=0)
			{
				zero.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			}
			if(crdy!=iy-1) for(tensptr=tensor.start, thisptr=this->start;!(((crdy+1>=tensptr->crdy)&&(crdy+1<tensptr->crdy+CHUNKSIZE))&&((crdz>=tensptr->crdz)&&(crdz<tensptr->crdz+CHUNKSIZE)));tensptr=tensptr->next, thisptr=thisptr->next);
		}
		if(crdy%CHUNKSIZE!=0)
		{
			for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			zero.init(data, ix-((ix%CHUNKSIZE==0)?CHUNKSIZE:ix%CHUNKSIZE), crdy, crdz);
		}
		if(crdz!=tensor.dimz-1) for(tensptr=tensor.start, thisptr=this->start;!((crdz+1>=tensptr->crdz)&&(crdz+1<tensptr->crdz+CHUNKSIZE));tensptr=tensptr->next, thisptr=thisptr->next);
		else break;
	}
	zero.dimz=tensor.dimz;
	return zero;
}
Tensor Tensor::operator*(Tensor &tensor)    //analogicznie do +
{
	Tensor zero;
	if ((this->dimx()!=tensor.dimx())||(this->dimy()!=tensor.dimy())||(this->dimz!=tensor.dimz)||(tensor.start==NULL))
	{
		std::cout<<"Dimensions mismatch, aborting."<<std::endl;
		return zero;
	}
	chunk* tensptr;
	chunk* thisptr;
	tensptr=tensor.start;
	thisptr=this->start;
	int crdz, crdy, crdx, i, iy, ix;
	ix=this->dimx();
	iy=this->dimy();
	double data[CHUNKSIZE];
	for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
	for(crdz=0;crdz<tensor.dimz;crdz++)
	{
		for(crdy=0;crdy<iy;crdy++)
		{
			for(crdx=0, i=0;crdx+i<ix;i++)
			{
				data[i]=((thisptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i])*(tensptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]));
				if (i==CHUNKSIZE-1)
				{
				zero.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
				crdx+=CHUNKSIZE;
				tensptr=tensptr->next;
				thisptr=thisptr->next;
				i=-1;
				}
			}
			if(i!=0)
			{
				zero.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			}
			if(crdy!=iy-1) for(tensptr=tensor.start, thisptr=this->start;!(((crdy+1>=tensptr->crdy)&&(crdy+1<tensptr->crdy+CHUNKSIZE))&&((crdz>=tensptr->crdz)&&(crdz<tensptr->crdz+CHUNKSIZE)));tensptr=tensptr->next, thisptr=thisptr->next);
		}
		if(crdy%CHUNKSIZE!=0)
		{
			for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			zero.init(data, ix-((ix%CHUNKSIZE==0)?CHUNKSIZE:ix%CHUNKSIZE), crdy, crdz);
		}
		if(crdz!=tensor.dimz-1) for(tensptr=tensor.start, thisptr=this->start;!((crdz+1>=tensptr->crdz)&&(crdz+1<tensptr->crdz+CHUNKSIZE));tensptr=tensptr->next, thisptr=thisptr->next);
		else break;
	}
	zero.dimz=tensor.dimz;
	return zero;
}
bool Tensor::operator==(Tensor &tensor) //analogicznie do +=, tylko zamiast dodawania sprawdzenie waruku i ew zwrocenie
{
	if ((this->dimx()!=tensor.dimx())||(this->dimy()!=tensor.dimy())||(this->dimz!=tensor.dimz)||(tensor.start==NULL))
	{
		return false;
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
				if(((thisptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i])!=(tensptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]))) return false;
				if (i==CHUNKSIZE-1)
				{
				crdx+=CHUNKSIZE;
				tensptr=tensptr->next;
				thisptr=thisptr->next;
				i=-1;
				}
			}
			if(crdy!=iy-1) for(tensptr=tensor.start, thisptr=this->start;!(((crdy+1>=tensptr->crdy)&&(crdy+1<tensptr->crdy+CHUNKSIZE))&&((crdz>=tensptr->crdz)&&(crdz<tensptr->crdz+CHUNKSIZE)));tensptr=tensptr->next, thisptr=thisptr->next);
		}
		if(crdz!=tensor.dimz-1) for(tensptr=tensor.start, thisptr=this->start;!((crdz+1>=tensptr->crdz)&&(crdz+1<tensptr->crdz+CHUNKSIZE));tensptr=tensptr->next, thisptr=thisptr->next);
		else break;
	}
	return true;
}
bool Tensor::operator!=(Tensor &tensor) //analogicznie do ==
{
	if ((this->dimx()!=tensor.dimx())||(this->dimy()!=tensor.dimy())||(this->dimz!=tensor.dimz)||(tensor.start==NULL))
	{
		return true;
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
				if(((thisptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i])!=(tensptr->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]))) return true;
				if (i==CHUNKSIZE-1)
				{
				crdx+=CHUNKSIZE;
				tensptr=tensptr->next;
				thisptr=thisptr->next;
				i=-1;
				}
			}
			if(crdy!=iy-1) for(tensptr=tensor.start, thisptr=this->start;!(((crdy+1>=tensptr->crdy)&&(crdy+1<tensptr->crdy+CHUNKSIZE))&&((crdz>=tensptr->crdz)&&(crdz<tensptr->crdz+CHUNKSIZE)));tensptr=tensptr->next, thisptr=thisptr->next);
		}
		if(crdz!=tensor.dimz-1) for(tensptr=tensor.start, thisptr=this->start;!((crdz+1>=tensptr->crdz)&&(crdz+1<tensptr->crdz+CHUNKSIZE));tensptr=tensptr->next, thisptr=thisptr->next);
		else break;
	}
	return false;
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
				if(flagx==0) dimx+=read;
				tensor.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
				read=0;
			}
			flagx=1;	//juz zmienilismy maksymalna wspolrzedna x
			crdx=0;
			read=0;
			if((crdy+1==dimy)&&(flagy==1))	//jezeli ktos by probowal dac za duzo linijek, niech nie probuje
			{
				input.putback(space);
				crdy++;
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
		if((crdy<dimy)&&(flagy==1))	//ktos dal za malo linijek
		{
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
		while(1)    //czy kontynuowac wpisywanie do nastepnego z
		{
			std::cout<<"Continue to z="<<crdz<<" y/n ?"<<std::endl;
			space=input.get();
			if((space!='y')&&(space!='n'))
			{
				fseek(stdin, 0, SEEK_END);
				std::cout<<"Unexpected input data. Input the vector again."<<std::endl;
				continue;
			}
			if(space=='n') space='\n';
			input.get();
			tensor.setz(crdz);
			break;
		}
	}
	while(space!='\n');
	std::cout<<"Tensor accepted. Dimx="<<tensor.dimx()<<" Dimy="<<tensor.dimy()<<std::endl;
	return input;
}
std::ostream &operator<<(std::ostream &output, Tensor tensor)   //wypisanie
{
	if(tensor.start==NULL) return output;   //brak danych
	Tensor::chunk* temp;    //pomocniczy pointer
	int crdx,crdy,crdz, ix, iy, i;  //wspolrzedne na ktprych jestesmy, wspolrzedne nieosiagalne, counter
	iy=tensor.dimy();   //przypisanie wspolrzednych nieosiagalnych
	ix=tensor.dimx();
	temp=tensor.start;
	for(crdz=0;crdz<tensor.dimz;crdz++) //petla wymiaru z
	{
		output<<"z="<<crdz<<std::endl;
		for(crdy=0;crdy<iy;crdy++)  //petla wymiaru y
		{
			for(crdx=0, i=0;crdx+i<ix;i++)  //petla wymiaru x
			{
				output<<temp->values[crdz%CHUNKSIZE][crdy%CHUNKSIZE][i]<<" ";   //wypisanie
				if(i==CHUNKSIZE-1)  //przejscie do nastepnego pointera
				{
				temp=temp->next;
				i=-1;
				crdx+=CHUNKSIZE;    //...i nastepnej wpsolrzednej
				}
			}
			output<<std::endl;
			if(crdy!=iy-1) for(temp=tensor.start;!(((crdy+1>=temp->crdy)&&(crdy+1<temp->crdy+CHUNKSIZE))&&((crdz>=temp->crdz)&&(crdz<temp->crdz+CHUNKSIZE)));temp=temp->next);  //lokalizacja iejsca na liscie
		}
		if(crdz!=tensor.dimz-1) for(temp=tensor.start;!((crdz+1>=temp->crdz)&&(crdz+1<temp->crdz+CHUNKSIZE));temp=temp->next);  //lokalizacja miejsca na liscie
		else return output;
	}
	return output;
}

