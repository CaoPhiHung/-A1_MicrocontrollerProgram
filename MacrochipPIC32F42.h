#include "Microcontroller.h"

class MacrochipPIC32F42 : public Microcontroller
{
	private:
		unsigned int W;
	public:
	MacrochipPIC32F42();

	//getter and setter of register W
	unsigned int getW();
	void setW(unsigned int W);

	Microcontroller* createNewObject();
	
	string getStatusString();
	
	void executeFromCurrentPC();
	void executeFromSpecificLocation();

	void moveValueToW();
	void moveWToMemory();
	void addValueToW();
	void subtractValueFromW();
	void goToAddress();
	void branchIfNotEqual();
	void halfOpcode();

	void reset();
	
};