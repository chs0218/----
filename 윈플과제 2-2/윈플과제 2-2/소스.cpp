#include <Windows.h>
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
	static int x = 0, y = 0, M = 0, Judge = 0;
	int start = 0;
	static char mystring[100];
	static int num;
	char Multi[20];
	static RECT rect;

	switch (iMessage) {
	case WM_CREATE:
		num = 0;
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (Judge == 1)
		{
			InvalidateRect(hWnd, &rect, TRUE);
			Judge = 0;
		}

		if (wParam == VK_BACK)
		{
			--num;
			if (num < 0)
				num = 0;

		}

		else if (wParam == VK_RETURN)
		{

			sscanf(mystring, "%d %d %d", &x, &y, &M);

			if (x == 0 || y == 0 || M == 0)
			{
				PostQuitMessage(0);
				break;
			}
			Judge = 1;

			InvalidateRgn(hWnd, NULL, TRUE);

		}

		

		else
			mystring[num++] = wParam;
		mystring[num] = '\0';
		TextOutA(hDC, x, y, mystring, strlen(mystring));

		ReleaseDC(hWnd, hDC);

		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		if (Judge == 1)
		{
			for (int i = 1; i < 10; ++i)
			{
				sprintf(Multi, "%d * %d = %d", M, i, M*i);
				TextOutA(hDC, x, y, Multi, strlen(Multi));
				y += 20;
			}

			rect.left = x;
			rect.top = y - 180;
			rect.right = x + 100;
			rect.bottom = y;

			x = 0, y = 0, M = 0;
			mystring[0] = '\0';
			num = 0;
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));


}
