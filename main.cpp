#include <iostream>
#include <iomanip>
#include <string>
#include "MopsR500.h"
#include "MacrochipPIC32F42.h"
#include "Rotamola34HC22.h"
#include "MicrocontrollerFactory.h"

using namespace std;
const char connectToMicrocontrollerOption = 'C';
const char printMenuOption = 'H';
const char executeFromCurrentPCOption = 'E';
const char modifyMemoryOption = 'M';
const char lookAtMemoryOption = 'L';
const char executeFromSpecificLocationOption = 'G';
const char displayAllMemoryOption = 'D';
const char displayStatusOption = 'S';
const char quitOption = 'Q';

//return the location from the userInput
int getLocation()
{
	cout << "\tlocation? ";
	int location;
	cin >> hex >> location;
	return location;
}


//checking the user input 
char checkInput()
{
	string userInput;
	cin >> userInput;
	if(userInput.size() > 1){
		return 'x';
	}else{
		return toupper(userInput.at(0));
	}
}

//switch option
void switchOption(char option, Microcontroller** mc)
{
	MicrocontrollerFactory mf;
	if(*mc == 0)
	{
		switch(option)
		{  
			case connectToMicrocontrollerOption :  
				mf.connectToMicrocontroller(mc);
				cout << "\n";
				break;

			case printMenuOption:  
				(*mc)->printMenu();
				cout << "\n";
				break;

			case quitOption:  
				cout << "\tThe Microcontroller Program is shutting down\n";
				break;

			default: cerr << "\tThe Microcontroller is not connected to any device\n";
				break;

		}
	}else{

		switch(option)
		{
			case connectToMicrocontrollerOption :  
				mf.connectToMicrocontroller(mc);
				cout << "\n";
				break;

			case displayAllMemoryOption:  
				cout << "\t..........Display All Memory..........\n";
				(*mc)->displayAllMemory();
				cout << "\n";
				break;

			case executeFromCurrentPCOption:	
				cout << "\t..........Execute From Current PC..........\n";  
				(*mc)->executeFromCurrentPC();
				cout << "\n";
				break;

			case executeFromSpecificLocationOption:	
				cout << "\t..........Execute From Specific Location..........\n";
				(*mc)->executeFromSpecificLocation();
				cout << "\n";
				break;

			case printMenuOption:  
				(*mc)->printMenu();
				cout << "\n";
				break;

			case lookAtMemoryOption:  	
				cout << "\t..........Look At Memory..........\n";
				(*mc)->lookAtMemory(getLocation());
				cout << "\n";
				break;

			case modifyMemoryOption:  	
				cout << "\t..........Modify Memory..........\n";
				(*mc)->modifyMemory(getLocation());
				cout << "\n";
				break;

			case displayStatusOption:	
				cout << "\t..........Display Microcontroller Status..........\n";  
				cout << (*mc)->getStatusString();
				cout << "\n";
				break;

			case quitOption:  
				cout << "\tThe Microcontroller Program is shutting down\n\n";
				break;

			default:   cerr << "\tWrong input!! Please enter other input or Type h for help.\n";
				break;
		}
	}
}

//main function
int main(int argc, char const *argv[])
{
	char userInput;
	Microcontroller* mc = 0;
	cout << "\n\tWELLCOME TO THE MICROCONTROLLER EMULATOR PROGRAM\n\n";
	cout << "\tCHOOSE YOUR COMMAND FROM THE MENU BELOW \n\n";
	mc->printMenu();
	cout << "Enter your command: \n\n";
	
	do
	{
		cout << "> \t" ;
		userInput = checkInput();
		switchOption(userInput,&mc);		

	} while (!(userInput == quitOption)) ;

	return 0;
}
