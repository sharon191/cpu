#include "cpu.h"
#include "Op_Handler.h"

void CPU::Execute()
{
	while (cycles > 0)           // clock ticks
	{
		ResetFlag();
		Byte opcode = Fetch();       // Instruction opcode
		Op_Func function = op_arr[opcode].func;    // gets appropriate opcode function pointer
		(this->*function)(op_arr[opcode].reg);
	}
}



int main()
{
	Fill_OpFunc();
	mem.Data[0x32] = 0x67;
	mem.Data[0x33] = 0x67;
	Byte code[] = { ADC_I, 30};
	int len = sizeof(code) / sizeof(Byte);
	cycles = CopyCode(code, len);
	CPU cpu;
	cpu.ResetReg();
	cpu.Registers[A] = 37;
	cpu.Execute();

	return 0;
}