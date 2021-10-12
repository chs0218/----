#include <Windows.h>
#include <math.h>
#include "resource.h"

static BOOL winStart, winDraw;
static int r, g, b;
static BOOL finish;
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"Window Programming Lab";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg1_Proc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	HWND hDlg = NULL;

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 10, NULL);
		break;
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg1_Proc);
		break;
	case WM_COMMAND:

		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		

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
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK Dlg1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	static BOOL Full, DOT;
	static char word[100];
	static int num;
	static int sign;
	static int FIRST, SECOND;
	static int FIRSTDOT, SECONDDOT;
	switch (iMsg) {
	case WM_INITDIALOG:
		sign = 0;
		Full = FALSE;
		DOT = FALSE;
		num = 0;
		FIRST = 0;
		FIRSTDOT = 0;
		SECOND = 0;
		SECONDDOT = 0;
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_NUMBER0:
			if (num == 100)
				break;
			else
			{
				word[num++] = '0';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
				if (!Full)
				{
					FIRST = FIRST * 10 + 0;
					if (DOT)
					{
						FIRSTDOT = FIRSTDOT * 10 + 0;
					}
				}
				else
				{
					SECOND = SECOND * 10 + 0;
					if (DOT)
					{
						FIRSTDOT = FIRSTDOT * 10 + 0;
					}
				}
			}
			break;
		case IDC_NUMBER1:
			if (num == 100)
				break;
			else
			{
				word[num++] = '1';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
				if (!Full)
				{
					FIRST = FIRST * 10 + 1;
				}
				else
				{
					SECOND = SECOND * 10 + 1;
				}
			}
			break;
		case IDC_NUMBER2:
			if (num == 100)
				break;
			else
			{
				word[num++] = '2';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
				if (!Full)
				{
					FIRST = FIRST * 10 + 2;
				}
				else
				{
					SECOND = SECOND * 10 + 2;
				}
			}
			break;
		case IDC_NUMBER3:
			if (num == 100)
				break;
			else
			{
				word[num++] = '3';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
				if (!Full)
				{
					FIRST = FIRST * 10 + 3;
				}
				else
				{
					SECOND = SECOND * 10 + 3;
				}
			}
			break;
		case IDC_NUMBER4:
			if (num == 100)
				break;
			else
			{
				word[num++] = '4';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
				if (!Full)
				{
					FIRST = FIRST * 10 + 4;
				}
				else
				{
					SECOND = SECOND * 10 + 4;
				}
			}
			break;
		case IDC_NUMBER5:
			if (num == 100)
				break;
			else
			{
				word[num++] = '5';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
				if (!Full)
				{
					FIRST = FIRST * 10 + 5;
				}
				else
				{
					SECOND = SECOND * 10 + 5;
				}
			}
			break;
		case IDC_NUMBER6:
			if (num == 100)
				break;
			else
			{
				word[num++] = '6';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
				if (!Full)
				{
					FIRST = FIRST * 10 + 6;
				}
				else
				{
					SECOND = SECOND * 10 + 6;
				}
			}
			break;
		case IDC_NUMBER7:
			if (num == 100)
				break;
			else
			{
				word[num++] = '7';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
				if (!Full)
				{
					FIRST = FIRST * 10 + 7;
				}
				else
				{
					SECOND = SECOND * 10 + 7;
				}
			}
			break;
		case IDC_NUMBER8:
			if (num == 100)
				break;
			else
			{
				word[num++] = '8';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
				if (!Full)
				{
					FIRST = FIRST * 10 + 8;
				}
				else
				{
					SECOND = SECOND * 10 + 8;
				}
			}
			break;
		case IDC_NUMBER9:
			if (num == 100)
				break;
			else
			{
				word[num++] = '9';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
				if (!Full)
				{
					FIRST = FIRST * 10 + 9;
				}
				else
				{
					SECOND = SECOND * 10 + 9;
				}
			}
			break;
		case IDC_DIVIDE:
			for (int i = 0; i < num; ++i)
			{
				word[i] = '\0';

			}
			sign = 1;
			num = 0;
			Full = TRUE;
			break;
		case IDC_MULTIPLY:
			for (int i = 0; i < num; ++i)
			{
				word[i] = '\0';
			}
			sign = 2;
			num = 0;
			Full = TRUE;
			break;
		case IDC_MINUS:
			for (int i = 0; i < num; ++i)
			{
				word[i] = '\0';
			}
			sign = 3;
			num = 0;
			Full = TRUE;
			break;
		case IDC_PLUS:
			for (int i = 0; i < num; ++i)
			{
				word[i] = '\0';
			}
			sign = 4;
			num = 0;
			Full = TRUE;
			break;
		case IDC_DOT:
			if (num == 100)
				break;
			else
			{
				word[num++] = '.';
				SetDlgItemTextA(hDlg, IDC_EDIT, word);
			}
			break;
		case IDC_EQUAL:
			switch (sign)
			{
			case 1:
				FIRST = FIRST / SECOND;
				SetDlgItemInt(hDlg, IDC_EDIT, FIRST, TRUE);
				break;
			case 2:
				FIRST = FIRST * SECOND;
				SetDlgItemInt(hDlg, IDC_EDIT, FIRST, TRUE);
				break;
			case 3:
				FIRST = FIRST - SECOND;
				SetDlgItemInt(hDlg, IDC_EDIT, FIRST, TRUE);
				break;
			case 4:
				FIRST = FIRST + SECOND;
				SetDlgItemInt(hDlg, IDC_EDIT, FIRST, TRUE);
				break;
			}
			SECOND = 0;
			sign = 0;
			break;
		case IDC_DELETEALL:
			for (int i = 0; i < 100; ++i)
			{
				word[i] = '\0';
			}
			sign = 0;
			Full = FALSE;
			DOT = FALSE;
			num = 0;
			FIRST = 0;
			SECOND = 0;
			SetDlgItemTextA(hDlg, IDC_EDIT, word);
			break;
		case IDC_END:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hDlg, &ps);
		GetClientRect(hDlg, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		
		GetClientRect(hDlg, &bufferRT);
		BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(hDC);
		EndPaint(hDlg, &ps);
		break;
	}
	return 0;
}
