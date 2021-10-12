#include <Windows.h>
#include <stdio.h>
#include "resource.h"

HINSTANCE g_hInst;

LPCTSTR IpszClass = L"ParentClass";
LPCTSTR IpszWindowName = L"?-1";

int BackGround = 0;
BOOL Grid = FALSE;
int MAP_WIDTH = 850;
int MAP_HEIGHT = 850;
int GRID_WIDTH = 10;
int GRID_HEIGHT = 10;
int Click_Status = 0;
BOOL Test = FALSE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg_Proc(HWND, UINT, WPARAM, LPARAM);


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
		0, 0, 1040, 950, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

struct Object {
	int x, y, cs;
	int Direction;
};

void Animation(HDC hDC, Object object[100], int ObjectN)
{
	HDC memDC;
	HBITMAP BIT_BackGround[3], EnemyBIT[2], ITEMBIT[3], OBSTACLEBIT[3];
	HPEN hPen, oldPen;

	BIT_BackGround[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND1));
	BIT_BackGround[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND2));
	BIT_BackGround[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND3));
	EnemyBIT[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ENEMY1));
	EnemyBIT[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ENEMY2));
	ITEMBIT[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ITEM1));
	ITEMBIT[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ITEM2));
	ITEMBIT[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ITEM3));
	OBSTACLEBIT[0] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OBSTACLE1));
	OBSTACLEBIT[1] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OBSTACLE2));
	OBSTACLEBIT[2] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OBSTACLE3));




	memDC = CreateCompatibleDC(hDC);
	switch (BackGround)
	{
	case 1:
		SelectObject(memDC, BIT_BackGround[0]);
		StretchBlt(hDC, 0, 0, MAP_WIDTH, MAP_HEIGHT, memDC, 0, 0, 850, 850, SRCCOPY);
		break;
	case 2:
		SelectObject(memDC, BIT_BackGround[1]);
		StretchBlt(hDC, 0, 0, MAP_WIDTH, MAP_HEIGHT, memDC, 0, 0, 850, 850, SRCCOPY);
		break;
	case 3:
		SelectObject(memDC, BIT_BackGround[2]);
		StretchBlt(hDC, 0, 0, MAP_WIDTH, MAP_HEIGHT, memDC, 0, 0, 850, 850, SRCCOPY);
		break;
	default:

		break;
	}

	if (Grid)
	{
		if (BackGround == 1)
		{
			hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
			oldPen = (HPEN)SelectObject(hDC, hPen);

			for (int i = 0; i < GRID_WIDTH; ++i)
			{
				MoveToEx(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*i, 0, NULL);
				LineTo(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*i, MAP_HEIGHT);
			}

			for (int i = 0; i < GRID_HEIGHT; ++i)
			{
				MoveToEx(hDC, 0, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*i, NULL);
				LineTo(hDC, MAP_WIDTH, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*i);
			}

			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
		}
		else
		{
			for (int i = 0; i < GRID_WIDTH; ++i)
			{
				MoveToEx(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*i, 0, NULL);
				LineTo(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*i, MAP_HEIGHT);
			}

			for (int i = 0; i < GRID_HEIGHT; ++i)
			{
				MoveToEx(hDC, 0, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*i, NULL);
				LineTo(hDC, MAP_WIDTH, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*i);
			}
		}
		
	}

	for (int i = 0; i < ObjectN; ++i)
	{
		switch (object[i].cs)
		{
		case 1:
			SelectObject(memDC, OBSTACLEBIT[0]);
			TransparentBlt(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*object[i].x, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*object[i].y, ((double)MAP_WIDTH / (double)GRID_WIDTH), ((double)MAP_HEIGHT / (double)GRID_HEIGHT), memDC, 0, 0, 50, 50, RGB(255, 255, 255));
			break;
		case 2:
			SelectObject(memDC, OBSTACLEBIT[1]);
			TransparentBlt(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*object[i].x, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*object[i].y, ((double)MAP_WIDTH / (double)GRID_WIDTH), ((double)MAP_HEIGHT / (double)GRID_HEIGHT), memDC, 0, 0, 50, 50, RGB(255, 255, 255));
			break;
		case 3:
			SelectObject(memDC, OBSTACLEBIT[2]);
			TransparentBlt(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*object[i].x, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*object[i].y, ((double)MAP_WIDTH / (double)GRID_WIDTH), ((double)MAP_HEIGHT / (double)GRID_HEIGHT), memDC, 0, 0, 50, 50, RGB(255, 255, 255));
			break;
		case 4:
			SelectObject(memDC, ITEMBIT[0]);
			TransparentBlt(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*object[i].x, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*object[i].y, ((double)MAP_WIDTH / (double)GRID_WIDTH), ((double)MAP_HEIGHT / (double)GRID_HEIGHT), memDC, 0, 0, 50, 50, RGB(255, 255, 255));
			break;
		case 5:
			SelectObject(memDC, ITEMBIT[1]);
			TransparentBlt(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*object[i].x, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*object[i].y, ((double)MAP_WIDTH / (double)GRID_WIDTH), ((double)MAP_HEIGHT / (double)GRID_HEIGHT), memDC, 0, 0, 50, 50, RGB(255, 255, 255));
			break;
		case 6:
			SelectObject(memDC, ITEMBIT[2]);
			TransparentBlt(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*object[i].x, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*object[i].y, ((double)MAP_WIDTH / (double)GRID_WIDTH), ((double)MAP_HEIGHT / (double)GRID_HEIGHT), memDC, 0, 0, 50, 50, RGB(255, 255, 255));
			break;
		case 7:
			SelectObject(memDC, EnemyBIT[0]);
			TransparentBlt(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*object[i].x, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*object[i].y, ((double)MAP_WIDTH / (double)GRID_WIDTH), ((double)MAP_HEIGHT / (double)GRID_HEIGHT), memDC, 0, 0, 81, 81, RGB(255, 255, 255));
			break;
		case 8:
			SelectObject(memDC, EnemyBIT[1]);
			TransparentBlt(hDC, ((double)MAP_WIDTH / (double)GRID_WIDTH)*object[i].x, ((double)MAP_HEIGHT / (double)GRID_HEIGHT)*object[i].y, ((double)MAP_WIDTH / (double)GRID_WIDTH), ((double)MAP_HEIGHT / (double)GRID_HEIGHT), memDC, 0, 0, 81, 81, RGB(255, 255, 255));
			break;
		default:

			break;
		}
		
	}

	DeleteDC(memDC);
	for (int i = 0; i < 3; ++i)
	{
		DeleteObject(BIT_BackGround[i]);
		DeleteObject(OBSTACLEBIT[i]);
		DeleteObject(ITEMBIT[i]);
	}
	for (int i = 0; i < 2; ++i)
	{
		DeleteObject(EnemyBIT[i]);
	}
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	HANDLE hFile;
	int n;
	char inBuff[1000], outBuff[100];
	DWORD DWtmp;
	static HDC hDC, MemDC;
	HDC tmphDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	PAINTSTRUCT ps;
	static HWND Button[10];
	static Object object[100];
	static int ObjectN;
	int mx, my;
	HWND hDlg = NULL;
	switch (iMessage) {
	case WM_CREATE:
		for (int i = 0; i < 100; ++i)
		{
			object[i].cs = 0;
			object[i].Direction = 0;
		}
		ObjectN = 0;
		SetTimer(hWnd, 1, 100, NULL);
		break;
	case WM_TIMER:
		if (Test)
		{
			for (int i = 0; i < ObjectN; ++i)
			{
				if (object[i].cs == 7)
				{
					if (object[i].Direction == 1)
					{
						object[i].y -= 1;
						if (object[i].y < 0)
						{
							object[i].y = 0;
							object[i].Direction = 2;
						}
					}
					else
					{
						object[i].y += 1;
						if (object[i].y > GRID_HEIGHT - 1)
						{
							object[i].y = GRID_HEIGHT - 1;
							object[i].Direction = 1;
						}
					}
				}

				if (object[i].cs == 8)
				{
					if (object[i].Direction == 1)
					{
						object[i].x -= 1;
						if (object[i].x < 0)
						{
							object[i].x = 0;
							object[i].Direction = 2;
						}
					}
					else
					{
						object[i].x += 1;
						if (object[i].x > GRID_WIDTH - 1)
						{
							object[i].x = GRID_WIDTH - 1;
							object[i].Direction = 1;
						}
					}
				}
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILESAVE:
			hFile = CreateFile(L"test.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
			SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
			sprintf(outBuff, "%d ", BackGround);
			WriteFile(hFile, outBuff, strlen(outBuff), &DWtmp, NULL);

			for (int i = 0; i < ObjectN; ++i)
			{
				sprintf(outBuff, "%d %d%d%d %d%d%d %d ", object[i].cs, object[i].x / 100, (object[i].x / 10) % 10, object[i].x % 10, object[i].y / 100, (object[i].y / 10) % 10, object[i].y % 10, object[i].Direction);
				WriteFile(hFile, outBuff, strlen(outBuff), &DWtmp, NULL);
			}
			CloseHandle(hFile);
			break;
		case ID_FILELOAD:
			for (int i = 0; i < 100; ++i)
			{
				object[i].cs = 0;
				object[i].Direction = 0;
			}
			ObjectN = 0;
			hFile = CreateFile(L"test.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
			ReadFile(hFile, inBuff, 1000, &DWtmp, NULL);
			inBuff[DWtmp] = '\0';
			n = 0;
			BackGround = (int)inBuff[n] - 48;
			n += 2;
			for (int i = 0; i < 100; ++i)
			{
				object[i].cs = (int)inBuff[n] - 48;
				n += 2;
				object[i].x = ((int)inBuff[n] - 48) * 100 + ((int)inBuff[n + 1] - 48) * 10 + ((int)inBuff[n + 2] - 48);
				n += 4;
				object[i].y = ((int)inBuff[n] - 48) * 100 + ((int)inBuff[n + 1] - 48) * 10 + ((int)inBuff[n + 2] - 48);
				n += 4;
				object[i].Direction = ((int)inBuff[n] - 48);
				n += 2;
				ObjectN += 1;
				if (n >= DWtmp)
					break;
			}
			CloseHandle(hFile);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		default:
			break;
		}
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		Animation(hDC, object, ObjectN);
		
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
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if ((0 <= mx && mx <= MAP_WIDTH) && (0 <= my && my <= MAP_HEIGHT) && (Click_Status != 0))
		{
			switch (Click_Status)
			{
			case 1:
				if (ObjectN < 100)
				{
					object[ObjectN].cs = 1;
					object[ObjectN].x = mx / ((double)MAP_WIDTH / (double)GRID_WIDTH);
					object[ObjectN].y = my / ((double)MAP_HEIGHT / (double)GRID_HEIGHT);
					object[ObjectN].Direction = 0;
					++ObjectN;
				}
				break;
			case 2:
				if (ObjectN < 100)
				{
					object[ObjectN].cs = 2;
					object[ObjectN].x = mx / ((double)MAP_WIDTH / (double)GRID_WIDTH);
					object[ObjectN].y = my / ((double)MAP_HEIGHT / (double)GRID_HEIGHT);
					object[ObjectN].Direction = 0;
					++ObjectN;
				}
				break;
			case 3:
				if (ObjectN < 100)
				{
					object[ObjectN].cs = 3;
					object[ObjectN].x = mx / ((double)MAP_WIDTH / (double)GRID_WIDTH);
					object[ObjectN].y = my / ((double)MAP_HEIGHT / (double)GRID_HEIGHT);
					object[ObjectN].Direction = 0;
					++ObjectN;
				}
				break;
			case 4:
				if (ObjectN < 100)
				{
					object[ObjectN].cs = 4;
					object[ObjectN].x = mx / ((double)MAP_WIDTH / (double)GRID_WIDTH);
					object[ObjectN].y = my / ((double)MAP_HEIGHT / (double)GRID_HEIGHT);
					object[ObjectN].Direction = 0;
					++ObjectN;
				}
				break;
			case 5:
				if (ObjectN < 100)
				{
					object[ObjectN].cs = 5;
					object[ObjectN].x = mx / ((double)MAP_WIDTH / (double)GRID_WIDTH);
					object[ObjectN].y = my / ((double)MAP_HEIGHT / (double)GRID_HEIGHT);
					object[ObjectN].Direction = 0;
					++ObjectN;
				}
				break;
			case 6:
				if (ObjectN < 100)
				{
					object[ObjectN].cs = 6;
					object[ObjectN].x = mx / ((double)MAP_WIDTH / (double)GRID_WIDTH);
					object[ObjectN].y = my / ((double)MAP_HEIGHT / (double)GRID_HEIGHT);
					object[ObjectN].Direction = 0;
					++ObjectN;
				}
				break;
			case 7:
				if (ObjectN < 100)
				{
					object[ObjectN].cs = 7;
					object[ObjectN].x = mx / ((double)MAP_WIDTH / (double)GRID_WIDTH);
					object[ObjectN].y = my / ((double)MAP_HEIGHT / (double)GRID_HEIGHT);
					object[ObjectN].Direction = 1;
					++ObjectN;
				}
				break;
			case 8:
				if (ObjectN < 100)
				{
					object[ObjectN].cs = 8;
					object[ObjectN].x = mx / ((double)MAP_WIDTH / (double)GRID_WIDTH);
					object[ObjectN].y = my / ((double)MAP_HEIGHT / (double)GRID_HEIGHT);
					object[ObjectN].Direction = 1;
					++ObjectN;
				}
				break;
			default:
				break;
			}
		}
		break;
	case WM_RBUTTONDOWN:
		if (!IsWindow(hDlg))
		{
			hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG), hWnd, Dlg_Proc);
			ShowWindow(hDlg, SW_SHOW);
		}
		break;
	case WM_LBUTTONUP:

		break;
	case WM_MOUSEMOVE:

		break;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK Dlg_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HBITMAP hBit;
	HWND hButton;
	
	switch (iMsg) {
		case WM_INITDIALOG: 
			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND1));
			hButton = GetDlgItem(hDlg, IDC_BACKGROUNDBUTTON1);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);

			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND2));
			hButton = GetDlgItem(hDlg, IDC_BACKGROUNDBUTTON2);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);

			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BACKGROUND3));
			hButton = GetDlgItem(hDlg, IDC_BACKGROUNDBUTTON3);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);

			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OBSTACLE1));
			hButton = GetDlgItem(hDlg, IDC_OBSTACLEBUTTON1);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);

			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OBSTACLE2));
			hButton = GetDlgItem(hDlg, IDC_OBSTACLEBUTTON2);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);

			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OBSTACLE3));
			hButton = GetDlgItem(hDlg, IDC_OBSTACLEBUTTON3);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);

			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ITEM1));
			hButton = GetDlgItem(hDlg, IDC_ITEMBUTTON1);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);

			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ITEM2));
			hButton = GetDlgItem(hDlg, IDC_ITEMBUTTON2);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);

			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ITEM3));
			hButton = GetDlgItem(hDlg, IDC_ITEMBUTTON3);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);

			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ENEMY1));
			hButton = GetDlgItem(hDlg, IDC_ENEMYBUTTON1);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);

			hBit = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ENEMY2));
			hButton = GetDlgItem(hDlg, IDC_ENEMYBUTTON2);
			SendMessage(hButton, BM_SETIMAGE, 0, (LPARAM)hBit);
			return true;
		case WM_COMMAND: 
			switch (LOWORD(wParam)) 
			{
			case IDC_BACKGROUNDBUTTON1:
				BackGround = 1;
				break;
			case IDC_BACKGROUNDBUTTON2:
				BackGround = 2;
				break;
			case IDC_BACKGROUNDBUTTON3:
				BackGround = 3;
				break;
			case IDC_GRIDCHECK:
				if (Grid)
					Grid = FALSE;
				else
					Grid = TRUE;
				break;

			case IDC_OBSTACLEBUTTON1:
				Click_Status = 1;
				break;

			case IDC_OBSTACLEBUTTON2:
				Click_Status = 2;
				break;

			case IDC_OBSTACLEBUTTON3:
				Click_Status = 3;
				break;

			case IDC_ITEMBUTTON1:
				Click_Status = 4;
				break;

			case IDC_ITEMBUTTON2:
				Click_Status = 5;
				break;

			case IDC_ITEMBUTTON3:
				Click_Status = 6;
				break;

			case IDC_ENEMYBUTTON1:
				Click_Status = 7;
				break;

			case IDC_ENEMYBUTTON2:
				Click_Status = 8;
				break;

			case IDC_BUTTONDRAW:
				MAP_WIDTH = GetDlgItemInt(hDlg, IDC_WIDTHSIZE, NULL, TRUE);
				MAP_HEIGHT = GetDlgItemInt(hDlg, IDC_HEIGHTSIZE, NULL, TRUE);
				GRID_WIDTH= GetDlgItemInt(hDlg, IDC_WIDTHGRIDNUM, NULL, TRUE);
				GRID_HEIGHT = GetDlgItemInt(hDlg, IDC_HEIGHTGRIDNUM, NULL, TRUE);

				break;
			case IDC_TESTBUTTON:
				if (Test)
					Test = FALSE;
				else
					Test = TRUE;
				break;
			case IDC_QUIT:
				DestroyWindow(hDlg); 
				hDlg = NULL;
				break;
			} 
			break;
	} 
	return 0;
}
