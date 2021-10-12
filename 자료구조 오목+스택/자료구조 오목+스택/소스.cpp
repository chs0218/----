#include <iostream>
#include <fstream>
#include <Windows.h>
#define Width 20
#define Height 20


using namespace std;

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

void DrawBoard(int Board[22][22])
{
	for (int i = 0; i < Width; ++i)
	{
		if (i == 0)
			cout << "┌";
		else if (i == Width - 1)
			cout << "─┐";
		else
			cout << "─┬";
	}
	cout << "\n";

	for (int i = 0; i < Height - 2; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			if (j == 0)
				cout << "├";
			else if (j == Width - 1)
				cout << "─┤";
			else
				cout << "─├";
		}
		cout << "\n";
	}

	for (int i = 0; i < Width; ++i)
	{
		if (i == 0)
			cout << "└";
		else if (i == Width - 1)
			cout << "─┘";
		else
			cout << "─┴";
	}
	cout << "\n";

	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			if (Board[x + 1][y + 1] == 1)
			{
				movetoxy(x * 2, y);
				cout << "흑";
			}
			else if (Board[x + 1][y + 1] == 2)
			{
				movetoxy(x * 2, y);
				cout << "백";
			}
		}
	}
}

int commandR(Stack* stack, Stack* stackreturn, int Board[22][22], int n)
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
		Board[x + 1][y + 1] = 2;
	else
		Board[x + 1][y + 1] = 1;


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

int Pop(Stack* stack, Stack* stackreturn, int Board[22][22])
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
	Board[x + 1][y + 1] = 0;
	
	stack->top = now->next;


	delete now;
	return 1;
}

void HowManyX(int Board[22][22])
{
	int y = 0;
	int Black = 0, White = 0;
	while (y != 20)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (Board[i + 1][y + 1] == 1)
				++Black;
			else if (Board[i + 1][y + 1] == 2)
				++White;
		}
		cout << y + 1 << "번째 가로줄의 (검은돌개수, 흰돌개수): (" << Black << ", " << White << ")\n";
		++y;
		Black = 0, White = 0;
	}
}

void HowManyY(int Board[22][22])
{
	int x = 0;
	int Black = 0, White = 0;
	while (x != 20)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (Board[x + 1][i + 1] == 1)
				++Black;
			else if (Board[x + 1][i + 1] == 2)
				++White;
		}
		cout << x + 1 << "번째 세로줄의 (검은돌개수, 흰돌개수): (" << Black << ", " << White << ")\n";
		++x;
		Black = 0, White = 0;
	}
}

void MaxXStone(int Board[22][22])
{
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0, y = 0;
	int BlackLocation = 0, WhiteLocation = 0;
	while (y < 21)
	{
		for (int i = 0; i < 21; ++i)
		{
			if (Black == 0 && White == 0)
			{
				if (Board[i + 1][y + 1] == 1)
					++Black;
				else if (Board[i + 1][y + 1] == 2)
					++White;
			}
			else
			{
				if (Board[i + 1][y + 1] == 1 && Black > 0)
					++Black;
				else if (Board[i + 1][y + 1] == 2 && White > 0)
					++White;
				else if (Board[i + 1][y + 1] != 1 && Black > 0)
				{
					if (MaxBlack < Black)
					{
						MaxBlack = Black;
						BlackLocation = i - Black;
					}
					Black = 0;
					if (Board[i + 1][y + 1] == 2)
						White = 1;
				}
				else if (Board[i + 1][y + 1] != 2 && White > 0)
				{
					if (MaxWhite < White)
					{
						MaxWhite = White;
						WhiteLocation = i - White;
					}
					White = 0;
					if (Board[i + 1][y + 1] == 1)
						Black = 1;
				}
			}
		}
		if (y < 20)
		{
			if (MaxBlack > MaxWhite)
			{
				cout << y + 1 << "번째 가로줄의 연속된 흑돌 개수: " << MaxBlack << " 연속된 흑돌 좌표:";
				for (int j = BlackLocation; j < BlackLocation + MaxBlack; ++j)
				{
					cout << "(" << j << ", " << y << ")";
				}
				cout << "                                                                                          \n";
			}
			else if (MaxBlack < MaxWhite)
			{
				cout << y + 1 << "번째 가로줄의 연속된 백돌 개수: " << MaxWhite << " 연속된 백돌 좌표:";
				for (int j = WhiteLocation; j < WhiteLocation + MaxWhite; ++j)
				{
					cout << "(" << j << ", " << y << ")";
				}
				cout << "                                                                                          \n";
			}
			else
			{
				cout << y + 1 << "번째 가로줄의 연속된 흑돌 개수: " << MaxBlack << " 연속된 흑돌 좌표:";
				for (int j = BlackLocation; j < BlackLocation + MaxBlack; ++j)
				{
					cout << "(" << j << ", " << y << ")";
				}
				cout << " ";
				cout << y + 1 << "번째 가로줄의 연속된 백돌 개수: " << MaxWhite << " 연속된 백돌 좌표:";
				for (int j = WhiteLocation; j < WhiteLocation + MaxWhite; ++j)
				{
					cout << "(" << j << ", " << y << ")";
				}
				cout << "\n";
			}
		}
		++y;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		BlackLocation = 0, WhiteLocation = 0;
	}

}

