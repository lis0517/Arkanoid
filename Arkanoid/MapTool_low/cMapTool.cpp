#include "stdafx.h"
#include "cMapTool.h"

struct DataInfo
{
	Vector2		_pos;
	Vector2		_size;
	eItem_List  _itemList;
	eBlockType	_type;
	eBlock_List _blockList;
	DWORD		_brush;
	DWORD		_pen;
};

cMapTool::cMapTool(HWND hWnd)
{
	map = new cMap(hWnd);
	Init();
}


cMapTool::~cMapTool()
{
}

void cMapTool::Init()
{
	_selectNomal = false;
	_selectUnique = false;
	_selectSaveRc = false;
	temp1 = nullptr;
	temp2 = nullptr;
}

void cMapTool::Update(DWORD x, DWORD y)
{
	
	POINT pt = { x,y };
	for (int i = 0; i < map->GetNomal()->size(); i++)
	{
		if (PtInRect(&map->GetNomal()->at(i)->GetRect(), pt))
		{
			for (int i = 0; i < 6; i++)
			{
				SendMessage(g_hCombo, CB_DELETESTRING, i, 0);
			}
			temp1 = map->GetNomal()->at(i);
			_selectNomal = true;
			
			Highlight(map->GetNomal()->at(i), _selectNomal);
			for (int i = 0; i < 6; i++)
			{
				SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)_nomalitem[i]);
			}
			break;
		}
	}
	for (int i = 0; i < map->GetUnique()->size(); i++)
	{
		if (PtInRect(&map->GetUnique()->at(i)->GetRect(), pt))
		{
			for (int i = 0; i < 6; i++)
			{
				SendMessage(g_hCombo, CB_DELETESTRING, i, 0);
			}
			temp1 = map->GetUnique()->at(i);
			
			_selectUnique = true;			
			Highlight(map->GetUnique()->at(i), _selectUnique);
			for (int i = 0; i < 6; i++)
			{
				SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)_uniqueitem[i]);
			}
			break;
		}
	}

	for (int i = 0; i < map->GetSave()->size(); i++)
	{
		if (PtInRect(&map->GetSave()->at(i)->GetRect(), pt))
		{
			temp2 = map->GetSave()->at(i);
			_selectSaveRc = true;
			Highlight(map->GetSave()->at(i), _selectSaveRc);
			break;
		}
	}

	if (_selectSaveRc && (_selectNomal || _selectUnique))
	{
		SelectSave(temp1, temp2, g_item);	
	}
	InvalidateRect(_hWnd, NULL, FALSE);
}

void cMapTool::Render(HDC hdc)
{
	map->Render(hdc);

	if (_selectSaveRc || _selectNomal || _selectUnique)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 50, 50));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH mybrush, oldbrush;
		mybrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldbrush = (HBRUSH)SelectObject(hdc, mybrush);
		Rectangle(hdc, _rcSelect.left, _rcSelect.top, _rcSelect.right, _rcSelect.bottom);
		SelectObject(hdc, oldbrush);
		SelectObject(hdc, oldPen);
		DeleteObject(pen);
		DeleteObject(mybrush);
	}
}

void cMapTool::Highlight(cBlock * block, bool state)
{
	if (state == false)
		return;
	_rcSelect = block->GetRect();
}

void cMapTool::SelectSave(cBlock *selectblock, cBlock *saveblock, int item)
{
	DWORD bcolor = selectblock->GetbColor();
	DWORD lcolor = selectblock->GetlColor();
	eBlock_List list = selectblock->GetColor();
	eBlockType etype = selectblock->GetType();
	
	saveblock->SetBrush(bcolor);
	saveblock->SetPen(PS_SOLID,0,lcolor);
	saveblock->SetBlockColor(list);
	saveblock->SetBlockType(etype);
	saveblock->SetItemList((eItem_List)item);
}

bool cMapTool::MapSave()
{
	FILE *fp, *fp2;

	_tfopen_s(&fp, TEXT("Size.txt"), TEXT("w"));
	_tfopen_s(&fp2, TEXT("Block.txt"), TEXT("wt,ccs=UTF-8"));
	int size = 0;
	for (int i = 0; i < map->GetSave()->size(); i++)
	{
		if (map->GetSave()->at(i)->GetType() != eBlockType::NONE)
		{
			++size;
		}
	}

	DataInfo * info = new DataInfo[size];
	int idx = 0;
	for (int i = 0; i < map->GetSave()->size(); i++)
	{
		if (map->GetSave()->at(i)->GetType() != eBlockType::NONE)
		{
			info[idx]._pos = map->GetSave()->at(i)->Getpos();
			info[idx]._size = map->GetSave()->at(i)->Getsize();
			info[idx]._type = map->GetSave()->at(i)->GetType();
			info[idx]._itemList = (eItem_List)map->GetSave()->at(i)->GetItemList();
			info[idx]._blockList = map->GetSave()->at(i)->GetColor();
			info[idx]._brush = map->GetSave()->at(i)->GetbColor();
			info[idx]._pen = map->GetSave()->at(i)->GetlColor();
			++idx;
		}
	}
	int dataSize = sizeof(DataInfo);

	if (!fp || !fp2)
	{
		fclose(fp);
		fclose(fp2);
		return false;
	}
	fprintf_s(fp, "%d", size);

	int writeCount = fwrite(info, sizeof(DataInfo), size, fp2);

	if (size == writeCount)
	{
		fclose(fp);
		fclose(fp2);
		return true;
	}

	fclose(fp);
	fclose(fp2);
	return false;
}

bool cMapTool::MapOpen()
{
	FILE *fp1, *fp2;

	_tfopen_s(
		&fp1
		, TEXT("Size.txt")
		//, TEXT("C:/Size.txt")
		, TEXT("r"));

	_tfopen_s(
		&fp2
		, TEXT("Block.txt")
		, TEXT("rt, ccs=UTF-8"));

	if (!fp1 || !fp2)
	{
		return false;
	}
	
	int dataLen = 0;
	fscanf_s(fp1, "%d", &dataLen);

	DataInfo *Info = new DataInfo[dataLen];
	int dataSize = sizeof(DataInfo);
	int readCount = fread(Info, dataSize, dataLen, fp2);

	for (int i = 0; i < dataLen; ++i) {
		cBlock *brick = new cBlock();
		brick->SetPos(Info[i]._pos.x,Info[i]._pos.y);
		brick->SetSize(Info[i]._size.x, Info[i]._size.y);
		brick->SetBrush(Info[i]._brush);
		brick->SetPen(PS_SOLID, 1, Info[i]._pen);
		brick->SetBlockType(Info[i]._type);
		brick->SetItemList(Info[i]._itemList);
		brick->SetBlockStyle(BlockStyle::RECTANGLE);

		map->GetSave()->push_back(brick);
	}
	return true;
}



