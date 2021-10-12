#include <Windows.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
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
		0, 0, 1000, 1000, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

double getRadian(int num)
{
	return num * (PI / 180);
}

struct Circle
{
	int X, Y, Radius, Angle, Direction;
	BOOL Rotate;
	BOOL Collision;
};

void DrawCircle(HDC hDC, int X, int Y, int Radius)
{
	Ellipse(hDC, X - Radius, Y - Radius, X + Radius, Y + Radius);
}

BOOL Incircle(int CircleX, int CircleY, int CircleRadius, int mx, int my)
{
	int delX = mx - CircleX;
	int delY = my - CircleY;

	float Distance = sqrt((delX*delX) + (delY * delY));

	if (Distance < CircleRadius)
		return TRUE;
	else
		return FALSE;
}

BOOL IsCollision(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r)
{
	float deltaX = c1x - c2x;
	float deltaY = c1y - c2y;
	float length = sqrt((deltaX*deltaX) + (deltaY * deltaY));
	if (length > (c1r + c2r))
		return FALSE;
	return TRUE;
}

void DrawObstacle(HDC hDC, int X, int Y, int Radius, int Angle)
{
	Ellipse(hDC, X - Radius, Y - Radius, X + Radius, Y + Radius);

	MoveToEx(hDC, X + Radius * cos(getRadian(Angle)), Y + Radius * sin(getRadian(Angle)), NULL);
	LineTo(hDC, X - Radius * cos(getRadian(Angle)), Y - Radius * sin(getRadian(Angle)));

	Angle += 60;

	MoveToEx(hDC, X + Radius * cos(getRadian(Angle)), Y + Radius * sin(getRadian(Angle)), NULL);
	LineTo(hDC, X - Radius * cos(getRadian(Angle)), Y - Radius * sin(getRadian(Angle)));

	Angle += 60;

	MoveToEx(hDC, X + Radius * cos(getRadian(Angle)), Y + Radius * sin(getRadian(Angle)), NULL);
	LineTo(hDC, X - Radius * cos(getRadian(Angle)), Y - Radius * sin(getRadian(Angle)));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	static HDC hDC, MemDC;
	HDC tmphDC;
	static HBITMAP BackBit, oldBackBit;

	static RECT bufferRT;

	PAINTSTRUCT ps;
	HBRUSH hBrush = 0, oldBrush = 0;
	static BOOL Selection, Drag;
	static int HeroX, HeroY;
	static Circle BigCircle[10];
	static Circle SmallCircle[10];
	static int mx, my;
	static BOOL Game;
	static int Point = 0;
	static int resultnum;
	static int Hred, HGreen, HBlue;
	static int OldHeroX, OldHeroY;
	char result[50];
	switch (iMessage) {
	case WM_CREATE:
		HeroX = 0;
		HeroY = 0;
		OldHeroX = 0;
		OldHeroY = 0;
		Game = TRUE;
		Drag = FALSE;
		for (int i = 0; i < 10; ++i)
		{
			while (1)
			{
				int num = 0;

				BigCircle[i].X = rand() % 1000;
				BigCircle[i].Y = rand() % 1000;
				BigCircle[i].Radius = rand() % 20 + 80;
				BigCircle[i].Angle = rand() % 360;

				for (int j = 0; j < i; ++j)
				{
					if (IsCollision(BigCircle[j].X, BigCircle[j].Y, BigCircle[j].Radius, HeroX, HeroY, 100))
						++num;

					if (IsCollision(BigCircle[j].X, BigCircle[j].Y, BigCircle[j].Radius, BigCircle[i].X, BigCircle[i].Y, BigCircle[i].Radius))
						++num;
				}

				if (num == 0)
					break;
			}
			BigCircle[i].Collision = FALSE;
			SmallCircle[i].Collision = FALSE;

			SmallCircle[i].Rotate = TRUE;
			SmallCircle[i].Direction = rand() % 2;
			SmallCircle[i].Angle = rand() % 360;



			if ((i % 2) == 1)
			{
				BigCircle[i].Rotate = TRUE;
				BigCircle[i].Direction = 1;
			}

			else
				BigCircle[i].Rotate = FALSE;
		}
		SetTimer(hWnd, 1, 250, NULL);
		SetTimer(hWnd, 2, 250, NULL);
		SetTimer(hWnd, 3, 10, NULL);

		Selection = FALSE;
		break;
	case WM_TIMER:
		if (wParam == 1)
		{
			if (Game)
			{
				for (int i = 0; i < 10; ++i)
				{
					if (BigCircle[i].Rotate)
					{
						if (BigCircle[i].Direction == 1)
							BigCircle[i].Angle += 5;
						else
							BigCircle[i].Angle -= 5;
					}

				}
			}
		}

		if (wParam == 2)
		{
			if (Game)

			{
				for (int i = 0; i < 10; ++i)
				{
					if (IsCollision(BigCircle[i].X, BigCircle[i].Y, BigCircle[i].Radius, HeroX, HeroY, 40))
					{
						BigCircle[i].Collision = TRUE;
						if (BigCircle[i].Rotate&&BigCircle[i].Direction == 1)
						{
							BigCircle[i].Direction = 2;
							++Point;
						}
						else if (!(BigCircle[i].Rotate))
						{
							BigCircle[i].Rotate = TRUE;
							BigCircle[i].Direction = 1;
							++Point;
						}
					}

					if (IsCollision(BigCircle[i].X + (BigCircle[i].Radius + 10) * cos(getRadian(SmallCircle[i].Angle)), BigCircle[i].Y + (BigCircle[i].Radius + 10) * sin(getRadian(SmallCircle[i].Angle)), 10, HeroX, HeroY, 40))
					{
						SmallCircle[i].Collision = TRUE;

						if (SmallCircle[i].Direction == 1)
						{
							SmallCircle[i].Direction = 3;
							++Point;
						}
						else if (SmallCircle[i].Direction == 0)
						{
							SmallCircle[i].Direction = 2;
							++Point;
						}
					}
				}
			}
		}
		if (wParam == 3)
		{
			if (Game)

			{
				for (int i = 0; i < 10; ++i)
				{
					if (SmallCircle[i].Direction == 1 || SmallCircle[i].Direction == 2)
						SmallCircle[i].Angle += 5;
					else
						SmallCircle[i].Angle -= 5;
				}
			}
		}

		InvalidateRgn(hWnd, NULL, FALSE);

		break;
	case WM_KEYDOWN:
		if (wParam == 'Q')
			PostQuitMessage(0);
		else if (wParam == 'R')
		{
			HeroX = 0;
			HeroY = 0;
			OldHeroX = 0;
			OldHeroY = 0;
			Game = TRUE;
			Drag = FALSE;
			for (int i = 0; i < 10; ++i)
			{
				while (1)
				{
					int num = 0;

					BigCircle[i].X = rand() % 1000;
					BigCircle[i].Y = rand() % 1000;
					BigCircle[i].Radius = rand() % 20 + 80;
					BigCircle[i].Angle = rand() % 360;

					for (int j = 0; j < i; ++j)
					{

						if (IsCollision(BigCircle[j].X, BigCircle[j].Y, BigCircle[j].Radius, BigCircle[i].X, BigCircle[i].Y, BigCircle[i].Radius))
							++num;
					}
					if (IsCollision(BigCircle[i].X, BigCircle[i].Y, BigCircle[i].Radius, HeroX, HeroY, 40))
						++num;
					if (num == 0)
						break;
				}
				BigCircle[i].Collision = FALSE;
				SmallCircle[i].Collision = FALSE;

				SmallCircle[i].Rotate = TRUE;
				SmallCircle[i].Direction = rand() % 2 + 1;
				SmallCircle[i].Angle = rand() % 360;



				if ((i % 2) == 1)
				{
					BigCircle[i].Rotate = TRUE;
					BigCircle[i].Direction = 1;
				}

				else
					BigCircle[i].Rotate = FALSE;
			}
		}
		break;
	case WM_PAINT:

		MemDC = BeginPaint(hWnd, &ps);



		GetClientRect(hWnd, &bufferRT);

		hDC = CreateCompatibleDC(MemDC);

		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);

		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);

		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);





		hBrush = CreateSolidBrush(RGB(125, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		DrawCircle(hDC, HeroX, HeroY, 40);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		/*for (int i = 0; i < 10; ++i)
		{

		 if (IsCollision(BigCircle[i].X, BigCircle[i].Y, BigCircle[i].Radius, HeroX, HeroY, 40))
		 {
		  DrawCircle(hDC, OldHeroX, OldHeroY, 40);

		  DrawObstacle(hDC, BigCircle[i].X, BigCircle[i].Y, BigCircle[i].Radius, BigCircle[i].Angle);

		  DrawCircle(hDC, mx, my, 40);
		 }

		}*/


		for (int i = 0; i < 10; ++i)
		{
			if (SmallCircle[i].Collision)
			{
				hBrush = CreateSolidBrush(RGB(130, 0, 130));
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

				DrawCircle(hDC, BigCircle[i].X + (BigCircle[i].Radius + 10) * cos(getRadian(SmallCircle[i].Angle)), BigCircle[i].Y + (BigCircle[i].Radius + 10) * sin(getRadian(SmallCircle[i].Angle)), 10);

				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}

			else
			{
				hBrush = CreateSolidBrush(RGB(125, 255, 125));
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

				DrawCircle(hDC, BigCircle[i].X + (BigCircle[i].Radius + 10) * cos(getRadian(SmallCircle[i].Angle)), BigCircle[i].Y + (BigCircle[i].Radius + 10) * sin(getRadian(SmallCircle[i].Angle)), 10);

				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
		}

		for (int i = 0; i < 10; ++i)
		{
			hBrush = CreateSolidBrush(RGB(125, 255, 125));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			if (BigCircle[i].Collision)
			{
				/*tmphDC = GetDC(hWnd);

				SetROP2(tmphDC, R2_XORPEN);
				SelectObject(tmphDC, (HPEN)GetStockObject(DC_BRUSH));
				
				SetDCBrushColor(tmphDC, RGB(125, 255, 125));*/

				hBrush = CreateSolidBrush(RGB(130, 0, 130));
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);


				DrawObstacle(hDC, BigCircle[i].X, BigCircle[i].Y, BigCircle[i].Radius, BigCircle[i].Angle);

				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);

				/*ReleaseDC(hWnd, tmphDC);*/

			}

			else
				DrawObstacle(hDC, BigCircle[i].X, BigCircle[i].Y, BigCircle[i].Radius, BigCircle[i].Angle);

			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);

		}

		if (Incircle(HeroX, HeroY, 40, 975, 975))
		{
			Game = FALSE;
			sprintf(result, "충돌한 횟수는 %d 회 입니다", Point);
			TextOutA(hDC, 0, 0, result, strlen(result));
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

	case WM_LBUTTONDOWN:
		if (Game)
		{
			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			if (Incircle(HeroX, HeroY, 40, mx, my))
				Selection = TRUE;
		}
		Drag = TRUE;
		break;

	case WM_LBUTTONUP:
		Selection = FALSE;
		Drag = FALSE;
		break;

	case WM_MOUSEMOVE:
		hDC = GetDC(hWnd);
		if (Game)
		{
			if (Drag)
			{
				SetROP2(hDC, R2_XORPEN);
				SelectObject(hDC, (HPEN)GetStockObject(WHITE_PEN));

				mx = LOWORD(lParam);
				my = HIWORD(lParam);


				for (int i = 0; i < 10; ++i)
				{

					if (IsCollision(BigCircle[i].X, BigCircle[i].Y, BigCircle[i].Radius, HeroX, HeroY, 40))
					{
						DrawCircle(hDC, OldHeroX, OldHeroY, 40);

						DrawObstacle(hDC, BigCircle[i].X, BigCircle[i].Y, BigCircle[i].Radius, BigCircle[i].Angle);

						DrawCircle(hDC, mx, my, 40);
					}

				}


				if (Selection)
				{
					if (mx < 990 && my < 990 && mx>0 && my>0)
					{
						HeroX = mx;
						HeroY = my;
					}
				}

				OldHeroX = mx;
				OldHeroY = my;

			}

		}
		ReleaseDC(hWnd, hDC);
		break;

	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
