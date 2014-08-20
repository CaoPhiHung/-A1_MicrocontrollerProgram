#include "Microcontroller.h"

class Rotamola34HC22 : public Microcontroller
{
	private:
		unsigned int A;
		unsigned int B;
	public:
	Rotamola34HC22();

	Microcontroller* createNewObject();

	//getter and setter for A,B
	unsigned int getA();
	unsigned int getB();
	void setA(unsigned int a);
	void setB(unsigned int b);

	string getStatusString();
	void executeFromCurrentPC();
	void executeFromSpecificLocation();

	void moveAToMemory();
	void loadAWithValue();
	void loadBWithValue();
	void incrementRegisterA();
	void branchAlways();
	void brachIfASmallerThanB();
	void brachIfLessThanA();
	void halfOpcode();

	void reset();
};