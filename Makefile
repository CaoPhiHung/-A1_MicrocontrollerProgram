CXXFLAGS = -Wall -g

APP = main
OBJS = Microcontroller.o MopsR500.o MacrochipPIC32F42.o Rotamola34HC22.o MicrocontrollerFactory.o

.PHONY: all
all: $(APP)

$(APP): $(OBJS)
Microcontroller.o: Microcontroller.h
MopsR500.o: MopsR500.h Microcontroller.h
MacrochipPIC32F42.o: MacrochipPIC32F42.h Microcontroller.h
Rotamola34HC22.o: Rotamola34HC22.h   Microcontroller.h
MicrocontrollerFactory.o: MicrocontrollerFactory.h MopsR500.h MacrochipPIC32F42.h Rotamola34HC22.h

.PHONY: clean
clean:
	$(RM) *.o *~ a.out core $(APP)

