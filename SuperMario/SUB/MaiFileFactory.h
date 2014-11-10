#ifndef MaiFileFactory_h
#define MaiFileFactory_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_mem.h"
#include "SUB/RandomAccessFile.h"
#include "SUB/MaiString.h"
#include "SUB/MaiCompress.h"

class MaiFileFactory
{
private:
	Heap_Alloc0 heap0;
public:
	Mai_Status encMaiFile(Mai_WChar *dst, Mai_WChar *src, Mai_I32 block_size);
};

#endif
