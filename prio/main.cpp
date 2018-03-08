#include <iostream>
#include <cstring>
#include <stdio.h>
#define CUPD "update"
#define CNEW "create"
#define CDEL "delete"
#define CSHO "show"
#define CHEL "help"
int detecc (std::string order);
void help (std::string what);
int main(void)
{
	using namespace std; 
	string command;
	cout<<"Welcome, here you can test the tensor class I've created. Type 'help' for a list of commands."<<endl;
	while(1)
	{
		cin>>command;
		switch (detecc(command))
		{
			case 1:
				cout<<"upd";
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
	if (order==CHEL) return 5;
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
