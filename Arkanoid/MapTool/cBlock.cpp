#include "stdafx.h"
#include "cBlock.h"

typedef std::vector<cBlock*>::iterator VITER;

cBlock::cBlock()
{
	_pen = NULL;
	_brush = NULL;
	Init();
}

cBlock::~cBlock() {}

//////////////////////////////////////Set//////////////////////////////////////
void cBlock::SetPen(HDC hdc, int penStyle, int width, DWORD color)
{
	if (!_pen)
	{
		DeleteObject(_pen);
	}
	_pen = CreatePen(penStyle, width, color);//첫번째 인자는 선 종류 두번째 인자는 외곽선 두께
}

void cBlock::SetBrush(HDC hdc, DWORD color)
{
	//HBRUSH oldBrush;
	if (!_brush)
	{
		DeleteObject(_brush);
	}
	_brush = CreateSolidBrush(color);
}

void cBlock::SetPos(float x, float y)
{
	_pos.x = x;
	_pos.y = y;
}

void cBlock::SetSize(float x, float y)
{
	_size.x = x;
	_size.y = y;
}

void cBlock::SetBlockStyle(BlockStyle style)
{
	m_Blockstyle = style;
}

void cBlock::SetBlockColor(eBlock_List color)
{
	m_BlockColor = color;
}

void cBlock::SetBlockType(eBlockType type)
{
	m_Blocktype = type;
}


//////////////////////////////////////Draw//////////////////////////////////////
void cBlock::DrawRectangle(HDC hdc, int left, int top, int right, int bottom)
{
	Rectangle(hdc, left, top, right, bottom);
}

//////////////////////////////////////Render//////////////////////////////////////
void cBlock::Init()
{
	//mapDraw[cBlockStyle::RECTANGLE] = &cBlock::DrawRectangle;
}

void cBlock::Render(HDC hdc)
{
	//MITER iter = mapDraw.find(m_cBlockstyle);
	CalculateRect();
	/*if (iter; != mapDraw.end())
	{*/
	oldPen = (HPEN)SelectObject(hdc, _pen);
	oldBrush = (HBRUSH)SelectObject(hdc, _brush);
	DrawRectangle(hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	//}
}

void cBlock::Release()
{
	DeleteObject(_pen);
	DeleteObject(_brush);
}

void cBlock::CalculateRect()
{
	float halfwidth = _size.x / 2;
	float halfheight = _size.y / 2;
	float left = _pos.x - halfwidth;
	float right = _pos.x + halfwidth;
	float top = _pos.y - halfheight;
	float bottom = _pos.y + halfheight;
	m_Rect.left = (LONG)left;
	m_Rect.top = (LONG)top;
	m_Rect.right = (LONG)right;
	m_Rect.bottom = (LONG)bottom;
}


void cBlock::SetPosX(float x)
{
	_pos.x = x;
}

//void cBlock::SetItemList(eItem_List item)
//{
//	this->item->Setitemlist(item);
//}

Vector2 cBlock::Getpos()
{
	return _pos;
}

Vector2 cBlock::Getsize()
{
	return _size;
}

RECT cBlock::GetRect()
{
	return m_Rect;
}


