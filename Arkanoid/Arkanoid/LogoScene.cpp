#include "resource.h"
#include "global.h"
#include "LogoScene.h"
#include "SceneMng.h"

static float time = 0.0f;

LogoScene::LogoScene()
{
	Init();
}

void LogoScene::Register()
{
	nextScene = eGameScene::TITLE;
}

void LogoScene::Enter()
{

}

void LogoScene::Exit()
{
	InvalidateRect(g_hWnd, NULL, FALSE);
}

void LogoScene::Rander(HDC hdc)
{
	HBITMAP myBitmap, oldBitmap;
	BITMAP bit;
	HDC memDC;
	int bx, by;
	memDC = CreateCompatibleDC(hdc);
	myBitmap=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
	oldBitmap = (HBITMAP)SelectObject(memDC, myBitmap);

	GetObject(myBitmap, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;
	BitBlt(hdc, 0, 0, bx, by, memDC, 0, 0, SRCCOPY);
	
	SelectObject(memDC, oldBitmap);
	DeleteObject(myBitmap);
	DeleteDC(memDC);
}
//HFONT hFont, oldFont;
//RECT rect;
//POINT pt;
//TEXTMETRIC ts;

//GetClientRect(g_hWnd, &rect);
//GetTextMetrics(hdc, &ts);
//int width = ts.tmAveCharWidth;//-widths
//hFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"돋움체");
//oldFont = (HFONT)SelectObject(hdc, hFont);
//_stprintf_s(Buffer, 80, TEXT("KTM 전문학교"));
//pt.x = ((rect.left + rect.right / 2));
//pt.y = rect.top + rect.bottom / 2;
//TextOut(hdc, pt.x-85, pt.y-30, Buffer, lstrlen(Buffer));
//SelectObject(hdc, oldFont);

//DeleteObject(hFont);
void LogoScene::Update(float delta)
{
	if (time <= 3)
	{
		time += delta;
	}
	else
	{
		SceneMng::GetInstance(g_hWnd)->ScnMove(nextScene);
	}
}

LRESULT CALLBACK LogoScene::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	}
	return FALSE;
}

