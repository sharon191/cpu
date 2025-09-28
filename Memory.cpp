#include "Memory.h"
#include <iostream>


void CycleError()
{
	cerr << "Cycles error"; exit(1);
}
void AddressError()
{
	cerr << "Error: Address overflow"; exit(1);

}

Byte Memory :: ReadByte(int adr, int& cycles)				// Reads byte from memory
	{
		if (adr > 0xFFFF) AddressError();
		if (cycles < 1) CycleError();
		cycles -= 1;
		return Data[adr];
	}
Word Memory :: ReadWord(int adr, int& cycles)				// Reads word from memory
	{
		if (adr > 0xFFFE) AddressError();
		if (cycles < 2) CycleError();
		cycles -= 2;
		return Data[adr] + (Data[adr + 1] << 8);

	}
void Memory :: WriteByte(int adr, Byte value, int& cycles)	// Writes byte to memory
	{
		if (adr > 0xFFFF) AddressError();
		if (cycles < 1) CycleError();
		cycles -= 1;
		Data[adr] = value;
	}
void Memory ::  WriteWord(int adr, Word value, int& cycles)		// Writes word to memory
	{
		if (adr > 0xFFFE) AddressError();
		if (cycles < 2) CycleError();

		WriteByte(adr, value & 0x00FF, cycles);         // little endian
		WriteByte(adr + 1, value >> 8, cycles);
	}
