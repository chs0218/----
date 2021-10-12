#include <Windows.h>
#include <time.h>
#include "resource.h"

#define WIDTH 1601
#define HEIGHT 2397
#define WIDTH2 576
#define HEIGHT2 384

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
		0, 0, 850, 567, NULL, (HMENU)NULL, hInstance, NULL);

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


void Animation(int xPos, int yPos, HDC hDC, int Direction, Block block[5], Block mob[10], Block bullet[5], Block Effect[10])
{

	HDC memDC;
	HBITMAP RunBit, Mask, hBit;
	HBITMAP FOXBIT, FOXMASK, BLOCK, Bullet;
	HBITMAP EFFECT[4];
	static int count;
	static int count2;
	int count2x, count2y;
	count++;
	count2++;
	count = count % 4;
	count2 = count2 % 54;

	count2x = count2 % 9;
	count2y = count2 / 9;

	FOXMASK = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_FOXMASK));
	FOXBIT = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_FOXSPRITE));
	RunBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	Mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	BLOCK = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_BLOCK));
	Bullet = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_BULLET));
	EFFECT[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_EFFECT1));
	EFFECT[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_EFFECT2));
	EFFECT[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_EFFECT3));
	EFFECT[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_EFFECT4));

	memDC = CreateCompatibleDC(hDC);



	(HBITMAP)SelectObject(memDC, BLOCK);
	for (int i = 0; i < 7; ++i)
	{
		if (block[i].cs != -1)
			StretchBlt(hDC, block[i].xPos, block[i].yPos, 50, 50, memDC, 0, 0, 50, 50, SRCCOPY);
	}

	memDC = CreateCompatibleDC(hDC);
	{
		for (int i = 0; i < 10; ++i)
		{
			if (Effect[i].cs != -1)
			{
				switch (Effect[i].cs)
				{
				case 0:
					(HBITMAP)SelectObject(memDC, EFFECT[0]);
					StretchBlt(hDC, Effect[i].xPos, Effect[i].yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
					++Effect[i].cs;
					break;
				case 1:
					(HBITMAP)SelectObject(memDC, EFFECT[1]);
					StretchBlt(hDC, Effect[i].xPos, Effect[i].yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
					++Effect[i].cs;
					break;
				case 2:
					(HBITMAP)SelectObject(memDC, EFFECT[2]);
					StretchBlt(hDC, Effect[i].xPos, Effect[i].yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
					++Effect[i].cs;
					break;
				case 3:
					(HBITMAP)SelectObject(memDC, EFFECT[3]);
					StretchBlt(hDC, Effect[i].xPos, Effect[i].yPos, 50, 50, memDC, 0, 0, 48, 48, SRCCOPY);
					Effect[i].cs = -1;
					break;
				}
			}
		}
	}

	memDC = CreateCompatibleDC(hDC);

	(HBITMAP)SelectObject(memDC, Mask);
	StretchBlt(hDC, xPos, yPos, 40, 40, memDC, WIDTH / 4 * count, HEIGHT / 4 * Direction, WIDTH / 4, HEIGHT / 4, SRCAND);
	(HBITMAP)SelectObject(memDC, RunBit);
	StretchBlt(hDC, xPos, yPos, 40, 40, memDC, WIDTH / 4 * count, HEIGHT / 4 * Direction, WIDTH / 4, HEIGHT / 4, SRCPAINT);

	memDC = CreateCompatibleDC(hDC);
	(HBITMAP)SelectObject(memDC, FOXMASK);
	for (int i = 0; i < 10; ++i)
	{
		if (mob[i].cs != -1)
			StretchBlt(hDC, mob[i].xPos, mob[i].yPos, 50, 50, memDC, WIDTH2 / 9 * count2x, HEIGHT2 / 6 * count2y, WIDTH2 / 9, HEIGHT2 / 6, SRCAND);
	}
	(HBITMAP)SelectObject(memDC, FOXBIT);
	for (int i = 0; i < 10; ++i)
	{
		if (mob[i].cs != -1)
			StretchBlt(hDC, mob[i].xPos, mob[i].yPos, 50, 50, memDC, WIDTH2 / 9 * count2x, HEIGHT2 / 6 * count2y, WIDTH2 / 9, HEIGHT2 / 6, SRCPAINT);
	}

	(HBITMAP)SelectObject(memDC, Bullet);
	for (int i = 0; i < 5; ++i)
	{
		if (bullet[i].cs != -1)
			StretchBlt(hDC, bullet[i].xPos, bullet[i].yPos, 10, 10, memDC, 0, 0, 50, 50, SRCCOPY);
	}

	DeleteDC(memDC);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	static int xPos, yPos, Direction;
	static int blockn;
	static Block mob[10];
	static Block block[7];
	static Block bullet[5];
	static Block Effect[10];
	BOOL Out;
	int emdwkd; 
	static int tmpDirect;
	switch (iMessage) {
	case WM_CREATE:
		blockn = 7;
		xPos = 350;
		yPos = 200;
		tmpDirect = 0;
		Direction = 0;
		srand(time(NULL));
		for (int i = 0; i < 7; ++i)
		{
			block[i].cs = 0;

			while (1)
			{
				Out = TRUE;
				block[i].xPos = rand() % 700;
				block[i].yPos = rand() % 430;

				for (int j = 0; j < i; ++j)
				{
					if (block[j].xPos - 100 < block[i].xPos&&block[i].xPos < block[j].xPos + 100 && block[j].yPos - 100 < block[i].yPos&&block[i].yPos < block[j].yPos + 100)
						Out = FALSE;
				}

				if (Out)
					break;
				else
					continue;
			}
		}

		for (int i = 0; i < 10; ++i)
		{
			mob[i].cs = -1;
			Effect[i].cs = -1;
		}

		for (int i = 0; i < 5; ++i)
		{
			bullet[i].cs = -1;
		}
		SetTimer(hWnd, 1, 100, NULL);
		SetTimer(hWnd, 2, 1000, NULL);
		break;
	case WM_TIMER:
		if (wParam == 1)
		{
			switch (Direction)
			{
			case 1:
				yPos -= 10;
				if (yPos < 0)
					yPos = 530;
				break;
			case 0:
				yPos += 10;
				if (yPos > 430)
					yPos = 0;
				break;
			case 3:
				xPos += 10;
				if (xPos > 750)
					xPos = 0;
				break;
			case 2:
				xPos -= 10;
				if (xPos < 0)
					xPos = 850;
				break;
			default:
				break;
			}

			for (int i = 0; i < 10; ++i)
			{
				if (mob[i].cs != -1)
				{
					switch (tmpDirect)
					{
					case 1:
						mob[i].yPos -= 10;
						if (mob[i].yPos < 0)
							mob[i].yPos = 530;

						break;
					case 0:
						mob[i].yPos += 10;
						if (mob[i].yPos > 430)
							mob[i].yPos = 0;

						break;
					case 3:
						mob[i].xPos += 10;
						if (mob[i].xPos > 750)
							mob[i].xPos = 0;

						break;
					case 2:
						mob[i].xPos -= 10;
						if (mob[i].xPos < 0)
							mob[i].xPos = 850;
						break;
					default:
						break;
					}

					++tmpDirect;

					if (tmpDirect > 3)
					{
						srand(time(NULL));

						tmpDirect = rand() % 4;
					}
				}
			}

			for (int i = 0; i < 5; ++i)
			{
				switch (bullet[i].cs)
				{
				case 1:
					bullet[i].yPos -= 10;
					if (bullet[i].yPos < 0)
					{
						bullet[i].cs = -1;
					}

					for (int j = 0; j < 7; ++j)
					{
						if (block[j].cs != -1 && block[j].xPos < bullet[i].xPos + 5 && bullet[i].xPos + 5 < block[j].xPos + 50 && block[j].yPos < bullet[i].yPos + 5 && bullet[i].yPos + 5 < block[j].yPos + 50)
						{
							++block[j].cs;
							if (block[j].cs >= 3)
							{
								block[j].cs = -1;
								--blockn;
							}
							bullet[i].cs = -1;
						}
					}

					for (int j = 0; j < 10; ++j)
					{
						if (mob[j].cs != -1 && mob[j].xPos < bullet[i].xPos + 5 && bullet[i].xPos + 5 < mob[j].xPos + 50 && mob[j].yPos < bullet[i].yPos + 5 && bullet[i].yPos + 5 < mob[j].yPos + 50)
						{
							mob[j].cs = -1;
							bullet[i].cs = -1;
							for (int l = 0; l < 10; ++l)
							{
								if (Effect[l].cs == -1)
								{
									Effect[l].xPos = mob[j].xPos;
									Effect[l].yPos = mob[j].yPos;
									Effect[l].cs = 0;
									break;
								}
							}
						}
					}
					break;
				case 0:
					bullet[i].yPos += 10;
					if (bullet[i].yPos > 430)
					{
						bullet[i].cs = -1;
					}

					for (int j = 0; j < 7; ++j)
					{
						if (block[j].cs != -1 && block[j].xPos < bullet[i].xPos + 5 && bullet[i].xPos + 5 < block[j].xPos + 50 && block[j].yPos < bullet[i].yPos + 5 && bullet[i].yPos + 5 < block[j].yPos + 50)
						{
							++block[j].cs;
							if (block[j].cs >= 3)
							{
								block[j].cs = -1;
								--blockn;
							}
							bullet[i].cs = -1;
						}
					}
					for (int j = 0; j < 10; ++j)
					{
						if (mob[j].cs != -1 && mob[j].xPos < bullet[i].xPos + 5 && bullet[i].xPos + 5 < mob[j].xPos + 50 && mob[j].yPos < bullet[i].yPos + 5 && bullet[i].yPos + 5 < mob[j].yPos + 50)
						{
							mob[j].cs = -1;
							bullet[i].cs = -1;
							for (int l = 0; l < 10; ++l)
							{
								if (Effect[l].cs == -1)
								{
									Effect[l].xPos = mob[j].xPos;
									Effect[l].yPos = mob[j].yPos;
									Effect[l].cs = 0;
									break;
								}
							}
						}
					}
					break;
				case 3:
					bullet[i].xPos += 10;
					if (bullet[i].xPos > 750)
					{
						bullet[i].cs = -1;
					}

					for (int j = 0; j < 7; ++j)
					{
						if (block[j].cs != -1 && block[j].xPos < bullet[i].xPos + 5 && bullet[i].xPos + 5 < block[j].xPos + 50 && block[j].yPos < bullet[i].yPos + 5 && bullet[i].yPos + 5 < block[j].yPos + 50)
						{
							++block[j].cs;
							if (block[j].cs >= 3)
							{
								block[j].cs = -1;
								--blockn;
							}
							bullet[i].cs = -1;
						}
					}
					for (int j = 0; j < 10; ++j)
					{
						if (mob[j].cs != -1 && mob[j].xPos < bullet[i].xPos + 5 && bullet[i].xPos + 5 < mob[j].xPos + 50 && mob[j].yPos < bullet[i].yPos + 5 && bullet[i].yPos + 5 < mob[j].yPos + 50)
						{
							mob[j].cs = -1;
							bullet[i].cs = -1;
							for (int l = 0; l < 10; ++l)
							{
								if (Effect[l].cs == -1)
								{
									Effect[l].xPos = mob[j].xPos;
									Effect[l].yPos = mob[j].yPos;
									Effect[l].cs = 0;
									break;
								}
							}
						}
					}

					break;
				case 2:
					bullet[i].xPos -= 10;
					if (bullet[i].xPos < 0)
					{
						bullet[i].cs = -1;
					}
					for (int j = 0; j < 7; ++j)
					{
						if (block[j].cs != -1 && block[j].xPos < bullet[i].xPos + 5 && bullet[i].xPos + 5 < block[j].xPos + 50 && block[j].yPos < bullet[i].yPos + 5 && bullet[i].yPos + 5 < block[j].yPos + 50)
						{
							++block[j].cs;
							if (block[j].cs >= 3)
							{
								block[j].cs = -1;
								--blockn;
							}
							bullet[i].cs = -1;
						}
					}
					for (int j = 0; j < 10; ++j)
					{
						if (mob[j].cs != -1 && mob[j].xPos < bullet[i].xPos + 5 && bullet[i].xPos + 5 < mob[j].xPos + 50 && mob[j].yPos < bullet[i].yPos + 5 && bullet[i].yPos + 5 < mob[j].yPos + 50)
						{
							mob[j].cs = -1;
							bullet[i].cs = -1;
							for (int l = 0; l < 10; ++l)
							{
								if (Effect[l].cs == -1)
								{
									Effect[l].xPos = mob[j].xPos;
									Effect[l].yPos = mob[j].yPos;
									Effect[l].cs = 0;
									break;
								}
							}
						}
					}
					break;
				default:
					break;
				}
			}
		}

		if (wParam == 2)
		{
			if (blockn > 0)
			{
				for (int i = 0; i < 10; ++i)
				{
					if (mob[i].cs == -1)
					{
						while (1)
						{
							emdwkd = rand() % 7;

							if (block[emdwkd].cs != -1)
							{
								mob[i].xPos = block[emdwkd].xPos;
								mob[i].yPos = block[emdwkd].yPos;
								mob[i].cs = 0;
								break;
							}
						}
						break;
					}
				}
			}

		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			Direction = 3;
			break;

		case VK_LEFT:
			Direction = 2;
			break;

		case VK_UP:
			Direction = 1;
			break;

		case VK_DOWN:
			Direction = 0;
			break;

		case VK_SPACE:
			for (int i = 0; i < 5; ++i)
			{
				if (bullet[i].cs == -1)
				{
					bullet[i].xPos = xPos + 20;
					bullet[i].yPos = yPos + 20;
					bullet[i].cs = Direction;
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

		Animation(xPos, yPos, hDC, Direction, block, mob, bullet, Effect);

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
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
