#include "cpu.h"

void CPU ::  ExST_Z(int info) // Stores reg value in zero page address		
{
	//  info contains reg enum in first 2 bits, and register offset enum in next 2 bits
	int reg = info & 3;      // gets register index
	int offset = (info & 0x0F) >> 2;  // gets index of register that will be added to address


	mem.WriteByte(AbsoluteAddress(offset, 0), this->Registers[reg], cycles);
}

void CPU::ExST_A(int info)    // Stores reg value in absolute address
{
	//  info contains reg enum in first 2 bits, and register offset enum in next 2 bits
	int reg = info & 3;      // gets register index
	int offset = (info & 0x0F) >> 2;  // gets index of register that will be added to address

	mem.WriteByte(AbsoluteAddress(offset, 1), this->Registers[reg], cycles); // Loads reg value into memory

}
void CPU::ExSTA_I(int reg)			// Indirect store
{				// reg is indirect index
	mem.WriteByte(IndirectAddress(reg), this->Registers[A], cycles);  // Value stored in effective address
}
