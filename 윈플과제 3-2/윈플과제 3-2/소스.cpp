#include <Windows.h>
#include <math.h>
#include <stdio.h>

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

		if((rcEX.left<cx&&cx<rcEX.right)&&(rcEX.top<cy&&cy<rcEX.bottom))
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

BOOL IsCollision2(int cx, int cy, int cr, int rx, int ry)
{
	if ((rx <= cx && cx <= rx + 80) || (ry <= cy && cy <= ry + 40))
	{
		RECT rcEX = {
			rx - cr,
			ry - cr,
			rx + 150 + cr,
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

		if (InCircle(cx, cy, rx + 150, ry, 20))
			return TRUE;

		if (InCircle(cx, cy, rx + 150, ry + 40, 20))
			return TRUE;
	}

	return FALSE;
}

BOOL InBlock(int x, int y, int mx, int my)
{
	if (mx >= x && mx <= x + 150 && my >= y && my <= y + 40)
		return TRUE;
	else
		return FALSE;
}

struct Block {
	int x = 0, y = 0, condition = 0;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	HBRUSH hBrush, oldBrush, hBrush2, oldBrush2;
	HPEN hPen, oldPen;
	static int direction = 0, direction2 = 0;
	static Block block[2][20];
	static int MainBlockX;
	static int EllipseX, EllipseY;
	static BOOL Selection, MOVE;
	static int Speed;
	static int ColorBlock = 0, DeletedBlock = 0;
	int X = 0, Y = 0;
	int mx, my;
	char colorBlock[40], deletedBlock[40];

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 500, NULL);

		Selection = FALSE;
		MOVE = FALSE;
		MainBlockX = 400;
		EllipseX = 450;
		EllipseY = 560;
		Speed = 100;

		for (int i = 0; i < 2; ++i)
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
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (direction == 0)
			{
				for (int i = 0; i < 2; ++i)
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
				for (int i = 0; i < 2; ++i)
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
					else if (EllipseY <= 120)
					{
						for (int i = 1; i >= 0; --i)
						{
							for (int j = 0; j < 10; ++j)
							{
								/*if (EllipseX+20 >= block[i][j].x&&EllipseX+20 <= block[i][j].x + 80&&EllipseY<=block[i][j].y+40&&EllipseY>=block[i][j].y)
								{
									block[i][j].y += 40;
									direction2 = 3;
									if (block[i][j].condition == 1)
									{
										block[i][j].condition = 2;
										block[i][j].y += 200;
									}
									else 
										block[i][j].condition = 1;

									break;
								}*/

								if (IsCollision(EllipseX+20, EllipseY+20, 20, block[i][j].x, block[i][j].y))
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
					else if (EllipseY <= 80)
					{
						for (int i = 1; i >= 0; --i)
						{
							for (int j = 0; j < 10; ++j)
							{
								/*if (EllipseX+20 >= block[i][j].x&&EllipseX+20 <= block[i][j].x + 80 && EllipseY <= block[i][j].y + 40 && EllipseY >= block[i][j].y)
								{
									block[i][j].y += 40;
									direction2 = 3;
									if (block[i][j].condition == 1)
									{	
										block[i][j].condition = 2;
										block[i][j].y += 200;
									}
									else
										block[i][j].condition = 1;
									break;
								}*/

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
						if (IsCollision2(EllipseX + 20, EllipseY + 20, 20, MainBlockX, 600))
						{
							if (EllipseX + 20 >= MainBlockX && EllipseX + 20 < MainBlockX + 75)
								direction2 = 0;
							else if (EllipseX + 20 >= MainBlockX + 75 && EllipseX + 20 <= MainBlockX + 150)
								direction2 = 1;
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
						if (IsCollision2(EllipseX + 20, EllipseY + 20, 20, MainBlockX, 600))
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
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		if (wParam == '+')
		{
			Speed -= 50;
			SetTimer(hWnd, 2, Speed, NULL);
			if (Speed <= 0)
				Speed = 50;

		}

		else if (wParam == '-')
		{
			Speed += 50;
			SetTimer(hWnd, 2, Speed, NULL);
			if (Speed > 1000)
				Speed = 1000;

		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hPen = CreatePen(PS_SOLID, 5, RGB(200, 200, 200));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		for (int i = 0; i < 2; ++i)
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
		Rectangle(hDC, MainBlockX, 600, MainBlockX + 150, 640);
		
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, EllipseX, EllipseY, EllipseX + 40, EllipseY + 40);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);

		sprintf(colorBlock, "색칠된 블럭의 개수는 %d 개 입니다", ColorBlock);
		sprintf(deletedBlock, "삭제된 블럭의 개수는 %d 개 입니다", DeletedBlock);

		TextOutA(hDC, 0, 800, colorBlock, 32);
		TextOutA(hDC, 0, 820, deletedBlock, 32);

		if (DeletedBlock == 20)
			PostQuitMessage(0);

		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		MOVE = TRUE;
		SetTimer(hWnd, 2, Speed, NULL);
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		if (InBlock(MainBlockX, 600, mx, my))
			Selection = TRUE;
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		Selection = FALSE;
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (Selection)
		{
			MainBlockX = mx - 75;
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}