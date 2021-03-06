/************************************************************************/
/*																		*/
/* 位图的创建、加载与绘制(CGdiBmp类的实现)    						    */
/* 采用Windows API方式实现												*/
/*																		*/
/* 作者：万立中	(C)2009-09-05											*/
/* www.wanlizhong.com													*/
/*																		*/
/************************************************************************/

#pragma once			
#include <windows.h>
//引用Transparent函数所在库
#pragma comment(lib,"Msimg32.lib")

class CGdiBmp
{
protected:
	HBITMAP hBitmap;//保存已经加载的位图句柄
	int bmpWidth;	//已经加载的位图的宽
	int bmpHeight;	//已经加载的位图的高	

public:
	//CGdiBmp类默认构造函数
	CGdiBmp();
	//使用指定的文件创建一个Bitmap对象
	CGdiBmp(LPTSTR fileName);
	//创建一个指定宽、高的空Bitmap对象，默认颜色为黑色
	CGdiBmp(HDC hDC, int ibWidth, int ibHeight, COLORREF crColor = RGB(0, 0, 0));

	//CGdiBmp类的析构函数
	virtual ~CGdiBmp();
	//释放资源
	void Destroy();	

	//获得位图的句柄
	HBITMAP GetBitmap(){return hBitmap;};
	//获得位图的宽
	int getBmpWidth(){return bmpWidth;}	
	//获得位图的高
	int getBmpHeight(){return bmpHeight;}	

	//创建空白位图函数
	HBITMAP CreateBlankBMP (HDC hDC, int ibWidth, int ibHeight, COLORREF crColor );
	//加载位图函数
	BOOL LoadBmp (LPTSTR path );
	//绘制镜像位图
	void DrawMirror(HDC hDC, int x, int y, int mirror);
	//绘制源图像中的局部图像
	void DrawSingleFrame( HDC hDC, int x, int y, 
		int xFrame, int yFrame, 
		int wFrame, int hFrame,
		double ratio, int mirror,
		COLORREF crTransColor);
	void DrawAnimatedFrames(HDC hDC,int x,int y,int FrameCount,int RowFrames,
		int wFrame,int hFrame,double ratio,int mirror,
		COLORREF crTransColor);
	static void DrawWords(HDC hDC, LPTSTR text, RECT FontRect);
	static void DrawWords(HDC hDC, LPTSTR text, COLORREF FontColor, int FontSize, LPCTSTR FontName, RECT FontRect, int Align);
};
