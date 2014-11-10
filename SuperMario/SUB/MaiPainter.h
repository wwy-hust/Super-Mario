#ifndef MaiPainter_h
#define MaiPainter_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_Math.h"
#include "SUB/Mai_mem.h"
#include "SUB/MaiRect.h"
#include "SUB/MaiImage.h"
#include "SUB/MaiImageFilterFactory.h"
#include "SUB/MaiPath.h"

class MaiPainter
{
private:
	Heap_Alloc0 heap0;
public:
	Mai_Status drawPoint(MaiImage *src, Mai_I32_Fixed x, Mai_I32_Fixed y, Mai_I32 color, Mai_I32 method = 0);
	Mai_Status drawCubicEx(MaiImage *src, double *points, double param, double param_len, double r_in, double r_out, Mai_I32 color_in, Mai_I32 color_out, Mai_I32 alpha_in, Mai_I32 alpha_out, MaiRect *mr0 = 0);
};

#endif