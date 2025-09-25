#include "cpu.h"



void CPU :: ExLD_I(int reg)       // Moves immediate value to register A
{
	Byte value = Fetch();		// Gets value
	this->Registers[reg] = value;
	UpdateFlag(value);

}
void CPU :: ExLD_Z(int reg)      // Lda Zero Page
{
	Byte address = Fetch();        // Zero page address
	Byte value = mem.ReadByte(address, cycles);    // Value from address
	this->Registers[reg] = value;
	UpdateFlag(value);

}

void CPU :: ExLD_ZX(int reg)   // Lda Zero Page X
{
	Byte address = Fetch();        // Zero page address
	if (reg == X) address += Y;		// In case of LDX you zero page with Y
	else address += X;       // Adds x to address
	cycles--;       // ALU takes cycle
	Byte value = mem.ReadByte(address,cycles);    // Value from address
	this->Registers[reg] = value;
	UpdateFlag(value);

}

void CPU :: ExLD_A(int info)   // Lda Absolute 
{
	//  info contains reg enum in first 2 bits, and register offset enum in next 2 bits
	int reg = info & 3;      // gets register index
	int offset = (info & 0x0F) >> 2;  // gets index of register that will be added to address
	Word address = Fetch(1);        // Gets 2 byte address
	if(offset) address += this->Registers[offset];
	Byte value = mem.ReadByte(address, cycles);    // Value from address
	this->Registers[reg] = value;
	UpdateFlag(value);

}
void CPU :: ExLDA_I(int reg)   // Lda Indirect
{

	Word address = Fetch();        // Gets low byte of address 
	if (reg == Y) address = mem.ReadWord(address, cycles);     // In case of indirect index (Y)->  the effective address is the value + y
	address += this->Registers[reg];    // Adds register to address if X or Y to
	cycles--;       // ALU takes cycle
	if(reg == X) address = mem.ReadWord(address, cycles);    // in case of indirect X-> Reads bytes of data to get effective address
	Byte value = mem.ReadByte(address, cycles);       // Value from effective address
	this->Registers[A] = value;
	UpdateFlag(value);

}

