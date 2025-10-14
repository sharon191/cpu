#include "cpu.h"



void CPU :: ExLD_I(int reg)       // Moves immediate value to register A
{
	Byte value = Fetch();		// Gets value
	this->Registers[reg] = value;
	UpdateFlag(value);

}
void CPU :: ExLD_Z(int info)      // Lda Zero Page
{
	int reg = info & 3;      // gets register index
	int offset = (info & 0x0F) >> 2;  // gets index of register that will be added to address

	Byte value = ReadByte(AbsoluteAddress(offset, 0), cycles);    // Value from address
	this->Registers[reg] = value;
	UpdateFlag(value);

}


void CPU :: ExLD_A(int info)   // Lda Absolute 
{
	//  info contains reg enum in first 2 bits, and register offset enum in next 2 bits
	int reg = info & 3;      // gets register index
	int offset = (info & 0x0F) >> 2;  // gets index of register that will be added to address
	
	Byte value = ReadByte(AbsoluteAddress(offset, 1), cycles);    // Value from address
	this->Registers[reg] = value;
	UpdateFlag(value);

}
void CPU :: ExLDA_I(int reg)   // Lda Indirect
{
	// reg is indirect index
	Byte value = ReadByte(IndirectAddress(reg), cycles);       // Value from effective address
	this->Registers[A] = value;
	UpdateFlag(value);

}

