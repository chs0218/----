#include <Windows.h>
#include <time.h>
#include "resource.h"

#define WIDTH 1601
#define HEIGHT 2397

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"Window Programming Lab";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg1_Proc(HWND, UINT, WPARAM, LPARAM);


int second = 0;
BOOL Grid;
int widthn, heightn;
int xPos, yPos, cs;
int r, g, b;

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
		0, 0, 1500, 1500, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

struct Block
{
	int xPos, yPos, cs;
};

void Animation(int xPos, int yPos, HDC hDC, int cs, Block block[25][15], int widthN, int heightN)
{
	HDC memDC;
	HBITMAP BAR[2], CORNER[4];
	static int count;
	int i;

	count++;
	count = count % 4;
	BAR[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	BAR[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	CORNER[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	CORNER[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	CORNER[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	CORNER[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));

	memDC = CreateCompatibleDC(hDC);

	switch (cs)
	{
	case 0:
		(HBITMAP)SelectObject(memDC, BAR[0]);
		TransparentBlt(hDC, xPos, yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
		break;
	case 1:
		(HBITMAP)SelectObject(memDC, BAR[1]);
		TransparentBlt(hDC, xPos, yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
		break;
	case 2:
		(HBITMAP)SelectObject(memDC, CORNER[0]);
		TransparentBlt(hDC, xPos, yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
		break;
	case 3:
		(HBITMAP)SelectObject(memDC, CORNER[1]);
		TransparentBlt(hDC, xPos, yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
		break;
	case 4:
		(HBITMAP)SelectObject(memDC, CORNER[2]);
		TransparentBlt(hDC, xPos, yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
		break;
	case 5:
		(HBITMAP)SelectObject(memDC, CORNER[3]);
		TransparentBlt(hDC, xPos, yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
		break;
	default:
		break;
	}

	for (int i = 0; i < heightN; ++i)
	{
		for (int j = 0; j < widthN; ++j)
		{
			if (block[i][j].cs != -1 && block[i][j].cs != 999)
			{
				switch (block[i][j].cs)
				{
				case 0:
					(HBITMAP)SelectObject(memDC, BAR[0]);
					TransparentBlt(hDC, block[i][j].xPos, block[i][j].yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
					break;
				case 1:
					(HBITMAP)SelectObject(memDC, BAR[1]);
					TransparentBlt(hDC, block[i][j].xPos, block[i][j].yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
					break;
				case 2:
					(HBITMAP)SelectObject(memDC, CORNER[0]);
					TransparentBlt(hDC, block[i][j].xPos, block[i][j].yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
					break;
				case 3:
					(HBITMAP)SelectObject(memDC, CORNER[1]);
					TransparentBlt(hDC, block[i][j].xPos, block[i][j].yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
					break;
				case 4:
					(HBITMAP)SelectObject(memDC, CORNER[2]);
					TransparentBlt(hDC, block[i][j].xPos, block[i][j].yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
					break;
				case 5:
					(HBITMAP)SelectObject(memDC, CORNER[3]);
					TransparentBlt(hDC, block[i][j].xPos, block[i][j].yPos, 30, 30, memDC, 0, 0, 48, 48, RGB(255, 255, 255));
					break;
				default:
					break;
				}
			}
		}
	}
	DeleteObject(BAR[0]);
	DeleteObject(BAR[1]);
	DeleteObject(CORNER[0]);
	DeleteObject(CORNER[1]);
	DeleteObject(CORNER[2]);
	DeleteObject(CORNER[3]);
	DeleteDC(memDC);
}

void checkpipe(Block block[25][15], int widthn, int heightn)
{
	BOOL check1;
	for (int i = 0; i < 16; ++i)
	{
		check1 = TRUE;
		for (int j = 0; j < widthn; ++j)
		{
			if (block[i][j].cs != 0)
				check1 = FALSE;
		}
		if (check1)
		{
			for (int j = i; j < heightn; ++j)
			{
				for (int k = 0; k < widthn; ++k)
				{
					block[j][k].cs = block[j + 1][k].cs;
				}
			}
			break;
		}
	}
}

void checkpipe2(Block block[25][15], int widthn, int heightn)
{
	BOOL check2;
	int left, Top;

	for (int i = 1; i < heightn; ++i)
	{

		check2 = FALSE;
		for (int j = 0; j < widthn; ++j)
		{
			if (block[i][j].cs == 4)
			{

				if (block[i][j + 1].cs == 5 && block[i - 1][j].cs == 3 && block[i - 1][j + 1].cs == 2)
				{
					check2 = TRUE;
					Top = i;
					left = j;
				}
			}
		}
		if (check2)
		{
			if (Top < heightn - 4)
			{
				for (int i = Top - 1; i < 14; ++i)
				{
					block[i][left].cs = block[i + 2][left].cs;
					block[i][left + 1].cs = block[i + 2][left + 1].cs;
				}
			}
			break;
		}
	}
}

BOOL checkpipe3(Block block[25][15], int widthn, int heightn)
{
	for (int i = 0; i < widthn; ++i)
	{
		if (block[heightn - 1][i].cs != -1)
			return TRUE;
	}
	return FALSE;
}

void DrawGrid(HDC hDC, int heightn, int widthn)
{

	for (int i = 0; i <= widthn; ++i)
	{
		MoveToEx(hDC, i * 30, 0, NULL);
		LineTo(hDC, i * 30, (heightn + 1) * 30);
	}

	for (int i = 0; i <= heightn + 1; ++i)
	{
		MoveToEx(hDC, 0, i * 30, NULL);
		LineTo(hDC, widthn * 30, i * 30);
	}
	
	
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC hDC, MemDC, tmpDC;
	static HBITMAP BackBit, oldBackBit;
	static RECT bufferRT;
	static Block block[25][15];
	static int Flag[4];
	static int status;
	static int current;
	static int currentwidthn;
	int f;
	switch (iMessage) {
	case WM_CREATE:
		Grid = FALSE;
		r = 255;
		g = 255;
		b = 255;
		widthn = 10;
		heightn = 20;
		xPos = 150;
		yPos = 0;
		cs = -1;
		status = 4;
		Flag[0] = 0;
		Flag[1] = 1;
		Flag[2] = 2;
		Flag[3] = 3;
		second = 50;
		current = 50;
		currentwidthn = 10;
		SetTimer(hWnd, 1, current, NULL);

		for (int i = 0; i < heightn; ++i)
		{
			for (int j = 0; j < widthn; ++j)
				block[i][j].cs = -1;
		}

		for (int i = 0; i < widthn; ++i)
		{
			block[0][i].xPos = 30 * i;
			block[0][i].yPos = 30 * heightn;
			block[0][i].cs = 999;
		}

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			xPos -= 30;
			if (xPos < 0)
				xPos = 0;
			break;
		case VK_RIGHT:
			xPos += 30;
			if (xPos >= 30 * widthn)
				xPos = 30* (widthn - 1);
			break;
		case VK_SPACE:
			if (cs == 0)
				cs = 1;
			else if (cs == 1)
				cs = 0;
			else if (cs == 2)
				cs += 1;
			else if (cs == 3)
				cs += 1;
			else if (cs == 4)
				cs += 1;
			else if (cs == 5)
				cs = 2;
			break;
		}
		break;
	case WM_LBUTTONDOWN:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg1_Proc);
		break;
	case WM_TIMER:
		if (current != second)
		{
			SetTimer(hWnd, 1, second, NULL);
			current = second;
		}

		if (currentwidthn != widthn)
		{
			xPos = 150;
			yPos = 0;
			cs = -1;
			status = 4;
			Flag[0] = 0;
			Flag[1] = 1;
			Flag[2] = 2;
			Flag[3] = 3;
			currentwidthn = widthn;


			for (int i = 0; i < heightn; ++i)
			{
				for (int j = 0; j < widthn; ++j)
					block[i][j].cs = -1;
			}

			for (int i = 0; i < widthn; ++i)
			{
				block[0][i].xPos = 30 * i;
				block[0][i].yPos = 30 * heightn;
				block[0][i].cs = 999;
			}
		}

		if (cs == -1)
		{
			srand(time(NULL));
			f = rand() % status;
			cs = Flag[f];
			Flag[f] = Flag[status - 1];
			--status;
			if (status == 0)
			{
				status = 4;
				Flag[0] = 0;
				Flag[1] = 1;
				Flag[2] = 2;
				Flag[3] = 3;
			}

			xPos = 150;
			yPos = 0;
		}
		if (yPos > 30*heightn)
		{
			yPos = 0;
			cs = -1;
		}
		else
		{
			yPos += 10;
			for (int i = 0; i < heightn; ++i)
			{
				for (int j = 0; j < widthn; ++j)
				{
					if (block[i][j].cs == 999 && yPos == block[i][j].yPos && xPos == block[i][j].xPos)
					{
						block[i][j].cs = cs;
						if (j < widthn)
						{
							block[i + 1][j].cs = 999;
							block[i + 1][j].xPos = block[i][j].xPos;
							block[i + 1][j].yPos = block[i][j].yPos - 30;
							cs = -1;
						}


					}
				}
			}
		}

		checkpipe(block, widthn, heightn);
		checkpipe2(block, widthn, heightn);
		if (checkpipe3(block, widthn, heightn))
			PostQuitMessage(0);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		MemDC = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &bufferRT);
		hDC = CreateCompatibleDC(MemDC);
		BackBit = CreateCompatibleBitmap(MemDC, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(hDC, BackBit);
		PatBlt(hDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

		HBRUSH hBrush, oldBrush;

		hBrush = CreateSolidBrush(RGB(r, g, b));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		Rectangle(hDC, 0, 0, widthn * 30, (heightn + 1) * 30);

		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		if (Grid)
		{
			DrawGrid(hDC, heightn, widthn);
		}

		Animation(xPos, yPos, hDC, cs, block, widthn, heightn);

		GetClientRect(hWnd, &bufferRT);
		BitBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(hDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK Dlg1_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) {
	case WM_INITDIALOG:
		
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_FINISH:
			EndDialog(hDlg, 0);
			break;

		case IDC_BUTTON1:
			xPos -= 30;
			if (xPos < 0)
				xPos = 0;
			break;

		case IDC_BUTTON2:
			xPos += 30;
			if (xPos >= 30 * widthn)
				xPos = 30 * (widthn - 1);
			break;

		case IDC_BUTTON3:
			if (cs == 0)
				cs = 1;
			else if (cs == 1)
				cs = 0;
			else if (cs == 2)
				cs += 1;
			else if (cs == 3)
				cs += 1;
			else if (cs == 4)
				cs += 1;
			else if (cs == 5)
				cs = 2;
			break;

		case IDC_BUTTON4:
			if (cs == 0)
				cs = 1;
			else if (cs == 1)
				cs = 0;
			else if (cs == 2)
				cs = 5;
			else if (cs == 3)
				cs -= 1;
			else if (cs == 4)
				cs -= 1;
			else if (cs == 5)
				cs -= 1;
			break;

		case IDC_BUTTON5:
			second = 50;
			break;

		case IDC_BUTTON6:
			r = 255;
			g = 0;
			b = 0;
			break;

		case IDC_BUTTON9:
			r = 0;
			g = 255;
			b = 0;
			break;

		case IDC_BUTTON10:
			r = 0;
			g = 0;
			b = 255;
			break;

		case IDC_BUTTON7:
			second = 100;
			break;

		case IDC_BUTTON8:
			second = 25;
			break;

		case IDC_RADIO3:
			Grid = TRUE;
			break;

		case IDC_RADIO4:
			Grid = FALSE;
			break;

		case IDC_RADIO1:
			widthn = 10;
			heightn = 20;
			break;

		case IDC_RADIO2:
			widthn = 15;
			heightn = 25;
			break;
		}
		break;
	case WM_PAINT:
		
		break;
	}
	return 0;
}