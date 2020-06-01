#pragma once

typedef class DlgBlock * LPCDLGBLOCK;

class DlgBlock
{
private:
	
	HWND _hDlgBlocktab;
	HWND _hBlocktab;

	POINT _Selectpos;
	POINT _ptMoveStart;
	POINT _ptMoveEnd;
	
	bool _bSelectRange;
	
	int _RangeDirection;

	HDC _hdc;
	RECT _rcSelect;
	RECT _DrawRect;

	cMap * map;
public:
	DlgBlock();
	~DlgBlock();
	LRESULT BlockTabMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	MAKEFUNC(int, BlockTab)
	MAKEFUNC(int, SelectTab)
	//MAKEFUNC(int, TileTab)
	MAKEFUNC(int, SelectRangeX)
	MAKEFUNC(int, SelectRangeY)
	MAKEFUNC(bool, SelectFlag)

	POINT& GetSelectBlock() { return _Selectpos; }
	RECT& GetDrawRect() { return _DrawRect; }
	void SelectCancel();
	void Init();
	void Update();
	void Render(HDC hdc);
};

