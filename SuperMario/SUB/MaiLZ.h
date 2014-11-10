#ifndef MaiLZ_h
#define MaiLZ_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_mem.h"
#include "SUB/MaiLZDict.h"

#define MaiLZAtomTypeRemain 0
#define MaiLZAtomTypeCopy 1

typedef struct
{
	Mai_I32 type;
	Mai_I32 data;
	Mai_I32 base;
	Mai_I32 copy_off;
	Mai_I32 copy_len;
} MaiLZAtom;

class MaiLZ
{
private:
	volatile struct
	{
		Mai_Bool is_lzh;
		Mai_I32 copy_off_min;
		Mai_I32 copy_off_max;
		Mai_I32 copy_len_min;
		Mai_I32 copy_len_max;
	} info;

	struct
	{
		MaiLZAtom *head;
		Mai_I32 n;
		Mai_I32 num;
	} atoms;

	Heap_Alloc0 heap0;
	MaiCriticalSection mcs0;

private:
	Mai_I32 cmp(Mai_I8* src0, Mai_I8* src1, Mai_I32 max_num);
	Mai_I32 findSame(Mai_I8 *src, Mai_I32 max);
public:
	MaiLZ();
	~MaiLZ();
	Mai_Status setCopyOff(Mai_I32 min, Mai_I32 max);
	Mai_Status setCopyLen(Mai_I32 min, Mai_I32 max);
	Mai_Status compress(Mai_I8 *src, Mai_I32 len_s, MaiLZAtom **dst, Mai_I32 *len_d);
	Mai_Status enableLZH(Mai_Bool is_lzh);
};

#endif