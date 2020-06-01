#include "Block.h"

typedef void (Block::*DrawFunc)(HDC hdc, int left, int top, int right, int bottom);
typedef void (Block::*TypeFunc)(int hp);
typedef map<int, DrawFunc>::iterator MITER;
map<int, DrawFunc> mapDraw;

Block::Block(HWND hwnd)
{
	_hwnd = hwnd;
	_pen = NULL;
	_brush = NULL;
	m_Blockstyle = BlockStyle::RECTANGLE;
	item = new Item(hwnd);
	Init();
}

Block::~Block(){}

//////////////////////////////////////Set//////////////////////////////////////
void Block::SetPen(int penStyle, int width, DWORD color)
{
	if (!_pen)
	{
		DeleteObject(_pen);
	}
	_pen = CreatePen(penStyle, width, color);//첫번째 인자는 선 종류 두번째 인자는 외곽선 두께
}

void Block::SetBrush(DWORD color)
{
	//HBRUSH oldBrush;
	if (!_brush)
	{
		DeleteObject(_brush);
	}
	_brush = CreateSolidBrush(color);
}

void Block::SetPos(float x, float y)
{
	_pos.x = x;
	_pos.y = y;
}

void Block::SetSize(float x, float y)
{
	_size.x = x;
	_size.y = y;
}

void Block::SetBlockStyle(BlockStyle style)
{
	m_Blockstyle = style;
}

void Block::SetBlockType(BlockType type)
{
	m_Blocktype = type;
}


//////////////////////////////////////Draw//////////////////////////////////////
void Block::DrawRectangle(HDC hdc, int left, int top, int right, int bottom)
{
	Rectangle(hdc, left, top, right, bottom);
}

void Block::DrawEllipse(HDC hdc, int left, int top, int right, int bottom)
{
	Ellipse(hdc, left, top, right, bottom);
}


//////////////////////////////////////Render//////////////////////////////////////
void Block::Init()
{
	mapDraw[BlockStyle::RECTANGLE] = &Block::DrawRectangle;
	mapDraw[BlockStyle::ELLIPSE] = &Block::DrawEllipse;
}

void Block::Render(HDC hdc)
{
	MITER iter = mapDraw.find(m_Blockstyle);
	CalculateRect();
	if ( iter != mapDraw.end())
	{
		oldPen = (HPEN)SelectObject(hdc, _pen);
		oldBrush = (HBRUSH)SelectObject(hdc, _brush);
		(this->*mapDraw[m_Blockstyle])(hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
		SelectObject(hdc, oldPen);
		SelectObject(hdc, oldBrush);
	}
	
}

void Block::Release()
{
	DeleteObject(_pen);
	DeleteObject(_brush);
}

void Block::CalculateRect()
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

//////////////////////////////////////Move//////////////////////////////////////

void Block::MovebyXY(float x, float y)
{
	_pos.x += x;
	_pos.y += y;
}

void Block::MovebyX(float x)
{
	_pos.x += x;
}

void Block::MovebyY(float y)
{
	_pos.y += y;
}

void Block::SetPosX(float x)
{
	_pos.x = x;
}

void Block::SetItemList(eItem_List item)
{
	this->item->Setitemlist(item);
}

eItem_List Block::GetItemList()
{
	return item->Getitemlist();
}

Vector2 Block::Getpos()
{
	return _pos;
}

Vector2 Block::Getsize()
{
	return _size;
}

RECT Block::GetRect()
{
	return m_Rect;
}

void Block::SetDirection(const Vector2& vec)
{
	_direction = vec;
}

Vector2 Block::GetDirection()
{
	return _direction;
}

Item* Block::GetItem()
{
	return item;
}
