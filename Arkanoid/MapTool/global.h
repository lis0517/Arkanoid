#pragma once

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern INT			g_BlockCellSize;
extern INT			g_BlockCellSizeY;

extern LRESULT CALLBACK ControlProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK BlockTabProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
