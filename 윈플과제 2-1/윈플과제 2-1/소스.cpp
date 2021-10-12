#include <Windows.h>
#include <random>
#include <time.h>
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
		0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}


char Shape[] = "¡á";
char Vline[] = "¦¢";
char Hline[] = "¦¡";
char Center[] = "¦«";

class Point{
public:
	int x, y;
};


Point* point = new Point[4];

void Drawline(HDC hDC, PAINTSTRUCT ps, HWND hWnd)
{
	int x = 400, y = 0;
	for (int i = 0; i < 43; ++i)
	{
		TextOutA(hDC, x, y, Vline, strlen(Vline));
		y += 13;
	}

	x = 0, y = 270;

	for (int i = 0; i < 60; ++i)
	{
		TextOutA(hDC, x, y, Hline, strlen(Hline));
		x += 13;
	}
	x = 0, y = 0;
	TextOutA(hDC, 400, 270, Center, strlen(Center));

}


void DrawX(HDC hDC, PAINTSTRUCT ps, HWND hWnd, int x, int y)
{

	SetBkColor(hDC, RGB(0, 0, 0));
	SetTextColor(hDC, RGB(255, 0, 0));
	int firstY = y;
	for (int i = 0; i < 17; ++i)
	{
		TextOutA(hDC, x, y, Shape, strlen(Shape));
		x += 20;
		y += 13;
	}
	y = firstY;
	x -= 20;
	for (int i = 0; i < 17; ++i)
	{
		TextOutA(hDC, x, y, Shape, strlen(Shape));
		x -= 20;
		y += 13;
	}
}

void DrawAngleTrine(HDC hDC, PAINTSTRUCT ps, HWND hWnd, int x, int y)
{
	SetBkColor(hDC, RGB(135, 255, 255));
	SetTextColor(hDC, RGB(135, 0, 255));
	int firstX = x;
	int num = 25;
	for (int i = 0 ; i < 17; i++)
	{
		for (int j = num; j > 0; --j)
		{
			TextOutA(hDC, x, y, Shape, strlen(Shape));
			x += 13;
		}
		firstX += 13;
		x = firstX;
		y += 13;
		num -= 2;
	}
}

void DrawRhombus(HDC hDC, PAINTSTRUCT ps, HWND hWnd, int x, int y)
{
	SetBkColor(hDC, RGB(135, 255, 0));
	SetTextColor(hDC, RGB(135, 0, 135));
	int firstX = x + 160;
	for (int i = 0; i < 7; i++)
	{
		x = firstX;
		for (int j = 0; j < 2 * i + 1; ++j)
		{
			TextOutA(hDC, x, y, Shape, strlen(Shape));
			x += 20;
		}
		firstX -= 20;
		y += 14;
	}

	firstX += 20;
	y -= 14;
	for (int i = 6; i >= 0 ; --i)
	{
		x = firstX;
		for (int j = 2*i+1; j >0; --j)
		{
			TextOutA(hDC, x, y, Shape, strlen(Shape));
			x += 20;
		}
		firstX += 20;
		y += 14;
	}


}

void DrawButterfly(HDC hDC, PAINTSTRUCT ps, HWND hWnd, int x, int y)
{
	SetBkColor(hDC, RGB(135, 90, 0));
	SetTextColor(hDC, RGB(135, 120, 210));
	x += 30;
	int firstX = x;
	int n;
	int k = x + 130;
	for (int i = 0; i < 7; ++i)
	{
		x = firstX;
		for (int j = 0; j <= i; ++j)
		{
			n = k - x;
			TextOutA(hDC, x, y, Shape, strlen(Shape));

			TextOutA(hDC, k + n, y, Shape, strlen(Shape));
			x += 20;
		}
		y += 14;
	}

	y -= 14;

	for (int i = 6; i >= 0; --i)
	{
		x = firstX;
		for (int j = 0; j <= i; ++j)
		{
			n = k - x;
			TextOutA(hDC, x, y, Shape, strlen(Shape));

			TextOutA(hDC, k + n, y, Shape, strlen(Shape));
			x += 20;
		}
		y += 14;
	}

}


void DrawRandom(HDC hDC, PAINTSTRUCT ps, HWND hWnd, int x, int y)
{

	std::default_random_engine dre(time(0));
	std::uniform_int_distribution<> uid(1, 4);
	x = 30, y = 20;
	int random = 0;
	int check[4] = { 0 };

	random = uid(dre);

	switch (random)
	{
	case (1):
		DrawX(hDC, ps, hWnd, x, y);
		break;
	case (2):
		DrawRhombus(hDC, ps, hWnd, x, y);
		break;
	case (3):
		DrawButterfly(hDC, ps, hWnd, x, y);
		break;
	case (4):
		DrawAngleTrine(hDC, ps, hWnd, x, y);
		break;
	}
	check[random - 1] = 1;

	x = 430, y = 20;
	while (1)
	{
		random = uid(dre);

		if (check[random-1] == 0)
		{
			switch (random)
			{
			case (1):
				DrawX(hDC, ps, hWnd, x, y);
				break;
			case (2):
				DrawRhombus(hDC, ps, hWnd, x, y);
				break;
			case (3):
				DrawButterfly(hDC, ps, hWnd, x, y);
				break;
			case (4):
				DrawAngleTrine(hDC, ps, hWnd, x, y);
				break;
			}

			check[random - 1] = 1;

			break;
		}
		
	}
	x = 30, y = 320;
	while (1)
	{
		random = uid(dre);

		if (check[random-1] == 0)
		{
			switch (random)
			{
			case (1):
				DrawX(hDC, ps, hWnd, x, y);
				break;
			case (2):
				DrawRhombus(hDC, ps, hWnd, x, y);
				break;
			case (3):
				DrawButterfly(hDC, ps, hWnd, x, y);
				break;
			case (4):
				DrawAngleTrine(hDC, ps, hWnd, x, y);
				break;
			}

			check[random - 1] = 1;

			break;
		}
		
	}
	x = 430, y = 320;

	while (1)
	{
		random = uid(dre);

		if (check[random - 1] == 0)
		{
			switch (random)
			{
			case (1):
				DrawX(hDC, ps, hWnd, x, y);
				break;
			case (2):
				DrawRhombus(hDC, ps, hWnd, x, y);
				break;
			case (3):
				DrawButterfly(hDC, ps, hWnd, x, y);
				break;
			case (4):
				DrawAngleTrine(hDC, ps, hWnd, x, y);
				break;
			}

			check[random - 1] = 1;

			break;
		}

	}
	
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hDC;
	int x = 0, y = 0;
	char c;

	switch (iMessage) {
	case WM_KEYDOWN:
		c = wParam;
		if (wParam == 'n' || wParam == 'N')
		{
			InvalidateRgn(hWnd, NULL, TRUE);
		}

		else if (wParam == 'Q' || wParam == 'q')
		{
			PostQuitMessage(0);
		}
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		Drawline(hDC, ps, hWnd);
		DrawRandom(hDC, ps, hWnd, x, y);
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}
