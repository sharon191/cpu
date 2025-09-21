#include "cpu.h"
#include "Op_Handler.h"

void CPU::Execute()
{
	while (cycles > 0)           // Clock tick
	{
		ResetFlag();
		Byte opcode = Fetch();       // Instruction opcode
		Op_Func function = op_arr[opcode].func;    // gets appropriate opcode function pointer
		(this->*function)(op_arr[opcode].reg);
		//switch (opcode) {
		//case LDA_I:
		//	ExLD_I(A);
		//	break;
		//case LDX_I:				// Immediate
		//	ExLD_I(X);
		//	break;
		//case LDY_I:
		//	ExLD_I(Y);
		//	break;


		//case LDA_Z:
		//	ExLD_Z(A);
		//	break;
		//case LDX_Z:				// Zero page
		//	ExLD_Z(X);
		//	break;
		//case LDY_Z:
		//	ExLD_Z(Y);
		//	break;

		//case LDA_ZX:
		//	ExLD_ZX(A);
		//	break;
		//case LDX_ZY:
		//	ExLD_ZX(X);		// Zero page, x / y
		//	break;
		//case LDY_ZX:
		//	ExLD_ZX(Y);
		//	break;

		//case LDA_A:
		//	ExLD_A(A);
		//	break;
		//case LDX_A:				// Absolute
		//	ExLD_A(X);
		//	break;
		//case LDY_A:
		//	ExLD_A(Y);
		//	break;

		//case LDA_AX:
		//	ExLD_A(A + (X << 2));			// Absolute, x
		//	break;
		//case LDY_AX:
		//	ExLD_A(Y + (X << 2));
		//	break;

		//case LDA_AY:
		//	ExLD_A(A + (Y << 2));			//Absolute, y
		//	break;
		//case LDX_AY:
		//	ExLD_A(X + (Y << 2));
		//	break;

		//case LDA_IX:
		//	ExLDA_I(X);			// Indirect
		//	break;
		//case LDA_IY:
		//	ExLDA_I(Y);
		//	break;
		//default:
		//	cerr << "Illegal opcode " << (int)opcode;
		//	exit(1);
		//}
	}
}



int main()
{
	Fill_OpFunc();
	mem.Data[0x70] = 0x30;
	mem.Data[0x35] = 67;
	Byte code[] = { LDX_I, 0x70 };
	int len = sizeof(code) / sizeof(Byte);
	cycles = CopyCode(code, len);
	CPU cpu;
	cpu.ResetReg();
	cpu.Registers[Y] = 5;

	cpu.Execute();
	return 0;
}