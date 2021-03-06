/**************************************************************/
/*                                                            */
/* 窗口处理及游戏框架构建                                     */
/* 作者：luren  （C）2012-03-12                                */
/*                                                            */
/*                                                            */
/**************************************************************/
#pragma once
#include<windows.h>
#include<stdio.h>
#include "CDesktop.h"
#include "CGdiBmp.h"
#include "debug_Global.h"
//----------------------------------------------------
//WinMain函数及回调函数的声明
//----------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
	PSTR szCmdLine,int iCmdShow);
LONG CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//----------------------------------------------------
//独立函数的声明，必须由具体游戏实现
//----------------------------------------------------
bool GameInitialize(HINSTANCE hInstance);
//new added
void GameBegin(HWND hWindow);
void GamePaint(HDC OffDC);
void GameRunning();
void GameStop();
//---------------------------------------------------
//CEngine类的定义
//---------------------------------------------------
class CEngine:public CGdiBmp
{
protected:
	static CEngine *pEngine;     //本游戏引擎类的静态指针
	HINSTANCE m_hInstance;       //实例句柄
	TCHAR wndClass[64];          //窗口类
	TCHAR wndTitle[64];      //标题
	int Width,Height,temp;        //窗口的高宽
	int scrnWidth,scrnHeight;    //屏幕分辨率宽和高
	//增加的变量-------------------------------------
	BOOL m_bFullScreen;      //设置全屏显示标志；
	RECT m_rcOld;            //记住当前窗口的尺寸
	LONG style;          //窗口的基本风格
	LONG ex_style;       //窗口的扩展风格
	CDesktop *dsk;       //屏幕管理类指针
	//-----------------------------------------------
	//增加的变量-------------------------------------
	BOOL isAsleep;				//运行状态
	int  IntervalTime;          //绘制速度
	HWND m_hWindow;				//窗口句柄
	//-----------------------------------------------
public:
	//构造函数
	CEngine(HINSTANCE hInstance,LPTSTR szWindowClass,LPTSTR szTitle,
		int iWidth=NORMAL_SCREEN_WIDTH, int iHeight=NORMAL_SCREEN_HEIGHT);
	virtual~CEngine();//析构函数
	static CEngine*GetEngine()  //返回本游戏引擎的静态指针
	{
		return pEngine;
	};
	BOOL Initialize(int iCmdShow); //初始化处理
	//消息处理函数，将被回调函数调用
	LONG GameEvent(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lparam);
	//新增加的函数
	BOOL GetSleep()
	{
		return isAsleep;
	}
	void SetSleep(BOOL asleep)
	{
		isAsleep=asleep;
	}
	int GetFrameSpeed()
	{
		return IntervalTime;
	}
	void SetFrameSpeed(int iTime)
	{
		IntervalTime=1000/iTime;
	}
	HWND GetWindow()
	{
		return m_hWindow;
	}
	void SetWindow(HWND hWindow)
	{
		m_hWindow=hWindow;
	}
	int GetWidth()
	{
		return Width;
	}
	int GetHeight()
	{
		return Height;
	}
};