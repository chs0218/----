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
			std::cout << "┌";
		else if (i == Width - 1)
			std::cout << "─┐";
		else
			std::cout << "─┬";
	}
	std::cout << "\n";

	for (int i = 0; i < Height - 2; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			if (j == 0)
				std::cout << "├";
			else if (j == Width - 1)
				std::cout << "─┤";
			else
				std::cout << "─├";
		}
		std::cout << "\n";
	}

	for (int i = 0; i < Width; ++i)
	{
		if (i == 0)
			std::cout << "└";
		else if (i == Width - 1)
			std::cout << "─┘";
		else
			std::cout << "─┴";
	}
	std::cout << "\n";

	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			if (Board[x][y] == 1)
			{
				movetoxy(x * 2, y);
				std::cout << "흑";
			}
			else if (Board[x][y] == 2)
			{
				movetoxy(x * 2, y);
				std::cout << "백";
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
			++*Black;
			restart[0] = *x;
			restart[1] = *y;
			*cs = 3;
			break;
		case 1:
			++*Black;
			break;

		case 2:
			++*White;
			if (*Black > *MaxBlack)
			{
				BlackLocation[0] = *x;
				BlackLocation[1] = *y;
				*MaxBlack = *Black;
			}
			*cs = 2;
			break;
		}
		break;
	case 2:
		switch (Board[*x][*y])
		{
		case 0:
			++*White;
			restart[0] = *x;
			restart[1] = *y;
			*cs = 4;
			break;
		case 1:
			++*Black;
			if (*White > *MaxWhite)
			{
				WhiteLocation[0] = *x;
				WhiteLocation[1] = *y;
				*MaxWhite = *White;
				*White = 0;
			}
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
			++*White;
			if (*Black > *MaxBlack)
			{
				BlackLocation[0] = *x;
				BlackLocation[1] = *y;
				*MaxBlack = *Black;
				*Black = 0;
			}
			*cs = 2;
			break;
		}
		break;
	case 4:
		switch (Board[*x][*y])
		{
		case 0:
			if (*White > *MaxWhite)
			{
				WhiteLocation[0] = *x;
				WhiteLocation[1] = *y;
				*MaxWhite = *White;
				*White = 0;
			}
			*x = restart[0];
			*y = restart[1];
			*cs = 0;
			break;
		case 1:
			++*Black;
			if (*White > *MaxWhite)
			{
				WhiteLocation[0] = *x;
				WhiteLocation[1] = *y;
				*MaxWhite = *White;
				*White = 0;
			}
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
				std::cout << y + 1 << "번째 가로줄의 연속된 흑돌 개수: " << MaxBlack << " 연속된 흑돌 좌표:";
				for (int j = BlackLocation[0] -  MaxBlack; j < BlackLocation[0]; ++j)
				{
					std::cout << "(" << j << ", " << y << ")";
				}
				std::cout << "                                                                                          \n";
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << y + 1 << "번째 가로줄의 연속된 백돌 개수: " << MaxWhite << " 연속된 백돌 좌표:";
				for (int j = WhiteLocation[0] - MaxWhite; j < WhiteLocation[0]; ++j)
				{
					std::cout << "(" << j << ", " << y << ")";
				}
				std::cout << "                                                                                          \n";
			}
			else
			{
				std::cout << y + 1 << "번째 가로줄의 연속된 흑돌 개수: " << MaxBlack << " 연속된 흑돌 좌표:";
				for (int j = BlackLocation[0] - MaxBlack; j < BlackLocation[0]; ++j)
				{
					std::cout << "(" << j << ", " << y << ")";
				}
				std::cout << y + 1 << "번째 가로줄의 연속된 백돌 개수: " << MaxWhite << " 연속된 백돌 좌표:";
				for (int j = WhiteLocation[0] - MaxWhite; j < WhiteLocation[0]; ++j)
				{
					std::cout << "(" << j << ", " << y << ")";
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
				std::cout << x + 1 << "번째 세로줄의 연속된 흑돌 개수: " << MaxBlack << " 연속된 흑돌 좌표:";
				for (int j = BlackLocation[1] - MaxBlack; j < BlackLocation[1]; ++j)
				{
					std::cout << "(" << x << ", " << j << ")";
				}
				std::cout << "                                                                                          \n";
				
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << x + 1 << "번째 세로줄의 연속된 백돌 개수: " << MaxWhite << " 연속된 백돌 좌표:";
				for (int j = WhiteLocation[1] - MaxWhite; j < WhiteLocation[1]; ++j)
				{
					std::cout << "(" << x << ", " << j << ")";
				}
				std::cout << "                                                                                          \n";
				
			}
			else
			{
				std::cout << x + 1 << "번째 세로줄의 연속된 흑돌 개수: " << MaxBlack << " 연속된 흑돌 좌표:";
				for (int j = BlackLocation[1] - MaxBlack; j < BlackLocation[1]; ++j)
				{
					std::cout << "(" << x << ", " << j << ")";
				}
				
				std::cout << x + 1 << "번째 세로줄의 연속된 백돌 개수: " << MaxWhite << " 연속된 백돌 좌표:";
				for (int j = WhiteLocation[1] - MaxWhite; j < WhiteLocation[1]; ++j)
				{
					std::cout << "(" << x << ", " << j << ")";
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
				std::cout << 20 - StartY << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
				std::cout << " 흑돌 좌표: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] - i << ", " << BlackLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << 20 - StartY << "번째 오른쪽 아래 대삭선줄의 연속된 백돌 개수: " << MaxWhite;
				std::cout << " 백돌 좌표: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] - i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
			}
			else
			{
				std::cout << 20 - StartY << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
				std::cout << " 흑돌 좌표: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] - i << ", " << BlackLocation[1] - i << ")";
				}
		
				std::cout << 20 - StartY << "번째 오른쪽 아래 대각선줄의 연속된 백돌 개수: " << MaxWhite;
				std::cout << " 백돌 좌표: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] - i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "\n";
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
				std::cout << 20 + StartX << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
				std::cout << " 흑돌 좌표: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] - i << ", " << BlackLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << 20 + StartX << "번째 오른쪽 아래 대삭선줄의 연속된 백돌 개수: " << MaxWhite;
				std::cout << " 백돌 좌표: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] - i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
			}
			else
			{
				std::cout << 20 + StartX << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
				std::cout << " 흑돌 좌표: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] - i << ", " << BlackLocation[1] - i << ")";
				}

				std::cout << 20 + StartX << "번째 오른쪽 아래 대각선줄의 연속된 백돌 개수: " << MaxWhite;
				std::cout << " 백돌 좌표: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] - i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "\n";
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
				std::cout << StartX  + 1 << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
				std::cout << " 흑돌 좌표: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] + i << ", " << BlackLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << StartX + 1<< "번째 오른쪽 아래 대삭선줄의 연속된 백돌 개수: " << MaxWhite;
				std::cout << " 백돌 좌표: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] + i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
			}
			else
			{
				std::cout << StartX + 1<< "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
				std::cout << " 흑돌 좌표: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] + i << ", " << BlackLocation[1] - i << ")";
				}

				std::cout << StartX + 1<< "번째 오른쪽 아래 대각선줄의 연속된 백돌 개수: " << MaxWhite;
				std::cout << " 백돌 좌표: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] + i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "\n";
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
				std::cout << 20 + StartY << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
				std::cout << " 흑돌 좌표: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] + i << ", " << BlackLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
			}
			else if (MaxBlack < MaxWhite)
			{
				std::cout << 20 + StartY << "번째 오른쪽 아래 대삭선줄의 연속된 백돌 개수: " << MaxWhite;
				std::cout << " 백돌 좌표: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] + i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "                                                                                          \n";
			}
			else
			{
				std::cout << 20 + StartY << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
				std::cout << " 흑돌 좌표: ";
				for (int i = MaxBlack; i > 0; --i)
				{
					std::cout << "(" << BlackLocation[0] + i << ", " << BlackLocation[1] - i << ")";
				}

				std::cout << 20 + StartY << "번째 오른쪽 아래 대각선줄의 연속된 백돌 개수: " << MaxWhite;
				std::cout << " 백돌 좌표: ";
				for (int i = MaxWhite; i > 0; --i)
				{
					std::cout << "(" << WhiteLocation[0] + i << ", " << WhiteLocation[1] - i << ")";
				}
				std::cout << "\n";
			}
		}

		x = 19;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		++StartY;
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

	std::ifstream inFile("오목.txt");

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


	std::ofstream outFile("오목.txt", std::ios::app);

	while (1)
	{
		system("cls");

		movetoxy(0, 26);
		std::cout << "\n\n";
		MaxXStone(Board);
		std::cout << "=============================================================================================\n\n";
		MaxYStone(Board);
		std::cout << "\n\n";
		MaxRDiagStone(Board);
		std::cout << "\n\n";
		MaxRDiagStone2(Board);
		std::cout << "\n\n";
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

		std::cout << "흰돌 개수: " << Wn << " " << "흑돌 개수: " << Bn << std::endl;
		std::cout << "명령을 입력하시려면 1을 눌러주세요: ";
		std::cin >> command;

		if (command == 1)
		{
			std::cout << "무르기를 하시려면 U, 무르기의 무르기를 하시려면 R을 눌러주세요:";
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
					DrawBoard(Board);

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
					DrawBoard(Board);
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
				std::cout << "좌표를 입력해주세요:                                       ";
			movetoxy(21, 23);
			std::cin >> x >> y;
			if (!std::cin)
			{
				std::cout << "잘못된 입력입니다\n";
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				continue;
			}

			if (x >= 0 && x < 20 && y >= 0 && y < 20)
			{
				Push(&stack, x, y);
				movetoxy(1, 25);
				std::cout << "                                          ";

				if (Board[x][y] == 0)
				{
					if (n % 2 == 0)
					{
						movetoxy(x * 2, y);
						std::cout << "흑";
						++Bn;
						Board[x][y] = 1;
					}
					else
					{
						movetoxy(x * 2, y);
						std::cout << "백";
						++Wn;
						Board[x][y] = 2;
					}
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