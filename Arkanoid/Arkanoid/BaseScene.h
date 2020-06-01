#pragma once
#include <Windows.h>

class SceneMng;

class BaseScene
{
public:
	enum eGameScene
	{
		NONE, LOGO, TITLE, INGAME, VICTORY, DEFEAT
	};
protected:
	eGameScene nextScene;
	
	virtual void Register() {}
public:
	BaseScene();
public:
	void Init();
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Rander(HDC hdc) = 0;
	virtual void Update(float delta) = 0;
	virtual LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)=0;
	eGameScene GetScene()
	{
		return nextScene;
	}
};
