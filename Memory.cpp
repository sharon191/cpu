#include "Memory.h"
#include <iostream>
#include "globals.h"

void CycleError()
{
	cerr << "Cycles error"; exit(1);
}
void AddressError()
{
	cerr << "Error: Address overflow"; exit(1);

}

void Memory::Decode(int& cycles)
{
	if (sys_bus.adr_bus > 0xFFFF) AddressError();
	if (cycles < 1) CycleError();
	cycles--;
	if (sys_bus.ctrl_line)	// read from memory
	{
		sys_bus.data_bus = Data[sys_bus.adr_bus];
	}
	else {		// writes to memory
		Data[sys_bus.adr_bus] = sys_bus.data_bus;
	}
}
