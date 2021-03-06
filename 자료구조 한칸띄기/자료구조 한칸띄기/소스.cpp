#include <iostream>
#include <fstream>
#include <Windows.h>
#define Width 20
#define Height 20

void movetoxy(int col, int row)

{

	COORD position = { col, row };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

struct Stone {
	int x, y;
	Stone* next;
};

struct Stack {
	Stone* top;
};

void InitStack(Stack* stack)
{
	stack->top = NULL;
}

int IsEmpty(Stack* stack)
{
	return stack->top == NULL;
}

void Push(Stack* stack, int x, int y)
{
	Stone* now = new Stone;
	now->x = x;
	now->y = y;
	now->next = stack->top;
	stack->top = now;
}

void DrawBoard(int Board[20][20])
{
	for (int i = 0; i < Width; ++i)
	{
		if (i == 0)
			std::cout << "忙";
		else if (i == Width - 1)
			std::cout << "式忖";
		else
			std::cout << "式成";
	}
	std::cout << "\n";

	for (int i = 0; i < Height - 2; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			if (j == 0)
				std::cout << "戍";
			else if (j == Width - 1)
				std::cout << "式扣";
			else
				std::cout << "式戍";
		}
		std::cout << "\n";
	}

	for (int i = 0; i < Width; ++i)
	{
		if (i == 0)
			std::cout << "戌";
		else if (i == Width - 1)
			std::cout << "式戎";
		else
			std::cout << "式扛";
	}
	std::cout << "\n";

	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			if (Board[x][y] == 1)
			{
				movetoxy(x * 2, y);
				std::cout << "??";
			}
			else if (Board[x][y] == 2)
			{
				movetoxy(x * 2, y);
				std::cout << "寥";
			}

			else if (Board[x][y] == 4)
			{
				movetoxy(x * 2, y);
				std::cout << "∪";
			}
		}
	}
}

int commandR(Stack* stack, Stack* stackreturn, int Board[20][20], int n)
{
	Stone* now;
	int x, y;
	if (IsEmpty(stackreturn))
	{
		return 0;
	}
	n = n % 2;
	now = stackreturn->top;
	x = now->x;
	y = now->y;

	Push(&*stack, x, y);

	if (n == 1)
		Board[x][y] = 2;
	else
		Board[x][y] = 1;


	stackreturn->top = now->next;


	delete now;
	return 1;
}

void Delete(Stack* stack)
{
	Stone* now;

	if (IsEmpty(stack))
	{
		return;
	}

	now = stack->top;
	stack->top = now->next;
	delete now;
}

int Pop(Stack* stack, Stack* stackreturn, int Board[20][20])
{
	Stone* now;
	int x, y;
	if (IsEmpty(stack))
	{
		return 0;
	}

	now = stack->top;
	x = now->x;
	y = now->y;

	Push(&*stackreturn, x, y);
	Board[x][y] = 0;

	stack->top = now->next;


	delete now;
	return 1;
}

