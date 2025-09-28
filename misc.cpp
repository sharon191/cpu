#include "cpu.h"
#include "Op_Handler.h"

Op_Instruction op_arr[0x100];      // array for opcode instructions

void CPU::ResetFlag()
{
	flag_reg = 0;
}
void CPU::ResetReg()
{
	for (int i = 0; i < 4; i++) this->Registers[i] = 0;
	PC = 0x200;        // Resets Stack Pointer and Program Counter
	ResetFlag();
}
int CopyCode(Byte* code, int len)         // Copies machine code to 0x200 returns number of cycles
{
	int cycles = 0, flag = 0;
	for (int i = 0; i < len; i++)
	{
		mem.Data[0x200 + i] = code[i];
		if (flag == 0) // if byte is instruction opcode
		{
			if (!op_arr[code[i]].func)
			{
				cerr << "Error: Illegal opcode" << (int)code[i];
				exit(1);
			}
			if (op_arr[code[i]].func == &CPU::ExLD_A || op_arr[code[i]].func == &CPU::ExST_A || op_arr[code[i]].func == &CPU::ExADC_A)		// Absolute load / store takes 2 bytes
				flag = 2;     // next 2 bytes are non instruction
			else flag = 1;   // next byte is non instruction opcode
			cycles += op_arr[code[i]].cycle;  // gets opcode cycle
		}
		else flag--;
	}
	return cycles;
}


Word CPU::Fetch(bool w_flag)          // Reads next byte from program counter and updates register
// flag for fetching word, default is byte
{
	Word instruction;
	if (!w_flag)
	{
		instruction = mem.ReadByte(PC, cycles);          // Byte instruction
		PC++;
	}
	else {
		instruction = mem.ReadWord(PC, cycles);       // Word instruction
		PC += 2;
	}
	return instruction;

}
Word CPU::IndirectAddress(int offset)
{
	Word address = Fetch();        // Gets low byte of address 
	if (offset == Y) address = mem.ReadWord(address, cycles);     // In case of indirect index (Y)->  the effective address is the value + y
	address += this->Registers[offset];    // Adds register to address if X or Y to
	cycles--;       // ALU takes cycle
	if (offset == X) address = mem.ReadWord(address, cycles);    // in case of indirect X-> Reads bytes of data to get effective address
	return address; // Returns final effective address
}
Word CPU::AbsoluteAddress(int offset, int flag)	// Absolute address, flag for zero page and reg offset if exists	
{
	Word address = Fetch(flag);	//Gets word / byte address according to flag
	if (offset)
	{
		address += this->Registers[offset];		// In case of absolute X / Y adds register to address
		cycles--;
	}
	return address;
}
void CPU::UpdateFlag(Byte value)
{
	if (value == 0) Z = 1;     // Updates Zero flag
	if (value >> 7 == 1) N = 1;       // Updates sign flag
}

