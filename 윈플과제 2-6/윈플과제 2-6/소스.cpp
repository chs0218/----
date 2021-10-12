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

class Shape {
public:

	int X, Y, shape;
	int r, g, b;
	int n = 0;
	Shape()
	{
		X = 0, Y = 0, shape = 0;
		r = 0, g = 0, b = 0;
	}

	void Draw(HDC hDC, HBRUSH hBrush, HBRUSH oldBrush)
	{
		if (shape == 1)
			Ellipse(hDC, X * 10 + 2, Y * 10 + 2, (X + n) * 10 + 8, (Y + n) * 10 + 8);
		
		else if (shape == 2)
		{
			MoveToEx(hDC, X * 10 + (n + 1) * 5, Y * 10 + 2, NULL);
			LineTo(hDC, X * 10 + 2, (Y + n) * 10 + 8);
			MoveToEx(hDC, X * 10 + (n + 1) * 5, Y * 10 + 2, NULL);
			LineTo(hDC, (X + n) * 10 + 8, (Y + n) * 10 + 8);
			MoveToEx(hDC, X * 10 + 2, (Y + n) * 10 + 8, NULL);
			LineTo(hDC, (X + n) * 10 + 8, (Y + n) * 10 + 8);
		}

		else if (shape == 3)
		{
			Rectangle(hDC, X * 10 + 2, Y * 10 + 2, (X + n) * 10 + 8, (Y + n) * 10 + 8);
		}
		
	}
};

void DrawBoard(HDC hDC, int num)
{
	int x = 0, y = 0;
	if (num == 30)
	{
		for (int i = 0; i <= 30; ++i)
		{
			MoveToEx(hDC, x, y, NULL);
			LineTo(hDC, x, y + 300);
			x += 10;
		}

		x = 0;

		for (int i = 0; i <= 30; ++i)
		{
			MoveToEx(hDC, x, y, NULL);
			LineTo(hDC, x + 300, y);
			y += 10;
		}
	}

	else if (num == 40)
	{
		for (int i = 0; i <= 40; ++i)
		{
			MoveToEx(hDC, x, y, NULL);
			LineTo(hDC, x, y + 400);
			x += 10;
		}

		x = 0;

		for (int i = 0; i <= 40; ++i)
		{
			MoveToEx(hDC, x, y, NULL);
			LineTo(hDC, x + 400, y);
			y += 10;
		}
	}

	else if (num == 50)
	{
		for (int i = 0; i <= 50; ++i)
		{
			MoveToEx(hDC, x, y, NULL);
			LineTo(hDC, x, y + 500);
			x += 10;
		}

		x = 0;

		for (int i = 0; i <= 50; ++i)
		{
			MoveToEx(hDC, x, y, NULL);
			LineTo(hDC, x + 500, y);
			y += 10;
		}
	}
}

void RandomCircle(Shape shape[6], int Board[50][50], int num, int* nShape)
{
	
}

void RandomTriangle(Shape shape[], int Board[50][50], int num, int* nShape)
{
	int x, y;
	while (1)
	{
		x = rand() % num;
		y = rand() % num;
		if (Board[x][y] == 0)
		{
			Board[x][y] = 2;
			break;
		}
	}
	if (*nShape == 6)
	{
		for (int i = 0; i < 5; ++i)
			shape[i] = shape[i + 1];
		*nShape = 5;
	}
	shape[*nShape].shape = 2;
	shape[*nShape].X = x;
	shape[*nShape].Y = y;
	shape[*nShape].r = rand() % 255;
	shape[*nShape].g = rand() % 255;
	shape[*nShape].b = rand() % 255;

	*nShape++;
}

void RandomRectangle(Shape shape[], int Board[50][50], int num, int* nShape)
{
	int x, y;
	while (1)
	{
		x = rand() % num;
		y = rand() % num;
		if (Board[x][y] == 0)
		{
			Board[x][y] = 3;
			break;
		}
	}

	if (*nShape == 6)
	{
		for (int i = 0; i < 5; ++i)
			shape[i] = shape[i + 1];
		*nShape = 5;
	}
	shape[*nShape].shape = 3;
	shape[*nShape].X = x;
	shape[*nShape].Y = y;
	shape[*nShape].r = rand() % 255;
	shape[*nShape].g = rand() % 255;
	shape[*nShape].b = rand() % 255;

	*nShape++;
}

void DrawCircle(HDC hDC, int x, int y)
{
	Ellipse(hDC, x * 10 + 2, y * 10 + 2, x * 10 + 8, y * 10 + 8);
}

