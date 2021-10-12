#include <Windows.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define PI 3.1415926535897
#define IDC_BUTTON 100
#define IDC_BUTTON1 101
#define IDC_BUTTON2 102
#define IDC_BUTTON3 103
#define IDC_BUTTON4 104
#define ID_SCSPEED 105
#define ID_SCCIRCLE 106
#define ID_R1 10
#define ID_R2 11
#define ID_R3 12
#define ID_R4 13
#define ID_R5 14
#define ID_R6 15

int Shape = 1;
int size = 200;
int hSize = 20;
int heroSpeed = 5;
int r = 0, g = 0, b = 0;
BOOL Direction = TRUE;

HINSTANCE g_hInst;

LPCTSTR IpszClass = L"ParentClass";
LPCTSTR IpszWindowName = L"7-1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage,
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
	WndClass.lpszClassName = L"ChildClass";
	WndClass.lpfnWndProc = ChildProc;
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW,
		0, 0, 1000, 570, NULL, (HMENU)NULL, hInstance, NULL);

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

void DrawCircle(HDC hDC, double X, double Y, int Radius)
{
	Ellipse(hDC, X - Radius, Y - Radius, X + Radius, Y + Radius);
}

void DrawRectangle(HDC hDC, int X, int Y, int size)
{
	Rectangle(hDC, X - size, Y - size, X + size, Y + size);
}

