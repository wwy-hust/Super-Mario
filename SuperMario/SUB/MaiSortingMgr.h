#ifndef MaiSortingMgr_h
#define MaiSortingMgr_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"

typedef struct _MaiSortingMgrAtom
{
	Mai_Void *ptr0;
	Mai_I32 value;
} MaiSortingMgrAtom;

class MaiSortingMgr
{
private:
	volatile struct
	{
		MaiSortingMgrAtom *head;
		Mai_I32 n;
		Mai_I32 num;
		Mai_I32 reserved0;
	} atoms;

	Heap_Alloc0 heap0;
	MaiCriticalSection mcs0;
public:
	MaiSortingMgr(Mai_I32 max_atom_num);
	~MaiSortingMgr();
	Mai_Status addAtom(Mai_Void *ptr0, Mai_I32 value);
	Mai_Status getPrtArray(Mai_Void **pptr, Mai_I32 *pn);
	Mai_Status getValueArray(Mai_I32 *pvalue, Mai_I32 *pn);
	Mai_Status sort();
};

#endif
