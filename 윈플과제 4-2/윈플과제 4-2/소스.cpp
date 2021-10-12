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
		0, 0, 1070, 1000, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

float LengthPts(int x1, int y1, int x2, int y2)
{
	int x0 = x2 - x1;
	int y0 = y2 - y1;
	return sqrt(x0*x0 + y0 * y0);
}

BOOL InCircle(int x, int y, int mx, int my, int BSIZE)
{
	if (LengthPts(x, y, mx, my) < BSIZE)
		return TRUE;
	else
		return FALSE;
}


BOOL IsCollision(int cx, int cy, int cr, int rx, int ry)
{
	if ((rx <= cx && cx <= rx + 80) || (ry <= cy && cy <= ry + 40))
	{
		RECT rcEX = {
			rx - cr,
			ry - cr,
			rx + 80 + cr,
			ry + 40 + cr
		};

		if ((rcEX.left < cx&&cx < rcEX.right) && (rcEX.top < cy&&cy < rcEX.bottom))
			return TRUE;
	}

	else
	{
		if (InCircle(cx, cy, rx, ry, 20))
			return TRUE;

		if (InCircle(cx, cy, rx, ry + 40, 20))
			return TRUE;

		if (InCircle(cx, cy, rx + 80, ry, 20))
			return TRUE;

		if (InCircle(cx, cy, rx + 80, ry + 40, 20))
			return TRUE;
	}

	return FALSE;
}

BOOL IsCollision2(int cx, int cy, int cr, int rx, int rx2, int ry)
{
	if ((rx <= cx && cx <= rx + 80) || (ry <= cy && cy <= ry + 40))
	{
		RECT rcEX = {
			rx - cr,
			ry - cr,
			rx2 + cr,
			ry + 40 + cr
		};

		if ((rcEX.left < cx&&cx < rcEX.right) && (rcEX.top < cy&&cy < rcEX.bottom))
			return TRUE;
	}

	else
	{
		if (InCircle(cx, cy, rx, ry, 20))
			return TRUE;

		if (InCircle(cx, cy, rx, ry + 40, 20))
			return TRUE;

		if (InCircle(cx, cy, rx2, ry, 20))
			return TRUE;

		if (InCircle(cx, cy, rx2, ry + 40, 20))
			return TRUE;
	}

	return FALSE;
}

BOOL InBlock(int x, int x2, int y, int mx, int my)
{
	if (mx >= x && mx <= x2 && my >= y && my <= y + 40)
		return TRUE;
	else
		return FALSE;
}

struct Block {
	int x = 0, y = 0, condition = 0;
};

