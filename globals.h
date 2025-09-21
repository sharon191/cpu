#ifndef GLOBALS_H
#define GLOBALS_H

#include "Memory.h"
extern Memory mem;			// Memory
extern int cycles;
enum OPCODES {
	// Immediate      // Zero Page		X			// Absolute		X			Y			// Indirect X    Y
	LDA_I = 0xA9, LDA_Z = 0xA5, LDA_ZX = 0xB5, LDA_A = 0xAD	, LDA_AX = 0xBD, LDA_AY = 0xB9, LDA_IX = 0xA1, LDA_IY = 0xB1,			// LDA
	LDX_I = 0xA2, LDX_Z = 0xA6, LDX_ZY =0xB6,	LDX_A = 0xAE				, LDX_AY = 0xBE,			// LDX
	LDY_I = 0xA0, LDY_Z = 0xA4,	LDY_ZX = 0xB4,  LDY_A = 0xAC , LDY_AX = 0xBC					// LDY
};


#endif