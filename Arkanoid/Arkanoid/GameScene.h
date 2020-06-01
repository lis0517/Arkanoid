#pragma once

#include "global.h"
#include "Ingame.h"
#include "BaseScene.h"

class SceneMng;
class GameScene : public BaseScene
{
private:
	virtual void Register();
private:
	Ingame * ingame;
public:
	GameScene();
	virtual void Enter();
	virtual void Exit();
	virtual void Rander(HDC);
	virtual void Update(float);
	virtual LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