void DrawBlock(HDC hDC, int MainBlockX, int MainBlockX2)
{
	Rectangle(hDC, MainBlockX, 600, MainBlockX2, 640);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;

	HBRUSH hBrush, oldBrush, hBrush2, oldBrush2;
	HPEN hPen, oldPen;
	static BOOL SHAPE;
	static int direction = 0, direction2 = 0;
	static Block block[4][10];
	static int MainBlockX, MainBlockX2;
	static int EllipseX, EllipseY;
	static BOOL Selection, MOVE;
	static int BoardSize = 1;
	static int Speed;
	static int ColorBlock = 0, DeletedBlock = 0;
	static int floor = 2;
	int X = 0, Y = 0;
	int mx, my;
	char colorBlock[40], deletedBlock[40];

	switch (iMessage) {
	case WM_CREATE:
		SHAPE = TRUE;
		SetTimer(hWnd, 1, 500, NULL);

		Selection = FALSE;
		MOVE = FALSE;
		MainBlockX = 400;
		MainBlockX2 = 550;
		EllipseX = 450;
		EllipseY = 560;
		Speed = 100;

		for (int i = 0; i < floor; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				block[i][j].x = X;
				block[i][j].y = Y;
				block[i][j].condition = 0;
				X += 80;
			}
			X = 0;
			Y += 40;
		}

		X = 0;

		for (int i = floor; i < 4; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				block[i][j].x = X;
				block[i][j].y = Y;
				block[i][j].condition = -1;
				X += 80;
			}
			X = 0;
			Y += 40;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_SECONDFLOOR:
			SHAPE = TRUE;

			Selection = FALSE;
			MOVE = FALSE;
			MainBlockX = 400;
			MainBlockX2 = 550;
			EllipseX = 450;
			EllipseY = 560;
			Speed = 100;

			for (int i = 0; i < floor; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					block[i][j].x = X;
					block[i][j].y = Y;
					block[i][j].condition = 0;
					X += 80;
				}
				X = 0;
				Y += 40;
			}

			X = 0;

			for (int i = floor; i < 4; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					block[i][j].x = X;
					block[i][j].y = Y;
					block[i][j].condition = -1;
					X += 80;
				}
				X = 0;
				Y += 40;
			}
			break;
		case ID_THIRDFLOOR:
			SHAPE = TRUE;
			floor = 3;

			Selection = FALSE;
			MOVE = FALSE;
			MainBlockX = 400;
			MainBlockX2 = 550;
			EllipseX = 450;
			EllipseY = 560;
			Speed = 100;

			for (int i = 0; i < floor; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					block[i][j].x = X;
					block[i][j].y = Y;
					block[i][j].condition = 0;
					X += 80;
				}
				X = 0;
				Y += 40;
			}

			X = 0;

			for (int i = floor; i < 4; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					block[i][j].x = X;
					block[i][j].y = Y;
					block[i][j].condition = -1;
					X += 80;
				}
				X = 0;
				Y += 40;
			}
			break;
		case ID_FORTHFLOOR:
			SHAPE = TRUE;
			floor = 4;

			Selection = FALSE;
			MOVE = FALSE;
			MainBlockX = 400;
			MainBlockX2 = 550;
			EllipseX = 450;
			EllipseY = 560;
			Speed = 100;

			for (int i = 0; i < floor; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					block[i][j].x = X;
					block[i][j].y = Y;
					block[i][j].condition = 0;
					X += 80;
				}
				X = 0;
				Y += 40;
			}

			X = 0;

			for (int i = floor; i < 4; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					block[i][j].x = X;
					block[i][j].y = Y;
					block[i][j].condition = -1;
					X += 80;
				}
				X = 0;
				Y += 40;
			}
			break;
		case ID_CIRCLEBALL:
			SHAPE = TRUE;
			InvalidateRgn(hWnd, NULL, FALSE);
			break;
		case ID_RECTANGLEBALL:
			SHAPE = FALSE;
			InvalidateRgn(hWnd, NULL, FALSE);
			break;
		case ID_START:
			MOVE = TRUE;
			SetTimer(hWnd, 2, Speed, NULL);
			break;
		case ID_END:
			PostQuitMessage(0);
			break;
		case ID_SMALLBOARD:
			BoardSize = 0;
			MainBlockX2 = MainBlockX + 100;
			EllipseX = MainBlockX+30;
			EllipseY = 560;
			direction2 = 0;
			MOVE = FALSE;
			break;

		case ID_MEDIUMBOARD:
			BoardSize = 1;
			MainBlockX2 = MainBlockX + 150;
			EllipseX = MainBlockX + 50;
			EllipseY = 560;
			direction2 = 0;
			MOVE = FALSE;
			break;

		case ID_BIGBOARD:
			BoardSize = 2;
			MainBlockX2 = MainBlockX + 200;
			EllipseX = MainBlockX + 80;
			EllipseY = 560;
			direction2 = 0;
			MOVE = FALSE;
			break;

		case ID_FASTSPEED:
			Speed = 50;
			SetTimer(hWnd, 2, Speed, NULL);
			break;
		case ID_MEDIUMSPEED:
			Speed = 100;
			SetTimer(hWnd, 2, Speed, NULL);
			break;
		case ID_SLOWSPEED:
			Speed = 150;
			SetTimer(hWnd, 2, Speed, NULL);
			break;
		default:
			break;
		}
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (direction == 0)
			{
				for (int i = 0; i < floor; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						block[i][j].x += 80;
					}
				}
				if (block[0][9].x >= 960)
					direction = 1;
			}
			else
			{
				for (int i = 0; i < floor; ++i)
				{
					for (int j = 0; j < 10; ++j)
					{
						block[i][j].x -= 80;
					}
				}
				if (block[0][0].x <= 0)
					direction = 0;
			}
			break;
		case 2:
			if (MOVE)
			{
				switch (direction2)
				{
				case 0:
					EllipseX -= 40;
					EllipseY -= 20;
					if (EllipseX < 0)
					{
						EllipseX = 0;
						direction2 = 1;
					}
					else if (EllipseY <= 0)
					{
						direction2 = 2;
					}
					else if (EllipseY <= 160)
					{
						for (int i = floor-1; i >= 0; --i)
						{
							for (int j = 0; j < 10; ++j)
							{

								if (IsCollision(EllipseX + 20, EllipseY + 20, 20, block[i][j].x, block[i][j].y))
								{
									EllipseY += 20;
									block[i][j].y += 40;
									direction2 = 3;
									if (block[i][j].condition == 1)
									{
										block[i][j].condition = 2;
										block[i][j].y += 200;
										ColorBlock--;
										DeletedBlock++;
									}
									else
									{
										ColorBlock++;
										block[i][j].condition = 1;
									}

									break;
								}
							}
							if (direction2 == 3)
								break;
						}
					}

					break;
				case 1:
					EllipseX += 40;
					EllipseY -= 20;
					if (EllipseX > 960)
					{
						EllipseX = 960;

						direction2 = 0;
					}
					else if (EllipseY <= 0)
						direction2 = 3;

					else if (EllipseY <= 160)
					{
						for (int i = floor-1; i >= 0; --i)
						{
							for (int j = 0; j < 10; ++j)
							{

								if (IsCollision(EllipseX + 20, EllipseY + 20, 20, block[i][j].x, block[i][j].y))
								{

									block[i][j].y += 40;
									direction2 = 2;
									if (block[i][j].condition == 1)
									{
										block[i][j].condition = 2;
										block[i][j].y += 200;
										ColorBlock--;
										DeletedBlock++;
									}
									else
									{
										block[i][j].condition = 1;
										ColorBlock++;
									}
									break;
								}
							}
							if (direction2 == 2)
								break;
						}
					}

					break;
				case 2:
					EllipseX += 40;
					EllipseY += 20;
					if (EllipseX > 960)
					{
						EllipseX = 960;
						direction2 = 3;
					}
					else if (EllipseY >= 560)
					{
						if (IsCollision2(EllipseX + 20, EllipseY + 20, 20, MainBlockX, MainBlockX2, 600))
						{
							if (EllipseX + 20 >= MainBlockX && EllipseX + 20 < MainBlockX + 75)
								direction2 = 0;
							else if (EllipseX + 20 >= MainBlockX + 75 && EllipseX + 20 <= MainBlockX + 150)
								direction2 = 1;
						}
					}

					else if (EllipseY <= 160)
					{
						for (int i = floor-1; i >= 0; --i)
						{
							for (int j = 0; j < 10; ++j)
							{

								if (IsCollision(EllipseX + 20, EllipseY + 20, 20, block[i][j].x, block[i][j].y))
								{
									EllipseY += 20;
									block[i][j].y += 40;
									direction2 = 3;
									if (block[i][j].condition == 1)
									{
										block[i][j].condition = 2;
										block[i][j].y += 200;
										ColorBlock--;
										DeletedBlock++;
									}
									else
									{
										ColorBlock++;
										block[i][j].condition = 1;
									}

									break;
								}
							}
							if (direction2 == 3)
								break;
						}
					}

					if (EllipseY >= 800)
					{
						EllipseX = MainBlockX + 50;
						EllipseY = 560;
						direction2 = 0;
						MOVE = FALSE;
					}
					break;
				case 3:
					EllipseX -= 40;
					EllipseY += 20;
					if (EllipseY >= 560)
					{
						if (IsCollision2(EllipseX + 20, EllipseY + 20, 20, MainBlockX, MainBlockX2, 600))
						{
							if (EllipseX + 20 >= MainBlockX && EllipseX > +20 < MainBlockX + 75)
								direction2 = 0;
							else if (EllipseX + 20 >= MainBlockX + 75 && EllipseX + 20 <= MainBlockX + 150)
								direction2 = 1;
						}
					}
					else if (EllipseX < 0)
					{
						EllipseX = 0;
						direction2 = 2;
					}

					else if (EllipseY <= 160)
					{
						for (int i = floor-1; i >= 0; --i)
						{
							for (int j = 0; j < 10; ++j)
							{

								if (IsCollision(EllipseX + 20, EllipseY + 20, 20, block[i][j].x, block[i][j].y))
								{
									EllipseY += 20;
									block[i][j].y += 40;
									direction2 = 3;
									if (block[i][j].condition == 1)
									{
										block[i][j].condition = 2;
										block[i][j].y += 200;
										ColorBlock--;
										DeletedBlock++;
									}
									else
									{
										ColorBlock++;
										block[i][j].condition = 1;
									}

									break;
								}
							}
							if (direction2 == 3)
								break;
						}
					}

					if (EllipseY >= 800)
					{
						EllipseX = MainBlockX + 50;
						EllipseY = 560;
						direction2 = 0;
						MOVE = FALSE;
					}
					break;
				}
			}
		}
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hPen = CreatePen(PS_SOLID, 5, RGB(200, 200, 200));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (block[i][j].condition == 0)
					Rectangle(hDC, block[i][j].x, block[i][j].y, block[i][j].x + 80, block[i][j].y + 40);
				else if (block[i][j].condition == 1)
				{
					hBrush2 = CreateSolidBrush(RGB(0, 0, 255));
					oldBrush2 = (HBRUSH)SelectObject(hDC, hBrush2);

					Rectangle(hDC, block[i][j].x, block[i][j].y, block[i][j].x + 80, block[i][j].y + 40);

					SelectObject(hDC, oldBrush2);
					DeleteObject(hBrush2);
				}

			}
		}
		DrawBlock(hDC, MainBlockX, MainBlockX2);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		if (SHAPE)
			Ellipse(hDC, EllipseX, EllipseY, EllipseX + 40, EllipseY + 40);
		else
			Rectangle(hDC, EllipseX, EllipseY, EllipseX + 40, EllipseY + 40);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);

		sprintf(colorBlock, "색칠된 블럭의 개수는 %d 개 입니다", ColorBlock);
		sprintf(deletedBlock, "삭제된 블럭의 개수는 %d 개 입니다", DeletedBlock);

		TextOutA(hDC, 0, 800, colorBlock, 32);
		TextOutA(hDC, 0, 820, deletedBlock, 32);

		if (DeletedBlock == floor * 10)
			PostQuitMessage(0);

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

		if (InBlock(MainBlockX, MainBlockX2, 600, mx, my))
			Selection = TRUE;
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		Selection = FALSE;
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (Selection)
		{
			MainBlockX = mx - 75;

			if (BoardSize == 1)
				MainBlockX2 = MainBlockX + 150;
			else if (BoardSize == 0)
				MainBlockX2 = MainBlockX + 100;
			else if (BoardSize == 2)
				MainBlockX2 = MainBlockX + 200;

		}

		if (!MOVE)
		{

			EllipseX = (MainBlockX + MainBlockX2) / 2 - 20;
		}
		InvalidateRgn(hWnd, NULL, FALSE);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}