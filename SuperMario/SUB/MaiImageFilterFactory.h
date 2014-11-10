#ifndef MaiImageFilterFactory_h
#define MaiImageFilterFactory_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_Math.h"
#include "SUB/Mai_mem.h"
#include "SUB/MaiRect.h"
#include "SUB/MaiImage.h"

class MaiImageFilterFactory
{
private:
	Heap_Alloc0 heap0;
public:
	MaiImageFilterFactory();
	~MaiImageFilterFactory();
	Mai_Status fad(MaiImage *src, Mai_I32_Fixed1 hodo);
	Mai_Status BoxBlurHVEx(MaiImage *src, Mai_I32 hR, Mai_I32 vR, MaiRect *mr0);
	Mai_Status BoxBlurHV(MaiImage *src, Mai_I32 hR, Mai_I32 vR);
	static Mai_I32 mixPoint(Mai_I32 src0, Mai_I32 src1);
	static Mai_Status mixEx(MaiImage* i_dst, MaiImage* i_src0, MaiImage* i_src1, Mai_I32 i_x, Mai_I32 i_y);
	static Mai_Status mix(MaiImage* i_dst, MaiImage* i_src0, MaiImage* i_src1);
	static Mai_Status mixSEx(MaiImage* i_dst, MaiImage* i_src0, MaiImage* i_src1, Mai_I32 i_x, Mai_I32 i_y);
	static Mai_Status mixS(MaiImage* i_dst, MaiImage* i_src0, MaiImage* i_src1);
	Mai_Status shineCore(MaiImage *src, Mai_I32_Fixed1 r, Mai_I32 color_in, Mai_I32 color_out, Mai_I32 method = 0);
	Mai_Status whirl(MaiImage *src, Mai_I32_Fixed1 x, Mai_I32_Fixed1 y, Mai_I32_Fixed1 angle);
	Mai_Status ywhirl(MaiImage *src, Mai_I32_Fixed1 x, Mai_I32_Fixed1 angle);
	static Mai_I32 GCC(Mai_I32 color1, Mai_I32 color2, Mai_I32_Fixed hodo);
	static Mai_I32 calcColorFromTwoColorsWithBlackWhiteBackGround(Mai_I32 color_with_black_ground, Mai_I32 color_with_white_ground);
};

#endif
