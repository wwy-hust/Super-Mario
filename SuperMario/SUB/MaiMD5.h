#ifndef MaiMD5_h
#define MaiMD5_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_mem.h"

class MaiMD5
{
private:
	Mai_I32 round_shift_table[0x40];
	Mai_U32 cons[0x40];

	Heap_Alloc0 heap0;
public:
	MaiMD5();
	Mai_Status calcCore(Mai_U32 *block_data, Mai_U32 *values);
	Mai_Status calcFromData(Mai_I8 *src, Mai_I32 len_s, Mai_U32 *rs);
};

#endif
