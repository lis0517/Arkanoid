#pragma once

typedef class DlgControl * LPDLGCONTROL;

class DlgControl
{
private:
	HWND m_DlgControl;
	HWND m_Combo;

	TCHAR * m_itemlist[10];

	POINT m_ptMouse;
	POINT m_SelectPos;

	int m_SelectTab;

	RECT m_BlockPos;
	RECT m_Draw;
public:
	DlgControl();
	~DlgControl();

public:
	LRESULT ControlMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void SelectBlock(int nSelectX, int nSelectY, int SelectTab);

	void Invalidate();
	void Init();
	void Render();
};

