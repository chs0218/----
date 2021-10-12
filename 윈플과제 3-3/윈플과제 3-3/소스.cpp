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

void DrawLine(HDC hDC, HBRUSH hBrush, HBRUSH oldBrush)
{
	MoveToEx(hDC, 0, 300, NULL);
	LineTo(hDC, 300, 300);

	MoveToEx(hDC, 300, 0, NULL);
	LineTo(hDC, 300, 300);

	MoveToEx(hDC, 600, 0, NULL);
	LineTo(hDC, 600, 300);

	MoveToEx(hDC, 600, 300, NULL);
	LineTo(hDC, 900, 300);

	MoveToEx(hDC, 0, 600, NULL);
	LineTo(hDC, 300, 600);

	MoveToEx(hDC, 600, 600, NULL);
	LineTo(hDC, 600, 900);

	MoveToEx(hDC, 300, 600, NULL);
	LineTo(hDC, 300, 900);

	MoveToEx(hDC, 600, 600, NULL);
	LineTo(hDC, 900, 600);

	MoveToEx(hDC, 55, 450, NULL);
	LineTo(hDC, 245, 450);

	MoveToEx(hDC, 450, 55, NULL);
	LineTo(hDC, 450, 245);

	MoveToEx(hDC, 655, 450, NULL);
	LineTo(hDC, 845, 450);

	MoveToEx(hDC, 450, 655, NULL);
	LineTo(hDC, 450, 845);
	// 횡단보도 1
	MoveToEx(hDC, 290, 400, NULL);
	LineTo(hDC, 410, 280);

	MoveToEx(hDC, 330, 440, NULL);
	LineTo(hDC, 450, 320);

	MoveToEx(hDC, 290, 400, NULL);
	LineTo(hDC, 330, 440);

	MoveToEx(hDC, 410, 280, NULL);
	LineTo(hDC, 450, 320);

	// 횡단보도 2
	MoveToEx(hDC, 370, 480, NULL);
	LineTo(hDC, 490, 360);

	MoveToEx(hDC, 410, 520, NULL);
	LineTo(hDC, 530, 400);

	MoveToEx(hDC, 370, 480, NULL);
	LineTo(hDC, 410, 520);

	MoveToEx(hDC, 490, 360, NULL);
	LineTo(hDC, 530, 400);

	// 횡단보도 3
	MoveToEx(hDC, 450, 560, NULL);
	LineTo(hDC, 570, 440);

	MoveToEx(hDC, 490, 600, NULL);
	LineTo(hDC, 610, 480);

	MoveToEx(hDC, 450, 560, NULL);
	LineTo(hDC, 490, 600);

	MoveToEx(hDC, 610, 480, NULL);
	LineTo(hDC, 570, 440);
	
}

struct Car
{
	RECT rect;
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

void DrawSign(HDC hDC, BOOL RED, BOOL YELLO, BOOL BLUE)
{
	HBRUSH hBrush, oldBrush;

	// 신호등
	Rectangle(hDC, 750, 50, 920, 100);
	Ellipse(hDC, 750, 50, 800, 100);
	Ellipse(hDC, 810, 50, 860, 100);
	Ellipse(hDC, 870, 50, 920, 100);

	if (RED)
	{
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, 750, 50, 800, 100);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
	}

	else if (YELLO)
	{
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, 810, 50, 860, 100);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
	}

	else if (BLUE)
	{
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, 870, 50, 920, 100);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
	}
}

void MoveCar(Car car[4], int n, BOOL GO[4], int order[], int* ordernum, BOOL Sign[3])
{
	switch (n)
	{
	case 1:
		if (GO[0])
		{
			car[0].rect.top += 10;
			car[0].rect.bottom += 10;
			
			if (car[0].rect.bottom > 900)
				car[0].rect.bottom = 20;
			else if (car[0].rect.top > 900)
				car[0].rect.top = 20;
			else if (car[0].rect.bottom == 300)
			{
				GO[0] = FALSE;
				order[*ordernum] = 0;
				++*ordernum;
			}

		}
		break;
	case 2:
		if (GO[1])
		{
			car[1].rect.left -= 10;
			car[1].rect.right -= 10;
			if (car[1].rect.left < 0)
				car[1].rect.left = 880;
			else if (car[1].rect.right < 0)
				car[1].rect.right = 880;
			else if (car[1].rect.left == 600)
			{
				GO[1] = FALSE;
				order[*ordernum] = 1;
				++*ordernum;
			}
		}
		break;
	case 3:
		if (GO[2])
		{
			car[2].rect.top -= 10;
			car[2].rect.bottom -= 10;
			if (car[2].rect.top < 0)
				car[2].rect.top = 880;
			else if (car[2].rect.bottom < 0)
				car[2].rect.bottom = 880;
			else if (car[2].rect.top == 600)
			{
				GO[2] = FALSE;
				order[*ordernum] = 2;
				++*ordernum;
			}
		}
		break;
	case 4:
		if (GO[3])
		{
			car[3].rect.left += 10;
			car[3].rect.right += 10;
			if (car[3].rect.right > 900)
				car[3].rect.right = 20;
			else if (car[3].rect.left > 900)
				car[3].rect.left = 20;
			else if (car[3].rect.right == 300)
			{
				GO[3] = FALSE;
				order[*ordernum] = 3;
				++*ordernum;
			}
		}
		break;
	}
}

