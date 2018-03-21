#ifndef CHUNKSIZE
#include <iostream>
#define CHUNKSIZE 4
#include <cmath>
#include <cctype>
class Tensor
{
	private:
		struct chunk    //przechowyanie danych na zasadzie "chunkow" o rozmiarze CHUNKSIZE x CHUNKSIZE x CHUNKSIZE z doublami, bedacych posortowane i odczytywane jak lista jednokierunkowa
		{
			double values[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE]; //dane
			int crdx, crdy, crdz;   //wspolrzedne na ktorych zaczyna sie chunk
			chunk* next;    //pointer do nastepnego elementu
		};
		int dimx();	//jaka dlugosc wspolrzednej x
		int dimy(); //jaka dlugosc wspolrzednej y
		int dimz;   //dlugosc wspolrzednej z
		chunk* start;   //pointer do poczatku listy
	public:
		Tensor();   //konstruktor
		void setz(int crdz);    //ustawienie maksymalnej dlugosci
		int change(double data, int crdx, int crdy, int crdz);  //czytanie danej na danej wspolrzednej
		void init(double data[CHUNKSIZE], int crdx, int crdy, int crdz);    //funkcja wpisuje pojedynczy wektor o rozmiarze CHUNKSIZE do listy na odpowiednich wspolrzednych
		friend std::istream &operator>>(std::istream &input, Tensor &tensor);   //wczytanie z cin
		friend std::ostream &operator<<(std::ostream &output, Tensor tensor);   //wypisanie do cout
		int reveal (int crdx, int crdy, int y); //czytanie danej na danej wspolrzendej
		void cleanse(void); //czyszczenie leakow ktore powstaja przez dzialania matematyczne
		Tensor& operator+=(Tensor &tensor); //matma
		Tensor& operator-=(Tensor &tensor);
		Tensor& operator*=(Tensor &tensor);
		bool operator==(Tensor &tensor);
		bool operator!=(Tensor &tensor);
		Tensor operator+(Tensor &tensor);
		Tensor operator-(Tensor &tensor);
		Tensor operator*(Tensor &tensor);
		~Tensor();  //destruktor
};
#endif
