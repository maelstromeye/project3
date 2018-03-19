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
			int i;
			for(temp=start;temp->next!=NULL;temp=temp->next);
			for(i=0;i<CHUNKSIZE;i++)
			{
				if(std::isnan(temp->values[0][0][i])!=0) return temp->crdx+i;
			}
			return i+temp->crdx;
		}
		int dimy()
		{
			if (start==NULL) return 0;
			chunk* temp;
			int i;
			for(temp=start;temp->next!=NULL;temp=temp->next);
			for(i=0;i<CHUNKSIZE;i++)
			{
				if(std::isnan(temp->values[0][i][0])!=0) return temp->crdy+i;
			}
			return i+temp->crdy;
		}
		int dimz;
		chunk* start;
	public:
		Tensor();
		int change(double data, int crdx, int crdy, int crdz);
		void init(double data[CHUNKSIZE], int crdx, int crdy, int crdz);
		friend std::istream &operator>>(std::istream &input, Tensor &tensor);
		friend std::ostream &operator<<(std::ostream &output, Tensor &tensor);
		int reveal (int crdx, int crdy, int y);
		bool operator+=(Tensor &tensor);
		bool operator-=(Tensor &tensor);
		bool operator*=(Tensor &tensor);
		bool operator==(Tensor &tensor);
		bool operator!=(Tensor &tensor);
		Tensor operator+(Tensor &tensor);
		Tensor operator-(Tensor &tensor);
		Tensor operator*(Tensor &tensor);
		~Tensor();
};
#endif