void DrawCar(HDC hDC, Car car[4])
{
	if (car[0].rect.top > car[0].rect.bottom)
	{
		MoveToEx(hDC, car[0].rect.left, 10, NULL);
		LineTo(hDC, car[0].rect.left, car[0].rect.bottom);

		MoveToEx(hDC, car[0].rect.right, 10, NULL);
		LineTo(hDC, car[0].rect.right, car[0].rect.bottom);

		MoveToEx(hDC, car[0].rect.left, car[0].rect.bottom, NULL);
		LineTo(hDC, car[0].rect.right, car[0].rect.bottom);

		MoveToEx(hDC, car[0].rect.left, car[0].rect.top, NULL);
		LineTo(hDC, car[0].rect.left, 900);

		MoveToEx(hDC, car[0].rect.right, car[0].rect.top, NULL);
		LineTo(hDC, car[0].rect.right, 900);

		MoveToEx(hDC, car[0].rect.left, car[0].rect.top, NULL);
		LineTo(hDC, car[0].rect.right, car[0].rect.top);
	}

	else
		Rectangle(hDC, car[0].rect.left, car[0].rect.top, car[0].rect.right, car[0].rect.bottom);

	if(car[1].rect.left> car[1].rect.right)
	{
		MoveToEx(hDC, car[1].rect.left, car[1].rect.top, NULL);
		LineTo(hDC, 900, car[1].rect.top);

		MoveToEx(hDC, car[1].rect.left, car[1].rect.bottom, NULL);
		LineTo(hDC, 900, car[1].rect.bottom);

		MoveToEx(hDC, car[1].rect.left, car[1].rect.top, NULL);
		LineTo(hDC, car[1].rect.left, car[1].rect.bottom);

		MoveToEx(hDC, 0, car[1].rect.top, NULL);
		LineTo(hDC, car[1].rect.right, car[1].rect.top);

		MoveToEx(hDC, 0, car[1].rect.bottom, NULL);
		LineTo(hDC, car[1].rect.right, car[1].rect.bottom);

		MoveToEx(hDC, car[1].rect.right, car[1].rect.top, NULL);
		LineTo(hDC, car[1].rect.right, car[1].rect.bottom);
	}
	else
		Rectangle(hDC, car[1].rect.left, car[1].rect.top, car[1].rect.right, car[1].rect.bottom);

	if (car[2].rect.bottom < car[2].rect.top)
	{
		MoveToEx(hDC, car[2].rect.left, car[2].rect.top, NULL);
		LineTo(hDC, car[2].rect.left, 900);

		MoveToEx(hDC, car[2].rect.right, car[2].rect.top, NULL);
		LineTo(hDC, car[2].rect.right, 900);
		
		MoveToEx(hDC, car[2].rect.left, car[2].rect.top, NULL);
		LineTo(hDC, car[2].rect.right, car[2].rect.top);

		MoveToEx(hDC, car[2].rect.left, 0, NULL);
		LineTo(hDC, car[2].rect.left, car[2].rect.bottom);

		MoveToEx(hDC, car[2].rect.right, 0, NULL);
		LineTo(hDC, car[2].rect.right, car[2].rect.bottom);

		MoveToEx(hDC, car[2].rect.left, car[2].rect.bottom, NULL);
		LineTo(hDC, car[2].rect.right, car[2].rect.bottom);
	}
	else
		Rectangle(hDC, car[2].rect.left, car[2].rect.top, car[2].rect.right, car[2].rect.bottom);

	if (car[3].rect.right < car[3].rect.left)
	{
		MoveToEx(hDC, car[3].rect.left, car[3].rect.top, NULL);
		LineTo(hDC, 900, car[3].rect.top);

		MoveToEx(hDC, car[3].rect.left, car[3].rect.bottom, NULL);
		LineTo(hDC, 900, car[3].rect.bottom);

		MoveToEx(hDC, car[3].rect.left, car[3].rect.top, NULL);
		LineTo(hDC, car[3].rect.left, car[3].rect.bottom);

		MoveToEx(hDC, car[3].rect.right, car[3].rect.top, NULL);
		LineTo(hDC, 0, car[3].rect.top);

		MoveToEx(hDC, car[3].rect.right, car[3].rect.bottom, NULL);
		LineTo(hDC, 0, car[3].rect.bottom);

		MoveToEx(hDC, car[3].rect.right, car[3].rect.top, NULL);
		LineTo(hDC, car[3].rect.right, car[3].rect.bottom);
	}
	else
		Rectangle(hDC, car[3].rect.left, car[3].rect.top, car[3].rect.right, car[3].rect.bottom);
}

