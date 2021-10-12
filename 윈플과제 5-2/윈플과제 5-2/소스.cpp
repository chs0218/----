#include <Windows.h>
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
		0, 0, 1700, 900, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

struct Picture {
	int x, y;
};

struct PictureBoard {
	int Leftx, Lefty, Selected;
	int Rightx, Righty;
	BOOL Able;
};

void DrawPictureBoard(HDC hDC, int DivideNum)
{
	int x = 900 / (DivideNum + 1), y = 800 / (DivideNum + 1);
	for (int i = 0; i < DivideNum + 1; ++i)
	{
		
		MoveToEx(hDC, 900 + x*i, 0, NULL);
		LineTo(hDC, 900 + x * i, y*DivideNum);
	}

	for (int i = 0; i < DivideNum + 1; ++i)
	{

		MoveToEx(hDC, 900, y*i, NULL);
		LineTo(hDC, 900 + x * DivideNum, y*i);
	}
}

void DrawLine(HDC hDC, int Width, int Height)
{
	int x = Width / 3, y = Height / 3;
	for (int i = 0; i < 4; ++i)
	{

		MoveToEx(hDC, x * i, 0, NULL);
		LineTo(hDC, x * i, Height);
	}

	for (int i = 0; i < 4; ++i)
	{

		MoveToEx(hDC, 0, y*i, NULL);
		LineTo(hDC, Width, y*i);
	}
}

BOOL InPicture(Picture picture[], int num, int mx, int my, int Width, int Height, int DivideNum)
{
	if (picture[num].x < mx&&mx < picture[num].x + (Width / DivideNum) && picture[num].y < my&&my < picture[num].y + (Height / DivideNum))
		return TRUE;
	else
		return FALSE;
}

