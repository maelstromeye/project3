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
		int dimx()	//detecc me jak duzo jest wersow
		{
			if (start==NULL) return 0;
			chunk* temp;
			int i, n;
			for(temp=start, n=0;temp->next!=NULL;temp=temp->next)
			{
				n++;
				if	(temp->crdx>temp->next->crdx) break;
			}
			for(i=0;i<CHUNKSIZE;i++)
			{
				if(std::isnan(temp->values[0][0][i])!=0) return i+CHUNKSIZE*n;
			}
			return i+CHUNKSIZE*n;
		}
		int dimy()
		{
			
		}
		chunk* start;
	public:
		Tensor();
		void init(double data[CHUNKSIZE], int crdx, int crdy, int crdz);
		friend std::istream &operator>>(std::istream &input, Tensor &tensor);
		friend std::ostream &operator<<(std::ostream &output, Tensor &tensor);
		/*~Tensor();
		void change(char tenname[], double val, int crdx, int crdy, int crdz);
		void show(int crdx, int crdy, int crdz);*/	
};
#endif	
