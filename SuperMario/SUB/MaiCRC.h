#ifndef MaiCRC_h
#define MaiCRC_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_Quene0.h"
#include "SUB/MaiBitReader.h"

class MaiCRC
{
private:
	volatile struct
	{
		Mai_I32 polynomial;
		Mai_I32 result;
	} info;

	Mai_I32 table[0x100];

	MaiCriticalSection mcs0;
public:
	MaiCRC();
	Mai_I32 calc(Mai_I32 crc0, Mai_I8 *src, Mai_I32 len_s);
};

#endif
