#pragma once
#include "Block.h"
#include "Item.h"
#include "BlockMng.h"
#include "OutPut.h"
#include "Util.h"

struct Player
{
	int m_score;
	int m_life;
};


class Ingame
{
	OutPut * output;
	HWND hWnd;
	//float m_deltaTm;
	bool resetcheck;
public:
	Ingame(HWND hWnd);
	~Ingame();
	//void GameStart();
	void Init();
	void Update(float accel, float delta);
	void Rander(HDC hdc);
	void Input(DWORD wParam);
	void KeyState(bool state);
	bool GameOver();
	static void SetScore(int);
	static void SetLife(int);
	static int GetLife();
};

