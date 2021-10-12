#include <Windows.h>
#include <math.h>
#include "resource.h"

#define WIDTH 1601
#define HEIGHT 2397
#define PI 3.1415926535897

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"Window Programming Lab";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg1_Proc(HWND, UINT, WPARAM, LPARAM);

BOOL singraph;
BOOL zigzaggraph;
BOOL springgraph;
BOOL Finish;
BOOL Move;
int xPos, yPos;
int r, g, b;
int x, y = 0;
int n, a;

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

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW,
		0, 0, 1500, 1500, NULL, (HMENU)NULL, hInstance, NULL);

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

void DrawCircle(HDC hDC, int X, int Y, int Radius)
{
	Ellipse(hDC, X - Radius, Y - Radius, X + Radius, Y + Radius);
}

void DrawSinGraph(HDC hDC, int x)
{
	for (int i = 0; i < 360; ++i)
	{
		MoveToEx(hDC, x - 1, 300 - (100 + y) * sin(getRadian(i)), NULL);
		LineTo(hDC, x, 300 - (100 + y) * sin(getRadian(i + 1)));
		++x;
	}

	for (int i = 0; i < 360; ++i)
	{
		MoveToEx(hDC, x - 1, 300 - (100 + y) * sin(getRadian(i)), NULL);
		LineTo(hDC, x, 300 - (100 + y)* sin(getRadian(i + 1)));
		++x;
	}

	for (int i = 0; i < 360; ++i)
	{
		MoveToEx(hDC, x - 1, 300 - (100 + y)* sin(getRadian(i)), NULL);
		LineTo(hDC, x, 300 - (100 + y) * sin(getRadian(i + 1)));
		++x;
	}

	for (int i = 0; i < 360; ++i)
	{
		MoveToEx(hDC, x - 1, 300 - (100 + y) * sin(getRadian(i)), NULL);
		LineTo(hDC, x, 300 - (100 + y) * sin(getRadian(i + 1)));
		++x;
	}

	for (int i = 0; i < 360; ++i)
	{
		MoveToEx(hDC, x - 1, 300 - (100 + y) * sin(getRadian(i)), NULL);
		LineTo(hDC, x, 300 - (100 + y) * sin(getRadian(i + 1)));
		++x;
	}

	for (int i = 0; i < 180; ++i)
	{
		MoveToEx(hDC, x - 1, 300 - (100 + y) * sin(getRadian(i)), NULL);
		LineTo(hDC, x, 300 - (100 + y) * sin(getRadian(i + 1)));
		++x;
	}
}

void Drawzigzag(HDC hDC, int x)
{
	MoveToEx(hDC, x - 1, 300, NULL);
	LineTo(hDC, x + 89, 210 - y);

	x += 90;

	for (int i = 0; i < 5; ++i)
	{
		MoveToEx(hDC, x - 1 + 360 * i, 210 - y, NULL);
		LineTo(hDC, x - 1 + 360 * i + 180, 390 + y);

		MoveToEx(hDC, x - 1 + 360 * i + 180, 390 + y, NULL);
		LineTo(hDC, x - 1 + 360 * (i + 1), 210 - y);
	}

}

