#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Tensor.h"
using namespace std;
void adapt(Tensor &, int, int, int);
void key(void);
int main()
{
    srand(time(NULL));
    Tensor tensors[7];
    adapt(tensors[1], 4, 4, 4);
    adapt(tensors[2], 4, 4, 4);
    adapt(tensors[3], 8, 8, 8);
    adapt(tensors[4], 8, 8, 8);
    adapt(tensors[5], 6, 6, 6);
    adapt(tensors[6], 6, 6, 6);
    cout<<"Tensor 1 is:"<<endl;
    cout<<tensors[1]<<"------------------------------------------------------"<<endl;
    key();
    cout<<"Tensor 2 is:"<<endl;
    cout<<tensors[2]<<"------------------------------------------------------"<<endl;
    key();
    cout<<"Tensor 2 + Tensor 1 is:"<<endl;
    cout<<tensors[1]+tensors[2]<<"------------------------------------------------------"<<endl;
    key();
    cout<<"Tensor2 - Tensor 1 is:"<<endl;
    cout<<tensors[2]-tensors[1]<<"------------------------------------------------------"<<endl;
    key();
    cout<<"Input  your tensor "<<endl;
    cin>>tensors[0];
    cout<<"Your tensor is:"<<endl;
    cout<<tensors[0];
    cout<<"------------------------------------------------------"<<endl;
    key();
    cout<<"Tensor 3 is:"<<endl;
    cout<<tensors[3];
    key();
    cout<<"You can't perform any mathematical operations between tensors 3 and 2 or 1, because their dimensions do not match."<<endl;
    key();
    cout<<"Tensor 4 is:"<<endl;
    cout<<tensors[4];
    key();
    cout<<"Tensor 4 - Tensor 3 is:"<<endl;
    cout<<tensors[4]-tensors[3]<<"------------------------------------------------------"<<endl;
    key();
    cout<<"Tensor 4 += Tensor 3 is:"<<endl;
    tensors[4]+=tensors[3];
    cout<<tensors[4]<<"------------------------------------------------------"<<endl;
    key();
    cout<<"Now Tensor 4 - Tensor 3 is:"<<endl;
    cout<<tensors[4]-tensors[3]<<"------------------------------------------------------"<<endl;
    key();
    tensors[4].~Tensor();
    key();
    tensors[3].~Tensor();
    key();
    cout<<"Trying to add tensors with varying dimensions won't work."<<endl;
    key();
    tensors[1]+tensors[3];
    cout<<"As will be with +=, and other likewise operations."<<endl;
    key();
    tensors[1]+=tensors[3];
    return 0;





    return 0;
    /*while(1)
    {
    cout<<"What do you want to?"<<endl;
    cin>>command;
    cin.get();
	i=-1;
	if(command=="==") i=0;
	if(command=="!=") i=1;
	if(command=="+=") i=2;
	if(command=="-=") i=3;
	if(command=="*=") i=4;
	if(command=="+") i=5;
	if(command=="-") i=6;
	if(command=="*") i=7;
	int j;
	switch(i)
	{
		case 0:
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            i=find(what);
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            j=find(what);
            if(Tensors.at(i)==Tensors.at(j)) cout<<"true"<<endl;
            else cout<<"false"<<endl;
            break;
        case 1:
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            i=find(what);
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            j=find(what);
            if(Tensors.at(i)!=Tensors.at(j)) cout<<"true"<<endl;
            else cout<<"false"<<endl;
            break;
		case 2:
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
			i=find(what);
			fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            j=find(what);
            Tensors.at(i)+=Tensors.at(j);
            cout<<Tensors.at(i);
            break;
        case 3:
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            i=find(what);
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            j=find(what);
            Tensors.at(i)-=Tensors.at(j);
            cout<<Tensors.at(i);
            break;
        case 4:
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            i=find(what);
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            j=find(what);
            Tensors.at(i)*=Tensors.at(j);
            cout<<Tensors.at(i);
            break;
        case 5:
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            i=find(what);
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            j=find(what);
            san=Tensors.at(i)+Tensors.at(j);
            cout<<san;
            break;
        case 6:
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            i=find(what);
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            j=find(what);
            san=Tensors.at(i)-Tensors.at(j);
            cout<<san;
            break;
        case 7:
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            i=find(what);
            fseek(stdin, 0, SEEK_END);
            cout<<"Specify the tensor."<<endl;
            getline(cin, what);
            j=find(what);
            san=Tensors.at(i)*Tensors.at(j);
            cout<<san;
            break;
        default:
            cout<<"Unknown action."<<endl;
            break;
    }
    }*/
    return 0;
}
void key(void)
{
    string bin;
    cout<<"Press enter to continue"<<endl;
    getline(cin, bin);
    return;
}
void adapt(Tensor &tensor, int maxz, int maxy, int maxx)
{
    double data[CHUNKSIZE];
    int crdx, crdy, crdz, i;
    for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
    for(crdz=0;crdz<maxz;crdz++)
	{
		for(crdy=0;crdy<maxy;crdy++)
		{
			for(crdx=0, i=0;crdx+i<maxx;i++)
			{
				data[i]=rand()/rand();
				if (i==CHUNKSIZE-1)
				{
				tensor.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
				crdx+=CHUNKSIZE;
				i=-1;
				}
			}
			if(i!=0)
			{
				tensor.init(data, crdx, crdy, crdz);
				for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			}
		}
		if(crdy%CHUNKSIZE!=0)
		{
			for(i=0;i<CHUNKSIZE;data[i]=NAN, i++);
			tensor.init(data, maxx-((maxx%CHUNKSIZE==0)?CHUNKSIZE:maxx%CHUNKSIZE), crdy, crdz);
		}
	}
	tensor.setz(maxz);
}

