#include "Microcontroller.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

Microcontroller::Microcontroller(int size)
{
	this->programCounter = 0;	
	this->memoryLimit = size;
	this->memoryArray = new unsigned char [size];
}


	// Destructor
Microcontroller::~Microcontroller()
{
	delete [] this->memoryArray;
}

int Microcontroller::getMemoryLimit()
{
	return this->memoryLimit;
}

void Microcontroller::addDefaultValueIntoArray()
{

	for (int i = 0; i < this->memoryLimit; i++)
	{
		this->memoryArray[i] = 0;
	}
}

int Microcontroller::getProgramCounter()
{
	return this->programCounter;
}

void Microcontroller::setProgramCounter(int newProgramCounter)
{
	this->programCounter = newProgramCounter;
}

unsigned char* Microcontroller::getMemoryArray()
{
	return this->memoryArray;
}

void Microcontroller::reset()
{
	//do something
}

void Microcontroller::executeFromCurrentPC()
{
	//do something
}

void Microcontroller::executeFromSpecificLocation()
{
	//do something
}

void Microcontroller::printMenu()
{
	cout << "\t\t---------------MENU---------------\n";
	cout << "\tComand c : Connect To Microcontroller\n";
	cout << "\tComand d : Display All The Memory\n";
	cout << "\tComand e : Execute From Current PC\n";
	cout << "\tComand g : Execute From The Specific Location\n";
	cout << "\tComand h : Display Help\n";
	cout << "\tComand l : Look At Memory\n";
	cout << "\tComand m : Modify Memory\n";
	cout << "\tComand r : Reset Microcontroller\n";
	cout << "\tComand s : Display PC And Register\n";
	cout << "\tComand q : Quit the program\n\n";
}

string Microcontroller::getStatusString()
{
	string status = "ProgramCounter: " + this->programCounter;
	return status;
}
//Common Microcontroller functions

// print out the value at the location which provided by user
bool Microcontroller::lookAtMemory(int location)
{

	if(location < 0 || location >= this->getMemoryLimit())
	{
		cerr << "\tInvalid Adress\n";
		return false;
	}else{
		unsigned int oldValue = (this->getMemoryArray())[location] ;
		cout << "\tOld value:" << hex << oldValue << "\n";
		return true;
	}

}

// modify the value at the location which provided by user
void Microcontroller::modifyMemory(int location)
{
	
	if(lookAtMemory(location))
	{
		cout << "\tnew? ";
		unsigned int input;
		cin >> hex >> input;
		//stack over flow => http://stackoverflow.com/questions/3270307/how-do-i-get-the-lower-8-bits-of-int
		unsigned char lower8bitValue = (input & 0xFF);
		this->getMemoryArray()[location] = lower8bitValue;
		unsigned int value = this->getMemoryArray()[location] ;
		cout << "Value after modify: "<< hex << value << "\n"; 
	}
}

// display all Memory
void Microcontroller::displayAllMemory()
{
	for (int i = 0; i < this->getMemoryLimit(); ++i)
	{
		//print the address of the top-most left-most value
		if((i % 16) == 0)
		{
			cout << "\n" << setfill('0') << setw(4)<< hex << i << " ";
		}
	
		//print the value in side the memory array with is 2 byte
		unsigned int value = this->getMemoryArray()[i];
		cout << " " << setfill('0') << setw(2) << hex << value;
	}
}

