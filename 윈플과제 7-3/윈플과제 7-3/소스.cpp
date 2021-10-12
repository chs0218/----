#include <Windows.h>
#include "resource.h"

#define PI 3.1415926535897
#define ID_LISTBOX 10
#define IDC_BUTTON 100
#define IDC_BUTTON1 101
#define IDC_BUTTON2 102
#define IDC_BUTTON3 103
#define IDC_BUTTON4 104
#define IDC_BUTTON5 105
#define IDC_BUTTON6 106
#define IDC_BUTTON7 107
#define IDC_BUTTON8 108
#define IDC_BUTTON9 109
#define IDC_BUTTON10 110
#define IDC_BUTTON11 111


char Items[5][15] = {"∫¢≤…", "«œ¥√", "πŸ¥Ÿ", "ªÍ", "«ÿπŸ∂Û±‚" };
int SelectedPicture;
int nowPicture, xPos;
int LastPicture;
BOOL SET, MOVE;
BOOL FLAG[10];
HINSTANCE g_hInst;

LPCTSTR IpszClass = "ParentClass";
LPCTSTR IpszWindowName = "7-1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildProc1(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildProc2(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;

	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass;
	WndClass.hInstance = hInstance;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	WndClass.lpszClassName = "ChildClass1";
	WndClass.lpfnWndProc = ChildProc1;
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW,
		0, 0, 1130, 570, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	static HWND hButton[6];
	HBITMAP hBit;
	static HWND child_hWnd, hList;
	int tmpPos;
	switch (iMessage) {
	case WM_CREATE:
		child_hWnd = CreateWindow("ChildClass1", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 50, 300, 300, hWnd, NULL, g_hInst, NULL);
		hButton[0] = CreateWindow("button", "¡¬√¯¿Ãµø", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 30, 180, 50, 50, hWnd, (HMENU)IDC_BUTTON, g_hInst, NULL);
		hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		SendMessage(hButton[0], BM_SETIMAGE, 0, (LPARAM)hBit);
		hButton[1] = CreateWindow("button", "øÏ√¯¿Ãµø", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 415, 180, 50, 50, hWnd, (HMENU)IDC_BUTTON1, g_hInst, NULL);
		hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		SendMessage(hButton[1], BM_SETIMAGE, 0, (LPARAM)hBit);
		hButton[2] = CreateWindow("button", "º±≈√", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 630, 10, 50, 50, hWnd, (HMENU)IDC_BUTTON2, g_hInst, NULL);
		hButton[3] = CreateWindow("button", "¿Ãµø", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 690, 10, 50, 50, hWnd, (HMENU)IDC_BUTTON3, g_hInst, NULL);
		hButton[4] = CreateWindow("button", "∏ÿ√„", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 630, 70, 50, 50, hWnd, (HMENU)IDC_BUTTON4, g_hInst, NULL);
		hButton[5] = CreateWindow("button", "øœº∫", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 690, 70, 50, 50, hWnd, (HMENU)IDC_BUTTON5, g_hInst, NULL);
		nowPicture = 0;
		xPos = 0;
		LastPicture = 9;
		SET = FALSE;
		MOVE = FALSE;
		for (int i = 0; i < 10; ++i)
		{
			FLAG[i] = FALSE;
		}
		hList = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_STANDARD, 500, 10, 100, 200, hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL); 
		for (int i = 0; i < 5; i++) 
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
			xPos -= 300;
			if (xPos < 0)
				xPos = 0;
			else
				nowPicture -= 1;
			break;
		case IDC_BUTTON1:
			xPos += 300;
			if (xPos > 2700)
				xPos = 2700;
			else
				nowPicture += 1;
			break;
		case IDC_BUTTON2:
			SET = TRUE;
			break;
		case IDC_BUTTON3:
			MOVE = TRUE;
			break;
		case IDC_BUTTON4:
			MOVE = FALSE;
			break;
		case IDC_BUTTON5:
			for (int i = 9; i >= 0; --i)
			{
				if (FLAG[i])
				{
					LastPicture = i;
					break;
				}
			}
			break;
		case ID_LISTBOX: 
			switch (HIWORD(wParam)) 
			{ 
			case LBN_SELCHANGE: 
				SelectedPicture = SendMessage(hList, LB_GETCURSEL, 0, 0);
				break; 
			}
			break;
		default:
			break;
		}
		break;
	case WM_PAINT:

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:

		break;

	case WM_LBUTTONUP:

		break;
	case WM_MOUSEMOVE:

		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void Animation(HDC hDC, HBITMAP hBit[10])
{

	HDC tmphDC;
	int Select, tmp;
	Select = xPos / 300;
	tmp = xPos % 300;

	if (xPos >= 0 && xPos < 300)
	{
		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[0]);
		StretchBlt(hDC, 0, 0, (300 - tmp), 300, tmphDC, tmp, 0, (300 - tmp), 300, SRCCOPY);
		DeleteObject(tmphDC);

		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[1]);
		StretchBlt(hDC, (300 - tmp), 0, tmp, 300, tmphDC, 0, 0, tmp, 300, SRCCOPY);
		DeleteObject(tmphDC);
	}

	else if (xPos >= 300 && xPos < 600)
	{
		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[1]);
		StretchBlt(hDC, 0, 0, (300 - tmp), 300, tmphDC, tmp, 0, (300 - tmp), 300, SRCCOPY);
		DeleteObject(tmphDC);

		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[2]);
		StretchBlt(hDC, (300 - tmp), 0, tmp, 300, tmphDC, 0, 0, tmp, 300, SRCCOPY);
		DeleteObject(tmphDC);
	}

	else if (xPos >= 600 && xPos < 900)
	{
		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[2]);
		StretchBlt(hDC, 0, 0, (300 - tmp), 300, tmphDC, tmp, 0, (300 - tmp), 300, SRCCOPY);
		DeleteObject(tmphDC);

		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[3]);
		StretchBlt(hDC, (300 - tmp), 0, tmp, 300, tmphDC, 0, 0, tmp, 300, SRCCOPY);
		DeleteObject(tmphDC);
	}

	else if (xPos >= 900 && xPos < 1200)
	{
		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[3]);
		StretchBlt(hDC, 0, 0, (300 - tmp), 300, tmphDC, tmp, 0, (300 - tmp), 300, SRCCOPY);
		DeleteObject(tmphDC);

		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[4]);
		StretchBlt(hDC, (300 - tmp), 0, tmp, 300, tmphDC, 0, 0, tmp, 300, SRCCOPY);
		DeleteObject(tmphDC);
	}

	else if (xPos >= 1200 && xPos < 1500)
	{
		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[4]);
		StretchBlt(hDC, 0, 0, (300 - tmp), 300, tmphDC, tmp, 0, (300 - tmp), 300, SRCCOPY);
		DeleteObject(tmphDC);

		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[5]);
		StretchBlt(hDC, (300 - tmp), 0, tmp, 300, tmphDC, 0, 0, tmp, 300, SRCCOPY);
		DeleteObject(tmphDC);
	}

	else if (xPos >= 1500 && xPos < 1800)
	{
		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[5]);
		StretchBlt(hDC, 0, 0, (300 - tmp), 300, tmphDC, tmp, 0, (300 - tmp), 300, SRCCOPY);
		DeleteObject(tmphDC);

		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[6]);
		StretchBlt(hDC, (300 - tmp), 0, tmp, 300, tmphDC, 0, 0, tmp, 300, SRCCOPY);
		DeleteObject(tmphDC);
	}

	else if (xPos >= 1800 && xPos < 2100)
	{
		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[6]);
		StretchBlt(hDC, 0, 0, (300 - tmp), 300, tmphDC, tmp, 0, (300 - tmp), 300, SRCCOPY);
		DeleteObject(tmphDC);

		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[7]);
		StretchBlt(hDC, (300 - tmp), 0, tmp, 300, tmphDC, 0, 0, tmp, 300, SRCCOPY);
		DeleteObject(tmphDC);
	}

	else if (xPos >= 2100 && xPos < 2400)
	{
		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[7]);
		StretchBlt(hDC, 0, 0, (300 - tmp), 300, tmphDC, tmp, 0, (300 - tmp), 300, SRCCOPY);
		DeleteObject(tmphDC);

		tmphDC = CreateCompatibleDC(hDC);
		SelectObject(tmphDC, hBit[8]);
		StretchBlt(hDC, (300 - tmp), 0, tmp, 300, tmphDC, 0, 0, tmp, 300, SRCCOPY);
		DeleteObject(tmphDC);
	}

	else if (xPos >= 2400 && xPos < 2700)
	{
	tmphDC = CreateCompatibleDC(hDC);
	SelectObject(tmphDC, hBit[8]);
	StretchBlt(hDC, 0, 0, (300 - tmp), 300, tmphDC, tmp, 0, (300 - tmp), 300, SRCCOPY);
	DeleteObject(tmphDC);

	tmphDC = CreateCompatibleDC(hDC);
	SelectObject(tmphDC, hBit[9]);
	StretchBlt(hDC, (300 - tmp), 0, tmp, 300, tmphDC, 0, 0, tmp, 300, SRCCOPY);
	DeleteObject(tmphDC);
	}

	else if (xPos >= 2700 && xPos < 3000)
	{
	tmphDC = CreateCompatibleDC(hDC);
	SelectObject(tmphDC, hBit[9]);
	StretchBlt(hDC, 0, 0, (300 - tmp), 300, tmphDC, tmp, 0, (300 - tmp), 300, SRCCOPY);
	DeleteObject(tmphDC);

	tmphDC = CreateCompatibleDC(hDC);
	SelectObject(tmphDC, hBit[0]);
	StretchBlt(hDC, (300 - tmp), 0, tmp, 300, tmphDC, 0, 0, tmp, 300, SRCCOPY);
	DeleteObject(tmphDC);
	}
}

LRESULT CALLBACK ChildProc1(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	static HDC hDC, MemDC;
	static HBITMAP BackBit, oldBackBit, hBit[10];
	static RECT bufferRT;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		for (int i = 0; i < 10; ++i)
		{
			hBit[i] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_NULL));
		}
		break;
	case WM_TIMER:
		if (SET)
		{
			switch (SelectedPicture)
			{
			case 0:
				hBit[nowPicture] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
				break;
			case 1:
				hBit[nowPicture] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
				break;
			case 2:
				hBit[nowPicture] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
				break;
			case 3:
				hBit[nowPicture] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
				break;
			case 4:
				hBit[nowPicture] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7));
				break;
			default:
				break;
			}
			FLAG[nowPicture] = TRUE;
			SET = FALSE;
		}
		if (MOVE)
		{
			xPos += 10;
			if (xPos > (300 * (LastPicture + 1)) - 1)
				xPos = 0;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:

		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
		
		Animation(hDC, hBit);

		GetClientRect(hWnd, &bufferRT);
		BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(hDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:

		break;

	case WM_LBUTTONUP:

		break;
	case WM_MOUSEMOVE:

		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
