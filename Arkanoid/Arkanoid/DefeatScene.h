#pragma once

#include "global.h"
#include "Ingame.h"
#include "BaseScene.h"

	class SceneMng;
	class DefeatScene : public BaseScene
	{
	private:
		float time;
		virtual void Register();
	private:
		Ingame * ingame;
	public:
		DefeatScene();
		virtual void Enter();
		virtual void Exit();
		virtual void Rander(HDC);
		virtual void Update(float);
		virtual LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