void DrawTriangle(HDC hDC, int x, int y)
{
	MoveToEx(hDC, x * 10 + 5, y * 10 + 2, NULL);
	LineTo(hDC, x * 10 + 2, y * 10 + 8);
	MoveToEx(hDC, x * 10 + 5, y * 10 + 2, NULL);
	LineTo(hDC, x * 10 + 8, y * 10 + 8);
	MoveToEx(hDC, x * 10 + 2, y * 10 + 8, NULL);
	LineTo(hDC, x * 10 + 8, y * 10 + 8);
}

void DrawRectangle(HDC hDC, int x, int y)
{
	Rectangle(hDC, x * 10 + 2, y * 10 + 2, x * 10 + 8, y * 10 + 8);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{

	PAINTSTRUCT ps;
	HDC hDC;
	static int num;
	static int Board[50][50] = { 0, };
	static int nShape = 0;
	static int Select = 0;
	static int Shapenum[5] = { 0, };
	static Shape shape[5];
	static int check = 0;
	HBRUSH hBrush, oldBrush;
	HPEN MyPen, OldPen;
	int x, y;
	switch (iMessage) {
	case WM_CREATE:
		num = 40;
		break;
	case WM_KEYDOWN:
		if (wParam == VK_UP)
		{
			if (Select == 5)
			{
				for (int i = 0; i < 5; ++i)
				{
					shape[i].Y--;
					if (shape[i].Y < 0)
						shape[i].Y = 0;
				}
			}
			else
			{
				shape[Select].Y--;
				if (shape[Select].Y < 0)
					shape[Select].Y = 0;
			}
		}
		else if(wParam == VK_DOWN)
		{
			if (Select == 5)
			{
				for (int i = 0; i < 5; ++i)
				{
					shape[i].Y++;
					if (shape[i].Y + shape[i].n >= num)
						shape[i].Y--;
				}
			}
			else
			{
				shape[Select].Y++;
				if (shape[Select].Y + shape[Select].n >= num)
					shape[Select].Y--;
			}
			
		}
		else if (wParam == VK_RIGHT)
		{
			if (Select == 5)
			{
				for (int i = 0; i < 5; ++i)
				{
					shape[i].X++;
					if (shape[i].X + shape[i].n >= num)
						shape[i].X--;
				}
			}
			else
			{
				shape[Select].X++;
				if ((shape[Select].X + shape[Select].n) >= num)
					shape[Select].X--;
			}
			
		}
		else if (wParam == VK_LEFT)
		{
			if (Select == 5)
			{
				for (int i = 0; i < 5; ++i)
				{
					shape[i].X--;
					if (shape[i].X < 0)
						shape[i].X = 0;
				}
			}
			else
			{
				shape[Select].X--;
				if (shape[Select].X < 0)
					shape[Select].X = 0;
			}
			
		}

		else if (wParam == VK_DELETE)
		{
			if (Select == 5)
			{
				for (int i = 0; i < nShape; ++i)
				{
					shape[i].shape = 0;
					shape[i].n = 0;
				}
				nShape = 0;
				for (int i = 0; i < 5; ++i)
					Shapenum[i] = 0;
			}

			else
			{
				shape[Select].shape = 0;
				shape[Select].n = 0;

				Shapenum[Select] = 0;
			}

		}

		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		if (wParam == 'E' || wParam == 'e')
		{
			while (1)
			{
				x = rand() % num;
				y = rand() % num;
				if (Board[x][y] == 0)
				{
					Board[x][y] = 1;
					break;
				}
			}
			
			for (int i = 0; i < nShape; ++i)
			{
				if (Shapenum[i] == 0)
				{
					nShape = i;
					break;
				}
			}

			if (nShape == 5)
			{
				for (int i = 0; i < 4; ++i)
					shape[i] = shape[i + 1];
				nShape = 4;
			}
			
			
			shape[nShape].shape = 1;
			shape[nShape].X = x;
			shape[nShape].Y = y;
			shape[nShape].r = rand() % 255;
			shape[nShape].g = rand() % 255;
			shape[nShape].b = rand() % 255;
			Shapenum[nShape] = 1;
			nShape++;
			Select = nShape;
			for (int i = 0; i < 5; ++i)
			{
				
				if (Shapenum[i] == 0)
				{
					break;
				}
				nShape = i + 1;
			}
		}

		else if (wParam == 'T' || wParam == 't')
		{
			while (1)
			{
				x = rand() % num;
				y = rand() % num;
				if (Board[x][y] == 0)
				{
					Board[x][y] = 2;
					break;
				}
			}
			for (int i = 0; i < nShape; ++i)
			{
				if (Shapenum[i] == 0)
				{
					nShape = i;
					break;
				}
			}
			if (nShape == 5)
			{
				for (int i = 0; i < 4; ++i)
					shape[i] = shape[i + 1];
				nShape = 4;
			}
			shape[nShape].shape = 2;
			shape[nShape].X = x;
			shape[nShape].Y = y;
			shape[nShape].r = rand() % 255;
			shape[nShape].g = rand() % 255;
			shape[nShape].b = rand() % 255;
			Shapenum[nShape] = 1;
			nShape++;
			Select = nShape;

			for (int i = 0; i < 5; ++i)
			{

				if (Shapenum[i] == 0)
				{
					break;
				}
				nShape = i + 1;
			}

		}

		else if (wParam == 'R' || wParam == 'r')
		{
			while (1)
			{
				x = rand() % num;
				y = rand() % num;
				if (Board[x][y] == 0)
				{
					Board[x][y] = 3;
					break;
				}
			}
			for (int i = 0; i < nShape; ++i)
			{
				if (Shapenum[i] == 0)
				{
					nShape = i;
					break;
				}
			}

			if (nShape == 5)
			{
				for (int i = 0; i < 4; ++i)
					shape[i] = shape[i + 1];
				nShape = 4;
			}
			shape[nShape].shape = 3;
			shape[nShape].X = x;
			shape[nShape].Y = y;
			shape[nShape].r = rand() % 255;
			shape[nShape].g = rand() % 255;
			shape[nShape].b = rand() % 255;
			Shapenum[nShape] = 1;
			nShape++;
			Select = nShape;

			for (int i = 0; i < 5; ++i)
			{

				if (Shapenum[i] == 0)
				{
					break;
				}
				nShape = i + 1;
			}

		}

		else if (wParam == '+')
		{
			if (Select == 5)
			{
				for (int i = 0; i < 5; ++i)
				{
					shape[i].n += 1;
					if (shape[i].X + shape[i].n >= num)
						shape[i].n -= 1;
					else if (shape[i].X - shape[i].n < 0)
						shape[i].n -= 1;

					else if ((shape[i].Y + shape[i].n) >= num)
						shape[i].n -= 1;

				}
			}
			else
			{
				shape[Select].n += 1;
				if (shape[Select].X + shape[Select].n >= num)
					shape[Select].n -= 1;
				else if(shape[Select].X - shape[Select].n < 0)
					shape[Select].n -= 1;
				else if ((shape[Select].Y + shape[Select].n) >= num)
					shape[Select].n -= 1;
			}
		}

		else if (wParam == '-')
		{
			if (Select == 5)
			{
				for (int i = 0; i < 5; ++i)
				{
					shape[i].n -= 1;

					if (shape[i].n < 0)
						shape[i].n = 0;
				}
			}
			else
			{
				shape[Select].n -= 1;

				if (shape[Select].n < 0)
					shape[Select].n = 0;
			}
		}

		else if(wParam=='q'||wParam=='Q')
			PostQuitMessage(0);


		else if (wParam == 's')
		{
		for (int i = 0; i < 5; ++i)
			if (Shapenum[i] != 0)
			{
				check = 1;
				break;
			}

		if (check == 0)
			num = 30;

		}
		else if (wParam == 'm')
		{

		for (int i = 0; i < 5; ++i)
			if (Shapenum[i] != 0)
			{
				check = 1;
				break;
			}
		if (check == 0)
			num = 40;
		}
		else if (wParam == 'l')
		{

		for (int i = 0; i < 5; ++i)
			if (Shapenum[i] != 0)
			{
				check = 1;
				break;
			}
		if (check == 0)
			num = 50;
		}

		else if (wParam == '1')
			Select = 0;
		else if (wParam == '2')
			Select = 1;
		else if (wParam == '3')
			Select = 2;
		else if (wParam == '4')
			Select = 3;
		else if (wParam == '5')
			Select = 4;
		else if (wParam == '6')
			Select = 5;

		InvalidateRgn(hWnd, NULL, TRUE);

		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		DrawBoard(hDC, num);
		
		check = 0;
		for (int i = 0; i < nShape; ++i)
		{
			hBrush = CreateSolidBrush(RGB(shape[i].r, shape[i].g, shape[i].b));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			MyPen = CreatePen(PS_SOLID, 4, RGB(shape[i].r, shape[i].g, shape[i].b));
			OldPen = (HPEN)SelectObject(hDC, MyPen);
			shape[i].Draw(hDC, hBrush, oldBrush);
			SelectObject(hDC, OldPen);
			DeleteObject(MyPen);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
		}
		if (Select != 5)
		{
			hBrush = CreateSolidBrush(RGB(shape[Select].r, shape[Select].g, shape[Select].b));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			MyPen = CreatePen(PS_SOLID, 4, RGB(shape[Select].r, shape[Select].g, shape[Select].b));
			OldPen = (HPEN)SelectObject(hDC, MyPen);

			shape[Select].Draw(hDC, hBrush, oldBrush);

			SelectObject(hDC, OldPen);
			DeleteObject(MyPen);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}
