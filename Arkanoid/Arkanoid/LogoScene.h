#pragma once
#include "BaseScene.h"

class SceneMng;
class LogoScene : public BaseScene
{
private:
	//HDC m_hdc;
	TCHAR Buffer[80];
protected:
	virtual void Register();
public:
	LogoScene();
	virtual void Enter();
	virtual void Exit();
	virtual void Rander(HDC hdc);
	virtual void Update(float delta);
	virtual LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

