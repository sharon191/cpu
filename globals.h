#ifndef GLOBALS_H
#define GLOBALS_H

#include "Memory.h"
extern Memory mem;			// Memory
struct SystemBus {
	Word adr_bus;
	Byte data_bus;
	Bit ctrl_line;
};
extern SystemBus sys_bus;
extern int cycles;
enum OPCODES {
	// Immediate      // Zero Page		X			// Absolute		X			Y			// Indirect X    Y
	LDA_I = 0xA9, LDA_Z = 0xA5, LDA_ZX = 0xB5, LDA_A = 0xAD	, LDA_AX = 0xBD, LDA_AY = 0xB9, LDA_IX = 0xA1, LDA_IY = 0xB1,			// LDA
	LDX_I = 0xA2, LDX_Z = 0xA6, LDX_ZY =0xB6,	LDX_A = 0xAE				, LDX_AY = 0xBE,			// LDX								// Loading////
	LDY_I = 0xA0, LDY_Z = 0xA4,	LDY_ZX = 0xB4,  LDY_A = 0xAC , LDY_AX = 0xBC,					// LDY

		// Zero page	X/Y			// Absolute		X				Y		// Indirect		X		Y
	STA_Z = 0x85,	STA_ZX = 0x95,	STA_A = 0x8D, STA_AX = 0x9D, STA_AY = 0x99,	STA_IX = 0x81 , STA_IY = 0x91, // STA				///////Storing//////
	STX_Z = 0x86,	STX_ZY = 0x96,	STX_A = 0x8E,	// STX
	STY_Z = 0x84,	STY_ZX = 0x94, STY_A = 0x84,		// STY

		//Immediate		Zero page			X		Absolute	X				Y			Indirect X		Y
	ADC_I = 0x60, ADC_Z = 0x65, ADC_ZX = 0x75, ADC_A = 0x6D, ADC_AX = 0x7D, ADC_AY = 0x79, ADC_IX = 0x61, ADC_IY = 0x71,		// ADC 
	SBC_I = 0xE9, SBC_Z = 0xE5, SBC_ZX = 0xF5, SBC_A = 0xED, SBC_AX = 0xFD, SBC_AY = 0xF9, SBC_IX = 0xE1, SBC_IY = 0xF1,		// SBC 

};


#endif
