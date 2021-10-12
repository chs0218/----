#include <Windows.h>
#include <time.h>
#include "resource.h"

#define WIDTH 1000
#define HEIGHT 1000

static BOOL winStart, winDraw;
static int r, g, b;
static int cs;
static BOOL finish;
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"Window Programming Lab";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg1_Proc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


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
		0, 0, 1000, 1000, NULL, (HMENU)NULL, hInstance, NULL);

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
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;

	static int xPos, yPos, Direction;
	static POINT point[3];
	HBRUSH hBrush, oldBrush;

	switch (iMessage) {
	case WM_CREATE:
		xPos = 500;
		yPos = 400;
		winStart = FALSE;
		winDraw = FALSE;
		Direction = 0;

		r = 255;
		g = 255;
		b = 255;

		finish = FALSE;
		SetTimer(hWnd, 1, 10, NULL);
		break;
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg1_Proc);
		break;
	case WM_TIMER:
		if (finish)
			PostQuitMessage(0);
		if (winStart)
			winDraw = TRUE;
		if (winStart)
		{
			switch (wParam)
			{
			case 1:
				switch (Direction)
				{
				case 0:
					xPos += 1;
					yPos += 1;
					if (yPos == 915)
						Direction = 1;
					else if (xPos == 933)
						Direction = 2;
					break;
				case 1:
					xPos += 1;
					yPos -= 1;
					if (xPos == 933)
						Direction = 3;
					else if (yPos == 0)
						Direction = 0;
					break;
				case 2:
					xPos -= 1;
					yPos += 1;
					if (xPos == 0)
						Direction = 0;
					else if (yPos == 915)
						Direction = 3;
					break;
				case 3:
					xPos -= 1;
					yPos -= 1;
					if (xPos == 0)
						Direction = 1;
					else if (yPos == 0)
						Direction = 2;
				}
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		if (winDraw)
		{
			hBrush = CreateSolidBrush(RGB(r, g, b));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			if (cs == 0)
				Ellipse(hDC, xPos, yPos, xPos + 50, yPos + 50);
			else if (cs == 1)
				Rectangle(hDC, xPos, yPos, xPos + 50, yPos + 50);
			else
			{
				point[0].x = xPos + 25;
				point[0].y = yPos;
				point[1].x = xPos;
				point[1].y = yPos + 50;
				point[2].x = xPos + 50;
				point[2].y = yPos + 50;
				Polygon(hDC, point, 3);
			}

			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
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
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	static BOOL Draw, start;

	static int xPos, yPos, Direction;
	static RECT rect;
	static POINT point[3];
	HBRUSH hBrush, oldBrush;

	switch (iMsg) {
	case WM_INITDIALOG:
		xPos = 150;
		yPos = 150;
		cs = 0;
		rect.left = 150;
		rect.right = 665;
		rect.top = 70;
		rect.bottom = 480;
		Direction = 0;
		start = FALSE;
		Draw = FALSE;
		SetTimer(hDlg, 1, 10, NULL);
		return true;
	case WM_TIMER:
		if (start)
		{
			switch (wParam)
			{
			case 1:
				switch (Direction)
				{
				case 0:
					xPos += 1;
					yPos += 1;
					if (yPos == 430)
						Direction = 1;
					else if (xPos == 615)
						Direction = 2;
					break;
				case 1:
					xPos += 1;
					yPos -= 1;
					if (xPos == 615)
						Direction = 3;
					else if (yPos == 70)
						Direction = 0;
					break;
				case 2:
					xPos -= 1;
					yPos += 1;
					if (xPos == 150)
						Direction = 0;
					else if (yPos == 430)
						Direction = 3;
					break;
				case 3:
					xPos -= 1;
					yPos -= 1;
					if (xPos == 150)
						Direction = 1;
					else if (yPos == 70)
						Direction = 2;
				}
			}
		}
		InvalidateRect(hDlg, &rect, FALSE);
		break;
	case WM_COMMAND: 
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1:
			Draw = TRUE;
			start = TRUE;
			break;

		case IDC_BUTTON2:
			EndDialog(hDlg, 0);
			break;

		case IDC_BUTTON3:
			start = FALSE;
			break;

		case IDC_BUTTON4:
			winStart = TRUE;
			break;

		case IDC_BUTTON5:
			EndDialog(hDlg, 0);
			finish = TRUE;
			break;

		case IDC_BUTTON6:
			winStart = FALSE;
			break;

		case IDC_RADIO7:
			cs = 0;
			break;

		case IDC_RADIO9:
			cs = 1;
			break;

		case IDC_RADIO8:
			cs = 2;
			break;

		case IDC_RADIO10:
			r = 255;
			g = 0;
			b = 255;
			break;

		case IDC_RADIO12:
			r = 0;
			g = 255;
			b = 255;
			break;

		case IDC_RADIO11:
			r = 255;
			g = 255;
			b = 0;
			break;
		}
		InvalidateRect(hDlg, &rect, FALSE);
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hDlg, &ps);
		GetClientRect(hDlg, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);

		if (Draw)
		{
			hBrush = CreateSolidBrush(RGB(r, g, b));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			if (cs == 0)
				Ellipse(hDC, xPos, yPos, xPos + 50, yPos + 50);
			else if (cs == 1)
				Rectangle(hDC, xPos, yPos, xPos + 50, yPos + 50);
			else
			{
				point[0].x = xPos + 25;
				point[0].y = yPos;
				point[1].x = xPos;
				point[1].y = yPos + 50;
				point[2].x = xPos + 50;
				point[2].y = yPos + 50;
				Polygon(hDC, point, 3);
			}

			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
		}

		GetClientRect(hDlg, &bufferRT);
		BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(hDC);
		EndPaint(hDlg, &ps);
		break;
	} 
	return 0;
}
