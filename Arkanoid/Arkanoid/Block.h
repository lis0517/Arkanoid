#pragma once
#include <Windows.h>
#include <map>
#include <iterator>
#include "Item.h"
#include "vector2.h"

using namespace std;

enum BlockStyle {RECTANGLE, ELLIPSE};

enum BlockType { IMMORTAL, NOMALBLOCK, UNIQUEBLOCK, ITEM, VAUS, LASERVAUS };

enum eBlock_List
{
	WHITE,
	ORANGE,
	BLUEGREEN,
	GREEN,
	RED,
	PURPLE,
	YELLOW,
	BLUE,

	SILVER,
	GOLD,
	FORTRESS,
};

class Block
{
	Vector2 _direction;
	Vector2 _pos;//��ġ
	Vector2 _size;//ũ��
	HPEN _pen, oldPen;//�� ����ü
	HBRUSH _brush, oldBrush;//�귯�� ����ü
	HWND _hwnd;//�ڵ�
	RECT m_Rect;//�簢��
	//HDC hdc;
	int m_Blockstyle;//���� ��Ÿ��
	int m_Blocktype;//���� Ÿ��
	Item * item;
public:
	Block(HWND);
	~Block();
//////////////SetFunc//////////////
public:
	void SetPen(int penStyle, int width, DWORD color);
	void SetBrush(DWORD color);
	void SetPos(float x, float y);
	void SetSize(float x, float y);
	void SetBlockStyle(BlockStyle style);
	void SetBlockType(BlockType type);
	void SetPosX(float x);
	void SetItemList(eItem_List item);
//////////////DrawFunc//////////////
public:	
	void DrawRectangle(HDC, int, int, int, int);
	void DrawEllipse(HDC, int, int, int, int);
//////////////RenderFunc//////////////
public:
	void Init();
	void Render(HDC hdc);
	void CalculateRect();
	void Release();
//////////////MoveFunc//////////////
public:
	void MovebyXY(float x, float y);
	void MovebyX(float x);
	void MovebyY(float y);
public:
	eItem_List GetItemList();
	Vector2 Getpos();
	Vector2 Getsize();
	RECT GetRect();
	void SetDirection(const Vector2& vec);
	Vector2 GetDirection();
	Item* GetItem();
};