void CountStone(int Board[20][20], int* x, int* y, int* cs, int* Black, int* White, int* MaxBlack, int* MaxWhite, int BlackLocation[2], int WhiteLocation[2], int restart[2], BOOL A, BOOL Diag)
{
	switch (*cs)
	{
	case 0:
		switch (Board[*x][*y])
		{
		case 0:
		case 4:

			break;
		case 1:
			*Black = 1;
			*cs = 1;
			break;

		case 2:
			*White = 1;
			*cs = 2;
			break;
		}
		break;
	case 1:
		switch (Board[*x][*y])
		{
		case 0:
		case 4:
			++*Black;
			restart[0] = *x;
			restart[1] = *y;
			*cs = 3;
			break;
		case 1:
			++*Black;
			break;

		case 2:
			*White = 1;
			if (*Black > *MaxBlack)
			{
				BlackLocation[0] = *x;
				BlackLocation[1] = *y;
				*MaxBlack = *Black;
			}
			*Black = 0;
			*cs = 2;
			break;
		}
		break;
	case 2:
		switch (Board[*x][*y])
		{
		case 0:
		case 4:
			++*White;
			restart[0] = *x;
			restart[1] = *y;
			*cs = 4;
			break;
		case 1:
			*Black = 1;
			if (*White > *MaxWhite)
			{
				WhiteLocation[0] = *x;
				WhiteLocation[1] = *y;
				*MaxWhite = *White;
			}
			*White = 0;
			*cs = 1;
			break;
		case 2:
			++*White;
			break;
		}
		break;
	case 3:
		switch (Board[*x][*y])
		{
		case 0:
		case 4:
			if (*Black > *MaxBlack)
			{
				BlackLocation[0] = *x;
				BlackLocation[1] = *y;
				*MaxBlack = *Black;
				*Black = 0;
			}
			*x = restart[0];
			*y = restart[1];
			*cs = 0;
			break;
		case 1:
			++*Black;
			break;

		case 2:
			*White = 1;
			if (*Black > *MaxBlack)
			{
				BlackLocation[0] = *x;
				BlackLocation[1] = *y;
				*MaxBlack = *Black;
			}
			*Black = 0;
			*cs = 2;
			break;
		}
		break;
	case 4:
		switch (Board[*x][*y])
		{
		case 0:
		case 4:
			if (*White > *MaxWhite)
			{
				WhiteLocation[0] = *x;
				WhiteLocation[1] = *y;
				*MaxWhite = *White;
			}
			*White = 0;
			*x = restart[0];
			*y = restart[1];
			*cs = 0;
			break;
		case 1:
			*Black = 1;
			if (*White > *MaxWhite)
			{
				WhiteLocation[0] = *x;
				WhiteLocation[1] = *y;
				*MaxWhite = *White;
			}
			*White = 0;
			*cs = 1;
			break;
		case 2:
			++*White;
			break;
		}
		break;
	}
	if (!Diag)
	{
		if (A)
		{
			if (*x == 19)
			{
				if (*Black > *MaxBlack)
				{
					BlackLocation[0] = *x + 1;
					BlackLocation[1] = *y;
					*MaxBlack = *Black;
				}

				if (*White > *MaxWhite)
				{
					WhiteLocation[0] = *x + 1;
					WhiteLocation[1] = *y;
					*MaxWhite = *White;
				}
			}
		}

		else
		{
			if (*y == 19)
			{
				if (*Black > *MaxBlack)
				{
					BlackLocation[0] = *x;
					BlackLocation[1] = *y + 1;
					*MaxBlack = *Black;
				}

				if (*White > *MaxWhite)
				{
					WhiteLocation[0] = *x;
					WhiteLocation[1] = *y + 1;
					*MaxWhite = *White;
				}
			}
		}
	}

	else
	{
		if (A)
		{
			if (*x == 0 || *y == 19)
			{
				if (*Black > *MaxBlack)
				{
					BlackLocation[0] = *x - 1;
					BlackLocation[1] = *y + 1;
					*MaxBlack = *Black;
				}

				if (*White > *MaxWhite)
				{
					WhiteLocation[0] = *x - 1;
					WhiteLocation[1] = *y + 1;
					*MaxWhite = *White;
				}
			}
		}

		else
		{
			if (*x == 19 || *y == 19)
			{
				if (*Black > *MaxBlack)
				{
					BlackLocation[0] = *x + 1;
					BlackLocation[1] = *y + 1;
					*MaxBlack = *Black;
				}

				if (*White > *MaxWhite)
				{
					WhiteLocation[0] = *x + 1;
					WhiteLocation[1] = *y + 1;
					*MaxWhite = *White;
				}
			}
		}
	}
}

