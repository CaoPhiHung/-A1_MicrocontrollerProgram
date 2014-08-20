#include "MacrochipPIC32F42.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

const int moveValueToWOption = 0x50;
const int moveWToMemoryOption = 0x51;
const int addValueToWOption = 0x5A;
const int subtractValueFromWOption = 0x5B;
const int goToAddressOption = 0x6E;
const int branchIfNotEqualOption = 0x70;
const int halfOpcodeOption = 0xFF;

MacrochipPIC32F42::MacrochipPIC32F42(): Microcontroller(1536)
{
	cout << "MacrochipPIC32F42 selected\n";
	this->reset();
}

Microcontroller* MacrochipPIC32F42::createNewObject()
{
	return new MacrochipPIC32F42();
}

unsigned int MacrochipPIC32F42::getW()
{
	return this->W ;
}

void MacrochipPIC32F42::setW(unsigned int w)
{
	this->W = w;
}


string MacrochipPIC32F42::getStatusString()
{
	ostringstream ost;
	ost << "\tProgramCounter: "<< hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n" << "\tRegister W: " << hex << this->getW() << "\n";
	string s = ost.str();
	return s;
}

void MacrochipPIC32F42::executeFromCurrentPC()
{
	unsigned char opcode = this->getMemoryArray()[this->getProgramCounter()];

	switch(opcode)
	{
		case moveValueToWOption: moveValueToW();
			break;
		case moveWToMemoryOption: moveWToMemory();
			break;
		case addValueToWOption: addValueToW();
			break;
		case subtractValueFromWOption: subtractValueFromW();
			break;
		case goToAddressOption: goToAddress();
			break;
		case branchIfNotEqualOption: branchIfNotEqual();
			break;
		case halfOpcodeOption: halfOpcode();
			break;
		default: cout << "\tSIGOP.Invalid opcode. Program Counter = " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
			break;
	}
}

void MacrochipPIC32F42::executeFromSpecificLocation()
{
	cout << "\tlocation? ";
	int address;
	cin >> hex >> address;

	if(address < 0 || address > this->getMemoryLimit())
	{
		cerr << "\tInvalid Adress\n";
	}else{

		this->setProgramCounter(address);
		executeFromCurrentPC();
	}
}

void MacrochipPIC32F42::reset()
{
	this->setW(0);
	this->setProgramCounter(0);
	cout << "\tMicrocontroller has been reset\n";	
}

void MacrochipPIC32F42::moveValueToW()
{
	int newProgramCounter = this->getProgramCounter() + 2;
	if(newProgramCounter > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		unsigned int newValue = this->getMemoryArray()[this->getProgramCounter() + 1];
		cout << "\t.....Move Value To W....\n";
		this->setW(newValue);
		cout << "\tNew W : " << hex << newValue << "\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";

		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();

	}
}

void MacrochipPIC32F42::moveWToMemory()
{
	int newProgramCounter = this->getProgramCounter() + 3;
	if(newProgramCounter > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		unsigned char highByte = this->getMemoryArray()[(this->getProgramCounter() + 1)];
		unsigned char lowByte = this->getMemoryArray()[(this->getProgramCounter() + 2)];
		unsigned int location = (highByte << 8) | lowByte;
		unsigned int newValue = this->getW();
		this->getMemoryArray()[location] = newValue;
		cout << "\t.....Move W To Memory...\n";
		this->setW(newValue);
		cout << "\tNew Value : " << hex << newValue << "\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";

		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();
	}
}

void MacrochipPIC32F42::addValueToW()
{
	int newProgramCounter = this->getProgramCounter() + 2;
	if(newProgramCounter > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		unsigned int value = this->getMemoryArray()[this->getProgramCounter() + 1];
		unsigned int oldValue = this->getW();
		unsigned int newValue = value + oldValue;
		cout << "\t.....Add Value To W....\n";
		cout << "\tOld W : " << hex << oldValue << "\n";
		this->setW(newValue);
		cout << "\tNew W : " << hex << newValue << "\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";

		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();
	}
}

void MacrochipPIC32F42::subtractValueFromW()
{	
	int newProgramCounter = this->getProgramCounter() + 2;
	if(newProgramCounter > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		unsigned int value = this->getMemoryArray()[this->getProgramCounter() + 1];
		unsigned int oldValue = this->getW();
		unsigned int newValue = oldValue - value;
		cout << "\t.....Subtract Value From W....\n";
		cout << "\tOld W : " << hex << oldValue << "\n";
		this->setW(newValue);
		cout << "\tNew W : " << hex << newValue << "\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";

		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();

	}
}

void MacrochipPIC32F42::goToAddress()
{
	unsigned char highByte = this->getMemoryArray()[(this->getProgramCounter() + 1)];
	unsigned char lowByte = this->getMemoryArray()[(this->getProgramCounter() + 2)];
	int location = (highByte << 8) | lowByte;
	
	if(location <= this->getMemoryLimit())
	{
		cout << "\t.....Go to Address....\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		cout << "\tNew Location : " << hex << setfill('0') << setw(4) << location << "\n";
		this->setProgramCounter(location);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();

	}else{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}
}

void MacrochipPIC32F42::branchIfNotEqual()
{
	unsigned int WValue = this->getW();
	unsigned int compareValue = this->getMemoryArray()[(this->getProgramCounter() + 1)];
	unsigned char highByte = this->getMemoryArray()[(this->getProgramCounter() + 2)];
	unsigned char lowByte = this->getMemoryArray()[(this->getProgramCounter() + 3)];
	int location = (highByte << 8) | lowByte;
	int newLocation = 0;
	
	cout << "\t.....Branch If Not Equal....\n";
	if(WValue == compareValue)
	{
		cout << "\tEqual\n";
		newLocation = this->getProgramCounter() + 4 ;

	}else if(WValue != compareValue){
		cout << "\tNot Equal\n";
		newLocation = location;
	}

	if(newLocation > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->setProgramCounter(newLocation);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();
	}

}

void MacrochipPIC32F42::halfOpcode()
{
	cout << "\tProgram halted";
}