void DrawTriangle(HDC hDC, int X, int Y, int size)
{
	POINT point[3];
	point[0].x = X;
	point[0].y = Y - size;
	point[1].x = X - size;
	point[1].y = Y + size;
	point[2].x = X + size;
	point[2].y = Y + size;
	Polygon(hDC, point, 3);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	static HWND hButton[2], OrbitRadio[3], OrbitSizeRadio[3], hCheck, hSpeed, hCircleSize;
	HWND child_hWnd;
	int tmpPos;
	switch (iMessage) {
	case WM_CREATE:
		child_hWnd = CreateWindow(L"ChildClass", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 500, 500, hWnd, NULL, g_hInst, NULL);
		hButton[0] = CreateWindow(L"button", L"종료", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 450, 100, 50, hWnd, (HMENU)IDC_BUTTON, g_hInst, NULL);
		hButton[1] = CreateWindow(L"button", L"반전", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600, 450, 100, 50, hWnd, (HMENU)IDC_BUTTON1, g_hInst, NULL);
		CreateWindow(L"button", L"Orbit", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 550, 5, 400, 105, hWnd, (HMENU)0, g_hInst, NULL);

		OrbitRadio[0] = CreateWindow(L"button", L"사각형", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 580, 38, 100, 50, hWnd, (HMENU)ID_R1, g_hInst, NULL); 
		OrbitRadio[1] = CreateWindow(L"button", L"원", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 700, 38, 100, 50, hWnd, (HMENU)ID_R2, g_hInst, NULL);
		OrbitRadio[2] = CreateWindow(L"button", L"삼각형", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 820, 38, 100, 50, hWnd, (HMENU)ID_R3, g_hInst, NULL);

		CreateWindow(L"button", L"OrbitSize", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 550, 110, 400, 105, hWnd, (HMENU)0, g_hInst, NULL);
		OrbitSizeRadio[0] = CreateWindow(L"button", L"소", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 580, 143, 100, 50, hWnd, (HMENU)ID_R4, g_hInst, NULL);
		OrbitSizeRadio[1] = CreateWindow(L"button", L"중", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 700, 143, 100, 50, hWnd, (HMENU)ID_R5, g_hInst, NULL);
		OrbitSizeRadio[2] = CreateWindow(L"button", L"대", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 820, 143, 100, 50, hWnd, (HMENU)ID_R6, g_hInst, NULL);

		hCheck = CreateWindow(L"button", L"Cyan", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 550, 380, 100, 50, hWnd, (HMENU)IDC_BUTTON2, g_hInst, NULL);
		hCheck = CreateWindow(L"button", L"Magenta", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 700, 380, 100, 50, hWnd, (HMENU)IDC_BUTTON3, g_hInst, NULL);
		hCheck = CreateWindow(L"button", L"Yello", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 850, 380, 100, 50, hWnd, (HMENU)IDC_BUTTON4, g_hInst, NULL);

		hSpeed = CreateWindow(L"scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 550, 233, 400, 50, hWnd, (HMENU)ID_SCSPEED, g_hInst, NULL);
		SetScrollRange(hSpeed, SB_CTL, 1, 10, TRUE);
		SetScrollPos(hSpeed, SB_CTL, 5, TRUE);
		hCircleSize = CreateWindow(L"scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 550, 313, 400, 50, hWnd, (HMENU)ID_SCCIRCLE, g_hInst, NULL);
		SetScrollRange(hCircleSize, SB_CTL, 10, 30, TRUE);
		SetScrollPos(hCircleSize, SB_CTL, 20, TRUE);
		SetTimer(hWnd, 1, 100, NULL);
		break;
	case WM_HSCROLL:
		if ((HWND)lParam == hCircleSize)
			tmpPos = hSize;
		if ((HWND)lParam == hSpeed)
			tmpPos = heroSpeed;
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			tmpPos = max(10, tmpPos - 1);
			break;
		case SB_LINERIGHT:
			tmpPos = min(30, tmpPos + 1);
			break;
		case SB_PAGELEFT:
			tmpPos = max(10, tmpPos - 10);
			break;
		case SB_PAGERIGHT:
			tmpPos = max(30, tmpPos + 10);
			break;
		case SB_THUMBTRACK:
			tmpPos = HIWORD(wParam);
			break;
		}
		if ((HWND)lParam == hCircleSize)
			hSize = tmpPos;
		if ((HWND)lParam == hSpeed)
			heroSpeed = tmpPos;
		SetScrollPos((HWND)lParam, SB_CTL, tmpPos, TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_R1:
			Shape = -1;
			break;

		case ID_R2:
			Shape = 0;
			break;

		case ID_R3:
			Shape = 1;
			break;

		case ID_R4:
			size = 180;
			break;

		case ID_R5:
			size = 200;
			break;

		case ID_R6:
			size = 220;
			break;

		case IDC_BUTTON:
			PostQuitMessage(0);
			break;
		case IDC_BUTTON1:
			if (Direction)
				Direction = FALSE;
			else
				Direction = TRUE;
			break;
		case IDC_BUTTON2:
			b -= 255;
			b = abs(b);
			g -= 255;
			g = abs(g);
			break;
		case IDC_BUTTON3:
			r -= 255;
			r = abs(r);
			b -= 255;
			b = abs(b);
			break;
		case IDC_BUTTON4:
			r -= 255;
			r = abs(r);
			g -= 255;
			g = abs(g);
			break;
		}
	case WM_PAINT:

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		
		break;

	case WM_LBUTTONUP:
		
		break;
	case WM_MOUSEMOVE:
		
		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	static HDC hDC, MemDC;
	HDC tmphDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	int tmp;

	static double hX = 450, hY = 250, theta;

	switch (iMessage) {
	case WM_CREATE:
		theta = 0;
		SetTimer(hWnd, 1, heroSpeed, NULL);
		break;
	case WM_TIMER:
		if (Direction)
			theta += heroSpeed;
		else
			theta -= heroSpeed;
		if (theta < 0)
		{
			theta = 360 + theta;
		}
		theta = (int)theta % 360;
		switch (Shape)
		{
		case -1:
			if ((theta <= 45 && theta >= 0) || (315 <= theta && 360 >= theta))
				hX = 250 + size;
			else if (theta >= 135 && theta <= 225)
				hX = 250 - size;
			else
				hX = 250 + size * cos(getRadian(theta));
			if (theta >= 45 && theta <= 135)
				hY = 250 + size;
			else if(theta >= 225 && theta <= 315)
				hY = 250 - size;
			else
				hY = 250 + size * sin(getRadian(theta));
			break;
		case 0:
			hX = 250 + size * cos(getRadian(theta));
			hY = 250 + size * sin(getRadian(theta));
			break;
		case 1:
			if (0 <= theta && 120 > theta)
			{
				hX = (250 + (((float)size / 120.0) * theta));
				hY = (250 - size) + (((float)size / 60.0)*theta);
			}
			else if (120 <= theta && 240 > theta)
			{
				tmp = (int)theta % 120;
				hX = ((250 + size) - (((float)size / 60.0)*tmp));
				hY = 250 + size;
			}
			else
			{
				tmp = (int)theta % 120;
				hX = (250 - size) + (((float)size / 120.0)*tmp);
				hY = (250 + size) - (((float)size / 60.0)*tmp);
			}
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:

		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		hBrush = CreateSolidBrush(RGB(100, 100, 100));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		Rectangle(hDC, 0, 0, 500, 500);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		hPen = CreatePen(PS_SOLID, 3, RGB(135, 255, 255));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		MoveToEx(hDC, 0, 250, NULL);
		LineTo(hDC, 500, 250);
		MoveToEx(hDC, 250, 0, NULL);
		LineTo(hDC, 250, 500);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
		
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		switch (Shape)
		{
		case -1:
			DrawRectangle(hDC, 250, 250, size);
			break;
		case 0:
			DrawCircle(hDC, 250, 250, size);
			break;
		case 1:
			DrawTriangle(hDC, 250, 250, size);
			break;
		default:
			break;
		}

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		hPen = CreatePen(PS_SOLID, 3, RGB(135, 135, 135));
		oldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(r, g, b));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		DrawCircle(hDC, hX, hY, hSize);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hDC, oldPen);
		DeleteObject(hPen);

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

		break;

	case WM_LBUTTONUP:

		break;
	case WM_MOUSEMOVE:

		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
