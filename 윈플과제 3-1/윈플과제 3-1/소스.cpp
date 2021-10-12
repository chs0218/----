#include <Windows.h>
#include <math.h>

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

struct Circle
{
	int x=0, y=0;
	char direction = 'R';
};

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

void DrawBoard(HDC hDC)
{
	int x = 0, y = 0;
	for (int i = 0; i <= 40; ++i)
		{
			MoveToEx(hDC, x, y, NULL);
			LineTo(hDC, x, y + 800);
			x += 20;
		}

	x = 0;

	for (int i = 0; i <= 40; ++i)
		{
			MoveToEx(hDC, x, y, NULL);
			LineTo(hDC, x + 800, y);
			y += 20;
		}
}

void DrawCircle(HDC hDC, int X, int Y)
{
	Ellipse(hDC, X * 20 + 6, Y * 20 + 6, X * 20 + 14, Y * 20 + 14);
}

void DrawBigCircle(HDC hDC, int X, int Y)
{
	Ellipse(hDC, X * 20 + 2, Y * 20 + 2, X * 20 + 18, Y * 20 + 18);
}

void DrawHCircle(HDC hDC, HBRUSH hBrush, HBRUSH oldBrush, const int Hero[2][20], const int nHero)
{
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Ellipse(hDC, Hero[0][0] * 20 + 2, Hero[1][0] * 20 + 2, Hero[0][0] * 20 + 18, Hero[1][0] * 20 + 18);
	if (nHero > 0)
	{
		for (int i = 1; i <= nHero; ++i)
			DrawCircle(hDC, Hero[0][i], Hero[1][i]);
	}
	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
}

void DrawBigHCircle(HDC hDC, HBRUSH hBrush, HBRUSH oldBrush, const int Hero[2][20], const int nHero)
{
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Ellipse(hDC, Hero[0][0] * 20-2, Hero[1][0] * 20-2, Hero[0][0] * 20 + 22, Hero[1][0] * 20 + 22);
	if (nHero > 0)
	{
		for (int i = 1; i <= nHero; ++i)
			DrawCircle(hDC, Hero[0][i], Hero[1][i]);
	}
	SelectObject(hDC, oldBrush);
	DeleteObject(hBrush);
}

void move(char* direction, int* X, int* Y)
{
	int random = 0;
	switch (*direction)
	{
	case('R'):
		++*X;
		if (*X > 39)
		{
			*X = 39;
			random = rand() % 3;
			switch (random)
			{
			case(0):
				*direction = 'D';
				break;
			case(1):
				*direction = 'L';
				break;
			case(2):
				*direction = 'U';
				break;
			}
		}
		break;
	case('U'):
		--*Y;
		if (*Y < 0)
		{
			*Y = 0;
			random = rand() % 3;
			switch (random)
			{
			case(0):
				*direction = 'R';
				break;
			case(1):
				*direction = 'L';
				break;
			case(2):
				*direction = 'D';
			}
		}
		break;
	case('L'):
		--*X;
		if (*X < 0)
		{
			*X = 0;
			random = rand() % 3;
			switch (random)
			{
			case(0):
				*direction = 'R';
				break;
			case(1):
				*direction = 'D';
				break;
			case(2):
				*direction = 'U';
				break;
			}
		}
		break;
	case('D'):
		++*Y;
		if (*Y > 39)
		{
			*Y = 39;
			random = rand() % 3;
			switch (random)
			{
			case(0):
				*direction = 'R';
				break;
			case(1):
				*direction = 'R';
				break;
			case(2):
				*direction = 'L';
				break;
			}
		}
		break;
	}
}

