#include "Microcontroller.h"

class MopsR500 : public Microcontroller
{
	public:
	
	MopsR500();

	Microcontroller* createNewObject();

	string getStatusString();

	void executeFromCurrentPC();
	void executeFromSpecificLocation();

	//add value to memory
	void addValue();

	//subtract value to memory
	void subtractValue();

	//go to address
	void goToAddress();
	
	//branch relative
	void branchRelative();

	//half opcode
	void halfOpcode();

	void reset();

};