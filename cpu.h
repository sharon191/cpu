#ifndef CPU_H
#define CPU_H
#include "globals.h"
#include <iostream>

typedef uint8_t Byte;
typedef uint16_t Word;

enum Registers { A, X, Y, SP };// Addressing registers X Y
enum ops { ADD, SUB };	// Arithmetic operations

      // Accumilator      // Stack Pointer
using namespace std;

extern Byte ReadByte(int adr, int& cycles);
extern Word ReadWord(int adr, int& cycles);						// Decoding processor bus
extern void WriteByte(int adr, Byte value, int& cycles);
extern void WriteWord(int adr, Word value, int& cycles);
struct CPU {
	Byte Registers[4]; 
	Word PC;      // Program Counter
	union {
		Byte flag_reg;
		struct {
			unsigned int CF : 1;			// Carry
			unsigned int Z : 1;				// Zero
			unsigned int I : 1;				// Interrupt Disable
			unsigned int D : 1;       // Decimal Mode
			unsigned int B : 1;		// Break
			unsigned int : 1;
			unsigned int O : 1;				// Overflow
			unsigned int N : 1;				// Negative

		};
	};
	Word Fetch(bool w_flag =0 );          // Reads next byte from program counter and updates register
	Word IndirectAddress(int offset);			// Indirect index access to memory
	Word AbsoluteAddress(int offset, int flag);	// Absolute address, flag for zero page and reg offset if exists		// misc
	int ReturnCycles(int opcode);      // Returns number of cycles for opcode
	int CopyCode(Byte* code, int len);         // Copies machine code to 0x200 returns number of cycles
	void UpdateFlag(Byte value);     // Updates flag register based on value

	void ExLD_I(int reg);       // Moves immediate value to register A
	void ExLD_Z(int info);      // Lda Zero Page
	void ExLD_A(int info);   // Lda Absolute										Load value
	void ExLDA_I(int reg);   // Lda Indirect

	void ExST_Z(int info); // Stores reg value in zero page address						// Storing values
	void ExST_A(int info);    // Stores reg value in absolute address
	void ExSTA_I(int reg);   // Sta Indirect
																					// ADC / SBC
	void UpdateA(int value, int op); // Updates accumalator and zero flags, according to value and op
	void ExADC_I(int op);   // Add / Sub with carry immediate,		// Addition updates accumalator and updates carry, zero and sign flag 
	void ExADC_Z(int info);		// ADC / SBC zero page
	void ExADC_A(int info);		// Absolute					** first 2 bits contain op and second 2 bits contain offest if exists
	void ExADC_In(int info);			// Adc Indirect

	void Execute();		// Executes machine code
	void ResetFlag();	// Resets flag register
	void ResetReg();   // Resets registers at the beginning of run








};

//extern int ReturnCycles(int opcode);      // Returns number of cycles for opcode
extern int CopyCode(Byte* code, int len);         // Copies machine code to 0x200 returns number of cycles


#endif