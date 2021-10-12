#include <Windows.h>

#include <math.h>
#include <stdio.h>
#include <time.h>
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

struct Picture {
	int num;
	int x, y;
};

void Swap(Picture* A, Picture* B)
{
	Picture tmp;
	tmp.num = (*A).num;
	(*A).num = (*B).num;
	(*B).num = tmp.num;
}

BOOL InPicture(Picture picture[], int num, int mx, int my, int Width, int Height, int DivideNum)
{
	if (picture[num].x < mx&&mx < picture[num].x + (Width / DivideNum) && picture[num].y < my&&my < picture[num].y + (Height / DivideNum))
		return TRUE;
	else
		return FALSE;
}

void printpicture(HDC hDC, Picture picture[], int n, int WIDTH, int HEIGHT, int DivideNum, HDC memDC, int distanceX, int distanceY)
{
	switch (picture[n].num)
	{
	case 0:
		BitBlt(hDC, picture[n].x+distanceX, picture[n].y +distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, 0, SRCCOPY);
		break;
	case 1:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, 0, SRCCOPY);

		break;
	case 2:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, 0, SRCCOPY);

		break;
	case 3:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum, SRCCOPY);

		break;
	case 4:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum, SRCCOPY);

		break;
	case 5:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum, SRCCOPY);

		break;
	case 6:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum * 2, SRCCOPY);

		break;
	case 7:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum * 2, SRCCOPY);

		break;
	case 8:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum * 2, SRCCOPY);

		break;
	case 9:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, 0, SRCCOPY);

		break;
	case 10:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum, SRCCOPY);

		break;
	case 11:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum * 2, SRCCOPY);

		break;
	case 12:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum * 3, SRCCOPY);

		break;
	case 13:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum * 3, SRCCOPY);

		break;
	case 14:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum * 3, SRCCOPY);

		break;
	case 15:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum * 3, SRCCOPY);

		break;
	case 16:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum * 4, SRCCOPY);

		break;
	case 17:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum * 4, SRCCOPY);

		break;
	case 18:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum * 4, SRCCOPY);

		break;
	case 19:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum * 4, SRCCOPY);

		break;
	case 20:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, 0, SRCCOPY);

		break;
	case 21:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum, SRCCOPY);

		break;
	case 22:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum * 2, SRCCOPY);

		break;
	case 23:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum * 3, SRCCOPY);

		break;
	case 24:
		BitBlt(hDC, picture[n].x + distanceX, picture[n].y + distanceY, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum * 4, SRCCOPY);
		break;
	default:
		break;
	}
}

