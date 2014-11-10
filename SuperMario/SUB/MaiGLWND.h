#ifndef MaiGLWND_h
#define MaiGLWND_h

#include "Mai_All.h"
#include "Heap_Alloc0.h"
#include "MaiCriticalSection.h"
#include "MaiString.h"
#include "MaiWND.h"

#include <gl/gl.h>
#include <gl/glu.h>
//#include <gl/glaux.h>

class MaiGLWND : public MaiWND
{
public:
	HDC hdcgl;
	HGLRC hrc;
public:
	MaiGLWND(MaiWND* parent = NULL, DWORD exstyle = 0, DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU);
	Mai_Status doPaintEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	Mai_Status show();
	virtual Mai_Status initGL() = 0;
	virtual Mai_Status paintGL() = 0;
};

#endif
