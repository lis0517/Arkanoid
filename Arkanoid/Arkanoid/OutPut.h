#pragma once
#include <list>
#include <iterator>
#include <math.h>
#include "Block.h"
#include "Item.h"
#include "BlockMng.h"
#include "Util.h"

struct LineBoolList
{
	bool bLeft;
	bool bRight;
	bool bTop;
	bool bBottom;
};

class OutPut
{
	bool flag;
	bool Ballflag;
	bool stateflag;
	bool m_Moving;
	bool m_reset;
	bool itemstate;

	LineBoolList t_Linelist;
private:
	float m_deltaTime;
	float m_accel;
	float playerSpeed;
	//static float ballSpeed;
	DWORD m_keyDir;
	float m_x, m_y;
	HDC hdc;
public:
	BlockMng * mng;
	float x, y;
	float bx, by;
public:
	OutPut(HWND hWnd);
	~OutPut();
	//////////////////////////Setting//////////////////////////
	void Init(HWND hWnd);
	void SettingMap(HDC hdc);
	bool ResetMap(HDC hdc);
	void Render(HDC hdc);
	void Release();
	//////////////////////////Update//////////////////////////
	void PlayerUpdate();
	void Update(float accel, float delta);
	void KeyInput(DWORD key);
	void BallUpdate(float delta);
	void KeyState(bool state);
	//////////////////////////Check//////////////////////////
	void CollisionCheck(Block * ball);
	void CollisionCal(Block * ball, Block * block);
	int CheckHit(Block * block1, Block * block2);
	float DistanceSqr(float x1, float y1, float x2, float y2);
	void BlockDirection(Block * block1, Block * block2);
	bool CheckPlayerDie(Block *block1);
	void returnDelta(Block * block1, Block * block2);
	//////////////////////////Game//////////////////////////
	void BlockDelete(Block * enemy);
	void ItemMaker(Block * item);
	void ItemUpdate();
	static float GetSpeed();
	static void SetSpeed(float speed);
	//////////////////////////Calculate//////////////////////////
	LineBoolList myIntersectRect(Block * rect, Vector2 line1, Vector2 line2);
	bool IntersectLine(Vector2 line1, Vector2 line2, Vector2 line3, Vector2 line4);
};