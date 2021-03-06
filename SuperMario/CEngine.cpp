#include "CEngine.h"
#include "CGdiBmp.h"
#include "CDxSound.h"

#include "MaiMarioSprite.h"

//-----------------------------------------------------
// 初始化类的静态变量
//-----------------------------------------------------
CEngine *CEngine::pEngine=NULL;

extern bool inWelcome;
extern bool inLevelBegin;
extern bool inPlaying;

extern CGdiBmp* about;
extern CGdiBmp* WelcomeScreenLogo;

extern void GamePaint(HDC OffDC);
extern void KeyControl(bool isUp, HDC OffDC);
extern void MouseMove(int x,int y);
extern void MouseLBDown(int x, int y);

//-----------------------------------------------------
//回调函数
//-----------------------------------------------------
LONG CALLBACK WndProcAbout(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	RECT rect;
	rect.left=485;
	rect.top=336;
	// problem maybe
	rect.right=600;
	rect.bottom=416;

	switch(msg){
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		about->DrawMirror(hdc, 0, 0, 0);
		CGdiBmp::DrawWords(hdc, TEXT("Exit[E]"), RGB(255, 255, 255), 19, TEXT("黑体"), rect, DT_CENTER);
		EndPaint(hWnd,&ps);
		return 0;
	case WM_CHAR:
		if(wParam == 'e' || wParam == 'E'){
			ShowWindow(hWnd, SW_HIDE);
			return 0;
		}
	default:
		return DefWindowProc(hWnd,msg,wParam,lParam);
	}
}

LONG CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	//只调用类中的消息处理函数
	return CEngine::GetEngine()->GameEvent(hWnd,msg,wParam,lParam);
}

//------------------------------------------------------
//WinMain函数
//------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
/*
	AllocConsole();
	freopen( "CONOUT$", "w+t", stdout );
	freopen( "CONIN$", "r+t", stdin );
*/

	MSG msg;
	static int TickElapsed = 0;
	int nowTick;
	if(GameInitialize(hInstance))
	{
		if(!CEngine::GetEngine()->Initialize(iCmdShow)){
			return FALSE;
		}
		while(TRUE)
		{
			if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				if(msg.message==WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//确保游戏没有进入睡眠状态
				if(!CEngine::GetEngine()->GetSleep())
				{
					nowTick = GetTickCount();
					if(nowTick > TickElapsed)
					{
						TickElapsed = nowTick + CEngine::GetEngine()->GetFrameSpeed();
						GameRunning();
					}
				}
			}
		}
		GameStop();
		return (int)msg.wParam;
	}
	return TRUE;
}

//------------------------------------------------------------
//构造函数
//------------------------------------------------------------
CEngine::CEngine(HINSTANCE hInstance,LPTSTR szWindowClass,LPTSTR szTitle,int iWidth,int iHeight)
{
	pEngine=this;
	m_hInstance=hInstance;
	//if(lstrlen(wndClass)>0)
	lstrcpy(wndClass,szWindowClass);
	//if(lstrlen(szTitle)>0)
	lstrcpy(wndTitle,szTitle);
	Width=iWidth;
	Height=iHeight;
	m_bFullScreen=FALSE;
	dsk=new CDesktop();
}

//------------------------------------------------------------
//析构函数
//------------------------------------------------------------
CEngine::~CEngine()
{
	delete dsk;
}

