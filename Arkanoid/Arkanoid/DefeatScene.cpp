#include "resource.h"
#include "global.h"
#include "DefeatScene.h"
#include "SceneMng.h"


DefeatScene::DefeatScene()
{
	Init();
}

void DefeatScene::Register()
{
	nextScene = eGameScene::TITLE;
}

void DefeatScene::Enter()
{
	time = 0.0f;
}

void DefeatScene::Exit()
{
	InvalidateRect(g_hWnd, NULL, FALSE);
}

void DefeatScene::Rander(HDC hdc)
{
	HBITMAP myBitmap, oldBitmap;
	BITMAP bit;
	HDC memDC;
	int bx, by;
	memDC = CreateCompatibleDC(hdc);
	myBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	oldBitmap = (HBITMAP)SelectObject(memDC, myBitmap);

	GetObject(myBitmap, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;
	BitBlt(hdc, 0, 0, bx, by, memDC, 0, 0, SRCCOPY);

	SelectObject(memDC, oldBitmap);
	DeleteObject(myBitmap);
	DeleteDC(memDC);
}

void DefeatScene::Update(float delta)
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

LRESULT CALLBACK DefeatScene::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	}
	return FALSE;
}
