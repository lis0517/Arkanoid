#include "stdafx.h"
#include "DlgBlock.h"

LPCDLGBLOCK g_DlgBlockTab = NULL;

DlgBlock::DlgBlock()
{
	g_DlgBlockTab = this;
	m_BlockTab = 0;
	m_SelectFlag = false;
	_bSelectRange = false;
	m_SelectRangeX = 0;
	m_SelectRangeY = 0;
	m_SelectTab = 0;
	_RangeDirection = 0;
	map = new cMap();
}


DlgBlock::~DlgBlock()
{
	ReleaseDC(_hDlgBlocktab, _hdc);
}

LRESULT DlgBlock::BlockTabMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_LBUTTONDOWN:
		_ptMoveStart.x = LOWORD(lParam) / g_BlockCellSize * g_BlockCellSize;
		_ptMoveStart.y = (HIWORD(lParam) - 25) / g_BlockCellSize * g_BlockCellSize;
		_Selectpos.x = _ptMoveStart.x / g_BlockCellSize;
		_Selectpos.y = _ptMoveStart.y / g_BlockCellSize;

		m_SelectFlag = true;
		_bSelectRange = true;
		m_SelectRangeX = m_SelectRangeY = 0;
		m_SelectTab = m_BlockTab;
		SMT->SetControlBlock();
		break;
	case WM_LBUTTONUP:
		if (_bSelectRange) _bSelectRange = false;
		break;
	case WM_RBUTTONDOWN:
		m_SelectFlag = false;
		SelectCancel();
		SMT->SetControlBlock();
		break;
	}
	return FALSE;
}

LRESULT CALLBACK BlockTabProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_DlgBlockTab->BlockTabMsgProc(hDlg, msg, wParam, lParam);
}

void DlgBlock::SelectCancel()
{
	_Selectpos.x = -1;
	_Selectpos.y = -1;
	m_SelectFlag = false;
}

void DlgBlock::Init()
{
	_hDlgBlocktab = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_BLOCKTAB), g_hWnd, (DLGPROC)BlockTabProc);
	GetWindowRect(_hDlgBlocktab, &_DrawRect);
	MoveWindow(_hDlgBlocktab, _DrawRect.left + (WIDTH + 10), _DrawRect.top , _DrawRect.right - _DrawRect.left, _DrawRect.bottom - _DrawRect.top, true);
	ShowWindow(_hDlgBlocktab, SW_SHOW);
	
	_hdc = GetDC(_hDlgBlocktab);

	TCITEM blk;
	_hBlocktab = CreateWindow(WC_TABCONTROL, TEXT(""), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_EX_STATICEDGE, 0, 0, 350, 500, _hDlgBlocktab, (HMENU)0, g_hInstance, NULL);
	blk.mask = TCIF_TEXT;
	blk.pszText = TEXT("Nomal");
	TabCtrl_InsertItem(_hBlocktab, 0, &blk);
	blk.pszText = TEXT("Unique");
	TabCtrl_InsertItem(_hBlocktab, 1, &blk);
}

void DlgBlock::Update()
{
	if (m_SelectFlag && (m_BlockTab == m_SelectTab))
	{
		int Left = _Selectpos.x * g_BlockCellSize;
		int Top = _Selectpos.y * g_BlockCellSize;

		switch (_RangeDirection)
		{
		case 0://nomal
			SetRect(&_rcSelect, Left, Top, Left + g_BlockCellSize*(m_SelectRangeX + 1), Top + g_BlockCellSize*(m_SelectRangeY + 1));
			break;
		//case 1://x
		//	SetRect(&_rcSelect, Left, Top, Left + g_BlockCellSize*(m_SelectRangeX + 1), Top + g_BlockCellSize*(m_SelectRangeY + 1));
		//	break;
		//case 2://y
		//	SetRect(&_rcSelect, Left, Top, Left + g_BlockCellSize*(m_SelectRangeX + 1), Top + g_BlockCellSize*(m_SelectRangeY + 1));
		//	break;
		//case 3://´ë°¢
		//	SetRect(&_rcSelect, Left, Top, Left + g_BlockCellSize*(m_SelectRangeX + 1), Top + g_BlockCellSize*(m_SelectRangeY + 1));
		//	break;
		}
	}
}

void DlgBlock::Render(HDC hdc)
{
	if (m_BlockTab == 0)
	{
		for (int i = 0; i < map->GetNomal().size(); ++i)
		{
			map->GetNomal()[i]->Render(hdc);
		}
	}
	else if (m_BlockTab == 1)
	{
		for (int i = 0; i < map->GetUnique().size(); ++i)
		{
			map->GetUnique()[i]->Render(hdc);
		}
	}
	if (m_SelectFlag && (m_BlockTab == m_SelectTab))
	{
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 50, 50));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

		Rectangle(hdc, _rcSelect.left, _rcSelect.top+ g_BlockCellSizeY, _rcSelect.right, _rcSelect.bottom+ g_BlockCellSizeY);
		SelectObject(hdc, oldbrush);
		SelectObject(hdc, oldPen);
		DeleteObject(pen);
		//Rectangle()
	}
}