BOOL CEngine::Initialize(int iCmdShow)
{//printf("%s\n", wndClass);while (1) {Sleep(100);}
	WNDCLASSEX gamewin;
	//注意：style中必须加入CL——DBLCLKS，否则窗口不接收鼠标双击消息
	gamewin.cbSize           =sizeof(WNDCLASSEX);
	gamewin.style            =CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
	gamewin.lpfnWndProc      =WndProc;
	gamewin.cbClsExtra       =0;
	gamewin.cbWndExtra       =0;
	gamewin.hInstance        =m_hInstance;
	gamewin.hIcon            =NULL;
	gamewin.hCursor          =LoadCursor(NULL,IDC_ARROW);
	gamewin.hbrBackground    =(HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	gamewin.lpszClassName    =wndClass;
	gamewin.lpszMenuName     =NULL;
	gamewin.hIconSm          =NULL;
	if(!RegisterClassEx(&gamewin))
		return FALSE;
	//printf("dd");while (1) {Sleep(100);}
	HWND hWnd;
	hWnd=CreateWindow(wndClass,wndTitle,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,CW_USEDEFAULT,0,Width,Height,NULL,NULL,m_hInstance,NULL);
	if(!hWnd)
		return FALSE;
	ShowWindow(hWnd,iCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LONG CEngine::GameEvent(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	int x,y;
	switch(msg)
	{
	case WM_KEYDOWN: //键被按下的处理
		PAINTSTRUCT p;
		hdc=BeginPaint(hWnd,&p);
		KeyControl(false, hdc);
		if (MaiMarioSprite::getMainSprite()) MaiMarioSprite::getMainSprite()->OnKeyDown(wParam);
		if(wParam == VK_ESCAPE)//按下ESC键
		{
			m_bFullScreen = !m_bFullScreen; // 设置全屏显示标志
			//恢复窗口模式
			if(!m_bFullScreen)
			{
				ShowCursor(true);
				dsk->ResetMode();

				SetWindowLong(hWnd, GWL_STYLE, style);
				SetWindowLong(hWnd, GWL_EXSTYLE, ex_style);

				int oldWidth=m_rcOld.right-m_rcOld.left;
				int oldHeight=m_rcOld.bottom-m_rcOld.top;
				x = m_rcOld.left;
				y = m_rcOld.top;
				SetWindowPos(hWnd, HWND_NOTOPMOST, x, y, oldWidth, oldHeight, SWP_SHOWWINDOW);
			}
			else //显示退出程序对话框
			{
				//显示光标
				ShowCursor(true);
				if(IDOK==MessageBox(NULL, "你确定要退出吗？", wndTitle, 
					MB_OKCANCEL|MB_ICONQUESTION))
				{
					DestroyWindow(hWnd);
				}
				else
				{
					//隐藏光标
					m_bFullScreen=!m_bFullScreen; // 设置全屏显示标志
					ShowCursor(false);
					return 0;
				}
			}
		}
		return 0;
	case WM_SETFOCUS:
		SetSleep(0);
		return 0;
	case WM_KILLFOCUS:
		SetSleep(1);
		return 0;
	case WM_CREATE:
		SetWindow(hWnd);
		GameBegin(hWnd);
		return 0;
	case WM_CHAR:
		if(!inPlaying && inWelcome && !inLevelBegin){
			if(wParam == 'A' || wParam == 'a'){
				WNDCLASSEX aboutWin;
				//注意：style中必须加入CL——DBLCLKS，否则窗口不接收鼠标双击消息
				aboutWin.cbSize           =sizeof(WNDCLASSEX);
				aboutWin.style            =CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
				aboutWin.lpfnWndProc      =WndProcAbout;
				aboutWin.cbClsExtra       =0;
				aboutWin.cbWndExtra       =0;
				aboutWin.hInstance        =m_hInstance;
				aboutWin.hIcon            =NULL;
				aboutWin.hCursor          =LoadCursor(NULL,IDC_ARROW);
				aboutWin.hbrBackground    =(HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
				aboutWin.lpszClassName    ="mai";
				aboutWin.lpszMenuName     =NULL;
				aboutWin.hIconSm          =NULL;
				if(!RegisterClassEx(&aboutWin))
					return FALSE;
				//printf("dd");while (1) {Sleep(100);}
				HWND hWnd;
				hWnd=CreateWindow("mai","ABOUT - Exit[E]",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,CW_USEDEFAULT,0,Width,Height,NULL,NULL,m_hInstance,NULL);
				printf("%d\n", hWnd);
				if(!hWnd)
					return FALSE;
				SetWindowPos(hWnd, 0, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 600, 416, 0);
				ShowWindow(hWnd, SW_SHOWNORMAL);

				UpdateWindow(hWnd);
			}
		}
		return 0;
	case WM_SYSCOMMAND:
		if(wParam == SC_MAXIMIZE)
		{
			m_bFullScreen=!m_bFullScreen; // 设置全屏显示标志
			if(m_bFullScreen)
			{
				ShowCursor(false);
				GetWindowRect(hWnd, &m_rcOld);//记住当前窗口的尺寸
				style = GetWindowLong(hWnd,GWL_STYLE); 
				ex_style = GetWindowLong(hWnd, GWL_EXSTYLE); 

				dsk->SaveMode();

				//全屏幕显示
				HWND hDesktop;   
				RECT rc;
				hDesktop = GetDesktopWindow();	//获取桌面窗口的指针  
				GetWindowRect(hDesktop, &rc);	//得到桌面窗口的矩形

				bool ok = dsk->ChangeMode(Width, Height);

				//设置为WS_DLGFRAME、WS_BORDER或WS_EX_CLIENTEDGE都可以去掉标题栏
				//设置扩展风格为WS_EX_WINDOWEDGE，去掉窗口边框
				SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_WINDOWEDGE);
				SetWindowLong(hWnd, GWL_STYLE, WS_BORDER);
				SetWindowPos(hWnd, HWND_TOP, -1, -1, rc.right, rc.bottom, SWP_SHOWWINDOW);
			}
		}
		else if(wParam == SC_CLOSE)
		{
			ShowCursor(true);
			if(IDOK==MessageBox(NULL,"你确定要退出吗？", 
				wndTitle, MB_OKCANCEL|MB_ICONQUESTION))
			{
				DestroyWindow(hWnd);
			}
		}
		else
		{
			//由于WM_SYSCOMMAND消息不是由程序控制的，
			//所以必须将该消息传给DefWindowProc,否则会造成其他消息无法处理
			return DefWindowProc(hWnd, WM_SYSCOMMAND, wParam,lParam); 
		}
		return 0;
	case WM_LBUTTONDBLCLK:
		m_bFullScreen=!m_bFullScreen;  //设置全屏的标志
		if(m_bFullScreen)
		{
			ShowCursor(false);
			GetWindowRect(hWnd,&m_rcOld);   //记住当前窗口的尺寸
			style=GetWindowLong(hWnd,GWL_STYLE);
			ex_style=GetWindowLong(hWnd,GWL_EXSTYLE);
			dsk->SaveMode();
			//全屏显示
			HWND hCDesktop;
			RECT rc;
			hCDesktop=GetDesktopWindow();    //获取桌面窗口的指针
			GetWindowRect(hCDesktop,&rc);    //得到桌面窗口的矩形

			//wwy edited		used to be	dsk->ChangeMode(800,600);
			dsk->ChangeMode(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

			//设置为WS_DLGFRAME WS_BORDER 或
			//WS_EX_CLLENTEDGE都可以去掉标题栏
			//设置扩展风格为WS_EX_WINDOWEDGE,去掉窗口边框
			SetWindowLong(hWnd,GWL_EXSTYLE,WS_EX_WINDOWEDGE);
			SetWindowLong(hWnd,GWL_STYLE,WS_BORDER);
			SetWindowPos(hWnd,HWND_TOP,0,0,rc.right,rc.bottom,SWP_SHOWWINDOW);
		}
		else
		{
			ShowCursor(true);
			dsk->ResetMode();
			SetWindowLong(hWnd,GWL_STYLE,style);
			SetWindowLong(hWnd,GWL_EXSTYLE,ex_style);
			Width=m_rcOld.right-m_rcOld.left;
			Height=m_rcOld.bottom-m_rcOld.top;
			x=m_rcOld.left;
			y=m_rcOld.top;
			SetWindowPos(hWnd,HWND_NOTOPMOST,x,y,Width,Height,SWP_SHOWWINDOW);
		}
		return 0;
	case WM_CLOSE:
		ShowCursor(true);
		if(IDOK==MessageBox(NULL,"Are you sure?",wndTitle,MB_OKCANCEL|MB_ICONQUESTION))
		{
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_PAINT:
		PAINTSTRUCT ps;
		hdc=BeginPaint(hWnd,&ps);
		GamePaint(hdc);
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}