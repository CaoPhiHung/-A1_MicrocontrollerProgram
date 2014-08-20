#include "MicrocontrollerFactory.h"
#include "MopsR500.h"
#include "MacrochipPIC32F42.h"
#include "Rotamola34HC22.h"
#include <iostream>
#include <string>
using namespace std;

// create the connection to the Microcontroller by create the pointer that point to the new microcontroller
// when adding new microcontroller just add here
void MicrocontrollerFactory::connectToMicrocontroller(Microcontroller** mc)
{
	string microcontrollerType;
	cout << "\t..........Connect to Microcontroller..........\n";
	cout << "\ttype? ";
	cin >> microcontrollerType;

	if(microcontrollerType.compare("R500") == 0 || microcontrollerType.compare("r500") == 0)
	{
		MopsR500* r500 = static_cast<MopsR500*> (*mc);
		*mc = r500->createNewObject();	
	}else if (microcontrollerType.compare("PIC32F42")==0 || microcontrollerType.compare("pic32f42") == 0)
	{
		MacrochipPIC32F42* pic32f42 = static_cast<MacrochipPIC32F42*> (*mc);
		*mc = pic32f42->createNewObject();

	}else if (microcontrollerType.compare("34HC22")==0 || microcontrollerType.compare("34hc22") == 0)
	{
		Rotamola34HC22* rotamola = static_cast<Rotamola34HC22*> (*mc);
		*mc = rotamola->createNewObject();

	}else{
		cerr << "\tInvalid Type\n";
		cout << "\tType h for help\n";
	}
}