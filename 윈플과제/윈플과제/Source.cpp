#include <Windows.h>
#include <math.h>
#include <time.h>
#include "resource.h"

#define PI 3.1415926535897

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"Window Programming Lab";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
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

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW,
		0, 0, 800, 800, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

struct Block
{
	int xPos, yPos, cs;
};

double getRadian(int num)
{
	return num * (PI / 180);
}

struct BULLET
{
	int X, Y, Angle, Direction;
	BOOL Rotate;
	BOOL Reloading;
};

void DrawCircle(HDC hDC, int X, int Y, int Radius)
{
	Ellipse(hDC, X - Radius, Y - Radius, X + Radius, Y + Radius);
}

void Animation(HDC hDC, Block Main, BULLET Bullet[6])
{
	HDC memDC;
	HBITMAP MAIN, BULLET[4];
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	MAIN = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));

	memDC = CreateCompatibleDC(hDC);

	(HBITMAP)SelectObject(memDC, MAIN);
	StretchBlt(hDC, Main.xPos, Main.yPos, 30, 30, memDC, 0, 0, 48, 48, SRCCOPY);


	DeleteObject(MAIN);
	DeleteDC(memDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	static Block Main;
	static Block Map[20][20];
	static BULLET Bullet[6];
	static int Level;
	int n;
	switch (iMessage) {
	case WM_CREATE:
		Main.xPos = 400;
		Main.yPos = 400;
		Main.cs = 1;
		for (int i = 0; i < 6; ++i)
		{
			Bullet[i].Angle = 60 * i;
			Bullet[i].Rotate = TRUE;
		}
		SetTimer(hWnd, 1, 25, NULL);
		SetTimer(hWnd, 2, 10, NULL);
		SetTimer(hWnd, 3, 500, NULL);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			for (int i = 0; i < 6; ++i)
			{
				Bullet[i].Angle += 3;
				Bullet[i].Angle = Bullet[i].Angle % 360;
			}
			break;
		case 2:
			for (int i = 0; i < 6; ++i)
			{
				if (!Bullet[i].Rotate)
				{
					switch (Bullet[i].Direction)
					{
					case 0:
						Bullet[i].Y -= 8;
						break;
					case 1:
						Bullet[i].X += 8;
						break;
					case 2:
						Bullet[i].Y += 8;
						break;
					case 3:
						Bullet[i].X -= 8;
					}
				}
			}
			break;
		default:
			break;
		}


		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'W':
			if (GetAsyncKeyState('A') & 0x8000)
				Main.xPos -= 8;
			if (GetAsyncKeyState('D') & 0x8000)
				Main.xPos += 8;
			Main.yPos -= 8;
			break;
		case 'A':
			if (GetAsyncKeyState('W') & 0x8000)
				Main.yPos -= 8;
			if (GetAsyncKeyState('S') & 0x8000)
				Main.yPos += 8;
			Main.xPos -= 8;
			break;
		case 'S':
			if (GetAsyncKeyState('A') & 0x8000)
				Main.xPos -= 8;
			if (GetAsyncKeyState('D') & 0x8000)
				Main.xPos += 8;
			Main.yPos += 8;
			break;
		case 'D':
			if (GetAsyncKeyState('W') & 0x8000)
				Main.yPos -= 8;
			if (GetAsyncKeyState('S') & 0x8000)
				Main.yPos += 8;
			Main.xPos += 8;
			break;
		case VK_LEFT:
			for (int i = 0; i < 6; ++i)
			{
				if (Bullet[i].Rotate)
				{
					Bullet[i].Rotate = FALSE;
					Bullet[i].Direction = 3;
					Bullet[i].X = Main.xPos + 15;
					Bullet[i].Y = Main.yPos + 15;
					break;
				}
			}
			break;
		case VK_RIGHT:
			for (int i = 0; i < 6; ++i)
			{
				if (Bullet[i].Rotate)
				{
					Bullet[i].Rotate = FALSE;
					Bullet[i].Direction = 1;
					Bullet[i].X = Main.xPos + 15;
					Bullet[i].Y = Main.yPos + 15;
					break;
				}
			}
			break;
		case VK_UP:
			for (int i = 0; i < 6; ++i)
			{
				if (Bullet[i].Rotate)
				{
					Bullet[i].Rotate = FALSE;
					Bullet[i].Direction = 0;
					Bullet[i].X = Main.xPos + 15;
					Bullet[i].Y = Main.yPos + 15;
					break;
				}
			}
			break;
		case VK_DOWN:
			for (int i = 0; i < 6; ++i)
			{
				if (Bullet[i].Rotate)
				{
					Bullet[i].Rotate = FALSE;
					Bullet[i].Direction = 2;
					Bullet[i].X = Main.xPos + 15;
					Bullet[i].Y = Main.yPos + 15;
					break;
				}
			}
			break;
		case 'Q':
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		Animation(hDC, Main, Bullet);

		GetClientRect(hWnd, &bufferRT);
		BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(hDC);
		EndPaint(hWnd, &ps);

		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
