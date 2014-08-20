#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H
#include <string>
using namespace std;

    class Microcontroller
	{
		private:
		int programCounter;
		unsigned char* memoryArray;
		int memoryLimit;
		
		public:
		Microcontroller(int);
		// destructor
		virtual ~Microcontroller();

		//getter and setter of program counter 
		int getProgramCounter();
		void setProgramCounter(int);

		//getter and setter of memory
		unsigned char* getMemoryArray();

		void addDefaultValueIntoArray();

		//getter and setter of memory limit
		int getMemoryLimit();

		// reset the controller
		virtual void reset();

		// execute from current program counter
		virtual void executeFromCurrentPC();

		virtual void executeFromSpecificLocation();

		//print the status string 
		virtual string getStatusString();

		//print the menu
		void printMenu();

		//look at memory location by user input
		bool lookAtMemory(int location);
		
		//modify memory by user input
		void modifyMemory(int location);
		
		//display all memory
		void displayAllMemory();
	};

#endif
