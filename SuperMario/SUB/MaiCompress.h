#ifndef MaiCompress_h
#define MaiCompress_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_mem.h"
#include "SUB/MaiLZ.h"
#include "SUB/MaiLLHeap.h"
#include "SUB/MaiSortingMgr.h"
#include "SUB/MaiBitWriter.h"

class MaiCompress
{
private:
	Heap_Alloc0 heap0;
	MaiCriticalSection mcs0;
public:
	MaiCompress();
	Mai_Status compress(Mai_I8 *src, Mai_I32 len_s, Mai_I8 *dst, Mai_I32 *len_d);
};

#endif
