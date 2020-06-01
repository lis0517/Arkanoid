#pragma once
#include <tchar.h>
#include <list>
#include <vector>
#include "define.h"
#include "struct.h"
#include "Block.h"
#include "Item.h"
#include "Util.h"

class BlockMng
{
private:
	RECT rect;
	HWND hWnd;
	vector<Block*> m_Wall;
	vector<Block*> m_Item;
	list<Block*> m_Blocks;
	list<Block*> m_Ball;
	Block * m_Vaus;
	Block * m_OrignVaus;
	float x, y;
private:
	float m_degree;
public:
	BlockMng(HWND hWnd);
	~BlockMng();
public:
	void Wall(HDC hdc);
	void Ball(HDC hdc);
	void Player(HDC hdc);
	void DistroyBlock(HDC hdc);
	void ItemBlock(Block * block, HDC hdc);
	void BackToOrign();
	vector<Block*>* GetWall();
	vector<Block*>* GetItemBlock();
	list<Block*>* GetDisBlock();
	Block * GetPlayer();
	list<Block*>* GetBall();
	MAKEFUNC(int, Ballsize)
	MAKEFUNC(int, Enemysize)
};

