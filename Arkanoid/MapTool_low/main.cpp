// MapTool_low.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "main.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE	g_hInstance = NULL;
HWND			g_hWnd = NULL;// ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void Compare(TCHAR *);

cMapTool * maptool;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MAPTOOL_LOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAPTOOL_LOW));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAPTOOL_LOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(BLACK_BRUSH);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MAPTOOL_LOW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInstance = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
HDC g_hdc = NULL;
HDC hdc;
PAINTSTRUCT ps;
HBITMAP hBitmap;
RECT crt;


#define ID_COMBOBOX 101
HWND g_hCombo = NULL;
int g_item = NULL;
TCHAR str[30];

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hMemDC;
	HBITMAP OldBit;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case ID_SAVE:
				if (maptool->MapSave())
				{
					MessageBox(g_hWnd, L"���� �Ϸ�", L"MapSave", MB_OK);
				}
				else
				{
					MessageBox(g_hWnd, L"���� ����", L"MapSave", MB_OK);
				}
				break;
			case ID_OPEN:
				if(maptool->MapOpen())
				{
					MessageBox(g_hWnd, L"���� �Ϸ�", L"MapSave", MB_OK);
				}
				else
				{
					MessageBox(g_hWnd, L"���� ����", L"MapSave", MB_OK);
				}
				break;
			case ID_COMBOBOX:
				switch (HIWORD(wParam)) {
				case CBN_SELCHANGE:
				{
					int i = 0;
					i = SendMessage(g_hCombo, CB_GETCURSEL, 0, 0);
					SendMessage(g_hCombo, CB_GETLBTEXT, i, (LPARAM)str);
					Compare(str);
				}
				break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}
        }
        break;
	case WM_CREATE:
		GetClientRect(hWnd, &crt);
		maptool = new cMapTool(hWnd);
		g_hCombo = CreateWindow(L"combobox", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,
			680, 450, 150, 200, hWnd, (HMENU)ID_COMBOBOX, g_hInstance, NULL);
		break;
	
		
	case WM_LBUTTONDOWN:
		maptool->Update(LOWORD(lParam), HIWORD(lParam));
		break;
	
    case WM_PAINT:
        {
		hdc = BeginPaint(hWnd, &ps);
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
		OldBit = (HBITMAP)SelectObject(hMemDC, hBitmap);
		FillRect(hMemDC, &crt, (HBRUSH)GetStockObject(BLACK_BRUSH));
		maptool->Render(hMemDC);
		/*_stprintf_s(countBuffer, 80, TEXT("%d"),in->GetLife());
		TextOut(hMemDC, 30, 30, countBuffer, lstrlen(countBuffer));*/
		/*_stprintf_s(speedBuffer, 80, TEXT("%f"), m_accel);
		TextOut(hMemDC, 300, 150, speedBuffer, lstrlen(speedBuffer));*/
		BitBlt(hdc, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);
		DeleteObject(SelectObject(hMemDC, OldBit));
		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Compare(TCHAR * str)
{
	if (!lstrcmp(str, L"None"))
	{
		g_item = eItem_List::NONEITEM;
	}
	else if (!lstrcmp(str, L"Expandvaus"))
	{
		g_item = eItem_List::EXPANDVAUS;
	}
	else if (!lstrcmp(str, L"Shrinkvaus"))
	{
		g_item = eItem_List::SHRINKVAUS;
	}
	else if (!lstrcmp(str, L"GrapBall"))
	{
		g_item = eItem_List::GRAPBALL;
	}
	else if (!lstrcmp(str, L"SlowBall"))
	{
		g_item = eItem_List::SLOWBALL;
	}
	else if (!lstrcmp(str, L"IncreaseBall"))
	{
		g_item = eItem_List::INCREASEBALL;
	}
	else if (!lstrcmp(str, L"LaserVaus"))
	{
		g_item = eItem_List::LASER;
	}
	else if (!lstrcmp(str, L"SkipStage"))
	{
		g_item = eItem_List::SKIPSTAGE;
	}
	else if (!lstrcmp(str, L"MegaBall"))
	{
		g_item = eItem_List::MEGABALL;
	}
}