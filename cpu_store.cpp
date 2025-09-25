#include "cpu.h"

void CPU ::  ExST_Z(int info) // Stores reg value in zero page address		
{
	//  info contains reg enum in first 2 bits, and register offset enum in next 2 bits
	int reg = info & 3;      // gets register index
	int offset = (info & 0x0F) >> 2;  // gets index of register that will be added to address

	Byte address = Fetch();      // Gets zero page address
	if (offset) {
		address += this->Registers[offset];		// In case of zero page X / Y the register will be added to the base address
		cycles--;
	}
	mem.WriteByte(address, this->Registers[reg], cycles);
}

void CPU::ExST_A(int info)    // Stores reg value in absolute address
{
	//  info contains reg enum in first 2 bits, and register offset enum in next 2 bits
	int reg = info & 3;      // gets register index
	int offset = (info & 0x0F) >> 2;  // gets index of register that will be added to address

	Word address = Fetch(1);	//Gets word address
	if (offset)
	{
		address += this->Registers[offset];		// In case of absolute X / Y adds register to address
		cycles--;
	}
	mem.WriteByte(address, this->Registers[reg], cycles); // Loads reg value into memory

}
void CPU::ExSTA_I(int reg)			// Indirect store
{
	Word address = Fetch();        // Gets low byte of address 
	if (reg == Y) address = mem.ReadWord(address, cycles);     // In case of indirect index (Y)->  the effective address is the value + y
	address += this->Registers[reg];    // Adds register to address if X or Y to
	cycles--;       // ALU takes cycle
	if (reg == X) address = mem.ReadWord(address, cycles);    // in case of indirect X-> Reads bytes of data to get effective address
	mem.WriteByte(address, this->Registers[A], cycles);  // Value stored in effective address
}
