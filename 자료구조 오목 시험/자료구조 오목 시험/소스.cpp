#include <iostream>
#include <Windows.h>
#define Width 20
#define Height 20

using namespace std;

void movetoxy(int col, int row)

{

	COORD position = { col, row };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void DrawBoard()
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
			cout << 20-StartY << "번째 오른쪽 아래 대삭선줄의 연속된 백돌 개수: " << MaxWhite;

			cout << "                                                                                          \n";
		}
		else
		{
			cout << 20-StartY << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << " ";
			cout << 20-StartY << "번째 오른쪽 아래 대각선줄의 연속된 백돌 개수: " << MaxWhite;
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
			cout << 20+StartX << "번째 오른쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
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
			cout << StartX + 1<< "번째 왼쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << "                                                                                          \n";
		}
		else if (MaxBlack < MaxWhite)
		{
			cout << StartX + 1<< "번째 왼쪽 아래 대삭선줄의 연속된 백돌 개수: " << MaxWhite;

			cout << "                                                                                          \n";
		}
		else
		{
			cout << StartX + 1<< "번째 왼쪽 아래 대각선줄의 연속된 흑돌 개수: " << MaxBlack;
			cout << " ";
			cout << StartX + 1  << "번째 왼쪽 아래 대각선줄의 연속된 백돌 개수: " << MaxWhite;
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

	DrawBoard();

	while (1)
	{
		movetoxy(1, 21);
		cout << "흰돌 개수: " << Wn << " " << "흑돌 개수: " << Bn << endl;
		cout << "\n좌표를 입력해주세요:                                       ";
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
		}

		movetoxy(0, 26);
		HowManyX(Board);
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
		MaxLDiagStone2(Board);
	}
}