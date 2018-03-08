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
		addvalue(double values[CHUNKSIZE], int crdx, int crdy, int crdz);
		~Tensor();
		change(char tenname[], double val, int crdx, int crdy, int crdz);
		show(char tenname[], int crdx, int crdy, int crdz);
		show(char tenname[]);	
};
#endif	
