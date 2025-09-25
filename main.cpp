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
	}
}



int main()
{
	Fill_OpFunc();
	Byte code[] = { STA_AY, 0x30, 0x12 };
	int len = sizeof(code) / sizeof(Byte);
	cycles = CopyCode(code, len);
	CPU cpu;
	cpu.ResetReg();
	cpu.Registers[Y] = 4;
	cpu.Registers[A] = 67;
	cpu.Execute();
	cout << (int)mem.Data[0x1234];

	return 0;
}