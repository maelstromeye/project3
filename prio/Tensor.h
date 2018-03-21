#ifndef CHUNKSIZE
#include <iostream>
#define CHUNKSIZE 4
#include <cmath>
#include <cctype>
class Tensor
{
	private:
		struct chunk
		{
			double values[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE];
			int crdx, crdy, crdz;
			chunk* next;
		};
		int dimx();	//detecc me jak duzo jest wersow
		int dimy();
		int dimz;
		chunk* start;
	public:
		Tensor();
		void setz(int crdz);
		int change(double data, int crdx, int crdy, int crdz);
		void init(double data[CHUNKSIZE], int crdx, int crdy, int crdz);
		friend std::istream &operator>>(std::istream &input, Tensor &tensor);
		friend std::ostream &operator<<(std::ostream &output, Tensor tensor);
		int reveal (int crdx, int crdy, int y);
		void cleanse(void);
		Tensor& operator+=(Tensor &tensor);
		Tensor& operator-=(Tensor &tensor);
		Tensor& operator*=(Tensor &tensor);
		bool operator==(Tensor &tensor);
		bool operator!=(Tensor &tensor);
		Tensor operator+(Tensor &tensor);
		Tensor operator-(Tensor &tensor);
		Tensor operator*(Tensor &tensor);
		~Tensor();
};
#endif
