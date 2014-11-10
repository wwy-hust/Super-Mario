/* GUI LIB */
#include "SUB/Mai_GUI/MaiProcess.h"

#include <gdiplus.h>
using namespace Gdiplus;



typedef struct _MaiWPParam
{
	_MaiWPParam(HWND _hwnd, UINT _message, WPARAM _wparam, LPARAM _lparam) : 
hwnd(_hwnd), message(_message), wparam(_wparam), lparam(_lparam) {};
	HWND hwnd;
	UINT message;
	WPARAM wparam;
	LPARAM lparam;
} MaiWPParam;

/* MaiMouseListener */
class MaiMouseListener
{
public:
	virtual Mai_Status LBottonDown(MaiWPParam* param);
	virtual Mai_Status LBottonUp(MaiWPParam* param);
	virtual Mai_Status RBottonDown(MaiWPParam* param);
	virtual Mai_Status RBottonUp(MaiWPParam* param);
};

/* MaiComponent */
class MaiComponent
{
protected:
	Mai_I32 location_x;
	Mai_I32 location_y;
	Mai_I32 size_x;
	Mai_I32 size_y;

	Mai_Image* show_buffer;
	Mai_Graphics* show_buffer_g;
	Mai_I32 bgcolor;

	MaiMouseListener* mml0;

	Mai_Void* father_frame;

	Heap_Alloc0 heap0;
public:
	MaiComponent();
	virtual Mai_Status paint(Mai_Image* buffer) = 0;
	virtual Mai_Status repaint();
	Mai_Status setLocation(Mai_I32 x, Mai_I32 y);
	Mai_Status setSize(Mai_I32 width, Mai_I32 height);
	Mai_Bool isIn(Mai_I32 x, Mai_I32 y);
	virtual Mai_Bool isTextCom();
	virtual Mai_Status doEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	virtual Mai_Status doEffect();
	virtual Mai_Status setCursor();
	Mai_Status addMouseListener(MaiMouseListener* mml);
	Mai_Status removeMouseListener(MaiMouseListener* mml);
	Mai_Status setFatherFrame(Mai_Void* father_frame);
};

/* MaiCanvas */
class MaiCanvas:public MaiComponent
{
private:
	Mai_Image* image;
public:
	MaiCanvas();
	Mai_Status paint(Mai_Image* buffer);
	Mai_Status setImage(Mai_Image* img);
	Mai_Status delImage();
};

/* MaiBotton */
class MaiBotton:public MaiComponent
{
private:
	struct
	{
		WCHAR* head;
		Mai_I32 num;
	} title;

	Mai_Font* font0;

	//Heap_Alloc0 heap0;
public:
	MaiBotton();
	Mai_Status paint(Mai_Image* buffer);
	Mai_Status setTitle(WCHAR* tl);
	Mai_Status setFont(Mai_Font* font);
	Mai_Status doEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
};

/* MaiTextArea */
class MaiTextArea:public MaiComponent
{
public:
	typedef struct _Line
	{
		WCHAR* head;
		Mai_I32 n;
		Mai_I32 num;
	} Line;

	struct
	{
		Line** base;
		Mai_I32 n;
		Mai_I32 num;
	} text;

	struct
	{
		Mai_I32 a, b;
	} base_co;

	struct
	{
		Mai_I32_Fixed x, y;
	} off_co;

	struct
	{
		Mai_I32_Fixed left, top, right, bottom;
	} area_dis;

	struct
	{
		Mai_I32 a, b;
	} cursor;

	Mai_Font* font0;
	Mai_I32_Fixed line_height;

	Mai_I32 textcolor;

	HCURSOR cursor0;
public:
	MaiTextArea();
	Mai_Status paint(Mai_Image* buffer);
	Mai_Status setFont(Mai_Font* font);
	Mai_Status insertChar(WCHAR c);
	Mai_Status appendText(WCHAR* text0);
	Mai_Bool isTextCom();
	Mai_Status doEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	Mai_Status setCursor();
	Mai_Status doEffect();
};

/* MaiFrame */

class MaiFrame:public MaiThread
{
public:
	WNDCLASSEX wc0;
private:
	HINSTANCE hinstance;

	//LPWSTR classname;
	//LPWSTR title;

	

