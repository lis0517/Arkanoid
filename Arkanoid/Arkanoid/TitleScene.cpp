#include "resource.h"
#include "TitleScene.h"
#include "SceneMng.h"

TitleScene::TitleScene()
{
	Init();
}

void TitleScene::Register()
{
	nextScene = eGameScene::INGAME;
}

void TitleScene::Enter()
{
	RECT rect;
	//HBITMAP bBitmap;
	BITMAP bit;
	POINT pt;
	GetClientRect(g_hWnd, &rect);
	bBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	GetObject(bBitmap, sizeof(BITMAP), &bit);
	pt.x = (rect.left + rect.right / 2) - 75;
	pt.y = (rect.top + rect.bottom / 4 * 2);
	_hWnd = CreateWindow(L"button", L"", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, pt.x, pt.y, 150, 50, g_hWnd, (HMENU)0, g_hInst, NULL);
	SendMessage(_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bBitmap);
}


void TitleScene::Exit()
{
	DestroyWindow(_hWnd);
}

void TitleScene::Rander(HDC hdc)
{
	HBITMAP myBitmap, oldBitmap;
	BITMAP bit;
	HDC memDC;
	int bx, by;
	memDC = CreateCompatibleDC(hdc);
	myBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	
	oldBitmap = (HBITMAP)SelectObject(memDC, myBitmap);
	
	GetObject(myBitmap, sizeof(BITMAP), &bit);
	
	bx = bit.bmWidth;
	by = bit.bmHeight;
	BitBlt(hdc, 0, 0, bx, by, memDC, 0, 0, SRCCOPY);

	SelectObject(memDC, oldBitmap);
	DeleteObject(myBitmap);
	DeleteDC(memDC);
}

void TitleScene::Update(float delta)
{
}

LRESULT CALLBACK TitleScene::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			SceneMng::GetInstance(g_hWnd)->ScnMove(nextScene);
			break;
		}
		break;
	}
	return FALSE;
}