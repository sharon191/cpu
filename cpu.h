#ifndef CPU_H
#define CPU_H
#include "globals.h"
#include <iostream>

typedef uint8_t Byte;
typedef uint16_t Word;

enum Registers { A, X, Y, SP };// Addressing registers X Y
      // Accumilator      // Stack Pointer
using namespace std;

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
	int ReturnCycles(int opcode);      // Returns number of cycles for opcode
	int CopyCode(Byte* code, int len);         // Copies machine code to 0x200 returns number of cycles
	void UpdateFlag(Byte value);     // Updates flag register based on value

	void ExLD_I(int reg);       // Moves immediate value to register A
	void ExLD_Z(int reg);      // Lda Zero Page
	void ExLD_ZX(int reg);   // Lda Zero Page X
	void ExLD_A(int info);   // Lda Absolute										Load value
	void ExLDA_I(int reg);   // Lda Indirect



	void Execute();		// Executes machine code
	void ResetFlag();	// Resets flag register
	void ResetReg();   // Resets registers at the beginning of run








};

//extern int ReturnCycles(int opcode);      // Returns number of cycles for opcode
extern int CopyCode(Byte* code, int len);         // Copies machine code to 0x200 returns number of cycles


//void ALU(int op, Byte& operand1, Byte& operand2)
	//{
	//	cycles--;
	//	switch (op) 
	//	{
	//	case ADD:
	//		operand1 += operand2;
	//		break;
	//	case SUB:
	//		operand1 -= operand2;
	//		break;
	//	case MUL:
	//		operand1 *= operand2;
	//		break;
	//	case DIV:
	//		operand1 /= operand2;
	//		break;
	//	case NOT:
	//		operand1 = ~operand1;
	//		break;
	//	case OR:
	//		operand1 |= operand2;
	//		break;
	//	case AND:
	//		operand1 &= operand2;
	//		break;
	//	case XOR:
	//		operand1 ^= operand2;
	//		break;
	//	case SHR:
	//		operand1 >>= operand2;
	//		break;
	//	case SHL:
	//		operand1 <<= operand2;
	//		break;

	//	default:
	//		cerr << "ALU Error";
	//		exit(1);
	//	};
	//}
#endif