void MaxXStone(int Board[20][20])
{
	int x = 0, y = 0;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (y < 20)
	{
		while (x < 20)
		{
			CountStone(Board, &x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, TRUE, FALSE);
			++x;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				std::cout << y + 1 << "廓簞 陛煎還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack << " 翱樓脹 ?瘚? 謝ル:";
				for (int j = BlackLocation[0] - MaxBlack; j < BlackLocation[0]; ++j)
				{
					std::cout << "(" << j << ", " << y << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxBlack > 3)
				{
					for (int j = BlackLocation[0] - MaxBlack - 1; j < BlackLocation[0] + 1; ++j)
					{
						if (Board[j][y] == 0 && (-1 < j && j < 20))
						{
							if (Board[j - 1][y] != 4)
								Board[j][y] = 4;
						}
					}
				}
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << y + 1 << "廓簞 陛煎還曖 翱樓脹 寥給 偃熱: " << MaxWhite << " 翱樓脹 寥給 謝ル:";
				for (int j = WhiteLocation[0] - MaxWhite; j < WhiteLocation[0]; ++j)
				{
					std::cout << "(" << j << ", " << y << ")";
				}
				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[0] - MaxWhite - 1; j < WhiteLocation[0] + 1; ++j)
					{
						if (Board[j][y] == 0 && (-1 < j && j < 20))
						{
							if (Board[j - 1][y] != 4)
								Board[j][y] = 4;
						}
					}
				}
				std::cout << "                                                                                          \n";
			}
			else
			{
				std::cout << y + 1 << "廓簞 陛煎還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack << " 翱樓脹 ?瘚? 謝ル:";
				for (int j = BlackLocation[0] - MaxBlack; j < BlackLocation[0]; ++j)
				{
					std::cout << "(" << j << ", " << y << ")";
				}
				if (MaxBlack > 3)
				{
					for (int j = BlackLocation[0] - MaxBlack - 1; j < BlackLocation[0] + 1; ++j)
					{
						if (Board[j][y] == 0 && (-1 < j && j < 20))
						{
							if (Board[j - 1][y] != 4)
								Board[j][y] = 4;
						}
					}
				}
				std::cout << y + 1 << "廓簞 陛煎還曖 翱樓脹 寥給 偃熱: " << MaxWhite << " 翱樓脹 寥給 謝ル:";
				for (int j = WhiteLocation[0] - MaxWhite; j < WhiteLocation[0]; ++j)
				{
					std::cout << "(" << j << ", " << y << ")";
				}
				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[0] - MaxWhite - 1; j < WhiteLocation[0] + 1; ++j)
					{
						if (Board[j][y] == 0 && (-1 < j && j < 20))
						{
							if (Board[j - 1][y] != 4)
								Board[j][y] = 4;
						}
					}
				}
				std::cout << "\n";
			}
		}

		x = 0;
		++y;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	}

}

void MaxYStone(int Board[20][20])
{
	int x = 0, y = 0;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (x < 20)
	{
		while (y < 20)
		{
			CountStone(Board, &x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, FALSE, FALSE);
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				std::cout << x + 1 << "廓簞 撮煎還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack << " 翱樓脹 ?瘚? 謝ル:";
				for (int j = BlackLocation[1] - MaxBlack; j < BlackLocation[1]; ++j)
				{
					std::cout << "(" << x << ", " << j << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxBlack > 3)
				{
					for (int j = BlackLocation[1] - MaxBlack - 1; j < BlackLocation[1] + 1; ++j)
					{
						if (Board[x][j] == 0 && (-1 < j && j < 20))
						{
							if (Board[x][j - 1] != 4)
								Board[x][j] = 4;
						}
					}
				}

			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << x + 1 << "廓簞 撮煎還曖 翱樓脹 寥給 偃熱: " << MaxWhite << " 翱樓脹 寥給 謝ル:";
				for (int j = WhiteLocation[1] - MaxWhite; j < WhiteLocation[1]; ++j)
				{
					std::cout << "(" << x << ", " << j << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[1] - MaxWhite - 1; j < WhiteLocation[1] + 1; ++j)
					{
						if (Board[x][j] == 0 && (-1 < j && j < 20))
						{
							if (Board[x][j - 1] != 4)
								Board[x][j] = 4;
						}
					}
				}
			}
			else
			{
				std::cout << x + 1 << "廓簞 撮煎還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack << " 翱樓脹 ?瘚? 謝ル:";
				for (int j = BlackLocation[1] - MaxBlack; j < BlackLocation[1]; ++j)
				{
					std::cout << "(" << x << ", " << j << ")";
				}
				if (MaxBlack > 3)
				{
					for (int j = BlackLocation[1] - MaxBlack - 1; j < BlackLocation[1] + 1; ++j)
					{
						if (Board[x][j] == 0 && (-1 < j && j < 20))
						{
							if (Board[x][j - 1] != 4)
								Board[x][j] = 4;
						}
					}
				}
				std::cout << x + 1 << "廓簞 撮煎還曖 翱樓脹 寥給 偃熱: " << MaxWhite << " 翱樓脹 寥給 謝ル:";
				for (int j = WhiteLocation[1] - MaxWhite; j < WhiteLocation[1]; ++j)
				{
					std::cout << "(" << x << ", " << j << ")";
				}
				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[1] - MaxWhite - 1; j < WhiteLocation[1] + 1; ++j)
					{
						if (Board[x][j] == 0 && (-1 < j && j < 20))
						{
							if (Board[x][j - 1] != 4)
								Board[x][j] = 4;
						}
					}
				}

				std::cout << "\n";
			}
		}

		y = 0;
		++x;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	}
}