BOOL InBoard(PictureBoard Board[], int num, int mx, int my)
{
	if (Board[num].Leftx < mx&&mx < Board[num].Rightx && Board[num].Lefty < my&&my < Board[num].Righty)
		return TRUE;
	else
		return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	static HDC memDC;
	static HDC hDC, mem1DC, mem2DC;
	PAINTSTRUCT ps;
	static HBITMAP hBit1, hBit2, oldBit1, oldBit2, hBitmap;
	static int DivideNum;
	static Picture picture[9];
	static PictureBoard Board[25];
	static int SelectedN, SelectedCase;
	static BOOL Select, Select2;
	static PictureBoard cstBoard[25];
	
	int mx, my;
	switch (iMessage) {
	case WM_CREATE:
		hBit2 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				picture[3 * i + j].x = 411 / 3 * j;
				picture[3 * i + j].y = 432 / 3 * i;
			}

		}

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				Board[3 * i + j].Leftx = 900 + 225 * j;
				Board[3 * i + j].Lefty = 200 * i;
				Board[3 * i + j].Rightx = 900 + 225 * (j + 1);
				Board[3 * i + j].Righty = 200 * (i + 1);

			}
		}

		for (int i = 0; i < 25; ++ i)
		{
			Board[i].Selected = -1;
			Board[i].Able = FALSE;
		}
		

		for (int i = 0; i < 25; ++i)
		{
			cstBoard[i].Leftx = Board[i].Leftx;
			cstBoard[i].Lefty = Board[i].Lefty;
			cstBoard[i].Rightx = Board[i].Rightx;
			cstBoard[i].Righty = Board[i].Righty;

		}
		Select = FALSE;
		Select2 = FALSE;
		DivideNum = 3;
		SelectedN = -1;
		break;

	case WM_KEYDOWN:
		if (wParam == '1')
		{
			DivideNum = 1;

			for (int i = 0; i < DivideNum; ++i)
			{
				for (int j = 0; j < DivideNum; ++j)
				{
					Board[DivideNum * i + j].Leftx = 900 + ((900 / (DivideNum + 1)) * j);
					Board[DivideNum * i + j].Lefty = (800 / (DivideNum + 1)) * i;
					Board[DivideNum * i + j].Rightx = 900 + ((900 / (DivideNum + 1)) * (j + 1));
					Board[DivideNum * i + j].Righty = (800 / (DivideNum + 1)) * (i + 1);
					Board[DivideNum * i + j].Selected = -1;
				}

			}

			for (int i = 0; i < 25; ++i)
			{
				cstBoard[i].Leftx = Board[i].Leftx;
				cstBoard[i].Lefty = Board[i].Lefty;
				cstBoard[i].Rightx = Board[i].Rightx;
				cstBoard[i].Righty = Board[i].Righty;

			}
			for (int i = 0; i < 25; ++i)
			{
				Board[i].Selected = -1;
			}
		}

		else if (wParam == '2')
		{
			DivideNum = 2;

			for (int i = 0; i < DivideNum; ++i)
			{
				for (int j = 0; j < DivideNum; ++j)
				{
					Board[DivideNum * i + j].Leftx = 900 + ((900 / (DivideNum + 1)) * j);
					Board[DivideNum * i + j].Lefty = (800 / (DivideNum + 1)) * i;
					Board[DivideNum * i + j].Rightx = 900 + ((900 / (DivideNum + 1)) * (j + 1));
					Board[DivideNum * i + j].Righty = (800 / (DivideNum + 1)) * (i + 1);
					Board[DivideNum * i + j].Selected = -1;

				}

				

			}
			for (int i = 0; i < 25; ++i)
			{
				cstBoard[i].Leftx = Board[i].Leftx;
				cstBoard[i].Lefty = Board[i].Lefty;
				cstBoard[i].Rightx = Board[i].Rightx;
				cstBoard[i].Righty = Board[i].Righty;

			}
			for (int i = 0; i < 25; ++i)
			{
				Board[i].Selected = -1;
			}
		}

		else if (wParam == '3')
		{
			DivideNum = 3;

			for (int i = 0; i < DivideNum; ++i)
			{
				for (int j = 0; j < DivideNum; ++j)
				{
					Board[DivideNum * i + j].Leftx = 900 + ((900 / (DivideNum + 1)) * j);
					Board[DivideNum * i + j].Lefty = (800 / (DivideNum + 1)) * i;
					Board[DivideNum * i + j].Rightx = 900 + ((900 / (DivideNum + 1)) * (j + 1));
					Board[DivideNum * i + j].Righty = (800 / (DivideNum + 1)) * (i + 1);
					Board[DivideNum * i + j].Selected = -1;

				}

				

			}
			for (int i = 0; i < 25; ++i)
			{
				cstBoard[i].Leftx = Board[i].Leftx;
				cstBoard[i].Lefty = Board[i].Lefty;
				cstBoard[i].Rightx = Board[i].Rightx;
				cstBoard[i].Righty = Board[i].Righty;

			}
			for (int i = 0; i < 25; ++i)
			{
				Board[i].Selected = -1;
			}
		}

		else if (wParam == '4')
		{
			DivideNum = 4;

			for (int i = 0; i < DivideNum; ++i)
			{
				for (int j = 0; j < DivideNum; ++j)
				{
					Board[DivideNum * i + j].Leftx = 900 + ((900 / (DivideNum + 1)) * j);
					Board[DivideNum * i + j].Lefty = (800 / (DivideNum + 1)) * i;
					Board[DivideNum * i + j].Rightx = 900 + ((900 / (DivideNum + 1)) * (j + 1));
					Board[DivideNum * i + j].Righty = (800 / (DivideNum + 1)) * (i + 1);
					Board[DivideNum * i + j].Selected = -1;

				}

				

			}
			for (int i = 0; i < 25; ++i)
			{
				cstBoard[i].Leftx = Board[i].Leftx;
				cstBoard[i].Lefty = Board[i].Lefty;
				cstBoard[i].Rightx = Board[i].Rightx;
				cstBoard[i].Righty = Board[i].Righty;

			}
			for (int i = 0; i < 25; ++i)
			{
				Board[i].Selected = -1;
			}
		}

		else if (wParam == '5')
		{
			DivideNum = 5;

			for (int i = 0; i < DivideNum; ++i)
			{
				for (int j = 0; j < DivideNum; ++j)
				{
					Board[DivideNum * i + j].Leftx = 900 + ((900 / (DivideNum + 1)) * j);
					Board[DivideNum * i + j].Lefty = (800 / (DivideNum + 1)) * i;
					Board[DivideNum * i + j].Rightx = 900 + ((900 / (DivideNum + 1)) * (j + 1));
					Board[DivideNum * i + j].Righty = (800 / (DivideNum + 1)) * (i + 1);
					Board[DivideNum * i + j].Selected = -1;

				}

				

			}
			for (int i = 0; i < 25; ++i)
			{
				cstBoard[i].Leftx = Board[i].Leftx;
				cstBoard[i].Lefty = Board[i].Lefty;
				cstBoard[i].Rightx = Board[i].Rightx;
				cstBoard[i].Righty = Board[i].Righty;

			}
			for (int i = 0; i < 25; ++i)
			{
				Board[i].Selected = -1;
			}
		}

		InvalidateRgn(hWnd, NULL, FALSE);

		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mem1DC = CreateCompatibleDC(hDC);
		memDC = CreateCompatibleDC(hDC);
		oldBit1 = (HBITMAP)SelectObject(mem1DC, hBit1);
		BitBlt(hDC, 0, 0, 1700, 900, mem1DC, 0, 0, SRCCOPY);
		
		SelectObject(memDC, hBitmap);
		DrawPictureBoard(hDC, DivideNum);

		for (int i = 0; i < DivideNum*DivideNum; ++i)
		{
			if (Board[i].Selected != -1)
			{
				StretchBlt(hDC, Board[i].Leftx, Board[i].Lefty, (Board[i].Rightx - Board[i].Leftx), (Board[i].Righty - Board[i].Lefty), memDC, picture[Board[i].Selected].x, picture[Board[i].Selected].y, 137, 144, SRCCOPY);

			}
		}

		DrawLine(hDC, 411, 432);
		DrawPictureBoard(hDC, DivideNum);

		SelectObject(mem1DC, oldBit1);
		DeleteDC(memDC);
		DeleteDC(mem2DC);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		for (int i = 0; i < 9; ++i)
		{
			if (InPicture(picture, i, mx, my, 411, 432, 3))
			{
				Select = TRUE;
				SelectedN = i;
			}
		}

		for (int i = 0; i < DivideNum*DivideNum; ++i)
		{
			if (Board[i].Able&&Board[i].Leftx < mx&&mx < Board[i].Leftx+20 && Board[i].Lefty < my&&my < Board[i].Lefty + 20)
			{
				Select2 = TRUE;
				SelectedN = i;
				SelectedCase = 1;
				break;
			}

			else if (Board[i].Able&&Board[i].Rightx - 20 < mx&&mx < Board[i].Rightx && Board[i].Lefty < my&&my < Board[i].Lefty + 20)
			{
				Select2 = TRUE;
				SelectedN = i;
				SelectedCase = 2;
				break;
			}

			else if (Board[i].Able&&Board[i].Leftx < mx&&mx < Board[i].Leftx + 20 && Board[i].Righty-20 < my&&my < Board[i].Righty)
			{
				Select2 = TRUE;
				SelectedN = i;
				SelectedCase = 3;
				break;
			}

			else if (Board[i].Able&&Board[i].Rightx - 20 < mx&&mx < Board[i].Rightx && Board[i].Righty - 20 < my&&my < Board[i].Righty)
			{
				Select2 = TRUE;
				SelectedN = i;
				SelectedCase = 4;
				break;

			}

		}

		break;
	case WM_LBUTTONUP:

		Select = FALSE;

		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		hDC = GetDC(hWnd);
		if (!(Select2))
		{
			for (int i = 0; i < DivideNum*DivideNum; ++i)
			{
				if (InBoard(Board, i, mx, my))
				{

					Board[i].Selected = SelectedN;
					Board[i].Able = TRUE;
				}
			}
		}

		else
		{
			for (int i = 0; i < DivideNum*DivideNum; ++i)
			{
				if (InBoard(cstBoard, i, mx, my))
				{
					switch (SelectedCase)
					{
					case 1:
						Board[SelectedN].Leftx = cstBoard[i].Leftx;
						Board[SelectedN].Lefty = cstBoard[i].Lefty;

						break;
					case 2:
						Board[SelectedN].Rightx = cstBoard[i].Rightx;
						Board[SelectedN].Lefty = cstBoard[i].Lefty;
						break;
					case 3:
						Board[SelectedN].Leftx = cstBoard[i].Leftx;
						Board[SelectedN].Righty = cstBoard[i].Righty;
						break;
					case 4:
						Board[SelectedN].Rightx = cstBoard[i].Rightx;
						Board[SelectedN].Righty = cstBoard[i].Righty;
						break;
					}
				}
			}
		}
		Select2 = FALSE;
		SelectedN = -1;

		ReleaseDC(hWnd, hDC);
		InvalidateRect(hWnd, NULL, FALSE);

		break;
	case WM_MOUSEMOVE:

		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		hDC = GetDC(hWnd);

		hBit1 = CreateCompatibleBitmap(hDC, 1700, 900);

		mem1DC = CreateCompatibleDC(hDC);
		mem2DC = CreateCompatibleDC(mem1DC);

		oldBit1 = (HBITMAP)SelectObject(mem1DC, hBit1);
		oldBit2 = (HBITMAP)SelectObject(mem2DC, hBit2);

		BitBlt(mem1DC, 0, 0, 1700, 900, mem2DC, 0, 0, SRCCOPY);

		SetBkMode(mem1DC, TRANSPARENT);
		if (Select)
			BitBlt(mem1DC, mx - 68, my - 72, 137, 144, mem2DC, picture[SelectedN].x, picture[SelectedN].y, SRCCOPY);

		if (Select2)
		{
			switch (SelectedCase)
			{
			case 1:
				Board[SelectedN].Leftx = mx;
				Board[SelectedN].Lefty = my;
				BitBlt(mem1DC, mx, my, (Board[SelectedN].Rightx - Board[SelectedN].Leftx), (Board[SelectedN].Righty - Board[SelectedN].Lefty), mem2DC, picture[Board[SelectedN].Selected].x, picture[Board[SelectedN].Selected].y, SRCCOPY);
				break;
			case 2:
				Board[SelectedN].Rightx = mx;
				Board[SelectedN].Lefty = my;
				BitBlt(mem1DC, mx - (Board[SelectedN].Rightx - Board[SelectedN].Leftx), my, (Board[SelectedN].Rightx - Board[SelectedN].Leftx), (Board[SelectedN].Righty - Board[SelectedN].Lefty), mem2DC, picture[Board[SelectedN].Selected].x, picture[Board[SelectedN].Selected].y, SRCCOPY);
				break;
			case 3:
				Board[SelectedN].Leftx = mx;
				Board[SelectedN].Righty = my;
				BitBlt(mem1DC, mx, my- (Board[SelectedN].Righty - Board[SelectedN].Lefty), (Board[SelectedN].Rightx - Board[SelectedN].Leftx), (Board[SelectedN].Righty - Board[SelectedN].Lefty), mem2DC, picture[Board[SelectedN].Selected].x, picture[Board[SelectedN].Selected].y, SRCCOPY);
				break;
			case 4:
				Board[SelectedN].Rightx = mx;
				Board[SelectedN].Righty = my;
				BitBlt(mem1DC, mx - (Board[SelectedN].Rightx - Board[SelectedN].Leftx), my - (Board[SelectedN].Righty - Board[SelectedN].Lefty), (Board[SelectedN].Rightx - Board[SelectedN].Leftx), (Board[SelectedN].Righty - Board[SelectedN].Lefty), mem2DC, picture[Board[SelectedN].Selected].x, picture[Board[SelectedN].Selected].y, SRCCOPY);
				break;
			}
		}

		SelectObject(mem2DC, oldBit2);
		DeleteDC(mem2DC);
		SelectObject(mem1DC, oldBit1);
		DeleteDC(mem1DC);
		ReleaseDC(hWnd, hDC);
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}