void moveHero(char* direction, int Hero[2][20], int* nHero, Circle circle[20], int* nCircle)
{
	int random = 0;
	int oldX = Hero[0][0], oldY = Hero[1][0];
	switch (*direction)
	{
	case('R'):
		++Hero[0][0];
		for (int i = 0; i < *nCircle; ++i)
		{
			if (Hero[0][0] == circle[i].x&&Hero[1][0] == circle[i].y)
			{
				++*nHero;
				if (*nHero > 19)
				{
					*nHero = 19;
					break;
				}
				Hero[0][*nHero] = Hero[0][*nHero - 1] - 1;
				Hero[1][*nHero] = Hero[1][*nHero - 1];
				for (int j = i; j < *nCircle; ++j)
				{
					circle[j] = circle[j + 1];
				}
				--*nCircle;
			}
		}

		if (Hero[0][0] > 39)
		{
			Hero[0][0] = 39;
			random = rand() % 3;
			switch (random)
			{
			case(0):
				*direction = 'D';
				break;
			case(1):
				*direction = 'L';
				break;
			case(2):
				*direction = 'U';
				break;
			}
		}
		break;
	case('U'):
		--Hero[1][0];

		for (int i = 0; i < *nCircle; ++i)
		{
			if (Hero[0][0] == circle[i].x&&Hero[1][0] == circle[i].y)
			{
				++*nHero;
				if (*nHero > 19)
				{
					*nHero = 19;
					break;
				}
				Hero[0][*nHero] = Hero[0][*nHero - 1];
				Hero[1][*nHero] = Hero[1][*nHero - 1] + 1;
				for (int j = i; j < *nCircle; ++j)
				{
					circle[j] = circle[j + 1];
				}
				--*nCircle;
			}
		}

		if (Hero[1][0] < 0)
		{
			Hero[1][0] = 0;
			random = rand() % 3;
			switch (random)
			{
			case(0):
				*direction = 'R';
				break;
			case(1):
				*direction = 'L';
				break;
			case(2):
				*direction = 'D';
			}
		}
		break;
	case('L'):
		--Hero[0][0];

		for (int i = 0; i < *nCircle; ++i)
		{
			if (Hero[0][0] == circle[i].x&&Hero[1][0] == circle[i].y)
			{
				++*nHero;
				if (*nHero > 19)
				{
					*nHero = 19;
					break;
				}
				Hero[0][*nHero] = Hero[0][*nHero - 1] + 1;
				Hero[1][*nHero] = Hero[1][*nHero - 1];
				for (int j = i; j < *nCircle; ++j)
				{
					circle[j] = circle[j + 1];
				}
				--*nCircle;
			}
		}

		if (Hero[0][0] < 0)
		{
			Hero[0][0] = 0;
			random = rand() % 3;
			switch (random)
			{
			case(0):
				*direction = 'R';
				break;
			case(1):
				*direction = 'D';
				break;
			case(2):
				*direction = 'U';
				break;
			}
		}
		break;
	case('D'):
		++Hero[1][0];

		for (int i = 0; i < *nCircle; ++i)
		{
			if (Hero[0][0] == circle[i].x&&Hero[1][0] == circle[i].y)
			{
				++*nHero;
				if (*nHero > 19)
				{
					*nHero = 19;
					break;
				}
				Hero[0][*nHero] = Hero[0][*nHero - 1];
				Hero[1][*nHero] = Hero[1][*nHero - 1] - 1;
				for (int j = i; j < *nCircle; ++j)
				{
					circle[j] = circle[j + 1];
				}
				--*nCircle;
			}
		}

		if (Hero[1][0] > 39)
		{
			Hero[1][0] = 39;
			random = rand() % 3;
			switch (random)
			{
			case(0):
				*direction = 'R';
				break;
			case(1):
				*direction = 'R';
				break;
			case(2):
				*direction = 'L';
				break;
			}
		}
		break;
	}
	for (int i = *nHero; i > 1; --i)
	{
		Hero[0][i] = Hero[0][i - 1];
		Hero[1][i] = Hero[1][i - 1];
	}
	
	if (*nHero > 0)
	{
		Hero[0][1] = oldX;
		Hero[1][1] = oldY;
	}
}

void RandomCircle(int* X, int* Y)
{
	int random = 0;
	random = rand() % 4;
	switch (random)
	{
	case 0:
		*X = 0, *Y = 0;
		break;
	case 1:
		*X = 39, *Y = 0;
		break;
	case 2:
		*X = 0, *Y = 39;
		break;
	case 3:
		*X = 39, *Y = 39;
		break;
	}
}

