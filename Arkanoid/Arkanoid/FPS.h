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
	DWORD start;//�ý��� ���� �� ��� �� �и� �� ���� �˻��մϴ� (�ִ� 49.7 ��)
	DWORD prev;
	DWORD total;
public:
	Fps();
	~Fps();
	void Update(HWND hWnd);
	void Start();
};