BOOL Clear(const Picture picture[], int DivideNum)
{
	BOOL clear = TRUE;
	for (int i = 0; i < DivideNum*DivideNum; ++i)
	{
		if (picture[i].num == 30)
			DivideNum = DivideNum;

		else if (picture[i].num != i)
			clear = FALSE;
	}
	return clear;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	int y = 40;

	char hello[100];
	static HDC hDC, memDC;
	PAINTSTRUCT ps;
	static HBITMAP hBitmap;
	static int DivideNum;
	int Judge, Total;
	static int flag[25];
	static BOOL CmdF, First, CmdS;
	int n, mx, my;
	static int num = 0;
	static BOOL PictureNum;
	static Picture picture[25];
	static int Blank;
	static int WIDTH = 822, HEIGHT = 862;
	switch (iMessage) {
	case WM_CREATE:
		hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		DivideNum = 4;
		for (int i = 0; i < 25; ++i)
			flag[i] = i;
		CmdF = FALSE;
		CmdS = FALSE;
		First = TRUE;
		PictureNum = FALSE;
		break;
	case WM_KEYDOWN:

		if (wParam == 'F')
		{
			if (CmdF)
				CmdF = FALSE;
			else
				CmdF = TRUE;

			InvalidateRgn(hWnd, NULL, TRUE);
		}

		else if (wParam == VK_RIGHT)
		{
			if (PictureNum)
			{
				hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
				PictureNum = FALSE;
				WIDTH = 822, HEIGHT = 862;
			}

			else
			{
				hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
				PictureNum = TRUE;
				WIDTH = 743, HEIGHT = 743;
			}

			DivideNum = 4;
			for (int i = 0; i < 25; ++i)
				flag[i] = i;
			CmdS = FALSE;
			First = TRUE;
			InvalidateRgn(hWnd, NULL, TRUE);

		}

		else if (wParam == 'S')
		{
			if (!CmdS)
			{
				srand(time(NULL));
				Judge = rand() % DivideNum*DivideNum;
				num = Judge;
				Blank = picture[Judge].num;
				picture[Judge].num = 30;
				CmdS = TRUE;
				InvalidateRgn(hWnd, NULL, TRUE);
			}
		}
		else if (wParam == '2')
		{
			hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
			PictureNum = TRUE;
			WIDTH = 743, HEIGHT = 743;
			DivideNum = 4;
			for (int i = 0; i < 25; ++i)
				flag[i] = i;
			CmdS = FALSE;
			First = TRUE;
			InvalidateRgn(hWnd, NULL, TRUE);
		}

		else if (wParam == '1')
		{
			hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
			PictureNum = FALSE;
			WIDTH = 822, HEIGHT = 862;
			DivideNum = 4;
			for (int i = 0; i < 25; ++i)
				flag[i] = i;
			CmdS = FALSE;
			First = TRUE;
			InvalidateRgn(hWnd, NULL, TRUE);
		}

		else if (wParam == '3')
		{
			DivideNum = 3;
			for (int i = 0; i < 25; ++i)
				flag[i] = i;
			CmdS = FALSE;
			First = TRUE;
			InvalidateRgn(hWnd, NULL, TRUE);
		}

		else if (wParam == '4')
		{
			DivideNum = 4;
			for (int i = 0; i < 25; ++i)
				flag[i] = i;
			CmdS = FALSE;
			First = TRUE;
			InvalidateRgn(hWnd, NULL, TRUE);
		}

		else if (wParam == '5')
		{
			;
			DivideNum = 5;
			for (int i = 0; i < 25; ++i)
				flag[i] = i;
			CmdS = FALSE;
			First = TRUE;
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		memDC = CreateCompatibleDC(hDC);
		SelectObject(memDC, hBitmap);
		Total = DivideNum * DivideNum;
		n = 0;

		if (First)
		{
			for (int i = 0; i < DivideNum; ++i)
			{
				for (int j = 0; j < DivideNum; ++j)
				{
					srand(time(NULL));

					Judge = rand() % Total;
					picture[n].num = flag[Judge];
					picture[n].x = WIDTH / DivideNum * j;
					picture[n].y = HEIGHT / DivideNum * i;
					switch (flag[Judge])
					{
					case 0:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, 0, SRCCOPY);
						break;
					case 1:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, 0, SRCCOPY);

						break;
					case 2:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, 0, SRCCOPY);

						break;
					case 3:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum, SRCCOPY);

						break;
					case 4:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum, SRCCOPY);

						break;
					case 5:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum, SRCCOPY);

						break;
					case 6:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum * 2, SRCCOPY);

						break;
					case 7:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum * 2, SRCCOPY);

						break;
					case 8:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum * 2, SRCCOPY);

						break;
					case 9:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, 0, SRCCOPY);

						break;
					case 10:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum, SRCCOPY);

						break;
					case 11:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum * 2, SRCCOPY);

						break;
					case 12:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum * 3, SRCCOPY);

						break;
					case 13:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum * 3, SRCCOPY);

						break;
					case 14:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum * 3, SRCCOPY);

						break;
					case 15:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum * 3, SRCCOPY);

						break;
					case 16:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum * 4, SRCCOPY);

						break;
					case 17:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum * 4, SRCCOPY);

						break;
					case 18:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum * 4, SRCCOPY);

						break;
					case 19:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum * 4, SRCCOPY);

						break;
					case 20:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, 0, SRCCOPY);

						break;
					case 21:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum, SRCCOPY);

						break;
					case 22:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum * 2, SRCCOPY);

						break;
					case 23:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum * 3, SRCCOPY);

						break;
					case 24:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum * 4, SRCCOPY);

						break;
					default:
						break;
					}
					flag[Judge] = flag[Total - 1];
					Total -= 1;
					++n;
				}
			}
			First = FALSE;
		}

		else
		{
			for (int i = 0; i < DivideNum; ++i)
			{
				for (int j = 0; j < DivideNum; ++j)
				{
					switch (picture[n].num)
					{
					case 0:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, 0, SRCCOPY);
						break;
					case 1:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, 0, SRCCOPY);

						break;
					case 2:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, 0, SRCCOPY);

						break;
					case 3:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum, SRCCOPY);

						break;
					case 4:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum, SRCCOPY);

						break;
					case 5:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum, SRCCOPY);

						break;
					case 6:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum * 2, SRCCOPY);

						break;
					case 7:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum * 2, SRCCOPY);

						break;
					case 8:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum * 2, SRCCOPY);

						break;
					case 9:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, 0, SRCCOPY);

						break;
					case 10:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum, SRCCOPY);

						break;
					case 11:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum * 2, SRCCOPY);

						break;
					case 12:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum * 3, SRCCOPY);

						break;
					case 13:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum * 3, SRCCOPY);

						break;
					case 14:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum * 3, SRCCOPY);

						break;
					case 15:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum * 3, SRCCOPY);

						break;
					case 16:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, 0, HEIGHT / DivideNum * 4, SRCCOPY);

						break;
					case 17:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 2, HEIGHT / DivideNum * 4, SRCCOPY);

						break;
					case 18:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 3, HEIGHT / DivideNum * 4, SRCCOPY);

						break;
					case 19:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum * 4, SRCCOPY);

						break;
					case 20:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, 0, SRCCOPY);

						break;
					case 21:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum, SRCCOPY);

						break;
					case 22:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum * 2, SRCCOPY);

						break;
					case 23:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum * 4, HEIGHT / DivideNum * 3, SRCCOPY);

						break;
					case 24:
						BitBlt(hDC, WIDTH / DivideNum * j, HEIGHT / DivideNum * i, WIDTH / DivideNum, HEIGHT / DivideNum, memDC, WIDTH / DivideNum, HEIGHT / DivideNum * 4, SRCCOPY);
						break;
					default:
						break;
					}
					n += 1;
				}
			}
		}

		if (Clear(picture, DivideNum))
			TextOutA(hDC, 500, 500, "완성 하셨습니다.", 16);

		if (CmdF)
			BitBlt(hDC, 0, 0, WIDTH, HEIGHT, memDC, 0, 0, SRCCOPY);
		DeleteDC(memDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		hDC = GetDC(hWnd);
		memDC = CreateCompatibleDC(hDC);
		SelectObject(memDC, hBitmap);

		if ((num + 1) % DivideNum != 0 && InPicture(picture, num + 1, mx, my, WIDTH, HEIGHT, DivideNum))
		{
			for (int i = 0; i > -210; i -= 10)
			{
				printpicture(hDC, picture, num + 1, WIDTH, HEIGHT, DivideNum, memDC, i, 0);
				Sleep(100);
			}
			Swap(&picture[num], &picture[num + 1]);

			num = num + 1;
		}

		else if (num >= DivideNum && InPicture(picture, num - DivideNum, mx, my, WIDTH, HEIGHT, DivideNum))
		{
			for (int i = 0; i < 210; i += 10)
			{
				printpicture(hDC, picture, num - DivideNum, WIDTH, HEIGHT, DivideNum, memDC, 0, i);
				Sleep(100);
			}
			Swap(&picture[num], &picture[num - DivideNum]);
			num = num - DivideNum;
		}

		else if (num < DivideNum*DivideNum - DivideNum && InPicture(picture, num + DivideNum, mx, my, WIDTH, HEIGHT, DivideNum))
		{
			for (int i = 0; i > -210; i -= 10)
			{
				printpicture(hDC, picture, num + DivideNum, WIDTH, HEIGHT, DivideNum, memDC, 0, i);
				Sleep(100);
			}
			Swap(&picture[num], &picture[num + DivideNum]);
			num = num + DivideNum;
		}

		else if (num%DivideNum != 0 && InPicture(picture, num - 1, mx, my, WIDTH, HEIGHT, DivideNum))
		{
			for (int i = 0; i < 210; i += 10)
			{
				printpicture(hDC, picture, num - 1, WIDTH, HEIGHT, DivideNum, memDC, i, 0);
				Sleep(100);
			}
			Swap(&picture[num], &picture[num - 1]);
			num = num - 1;
		}
		DeleteDC(memDC);
		ReleaseDC(hWnd, hDC);
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}