void MaxYStone(int Board[22][22])
{
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0, x = 0;
	int BlackLocation = 0, WhiteLocation = 0;
	while (x < 21)
	{
		for (int i = 0; i < 21; ++i)
		{
			if (Black == 0 && White == 0)
			{
				if (Board[x + 1][i + 1] == 1)
					++Black;
				else if (Board[x + 1][i + 1] == 2)
					++White;
			}
			else
			{
				if (Board[x + 1][i + 1] == 1 && Black > 0)
					++Black;
				else if (Board[x + 1][i + 1] == 2 && White > 0)
					++White;
				else if (Board[x + 1][i + 1] != 1 && Black > 0)
				{
					if (MaxBlack < Black)
					{
						MaxBlack = Black;
						BlackLocation = i - Black;
					}
					Black = 0;
					if (Board[x + 1][i + 1] == 2)
						White = 1;
				}
				else if (Board[x + 1][i + 1] != 2 && White > 0)
				{
					if (MaxWhite < White)
					{
						MaxWhite = White;
						WhiteLocation = i - White;
					}
					White = 0;
					if (Board[x + 1][i + 1] == 1)
						Black = 1;
				}
			}
		}
		if (x < 20)
		{
			if (MaxBlack > MaxWhite)
			{
				cout << x + 1 << "번째 세로줄의 연속된 흑돌 개수: " << MaxBlack << " 연속된 흑돌 좌표:";
				for (int j = BlackLocation; j < BlackLocation + MaxBlack; ++j)
				{
					cout << "(" << x << ", " << j << ")";
				}
				cout << "                                                                                          \n";
			}
			else if (MaxBlack < MaxWhite)
			{
				cout << x + 1 << "번째 세로줄의 연속된 백돌 개수: " << MaxWhite << " 연속된 백돌 좌표:";
				for (int j = WhiteLocation; j < WhiteLocation + MaxWhite; ++j)
				{
					cout << "(" << x << ", " << j << ")";
				}
				cout << "                                                                                          \n";
			}
			else
			{
				cout << x + 1 << "번째 세로줄의 연속된 흑돌 개수: " << MaxBlack << " 연속된 흑돌 좌표:";
				for (int j = BlackLocation; j < BlackLocation + MaxBlack; ++j)
				{
					cout << "(" << x << ", " << j << ")";
				}
				cout << " ";
				cout << x + 1 << "번째 세로줄의 연속된 백돌 개수: " << MaxWhite << " 연속된 백돌 좌표:";
				for (int j = WhiteLocation; j < WhiteLocation + MaxWhite; ++j)
				{
					cout << "(" << x << ", " << j << ")";
				}
				cout << "\n";
			}
		}
		++x;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		BlackLocation = 0, WhiteLocation = 0;
	}
}

