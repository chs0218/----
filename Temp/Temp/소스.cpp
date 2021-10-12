#include <Windows.h>

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


char Items[5][15] = { "º¢²É", "ÇÏ´Ã", "¹Ù´Ù", "»ê", "ÇØ¹Ù¶ó±â" };
int SelectedPicture;
int nowPicture, xPos;
int LastPicture;
BOOL SET, MOVE;
BOOL FLAG[10];
HINSTANCE g_hInst;

LPCTSTR IpszClass = L"ParentClass";
LPCTSTR IpszWindowName = L"Temp";

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
