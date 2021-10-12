#include <Windows.h>
#include <tchar.h>
#include <conio.h>
#include "resource.h"

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
	OPENFILENAME OFN;
	TCHAR str[100], lpstrFile[100] = L"";

	PAINTSTRUCT ps;
	HDC hDC;
	HANDLE hFile;
	static int x = 0, y = 0;
	static TCHAR mystring[10][100] = { '\0', };
	static TCHAR InBuff[1000];
	static int num;
	static SIZE size;
	static int judge = 0;
	static int CAPITAL;
	static int maxnum[10] = { 0 };
	int n;
	int max;
	RECT rect;
	int endl;
	DWORD DWtmp;
	switch (iMessage) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		num = 0;
		CAPITAL = 0;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILESAVE:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = L"Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = L".";
			if (GetOpenFileName(&OFN) != 0) {
				hFile = CreateFile(OFN.lpstrFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
				SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
				for (int i = 0; i < 10; ++i)
				{
					max = lstrlen(mystring[i]);
					mystring[i][max++] = '\r';
					mystring[i][max++] = '\n';
					mystring[i][max] = '\0';
					WriteFile(hFile, mystring[i], lstrlen(mystring[i]) * 2, &DWtmp, NULL);
					mystring[i][--max] = '\0';
					mystring[i][--max] = '\0';
				}
				CloseHandle(hFile);
			}
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		case ID_FILELOAD:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = L"Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = L".";
			if (GetOpenFileName(&OFN) != 0) {
				hFile = CreateFile(OFN.lpstrFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
				SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

				memset(InBuff, 0, 1000 * sizeof(TCHAR));
				ReadFile(hFile, InBuff, 1000, &DWtmp, NULL);
				InBuff[DWtmp] = '\t';
				n = 0;
				max = 0;
				for (int i = 0; i < 1000; ++i)
				{
					if (InBuff[i] == '\t')
						break;

					else if (InBuff[i] == '\r')
					{
						maxnum[n] = max;
						i++;
						++n;
						max = 0;
					}
					else
					{
						mystring[n][max++] = InBuff[i];
					}
				}
				CloseHandle(hFile);
			}
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);

		if (wParam == VK_LEFT)
		{
			--num;
		}

		else if (wParam == VK_RIGHT)
		{
			++num;
			if (maxnum[y] < num)
				--num;
		}


		else if (wParam == VK_UP)
		{
			y -= 1;
			if (y < 0)
				y = 0;
			if (maxnum[y] < num)
				num = maxnum[y];
		}

		else if (wParam == VK_DOWN)
		{
			y += 1;
			if (y > 9)
				y = 9;
			if (maxnum[y] < num)
				num = maxnum[y];
		}

		else if (wParam == VK_HOME)
		{
			InvalidateRgn(hWnd, NULL, TRUE);
			num = 0;
		}

		else if (wParam == VK_DELETE)
		{
			num = 0;
			int j = 0;
			for (int i = y; i < 9; ++i)
			{
				for (int j = 0; j < 100; ++j)
					mystring[i][j] = mystring[i + 1][j];

			}
		}

		GetTextExtentPoint(hDC, mystring[y], num, &size);
		x = size.cx;
		InvalidateRgn(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == VK_BACK)
		{
			--num;

			if (num < 0)
			{
				--y;
				num = maxnum[y];
				GetTextExtentPoint(hDC, mystring[y], num, &size);
				x = size.cx;
				break;
			}
			if (maxnum[y] > num)
			{
				for (int i = num; i < 100; ++i)
				{
					mystring[y][i] = mystring[y][i + 1];
					if (mystring[y][i + 1] == '\0')
						break;
				}
			}
			else
				mystring[y][num] = '\0';

			InvalidateRgn(hWnd, NULL, TRUE);

		}

		else if (wParam == VK_ESCAPE)
		{
			judge = 1;
			InvalidateRgn(hWnd, NULL, TRUE);

		}

		else if (wParam == VK_RETURN)
		{

			++y;
			if (y > 9)
			{
				TextOutA(hDC, 0, 300, "최대 10줄 입니다.(2초 뒤에 프로그램이 종료됩니다)", 50);
				Sleep(2000);
				PostQuitMessage(0);
			}

			num = 0;
			InvalidateRgn(hWnd, NULL, TRUE);

		}

		else if (wParam == VK_TAB)
		{
			for (int i = 0; i < 4; ++i)
				mystring[y][num++] = ' ';
		}

		else if (wParam == VK_CAPITAL)
		{
			CAPITAL = 1;
			if ((int)wParam >= 97)
				mystring[y][num++] = wParam - 32;
			else
				mystring[y][num++] = wParam + 32;

			if (num > 100)
			{
				TextOutA(hDC, 0, 300, "100철자를 넘기셨습니다.(2초 뒤에 프로그램이 종료됩니다)", 56);
				Sleep(2000);
				PostQuitMessage(0);
			}
		}


		else
		{
			if (CAPITAL == 1)
			{
				if ((int)wParam >= 97)
					mystring[y][num++] = wParam - 32;
				else
					mystring[y][num++] = wParam + 32;


				maxnum[y] = num;
			}
			else
			{
				mystring[y][num++] = wParam;
				maxnum[y] = num;
			}
			if (num > 100)
			{
				TextOutA(hDC, 0, 300, "100철자를 넘기셨습니다.(2초 뒤에 프로그램이 종료됩니다)", 56);
				Sleep(2000);
				PostQuitMessage(0);
			}

		}
		endl = _tcslen(mystring[y]);
		mystring[y][endl] = '\0';
		GetTextExtentPoint(hDC, mystring[y], num, &size);
		x = size.cx;
		InvalidateRgn(hWnd, NULL, FALSE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		if (judge == 1)
		{
			for (int i = 0; i < 10; ++i)
			{
				for (int j = 0; j < 100; ++j)
					mystring[i][j] = '\0';
			}
			x = 0, y = 0;
			num = 0;
			judge = 0;
		}

		for (int i = 0; i < 10; ++i)
		{
			TextOut(hDC, 0, i * 20, mystring[i], _tcslen(mystring[i]));
		}

		SetCaretPos(x, y * 20);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


