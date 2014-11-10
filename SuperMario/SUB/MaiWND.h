#ifndef MaiWND_h
#define MaiWND_h

#include "Mai_All.h"
#include "Heap_Alloc0.h"
#include "MaiCriticalSection.h"
#include "MaiString.h"
#include "MaiThread.h"


class MaiWND
{
public:
	WNDCLASSEX wc0;
protected:
	HINSTANCE hinstance;

	HWND hwnd0;

	Heap_Alloc0 heap0;

	Mai_I32 location_x;
	Mai_I32 location_y;
	Mai_I32 size_x;
	Mai_I32 size_y;

	Mai_WChar* classname;
	Mai_WChar* title;

	/*struct
	{
		MaiComponent** head;
		Mai_I32 num;
	} components;*/

	HDC hdc1;

	DWORD style;
	DWORD exstyle;
	MaiWND* parent;
	

	
	//MaiComponent* mouse_comp;
public:
	HCURSOR cursor_temp;
private:

public:
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	virtual Mai_Status doMouseEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	virtual Mai_Status doKeyEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	virtual Mai_Status doPaintEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	virtual Mai_Status doResizeEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	MaiWND(MaiWND* parent = NULL, DWORD exstyle = 0, DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU);
	Mai_Status init(MaiWND* parent, DWORD exstyle, DWORD style);
	Mai_Status setBGColor(Mai_I32 color);
	Mai_Status setLocation(Mai_I32 x, Mai_I32 y);
	Mai_Status setSize(Mai_I32 width, Mai_I32 height);
	Mai_Status setTitle(WCHAR* title);
	virtual Mai_Status show();
	//Mai_Status addComponent(MaiComponent* mc);
	//Mai_Status delComponent(MaiComponent* mc);
	HWND getHWND();
	static Mai_Status MessageLoop();
	
};


#endif

