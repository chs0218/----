#include <Windows.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define PI 3.1415926535897
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


int hX[2] = { 70, 70 }, hY[2] = { 70, 70 };
BOOL CHANGESIZE[2] = { FALSE, FALSE };
BOOL MOVERL[2] = { FALSE, FALSE };
BOOL MOVEUD[2] = { FALSE, FALSE };
BOOL JUMP[2] = { FALSE, FALSE };
int r[2], g[2], b[2];
int SHAPE[2];
int tmpY[2];
int Size[2] = { 50, 50 };
HINSTANCE g_hInst;

LPCTSTR IpszClass = L"ParentClass";
LPCTSTR IpszWindowName = L"7-1";

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
	WndClass.lpszClassName = L"ChildClass1";
	WndClass.lpfnWndProc = ChildProc1;
	RegisterClassEx(&WndClass);
	WndClass.lpszClassName = L"ChildClass2";
	WndClass.lpfnWndProc = ChildProc2;
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

double getRadian(int num)
{
	return num * (PI / 180);
}

void DrawCircle(HDC hDC, double X, double Y, int Radius)
{
	Ellipse(hDC, X - Radius, Y - Radius, X + Radius, Y + Radius);
}

void DrawRectangle(HDC hDC, int X, int Y, int size)
{
	Rectangle(hDC, X - size, Y - size, X + size, Y + size);
}

