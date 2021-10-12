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
		0, 0, 1000, 800, NULL, (HMENU)NULL, hInstance, NULL);

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

BOOL STARTCLICK(int mx, int my)
{
	if (mx <= 568 && mx >= 208 && my <= 500 && my >= 390)
		return TRUE;
	return FALSE;
}

BOOL EXITCLICK(int mx, int my)
{
	if (mx <= 568 && mx >= 208 && my <= 743 && my >= 638)
		return TRUE;
	return FALSE;
}

BOOL HELPCLICK(int mx, int my)
{
	if (mx <= 568 && mx >= 208 && my <= 615 && my >= 515)
		return TRUE;
	return FALSE;
}

BOOL LEVEL1CLICK(int mx, int my)
{
	if (mx <= 655 && mx >= 140 && my <= 207 && my >= 87)
		return TRUE;
	return FALSE;
}

BOOL LEVEL2CLICK(int mx, int my)
{
	if (mx <= 655 && mx >= 140 && my <= 435 && my >= 315)
		return TRUE;
	return FALSE;
}

BOOL LEVEL3CLICK(int mx, int my)
{
	if (mx <= 655 && mx >= 140 && my <= 660 && my >= 540)
		return TRUE;
	return FALSE;
}

void DrawCircle(HDC hDC, int X, int Y, int Radius)
{
	Ellipse(hDC, X - Radius, Y - Radius, X + Radius, Y + Radius);
}

void Interface(HDC hDC, BOOL HELP, BOOL LevelSelect)
{
	HDC memDC;
	HBITMAP BackGround, Help, LEVELSELECT;

	BackGround = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND));
	Help = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_HELP));
	LEVELSELECT=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_LEVELSELECT));

	memDC = CreateCompatibleDC(hDC);
	(HBITMAP)SelectObject(memDC, BackGround);


	StretchBlt(hDC, 0, 0, 780, 780, memDC, 0, 0, 1024, 1024, SRCCOPY);

	(HBITMAP)SelectObject(memDC, Help);

	if(HELP)
		StretchBlt(hDC, 0, 100, 800, 500, memDC, 0, 0, 800, 500, SRCCOPY);

	(HBITMAP)SelectObject(memDC, LEVELSELECT);

	if(LevelSelect)
		StretchBlt(hDC, 0, 0, 800, 800, memDC, 0, 0, 800, 800, SRCCOPY);

	



	DeleteObject(Help);
	DeleteObject(BackGround);
	DeleteDC(memDC);
}

void EnemyDie(Block Map[20][20], Block Enemy[50], int num)
{
	Enemy[num].cs = 2;
	for (int j = 0; j < 3; ++j)
	{
		for (int k = 0; k < 3; ++k)
		{
			Map[(((Enemy[num].yPos - 15) / 39) + j)][(((Enemy[num].xPos - 15) / 39) + k)].cs = 1;

		}
	}
	for (int j = 0; j < 50; ++j)
	{
		if (Enemy[j].cs == 1)
		{
			if (((Enemy[j].xPos - 30) < (Enemy[num].xPos + 60)) && ((Enemy[j].yPos - 30) < (Enemy[num].yPos + 60)) && ((Enemy[j].xPos + 60) > (Enemy[num].xPos - 30)) && ((Enemy[j].yPos + 60) > (Enemy[num].yPos - 30)))
			{
				EnemyDie(Map, Enemy, j);
			}
		}
	}

}

