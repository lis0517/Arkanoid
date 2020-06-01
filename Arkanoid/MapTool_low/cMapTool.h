#pragma once

#ifdef  UNICODE 
#define __TEXT(quote) L##quote      // r_winnt
#else
#define __TEXT(quote) quote
#endif

#define TEXT(quote) __TEXT(quote)

class cMapTool
{
private:
	bool _selectNomal;
	bool _selectUnique;
	bool _selectSaveRc;
	HWND _hWnd;
	cMap * map;
	RECT _rcSelect;
	cBlock * temp1;
	cBlock * temp2;


private:
	TCHAR _nomalitem[6][30] = { L"None",L"Expandvaus",L"Shrinkvaus",L"GrapBall",L"SlowBall",L"IncreaseBall" };
	TCHAR _uniqueitem[5][15] = { L"None",L"ExtraLife",L"LaserVaus",L"SkipStage",L"MegaBall" };
public:
	cMapTool(HWND hWnd);
	~cMapTool();
	void Init();
	void Update(DWORD x, DWORD y);
	void Render(HDC hdc);
	void Highlight(cBlock * block, bool state);
	void SelectSave(cBlock *block1, cBlock *block2, int item);

	bool MapSave();
	bool MapOpen();
};