void MoveHuman(HDC hDC, int HumanX, int HumanY)
{
	// 사람
	Ellipse(hDC, HumanX, HumanY, HumanX + 50, HumanY + 50);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{

	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;

	HBRUSH hBrush = 0, oldBrush = 0;
	static Car car[4];
	static int order[4] = { 0, };
	int mx, my;
	static BOOL Sign[3];
	static BOOL GO[4];
	static int Wait = 0;
	static int speed = 30;
	static int HumanX = 250, HumanY = 250, HumanDirection = 0;
	static BOOL MOVE;
	switch (iMessage) {
	case WM_CREATE:
		car[0].rect = { 330,10,420,150 };
		car[1].rect = { 750,330,890,420 };
		car[2].rect = { 480,750,570,890 };
		car[3].rect = { 10,480,150,570 };
		Sign[0] = FALSE;
		Sign[1] = FALSE;
		Sign[2] = TRUE;
		MOVE = FALSE;
		
		for (int i = 0; i < 4; ++i)
			GO[i] = TRUE;

		SetTimer(hWnd, 1, 40, NULL);
		SetTimer(hWnd, 2, 50, NULL);
		SetTimer(hWnd, 3, 70, NULL);
		SetTimer(hWnd, 4, 30, NULL);
		SetTimer(hWnd, 5, 2000, NULL);

		break;
	case WM_CHAR:
		if (wParam == '+')
		{
			speed -= 10;
			{
				if (speed == 0)
					speed = 10;
			}
			SetTimer(hWnd, 1, speed+10, NULL);
			SetTimer(hWnd, 2, speed+20, NULL);
			SetTimer(hWnd, 3, speed+40, NULL);
			SetTimer(hWnd, 4, speed, NULL);
		}
		else if (wParam == '-')
		{
			speed += 10;
			if (speed > 1000)
				speed = 1000;

			SetTimer(hWnd, 1, speed + 10, NULL);
			SetTimer(hWnd, 2, speed + 20, NULL);
			SetTimer(hWnd, 3, speed + 40, NULL);
			SetTimer(hWnd, 4, speed, NULL);
		}
	case WM_TIMER:
		if (wParam == 1)
			MoveCar(car, 1, GO, order, &Wait, Sign);

		if (wParam == 2)
			MoveCar(car, 2, GO, order, &Wait, Sign);

		if (wParam == 3)
			MoveCar(car, 3, GO, order, &Wait, Sign);

		if (wParam == 4)
			MoveCar(car, 4, GO, order, &Wait, Sign);

		if (wParam == 5)
		{
			if (Sign[2]||Sign[1])
			{
				if (Wait > 0)
				{
					if (HumanX == 250 || HumanX == 650)
					{
						GO[order[0]] = TRUE;
						for (int i = 0; i < Wait; ++i)
						{
							order[i] = order[i + 1];
						}
						--Wait;
					}
				}
			}
		}

		else if (wParam == 6)
		{
			if (Sign[1])
			{
				Sign[0] = TRUE;
				Sign[1] = FALSE;
				MOVE = TRUE;
			}
		}

		if (wParam == 7)
		{
			if (MOVE)
			{
				if (HumanDirection == 0)
				{
					HumanX += 10;
					HumanY += 10;
					if (HumanX >= 650)
					{
						HumanDirection = 1;
						if (Sign[1] || Sign[2])
							MOVE = FALSE;
					}
				}
				else
				{
					HumanX -= 10;
					HumanY -= 10;

					if (HumanX <= 250)
					{
						HumanDirection = 0;
						if (Sign[1] || Sign[2])
							MOVE = FALSE;
					}
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




		DrawLine(hDC, hBrush, oldBrush);

		DrawCar(hDC, car);

		DrawSign(hDC, Sign[0], Sign[1], Sign[2]);

		
		MoveHuman(hDC, HumanX, HumanY);
		
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

		if (InCircle(775, 75, mx, my, 25))
		{
			Sign[0] = TRUE;
			Sign[1] = FALSE;
			Sign[2] = FALSE;
			SetTimer(hWnd, 7, 100, NULL);
			MOVE = TRUE;
		}

		else if (InCircle(835, 75, mx, my, 25))
		{
			Sign[0] = FALSE;
			Sign[1] = TRUE;
			Sign[2] = FALSE;
			SetTimer(hWnd, 6, 1000, NULL);
		}

		else if (InCircle(895, 75, mx, my, 25))
		{
			Sign[0] = FALSE;
			Sign[1] = FALSE;
			Sign[2] = TRUE;
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}