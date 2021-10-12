#include <Windows.h>
#include <math.h>
#include "resource.h"

char Items[][15] = { "1970", "1980", "1990", "2000", "2010" };

HINSTANCE g_hInst;
LPCTSTR IpszClass = "Window Class Name";
LPCTSTR IpszWindowName = "Window Programming Lab";

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

class Member {

};

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

	OPENFILENAME OFN;
	TCHAR str[100], lpstrFile[100] = "";
	HANDLE hFile;
	DWORD DWtmp;

	static HWND hCombo, hList;
	static BOOL Gender;
	static char name[100];
	static char CallNumber[100];
	static char output[200];
	static char tmp1[200], tmp2[200], tmp3[200];
	static int SelectionYear, ListBoxSelection;
	static int num;
	switch (iMsg) {
	case WM_INITDIALOG:
		hCombo = GetDlgItem(hDlg, IDC_COMBO1);
		hList = GetDlgItem(hDlg, IDC_LIST1);
		for (int i = 0; i < 5; ++i)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		SelectionYear = -1;
		num = 0;
		Gender = FALSE;
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RADIO1:
			Gender = TRUE;
			break;
		case IDC_RADIO2:
			Gender = FALSE;
			break;
		case IDC_BUTTON1:
			for (int i = 0; i < num - 1; ++i)
			{
				for (int j = i + 1; j < num; ++j)
				{
					SendMessage(hList, LB_GETTEXT, i, (LPARAM)tmp1);
					SendMessage(hList, LB_GETTEXT, j, (LPARAM)tmp2);
					if (strcmp(tmp1, tmp2) > 0)
					{
						strcpy(tmp3, tmp1);
						strcpy(tmp1, tmp2);
						strcpy(tmp2, tmp3);
						SendMessage(hList, LB_DELETESTRING, i, 0);
						SendMessage(hList, LB_INSERTSTRING, i, (LPARAM)tmp1);

						SendMessage(hList, LB_DELETESTRING, j, 0);
						SendMessage(hList, LB_INSERTSTRING, j, (LPARAM)tmp2);
					}
				}
			}
			break;
		case IDC_BUTTON2:
			SetDlgItemText(hDlg, IDC_EDIT1, "");
			SetDlgItemText(hDlg, IDC_EDIT2, "");
			for (int i = 0; i < 100; ++i)
			{
				name[i] = '\0';
				CallNumber[i] = '\0';
			}
			break;
		case IDC_BUTTON3:
			GetDlgItemTextA(hDlg, IDC_EDIT1, name, 100);
			GetDlgItemTextA(hDlg, IDC_EDIT2, CallNumber, 100);
			if (Gender)
			{
				switch (SelectionYear)
				{
				case 0:
					wsprintf(output, "이름: %s, 전화번호: %s, 성별: 여자, 출생년도: 1970\r\n", name, CallNumber);
					break;
				case 1:
					wsprintf(output, "이름: %s, 전화번호: %s, 성별: 여자, 출생년도: 1980\r\n", name, CallNumber);
					break;
				case 2:
					wsprintf(output, "이름: %s, 전화번호: %s, 성별: 여자, 출생년도: 1990\r\n", name, CallNumber);
					break;
				case 3:
					wsprintf(output, "이름: %s, 전화번호: %s, 성별: 여자, 출생년도: 2000\r\n", name, CallNumber);
					break;
				case 4:
					wsprintf(output, "이름: %s, 전화번호: %s, 성별: 여자, 출생년도: 2010\r\n", name, CallNumber);
					break;
				}
			}
			else
			{
				switch (SelectionYear)
				{
				case 0:
					wsprintf(output, "이름: %s, 전화번호: %s, 성별: 남자, 출생년도: 1970\r\n", name, CallNumber);
					break;
				case 1:
					wsprintf(output, "이름: %s, 전화번호: %s, 성별: 남자, 출생년도: 1980\r\n", name, CallNumber);
					break;
				case 2:
					wsprintf(output, "이름: %s, 전화번호: %s, 성별: 남자, 출생년도: 1990\r\n", name, CallNumber);
					break;
				case 3:
					wsprintf(output, "이름: %s, 전화번호: %s, 성별: 남자, 출생년도: 2000\r\n", name, CallNumber);
					break;
				case 4:
					wsprintf(output, "이름: %s, 전화번호: %s, 성별: 남자, 출생년도: 2010\r\n", name, CallNumber);
					break;
				}
			}
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)output);
			++num;
			break;
		case IDC_BUTTON4:
			SendMessage(hList, LB_DELETESTRING, ListBoxSelection, 0);
			--num;
			break;
		case IDC_BUTTON5:
			hFile = CreateFile("test.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
			SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
			for (int i = 0; i < num; ++i)
			{
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)tmp1);
				WriteFile(hFile, tmp1, strlen(tmp1), &DWtmp, NULL);
			}
			CloseHandle(hFile);
			break;
		case IDC_COMBO1:
			if (HIWORD(wParam) == CBN_SELCHANGE)
				SelectionYear = SendMessage(hCombo, CB_GETCURSEL, 0, 0);

			break;

		case IDC_LIST1:
			if (HIWORD(wParam) == LBN_SELCHANGE)
				ListBoxSelection = SendMessage(hList, LB_GETCURSEL, 0, 0); break;
		case IDCANCEL:
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