void Drawspring(HDC hDC, int x)
{
	x = x - 151;
	for (int i = 0; i < 2160; ++i)
	{
		MoveToEx(hDC, x + 150* cos(getRadian(i)), 300 + (150 + y) * sin(getRadian(i)), NULL);
		LineTo(hDC, x + 150 * cos(getRadian(i + 1)), 300 + (150 + y) * sin(getRadian(i + 1)));
		++x;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	HPEN hPen, oldPen;
	static int a;
	switch (iMessage) {
	case WM_CREATE:
		singraph = FALSE;
		zigzaggraph = FALSE;
		springgraph = FALSE;
		Finish = FALSE;
		xPos = 0;
		yPos = 300;
		r = 0;
		g = 0;
		b = 0;
		x = 1;
		SetTimer(hWnd, 1, 25, NULL);
		break;
	case WM_TIMER:
		if (Finish)
			PostQuitMessage(0);

		if (Move)
		{
			if (singraph)
			{
				++xPos;
				if (xPos > 1480)
					xPos = 0;
				yPos = 300 - (100 + y) * sin(getRadian(xPos));
			}

			if (zigzaggraph)
			{
				++xPos;
				if (xPos > 1480)
					xPos = 0;
				if (a == 1)
				{
					++yPos;
					if (yPos == 390)
						a = 0;
					
				}

				else
				{
					--yPos;
					if (yPos == 210)
						a = 1;
				}
			}

			if (springgraph)
			{
				xPos = n + (150 + y) * cos(getRadian(a));
				yPos = 300 + (150 + y) * sin(getRadian(a));
				++n;
				++a;
			}

		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg1_Proc);
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		if (singraph)
		{
			hPen = CreatePen(PS_SOLID, 10, RGB(r, g, b));
			oldPen = (HPEN)SelectObject(hDC, hPen);
			DrawSinGraph(hDC, x);
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
			DrawCircle(hDC, xPos, yPos, 50);
		}
		if (zigzaggraph)
		{
			hPen = CreatePen(PS_SOLID, 10, RGB(r, g, b));
			oldPen = (HPEN)SelectObject(hDC, hPen);
			Drawzigzag(hDC, x);
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
			DrawCircle(hDC, xPos, yPos, 50);
		}
		if (springgraph)
		{
			hPen = CreatePen(PS_SOLID, 10, RGB(r, g, b));
			oldPen = (HPEN)SelectObject(hDC, hPen);
			Drawspring(hDC, x);
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
			DrawCircle(hDC, xPos, yPos, 50);
		}
		

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
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK Dlg1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static BOOL MoveLeft;
	static BOOL MoveUP;
	static BOOL MoveDOWN;

	switch (iMsg) {
	case WM_INITDIALOG:
		SetTimer(hDlg, 2, 25, NULL);
		MoveUP = FALSE;
		MoveDOWN = FALSE;
		return true;

	case WM_TIMER:
		if (MoveLeft)
		{
			--x;
			if (x < -359)
				x = 1;
		}

		if (MoveUP)
		{
			--y;
			if (y <  -100)
			{
				MoveUP = FALSE;
				MoveDOWN = TRUE;
			}

		}

		if (MoveDOWN)
		{
			++y;
			if (y > 100)
			{
				MoveUP = TRUE;
				MoveDOWN = FALSE;
			}

		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1:
			if (!Move)
			{
				if (MoveLeft)
					MoveLeft = FALSE;
				else
					MoveLeft = TRUE;
			}
			break;

		case IDC_BUTTON4:
			singraph = FALSE;
			zigzaggraph = FALSE;
			springgraph = FALSE;
			xPos = 0;
			yPos = 300;
			r = 0;
			g = 0;
			b = 0;
			x = 1;
			break;

		case IDC_BUTTON2:
			Move = FALSE;
			break;

		case IDC_BUTTON3:
			if (MoveUP || MoveDOWN)
			{
				MoveUP = FALSE;
				MoveDOWN = FALSE;
			}
			else
				MoveUP = TRUE;
			break;

		case IDC_BUTTON5:
			Move = TRUE;
			MoveLeft = FALSE;
			MoveUP = FALSE;
			MoveDOWN = FALSE;
			x = 1;
			y = 0;
			break;

		case IDC_BUTTON6:
			Finish = TRUE;
			break;

		case IDC_RADIO1:
			singraph = TRUE;
			zigzaggraph = FALSE;
			springgraph = FALSE;
			Move = FALSE;
			n = -150;
			a = 0;
			xPos = 0;
			yPos = 300;
			break;

		case IDC_RADIO2:
			singraph = FALSE;
			zigzaggraph = TRUE;
			springgraph = FALSE;
			Move = FALSE;
			n = -150;
			a = 0;
			xPos = 1;
			yPos = 300;
			break;

		case IDC_RADIO3:
			singraph = FALSE;
			zigzaggraph = FALSE;
			springgraph = TRUE;
			Move = FALSE;
			n = -150;
			a = 0;
			xPos = 0;
			yPos = 300;
			break;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;

		case IDC_CHECK2:
			if (r == 0)
				r += 255;

			else
				r -= 255;
			break;

		case IDC_CHECK3:
			r = abs(r - 255);
			g = abs(g - 255);
			b = abs(b - 255);
			break;

		case IDC_CHECK5:
			if (g == 0)
				g += 255;

			else
				g -= 255;
			break;

		case IDC_CHECK4:
			if (b == 0)
				b += 255;
			else
				b -= 255;
			break;
		}
		break;
	case WM_PAINT:

		break;

	case WM_DESTROY:
		KillTimer(hDlg, 2);
		break;
	}
	return 0;
}