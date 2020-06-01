#pragma once
#include <Windows.h>
#include <map>
//#include "Block.h"
#include "vector2.h"
#include "Util.h"
using namespace std;

enum eItem_List
{
	NONEITEM,

	EXTRALIFE,// 목숨 1개 추가
	EXPANDVAUS,// 바우스 크기 증가
	SHRINKVAUS,// 바우스 크기 감소
	REVERSEVAUS,// 바우스 움직임 반전
	LASER,//바우스 레이저
	SKIPSTAGE,//스테이지 넘어가기

	GRAPBALL,//공 잡기
	SLOWBALL, //공 속도 감소
	INCREASEBALL, // 공 개수 증가 (3개)
	MEGABALL,// 메가 볼(데미지 증가)
};

class Block;
class OutPut;
class Ingame;
class Item 
{
private:
	//eItem_List m_itemlist;
	Block * nVaus;
	Block * nBall;
	bool m_state;
public:
	Item(HWND hWnd);
	~Item();
	void Init();
	void Nomalstate(Block * vaus);
	void StateUpdate(bool activateItem);
	void ItemCall();
	bool SlowBall(bool activateItem);
	bool ExpandVaus(bool activateItem);
	bool ShrinkVaus(bool activateItem);
	bool GrapBall(bool activateItem);
	bool IncreaseBall(bool activateItem);
	
	bool LaserVaus(bool activateItem);
	bool ExtraLife(bool activateItem);
	bool MegaBall(bool activateItem);
	bool StageSkip(bool activateItem);
	MAKEFUNC(eItem_List, itemlist)
};

