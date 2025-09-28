#include "cpu.h"

void CPU::UpdateA(int value, int op)			// Updates accumalator according to operation
{
	switch (op)
	{
	case ADD:
		if (this->Registers[A] + value > 0xFF) CF = 1;	// Carry flag
		this->Registers[A] += value;
		break;
	case SUB:
		if (this->Registers[A] - value > 0xFF) CF = 1;	// Carry flag
		this->Registers[A] -= value;
	}
	UpdateFlag(this->Registers[A]);      // Zero and sign flag
}
void CPU:: ExADC_I(int op)   // Add / Sub with carry immediate
{
	Byte value = Fetch();		// Immediate address
	UpdateA(value, op);     // Adds value to A

}
void CPU::ExADC_Z(int info)   // Add / Sub with carry Zero page
{
	//  info contains operation enum in first 2 bits, and register offset enum in next 2 bits
	int op = info & 3;      // gets op index
	int offset = (info & 0x0F) >> 2;  // gets index of register that will be added to address

	Byte value = mem.ReadByte(AbsoluteAddress(offset, 0), cycles);		// Gets value from zero page address
	UpdateA(value, op);     // Adds value to A

}

void CPU::ExADC_A(int info)		//ADC/SBC absolute
{

	//  info contains operation enum in first 2 bits, and register offset enum in next 2 bits
	int op = info & 3;      // gets op index
	int offset = (info & 0x0F) >> 2;  // gets index of register that will be added to address

	Byte value = mem.ReadByte(AbsoluteAddress(offset, 1), cycles);		// Gets value from zero page address
	UpdateA(value, op);     // Adds value to A
}

void CPU::ExADC_In(int info)			// Indirect ADC 
{
	//  info contains operation enum in first 2 bits, and register offset enum in next 2 bits
	int op = info & 3;      // gets op index
	int offset = (info & 0x0F) >> 2;  // gets register that is indirect index

	Byte value = mem.ReadByte(IndirectAddress(offset), cycles);   // Gets value from effective address
	UpdateA(value, op);     // Adds value to A
}

