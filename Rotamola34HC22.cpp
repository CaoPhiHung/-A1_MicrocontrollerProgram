#include "Rotamola34HC22.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;
const int moveAToMemoryOption = 0x0C;
const int loadAWithValueOption = 0x37;
const int loadBWithValueOption = 0x38;
const int incrementRegisterAOption = 0x53;
const int branchAlwaysOption = 0x5A;
const int brachIfASmallerThanBOption = 0x5B;
const int brachIfLessThanAOption = 0x5D;
const int halfOpcodeOption = 0x64;

Rotamola34HC22::Rotamola34HC22(): Microcontroller(512)
{
	cout << "Rotamola34HC22 selected\n";
	this->reset();
}

unsigned int Rotamola34HC22::getA()
{
	return this->A;
}

unsigned int Rotamola34HC22::getB()
{
	return this-> B;
}

void Rotamola34HC22::setA(unsigned int a)
{
	this->A = a;
}

void Rotamola34HC22::setB(unsigned int b)
{
	this->B = b;
}

//create the microcontroller pointer which is pointed in the new microcontroller
Microcontroller* Rotamola34HC22::createNewObject()
{
	return new Rotamola34HC22();
}

// return the string that contain the program counter ,a and b.
string Rotamola34HC22::getStatusString()
{
	ostringstream ost;
	ost << "\tProgramCounter: "<< hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n" << "\tRegister A: " << this->A << "\n";
	ost << "\tRegister B: " << this->B ;
	string s = ost.str();
	return s;
}

// run the program with the current programcounter
void Rotamola34HC22::executeFromCurrentPC()
{
	unsigned char opcode = this->getMemoryArray()[this->getProgramCounter()];

	switch(opcode)
	{
		case moveAToMemoryOption: moveAToMemory();
			break;
		case loadAWithValueOption: loadAWithValue();
			break;
		case loadBWithValueOption: loadBWithValue();
			break;
		case incrementRegisterAOption: incrementRegisterA();
			break;
		case branchAlwaysOption: branchAlways();
			break;
		case brachIfASmallerThanBOption: brachIfASmallerThanB();
			break;
		case brachIfLessThanAOption: brachIfLessThanA();
			break;
		case halfOpcodeOption: halfOpcode();
			break;
		default: cout << "\tSIGOP.Invalid opcode. Program Counter = " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
			break;
	}
}

// run the program in the specificLocation (given location)
void Rotamola34HC22::executeFromSpecificLocation()
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

void Rotamola34HC22::reset()
{
	this->setProgramCounter(509);
	cout << "\tMicrocontroller has been reset\n";	
}

// add the value of a to the memory and increase the program counter

void Rotamola34HC22::moveAToMemory()
{
	unsigned char highByte = this->getMemoryArray()[(this->getProgramCounter() + 1)];
	unsigned char lowByte = this->getMemoryArray()[(this->getProgramCounter() + 2)];
	int location = (highByte << 8) | lowByte;
	int newProgramCounter = this->getProgramCounter() + 3;
	
	if(newProgramCounter > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		cout << "\t.....Move A To Memory....\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->getMemoryArray()[location] = this->getA();

		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();
	}

}

// add new value to a and change the program counter

void Rotamola34HC22::loadAWithValue()
{
	unsigned int value= this->getMemoryArray()[(this->getProgramCounter() + 1)];
	int newProgramCounter = this->getProgramCounter() + 2;
	
	if(newProgramCounter > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		cout << "\t.....Load A With Value....\n";
		cout << "\tOld A: " << this->getA() << "\n";
		this->setA(value);
		cout << "\tNew A: " << this->getA() << "\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();
	}
	
}
//add the new value to b and change the location of program counter

void Rotamola34HC22::loadBWithValue()
{
	unsigned int value= this->getMemoryArray()[(this->getProgramCounter() + 1)];
	int newProgramCounter = this->getProgramCounter() + 2;
	
	if(newProgramCounter > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		cout << "\t.....Load B With Value....\n";
		cout << "\tOld B: " << this->getB() << "\n";
		this->setB(value);
		cout << "\tNew B: " << this->getB() << "\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();
	}
}

// move the program counter to the next location and increase a
void Rotamola34HC22::incrementRegisterA()
{
	int newProgramCounter = this->getProgramCounter() + 1;
	unsigned int value = this->getA() + 1;
	if(newProgramCounter > this->getMemoryLimit())
	{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}else{
		cout << "\t.....Increment Register A....\n";
		cout << "\tOld A: " << this->getA() << "\n";
		this->setA(value);
		cout << "\tNew A: " << this->getA() << "\n";
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();
	}

}

//move the program counter to new location
void Rotamola34HC22::branchAlways()
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

//move the program counter to the new location if a < b
void Rotamola34HC22::brachIfASmallerThanB()
{
	unsigned char highByte = this->getMemoryArray()[(this->getProgramCounter() + 1)];
	unsigned char lowByte = this->getMemoryArray()[(this->getProgramCounter() + 2)];
	int location = (highByte << 8) | lowByte;
	int newProgramCounter= 0;

	cout << "\t.....Branch If A < B....\n";
	if(this->getA() < this->getB())
	{
		cout << "\tA < B\n";
		newProgramCounter = location;
	}else{
		cout << "\tA >= B\n";
		newProgramCounter = this->getProgramCounter() + 3;
	}

	if(newProgramCounter <= this->getMemoryLimit())
	{
		
		cout << "\tOld Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";
		cout << "\tNew Location : " << hex << setfill('0') << setw(4) << location << "\n";
		this->setProgramCounter(newProgramCounter);
		cout << "\tNew Program counter : " << hex << setfill('0') << setw(4) << this->getProgramCounter() << "\n";

		//countinute to execute next instruction until meet the halfcode
		executeFromCurrentPC();

	}else{
		cerr << "\tSIGWEED. Program executed past top of memory\n";
	}

}

//move the program counter to new location if the value < a
void Rotamola34HC22::brachIfLessThanA()
{
	unsigned int AValue = this->getA();
	unsigned int compareValue = this->getMemoryArray()[(this->getProgramCounter() + 1)];
	unsigned char highByte = this->getMemoryArray()[(this->getProgramCounter() + 2)];
	unsigned char lowByte = this->getMemoryArray()[(this->getProgramCounter() + 3)];
	int location = (highByte << 8) | lowByte;
	int newLocation = 0;
	
	cout << "\t.....Branch If Less Than A....\n";
	if(AValue >= compareValue)
	{
		cout << "\tA >= value\n";
		newLocation = location;
	}else{
		cout << "\tA < value\n";
		newLocation = this->getProgramCounter()+4;
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

//halfOpcode
void Rotamola34HC22::halfOpcode()
{
	cout << "\tProgram halted";
}