void DrawTriangle(HDC hDC, int X, int Y, int size)
{
	POINT point[3];
	point[0].x = X;
	point[0].y = Y - size;
	point[1].x = X - size;
	point[1].y = Y + size;
	point[2].x = X + size;
	point[2].y = Y + size;
	Polygon(hDC, point, 3);
}
void realSwap(int* a, int* b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void BOOLSwap(BOOL* a, BOOL* b)
{
	BOOL tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void Swap()
{
	int tmp;

	realSwap(&hX[0], &hX[1]);
	realSwap(&hY[0], &hY[1]);
	realSwap(&tmpY[0], &tmpY[1]);
	realSwap(&Size[0], &Size[1]);
	realSwap(&r[0], &r[1]);
	realSwap(&g[0], &g[1]);
	realSwap(&b[0], &b[1]);
	BOOLSwap(&CHANGESIZE[0], &CHANGESIZE[1]);
	BOOLSwap(&MOVERL[0], &MOVERL[1]);
	BOOLSwap(&MOVEUD[0], &MOVEUD[1]);
	BOOLSwap(&JUMP[0], &JUMP[1]);

	tmp = SHAPE[0];
	SHAPE[0] = SHAPE[1];
	SHAPE[1] = SHAPE[0];

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	static HWND hButton[12];
	HWND child_hWnd;
	int tmpPos;
	switch (iMessage) {
	case WM_CREATE:
		child_hWnd = CreateWindow(L"ChildClass1", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 500, 400, hWnd, NULL, g_hInst, NULL);
		child_hWnd = CreateWindow(L"ChildClass2", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 600, 10, 500, 400, hWnd, NULL, g_hInst, NULL);
		hButton[0] = CreateWindow(L"button", L"1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 60, 450, 50, 50, hWnd, (HMENU) IDC_BUTTON, g_hInst, NULL);
		hButton[1] = CreateWindow(L"button", L"2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON1, g_hInst, NULL);
		hButton[2] = CreateWindow(L"button", L"3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 240, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON2, g_hInst, NULL);
		hButton[3] = CreateWindow(L"button", L"4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 330, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON3, g_hInst, NULL);
		hButton[4] = CreateWindow(L"button", L"5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 420, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON4, g_hInst, NULL);
		hButton[5] = CreateWindow(L"button", L"6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 510, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON5, g_hInst, NULL);
		hButton[6] = CreateWindow(L"button", L"7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON6, g_hInst, NULL);
		hButton[7] = CreateWindow(L"button", L"8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 690, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON7, g_hInst, NULL);
		hButton[8] = CreateWindow(L"button", L"9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 780, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON8, g_hInst, NULL);
		hButton[9] = CreateWindow(L"button", L"10", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 870, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON9, g_hInst, NULL);
		hButton[10] = CreateWindow(L"button", L"11", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 960, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON10, g_hInst, NULL);
		hButton[11] = CreateWindow(L"button", L"12", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1050, 450, 50, 50, hWnd, (HMENU)IDC_BUTTON11, g_hInst, NULL);

		srand(time(0));
		r[0] = rand() % 256;
		g[0] = rand() % 256;
		b[0] = rand() % 256;
		r[1] = rand() % 256;
		g[1] = rand() % 256;
		b[1] = rand() % 256;
		SHAPE[0] = rand() % 3;
		SHAPE[1] = rand() % 3;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
			if (MOVEUD[0])
			{
				hX[0] = 70;
				hY[0] = 70;
				MOVEUD[0] = FALSE;
			}
			if (MOVERL[0])
				MOVERL[0] = FALSE;
			else
				MOVERL[0] = TRUE;
			break;
		case IDC_BUTTON1:
			if (MOVERL[0])
			{
				hX[0] = 70;
				hY[0] = 70;
				MOVERL[0] = FALSE;
			}
			if (MOVEUD[0])
				MOVEUD[0] = FALSE;
			else
				MOVEUD[0] = TRUE;
			break;
		case IDC_BUTTON2:
			if (!JUMP[0])
			{
				tmpY[0] = hY[0];
				JUMP[0] = TRUE;
			}
			break;
		case IDC_BUTTON3:
			if (CHANGESIZE[0])
				CHANGESIZE[0] = FALSE;
			else
				CHANGESIZE[0] = TRUE;
			break;
		case IDC_BUTTON4:
			if (MOVEUD[1])
			{
				hX[1] = 70;
				hY[1] = 70;
				MOVEUD[1] = FALSE;
			}
			if (MOVERL[1])
				MOVERL[1] = FALSE;
			else
				MOVERL[1] = TRUE;
			break;
		case IDC_BUTTON5:
			if (MOVERL[1])
			{
				hX[1] = 70;
				hY[1] = 70;
				MOVERL[1] = FALSE;
			}
			if (MOVEUD[1])
				MOVEUD[1] = FALSE;
			else
				MOVEUD[1] = TRUE;
			break;
		case IDC_BUTTON6:
			if (!JUMP[1])
			{
				tmpY[1] = hY[1];
				JUMP[1] = TRUE;
			}
			break;
		case IDC_BUTTON7:
			if (CHANGESIZE[1])
				CHANGESIZE[1] = FALSE;
			else
				CHANGESIZE[1] = TRUE;
			break;
		case IDC_BUTTON8:
			for (int i = 0; i < 2; ++i)
			{
				MOVERL[i] = FALSE;
				MOVEUD[i] = FALSE;
				JUMP[i] = FALSE;
				CHANGESIZE[i] = FALSE;
			}
			break;
		case IDC_BUTTON9:
			r[0] = rand() % 256;
			g[0] = rand() % 256;
			b[0] = rand() % 256;
			r[1] = rand() % 256;
			g[1] = rand() % 256;
			b[1] = rand() % 256;
			SHAPE[0] = rand() % 3;
			SHAPE[1] = rand() % 3;
			break;
		case IDC_BUTTON10:
			PostQuitMessage(0);
			break;
		case IDC_BUTTON11:
			Swap();
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

LRESULT CALLBACK ChildProc1(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	static HDC hDC, MemDC;
	HDC tmphDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	
	static BOOL SIZEUP;

	switch (iMessage) {
	case WM_CREATE:
		SIZEUP = TRUE;
		SetTimer(hWnd, 1, 100, NULL);
		break;
	case WM_TIMER:
		if (CHANGESIZE[0])
		{
			if (SIZEUP)
			{
				Size[0] += 2;
				if (Size[0] > 70)
					SIZEUP = FALSE;
			}
			else
			{
				Size[0] -= 2;
				if (Size[0] < 30)
					SIZEUP = TRUE;
			}
		}
		else
		{
			if (JUMP[0])
			{
				hY[0] -= 10;
				if ((tmpY[0] - hY[0] == 50))
				{
					hY[0] = tmpY[0];
					JUMP[0] = FALSE;
				}
			}

			else if (MOVERL[0])
			{
				if (hY[0] == 70)
				{
					hX[0] += 10;
					if (hX[0] > 445)
						hY[0] = 320;
				}
				if (hY[0] == 320)
				{
					hX[0] -= 10;
					if (hX[0] < 70)
						hY[0] = 70;
				}
			}

			else if (MOVEUD[0])
			{
				if (hX[0] == 70)
				{
					hY[0] += 10;
					if (hY[0] > 320)
						hX[0] = 240;
				}
				else if (hX[0] == 240)
				{
					hY[0] -= 10;
					if (hY[0] < 70)
						hX[0] = 390;
				}
				else if (hX[0] == 390)
				{
					hY[0] += 10;
					if (hY[0] > 340)
					{
						hY[0] = 70;
						hX[0] = 70;
					}
				}
			}
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

		hBrush = CreateSolidBrush(RGB(r[0], g[0], b[0]));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		switch (SHAPE[0])
		{
		case 0:
			DrawCircle(hDC, hX[0], hY[0], Size[0]);
			break;
		case 1:
			DrawRectangle(hDC, hX[0], hY[0], Size[0]);
			break;
		case 2:
			DrawTriangle(hDC, hX[0], hY[0], Size[0]);
			break;
		}

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

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

LRESULT CALLBACK ChildProc2(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	static HDC hDC, MemDC;
	HDC tmphDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	int tmp;
	static BOOL SIZEUP;

	switch (iMessage) {
	case WM_CREATE:
		SIZEUP = TRUE;
		SetTimer(hWnd, 1, 100, NULL);
		break;
	case WM_TIMER:
		if (CHANGESIZE[1])
		{
			if (SIZEUP)
			{
				Size[1] += 2;
				if (Size[1] > 70)
					SIZEUP = FALSE;
			}
			else
			{
				Size[1] -= 2;
				if (Size[1] < 30)
					SIZEUP = TRUE;
			}
		}
		else
		{
			if (JUMP[1])
			{
				hY[1] -= 10;
				if ((tmpY[1] - hY[1] == 50))
				{
					hY[1] = tmpY[1];
					JUMP[1] = FALSE;
				}
			}

			else if (MOVERL[1])
			{
				if (hY[1] == 70)
				{
					hX[1] += 10;
					if (hX[1] > 445)
						hY[1] = 320;
				}
				if (hY[1] == 320)
				{
					hX[1] -= 10;
					if (hX[1] < 70)
						hY[1] = 70;
				}
			}

			else if (MOVEUD[1])
			{
				if (hX[1] == 70)
				{
					hY[1] += 10;
					if (hY[1] > 320)
						hX[1] = 240;
				}
				else if (hX[1] == 240)
				{
					hY[1] -= 10;
					if (hY[1] < 70)
						hX[1] = 390;
				}
				else if (hX[1] == 390)
				{
					hY[1] += 10;
					if (hY[1] > 340)
					{
						hY[1] = 70;
						hX[1] = 70;
					}
				}
			}
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

		hBrush = CreateSolidBrush(RGB(r[1], g[1], b[1]));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		switch (SHAPE[1])
		{
		case 0:
			DrawTriangle(hDC, hX[1], hY[1], Size[1]);
			break;
		case 1:
			DrawRectangle(hDC, hX[1], hY[1], Size[1]);
			break;
		case 2:
			DrawCircle(hDC, hX[1], hY[1], Size[1]);
			break;
		}

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

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
