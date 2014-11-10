#ifndef MaiPath_h
#define MaiPath_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/Mai_Math.h"

class MaiCubic
{
private:
	double base_points[8];
	double cc[4];
public:
	MaiCubic();
	MaiCubic(double *points);
	Mai_Status setBasePoints(double *points);
	Mai_Status PreCalc();
	Mai_Status getPoint(double *ppoint, double Param);
	double calcParamUnderDis(double dis);
};

#endif