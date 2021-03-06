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

	for (int i = 0; i < Height-2; ++i)
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

		if (x >= 0 && x < 20 && y >= 0 && y < 20)
		{
			if (Board[x][y] == 0)
			{
				if (n % 2 == 0)
				{
					movetoxy(x * 2, y);
					cout << "흑";
					++Bn;
				}
				else
				{
					movetoxy(x * 2, y);
					cout << "백";
					++Wn;
				}
				Board[x][y] = 1;
			}
			else
				continue;
			++n;
		}
		else
		{
			cout << endl << "잘못된 입력입니다\n";
			break;
		}
	}
	
}