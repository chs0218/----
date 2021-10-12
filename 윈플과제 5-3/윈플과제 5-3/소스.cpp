#include <Windows.h>
#include <time.h>
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
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass;
	WndClass.hInstance = hInstance;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW,
		0, 0, 1700, 900, NULL, (HMENU)NULL, hInstance, NULL);

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
	HDC memDC;
	static HDC hDC, mem1DC, mem2DC;
	static HBITMAP hBit1, hBit2, oldBit1, oldBit2;
	PAINTSTRUCT ps;
	HPEN hPen, oldPen;
	static BOOL Select, Start, Command1, Command2, CommandD, CommandC, CommandP, CommandX, RBUTTON, CommandH, CommandV;
	static int mx, my, mx2, my2, Copyx, Copyy;
	static int Width, Height;
	static RECT Copy, Rectangle;
	switch (iMessage) {
	case WM_CREATE:
		Width = 0;
		Height = 0;
		Start = FALSE;
		Select = FALSE;
		Command1 = FALSE;
		Command2 = FALSE;
		CommandD = TRUE;
		CommandC = FALSE;
		CommandP = FALSE;
		CommandH = FALSE;
		CommandV = FALSE;
		CommandX = FALSE;
		RBUTTON = FALSE;
		Copy.left = 0;
		Copy.right = 0;
		Copy.top = 0;
		Copy.bottom = 0;
		Copyx = 0;
		Copyy = 0;
		SetTimer(hWnd, 1, 100, NULL);
		hBit2 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		break;

	case WM_TIMER:
		if (wParam == 1)
		{
			hDC = GetDC(hWnd);

			hBit1 = CreateCompatibleBitmap(hDC, 1700, 900);

			mem1DC = CreateCompatibleDC(hDC);
			mem2DC = CreateCompatibleDC(mem1DC);
			

			oldBit1 = (HBITMAP)SelectObject(mem1DC, hBit1);
			oldBit2 = (HBITMAP)SelectObject(mem2DC, hBit2);
			BitBlt(mem1DC, 0, 0, 1700, 900, mem2DC, 0, 0, SRCCOPY);

			SetBkMode(mem1DC, TRANSPARENT);


			hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
			oldPen = (HPEN)SelectObject(mem1DC, hPen);
			MoveToEx(mem1DC, Rectangle.left, Rectangle.top, NULL);
			LineTo(mem1DC, Rectangle.right, Rectangle.top);

			MoveToEx(mem1DC, Rectangle.left, Rectangle.top, NULL);
			LineTo(mem1DC, Rectangle.left, Rectangle.bottom);

			MoveToEx(mem1DC, Rectangle.right, Rectangle.bottom, NULL);
			LineTo(mem1DC, Rectangle.right, Rectangle.top);

			MoveToEx(mem1DC, Rectangle.right, Rectangle.bottom, NULL);
			LineTo(mem1DC, Rectangle.left, Rectangle.bottom);
			SelectObject(mem1DC, oldPen);
			DeleteObject(hPen);

			

			if (CommandD)
			{
				if (CommandH)
				{
					if (CommandV)
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2, my2, -1 * Width, -1 * Height, SRCCOPY);
					else
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2, my, -1 * Width, Height, SRCCOPY);
				}
				else if (CommandV)
				{
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx, my2, Width, -1 * Height, SRCCOPY);
				}
				else
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx, my, Width, Height, SRCCOPY);
			}

			else if (Command1)
			{
				if (CommandH)
				{
					if (CommandV)
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2 - (Width*0.1), my2 - (Height*0.1), -1 * Width * 0.8, -1 * Height*0.8, SRCCOPY);
					else
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2 - (Width*0.1), my + (Height*0.1), -1 * Width * 0.8, Height*0.8, SRCCOPY);
				}
				else if (CommandV)
				{
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx + (Width*0.1), my2 - (Height*0.1), Width * 0.8, -1 * Height*0.8, SRCCOPY);
				}
				else
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx + (Width*0.1), my + (Height*0.1), Width * 0.8, Height*0.8, SRCCOPY);

			}

			else if (Command2)
			{
				if (CommandH)
				{
					if (CommandV)
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2 - (Width*0.2), my2 - (Height*0.2), -1 * Width * 0.6, -1 * Height*0.6, SRCCOPY);
					else
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2 - (Width*0.2), my + (Height*0.2), -1 * Width * 0.6, Height*0.6, SRCCOPY);
				}
				else if (CommandV)
				{
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx + (Width*0.2), my2 - (Height*0.2), Width * 0.6, -1 * Height*0.6, SRCCOPY);
				}
				else
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx + (Width*0.2), my + (Height*0.2), Width * 0.6, Height*0.6, SRCCOPY);
			}

			else if (CommandX)
			{
				if (CommandH)
				{
					if (CommandV)
						StretchBlt(mem1DC, 0, 0, 1312, 768, mem1DC, Copy.right, Copy.bottom, Copy.left - Copy.right, Copy.top - Copy.bottom, SRCCOPY);
					else
						StretchBlt(mem1DC, 0, 0, 1312, 768, mem1DC, Copy.right, Copy.top, Copy.left - Copy.right, Copy.bottom - Copy.top, SRCCOPY);
				}
				else if (CommandV)
				{
					StretchBlt(mem1DC, 0, 0, 1312, 768, mem1DC, Copy.left, Copy.bottom, Copy.right - Copy.left, Copy.top - Copy.bottom, SRCCOPY);
				}
				else
					StretchBlt(mem1DC, 0, 0, 1312, 768, mem1DC, Copy.left, Copy.top, Copy.right - Copy.left, Copy.bottom - Copy.top, SRCCOPY);
			}
				
			if (RBUTTON)
			{
				BitBlt(mem1DC, Copyx, Copyy, Copy.right - Copy.left, Copy.bottom - Copy.top, mem2DC, Copy.left, Copy.top, SRCCOPY);
			}
			SelectObject(mem2DC, oldBit2);
			DeleteDC(mem2DC);
			SelectObject(mem1DC, oldBit1);
			DeleteDC(mem1DC);
			ReleaseDC(hWnd, hDC);
			InvalidateRgn(hWnd, NULL, FALSE);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == '1')
		{
			Command1 = TRUE;
			Command2 = FALSE;
			CommandD = FALSE;
		}

		if (wParam == '2')
		{
			Command1 = FALSE;
			Command2 = TRUE;
			CommandD = FALSE;
		}

		else if (wParam == '0')
		{
			Command1 = FALSE;
			Command2 = FALSE;
			CommandD = TRUE;
		}

		else if (wParam == 'C')
		{
			Copy.left = mx;
			Copy.right = mx2;
			Copy.top = my;
			Copy.bottom = my2;
		}

		else if (wParam == 'W')
		{
			my -= 5;
			my2 -= 5;
			if (my < 8 || my2 < 8)
			{
				my += 5;
				my2 += 5;
			}
		}

		else if (wParam == 'A')
		{
			mx -= 5;
			mx2 -= 5;
			if (mx2 < 0 || mx < 0)
			{
				mx += 5;
				mx2 += 5;
			}
		}

		else if (wParam == 'S')
		{
			my += 5;
			my2 += 5;
			if (my > 768 || my2 > 768)
			{
				my -= 5;
				my2 -= 5;
			}
		}

		else if (wParam == 'D')
		{
			mx += 5;
			mx2 += 5;
			if (mx2 > 1312 || mx > 1312)
			{
				mx -= 5;
				mx2 -= 5;
			}
		}

		else if (wParam == 'H')
		{
			if (CommandH)
				CommandH = FALSE;
			else
				CommandH = TRUE;
		}

		else if (wParam == 'V')
		{
			if (CommandV)
				CommandV = FALSE;
			else
				CommandV = TRUE;
		}

		else if (wParam == VK_RIGHT)
		{
			

			Rectangle.left += 5;
			Rectangle.right += 5;
			if (Rectangle.left > 1312 || Rectangle.right > 1312)
			{
				Rectangle.right -= 5;
				Rectangle.left -= 5;
			}
		}

		else if (wParam == VK_LEFT)
		{
			

			Rectangle.left -= 5;
			Rectangle.right -= 5;
			if (Rectangle.right < 0 || Rectangle.left < 0)
			{
				mx += 5;
				mx2 += 5;
			}
		}

		else if (wParam == VK_UP)
		{
			

			Rectangle.bottom -= 5;
			Rectangle.top -= 5;
			if (Rectangle.top < 8 || Rectangle.bottom < 8)
			{
				Rectangle.top += 5;
				Rectangle.bottom += 5;
			}
		}

		else if (wParam == 'R')
		{
			Width = 0;
			Height = 0;
			Start = FALSE;
			Select = FALSE;
			Command1 = FALSE;
			Command2 = FALSE;
			CommandD = TRUE;
			CommandC = FALSE;
			CommandP = FALSE;
			CommandH = FALSE;
			CommandV = FALSE;
			CommandX = FALSE;
			RBUTTON = FALSE;
			Copy.left = 0;
			Copy.right = 0;
			Copy.top = 0;
			Copy.bottom = 0;
			Copyx = 0;
			Copyy = 0;
			SetTimer(hWnd, 1, 100, NULL);
			hBit2 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
			mx = 0;
			mx2 = 0;
			my = 0;
			my2 = 0;
		}

		else if (wParam == VK_DOWN)
		{

			Rectangle.bottom += 5;
			Rectangle.top += 5;
			if (Rectangle.top > 768 || Rectangle.bottom > 768)
			{
				Rectangle.top -= 5;
				Rectangle.bottom -= 5;
			}
		}

		else if (wParam == 'X')
		{
			if (CommandX)
			{
				CommandX = FALSE;
				CommandD = TRUE;
			}
			else
			{
				CommandX = TRUE;
				CommandD = FALSE;
				Command1 = FALSE;
				Command2 = FALSE;
			}
		}
		break;
	case WM_CHAR:
		if (wParam == 'M')
		{
			if (Rectangle.left < Rectangle.right)
			{
				Rectangle.left -= 5;
				Rectangle.right += 5;

				if (Rectangle.top < Rectangle.bottom)
				{
					Rectangle.top -= 5;
					Rectangle.bottom += 5;
				}

				else
				{
					Rectangle.top += 5;
					Rectangle.bottom -= 5;
				}
			}
			else
			{
				Rectangle.left += 5;
				Rectangle.right -= 5;

				if (my < my2)
				{
					Rectangle.top -= 5;
					Rectangle.bottom += 5;
				}

				else
				{
					Rectangle.top += 5;
					Rectangle.bottom -= 5;
				}
			}

			Width = Rectangle.right - Rectangle.left;
			Height = Rectangle.bottom - Rectangle.top;
		}

		else if (wParam == 'm')
		{
			if (Rectangle.left < Rectangle.right)
			{
				Rectangle.left += 5;
				Rectangle.right -= 5;

				if (Rectangle.top < Rectangle.bottom)
				{
					Rectangle.top += 5;
					Rectangle.bottom -= 5;
				}

				else
				{
					Rectangle.top -= 5;
					Rectangle.bottom += 5;
				}
			}
			else
			{
				Rectangle.left -= 5;
				Rectangle.right += 5;

				if (my < my2)
				{
					Rectangle.top += 5;
					Rectangle.bottom -= 5;
				}

				else
				{
					Rectangle.top -= 5;
					Rectangle.bottom += 5;
				}
			}

			Width = Rectangle.right - Rectangle.left;
			Height = Rectangle.bottom - Rectangle.top;
		}

		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mem1DC = CreateCompatibleDC(hDC);
		oldBit1 = (HBITMAP)SelectObject(mem1DC, hBit1);

		BitBlt(hDC, 0, 0, 1312, 768, mem1DC, 0, 0, SRCCOPY);

		SelectObject(mem1DC, oldBit1);
		DeleteDC(mem2DC);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		Select = TRUE;
		Start = TRUE;
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		Rectangle.left = mx;
		Rectangle.top = my;

		mx2 = mx;
		my2 = my;

		Rectangle.right = mx2;
		Rectangle.bottom = my2;
		break;

	case WM_RBUTTONDOWN:
		RBUTTON = TRUE;
		Copyx = LOWORD(lParam);
		Copyy = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		Select = FALSE;
		break;
	case WM_MOUSEMOVE:

		hDC = GetDC(hWnd);

		hBit1 = CreateCompatibleBitmap(hDC, 1700, 900);

		mem1DC = CreateCompatibleDC(hDC);
		mem2DC = CreateCompatibleDC(mem1DC);

		oldBit1 = (HBITMAP)SelectObject(mem1DC, hBit1);
		oldBit2 = (HBITMAP)SelectObject(mem2DC, hBit2);

		BitBlt(mem1DC, 0, 0, 1700, 900, mem2DC, 0, 0, SRCCOPY);

		SetBkMode(mem1DC, TRANSPARENT);

		if (Select)
		{
			mx2 = LOWORD(lParam);
			my2 = HIWORD(lParam);
			Rectangle.right = mx2;
			Rectangle.bottom = my2;
			Width = Rectangle.right - Rectangle.left;
			Height = Rectangle.bottom - Rectangle.top;
		}

		

		if(Start)
		{
			hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
			oldPen = (HPEN)SelectObject(mem1DC, hPen);
			MoveToEx(mem1DC, Rectangle.left, Rectangle.top, NULL);
			LineTo(mem1DC, Rectangle.right, Rectangle.top);

			MoveToEx(mem1DC, Rectangle.left, Rectangle.top, NULL);
			LineTo(mem1DC, Rectangle.left, Rectangle.bottom);

			MoveToEx(mem1DC, Rectangle.right, Rectangle.bottom, NULL);
			LineTo(mem1DC, Rectangle.right, Rectangle.top);

			MoveToEx(mem1DC, Rectangle.right, Rectangle.bottom, NULL);
			LineTo(mem1DC, Rectangle.left, Rectangle.bottom);
			SelectObject(mem1DC, oldPen);
			DeleteObject(hPen);

			if (CommandD)
			{
				if (CommandH)
				{
					if (CommandV)
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2, my2, -1 * Width, -1 * Height, SRCCOPY);
					else
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2, my, -1 * Width, Height, SRCCOPY);
				}
				else if (CommandV)
				{
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx, my2, Width, -1 * Height, SRCCOPY);
				}
				else
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx, my, Width, Height, SRCCOPY);
			}

			else if (Command1)
			{
				if (CommandH)
				{
					if (CommandV)
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2 - (Width*0.1), my2 - (Height*0.1), -1 * Width * 0.8, -1 * Height*0.8, SRCCOPY);
					else
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2 - (Width*0.1), my + (Height*0.1), -1 * Width * 0.8, Height*0.8, SRCCOPY);
				}
				else if (CommandV)
				{
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx + (Width*0.1), my2 - (Height*0.1), Width * 0.8, -1 * Height*0.8, SRCCOPY);
				}
				else
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx + (Width*0.1), my + (Height*0.1), Width * 0.8, Height*0.8, SRCCOPY);

			}

			else if (Command2)
			{
				if (CommandH)
				{
					if (CommandV)
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2 - (Width*0.2), my2 - (Height*0.2), -1 * Width * 0.6, -1 * Height*0.6, SRCCOPY);
					else
						StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx2 - (Width*0.2), my + (Height*0.2), -1 * Width * 0.6, Height*0.6, SRCCOPY);
				}
				else if (CommandV)
				{
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx + (Width*0.2), my2 - (Height*0.2), Width * 0.6, -1 * Height*0.6, SRCCOPY);
				}
				else
					StretchBlt(mem1DC, Rectangle.left, Rectangle.top, (mx2 - mx), (my2 - my), mem2DC, mx + (Width*0.2), my + (Height*0.2), Width * 0.6, Height*0.6, SRCCOPY);
			}

			else if (CommandX)
			{
				if (CommandH)
				{
					if (CommandV)
						StretchBlt(mem1DC, 0, 0, 1312, 768, mem1DC, Copy.right, Copy.bottom, Copy.left - Copy.right, Copy.top - Copy.bottom, SRCCOPY);
					else
						StretchBlt(mem1DC, 0, 0, 1312, 768, mem1DC, Copy.right, Copy.top, Copy.left - Copy.right, Copy.bottom - Copy.top, SRCCOPY);
				}
				else if (CommandV)
				{
					StretchBlt(mem1DC, 0, 0, 1312, 768, mem1DC, Copy.left, Copy.bottom, Copy.right - Copy.left, Copy.top - Copy.bottom, SRCCOPY);
				}
				else
					StretchBlt(mem1DC, 0, 0, 1312, 768, mem1DC, Copy.left, Copy.top, Copy.right - Copy.left, Copy.bottom - Copy.top, SRCCOPY);
			}
		}

		if (RBUTTON)
		{
			BitBlt(mem1DC, Copyx, Copyy, Copy.right - Copy.left, Copy.bottom - Copy.top, mem2DC, Copy.left, Copy.top, SRCCOPY);
		}
		SelectObject(mem2DC, oldBit2);
		DeleteDC(mem2DC);
		SelectObject(mem1DC, oldBit1);
		DeleteDC(mem1DC);
		ReleaseDC(hWnd, hDC);
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}