void MaxRDiagStone(int Board[20][20])
{
	int x = 0, y = 0;
	int StartY = 19;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (StartY >= 0)
	{
		y = StartY;
		while (y < 20)
		{
			CountStone(Board, &x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, FALSE, TRUE);
			++x;
			++y;
		}
		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				std::cout << 20 - StartY << "廓簞 螃艇薹 嬴楚 渠陝摹還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack;
				std::cout << " ?瘚? 謝ル: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] - i << ", " << BlackLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 20) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 20))
						{
							if (Board[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								Board[BlackLocation[0] - i][BlackLocation[1] - i] = 4;
							}
						}
					}
				}
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << 20 - StartY << "廓簞 螃艇薹 嬴楚 渠陝摹還曖 翱樓脹 寥給 偃熱: " << MaxWhite;
				std::cout << " 寥給 謝ル: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] - i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 20) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 20))
						{
							if (Board[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								Board[WhiteLocation[0] - i][WhiteLocation[1] - i] = 4;
							}
						}
					}
				}
			}
			
			else
			{
				std::cout << 20 - StartY << "廓簞 螃艇薹 嬴楚 渠陝摹還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack;
				std::cout << " ?瘚? 謝ル: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] - i << ", " << BlackLocation[1] - i << ")";
				}
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 20) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 20))
						{
							if (Board[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								Board[BlackLocation[0] - i][BlackLocation[1] - i] = 4;
							}
						}
					}
				}
				std::cout << 20 - StartY << "廓簞 螃艇薹 嬴楚 渠陝摹還曖 翱樓脹 寥給 偃熱: " << MaxWhite;
				std::cout << " 寥給 謝ル: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] - i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "\n";
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 20) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 20))
						{
							if (Board[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								Board[WhiteLocation[0] - i][WhiteLocation[1] - i] = 4;
							}
						}
					}
				}
			}
		}
		x = 0;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		--StartY;
	}
}

void MaxRDiagStone2(int Board[20][20])
{
	int x = 0, y = 0;
	int StartX = 1;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };
	while (StartX < 20)
	{
		x = StartX;
		while (x < 20)
		{
			CountStone(Board, &x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, FALSE, TRUE);
			++x;
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				std::cout << 20 + StartX << "廓簞 螃艇薹 嬴楚 渠陝摹還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack;
				std::cout << " ?瘚? 謝ル: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] - i << ", " << BlackLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 20) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 20))
						{
							if (Board[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								Board[BlackLocation[0] - i][BlackLocation[1] - i] = 4;
							}
						}
					}
				}
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << 20 + StartX << "廓簞 螃艇薹 嬴楚 渠陝摹還曖 翱樓脹 寥給 偃熱: " << MaxWhite;
				std::cout << " 寥給 謝ル: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] - i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 20) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 20))
						{
							if (Board[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								Board[WhiteLocation[0] - i][WhiteLocation[1] - i] = 4;
							}
						}
					}
				}
			}
			else
			{
				std::cout << 20 + StartX << "廓簞 螃艇薹 嬴楚 渠陝摹還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack;
				std::cout << " ?瘚? 謝ル: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] - i << ", " << BlackLocation[1] - i << ")";
				}
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 20) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 20))
						{
							if (Board[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								Board[BlackLocation[0] - i][BlackLocation[1] - i] = 4;
							}
						}
					}
				}
				std::cout << 20 + StartX << "廓簞 螃艇薹 嬴楚 渠陝摹還曖 翱樓脹 寥給 偃熱: " << MaxWhite;
				std::cout << " 寥給 謝ル: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] - i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "\n";
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 20) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 20))
						{
							if (Board[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								Board[WhiteLocation[0] - i][WhiteLocation[1] - i] = 4;
							}
						}
					}
				}
			}
		}

		y = 0;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		++StartX;

	}
}

