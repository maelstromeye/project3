#include <iostream>
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
int detecc (std::string order);
void help (std::string what);
int main(void)
{
	using namespace std; 
	int namecount=0;
	int crds[3], i;
	double value;
	char space;
	vector<string> names;	//imiona uzywane przez uzytkowika
	vector<Tensor> Tensors;
	Tensor ichi, ni, san;
	string command;
	cout<<"Welcome, here you can test the tensor class I've created. Type 'help' for a list of commands."<<endl;
	while(1)
	{
		cin>>command;
		switch (detecc(command))
		{
			case 1:
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
				if(!ichi.change(value, crds[0], crds[1], crds[2])) cout<<"Data doesn't exist"<<endl;
				else cout<<"Updated"<<endl;
				break;
			case 2:
				cout<<"Type a name for your new tensor"<<endl;
				cin.get();	
				getline(cin, command);
				names.push_back(command);
				cout<<"Your new tensor is called: "<<names[namecount]<<endl;
				cin>>ichi;
				namecount++;
				break;
			case 3:
				cout<<"Type a name for your new tensor"<<endl;
				cin.get();	
				getline(cin, command);
				names.push_back(command);
				cout<<"Your new tensor is called: "<<names[namecount]<<endl;
				cin>>ni;
				namecount++;
				break;
			case 4:
				//san=(ni+ichi);
				//cout<<san;
				cout<<ni;
				cout<<ichi;
				san=(ni+ichi);
				cout<<san;
				san+=ichi;
				cout<<ni;
				break;
			case 5:
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
				if(!ichi.reveal(crds[0], crds[1], crds[2])) cout<<"Data doesn't exist"<<endl;
				else cout<<"At: x="<<crds[0]<<" y="<<crds[1]<<" z="<<crds[2]<<endl;
				break;	
			case 6:
				cin>>command;
				help(command);
				break;
			default:
				break;				
		}		
	}
}
int detecc (std::string order)
{
	if (order==CUPD) return 1;
	if (order==CNEW) return 2;
	if (order==CDEL) return 3;
	if (order==CSHO) return 4;
	if (order==CREV) return 5;
	if (order==CHEL) return 6;
	return 0;	
}
void help (std::string what)
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
