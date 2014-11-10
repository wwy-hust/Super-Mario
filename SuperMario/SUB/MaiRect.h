#ifndef MaiRect_h
#define MaiRect_h

#include "SUB/Mai_All.h"

class MaiRect
{
public:
	Mai_I32 left;
	Mai_I32 top;
	Mai_I32 right;
	Mai_I32 bottom;
public:
	MaiRect();
	MaiRect(Mai_I32 l, Mai_I32 t, Mai_I32 r, Mai_I32 b);
	Mai_Status makeInner(MaiRect *mr0);
	Mai_I32 getWidth();
	Mai_I32 getHeight();
};

#endif