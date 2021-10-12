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

int zxcv = 0;

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
		0, 0, 418, 800, NULL, (HMENU)NULL, hInstance, NULL);

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

void Animation(int xPos, int yPos, HDC hDC, int cs, Block block[16][8])
{
	HDC memDC;
	HBITMAP BAR[2], CORNER[4];
	static int count;
	int i;

	count++;
	count = count % 4;
	BAR[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	BAR[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	CORNER[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	CORNER[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	CORNER[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	CORNER[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));

	memDC = CreateCompatibleDC(hDC);

	switch (cs)
	{
	case 0:
		(HBITMAP)SelectObject(memDC, BAR[0]);
		StretchBlt(hDC, xPos, yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
		break;
	case 1:
		(HBITMAP)SelectObject(memDC, BAR[1]);
		StretchBlt(hDC, xPos, yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
		break;
	case 2:
		(HBITMAP)SelectObject(memDC, CORNER[0]);
		StretchBlt(hDC, xPos, yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
		break;
	case 3:
		(HBITMAP)SelectObject(memDC, CORNER[1]);
		StretchBlt(hDC, xPos, yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
		break;
	case 4:
		(HBITMAP)SelectObject(memDC, CORNER[2]);
		StretchBlt(hDC, xPos, yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
		break;
	case 5:
		(HBITMAP)SelectObject(memDC, CORNER[3]);
		StretchBlt(hDC, xPos, yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
		break;
	default:
		break;
	}
	
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (block[i][j].cs != -1 && block[i][j].cs != 999)
			{
				switch (block[i][j].cs)
				{
				case 0:
					(HBITMAP)SelectObject(memDC, BAR[0]);
					StretchBlt(hDC, block[i][j].xPos, block[i][j].yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
					break;
				case 1:
					(HBITMAP)SelectObject(memDC, BAR[1]);
					StretchBlt(hDC, block[i][j].xPos, block[i][j].yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
					break;
				case 2:
					(HBITMAP)SelectObject(memDC, CORNER[0]);
					StretchBlt(hDC, block[i][j].xPos, block[i][j].yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
					break;
				case 3:
					(HBITMAP)SelectObject(memDC, CORNER[1]);
					StretchBlt(hDC, block[i][j].xPos, block[i][j].yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
					break;
				case 4:
					(HBITMAP)SelectObject(memDC, CORNER[2]);
					StretchBlt(hDC, block[i][j].xPos, block[i][j].yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
					break;
				case 5:
					(HBITMAP)SelectObject(memDC, CORNER[3]);
					StretchBlt(hDC, block[i][j].xPos, block[i][j].yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
					break;
				default:
					break;
				}
			}
		}
	}


	DeleteObject(BAR[0]);
	DeleteObject(BAR[1]);
	DeleteObject(CORNER[0]);
	DeleteObject(CORNER[1]);
	DeleteObject(CORNER[2]);
	DeleteObject(CORNER[3]);
	DeleteDC(memDC);
}

void checkpipe(Block block[16][8])
{
	BOOL check1;
	for (int i = 0; i < 16; ++i)
	{
		check1 = TRUE;
		for (int j = 0; j < 8; ++j)
		{
			if (block[i][j].cs != 0)
				check1 = FALSE;
		}
		if (check1)
		{
			for (int j = i; j < 15; ++j)
			{
				for (int k = 0; k < 8; ++k)
				{
					block[j][k].cs = block[j + 1][k].cs;
				}
			}
			break;
		}
	}
}

void checkpipe2(Block block[16][8])
{
	BOOL check2;
	int left, Top;

	for (int i = 1; i < 16; ++i)
	{

		check2 = FALSE;
		for (int j = 0; j < 7; ++j)
		{
			if (block[i][j].cs == 4)
			{
				
				if (block[i][j + 1].cs == 5 && block[i - 1][j].cs == 3 && block[i - 1][j + 1].cs == 2)
				{
					check2 = TRUE;
					Top = i;
					left = j;
				}
			}
		}
		if (check2)
		{
			if (Top < 14)
			{
				for (int i = Top - 1; i < 14; ++i)
				{
					block[i][left].cs = block[i + 2][left].cs;
					block[i][left + 1].cs = block[i + 2][left + 1].cs;
				}
			}
			break;
		}
	}
}

BOOL checkpipe3(Block block[16][8])
{
	for (int i = 0; i < 8; ++i)
	{
		if (block[14][i].cs != -1)
			return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	static int xPos, yPos, cs;
	static Block block[16][8];
	static int Flag[4];
	static int status;
	int f;
	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 25, NULL);
		xPos = 150;
		yPos = 0;
		cs = -1;
		status = 4;
		Flag[0] = 0;
		Flag[1] = 1;
		Flag[2] = 2;
		Flag[3] = 3;

		for (int i = 0; i < 16; ++i)
		{
			for (int j = 0; j < 8; ++j)
				block[i][j].cs = -1;
		}

		for (int i = 0; i < 8; ++i)
		{
			block[0][i].xPos = 50 * i;
			block[0][i].yPos = 700;
			block[0][i].cs = 999;
		}

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			xPos -= 50;
			if (xPos < 0)
				xPos = 0;
			break;
		case VK_RIGHT:
			xPos += 50;
			if (xPos > 350)
				xPos = 350;
			break;
		case VK_SPACE:
			if (cs == 0)
				cs = 1;
			else if (cs == 1)
				cs = 0;
			else if (cs == 2)
				cs += 1;
			else if (cs == 3)
				cs += 1;
			else if (cs == 4)
				cs += 1;
			else if (cs == 5)
				cs = 2;
			break;
		}
		break;
	case WM_TIMER:
		if (cs == -1)
		{
			srand(time(NULL));
			f = rand() % status;
			cs = Flag[f];
			Flag[f] = Flag[status - 1];
			--status;
			if (status == 0)
			{
				status = 4;
				Flag[0] = 0;
				Flag[1] = 1;
				Flag[2] = 2;
				Flag[3] = 3;
			}

			xPos = 150;
			yPos = 0;
		}
		if (yPos > 700)
		{
			yPos = 0;
			cs = -1;
		}
		else
		{
			yPos += 10;
			for (int i = 0; i < 16; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					if (block[i][j].cs == 999 && yPos == block[i][j].yPos && xPos == block[i][j].xPos)
					{

						++zxcv;
						block[i][j].cs = cs;
						if (j < 8)
						{
							block[i + 1][j].cs = 999;
							block[i + 1][j].xPos = block[i][j].xPos;
							block[i + 1][j].yPos = block[i][j].yPos - 50;
							cs = -1;
						}


					}
				}
			}
		}

		checkpipe(block);
		checkpipe2(block);
		if (checkpipe3(block))
			PostQuitMessage(0);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		Animation(xPos, yPos, hDC, cs, block);

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
