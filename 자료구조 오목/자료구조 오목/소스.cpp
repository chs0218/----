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

int HowManyWhiteX(int Board[20][20], int y)
{
	int n = 0;
	for (int i = 0; i < 20; ++i)
	{
		if (Board[i][y] == 2)
			++n;
	}
	return n;
}

int HowManyWhiteY(int Board[20][20], int x)
{
	int n = 0;
	for (int i = 0; i < 20; ++i)
	{
		if (Board[x][i] == 2)
			++n;
	}
	return n;
}

int HowManyBlackX(int Board[20][20], int y)
{
	int n = 0;
	for (int i = 0; i < 20; ++i)
	{
		if (Board[i][y] == 1)
			++n;
	}
	return n;
}

int HowManyBlackY(int Board[20][20], int x)
{
	int n = 0;
	for (int i = 0; i < 20; ++i)
	{
		if (Board[x][i] == 1)
			++n;
	}
	return n;
}

void MaxXStone(int Board[20][20], int y)
{
	int White = 0, Black = 0;
	int MaxWhite = 0, MaxBlack = 0;
	int LocationWhite = 0, LocationBlack = 0;
	for (int i = 0; i < 20; ++i)
	{
		if (White == 0 && Black == 0)
		{
			if (Board[i][y] == 1)
				++Black;

			else if (Board[i][y] == 2)
				++White;
		}

		else
		{
			if (Board[i][y] == 1 && Black > 0)
				++Black;
			else if (Board[i][y] == 2 && White > 0)
				++White;
			else if (Board[i][y] != 2 && White > 0)
			{
				if (White > MaxWhite)
				{
					LocationWhite = i - White - 1;
					MaxWhite = White;
				}
				White = 0;
				if (Board[i][y] == 1)
					Black = 1;
			}
			else if (Board[i][y] != 1 && Black > 0)
			{
				if (Black > MaxBlack)
				{
					LocationBlack = i - Black - 1;
					MaxBlack = Black;
				}
				Black = 0;
				if (Board[i][y] == 2)
					White = 1;
			}

		}
	}

	if (MaxWhite > MaxBlack)
	{
		cout << y + 1 << "번째 가로줄 연속된 흰돌 개수: " << MaxWhite << " 연속되는 흰돌 좌표: ";
		for (int i = LocationWhite; i < LocationWhite + MaxWhite; ++i)
			cout <<"(" << i + 1 << ", " << y << ") ";
		cout << "                                                                                ";
	}
	else if (MaxBlack > MaxWhite)
	{
		cout << y + 1 << "번째 가로줄 연속된 흑돌 개수: " << MaxBlack << " 연속되는 검은돌 좌표: ";
		for (int i = LocationBlack; i < LocationBlack + MaxBlack; ++i)
			cout << "(" << i + 1 << ", " << y << ") ";
		cout << "                                                                                ";
	}
	else
	{
		cout << y + 1 << "번째 가로줄 연속된 흰돌 개수: " << MaxWhite << " " << y + 1 << "번째 가로줄 연속된 흑돌 개수: " << MaxBlack << " 연속되는 흰돌 좌표: ";
		for (int i = LocationWhite; i < LocationWhite + MaxWhite; ++i)
			cout << "(" << i + 1 << ", " << y << ") ";
		cout << " 연속되는 검은돌 좌표: ";
		for (int i = LocationBlack; i < LocationBlack + MaxBlack; ++i)
			cout << "(" << i + 1 << ", " << y << ") ";
		cout << "                                                                                ";
	}

}

void MaxYStone(int Board[20][20], int x)
{
	int White = 0, Black = 0;
	int MaxWhite = 0, MaxBlack = 0;
	for (int i = 0; i < 20; ++i)
	{
		if (White == 0 && Black == 0)
		{
			if (Board[x][i] == 1)
				++Black;

			else if (Board[x][i] == 2)
				++White;
		}

		else
		{
			if (Board[x][i] == 1 && Black > 0)
				++Black;
			else if (Board[x][i] == 2 && White > 0)
				++White;
			else if (Board[x][i] != 2 && White > 0)
			{
				if (White > MaxWhite)
					MaxWhite = White;
				White = 0;
				if (Board[x][i] == 1)
					Black = 1;
			}
			else if (Board[x][i] != 1 && Black > 0)
			{
				if (Black > MaxBlack)
					MaxBlack = Black;
				Black = 0;
				if (Board[x][i] == 2)
					White = 1;
			}

		}
	}

	if (MaxWhite > MaxBlack)
		cout << x + 1 << "번째 세로줄 연속된 흰돌 개수: " << MaxWhite << "                                                  " << endl;
	else if (MaxBlack > MaxWhite)
		cout << x + 1 << "번째 세로줄 연속된 흑돌 개수: " << MaxBlack << "                                                  " << endl;
	else
		cout << x + 1 << "번째 세로줄 연속된 흰돌 개수: " << MaxWhite << " " << x + 1 << "번째 세로줄 연속된 흑돌 개수: " << MaxBlack << endl;

}

