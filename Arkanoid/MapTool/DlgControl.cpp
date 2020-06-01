#include "stdafx.h"
#include "DlgControl.h"

LPDLGCONTROL	g_DlgControl = NULL;

DlgControl::DlgControl()
{
	g_DlgControl = this;
	m_SelectTab = 0;
}


DlgControl::~DlgControl()
{
}

LRESULT CALLBACK ControlProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_DlgControl->ControlMsgProc(hDlg,iMessage,wParam,lParam);
}

LRESULT DlgControl::ControlMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case IDC_COMBO1:
			switch (HIWORD(wParam))
			{
				
					
			}
			break;
		default:
			break;
		}
	default:
		break;
	}
	return LRESULT();
}

void DlgControl::SelectBlock(int nSelectX, int nSelectY, int nSelectTab)
{
	m_SelectPos.x = nSelectX;
	m_SelectPos.y = nSelectY;
	m_SelectTab = nSelectTab;
}

void DlgControl::Invalidate()
{
	InvalidateRect(m_DlgControl, NULL, TRUE);
}

void DlgControl::Init()
{
	m_DlgControl = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_CONTROL), g_hWnd, (DLGPROC)ControlProc);
	GetWindowRect(m_DlgControl, &m_Draw);
	MoveWindow(m_DlgControl, m_Draw.left + (WIDTH+10), m_Draw.top + (HEIGHT-255), m_Draw.right - m_Draw.left, m_Draw.bottom - m_Draw.top, true);
	ShowWindow(m_DlgControl, SW_SHOW);

	m_Combo = GetDlgItem(m_DlgControl, IDC_COMBO1);

}


