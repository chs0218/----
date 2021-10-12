#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include "resource.h"

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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

struct Shape
{
	RECT rect;
	int Shape;
	int Red, Green, Blue;
};

void DrawGrid(HDC hDC)
{
	for (int i = 0; i <= 100; ++i)
	{
		MoveToEx(hDC, i * 8, 0, NULL);
		LineTo(hDC, i * 8, 800);
	}

	for (int i = 0; i <= 100; ++i)
	{
		MoveToEx(hDC, 0, i * 8, NULL);
		LineTo(hDC, 800, i * 8);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	static int mx, my, OldX, OldY, StartX, StartY;
	static HBRUSH hBrush, oldBrush;
	static HPEN hPen, oldPen;
	static BOOL GRID, DRAG, ELLIPSE, RECTANGLE, FREE;
	static int Red, Green, Blue;
	static Shape shape[100];
	static int ShapeNum;

	switch (iMessage) {
	case WM_CREATE:
		GRID = FALSE;
		DRAG = FALSE;
		ELLIPSE = TRUE;
		RECTANGLE = FALSE;
		FREE = FALSE;
		StartX = 0, StartY = 0, OldX = 0, OldY = 0;
		Red = 255;
		Green = 255;
		Blue = 255;
		ShapeNum = 0;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_COLOR_COLOR1:
			Red = 255;
			Green = 255;
			Blue = 255;
			break;
		case ID_COLOR_COLOR2:
			Red = 130;
			Green = 0;
			Blue = 0;
			break;
		case ID_COLOR_COLOR3:
			Red = 50;
			Green = 20;
			Blue = 250;
			break;
		case ID_COLOR_COLOR4:
			Red = 0;
			Green = 200;
			Blue = 80;
			break;
		case ID_COLOR_COLOR5:
			Red = 130;
			Green = 180;
			Blue = 50;
			break;
		case ID_COLOR_COLOR6:
			Red = 225;
			Green = 50;
			Blue = 145;
			break;
		case ID_SHAPE_ELLIPSE:
			ELLIPSE = TRUE;
			RECTANGLE = FALSE;
			FREE = FALSE;
			break;
		case ID_SHAPE_RECTANGLE:
			ELLIPSE = FALSE;
			RECTANGLE = TRUE;
			FREE = FALSE;
			break;
		case ID_SHAPE_FREE:
			ELLIPSE = FALSE;
			RECTANGLE = FALSE;
			FREE = TRUE;
			break;
		case ID_GRID_ON:
			GRID = TRUE;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_GRID_OFF:
			GRID = FALSE;
			InvalidateRect(hWnd, NULL, FALSE);
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


		if (GRID)
			DrawGrid(hDC);

		{
			SetROP2(hDC, R2_XORPEN);
			SelectObject(hDC, (HPEN)GetStockObject(BLACK_PEN));

		for (int i = 0; i < ShapeNum; ++i)
		{
			hBrush = CreateSolidBrush(RGB(shape[i].Red, shape[i].Green, shape[i].Blue));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			if (shape[i].Shape == 0)
				Ellipse(hDC, shape[i].rect.left, shape[i].rect.top, shape[i].rect.right, shape[i].rect.bottom);
			else if (shape[i].Shape == 1)
				Rectangle(hDC, shape[i].rect.left, shape[i].rect.top, shape[i].rect.right, shape[i].rect.bottom);


			if (shape[i].Shape == 0)
				Ellipse(hDC, shape[i].rect.left, shape[i].rect.top, shape[i].rect.right, shape[i].rect.bottom);
			else if (shape[i].Shape == 1)
				Rectangle(hDC, shape[i].rect.left, shape[i].rect.top, shape[i].rect.right, shape[i].rect.bottom);

			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
		}

		}
		GetClientRect(hWnd, &bufferRT);
		BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(hDC);
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		DRAG = TRUE;
		StartX = LOWORD(lParam);
		StartY = HIWORD(lParam);
		OldX= LOWORD(lParam);
		OldY = HIWORD(lParam);

		if (ELLIPSE || RECTANGLE)
		{
			if (ELLIPSE)
				shape[ShapeNum].Shape = 0;

			else 
				shape[ShapeNum].Shape = 1;

			shape[ShapeNum].rect.left = StartX;
			shape[ShapeNum].rect.top = StartY;
			shape[ShapeNum].Red = 255-Red;
			shape[ShapeNum].Green = 255-Green;
			shape[ShapeNum].Blue = 255-Blue;

		}
		break;

	case WM_MOUSEMOVE:
		hDC = GetDC(hWnd);

		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		if (mx >= 800 || my >= 800)
			break;

		hBrush = CreateSolidBrush(RGB(Red, Green, Blue));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		if (DRAG)
		{
			SetROP2(hDC, R2_XORPEN);
			SelectObject(hDC, (HPEN)GetStockObject(BLACK_PEN));



			if (ELLIPSE)
				Ellipse(hDC, StartX, StartY, OldX, OldY);

			else if (RECTANGLE)
				Rectangle(hDC, StartX, StartY, OldX, OldY);

			else if (FREE)
			{
				mx = mx / 8;
				mx *= 8;
				my = my / 8;
				my *= 8;
				Rectangle(hDC, mx, my, mx + 9, my + 9);
			}




			if (ELLIPSE)
				Ellipse(hDC, StartX, StartY, mx, my);

			else if (RECTANGLE)
				Rectangle(hDC, StartX, StartY, mx, my);


			

			OldX = mx, OldY = my;
		}


		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		ReleaseDC(hWnd, hDC);
		break;
	case WM_LBUTTONUP:
		DRAG = FALSE;
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (ELLIPSE || RECTANGLE)
		{
			shape[ShapeNum].rect.right = mx;
			shape[ShapeNum].rect.bottom = my;
			ShapeNum++;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}