void CountDiagonalVertical(int Board[20][20], int n, int i)
{
	int White = 0, Black = 0;
	int MaxWhite = 0, MaxBlack = 0;
	int x = 0;
	while (n != 20)
	{
		if (White == 0 && Black == 0)
		{
			if (Board[x][n] == 1)
				++Black;

			else if (Board[x][n] == 2)
				++White;
		}

		else
		{
			if (Board[x][n] == 1 && Black > 0)
				++Black;
			else if (Board[x][n] == 2 && White > 0)
				++White;
			else if (Board[x][n] != 2 && White > 0)
			{
				if (White > MaxWhite)
					MaxWhite = White;
				White = 0;
				if (Board[x][n] == 1)
					Black = 1;
			}
			else if (Board[x][n] != 1 && Black > 0)
			{
				if (Black > MaxBlack)
					MaxBlack = Black;
				Black = 0;
				if (Board[x][n] == 2)
					White = 1;
			}
		}

		++n;
		++x;
	}

	if (MaxWhite > MaxBlack)
		cout << i << "번째 오른쪽 아래로 향하는 대각선줄 연속된 흰돌 개수: " << MaxWhite << "                                                                        " << endl;
	else if (MaxBlack > MaxWhite)
		cout << i << "번째 오른쪽 아래로 향하는 대각선줄 연속된 흑돌 개수: " << MaxBlack << "                                                                        " << endl;
	else
		cout << i << "번째 오른쪽 아래로 향하는 대각선줄 연속된 흰돌 개수: " << MaxWhite << " " << i << "번째 오른쪽 아래로 향하는 대각선줄 연속된 흑돌 개수: " << MaxBlack << endl;

}


void CountDiagonalHorizontal(int Board[20][20], int n, int i)
{
	int White = 0, Black = 0;
	int MaxWhite = 0, MaxBlack = 0;
	int y = 0;
	while (n > 0)
	{
		if (White == 0 && Black == 0)
		{
			if (Board[n][y] == 1)
				++Black;

			else if (Board[n][y] == 2)
				++White;
		}

		else
		{
			if (Board[n][y] == 1 && Black > 0)
				++Black;
			else if (Board[n][y] == 2 && White > 0)
				++White;
			else if (Board[n][y] != 2 && White > 0)
			{
				if (White > MaxWhite)
					MaxWhite = White;
				White = 0;
				if (Board[n][y] == 1)
					Black = 1;
			}
			else if (Board[n][y] != 1 && Black > 0)
			{
				if (Black > MaxBlack)
					MaxBlack = Black;
				Black = 0;
				if (Board[n][y] == 2)
					White = 1;
			}
		}

		--n;
		++y;
	}

	if (MaxWhite > MaxBlack)
		cout << i << "번째 왼쪽 아래로 향하는 대각선줄 연속된 흰돌 개수: " << MaxWhite << "                                                                        " << endl;
	else if (MaxBlack > MaxWhite)
		cout << i << "번째 왼쪽 아래로 향하는 대각선줄 연속된 흑돌 개수: " << MaxBlack << "                                                                        " << endl;
	else
		cout << i << "번째 왼쪽 아래로 향하는 대각선줄 연속된 흰돌 개수: " << MaxWhite << " " << i << "번째 왼쪽 아래로 향하는 대각선줄 연속된 흑돌 개수: " << MaxBlack << endl;

}

int main()
{
	int n = 0, x, y;
	int Wn = 0, Bn = 0;
	int Board[20][20] = { 0 };

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

		if(x >= 0 && x < 20 && y >= 0 && y < 20)
		{
			movetoxy(1, 25);
			cout << "                                          ";

			if (Board[x][y] == 0)
			{
				if (n % 2 == 0)
				{
					movetoxy(x * 2, y);
					cout << "흑";
					++Bn;
					Board[x][y] = 1;
				}
				else
				{
					movetoxy(x * 2, y);
					cout << "백";
					++Wn;
					Board[x][y] = 2;
				}
			}
			else
				continue;
			++n;
		}

		movetoxy(0, 25);
		/*for (int i = 1; i < 21; ++i)
		{
			cout << i << "번째 가로줄(흰돌의 개수, 흑돌의 개수): " << "(" << HowManyWhiteX(Board, i - 1) << ", " << HowManyBlackX(Board, i - 1) << ")" << endl;
			cout << i << "번째 세로줄(흰돌의 개수, 흑돌의 개수): " << "(" << HowManyWhiteY(Board, i - 1) << ", " << HowManyBlackY(Board, i - 1) << ")" << endl;
		}
		cout << endl;*/
		for (int i = 0; i < 20; ++i)
		{
			MaxXStone(Board, i);
			cout << endl;
			//MaxYStone(Board, i);
		}
		/*cout << endl;
		for (int i = 19; i >= 0; --i)
		{
			CountDiagonalVertical(Board, i, 20 - i);
		}
		for (int i = 1; i < 20; ++i)
		{
			CountDiagonalHorizontal(Board, i, i);
		}*/
	}

}