void Fill_OpFunc()
{
	op_arr[LDA_I] = {A, 2, &CPU:: ExLD_I};
	op_arr[LDX_I] = {X, 2,  &CPU::ExLD_I };       // Immediate Loading
	op_arr[LDY_I] = {Y, 2,  &CPU::ExLD_I };

	op_arr[LDA_Z] = { A, 3, &CPU::ExLD_Z };			// Zero Page
	op_arr[LDX_Z] = { X, 3, &CPU::ExLD_Z };
	op_arr[LDY_Z] = { Y, 3, &CPU::ExLD_Z };

	op_arr[LDA_ZX] = { A + (X << 2), 4, &CPU::ExLD_Z };			// Zero Page offset						////////// Loading //////////////
	op_arr[LDX_ZY] = { X + (Y << 2), 4, &CPU::ExLD_Z };
	op_arr[LDY_ZX] = { Y + (X << 2), 4, &CPU::ExLD_Z };

	op_arr[LDA_A] = { A, 4, &CPU::ExLD_A };				// Absolute
	op_arr[LDX_A] = { X, 4, &CPU::ExLD_A };
	op_arr[LDY_A] = { Y, 4, &CPU::ExLD_A };

	op_arr[LDA_AX] = { A + (X << 2), 4, &CPU::ExLD_A };				// Absolute offset
	op_arr[LDA_AY] = { A + (Y << 2), 4, &CPU::ExLD_A };
	op_arr[LDX_AY] = { X + (Y << 2), 4, &CPU::ExLD_A};
	op_arr[LDY_AX] = { Y + (X << 2), 4, &CPU::ExLD_A};

	op_arr[LDA_IX] = { X, 6, &CPU::ExLDA_I };				// Indirect
	op_arr[LDA_IY] = { Y, 6, &CPU::ExLDA_I };



	op_arr[STA_Z] = { A, 3, &CPU::ExST_Z };			// Zero page		 //////// Storing /////////////////
	op_arr[STX_Z] = { X, 3, &CPU::ExST_Z };
	op_arr[STY_Z] = { Y, 3, &CPU::ExST_Z };

	op_arr[STA_ZX] = { A + (X << 2), 4, &CPU::ExST_Z };     // Zero page X / Y
	op_arr[STX_ZY] = { X + (Y << 2), 4, &CPU::ExST_Z };
	op_arr[STY_ZX] = { Y + (X << 2), 4, &CPU::ExST_Z };

	op_arr[STA_A] = { A, 4, &CPU::ExST_A };     // Absolute
	op_arr[STX_A] = { X, 4, &CPU::ExST_A };
	op_arr[STY_A] = { Y, 4, &CPU::ExST_A };
	op_arr[STA_AX] = { A + (X << 2), 5, &CPU::ExST_A};			// X
	op_arr[STA_AY] = { A  + (Y << 2), 5, &CPU::ExST_A};			// Y

	op_arr[STA_IX] = { X, 6, &CPU::ExSTA_I };				// Indirect
	op_arr[STA_IY] = { Y, 6, &CPU::ExSTA_I };

																						///Arithmetic/////////////
	op_arr[ADC_I] = { ADD, 2, &CPU::ExADC_I };	// Immediate			// Add with carry
	op_arr[ADC_Z] = { ADD, 3, &CPU::ExADC_Z };	// Zero page
	op_arr[ADC_ZX] = { ADD + (X << 2), 4, &CPU::ExADC_Z };	// X
	op_arr[ADC_A] = { ADD, 4, &CPU::ExADC_A };	// Absolute
	op_arr[ADC_AX] = { ADD + (X << 2), 5, &CPU::ExADC_A };	// X	
	op_arr[ADC_AY] = { ADD + (Y << 2), 5, &CPU::ExADC_A };	// Y	
	op_arr[ADC_IX] = { ADD + (X << 2), 6, &CPU::ExADC_In};	// Immediate	
	op_arr[ADC_IY] = { ADD + (Y << 2), 6, &CPU::ExADC_In };	// Immediate	

	op_arr[SBC_I] = { SUB, 2, &CPU::ExADC_I };	// Immediate			// Sub with carry
	op_arr[SBC_Z] = { SUB, 3, &CPU::ExADC_Z };	// Zero page
	op_arr[SBC_ZX] = { SUB + (X << 2), 4, &CPU::ExADC_Z};	// X
	op_arr[SBC_A] = { SUB, 4, &CPU::ExADC_A };	// Absolute
	op_arr[SBC_AX] = { SUB + (X << 2), 5, &CPU::ExADC_A };	// X	
	op_arr[SBC_AY] = { SUB + (Y << 2), 5, &CPU::ExADC_A };	// Y	
	op_arr[SBC_IX] = { SUB + (X << 2), 6, &CPU::ExADC_In };	// Immediate	
	op_arr[SBC_IY] = { SUB + (Y << 2), 6, &CPU::ExADC_In };	// Immediate	
}