void Game(HDC hDC, Block Main, BULLET Bullet[6], Block Map[20][20], Block Enemy[100])
{
	HDC memDC;
	HBITMAP MAIN, BULLET[4], ENEMY, RANGE, EFFECT[4];

	HPEN hPen, oldPen;
	HPEN hPen1, oldPen1;

	HBRUSH hBrush, oldBrush;
	HBRUSH hBrush1, oldBrush1;


	MAIN = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_MAIN));
	BULLET[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BULLETU));
	BULLET[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BULLETR));
	BULLET[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BULLETD));
	BULLET[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BULLETL));
	ENEMY = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ENEMY));
	RANGE = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_RANGE));
	memDC = CreateCompatibleDC(hDC);
	EFFECT[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_DEFFECT1));
	EFFECT[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_DEFFECT2));
	EFFECT[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_DEFFECT3));
	EFFECT[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_DEFFECT4));


	hBrush1 = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush1 = (HBRUSH)SelectObject(hDC, hBrush1);
	hPen1 = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	oldPen1 = (HPEN)SelectObject(hDC, hPen1);

	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Map[i][j].cs == -1)
			{
				Rectangle(hDC, Map[i][j].xPos, Map[i][j].yPos, Map[i][j].xPos + 39, Map[i][j].yPos + 39);
			}
		}
	}

	SelectObject(hDC, oldBrush1);
	DeleteObject(hBrush1);
	SelectObject(hDC, oldPen1);
	DeleteObject(hPen1);

	hBrush1 = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush1 = (HBRUSH)SelectObject(hDC, hBrush1);
	hPen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	oldPen1 = (HPEN)SelectObject(hDC, hPen1);

	for (int i = 0; i < 19; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Map[i][j].cs == 2)
			{
				Rectangle(hDC, Map[i][j].xPos, Map[i][j].yPos, Map[i][j].xPos + 39, Map[i][j].yPos + 39);
			}
		}
	}

	SelectObject(hDC, oldBrush1);
	DeleteObject(hBrush1);
	SelectObject(hDC, oldPen1);
	DeleteObject(hPen1);

	for (int i = 0; i < 6; ++i)
	{
		if (!Bullet[i].Rotate && !Bullet[i].Reloading)
		{
			if (Bullet[i].Direction == 1 || Bullet[i].Direction == 3)
			{
				(HBITMAP)SelectObject(memDC, BULLET[Bullet[i].Direction]);
				StretchBlt(hDC, Bullet[i].X, Bullet[i].Y, 20, 5, memDC, 0, 0, 48, 13, SRCCOPY);
			}
			else
			{
				(HBITMAP)SelectObject(memDC, BULLET[Bullet[i].Direction]);
				StretchBlt(hDC, Bullet[i].X, Bullet[i].Y, 5, 20, memDC, 0, 0, 13, 48, SRCCOPY);
			}
		}
	}
	(HBITMAP)SelectObject(memDC, RANGE);
	for (int i = 0; i < 50; ++i)
	{
		if (Enemy[i].cs == 1)
			TransparentBlt(hDC, Enemy[i].xPos - 30, Enemy[i].yPos - 30, 90, 90, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
	}

	(HBITMAP)SelectObject(memDC, ENEMY);
	for (int i = 0; i < 50; ++i)
	{
		if (Enemy[i].cs == 1)
			StretchBlt(hDC, Enemy[i].xPos, Enemy[i].yPos, 30, 30, memDC, 0, 0, 48, 48, SRCCOPY);
	}

	for (int i = 0; i < 50; ++i)
	{
		if (Enemy[i].cs >= 2)
		{
			switch (Enemy[i].cs)
			{
			case 2:
				(HBITMAP)SelectObject(memDC, EFFECT[0]);
				TransparentBlt(hDC, Enemy[i].xPos - 30, Enemy[i].yPos - 30, 90, 90, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
				break;
			case 3:
				(HBITMAP)SelectObject(memDC, EFFECT[1]);
				TransparentBlt(hDC, Enemy[i].xPos - 30, Enemy[i].yPos - 30, 90, 90, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
				break;
			case 4:
				(HBITMAP)SelectObject(memDC, EFFECT[2]);
				TransparentBlt(hDC, Enemy[i].xPos - 30, Enemy[i].yPos - 30, 90, 90, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
				break;
			case 5:
				(HBITMAP)SelectObject(memDC, EFFECT[3]);
				TransparentBlt(hDC, Enemy[i].xPos - 30, Enemy[i].yPos - 30, 90, 90, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
				break;
			}
		}
	}


	(HBITMAP)SelectObject(memDC, MAIN);
	if (Main.cs == 1)
		TransparentBlt(hDC, Main.xPos, Main.yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
	else
	{
		switch (Main.cs)
		{
		case 2:
			(HBITMAP)SelectObject(memDC, EFFECT[0]);
			TransparentBlt(hDC, Main.xPos - 30, Main.yPos - 30, 90, 90, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
			break;
		case 3:
			(HBITMAP)SelectObject(memDC, EFFECT[1]);
			TransparentBlt(hDC, Main.xPos - 30, Main.yPos - 30, 90, 90, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
			break;
		case 4:
			(HBITMAP)SelectObject(memDC, EFFECT[2]);
			TransparentBlt(hDC, Main.xPos - 30, Main.yPos - 30, 90, 90, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
			break;
		case 5:
			(HBITMAP)SelectObject(memDC, EFFECT[3]);
			TransparentBlt(hDC, Main.xPos - 30, Main.yPos - 30, 90, 90, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
			break;
		}
	}

	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hDC, hPen);

	for (int i = 0; i < 6; ++i)
	{
		if (Bullet[i].Rotate)
			DrawCircle(hDC, Main.xPos + 15 + 10 * cos(getRadian(Bullet[i].Angle)), Main.yPos + 15 - 10 * sin(getRadian(Bullet[i].Angle)), 3);
	}

	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(hPen);

	

	DeleteObject(MAIN);
	for (int i = 0; i < 4; ++i)
	{
		DeleteObject(BULLET[i]);
	}
	for (int i = 0; i < 4; ++i)
	{
		DeleteObject(EFFECT[i]);
	}
	DeleteObject(RANGE);
	DeleteObject(ENEMY);
	DeleteDC(memDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	static Block Main, Enemy[50];
	static Block Map[20][20];
	static BULLET Bullet[6];
	static BOOL Start, LEVELSELECT, HELP, Power;
	static int Level;
	static int Relive;
	static int Score;
	int n, mx, my;
	switch (iMessage) {
	case WM_CREATE:
		for (int i = 0; i < 100; ++i)
		{
			Enemy[i].cs = 0;
		}
		Score = 0;
		Power = FALSE;
		HELP = FALSE;
		LEVELSELECT = FALSE;
		Start = FALSE;
		Relive = 5000;
		Main.xPos = 400;
		Main.yPos = 400;
		Main.cs = 1;
		for (int i = 0; i < 6; ++i)
		{
			Bullet[i].Angle = 60 * i;
			Bullet[i].Rotate = TRUE;
			Bullet[i].Reloading = FALSE;
		}
		for (int i = 0; i < 19; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				Map[i][j].xPos = j * 39;
				Map[i][j].yPos = i * 39;
				Map[i][j].cs = 0;
			}
		}

		SetTimer(hWnd, 1, 25, NULL);
		SetTimer(hWnd, 2, 10, NULL);
		SetTimer(hWnd, 3, 1000, NULL);
		SetTimer(hWnd, 4, Relive, NULL);
		SetTimer(hWnd, 5, 50, NULL);
		SetTimer(hWnd, 6, 100, NULL);
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
				if (!Bullet[i].Rotate && !Bullet[i].Reloading)
				{
					if (Level == 1)
					{
						switch (Bullet[i].Direction)
						{
						case 0:
							Bullet[i].Y -= 8;
							if (Bullet[i].Y <= 156)
								Bullet[i].Reloading = TRUE;
							for (int j = 0; j < 50; ++j)
							{
								if (Enemy[j].cs == 1)
								{
									if ((Bullet[i].X < (Enemy[j].xPos + 30)) && (Bullet[i].Y < (Enemy[j].yPos + 30)) && ((Bullet[i].X + 5) > Enemy[j].xPos) && ((Bullet[i].Y + 20) > Enemy[j].yPos))
									{
										EnemyDie(Map, Enemy, j);
										Bullet[i].Reloading = TRUE;
									}
								}
							}
							break;
						case 1:
							Bullet[i].X += 8;
							if (Bullet[i].X >= 663)
								Bullet[i].Reloading = TRUE;
							for (int j = 0; j < 50; ++j)
							{
								if (Enemy[j].cs == 1)
								{
									if ((Bullet[i].X < (Enemy[j].xPos + 30)) && (Bullet[i].Y < (Enemy[j].yPos + 30)) && ((Bullet[i].X + 20) > Enemy[j].xPos) && ((Bullet[i].Y + 5) > Enemy[j].yPos))
									{
										EnemyDie(Map, Enemy, j);
										Bullet[i].Reloading = TRUE;
									}
								}
							}
							break;
						case 2:
							Bullet[i].Y += 8;
							if (Bullet[i].Y >= 663)
								Bullet[i].Reloading = TRUE;
							for (int j = 0; j < 50; ++j)
							{
								if (Enemy[j].cs == 1)
								{
									if ((Bullet[i].X < (Enemy[j].xPos + 30)) && (Bullet[i].Y < (Enemy[j].yPos + 30)) && ((Bullet[i].X + 5) > Enemy[j].xPos) && ((Bullet[i].Y + 20) > Enemy[j].yPos))
									{
										EnemyDie(Map, Enemy, j);
										Bullet[i].Reloading = TRUE;
									}
								}
							}
							break;
						case 3:
							Bullet[i].X -= 8;
							if (Bullet[i].X <= 156)
								Bullet[i].Reloading = TRUE;
							for (int j = 0; j < 50; ++j)
							{
								if (Enemy[j].cs == 1)
								{
									if ((Bullet[i].X < (Enemy[j].xPos + 30)) && (Bullet[i].Y < (Enemy[j].yPos + 30)) && ((Bullet[i].X + 20) > Enemy[j].xPos) && ((Bullet[i].Y + 5) > Enemy[j].yPos))
									{
										EnemyDie(Map, Enemy, j);
										Bullet[i].Reloading = TRUE;
									}
								}
							}

						}
						if (Bullet[i].Y <= 780 && Bullet[i].Y >= 0 && Bullet[i].X >= 0 && Bullet[i].X <= 780)
						{
							if (Map[Bullet[i].Y / 39][Bullet[i].X / 39].cs == 2)
								Bullet[i].Reloading = TRUE;

							else if (Map[Bullet[i].Y / 39][Bullet[i].X / 39].cs == -1)
								Map[Bullet[i].Y / 39][Bullet[i].X / 39].cs = 1;
						}
					}
					else
					{
						switch (Bullet[i].Direction)
						{
						case 0:
							Bullet[i].Y -= 8;
							if (Bullet[i].Y <= 0)
								Bullet[i].Reloading = TRUE;
							for (int j = 0; j < 50; ++j)
							{
								if (Enemy[j].cs == 1)
								{
									if ((Bullet[i].X < (Enemy[j].xPos + 30)) && (Bullet[i].Y < (Enemy[j].yPos + 30)) && ((Bullet[i].X + 5) > Enemy[j].xPos) && ((Bullet[i].Y + 20) > Enemy[j].yPos))
									{
										EnemyDie(Map, Enemy, j);
										Bullet[i].Reloading = TRUE;
									}
								}
							}
							break;
						case 1:
							Bullet[i].X += 8;
							if (Bullet[i].X >= 780)
								Bullet[i].Reloading = TRUE;
							for (int j = 0; j < 50; ++j)
							{
								if (Enemy[j].cs == 1)
								{
									if ((Bullet[i].X < (Enemy[j].xPos + 30)) && (Bullet[i].Y < (Enemy[j].yPos + 30)) && ((Bullet[i].X + 20) > Enemy[j].xPos) && ((Bullet[i].Y + 5) > Enemy[j].yPos))
									{
										EnemyDie(Map, Enemy, j);
										Bullet[i].Reloading = TRUE;
									}
								}
							}
							break;
						case 2:
							Bullet[i].Y += 8;
							if (Bullet[i].Y >= 780)
								Bullet[i].Reloading = TRUE;
							for (int j = 0; j < 50; ++j)
							{
								if (Enemy[j].cs == 1)
								{
									if ((Bullet[i].X < (Enemy[j].xPos + 30)) && (Bullet[i].Y < (Enemy[j].yPos + 30)) && ((Bullet[i].X + 5) > Enemy[j].xPos) && ((Bullet[i].Y + 20) > Enemy[j].yPos))
									{
										EnemyDie(Map, Enemy, j);
										Bullet[i].Reloading = TRUE;
									}
								}
							}
							break;
						case 3:
							Bullet[i].X -= 8;
							if (Bullet[i].X <= 0)
								Bullet[i].Reloading = TRUE;
							for (int j = 0; j < 50; ++j)
							{
								if (Enemy[j].cs == 1)
								{
									if ((Bullet[i].X < (Enemy[j].xPos + 30)) && (Bullet[i].Y < (Enemy[j].yPos + 30)) && ((Bullet[i].X + 20) > Enemy[j].xPos) && ((Bullet[i].Y + 5) > Enemy[j].yPos))
									{
										EnemyDie(Map, Enemy, j);
										Bullet[i].Reloading = TRUE;
									}
								}
							}
							break;
						}

						

						if (Bullet[i].Y <= 780 && Bullet[i].Y >= 0 && Bullet[i].X >= 0 && Bullet[i].X <= 780)
						{
							if (Map[Bullet[i].Y / 39][Bullet[i].X / 39].cs == 2)
								Bullet[i].Reloading = TRUE;

							else if (Map[Bullet[i].Y / 39][Bullet[i].X / 39].cs == -1)
								Map[Bullet[i].Y / 39][Bullet[i].X / 39].cs = 1;
						}
					}
				}
			}
			break;
		case 3:
			for (int i = 0; i < 6; ++i)
			{
				if (Bullet[i].Reloading)
				{
					Bullet[i].Rotate = TRUE;
					Bullet[i].Reloading = FALSE;
					break;
				}
			}
			break;
		case 4:
			srand(time(0));
			if (Level == 1)
			{
				while (1)
				{
					mx = rand() % 436 + 170;
					my = rand() % 506 + 156;
					if ((mx >= 156 && mx <= 633 && my >= 156 && my <= 186) || (mx >= 156 && mx <= 633 && my >= 603 && my <= 633) || (mx >= 156 && mx <= 186 && my >= 156 && my <= 633) || (mx >= 603 && mx <= 633 && my >= 156 && my <= 633))
						break;
				}
				for (int i = 0; i < 50; ++i)
				{
					if (Enemy[i].cs == 0)
					{
						Enemy[i].cs = 1;
						Enemy[i].xPos = mx;
						Enemy[i].yPos = my;
						break;
					}
				}

			}
			else
			{
				while (1)
				{
					mx = rand() % 720 + 50;
					my = rand() % 664 + 78;
					if ((mx >= 39 && mx <= 780 && my >= 78 && my <= 108) || (mx >= 39 && mx <= 780 && my >= 711 && my <= 741) || (mx >= 39 && mx <= 69 && my >= 78 && my <= 741) || (mx >= 750 && mx <= 780 && my >= 78 && my <= 741))
						break;
				}
				for (int i = 0; i < 50; ++i)
				{
					if (Enemy[i].cs == 0)
					{
						Enemy[i].cs = 1;
						Enemy[i].xPos = mx;
						Enemy[i].yPos = my;
						break;
					}
				}
			}
			Relive -= 300;
			if (Relive <= 0)
				Relive = 1;
			SetTimer(hWnd, 4, Relive, NULL);
			break;
		case 5:
			for (int i = 0; i < 50; ++i)
			{
				if (Enemy[i].cs == 1)
				{
					if (Enemy[i].xPos < Main.xPos)
						Enemy[i].xPos++;
					else if (Enemy[i].xPos > Main.xPos)
						Enemy[i].xPos--;

					if (Enemy[i].yPos < Main.yPos)
						Enemy[i].yPos++;
					else if (Enemy[i].yPos > Main.yPos)
						Enemy[i].yPos--;

					Map[(Enemy[i].yPos + 15) / 39][(Enemy[i].xPos + 15) / 39].cs = -1;
					if (((Enemy[i].xPos - 30) < (Main.xPos + 30)) && ((Enemy[i].yPos - 30) < (Main.yPos + 30)) && ((Enemy[i].xPos + 60) > Main.xPos) && ((Enemy[i].yPos + 60) > Main.yPos))
					{
						for (int j = 0; j < 3; ++j)
						{
							for (int k = 0; k < 3; ++k)
							{
								Map[(((Main.yPos - 15) / 39) + j)][(((Main.xPos - 15) / 39) + k)].cs = 1;

							}
						}
						for (int j = 0; j < 50; ++j)
						{
							if (((Enemy[j].xPos - 30) < (Main.xPos + 60)) && ((Enemy[j].yPos - 30) < (Main.yPos + 60)) && ((Enemy[j].xPos + 60) > (Main.xPos - 30)) && ((Enemy[j].yPos + 60) > (Main.yPos - 30)))
								EnemyDie(Map, Enemy, j);
						}
						if (!Power)
							Main.cs = 2;
					}
				}
			}
			break;
		case 6:
			for (int i = 0; i < 50; ++i)
			{
				if (Enemy[i].cs >= 2)
				{
					++Enemy[i].cs;
					if (Enemy[i].cs > 5)
						Enemy[i].cs = 0;
				}
			}
			if (Main.cs >= 2)
			{
				++Main.cs;
				if (Main.cs > 5)
				{
					Main.cs = 1;
					Main.xPos = 400;
					Main.yPos = 400;
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
			{
				Main.xPos -= 8;
				if (Map[Main.yPos / 39][Main.xPos / 39].cs != 1)
					Main.xPos += 8;
			}
			if (GetAsyncKeyState('D') & 0x8000)
			{
				Main.xPos += 8;
				if (Map[Main.yPos / 39][(Main.xPos + 30) / 39].cs != 1)
					Main.xPos -= 8;
			}
			Main.yPos -= 8;
			if (Map[Main.yPos / 39][Main. xPos / 39].cs != 1)
				Main.yPos += 8;
			break;
		case 'A':
			if (GetAsyncKeyState('W') & 0x8000)
			{
				Main.yPos -= 8;
				if (Map[Main.yPos / 39][Main. xPos / 39].cs != 1)
					Main.yPos += 8;
			}
			if (GetAsyncKeyState('S') & 0x8000)
			{
				Main.yPos += 8;
				if (Map[(Main.yPos + 30) / 39][Main.xPos / 39].cs != 1)
					Main.yPos -= 8;
			}
			Main.xPos -= 8;
			if (Map[Main.yPos / 39][Main. xPos / 39].cs != 1)
				Main.xPos += 8;
			break;
		case 'S':
			if (GetAsyncKeyState('A') & 0x8000)
			{
				Main.xPos -= 8;
				if (Map[Main.yPos / 39][Main. xPos / 39].cs != 1)
					Main.xPos += 8;
			}
			if (GetAsyncKeyState('D') & 0x8000)
			{
				Main.xPos += 8;
				if (Map[ Main.yPos/ 39][(Main.xPos + 30) / 39].cs != 1)
					Main.xPos -= 8;
			}
			Main.yPos += 8;
			if (Map[(Main.yPos + 30) / 39][Main.xPos / 39].cs != 1)
				Main.yPos -= 8;
			break;
		case 'D':
			if (GetAsyncKeyState('W') & 0x8000)
			{
				Main.yPos -= 8;
				if (Map[Main.yPos / 39][Main. xPos / 39].cs != 1)
					Main.yPos += 8;
			}
			if (GetAsyncKeyState('S') & 0x8000)
			{
				Main.yPos += 8;
				if (Map[(Main.yPos + 30) / 39][Main.xPos / 39].cs != 1)
					Main.yPos -= 8;
			}
			Main.xPos += 8;
			if (Map[Main.yPos / 39][(Main.xPos + 30) / 39].cs != 1)
				Main.xPos -= 8;
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
		case VK_F1:
			if (Power)
				Power = FALSE;
			else
				Power = TRUE;
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

		if (Start)
			Game(hDC, Main, Bullet, Map, Enemy);
		else
			Interface(hDC, HELP, LEVELSELECT);

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

		if (LEVELSELECT)
		{
			if (LEVEL1CLICK(mx, my))
			{
				for (int i = 4; i < 17; ++i)
				{
					for (int j = 4; j < 17; ++j)
					{
						Map[i][j].xPos = j * 39;
						Map[i][j].yPos = i * 39;
						if (i <= 12 && i >= 8 && j <= 12 && j >= 8)
							Map[i][j].cs = 1;
						else
							Map[i][j].cs = -1;
					}
				}
				Start = TRUE;
				LEVELSELECT = FALSE;
				Level = 1;
			}

			if (LEVEL2CLICK(mx, my))
			{
				for (int i = 2; i < 19; ++i)
				{
					for (int j = 1; j < 20; ++j)
					{
						Map[i][j].xPos = j * 39;
						Map[i][j].yPos = i * 39;
						if (i <= 12 && i >= 8 && j <= 12 && j >= 8)
							Map[i][j].cs = 1;
						else
							Map[i][j].cs = -1;
					}
				}
				Start = TRUE;
				LEVELSELECT = FALSE;
				Level = 2;
			}

			if (LEVEL3CLICK(mx, my))
			{
				srand(time(0));
				for (int i = 2; i < 19; ++i)
				{
					for (int j = 1; j < 20; ++j)
					{
						Map[i][j].xPos = j * 39;
						Map[i][j].yPos = i * 39;
						if (i <= 12 && i >= 8 && j <= 12 && j >= 8)
							Map[i][j].cs = 1;
						else
							Map[i][j].cs = -1;
					}
				}
				for (int i = 0; i < 10; ++i)
				{
					while (1)
					{
						mx = rand() % 17 + 2;
						my = rand() % 19 + 1;
						if (Map[my][mx].cs == -1)
						{
							Map[my][mx].cs = 2;
							break;
						}
					}
				}
				Start = TRUE;
				LEVELSELECT = FALSE;
				Level= 3;
			}
		}

		else
		{
			if (!HELP && !Start && STARTCLICK(mx, my))
			{
				LEVELSELECT = TRUE;
			}

			if (!HELP && !Start&&EXITCLICK(mx, my))
			{
				PostQuitMessage(0);
			}

			HELP = FALSE;

			if (!HELP && !Start&&HELPCLICK(mx, my))
			{
				HELP = TRUE;
			}
		}

		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		KillTimer(hWnd, 4);
		KillTimer(hWnd, 5);
		KillTimer(hWnd, 6);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
