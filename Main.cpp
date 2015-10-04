#include "Globals.h"
#include "Timer.h"
#include "Game.h"
#include "Debug.h"

LPCTSTR mainClassName = TEXT("Xetrix Class");
LPCTSTR mainWindowName = TEXT("Xetrix");

HDC		mainDC = NULL;
HGLRC	mainRC = NULL;
HWND	mainWnd = NULL;

void ReSizeScene(ULONG width,ULONG height)
{
	if(!height)
		height = 1;

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(float)width/(float)height,0.1f,100.0f);
}

bool InitializeGraphics(void)
{
	glShadeModel(GL_SMOOTH);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);

	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClearDepth(1.0f);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_POLYGON_SMOOTH);
	//glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	
	return true;
}

bool Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	if(!DrawGame())
		return false;
	
	return true;
}

bool Update(void)
{
	if(!UpdateTimer())
		return false;

	if(!UpdateGame())
		return false;

	return true;
}

void KillWindow(void)
{
	if(mainRC)
	{
		if(!wglMakeCurrent(NULL,NULL))
			MessageBox(NULL,TEXT("Could not release the device context."),TEXT("Error"),MB_OK|MB_ICONINFORMATION);

		if(!wglDeleteContext(mainRC))
			MessageBox(NULL,TEXT("Could not release the rendering context."),TEXT("Error"),MB_OK|MB_ICONINFORMATION);

		mainRC = NULL;
	}

	if(mainDC && !ReleaseDC(mainWnd,mainDC))
	{
		MessageBox(NULL,TEXT("Could not release the device context."),TEXT("Error"),MB_OK|MB_ICONINFORMATION);

		mainDC = NULL;
	}

	if(mainWnd && !DestroyWindow(mainWnd))
	{
		MessageBox(NULL,TEXT("Could not release the window handle."),TEXT("Error"),MB_OK|MB_ICONINFORMATION);

		mainWnd = NULL;
	}

	if(!UnregisterClass(mainClassName,GetModuleHandle(NULL)))
		MessageBox(NULL,TEXT("Could not unregister the window class."),TEXT("Error"),MB_OK|MB_ICONINFORMATION);
}

LRESULT WINAPI WinProcedure(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_SYSCOMMAND:
		switch(wParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return FALSE;
		}
		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
		ReSizeScene(LOWORD(lParam),HIWORD(lParam));
		return 0;

	case WM_KEYDOWN:
		KeyboardGame(lParam,wParam);
		return 0;

	case WM_LBUTTONDOWN:
		MouseGame(lParam,wParam);
		return 0;
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

bool InitializeWindow(ULONG width,ULONG height)
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,	// Color Buffer Size
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		24,	// Depth Buffer Size
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	UINT		pixelFormat;
	WNDCLASS	wc = {0};
	DWORD		dwExStyle = 0;
	DWORD		dwStyle = WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_SIZEBOX|WS_MAXIMIZEBOX;
	RECT		windowRect = {0,0,width,height};

	wc.style			= CS_CLASSDC;
	wc.lpfnWndProc		= WinProcedure;
	wc.hInstance		= GetModuleHandle(NULL);
	wc.hIcon			= LoadIcon(NULL,IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL,IDC_ARROW);
	wc.lpszClassName	= mainClassName;

	if(!RegisterClass(&wc))
	{
		MessageBox(NULL,TEXT("Could not register the window class."),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);

		return false;
	}

	AdjustWindowRectEx(&windowRect,dwStyle,FALSE,dwExStyle);

	mainWnd = CreateWindowEx(dwExStyle,
								mainClassName,
								mainWindowName,
								dwStyle,
								CW_USEDEFAULT,CW_USEDEFAULT,
								windowRect.right-windowRect.left,
								windowRect.bottom-windowRect.top,
								NULL,
								NULL,
								GetModuleHandle(NULL),
								NULL);
	if(!mainWnd)
	{
		KillWindow();
		MessageBox(NULL,TEXT("Window creation error."),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	
	mainDC = GetDC(mainWnd);
	if(!mainDC)
	{
		KillWindow();
		MessageBox(NULL,TEXT("Could not create a device context."),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	pixelFormat = ChoosePixelFormat(mainDC,&pfd);
	if(!pixelFormat)
	{
		KillWindow();
		MessageBox(NULL,TEXT("Could not find a suitable pixel format."),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(!SetPixelFormat(mainDC,pixelFormat,&pfd))
	{
		KillWindow();
		MessageBox(NULL,TEXT("Could not set the pixel format."),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	mainRC = wglCreateContext(mainDC);
	if(!mainRC)
	{
		KillWindow();
		MessageBox(NULL,TEXT("Could not create a rendering context."),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(!wglMakeCurrent(mainDC,mainRC))
	{
		KillWindow();
		MessageBox(NULL,TEXT("Could not activate the rendering context."),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	ShowWindow(mainWnd,SW_SHOW);
	SetForegroundWindow(mainWnd);
	SetFocus(mainWnd);
	ReSizeScene(width,height);

	if(!InitializeGraphics())
	{
		KillWindow();
		MessageBox(NULL,TEXT("Graphics initialization failed."),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(!InitializeGame())
	{
		KillWindow();
		MessageBox(NULL,TEXT("Game initialization failed."),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	if(!InitializeTimer())
	{
		KillWindow();
		MessageBox(NULL,TEXT("Timer initialization failed."),TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	TRACE(TEXT("OpenGL %S\n"), glGetString(GL_VERSION));

	return true;
}

INT WINAPI WinMain(HINSTANCE /*hInstance*/,HINSTANCE /*hPrevInstance*/,LPSTR /*lpCmdLine*/,INT /*nCmdShow*/)
{
	SetUnhandledExceptionFilter(Debug::DumpException);

	srand(GetTickCount());

	InitCommonControls();

	if(!InitializeWindow(800,600))
		return 0;

	MSG	msg = {0};

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if(!Update())
			PostQuitMessage(0);
		else if(!Draw())
			PostQuitMessage(0);
		else if(!SwapBuffers(mainDC))
			TRACE(TEXT("Failed to swap buffers.\n"));
	}

	KillGame();
	KillTimer();
	KillWindow();

	return msg.wParam;
}