void MaxLDiagStone(int Board[20][20])
{
	int x = 0, y = 0;
	int StartX = 0;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (StartX < 20)
	{
		x = StartX;
		while (x >= 0)
		{
			CountStone(Board, &x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, TRUE, TRUE);
			--x;
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				std::cout << StartX + 1 << "廓簞 豭薹 嬴楚 渠陝摹還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack;
				std::cout << " ?瘚? 謝ル: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] + i << ", " << BlackLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 20) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 20))
						{
							if (Board[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								Board[BlackLocation[0] + i][BlackLocation[1] - i] = 4;
							}
						}
					}
				}
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << StartX + 1 << "廓簞 豭薹 嬴楚 渠陝摹還曖 翱樓脹 寥給 偃熱: " << MaxWhite;
				std::cout << " 寥給 謝ル: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] + i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 20) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 20))
						{
							if (Board[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								Board[WhiteLocation[0] + i][WhiteLocation[1] - i] = 4;
							}
						}
					}
				}
			}
			else
			{
				std::cout << StartX + 1 << "廓簞 豭薹 嬴楚 渠陝摹還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack;
				std::cout << " ?瘚? 謝ル: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] + i << ", " << BlackLocation[1] - i << ")";
				}
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 20) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 20))
						{
							if (Board[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								Board[BlackLocation[0] + i][BlackLocation[1] - i] = 4;
							}
						}
					}
				}
				std::cout << StartX + 1 << "廓簞 豭薹 嬴楚 渠陝摹還曖 翱樓脹 寥給 偃熱: " << MaxWhite;
				std::cout << " 寥給 謝ル: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] + i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "\n";
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 20) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 20))
						{
							if (Board[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								Board[WhiteLocation[0] + i][WhiteLocation[1] - i] = 4;
							}
						}
					}
				}
			}
		}

		y = 0;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		++StartX;
	}
}

void MaxLDiagStone2(int Board[20][20])
{
	int x = 19, y = 0;
	int StartY = 1;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (StartY < 20)
	{
		y = StartY;
		while (y < 20)
		{
			CountStone(Board, &x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, TRUE, TRUE);
			--x;
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				std::cout << 20 + StartY << "廓簞 豭薹 嬴楚 渠陝摹還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack;
				std::cout << " ?瘚? 謝ル: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] + i << ", " << BlackLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 20) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 20))
						{
							if (Board[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								Board[BlackLocation[0] + i][BlackLocation[1] - i] = 4;
							}
						}
					}
				}
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << 20 + StartY << "廓簞 豭薹 嬴楚 渠陝摹還曖 翱樓脹 寥給 偃熱: " << MaxWhite;
				std::cout << " 寥給 謝ル: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] + i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 20) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 20))
						{
							if (Board[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								Board[WhiteLocation[0] + i][WhiteLocation[1] - i] = 4;
							}
						}
					}
				}
			}
			else
			{
				std::cout << 20 + StartY << "廓簞 豭薹 嬴楚 渠陝摹還曖 翱樓脹 ?瘚? 偃熱: " << MaxBlack;
				std::cout << " ?瘚? 謝ル: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] + i << ", " << BlackLocation[1] - i << ")";
				}
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 20) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 20))
						{
							if (Board[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								Board[BlackLocation[0] + i][BlackLocation[1] - i] = 4;
							}
						}
					}
				}
				std::cout << 20 + StartY << "廓簞 豭薹 嬴楚 渠陝摹還曖 翱樓脹 寥給 偃熱: " << MaxWhite;
				std::cout << " 寥給 謝ル: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] + i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "\n";
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 20) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 20))
						{
							if (Board[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								Board[WhiteLocation[0] + i][WhiteLocation[1] - i] = 4;
							}
						}
					}
				}
			}
		}

		x = 19;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		++StartY;
	}
}

void SetBoard(int Board[20][20])
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Board[i][j] == 4)
				Board[i][j] = 0;
		}
	}
}

