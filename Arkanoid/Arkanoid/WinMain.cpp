#include <Windows.h>
#include <tchar.h>
#include "define.h"
#include "global.h"
#include "Block.h"
#include "Item.h"
#include "BlockMng.h"
#include "OutPut.h"
#include "FPS.h"
#include "Ingame.h"

//#include "LogoScene.h"
//#include "TitleScene.h"
//#include "GameScene.h"
//#include "BaseScene.h"
#include "SceneMng.h"

HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;
LPWSTR lpszClass = L"Arkanoid";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//Ingame * in;
Fps fps;
float m_accel;
float frametime;

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE prevhInstance, LPWSTR lpszcmd, int nCmdshow)
{
	HWND hWnd;
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	g_hInst = hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	//int x = GetSystemMetrics(SM_CXFRAME);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);

	//SetWindowPos();

	ShowWindow(hWnd, nCmdshow);

	//다이렉트 X에서도 많이 쓰이는 프레임 워크
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else//메시지가 없다면
		{
			fps.Update(hWnd);
			frametime = fps.deltaTime;
			//in->Update(m_accel,frametime);
			SceneMng::GetInstance(hWnd)->Update(frametime);
			InvalidateRect(hWnd, NULL, FALSE);
		}
	}
	return msg.wParam;
}

//////////////전역////////////////
HDC hdc;
PAINTSTRUCT ps;
RECT crt;
HBITMAP hBitmap;
//////////////////////////////////

TCHAR countBuffer[80];
TCHAR speedBuffer[80];

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hMemDC;
	HBITMAP OldBit;
	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &crt);
		//SetTimer(hWnd,1,100,(TIMERPROC))
		//in = new Ingame(hWnd);
		//SceneMng::GetInstance(hWnd)->RegisterScene();
		break;
	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
		OldBit = (HBITMAP)SelectObject(hMemDC, hBitmap);
		FillRect(hMemDC, &crt, (HBRUSH)GetStockObject(BLACK_BRUSH));
		SceneMng::GetInstance(hWnd)->Render(hMemDC);
		/*_stprintf_s(countBuffer, 80, TEXT("%d"),in->GetLife());
		TextOut(hMemDC, 30, 30, countBuffer, lstrlen(countBuffer));*/
		/*_stprintf_s(speedBuffer, 80, TEXT("%f"), m_accel);
		TextOut(hMemDC, 300, 150, speedBuffer, lstrlen(speedBuffer));*/
		BitBlt(hdc, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);
		DeleteObject(SelectObject(hMemDC, OldBit));
		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_QUIT:
		
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	SceneMng::GetInstance(hWnd)->EventScn(hWnd, iMessage, wParam, lParam);
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}