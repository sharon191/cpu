#include "cpu.h"
typedef void (CPU::* Op_Func)(int);

struct Op_Instruction {		// holds information regarding opcode
	int reg;    // register to be passed into function
	int cycle;      // number of cycles for opcode
	Op_Func func;       //      opcode function pointer
};

extern struct Op_Instruction op_arr[0x100];     
extern void Fill_OpFunc();        // Defines opcode handler function pointer array