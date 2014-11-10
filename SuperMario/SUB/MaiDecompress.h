#ifndef MaiDecompress_h
#define MaiDecompress_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_mem.h"
#include "SUB/MaiLZ.h"
#include "SUB/MaiLLHeap.h"
#include "SUB/MaiSortingMgr.h"
#include "SUB/MaiBitReader.h"

class MaiDecompress
{
private:
	Heap_Alloc0 heap0;
	MaiCriticalSection mcs0;
public:
	MaiDecompress();
	Mai_Status decompress(Mai_I8 *src, Mai_I32 len_s, Mai_I8 *dst, Mai_I32 *len_d);
};

#endif
