#pragma once
#include "BaseScene.h"

class SceneMng;
class TitleScene : public BaseScene
{
private:
	TCHAR Buffer[80];
	HWND _hWnd;
	HDC _hdc;
	
	HBITMAP bBitmap;
protected:
	virtual void Register();
public:
	TitleScene();
	virtual void Enter();
	virtual void Exit();
	virtual void Rander(HDC hdc);
	virtual void Update(float delta);
	void DrawBtn(HWND hWnd, WPARAM wParam, LPARAM lParam);
	virtual LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

