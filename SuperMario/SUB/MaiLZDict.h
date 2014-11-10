#ifndef MaiLZDict_h
#define MaiLZDict_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_mem.h"

typedef struct _MaiLZDictNode
{
	Mai_I32 hash;
	Mai_I32 off;
	struct _MaiLZDictNode *pre;
	struct _MaiLZDictNode *next;
} MaiLZDictNode;

class MaiLZDict
{
private:
	volatile struct
	{
		//Mai_I32 dict_size;
		Mai_I32 bit_len;
		Mai_I32 min_match_len;
	} info;

	struct
	{
		MaiLZDictNode **head;
		Mai_I32 *counter;
		Mai_I32 num;
	} table;

	struct
	{
		MaiLZDictNode *head;
		Mai_I32 n;
		Mai_I32 num;
		Mai_Bool is_over;
	} nodes;

	Mai_I8 change_table[0x100];

	MaiCriticalSection mcs0;

	Heap_Alloc0 heap0;

public:
	MaiLZDict(Mai_I32 dict_size, Mai_I32 min_match_len);
	~MaiLZDict();
	Mai_I32 getHash(Mai_I8 *src);
	Mai_Status add(Mai_I8 *src, Mai_I32 off);
	Mai_Status search(Mai_I8 *src, Mai_I32 *offs, Mai_I32 *num_of_offs);
	Mai_Status search(Mai_I32 hash, Mai_I32 *offs, Mai_I32 *num_of_offs);
	Mai_I32 getNumOfOffs(Mai_I8 *src);
	Mai_I32 getNumOfOffs(Mai_I32 hash);
};

#endif