void MaxRDiagStone(int Board[22][22])
{
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0, StartY = 19, x = 0, y = 0;
	while (StartY >= 0)
	{
		y = StartY;
		while (y != 21)
		{
			if (Black == 0 && White == 0)
			{
				if (Board[x + 1][y + 1] == 1)
					++Black;
				else if (Board[x + 1][y + 1] == 2)
					++White;
			}
			else
			{
				if (Board[x + 1][y + 1] == 1 && Black > 0)
					++Black;
				else if (Board[x + 1][y + 1] == 2 && White > 0)
					++White;
				else if (Board[x + 1][y + 1] != 1 && Black > 0)
				{
					if (MaxBlack < Black)
					{
						MaxBlack = Black;
					}
					Black = 0;
					if (Board[x + 1][y + 1] == 2)
						White = 1;
				}
				else if (Board[x + 1][y + 1] != 2 && White > 0)
				{
					if (MaxWhite < White)
					{
						MaxWhite = White;
					}
					White = 0;
					if (Board[x + 1][y + 1] == 1)
						Black = 1;
				}
			}
			++y;
			++x;
		}

		if (MaxBlack > MaxWhite)
		{
			cout << 20 - StartY << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << "                                                                                          \n";
		}
		else if (MaxBlack < MaxWhite)
		{
			cout << 20 - StartY << "번째 오른쪽 아래 대삭선줄의 연속된 백돌 개수: " << MaxWhite;

			cout << "                                                                                          \n";
		}
		else
		{
			cout << 20 - StartY << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << " ";
			cout << 20 - StartY << "번째 오른쪽 아래 대각선줄의 연속된 백돌 개수: " << MaxWhite;
			cout << "\n";
		}

		--StartY;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		x = 0;
	}
}


void MaxRDiagStone2(int Board[22][22])
{
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0, StartX = 1, x = 0, y = 0;
	while (StartX < 20)
	{
		x = StartX;
		while (x != 21)
		{
			if (Black == 0 && White == 0)
			{
				if (Board[x + 1][y + 1] == 1)
					++Black;
				else if (Board[x + 1][y + 1] == 2)
					++White;
			}
			else
			{
				if (Board[x + 1][y + 1] == 1 && Black > 0)
					++Black;
				else if (Board[x + 1][y + 1] == 2 && White > 0)
					++White;
				else if (Board[x + 1][y + 1] != 1 && Black > 0)
				{
					if (MaxBlack < Black)
					{
						MaxBlack = Black;
					}
					Black = 0;
					if (Board[x + 1][y + 1] == 2)
						White = 1;
				}
				else if (Board[x + 1][y + 1] != 2 && White > 0)
				{
					if (MaxWhite < White)
					{
						MaxWhite = White;
					}
					White = 0;
					if (Board[x + 1][y + 1] == 1)
						Black = 1;
				}
			}
			++y;
			++x;
		}

		if (MaxBlack > MaxWhite)
		{
			cout << 20 + StartX << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << "                                                                                          \n";
		}
		else if (MaxBlack < MaxWhite)
		{
			cout << 20 + StartX << "번째 오른쪽 아래 대삭선줄의 연속된 백돌 개수: " << MaxWhite;

			cout << "                                                                                          \n";
		}
		else
		{
			cout << 20 + StartX << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << " ";
			cout << 20 + StartX << "번째 오른쪽 아래 대각선줄의 연속된 백돌 개수: " << MaxWhite;
			cout << "\n";
		}

		++StartX;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		y = 0;
	}
}

void MaxLDiagStone(int Board[22][22])
{
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0, StartX = 0, x = 0, y = 0;
	while (StartX < 20)
	{
		x = StartX;
		while (x >= -1)
		{
			if (Black == 0 && White == 0)
			{
				if (Board[x + 1][y + 1] == 1)
					++Black;
				else if (Board[x + 1][y + 1] == 2)
					++White;
			}
			else
			{
				if (Board[x + 1][y + 1] == 1 && Black > 0)
					++Black;
				else if (Board[x + 1][y + 1] == 2 && White > 0)
					++White;
				else if (Board[x + 1][y + 1] != 1 && Black > 0)
				{
					if (MaxBlack < Black)
					{
						MaxBlack = Black;
					}
					Black = 0;
					if (Board[x + 1][y + 1] == 2)
						White = 1;
				}
				else if (Board[x + 1][y + 1] != 2 && White > 0)
				{
					if (MaxWhite < White)
					{
						MaxWhite = White;
					}
					White = 0;
					if (Board[x + 1][y + 1] == 1)
						Black = 1;
				}
			}
			++y;
			--x;
		}

		if (MaxBlack > MaxWhite)
		{
			cout << StartX + 1 << "번째 왼쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << "                                                                                          \n";
		}
		else if (MaxBlack < MaxWhite)
		{
			cout << StartX + 1 << "번째 왼쪽 아래 대삭선줄의 연속된 백돌 개수: " << MaxWhite;

			cout << "                                                                                          \n";
		}
		else
		{
			cout << StartX + 1 << "번째 왼쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << " ";
			cout << StartX + 1 << "번째 왼쪽 아래 대각선줄의 연속된 백돌 개수: " << MaxWhite;
			cout << "\n";
		}

		++StartX;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		y = 0;
	}
}

