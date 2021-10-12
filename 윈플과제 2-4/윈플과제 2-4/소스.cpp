#include <Windows.h>
#include <random>
#include <time.h>

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
		0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

char shape[] = "■";

void DrawBoard(HDC hDC)
{
	int x = 0, y = 0;
	for (int i = 0; i <= 20; ++i)
	{
		MoveToEx(hDC, x, y, NULL);
		LineTo(hDC, x, y + 400);
		x += 20;
	}

	x = 0;

	for (int i = 0; i <= 20; ++i)
	{
		MoveToEx(hDC, x, y, NULL);
		LineTo(hDC, x + 400, y);
		y += 20;
	}
}

void DrawRedZone(HDC hDC)
{
	int x = 160, y = 160;
	Rectangle(hDC, x, y, x + 80, y + 80);
}

void RandomCoordinate(int* Black_X, int* Black_Y, int* White_X, int* White_Y)
{
	std::default_random_engine dre(time(0));
	std::uniform_int_distribution<> uid(0,19);

	while (1)
	{
		*Black_X = uid(dre);
		*Black_Y = uid(dre);
		if (*Black_X > 7 && *Black_X < 12 && *Black_Y>7 && *Black_Y < 12)
			continue;
		else
			break;
	}

	while (1)
	{
		*White_X = uid(dre);
		*White_Y = uid(dre);

		if (*Black_X == *White_X&&*Black_Y == *White_Y)
			continue;
		else if (*White_X > 7 && *White_X < 12 && *White_Y>7 && *White_Y < 12)
			continue;
		else break;
	}
}

void RandomBCoordinate(int* Black_X, int* Black_Y, int White_X, int White_Y)
{
	std::default_random_engine dre(time(0));
	std::uniform_int_distribution<> uid(0, 19);

	while (1)
	{
		*Black_X = uid(dre);
		*Black_Y = uid(dre);

		if (*Black_X == White_X&&*Black_Y == White_Y)
			continue;
		else if (*Black_X > 7 && *Black_X < 12 && *Black_Y>7 && *Black_Y < 12)
			continue;
		else break;
	}
}

void RandomWCoordinate(int Black_X, int Black_Y, int* White_X, int* White_Y)
{
	std::default_random_engine dre(time(0));
	std::uniform_int_distribution<> uid(0, 19);

	while (1)
	{
		*White_X = uid(dre);
		*White_Y = uid(dre);

		if (Black_X == *White_X&&Black_Y == *White_Y)
			continue;
		else if (*White_X > 7 && *White_X < 12 && *White_Y>7 && *White_Y < 12)
			continue;
		else break;
	}
}

