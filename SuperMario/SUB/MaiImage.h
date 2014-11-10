#ifndef MaiImage_h
#define MaiImage_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiCriticalSection.h"
#include "SUB/Mai_Math.h"
#include "SUB/Mai_mem.h"

class MaiImage
{
private:
	volatile struct
	{
		Mai_Bool is_ok;
		Mai_Bool is_out_image;
	} switcher;

	struct
	{
		Mai_I32* data;
		Mai_I32 width;
		Mai_I32 height;
		//Mai_I32 pitch;
		//Mai_I32 type;
	} bitmap;

	Heap_Alloc0 heap0;
	MaiCriticalSection mcs0;
private:
	//Mai_U8 Clip_base[256*3];
	//Mai_U8* Clip;


	//Mai_Bool fColorConvInitOK;
public:
	MaiImage(Mai_I32* ptr, Mai_I32 width, Mai_I32 height);
	MaiImage(Mai_I32 width, Mai_I32 height);
	~MaiImage();
	Mai_I32* getBitmapPointer();
	Mai_I32 getWidth();
	Mai_I32 getHeight();
	//Mai_I32 getType();
	//Mai_I32 getPitch();
	Mai_Status fillWith(Mai_I32 color);
	Mai_Status setAlpha(Mai_I32 alpha);
	//Mai_Status fad(Mai_I32_Fixed1 hodo);
	//Mai_Status BoxBlur(Mai_I32_Fixed1 hRadius, Mai_I32_Fixed1 vRadius, Mai_I32 iterations);
	Mai_Status shiftAlpha();
	Mai_Status shiftRGB();
	Mai_Status shift();
	Mai_I32 getPoint(Mai_I32_Fixed x, Mai_I32_Fixed y);
	Mai_Status resize(Mai_I32 width, Mai_I32 height);
	//Mai_Status whirl(Mai_I32_Fixed1 x, Mai_I32_Fixed1 y, Mai_I32_Fixed1 angle);
	//Mai_Status zwhirl(Mai_I32_Fixed1 angle);
	Mai_Status copyTo(MaiImage* dst);
	//Mai_Status convertTo(Mai_I32 type_dst);
	//Mai_Status mixToAVS(SubPicDesc* pTarget, Mai_I32 x, Mai_I32 y);
};

#endif