void MaxLDiagStone2(int Board[22][22])
{
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0, StartY = 1, x = 19, y = 0;
	while (StartY < 20)
	{
		y = StartY;
		while (y != 21)
		{
			if (Black == 0 && White == 0)
			{
				if (Board[x + 1][y + 1] == 1)
					++Black;
				else if (Board[x + 1][y + 1] == 2)
					++White;
			}
			else
			{
				if (Board[x + 1][y + 1] == 1 && Black > 0)
					++Black;
				else if (Board[x + 1][y + 1] == 2 && White > 0)
					++White;
				else if (Board[x + 1][y + 1] != 1 && Black > 0)
				{
					if (MaxBlack < Black)
					{
						MaxBlack = Black;
					}
					Black = 0;
					if (Board[x + 1][y + 1] == 2)
						White = 1;
				}
				else if (Board[x + 1][y + 1] != 2 && White > 0)
				{
					if (MaxWhite < White)
					{
						MaxWhite = White;
					}
					White = 0;
					if (Board[x + 1][y + 1] == 1)
						Black = 1;
				}
			}
			++y;
			--x;
		}

		if (MaxBlack > MaxWhite)
		{
			cout << 20 + StartY << "번째 왼쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << "                                                                                          \n";
		}
		else if (MaxBlack < MaxWhite)
		{
			cout << 20 + StartY << "번째 왼쪽 아래 대삭선줄의 연속된 백돌 개수: " << MaxWhite;

			cout << "                                                                                          \n";
		}
		else
		{
			cout << 20 + StartY << "번째 왼쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << " ";
			cout << 20 + StartY << "번째 왼쪽 아래 대각선줄의 연속된 백돌 개수: " << MaxWhite;
			cout << "\n";
		}

		++StartY;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		x = 19;
	}
}

int main()
{
	int n = 0, x, y;
	int Wn = 0, Bn = 0;
	int Board[22][22] = { 0 };
	int command;
	char commandC;
	char inputString[20];

	Stack stack;
	Stack stackreturn;

	InitStack(&stack);
	InitStack(&stackreturn);

	ifstream inFile("오목.txt");

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
			Board[x + 1][y + 1] = n % 2 + 1;
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

	DrawBoard(Board);

	ofstream outFile("오목.txt", ios::app);

	while (1)
	{
		movetoxy(1, 22);
		cout << "                                                                                      ";
		movetoxy(1, 23);
		cout << "                                                                                      ";
		movetoxy(1, 21);

		cout << "흰돌 개수: " << Wn << " " << "흑돌 개수: " << Bn << endl;
		cout << "명령을 입력하시려면 1을 눌러주세요: ";
		cin >> command;

		if (command == 1)
		{
			cout << "무르기를 하시려면 U, 무르기의 무르기를 하시려면 R을 눌러주세요:";
			cin >> commandC;

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

					outFile << "1" << endl;

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

					outFile << "2" << endl;

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

			if(IsEmpty)
			cout << "좌표를 입력해주세요:                                       ";
			movetoxy(21, 23);
			cin >> x >> y;
			if (!cin)
			{
				cout << "잘못된 입력입니다\n";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				continue;
			}

			if (x >= 0 && x < 20 && y >= 0 && y < 20)
			{
				Push(&stack, x, y);
				movetoxy(1, 25);
				cout << "                                          ";

				if (Board[x + 1][y + 1] == 0)
				{
					if (n % 2 == 0)
					{
						movetoxy(x * 2, y);
						cout << "흑";
						++Bn;
						Board[x + 1][y + 1] = 1;
					}
					else
					{
						movetoxy(x * 2, y);
						cout << "백";
						++Wn;
						Board[x + 1][y + 1] = 2;
					}
				}
				else
					continue;
				++n;


				outFile << "0 " << x / 10 << x % 10 << " " << y / 10 << y % 10 << endl;

			}
		}
		movetoxy(0, 26);
		/*HowManyX(Board);
		cout << "\n\n";
		HowManyY(Board);
		cout << "\n\n";
		MaxXStone(Board);
		cout << "\n\n";
		MaxYStone(Board);
		cout << "\n\n";
		MaxRDiagStone(Board);
		cout << "\n\n";
		MaxRDiagStone2(Board);
		cout << "\n\n";
		MaxLDiagStone(Board);
		cout << "\n\n";
		MaxLDiagStone2(Board);*/
	}

	outFile.close();

}