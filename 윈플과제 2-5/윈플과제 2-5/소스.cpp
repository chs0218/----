#include <Windows.h>
#include <tchar.h>
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hDC;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	static char str[100] = { '\0', };
	static int num = 0;
	static int Shape, Top, Left, Bottom, Right, Th;
	RECT Box = { 0, 530, 490, 560};
	static SIZE size;
	static int check = 0;
	switch (iMessage) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		Shape = 0;
		ShowCaret(hWnd);
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_UP)
		{
			if (Shape == 0)
				Shape = -1;

			Top -= 20, Bottom -= 20;
			if (Top < 0)
			{
				Top += 20;
				Bottom += 20;
			}
			InvalidateRgn(hWnd, NULL, TRUE);

		}
		else if (wParam == VK_DOWN)
		{
			if (Shape == 0)
				Shape = -1;

			Top += 20, Bottom += 20;
			if (Bottom > 530)
			{
				Top -= 20;
				Bottom -= 20;
			}
			InvalidateRgn(hWnd, NULL, TRUE);

		}
		else if (wParam == VK_RIGHT)
		{

			if (Shape == 0)
				Shape = -1;

			Left += 20;
			Right += 20;
			if (Right > 780)
			{
				Left -= 20;
				Right -= 20;
			}
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		else if (wParam == VK_LEFT)
		{

			if (Shape == 0)
				Shape = -1;

			Left -= 20;
			Right -= 20;
			if (Left < 0)
			{
				Left += 20;
				Right += 20;
			}
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		
		ReleaseDC(hWnd, hDC);
		break;
	case WM_CHAR:
		if (wParam == VK_BACK)
		{
			--num;

			if (num < 0)
			{
				num = 0;
				break;
			}
			
		}
		else if (wParam == VK_RETURN)
		{
			sscanf(str, "%d %d %d %d %d %d", &Shape, &Left, &Top, &Right, &Bottom, &Th);
			for (int i = 0; i < num; ++i)
				str[i] = '\0';
			check = 1;
			num = 0;
		}
		else if (wParam == '+')
		{
			if (Shape == 0)
				Shape = -1;
			else 
				++Th;
		}
		else if (wParam == '-')
		{
			if (Shape == 0)
				Shape = -1;
			else
				--Th;
			if (Th == 0)
				Th = 1;
		}
		else 
			str[num++] = wParam;
		str[num] = '\0';
		InvalidateRgn(hWnd, NULL, TRUE);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		FrameRect(hDC, &Box, hBrush);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);
		
		GetTextExtentPointA(hDC, str, strlen(str), &size);
		TextOutA(hDC, 5, 540, str, strlen(str));
		SetCaretPos(size.cx + 5, 540);

		if (check == 1)
		{
			hPen = CreatePen(PS_SOLID, Th, RGB(rand() % 255, rand() % 255, rand() % 255));
			oldPen = (HPEN)SelectObject(hDC, hPen);
			switch (Shape)
			{
			case 1:
				MoveToEx(hDC, Left, Top, NULL);
				LineTo(hDC, Right, Bottom);
				break;
			case 2:
				Ellipse(hDC, Left, Top, Right, Bottom);
				break;
			case 3:
				MoveToEx(hDC, (Left + Right) / 2, Top, NULL);
				LineTo(hDC, Left, Bottom);
				MoveToEx(hDC, (Left + Right) / 2, Top, NULL);
				LineTo(hDC, Right, Bottom);
				MoveToEx(hDC, Left, Bottom, NULL);
				LineTo(hDC, Right, Bottom);
				break;
			case 4:
				Rectangle(hDC, Left, Top, Right, Bottom);
				break;
			}
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
		}

		if (Shape == -1)
		{
			TextOutA(hDC, 500, 540, "ERROR: 도형이 존재하지않습니다", 30);
			Shape = 0;
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}