	HWND hwnd0;

	MSG msg0;

	Mai_Status status;

	Heap_Alloc0 heap0;

	Mai_I32 location_x;
	Mai_I32 location_y;
	Mai_I32 size_x;
	Mai_I32 size_y;

	WCHAR* classname;
	WCHAR* title;

	Mai_Image* show_buffer;
	Mai_I32 bgcolor;

	BITMAPINFO* bmi0;

	struct
	{
		MaiComponent** head;
		Mai_I32 num;
	} components;

	Mai_Bool is_hold_dc;
	HDC hdc1;

	DWORD style;
	DWORD exstyle;
	MaiFrame* parent;
	

	MaiComponent* mouse_comp;
public:
	HCURSOR cursor_temp;
private:
	Mai_Status MessageLoop();

public:
	class Heart:public MaiThread
	{
	private:
		MaiFrame* of;
	public:
		Heart();
		Mai_Status setFrame(MaiFrame* f);
		Mai_Status Proc();
	};
private:
	Heart heart;
public:
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	Mai_Status doMouseEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	Mai_Status doKeyEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	MaiFrame(MaiFrame* parent = NULL, DWORD exstyle = 0, DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU);
	Mai_Status init(MaiFrame* parent, DWORD exstyle, DWORD style);
	Mai_Status Proc();
	Mai_Status HeartProc();
	Mai_Status holdDC(Mai_Bool is_hold);
	Mai_Status setBGColor(Mai_I32 color);
	Mai_Status setLocation(Mai_I32 x, Mai_I32 y);
	Mai_Status setSize(Mai_I32 width, Mai_I32 height);
	Mai_Status setTitle(WCHAR* title);
	Mai_Status show();
	Mai_Status paint(Mai_Bool is_hdc, HDC hdc0);
	Mai_Status repaint();
	Mai_Status addComponent(MaiComponent* mc);
	Mai_Status delComponent(MaiComponent* mc);
	HWND getHWND();
	
};



/* MaiWND */

class MaiWND:public MaiThread
{
public:
	WNDCLASSEX wc0;
protected:
	HINSTANCE hinstance;

	//LPWSTR classname;
	//LPWSTR title;

	

	HWND hwnd0;

	//MSG msg0;

	Mai_Status status;

	Heap_Alloc0 heap0;

	Mai_I32 location_x;
	Mai_I32 location_y;
	Mai_I32 size_x;
	Mai_I32 size_y;

	WCHAR* classname;
	WCHAR* title;

	Mai_Image* show_buffer;
	Mai_I32 bgcolor;

	BITMAPINFO* bmi0;

	/*struct
	{
		MaiComponent** head;
		Mai_I32 num;
	} components;*/

	Mai_Bool is_hold_dc;
	HDC hdc1;

	DWORD style;
	DWORD exstyle;
	MaiWND* parent;
	

	//MaiComponent* mouse_comp;
public:
	HCURSOR cursor_temp;
private:
	

public:
	class Heart:public MaiThread
	{
	private:
		MaiWND* of;
	public:
		Heart();
		Mai_Status setFrame(MaiWND* f);
		Mai_Status Proc();
	};
protected:
	Heart heart;
public:
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	Mai_Status doMouseEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	Mai_Status doKeyEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	virtual Mai_Status doPaintEvent(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	MaiWND(MaiWND* parent = NULL, DWORD exstyle = 0, DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU);
	Mai_Status init(MaiWND* parent, DWORD exstyle, DWORD style);
	Mai_Status Proc();
	Mai_Status HeartProc();
	Mai_Status holdDC(Mai_Bool is_hold);
	Mai_Status setBGColor(Mai_I32 color);
	Mai_Status setLocation(Mai_I32 x, Mai_I32 y);
	Mai_Status setSize(Mai_I32 width, Mai_I32 height);
	Mai_Status setTitle(WCHAR* title);
	virtual Mai_Status show();
	Mai_Status paint(Mai_Bool is_hdc, HDC hdc0);
	Mai_Status repaint();
	//Mai_Status addComponent(MaiComponent* mc);
	//Mai_Status delComponent(MaiComponent* mc);
	HWND getHWND();
	static Mai_Status MessageLoop();
	
};


#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

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

