#ifndef MEMORY_H
#define MEMORY_H

typedef unsigned char Byte;
typedef unsigned short int Word;
typedef bool Bit;

using namespace std;
extern void AddressError();
extern void CycleError();


struct Memory
{
	Byte Data[256 * 256];
	void Decode(int& cycles);
	//Byte ReadByte(int adr, int& cycles);
	//Word ReadWord(int adr, int& cycles);
	//void WriteByte(int adr, Byte value, int& cycles);
	//void WriteWord(int adr, Word value, int& cycles);

};

#endif