int main()
{
	int n = 0, x, y;
	int Wn = 0, Bn = 0;
	int Board[20][20] = { 0 };
	int command;
	char commandC;
	char inputString[20];

	Stack stack;
	Stack stackreturn;

	InitStack(&stack);
	InitStack(&stackreturn);

	std::ifstream inFile("螃跡.txt");

	while (!inFile.eof())
	{
		inFile.getline(inputString, 20);
		if (inputString[0] == '0')
		{
			while (1)
			{
				if (!IsEmpty(&stackreturn))
				{
					Delete(&stackreturn);
				}

				else
					break;
			}

			x = ((int)inputString[2] - 48) * 10 + ((int)inputString[3] - 48);
			y = ((int)inputString[5] - 48) * 10 + ((int)inputString[6] - 48);

			Push(&stack, x, y);
			Board[x][y] = n % 2 + 1;
			++n;
		}
		else if (inputString[0] == '1')
		{
			Pop(&stack, &stackreturn, Board);
			--n;
		}
		else if (inputString[0] == '2')
		{
			commandR(&stack, &stackreturn, Board, n);

			++n;
		}
	}
	inFile.close();

	for (int i = 0; i < n; ++i)
	{
		if (i % 2 == 1)
			++Wn;
		else
			++Bn;
	}


	std::ofstream outFile("螃跡.txt", std::ios::app);

	while (1)
	{
		system("cls");

		movetoxy(0, 26);
		std::cout << "\n\n";
		MaxXStone(Board);
		std::cout << "=============================================================================================\n\n";
		MaxYStone(Board);
		std::cout << "=============================================================================================\n\n";
		MaxRDiagStone(Board);
		std::cout << "\n\n";
		MaxRDiagStone2(Board);
		std::cout << "=============================================================================================\n\n";
		MaxLDiagStone(Board);
		std::cout << "\n\n";
		MaxLDiagStone2(Board);
		movetoxy(0, 0);
		DrawBoard(Board);

		movetoxy(1, 22);
		std::cout << "                                                                                      ";
		movetoxy(1, 23);
		std::cout << "                                                                                      ";
		movetoxy(1, 21);

		std::cout << "?繺? 偃熱: " << Wn << " " << "?瘚? 偃熱: " << Bn << std::endl;
		std::cout << "貲滄擊 殮溘ж衛溥賊 1擊 揚楝輿撮蹂: ";
		std::cin >> command;

		if (command == 1)
		{
			std::cout << "鼠腦晦蒂 ж衛溥賊 U, 鼠腦晦曖 鼠腦晦蒂 ж衛溥賊 R擊 揚楝輿撮蹂:";
			std::cin >> commandC;

			switch (commandC)
			{
			case 'U':
				if (!IsEmpty(&stack))
				{
					Pop(&stack, &stackreturn, Board);

					if (n % 2 == 1)
						--Bn;
					else
						--Wn;


					--n;

					outFile << "1" << std::endl;

					movetoxy(0, 0);
					SetBoard(Board);

				}
				break;

			case 'R':
				if (!IsEmpty(&stackreturn))
				{
					commandR(&stack, &stackreturn, Board, n);

					if (n % 2 == 1)
						++Wn;

					else
						++Bn;
					++n;

					outFile << "2" << std::endl;

					movetoxy(0, 0);
					SetBoard(Board);
				}
			}
		}

		else
		{
			while (1)
			{
				if (!IsEmpty(&stackreturn))
				{
					Delete(&stackreturn);
				}

				else
					break;
			}

			if (IsEmpty)
				std::cout << "謝ル蒂 殮溘п輿撮蹂:                                       ";
			movetoxy(21, 23);
			std::cin >> x >> y;
			if (!std::cin)
			{
				std::cout << "澀跤脹 殮溘殮棲棻\n";
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				continue;
			}

			if (x >= 0 && x < 20 && y >= 0 && y < 20)
			{
				movetoxy(1, 25);
				std::cout << "                                          ";

				if (Board[x][y] == 0 || Board[x][y] == 4)
				{
					Push(&stack, x, y);

					if (n % 2 == 0)
					{
						movetoxy(x * 2, y);
						std::cout << "??";
						++Bn;
						Board[x][y] = 1;
					}
					else
					{
						movetoxy(x * 2, y);
						std::cout << "寥";
						++Wn;
						Board[x][y] = 2;
					}
					SetBoard(Board);
				}
				else
					continue;
				++n;


				outFile << "0 " << x / 10 << x % 10 << " " << y / 10 << y % 10 << std::endl;

			}
		}

	}

	outFile.close();

}