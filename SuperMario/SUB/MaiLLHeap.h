#ifndef MaiLLHeap_h
#define MaiLLHeap_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"

#define MaiLLHeapTypeLittle 0
#define MaiLLHeapTypeLarge 1

typedef struct _MaiLLHeapAtom
{
	Mai_Void *ptr0;
	Mai_I32 value;
} MaiLLHeapAtom;

class MaiLLHeap
{
private:
	volatile struct
	{
		MaiLLHeapAtom *head;
		Mai_I32 n;
		Mai_I32 num;
		Mai_I32 reserved0;
	} atoms;

	Heap_Alloc0 heap0;
	MaiCriticalSection mcs0;

	Mai_I32 type;
private:
	Mai_I32 LevelUp(Mai_I32 lab0);
	Mai_I32 LevelDown(Mai_I32 lab0);
public:
	MaiLLHeap(Mai_I32 max_atom_num, Mai_I32 heap_type = MaiLLHeapTypeLittle);
	~MaiLLHeap();
	Mai_Status addAtom(Mai_Void *ptr0, Mai_I32 value);
	Mai_Status getTopAtom(Mai_Void **pptr0, Mai_I32 *pvalue, Mai_Bool get_and_del_from_heap = 1);
};

#endif
