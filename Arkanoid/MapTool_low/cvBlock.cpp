#include "stdafx.h"
#include "cvBlock.h"

typedef std::vector<cBlock*>::iterator VITER;


cBlock::cBlock()
{
	_pen = NULL;
	_brush = NULL;
	Init();
}

cBlock::~cBlock() {}

//////////////////////////////////////Set//////////////////////////////////////
void cBlock::SetPen(int penStyle, int width, DWORD color)
{
	_lColor = color;
	if (!_pen)
	{
		DeleteObject(_pen);
	}
	_pen = CreatePen(penStyle, width, _lColor);//첫번째 인자는 선 종류 두번째 인자는 외곽선 두께
}

void cBlock::SetBrush(DWORD color)
{
	_bColor = color;
	//HBRUSH oldBrush;
	if (!_brush)
	{
		DeleteObject(_brush);
	}
	_brush = CreateSolidBrush(_bColor);
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
	CalculateRect();

	oldPen = (HPEN)SelectObject(hdc, _pen);
	oldBrush = (HBRUSH)SelectObject(hdc, _brush);
	DrawRectangle(hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
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

void cBlock::SetItemList(eItem_List item)
{
	m_ItemList = item;
}

//void cBlock::SetItemList(eItem_List item)
//{
//	this->item->Setitemlist(item);
//}

int cBlock::GetItemList()
{
	return m_ItemList;
}

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


////////////BlockMng//////////////

cMap::cMap(HWND hWnd)
{
	Init(hWnd);
}


cMap::~cMap()
{
}

void cMap::Init(HWND hWnd)
{
	_hdc = GetDC(hWnd);
	GetClientRect(hWnd, &rect);
	Vector2 vec;
	DWORD Brgb = RGB(192, 192, 192);
	DWORD Lrgb = RGB(96, 96, 96);

	for (int i = 0; i < 3; i++) {
		cBlock * Wall = new cBlock();
		Wall->SetBlockStyle(BlockStyle::RECTANGLE);
		Wall->SetPen(PS_SOLID, 2, Lrgb);
		Wall->SetBrush(Brgb);
		switch (i)
		{
		case 0://위
			Wall->SetPos((float)PREVWIDTH / 2, (float)HEIGHT);
			Wall->SetSize((float)PREVWIDTH, 20);
			break;
		case 1://왼
			Wall->SetPos((float)0, (float)HEIGHT / 2);
			Wall->SetSize(20, (float)HEIGHT);
			break;
		case 2://오른
			Wall->SetPos((float)PREVWIDTH, (float)HEIGHT / 2);
			Wall->SetSize(20, (float)HEIGHT);
			break;
		}
		m_Wall.push_back(Wall);
	}

	DWORD dBrgb;
	DWORD dLrgb;
	int count = 0;
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cBlock * nBlock = new cBlock();
			nBlock->SetBlockStyle(BlockStyle::RECTANGLE);
			nBlock->SetBlockType(eBlockType::NOMALBLOCK);
			switch (count)
			{
			case 0:
				nBlock->SetBlockColor(eBlock_List::WHITE);
				dBrgb = RGB(255, 251, 240);
				dLrgb = RGB(160, 160, 164);	
				nBlock->SetPos(650, 200);
				nBlock->SetSize(43, 21);
				break;
			case 1:
				nBlock->SetBlockColor(eBlock_List::ORANGE);
				dBrgb = RGB(224, 160, 0);
				dLrgb = RGB(224, 96, 0);
				nBlock->SetPos(700, 200);
				nBlock->SetSize(43, 21);
				break;
			case 2:
				nBlock->SetBlockColor(eBlock_List::BLUEGREEN);
				dBrgb = RGB(0, 255, 255);
				dLrgb = RGB(0, 192, 192);
				nBlock->SetPos(750, 200);
				nBlock->SetSize(43, 21);
				break;
			case 3:
				nBlock->SetBlockColor(eBlock_List::GREEN);
				dBrgb = RGB(0, 255, 0);
				dLrgb = RGB(0, 192, 0);
				nBlock->SetPos(800, 200);
				nBlock->SetSize(43, 21);
				break;
			case 4:
				nBlock->SetBlockColor(eBlock_List::RED);
				dBrgb = RGB(255, 0, 0);
				dLrgb = RGB(192, 32, 0);
				nBlock->SetPos(650, 250);
				nBlock->SetSize(43, 21);
				break;
			case 5:
				nBlock->SetBlockColor(eBlock_List::PURPLE);
				dBrgb = RGB(224, 96, 192);
				dLrgb = RGB(160, 160, 164);
				nBlock->SetPos(700, 250);
				nBlock->SetSize(43, 21);
				break;
			case 6:
				nBlock->SetBlockColor(eBlock_List::YELLOW);
				dBrgb = RGB(255, 255, 0);
				dLrgb = RGB(192, 192, 0);
				nBlock->SetPos(750, 250);
				nBlock->SetSize(43, 21);
				break;
			case 7:
				nBlock->SetBlockColor(eBlock_List::BLUE);
				dBrgb = RGB(0, 160, 192);
				dLrgb = RGB(0, 128, 192);
				nBlock->SetPos(800, 250);
				nBlock->SetSize(43, 21);
				break;
			}
			nBlock->SetBrush(dBrgb);
			nBlock->SetPen( PS_SOLID, 0, dLrgb);
			m_NomalBlock.push_back(nBlock);
			++count;
		}
	}

	
	for (int i = 0; i < 3; i++)
	{
		DWORD dUBrgb;
		DWORD dULrgb;
		cBlock * uBlock = new cBlock();
		uBlock->SetBlockStyle(BlockStyle::RECTANGLE);
		uBlock->SetBlockType(eBlockType::UNIQUEBLOCK);
		switch (i)
		{
		case 0:
			uBlock->SetBlockColor(eBlock_List::SILVER);
			dUBrgb = RGB(192, 192, 192);
			dULrgb = RGB(128, 128, 128);
			uBlock->SetPos(700, 100);
			uBlock->SetSize(43, 21);
			break;
		case 1:
			uBlock->SetBlockColor(eBlock_List::GOLD);
			dUBrgb = RGB(225, 187, 0);
			dULrgb = RGB(160, 128, 0);
			uBlock->SetPos(750, 100);
			uBlock->SetSize(43, 21);
			break;
		case 2:
			uBlock->SetBlockColor(eBlock_List::FORTRESS);
			dUBrgb = RGB(128, 128, 128);
			dULrgb = RGB(225, 187, 0);
			uBlock->SetPos(800, 100);
			uBlock->SetSize(43, 21);
			break;
		}
		uBlock->SetBrush(dUBrgb);
		uBlock->SetPen( PS_SOLID, 0, dULrgb);
		m_UniqueBlock.push_back(uBlock);
	}
	
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			cBlock * eBlock = new cBlock();
			eBlock->SetBlockStyle(BlockStyle::RECTANGLE);
			eBlock->SetBlockType(eBlockType::NONE);
			eBlock->SetItemList(eItem_List::NONEITEM);
			float bSx = (PREVWIDTH - 13) / 12;
			float bSy = bSx / 2;
			float nx = bSx * j + bSx / 2;
			float ny = bSy * i + bSy / 2;
			eBlock->SetPos(nx+12, ny);
			eBlock->SetSize(bSx, bSy);
			eBlock->SetBrush(RGB(0, 0, 0));
			eBlock->SetPen( PS_SOLID, 0, RGB(192, 192, 192));
			m_saveBlock.push_back(eBlock);
		}
	}
}

void cMap::Render(HDC hdc)
{
	for (int i = 0; i < m_Wall.size(); ++i)
	{
		m_Wall[i]->Render(hdc);
	}
	for (int i = 0; i < m_NomalBlock.size(); ++i)
	{
		m_NomalBlock[i]->Render(hdc);
	}
	for (int i = 0; i < m_UniqueBlock.size(); ++i)
	{
		m_UniqueBlock[i]->Render(hdc);
	}
	for (int i = 0; i < m_saveBlock.size(); ++i)
	{
		m_saveBlock[i]->Render(hdc);
	}
}
