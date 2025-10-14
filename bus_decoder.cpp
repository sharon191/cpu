#include "cpu.h"

Byte ReadByte(int adr, int& cycles)				// Reads byte from memory
{
	sys_bus.adr_bus = adr;	// address bus 
	sys_bus.ctrl_line = 1;	// control 1 -> read
	mem.Decode(cycles);
	return sys_bus.data_bus;
}
Word ReadWord(int adr, int& cycles)				// Reads word from memory
{
	return ReadByte(adr, cycles) + (ReadByte(adr + 1, cycles) << 8);

}
void WriteByte(int adr, Byte value, int& cycles)	// Writes byte to memory
{
	sys_bus.adr_bus = adr;		// address bus 
	sys_bus.data_bus = value;		// data bus
	sys_bus.ctrl_line = 0;		// control 0 -> write
	mem.Decode(cycles);
}
void WriteWord(int adr, Word value, int& cycles)		// Writes word to memory
{
	WriteByte(adr, value & 0x00FF, cycles);         // little endian
	WriteByte(adr + 1, value >> 8, cycles);
}