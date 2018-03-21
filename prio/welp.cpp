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
    Tensor tensors[7], tensor;
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
    tensors[0]=tensors[1]+tensors[2];
    cout<<tensors[0]<<"------------------------------------------------------"<<endl;
    tensors[0].cleanse();
    key();
    cout<<"Tensor2 - Tensor 1 is:"<<endl;
    tensors[0]=tensors[2]-tensors[1];
    cout<<tensors[0]<<"------------------------------------------------------"<<endl;
    tensors[0].cleanse();
    key();
    cout<<"Input  your tensor "<<endl;
    cin>>tensor;
    cout<<"Your tensor is:"<<endl;
    cout<<tensor;
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
    tensors[0]=tensors[4]-tensors[3];
    cout<<tensors[0]<<"------------------------------------------------------"<<endl;
    tensors[0].cleanse();
    key();
    cout<<"Tensor 4 += Tensor 3 is:"<<endl;
    tensors[4]+=tensors[3];
    cout<<tensors[4]<<"------------------------------------------------------"<<endl;
    key();
   cout<<"Now Tensor 4 - Tensor 3 is:"<<endl;
    tensors[0]=tensors[4]-tensors[3];
    cout<<tensors[0]<<"------------------------------------------------------"<<endl;
    tensors[0].cleanse();
    key();
    cout<<"Trying to add tensors with varying dimensions won't work."<<endl;
    key();
    tensors[1]+tensors[3];
    cout<<"As will be with +=, and other likewise operations."<<endl;
    key();
    tensors[1]+=tensors[3];
    key();
    cout<<"Program also allows multiplication, element by element, for example Tensor 1 * Tensor 2 is:"<<endl;
    tensors[0]=tensors[2]*tensors[1];
    cout<<tensors[0]<<"------------------------------------------------------"<<endl;
    tensors[0].cleanse();
    key();
    cout<<"It can also reveal and alter data at specified coordinates. For example in Tensor 4 at [7,7,5] we have:"<<endl;
    tensors[4].reveal(5,7,7);
    key();
    cout<<"We can also change it to 73.7374"<<endl;
    tensors[4].change(73.7374, 5, 7, 7);
    key();
    cout<<tensors[4];
    key();
    cout<<"Now you can try doing something yourself. Program will now allow you to edit your input tensor and perform different"<<endl<<" mathematical operations between it, and the other ones. You can also compare to see if they're different."<<endl<<"For greater variety, Tensors will now all be reinitialized to different sizes according to their numbers"<<endl<<"(ex. Tensor 2 is 2x2x2, Tensor 3 is 3x3x3 etc.). Program will also add tensors 5 and 6"<<endl;
    int i;
    string command;
    for(i=1;i<7;i++)
    {
        tensors[i].cleanse();
        adapt(tensors[i],i,i,i);
        cout<<"Tensor "<<i<<" is:"<<endl;
        cout<<tensors[i];
        key();
    }
    while(1)
    {
        cout<<"What do you want to? (your options are: +, -, *, +=, -=, *=, ==, !=, new, exit)."<<endl;
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
        if(command=="new") i=8;
        if(command=="exit") i=9;
        switch(i)
        {
            case 0:
                fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                cin>>i;
                if(i>6)
                {
                    cout<<"No such Tensor"<<endl;
                    break;
                }
                fseek(stdin, 0, SEEK_END);
                if(tensors[i]==tensor) cout<<"True"<<endl;
                else cout<<"False"<<endl;
                break;
            case 1:
                fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                cin>>i;
                if(i>6)
                {
                    cout<<"No such Tensor"<<endl;
                    break;
                }
                fseek(stdin, 0, SEEK_END);
                if(tensors[i]!=tensor) cout<<"True"<<endl;
                else cout<<"False"<<endl;
                break;
            case 2:
                fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                cin>>i;
                if(i>6)
                {
                    cout<<"No such Tensor"<<endl;
                    break;
                }
                fseek(stdin, 0, SEEK_END);
                tensors[i]+=tensor;
                cout<<tensors[i];
                break;
            case 3:
                fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                cin>>i;
                if(i>6)
                {
                    cout<<"No such Tensor"<<endl;
                    break;
                }
                fseek(stdin, 0, SEEK_END);
                tensors[i]-=tensor;
                cout<<tensors[i];
                break;
            case 4:
                fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                cin>>i;
                if(i>6)
                {
                    cout<<"No such Tensor"<<endl;
                    break;
                }
                fseek(stdin, 0, SEEK_END);
                tensors[i]*=tensor;
                cout<<tensors[i];
                break;
            case 5:
                fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                cin>>i;
                if(i>6)
                {
                    cout<<"No such Tensor"<<endl;
                    break;
                }
                fseek(stdin, 0, SEEK_END);
                tensors[0]=tensors[i]+tensor;
                cout<<tensors[0];
                tensors[0].cleanse();
                break;
            case 6:
                fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                cin>>i;
                if(i>6)
                {
                    cout<<"No such Tensor"<<endl;
                    break;
                }
                fseek(stdin, 0, SEEK_END);
                tensors[0]=tensors[i]-tensor;
                cout<<tensors[0];
                tensors[0].cleanse();
                break;
            case 7:
                fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                cin>>i;
                if(i>6)
                {
                    cout<<"No such Tensor"<<endl;
                    break;
                }
                fseek(stdin, 0, SEEK_END);
                tensors[0]=tensors[i]*tensor;
                cout<<tensors[0];
                tensors[0].cleanse();
                break;
            case 8:
                tensor.cleanse();
                cin>>tensor;
                cout<<"Your tensor is:"<<endl;
                cout<<tensor;
                break;
            case 9:
                for(i=1;i<7;tensors[i].cleanse(), i++);
                tensor.cleanse();
                return 0;
            default:
                cout<<"Unknown action."<<endl;
                break;
        }
    }

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
				data[i]=rand()/(rand()+1);
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

