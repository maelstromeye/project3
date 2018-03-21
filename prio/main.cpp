/*#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include<cctype>
#include "Tensor.h"
#define CUPD "update"
#define CNEW "create"
#define CDEL "delete"
#define CSHO "show"
#define CREV "reveal"
#define CHEL "help"
#define CKIL "kill"
#define CMAT "math"
using namespace std;
int detecc (string order);
void help (string what);
int find (string what);
int namecount=0;
vector <string> names;
vector <Tensor> Tensors;
int main(void)
{
	int crds[3], i;
	double value;
	char space;
	Tensor ichi, ni, san;
	string command, what;
	cout<<"Welcome, here you can test the tensor class I've created. Type 'help' for a list of commands."<<endl;
	while(1)
	{
		cin>>command;
		switch (detecc(command))
		{
			case 1:
				fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                getline(cin, what);
                i=find(what);
				if (i==-1) break;
				cout<<"Input crdx, then crdy, then crdz, then the desired value"<<endl;
				for(i=0;i<4;i++)	//czy akceptowalny znak
				{
					space=cin.get();
					if((!isdigit(space))&&(space!='-')&&(space!='\n'))	//jezeli nie akcpetowalny
					{
						std::cout<<"Unexpected input data. Input the data again"<<std::endl;
						i=0;
						fseek(stdin, 0, SEEK_END);
						continue;
					}
					cin.putback(space);	//jezeli dobry to wraca do bufora
					if(i==3)
					{
						cin>>value;
						break;
					}
					cin>>crds[i];
					if (i==0) cout<<"crdx="<<crds[i]<<endl;
					if (i==1) cout<<"crdy="<<crds[i]<<endl;
					if (i==2) cout<<"crdz="<<crds[i]<<endl;
					fseek(stdin, 0, SEEK_END);
				}
				if(!Tensors[i].change(value, crds[0], crds[1], crds[2])) cout<<"Data doesn't exist"<<endl;
				else cout<<"Updated"<<endl;
				break;
			case 2:
				cout<<"Type a name for your new tensor"<<endl;
				cin.get();
				getline(cin, command);
				if(find(command)!=-1)
                    {
                        cout<<"Name taken"<<endl;
                        break;
                    }
				names.push_back(command);
				cout<<"Your new tensor is called: "<<names[namecount]<<endl;
				cin>>ichi;
				cout<<"accpet?"<<endl;
				Tensors.push_back(ichi);
				cout<<"accept"<<endl;
				ichi.~Tensor();
				namecount++;
				break;
			case 3:
				cout<<"Type a name for your new tensor"<<endl;
				cin.get();
				getline(cin, command);
				names.push_back(command);
				cout<<"Your new tensor is called: "<<names[namecount]<<endl;
				cin>>ichi;
				Tensors.push_back(ichi);
				namecount++;
				break;
			case 4:
				fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                getline(cin, what);
                i=find(what);
				if(i==-1) break;
				cout<<Tensors.at(i);
				break;
			case 5:
				fseek(stdin, 0, SEEK_END);
                cout<<"Specify the tensor."<<endl;
                getline(cin, what);
                i=find(what);
				if (i==-1) break;
				cout<<"Input crdx, then crdy, then crdz."<<endl;
				for(i=0;i<3;i++)	//czy akceptowalny znak
				{
					space=cin.get();
					if((!isdigit(space))&&(space!='-')&&(space!='\n'))	//jezeli nie akcpetowalny
					{
						std::cout<<"Unexpected input data. Input the data again"<<std::endl;
						i=0;
						fseek(stdin, 0, SEEK_END);
						continue;
					}
					cin.putback(space);	//jezeli dobry to wraca do bufora
					cin>>crds[i];
					if (i==0) cout<<"crdx="<<crds[i]<<endl;
					if (i==1) cout<<"crdy="<<crds[i]<<endl;
					if (i==2) cout<<"crdz="<<crds[i]<<endl;
					fseek(stdin, 0, SEEK_END);
				}
				if(!Tensors[i].reveal(crds[0], crds[1], crds[2])) cout<<"Data doesn't exist"<<endl;
				else cout<<"At: x="<<crds[0]<<" y="<<crds[1]<<" z="<<crds[2]<<endl;
				break;
			case 6:
				cin>>command;
				help(command);
				break;
			case 7:
				return 0;
			case 8:
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
		}
	}
}
int detecc (string order)
{
	if (order==CUPD) return 1;
	if (order==CNEW) return 2;
	if (order==CDEL) return 3;
	if (order==CSHO) return 4;
	if (order==CREV) return 5;
	if (order==CHEL) return 6;
	if (order==CKIL) return 7;
	if (order==CMAT) return 8;
	return 0;
}
int find(string what)
{
    string nani;
	int i;
	for(i=0;i<namecount;i++)
	{
		nani=names[i];
		if (nani==what) return i;
	}
	return -1;
}
void help (string what)
{
	using namespace std;
	switch (detecc(what))
		{
			case 1:
				cout<<"'update' 'name' 'coordx:coordy:coordz' 'value'";
				break;
			case 2:
				cout<<"new";
				break;
			case 3:
				cout<<"del";
				break;
			case 4:
				cout<<"sho";
				break;
			case 5:
				cout<<"hel";
				break;
			default:
				break;
		}
		return;
}
*/
