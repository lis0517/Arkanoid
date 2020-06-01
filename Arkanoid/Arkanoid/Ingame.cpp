#include "Ingame.h"

static struct Player mFirstPlayer = { 0,3 };

Ingame::Ingame(HWND hWnd)
{
	this->hWnd = hWnd;
	Init();
}


Ingame::~Ingame()
{
}

void Ingame::Init()
{
	/*mFirstPlayer.m_life = 3;
	mFirstPlayer.m_score = 0;*/
	resetcheck = false;
	output = new OutPut(hWnd);
}

void Ingame::Update(float accel, float delta)
{
	//m_deltaTm = delta;
	output->Update(accel, delta);
	output->BallUpdate(delta);
	if (resetcheck)
	{
		mFirstPlayer.m_life--;
		resetcheck = false;
	}
}

void Ingame::Rander(HDC hdc)
{
	output->SettingMap(hdc);
	output->Render(hdc);
	resetcheck = output->ResetMap(hdc);
}

void Ingame::Input(DWORD wParam)
{
	output->KeyInput(wParam);
}

void Ingame::KeyState(bool state)
{
	output->KeyState(state);
}

bool Ingame::GameOver()
{
	if (mFirstPlayer.m_life == 0)
	{
		output->Release();
		return true;
	}
	return false;
}

void Ingame::SetScore(int score)
{
	mFirstPlayer.m_score = score;
}

void Ingame::SetLife(int life)
{
	mFirstPlayer.m_life = life;
}

int Ingame::GetLife()
{
	return mFirstPlayer.m_life;
}
