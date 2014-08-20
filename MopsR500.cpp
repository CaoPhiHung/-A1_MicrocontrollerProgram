#include "MopsR500.h"
#include <iostream>
#include <string>
#include "Microcontroller.h"
#include <sstream>
#include <iomanip>

using namespace std;

const int addOption = 0x0A;
const int subtractOption = 0x13;
const int goToAddressOption = 0x16;
const int branchRelativeOption = 0x17;
const int halfOpcodeOption = 0xFF;

MopsR500::MopsR500(): Microcontroller(1024)
{
	cout << "\tR500 selected\n";
	this->reset();
}

Microcontroller* MopsR500::createNewObject()
{
	return new MopsR500();
}

string MopsR500::getStatusString()
{
	ostringstream ost;
	ost << "\tProgramCounter: " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
	string s = ost.str();
	return s;
}

void MopsR500::reset()
{
	this->setProgramCounter(0);
	this->addDefaultValueIntoArray();
	cout << "\tMicrocontroller has been reset\n";	
}

void MopsR500::executeFromCurrentPC()
{

	unsigned char opcode = this->getMemoryArray()[this->getProgramCounter()];

	switch(opcode)
	{
		case addOption: addValue();
			break;
		case subtractOption: subtractValue();
			break;
		case goToAddressOption: goToAddress();
			break;
		case branchRelativeOption: branchRelative();
			break;
		case halfOpcodeOption: halfOpcode();
			break;
		default: cout << "\tSIGOP.Invalid opcode. Program Counter = " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
			break;
	}

}

void MopsR500::executeFromSpecificLocation()
{
	cout << "\tlocation? ";
	int address;
	cin >> hex >> address;

	if(address < 0 || address >= this->getMemoryLimit())
	{
		cerr << "\tInvalid Adress\n";
	}else{

		this->setProgramCounter(address);
		executeFromCurrentPC();
	}

}

//add value to memory
void MopsR500::addValue()
{
	int newProgramCounter = this->getProgramCounter() + 4;
	if(newProgramCounter > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		unsigned int newValue = this->getMemoryArray()[this->getProgramCounter() + 1];
		unsigned char highByte = this->getMemoryArray()[(this->getProgramCounter() + 2)];
		unsigned char lowByte = this->getMemoryArray()[(this->getProgramCounter() + 3)];
		unsigned int location = (highByte << 8) | lowByte;
		unsigned int oldValue = this->getMemoryArray()[location];
		unsigned int result = oldValue + newValue;
		
		//make sure that the new value which added lower than 8 bit 
		unsigned char lower8bitValue = (result & 0xFF);

		this->getMemoryArray()[location] = lower8bitValue;

		cout << "\t.....Add Value....\n";
		cout << "\tOld value : " << hex << oldValue << "\n";
		cout << "\tNew value : " << hex << newValue << "\n";
		cout << "\tResult : "<< hex << result << "\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";

		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();
	}
}

//subtract value to memory
void MopsR500::subtractValue()
{
	int newProgramCounter = this->getProgramCounter() + 4;
	if(newProgramCounter > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		unsigned int newValue = this->getMemoryArray()[this->getProgramCounter() + 1];
		unsigned char highByte = this->getMemoryArray()[(this->getProgramCounter() + 2)];
		unsigned char lowByte = this->getMemoryArray()[(this->getProgramCounter() + 3)];
		unsigned int location = (highByte << 8) | lowByte;
		unsigned int oldValue = this->getMemoryArray()[location];
		unsigned int result = oldValue - newValue;
		this->getMemoryArray()[location] = result;
		

		cout << "\t.....Subtract Value....\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		cout << "\tOld value : " << hex << oldValue << "\n";
		cout << "\tNew value : " << hex << newValue << "\n";
		cout << "\tSubtract result : " << hex << result << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";

		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();
	}
}

//go to address
void MopsR500::goToAddress()
{
	unsigned char highByte = this->getMemoryArray()[(this->getProgramCounter() + 1)];
	unsigned char lowByte = this->getMemoryArray()[(this->getProgramCounter() + 2)];
	int location = (highByte << 8) | lowByte;
	
	if(location <= this->getMemoryLimit())
	{
		cout << "\t.....Go to Address....\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		cout << "\tNew Location : " << hex << setfill('0') << setw(4) <<  location << "\n";
		this->setProgramCounter(location);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";

		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();
	}else{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}
}

//branch relative
void MopsR500::branchRelative()
{
	signed char signedValue = this->getMemoryArray()[(this->getProgramCounter() + 1)];
	int value = signedValue;
	int newProgramCounter = this->getProgramCounter() + value;

	if(newProgramCounter <= this->getMemoryLimit()){
		cout << "\t.....Branch Relative....\n";
		cout << "\tOld Program Counter: " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		cout << "\tSigned Value: " << hex << value << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program Counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter()<< "\n";

		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();

	}else{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}

}

//half opcode
void MopsR500::halfOpcode()
{
	cout << "\tProgram halted";
}