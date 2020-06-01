#include "FPS.h"

Fps::Fps()
{
	secondTick = 0;
	tickCount = 0;
	deltaTime = 0.0f;
	total = 0;
	Value = 0.0f;
	Start();
}


Fps::~Fps()
{
}

void Fps::Start()
{
	start = GetTickCount();
	prev = start;
}

//프레임을 계산해주는 함수
void Fps::Update(HWND hWnd)
{
	DWORD end = GetTickCount();
	DWORD frametime;
	frametime = (end - prev);
	deltaTime = (float)frametime * 0.001f;
	start = end;

	if (frametime >= 1000)
	{
		start = GetTickCount();
		secondTick = tickCount;
		tickCount = 0;
	}
	else
	{
		float FpsTime = 1.0f / FPS;
		if (deltaTime < FpsTime)
		{
			Value = (deltaTime + (FpsTime - deltaTime)) * 1000;
		}
	}
	prev = end;

	Sleep(Value);//16.666667
	++tickCount;
}
