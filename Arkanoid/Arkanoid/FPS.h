#pragma once
#include <Windows.h>
#define FPS 60.0f

class Fps
{
	static DWORD timeElapsed;
public:
	int secondTick;
	int tickCount;
	float Value;
	float deltaTime;
	DWORD start;//시스템 시작 후 경과 한 밀리 초 수를 검색합니다 (최대 49.7 일)
	DWORD prev;
	DWORD total;
public:
	Fps();
	~Fps();
	void Update(HWND hWnd);
	void Start();
};