void Turn(char* direction, int mx, int my, int HeroX, int HeroY)
{
	int distanceX = 0, distanceY = 0;
	if (mx < HeroX * 20)
	{
		distanceX = HeroX*20 - mx;
		if (my < HeroY*20)
			distanceY = HeroY*20 - my;
		else
			distanceY = my - HeroY*20;

		if (distanceX < distanceY)
		{
			if (my < HeroY*20)
				*direction = 'U';
			else
				*direction = 'D';
		}
		else
			*direction = 'L';
	}
	else
	{
		distanceX = mx - HeroX*20;
		if (my < HeroY*20)
			distanceY = HeroY*20 - my;
		else
			distanceY = my - HeroY*20;

		if (distanceX < distanceY)
		{
			if (my < HeroY*20)
				*direction = 'U';
			else
				*direction = 'D';
		}
		else
			*direction = 'R';
	}

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hDC;
	HBRUSH hBrush = 0, oldBrush = 0;
	static  Circle circle[20] = { 0 };
	static int Board[40][40] = { 0, };
	int random = 0, mx, my;
	static int Hero[2][20] = { 0 };
	static int nHero, selected = 0;
	static char Cdirection[20];
	static char direction = 'R';
	static int CircleNum, Jump = 0, change = 0;
	static int speed = 100;
	static BOOL Selection, Selection2, Change;
	switch (iMessage) {
	case WM_CREATE:
		Hero[0][0] = 20, Hero[1][0] = 20;
		Board[Hero[0][0]][Hero[1][0]] = 1;
		SetTimer(hWnd, 2, 1000, NULL);
		CircleNum = 0, nHero = 0;
		Selection = FALSE;
		Selection2 = FALSE;
		Change = FALSE;
		SetTimer(hWnd, 1, speed, NULL);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			Board[Hero[0][nHero]][Hero[1][nHero]] = 0;
			moveHero(&direction, Hero, &nHero, circle, &CircleNum);
			Board[Hero[0][0]][Hero[1][0]] = 1;
			Board[Hero[0][nHero]][Hero[1][nHero]] = 1;
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		case 2:

			if (CircleNum < 15)
			{
				RandomCircle(&(circle[CircleNum].x), &(circle[CircleNum].y));
				Board[circle[CircleNum].x][circle[CircleNum].y] = 2;
				++CircleNum;
			}

			for (int i = 0; i < CircleNum; ++i)
			{
				Board[circle[i].x][circle[i].y] = 0;
				random = rand() % 4;
				switch (random)
				{
				case 0:
					circle[i].direction = 'R';
					break;
				case 1:
					circle[i].direction = 'L';
					break;
				case 2:
					circle[i].direction = 'U';
					break;
				case 3:
					circle[i].direction = 'D';
					break;
				}
				move(&circle[i].direction, &circle[i].x, &circle[i].y);

				if (Board[circle[i].x][circle[i].y] == 2 || Board[circle[i].x][circle[i].y] == 3)
					Board[circle[i].x][circle[i].y] = 3;
				else
					Board[circle[i].x][circle[i].y] = 2;
			}

			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT)
			direction = 'R';

		else if (wParam == VK_LEFT)
			direction = 'L';

		else if (wParam == VK_UP)
			direction = 'U';

		else if (wParam == VK_DOWN)
			direction = 'D';
		else if (wParam == VK_SPACE)
			Jump = 6;
		else if (wParam == VK_ESCAPE)
		{
			if (Change)
				Change = FALSE;
			else
				Change = TRUE;
			change = 0;
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		if (wParam == '+')
		{
			speed -= 10;
			if (speed == 0)
				speed = 10;
			SetTimer(hWnd, 1, speed, NULL);

		}
		else if (wParam == '-')
		{
			speed += 10;
			if (speed == 1000)
				speed = 990;
			SetTimer(hWnd, 1, speed, NULL);

		}

		else if (wParam == 'q' || wParam == 'Q')
			PostQuitMessage(0);

		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:

		hDC = BeginPaint(hWnd, &ps);
		DrawBoard(hDC);
		
		
		for (int i = 0; i < CircleNum; ++i)
		{

			if (Board[circle[i].x][circle[i].y] == 3)
				DrawBigCircle(hDC, circle[i].x, circle[i].y);
			else
				DrawCircle(hDC, circle[i].x, circle[i].y);
		}

		if (Selection)
			DrawBigHCircle(hDC, hBrush, oldBrush, Hero, nHero);
		else
		{
			if (Jump == 6)
			{
				if (direction == 'R' || direction == 'L')
				{
					for (int i = 0; i <= nHero; ++i)
					{
						Hero[1][i] -= 5;
						if (Hero[1][i] < 0)
						{
							Hero[1][i] += 5;
							Jump = 0;
							break;
						}
						else if (Hero[0][0] <= 6 || Hero[0][0] >= 34)
						{
							Hero[1][0] += 5;
							Jump = 0;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i <= nHero; ++i)
					{
						Hero[0][i] += 5;
						if (Hero[0][i] > 39)
						{
							Hero[0][i] -= 5;
							Jump = 0;
							break;
						}

						else if (Hero[1][0] <= 6 || Hero[1][0] >= 34)
						{
							Hero[0][i] -= 5;
							Jump = 0;
							break;
						}
					}
				}
				--Jump;
			}
			else if (Jump > 0)
			{
				if (direction == 'R' || direction == 'L')
				{
					for (int i = 0; i <= nHero; ++i)
					{
						Hero[1][i] += 1;
					}
				}
				else
				{
					for (int i = 0; i <= nHero; ++i)
					{
						Hero[0][i] -= 1;
					}
				}
				--Jump;
			}
			
			DrawHCircle(hDC, hBrush, oldBrush, Hero, nHero);

			
		}

		if (Change)
		{
			if (change == 0)
			{
				DrawBigHCircle(hDC, hBrush, oldBrush, Hero, nHero);
				change += 1;
			}
			else
			{
				change = 0;
			}
		}

		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		for (int i = 0; i < CircleNum; ++i)
		{
			if (InCircle(circle[i].x * 20 + 10, circle[i].y * 20 + 10, mx, my, 4))
			{
				Selection2 = TRUE;
				InvalidateRgn(hWnd, NULL, TRUE);
				selected = i;
			}
		}

		if (InCircle(Hero[0][0] * 20+10, Hero[1][0] * 20+10, mx, my, 8))
		{
			Selection = TRUE;
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		
		else
		{
			Turn(&direction, mx, my, Hero[0][0], Hero[1][0]);
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONUP:
		InvalidateRgn(hWnd, NULL, TRUE);
		Selection = FALSE;
		Selection2 = FALSE;
		break;

	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (mx > 40 * 20 || my > 40 * 20)
			break;



		if (Selection2)
		{
			Board[circle[selected].x][circle[selected].y] = 0;

			circle[selected].x = mx / 20;
			circle[selected].y = my / 20;

			if (Board[circle[selected].x][circle[selected].y] == 2 || Board[circle[selected].x][circle[selected].y] == 3)
				Board[circle[selected].x][circle[selected].y] = 3;
			else
				Board[circle[selected].x][circle[selected].y] = 2;

			InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}