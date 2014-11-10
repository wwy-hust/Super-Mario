#ifndef Mai_Math_h
#define Mai_Math_h

#include "SUB/Mai_All.h"

class Mai_Math
{
public:
public:
	static Mai_I32_Fixed1 getPi();
	static Mai_I32_Fixed1 get2Pi();
	static Mai_I32_Fixed1 getE();
public:
	static Mai_I32_Fixed1 mul(Mai_I32_Fixed1 inArg0, Mai_I32_Fixed1 inArg1);

	static Mai_I32_Fixed mul8(Mai_I32_Fixed in0, Mai_I32_Fixed in1);

	static Mai_I32_Fixed1 sqrt(Mai_I32_Fixed1 in);
	static Mai_I32_Fixed1 sqrt(Mai_I64_Fixed1 in);
	static Mai_I32_Fixed1 sin(Mai_I32_Fixed1 inAngle);
	static Mai_I32_Fixed1 cos(Mai_I32_Fixed1 inAngle);

	static Mai_I32_Fixed1 calcDis(Mai_I32_Fixed1 x0, Mai_I32_Fixed1 y0, Mai_I32_Fixed x1, Mai_I32_Fixed y1);
};

#endif
