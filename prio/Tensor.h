#ifndef CHUNKSIZE
#include <iostream>
#define CHUNKSIZE 4
class Tensor
{
	private:
		struct chunk
		{
			double values[CHUNKSIZE][CHUNKSIZE][CHUNKSIZE];
			int crdx, crdy, crdz;
			chunk* next;
		};
		chunk* start;
	public:
		Tensor();
		void init(double data[CHUNKSIZE], int crdx, int crdy, int crdz);
		friend std::istream &operator>>(std::istream &input, Tensor &tensor);
		/*~Tensor();
		void change(char tenname[], double val, int crdx, int crdy, int crdz);
		void show(int crdx, int crdy, int crdz);*/
		void show();	
};
#endif	
