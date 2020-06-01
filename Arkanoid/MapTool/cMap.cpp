#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
{
	Init();
}


cMap::~cMap()
{
}

void cMap::Init()
{
	_hdc = GetDC(g_hWnd);
	GetClientRect(g_hWnd, &rect);
	Vector2 vec;
	DWORD Brgb = RGB(192, 192, 192);
	DWORD Lrgb = RGB(96, 96, 96);
	/*float xx, yy, temp = 20.0f;
	xx = rect.right / 10.0f;
	yy = rect.bottom / 8.0f;*/

	for (int i = 0; i < 3; i++) {
		cBlock * Wall = new cBlock();
		Wall->SetBlockStyle(BlockStyle::RECTANGLE);
		Wall->SetPen(_hdc, PS_SOLID, 2, Lrgb);
		Wall->SetBrush(_hdc, Brgb);
		switch (i)
		{
		case 0://À§
			Wall->SetPos((float)(rect.left + rect.right) / 2, (float)rect.top);
			Wall->SetSize((float)rect.right, 20);
			break;
		case 1://¿Þ
			Wall->SetPos((float)rect.left, (float)(rect.top + rect.bottom) / 2);
			Wall->SetSize(20, (float)rect.bottom);
			break;
		case 2://¿À¸¥
			Wall->SetPos((float)rect.right, (float)(rect.top + rect.bottom) / 2);
			Wall->SetSize(20, (float)rect.bottom);
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
				DWORD dBrgb = RGB(255, 251, 240);
				DWORD dLrgb = RGB(160, 160, 164);
				nBlock->SetBrush(hdc, dBrgb);
				nBlock->SetPen(hdc, dLrgb);
				break;
			case 1:
				nBlock->SetBlockColor(eBlock_List::ORANGE);
				DWORD dBrgb = RGB(224, 160, 0);
				DWORD dLrgb = RGB(224, 96, 0);
				break;
			case 2:
				nBlock->SetBlockColor(eBlock_List::BLUEGREEN);
				DWORD dBrgb = RGB(0, 255, 255);
				DWORD dLrgb = RGB(0, 192, 192);
				break;
			case 3:
				nBlock->SetBlockColor(eBlock_List::GREEN);
				DWORD dBrgb = RGB(0, 255, 0);
				DWORD dLrgb = RGB(0, 192, 0);
				break;
			case 4:
				nBlock->SetBlockColor(eBlock_List::RED);
				DWORD dBrgb = RGB(255, 0, 0);
				DWORD dLrgb = RGB(192, 32, 0);
				break;
			case 5:
				nBlock->SetBlockColor(eBlock_List::PURPLE);
				DWORD dBrgb = RGB(224, 96, 192);
				DWORD dLrgb = RGB(160, 160, 164);
				break;
			case 6:
				nBlock->SetBlockColor(eBlock_List::YELLOW);
				DWORD dBrgb = RGB(255, 255, 0);
				DWORD dLrgb = RGB(192, 192, 0);
				break;
			case 7:
				nBlock->SetBlockColor(eBlock_List::BLUE);
				DWORD dBrgb = RGB(0, 160, 192);
				DWORD dLrgb = RGB(0, 128, 192);
				break;
			}
			++count;
			m_NomalBlock.push_back(nBlock);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		cBlock * nBlock = new cBlock();
		nBlock->SetBlockStyle(BlockStyle::RECTANGLE);
		nBlock->SetBlockType(eBlockType::UNIQUEBLOCK);
		switch (count)
		{
		case 0:
			nBlock->SetBlockColor(eBlock_List::SILVER);
			DWORD dBrgb = RGB(192, 192, 192);
			DWORD dLrgb = RGB(128, 128, 128);
			break;
		case 1:
			nBlock->SetBlockColor(eBlock_List::GOLD);
			DWORD dBrgb = RGB(225, 187, 0);
			DWORD dLrgb = RGB(160, 128, 0);
			break;
		case 2:
			nBlock->SetBlockColor(eBlock_List::FORTRESS);
			DWORD dBrgb = RGB(128, 128, 128);
			DWORD dLrgb = RGB(225, 187, 0);
			break;
		}
		m_UniqueBlock.push_back(nBlock);
	}




	/*switch (i)
	{
	case 0:
		nBlock->SetItemList(eItem_List::EXTRALIFE);
		break;
	case 1:
		nBlock->SetItemList(eItem_List::SHRINKVAUS);
		break;
	case 2:
		nBlock->SetItemList(eItem_List::EXPANDVAUS);
		break;
	case 4:
		nBlock->SetItemList(eItem_List::SLOWBALL);
	}*/
	/*nBlock->SetPen(hdc, PS_SOLID, 2, Lrgb);
	nBlock->SetBrush(hdc, Brgb);
	nBlock->SetPos(xx + (j * xx), yy + (i * temp));
	nBlock->SetSize((float)rect.right / 10, 30);
	m_Blocks.push_front(nBlock);
	xx = (float)rect.right / 10;*/
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
}


