#include <Windows.h>
#include <time.h>
#include "resource.h"
#define WIDTH 1601
#define HEIGHT 2397

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
		0, 0, 850, 567, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

void Animation(int* xPos, int* yPos, HDC hDC, int Direction, int size, int twin, int* Step, BOOL* SELECTION, int SelectedN)
{
	HDC memDC;
	HBITMAP RunBit, Mask, hBit;
	static int count;
	int i;

	count++;
	count = count % 4;
	RunBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	Mask= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));

	memDC = CreateCompatibleDC(hDC);
	hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_BACK));

	(HBITMAP)SelectObject(memDC, hBit);
	BitBlt(hDC, 0, 0, 850, 567, memDC, 0, 0, SRCCOPY);

	if (*SELECTION)
	{
		switch (*Step)
		{
		case 0:
			xPos[SelectedN] -= 10;
			yPos[SelectedN] -= 10;
			(HBITMAP)SelectObject(memDC, Mask);
			StretchBlt(hDC, xPos[SelectedN], yPos[SelectedN], size, size, memDC, WIDTH / 4, HEIGHT / 4 * (*Step), WIDTH / 4, HEIGHT / 4, SRCAND);
			(HBITMAP)SelectObject(memDC, RunBit);
			StretchBlt(hDC, xPos[SelectedN], yPos[SelectedN], size, size, memDC, WIDTH / 4, HEIGHT / 4 * (*Step), WIDTH / 4, HEIGHT / 4, SRCPAINT);
			++*Step;
			break;
		case 1:
			xPos[SelectedN] -= 10;
			yPos[SelectedN] -= 10;
			(HBITMAP)SelectObject(memDC, Mask);
			StretchBlt(hDC, xPos[SelectedN], yPos[SelectedN], size, size, memDC, WIDTH / 4, HEIGHT / 4 * (*Step), WIDTH / 4, HEIGHT / 4, SRCAND);
			(HBITMAP)SelectObject(memDC, RunBit);
			StretchBlt(hDC, xPos[SelectedN], yPos[SelectedN], size, size, memDC, WIDTH / 4, HEIGHT / 4 * (*Step), WIDTH / 4, HEIGHT / 4, SRCPAINT);
			++*Step;
			break;
		case 2:
			xPos[SelectedN] -= 10;
			yPos[SelectedN] -= 10;
			(HBITMAP)SelectObject(memDC, Mask);
			StretchBlt(hDC, xPos[SelectedN], yPos[SelectedN], size, size, memDC, WIDTH / 4, HEIGHT / 4 * (*Step), WIDTH / 4, HEIGHT / 4, SRCAND);
			(HBITMAP)SelectObject(memDC, RunBit);
			StretchBlt(hDC, xPos[SelectedN], yPos[SelectedN], size, size, memDC, WIDTH / 4, HEIGHT / 4 * (*Step), WIDTH / 4, HEIGHT / 4, SRCPAINT);
			++*Step;
			break;
		case 3:
			xPos[SelectedN] -= 10;
			yPos[SelectedN] -= 10;
			(HBITMAP)SelectObject(memDC, Mask);
			StretchBlt(hDC, xPos[SelectedN], yPos[SelectedN], size, size, memDC, WIDTH / 4 * 2, HEIGHT / 4 * (*Step), WIDTH / 4, HEIGHT / 4, SRCAND);
			(HBITMAP)SelectObject(memDC, RunBit);
			StretchBlt(hDC, xPos[SelectedN], yPos[SelectedN], size, size, memDC, WIDTH / 4 * 2, HEIGHT / 4 * (*Step), WIDTH / 4, HEIGHT / 4, SRCPAINT);
			*Step = 0;
			*SELECTION = FALSE;
			break;
		default:
			break;
		}

		(HBITMAP)SelectObject(memDC, Mask);
		for (int i = 0; i < twin; ++i)
		{
			if (i != SelectedN)
				StretchBlt(hDC, xPos[i], yPos[i], size, size, memDC, WIDTH / 4 * count, HEIGHT / 4 * Direction, WIDTH / 4, HEIGHT / 4, SRCAND);
		}
		(HBITMAP)SelectObject(memDC, RunBit);
		for (int i = 0; i < twin; ++i)
		{
			if (i != SelectedN)
				StretchBlt(hDC, xPos[i], yPos[i], size, size, memDC, WIDTH / 4 * count, HEIGHT / 4 * Direction, WIDTH / 4, HEIGHT / 4, SRCPAINT);
		}
	}

	else
	{
		(HBITMAP)SelectObject(memDC, Mask);
		for (int i = 0; i < twin; ++i)
			StretchBlt(hDC, xPos[i], yPos[i], size, size, memDC, WIDTH / 4 * count, HEIGHT / 4 * Direction, WIDTH / 4, HEIGHT / 4, SRCAND);
		(HBITMAP)SelectObject(memDC, RunBit);
		for (int i = 0; i < twin; ++i)
			StretchBlt(hDC, xPos[i], yPos[i], size, size, memDC, WIDTH / 4 * count, HEIGHT / 4 * Direction, WIDTH / 4, HEIGHT / 4, SRCPAINT);
	}

	DeleteObject(RunBit);
	DeleteDC(memDC);
	DeleteObject(hBit);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	static int xPos[5], yPos[5];
	static int tmpx[5], tmpy[5];
	static int twin;
	static int size;
	static int Direction;
	static int step;
	static int SelectedN;
	static BOOL SELECTION, SELECTION2, SIZEUP, SIZEDOWN, JUMP;
	BOOL PASS;
	int mx, my;

	switch (iMessage) {
	case WM_CREATE:
		xPos[0] = 400;
		yPos[0] = 200;
		twin = 1;
		size = 100;
		Direction = 0;
		step = 0;
		SelectedN = -1;
		SIZEUP = FALSE;
		SIZEDOWN = FALSE;
		JUMP = FALSE;
		SELECTION = FALSE;
		SELECTION2 = FALSE;
		SetTimer(hWnd, 1, 100, NULL);
		break;
	case WM_TIMER:
		if (SIZEUP)
		{
			switch (step)
			{
			case 0:
				size += 10;
				++step;
				break;
			case 1:
				size += 10;
				++step;
				break;
			case 2:
				size += 10;
				++step;
				break;
			case 3:
				size += 10;
				++step;
				break;
			case 4:
				size -= 10;
				++step;
				break;
			case 5:
				size -= 10;
				++step;
				break;
			case 6:
				size -= 10;
				++step;
			case 7:
				size -= 10;
				step = 0;
				SIZEUP = FALSE;
				break;
			default:
				break;
			}
		}

		if (SIZEDOWN)
		{
			switch (step)
			{
			case 0:
				size -= 10;
				++step;
				break;
			case 1:
				size -= 10;
				++step;
				break;
			case 2:
				size -= 10;
				++step;
				break;
			case 3:
				size -= 10;
				++step;
				break;
			case 4:
				size += 10;
				++step;
				break;
			case 5:
				size += 10;
				++step;
				break;
			case 6:
				size += 10;
				++step;
			case 7:
				size += 10;
				step = 0;
				SIZEDOWN = FALSE;
				break;
			default:
				break;
			}
		}

		if (JUMP)
		{
			switch (step)
			{
			case 0:
				for (int i = 0; i < twin; ++i)
					yPos[i] -= 20;
				++step;
				break;
			case 1:
				for (int i = 0; i < twin; ++i)
					yPos[i] -= 20;
				++step;
				break;
			case 2:
				for (int i = 0; i < twin; ++i)
					yPos[i] -= 20;
				++step;
				break;
			case 3:
				for (int i = 0; i < twin; ++i)
					yPos[i] -= 20;
				++step;
				break;
			case 4:
				for (int i = 0; i < twin; ++i)
					yPos[i] += 20;
				++step;
				break;
			case 5:
				for (int i = 0; i < twin; ++i)
					yPos[i] += 20;
				++step;
				break;
			case 6:
				for (int i = 0; i < twin; ++i)
					yPos[i] += 20;
				++step;
			case 7:
				for (int i = 0; i < twin; ++i)
					yPos[i] += 20;
				step = 0;
				JUMP = FALSE;
				break;
			default:
				break;
			}
		}
		if (SELECTION2)
		{
			switch (Direction)
			{
			case 1:
				for (int i = 0; i < twin; ++i)
				{
					yPos[i] -= 10;
					if (yPos[i] < 0)
						yPos[i] = 530;
					else if (yPos[i] == tmpy[i])
						SELECTION2 = FALSE;
				}
				break;
			case 0:
				for (int i = 0; i < twin; ++i)
				{
					yPos[i] += 10;
					if (yPos[i] > 430)
						yPos[i] = 0;
					else if (yPos[i] == tmpy[i])
						SELECTION2 = FALSE;
				}
				break;
			case 3:
				for (int i = 0; i < twin; ++i)
				{
					xPos[i] += 10;
					if (xPos[i] > 750)
						xPos[i] = 0;
					else if (xPos[i] == tmpx[i])
						SELECTION2 = FALSE;
				}
				break;
			case 2:
				for (int i = 0; i < twin; ++i)
				{
					xPos[i] -= 10;
					if (xPos[i] < 0)
						xPos[i] = 850;
					else if (xPos[i] == tmpx[i])
						SELECTION2 = FALSE;
				}
				break;
			default:
				break;
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			Direction = 1;
			for (int i = 0; i < twin; ++i)
			{
				yPos[i] -= 10;
				if (yPos[i] < 0)
					yPos[i] = 0;
			}
			SELECTION2 = FALSE;
			break;
		case VK_DOWN:
			Direction = 0;
			for (int i = 0; i < twin; ++i)
			{
				yPos[i] += 10;
				if (yPos[i] > 430)
					yPos[i] = 430;
			}
			SELECTION2 = FALSE;
			break;
		case VK_RIGHT:
			Direction = 3;
			for (int i = 0; i < twin; ++i)
			{
				xPos[i] += 10;
				if (xPos[i] > 750)
					xPos[i] = 750;
			}
			SELECTION2 = FALSE;
			break;
		case VK_LEFT:
			Direction = 2;
			for (int i = 0; i < twin; ++i)
			{
				xPos[i] -= 10;
				if (xPos[i] < 0)
					xPos[i] = 0;
			}
			SELECTION2 = FALSE;
			break;
		case 'E':
			SIZEUP = TRUE;
			break;

		case 'S':
			SIZEDOWN = TRUE;
			break;

		case 'J':
			JUMP = TRUE;
			break;

		case 'T':
			if (twin < 5)
			{
				twin += 1;
				srand(time(NULL));

				while (1)
				{
					PASS = TRUE;
					xPos[twin - 1] = rand() % 750;
					yPos[twin - 1] = rand() % 430;

					for (int i = 0; i < twin - 1; ++i)
					{
						if (xPos[i] - 100 < xPos[twin - 1] && xPos[twin - 1] < xPos[i] + 100 && yPos[i] - 100 < yPos[twin - 1] && yPos[twin - 1] < yPos[i] + 100)
							PASS = FALSE;
					}
					if (PASS)
						break;
				}
			}
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

		Animation(xPos, yPos, hDC, Direction, size, twin, &step, &SELECTION, SelectedN);

		GetClientRect(hWnd, &bufferRT);
		BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(hDC);
		EndPaint(hWnd, &ps);

		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		for (int i = 0; i < twin; ++i)
		{
			if (xPos[i] < mx&&mx < xPos[i] + 100 && yPos[i] < my&&my < yPos[i] + 100)
			{
				SELECTION = TRUE;
				SelectedN = i;
			}
		}
		break;

	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		for (int i = 0; i < twin; ++i)
		{
			if (xPos[i] < mx&&mx < xPos[i] + 100 && yPos[i] < my&&my < yPos[i] + 100)
			{
				SELECTION2 = TRUE;
				for (int i = 0; i < twin; ++i)
				{
					tmpx[i] = xPos[i];
					tmpy[i] = yPos[i];
				}
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