void DrawStone(HDC hDC, const int x, const int y)
{
	Rectangle(hDC, x + 3, y + 3, x + 18, y + 18);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hDC;
	HBRUSH hBrush, oldBrush;
	static int Black_X = 0, Black_Y = 0, White_X = 0, White_Y = 0;
	static int order = 0;
	static int RedZone[4][4] = { 0 };
	static int newgame = 0;
	switch (iMessage) {
	case WM_CREATE:
		RandomCoordinate(&Black_X, &Black_Y, &White_X, &White_Y);
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);
		if (wParam == 'w')
		{
			if (order == 1)
			{
				TextOutA(hDC, 0, 500, "같은 돌을 두번 놓을 수 없습니다", 31);
				break;
			}

			Black_Y -= 1;

			if (Black_Y < 0)
				Black_Y = 0;
			else if (Black_X > 7 && Black_X < 12 && Black_Y>7 && Black_Y < 12)
			{
				if (Black_X == 8)
					RedZone[3][0] = 1;

				else if (Black_X == 9)
					RedZone[3][1] = 1;

				else if (Black_X == 10)
					RedZone[3][2] = 1;

				else
					RedZone[3][3] = 1;

				RandomBCoordinate(&Black_X, &Black_Y, White_X, White_Y);
			}
			else if (Black_X == White_X && Black_Y == White_Y)
				Black_Y += 1;

			order = 1;
		}

		else if (wParam == 's')
		{
			if (order == 1)
			{
				TextOutA(hDC, 0, 500, "같은 돌을 두번 놓을 수 없습니다", 31);
				break;
			}

			Black_Y += 1;
			if (Black_Y > 19)
				Black_Y = 19;
			else if (Black_X > 7 && Black_X < 12 && Black_Y>7 && Black_Y < 12)
			{
				if (Black_X == 8)
					RedZone[0][0] = 1;

				else if (Black_X == 9)
					RedZone[0][1] = 1;

				else if (Black_X == 10)
					RedZone[0][2] = 1;

				else
					RedZone[0][3] = 1;

				RandomBCoordinate(&Black_X, &Black_Y, White_X, White_Y);
			}
			else if (Black_X == White_X && Black_Y == White_Y)
				Black_Y -= 1;

			order = 1;
		}

		else if (wParam == 'a')
		{
			if (order == 1)
			{
				TextOutA(hDC, 0, 500, "같은 돌을 두번 놓을 수 없습니다", 31);
				break;
			}

			Black_X -= 1;
			if (Black_X < 0)
				Black_X = 0;

			else if (Black_X > 7 && Black_X < 12 && Black_Y>7 && Black_Y < 12)
			{
				if (Black_Y == 8)
					RedZone[0][3] = 1;

				else if (Black_Y == 9)
					RedZone[1][3] = 1;

				else if (Black_Y == 10)
					RedZone[2][3] = 1;

				else
					RedZone[3][3] = 1;

				RandomBCoordinate(&Black_X, &Black_Y, White_X, White_Y);
			}

			else if (Black_X == White_X && Black_Y == White_Y)
				Black_X += 1;

			order = 1;
		}

		else if (wParam == 'd')
		{
		
		if (order == 1)
		{
			TextOutA(hDC, 0, 500, "같은 돌을 두번 놓을 수 없습니다", 31);
			break;
		}

			Black_X += 1;
			if (Black_X > 19)
				Black_X = 19;
			else if (Black_X > 7 && Black_X < 12 && Black_Y>7 && Black_Y < 12)
			{
				if (Black_Y == 8)
					RedZone[0][0] = 1;

				else if (Black_Y == 9)
					RedZone[1][0] = 1;

				else if (Black_Y == 10)
					RedZone[2][0] = 1;

				else
					RedZone[3][0] = 1;

				RandomBCoordinate(&Black_X, &Black_Y, White_X, White_Y);
			}
			else if (Black_X == White_X && Black_Y == White_Y)
				Black_X -= 1;

			order = 1;
		}

		if (wParam == 'i')
		{
			if (order == 0)
			{
				TextOutA(hDC, 0, 500, "같은 돌을 두번 놓을 수 없습니다", 31);
				break;
			}

			White_Y -= 1;

			if (White_Y < 0)
				White_Y = 0;
			else if (White_X > 7 && White_X < 12 && White_Y>7 && White_Y < 12)
			{
				if (White_X == 8)
					RedZone[3][0] = 2;

				else if (White_X == 9)
					RedZone[3][1] = 2;

				else if (White_X == 10)
					RedZone[3][2] = 2;

				else
					RedZone[3][3] = 2;

				RandomWCoordinate(Black_X, Black_Y, &White_X, &White_Y);
			}
			else if (Black_X == White_X && Black_Y == White_Y)
				White_Y += 1;

			order = 0;
		}

		else if (wParam == 'k')
		{
			if (order == 0)
			{
				TextOutA(hDC, 0, 500, "같은 돌을 두번 놓을 수 없습니다", 31);
				break;
			}

			White_Y += 1;
			if (White_Y > 19)
				White_Y = 19;
			else if (White_X > 7 && White_X < 12 && White_Y>7 && White_Y < 12)
			{
				if (White_X == 8)
					RedZone[0][0] = 2;

				else if (White_X == 9)
					RedZone[0][1] = 2;

				else if (White_X == 10)
					RedZone[0][2] = 2;

				else
					RedZone[0][3] = 2;

				RandomWCoordinate(Black_X, Black_Y, &White_X, &White_Y);
			}
			else if (Black_X == White_X && Black_Y == White_Y)
				White_Y -= 1;

			order = 0;
		}

		else if (wParam == 'j')
		{
			if (order == 0)
			{
				TextOutA(hDC, 0, 500, "같은 돌을 두번 놓을 수 없습니다", 31);
				break;
			}

			White_X -= 1;
			if (White_X < 0)
				White_X = 0;

			else if (White_X > 7 && White_X < 12 && White_Y>7 && White_Y < 12)
			{
				if (White_Y == 8)
					RedZone[0][3] = 2;

				else if (White_Y == 9)
					RedZone[1][3] = 2;

				else if (White_Y == 10)
					RedZone[2][3] = 2;

				else
					RedZone[3][3] = 2;

				RandomWCoordinate(Black_X, Black_Y, &White_X, &White_Y);
			}

			else if (Black_X == White_X && Black_Y == White_Y)
				White_X += 1;

			order = 0;
		}

		else if (wParam == 'l')
		{
		if (order == 0)
		{
			TextOutA(hDC, 0, 500, "같은 돌을 두번 놓을 수 없습니다", 31);
			break;
		}

			White_X += 1;
			if (White_X > 19)
				White_X = 19;
			else if (White_X > 7 && White_X < 12 && White_Y>7 && White_Y < 12)
			{
				if (White_Y == 8)
					RedZone[0][0] = 2;

				else if (White_Y == 9)
					RedZone[1][0] = 2;

				else if (White_Y == 10)
					RedZone[2][0] = 2;

				else
					RedZone[3][0] = 2;

				RandomWCoordinate(Black_X, Black_Y, &White_X, &White_Y);
			}
			else if (Black_X == White_X && Black_Y == White_Y)
				White_X -= 1;

			order = 0;
		}
		else if (wParam == 'r' || wParam == 'R')
		{
			newgame = 1;
		}
		else if (wParam == 'q' || wParam == 'Q')
		{
			PostQuitMessage(0);
		}
		



		ReleaseDC(hWnd, hDC);

		InvalidateRgn(hWnd, NULL, TRUE);
		
		break;

	case WM_PAINT:
		if (newgame == 1)
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
					RedZone[i][j] = 0;
			}
			RandomCoordinate(&Black_X, &Black_Y, &White_X, &White_Y);
			order = 0;
			newgame = 0;
		}
		hDC = BeginPaint(hWnd, &ps);

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		DrawRedZone(hDC);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		DrawBoard(hDC);

		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		DrawStone(hDC, Black_X * 20, Black_Y * 20);

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (RedZone[i][j] == 1)
					DrawStone(hDC, (j + 8) * 20, (i + 8) * 20);
			}
		}

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		DrawStone(hDC, White_X * 20, White_Y * 20);

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (RedZone[i][j] == 2)
					DrawStone(hDC, (j + 8) * 20, (i + 8) * 20);
			}
		}

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}
