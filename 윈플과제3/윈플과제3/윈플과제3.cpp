#include <iostream>
#include <random>
#include <time.h>
#include <Windows.h>

using namespace std;

void movetoxy(int col, int row)

{

	COORD position = { col - 1,row - 1 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Drawboard()
{
	int n = 1;
	while (n<=10)
	{
		for (int i = 0; i < 21; ++i)
			cout << "-";
		cout << "\n";
		for (int i = 0; i < 21; ++i)
		{
			if ((i % 2) == 0)
				cout << "|";
			else
				cout << " ";
		}
		cout << "\n";
		++n;
	}

	for (int i = 0; i < 21; ++i)
		cout << "-";

}

int RandomX()
{
	default_random_engine dre(time(0));
	uniform_int_distribution<> uid(1, 10);

	return 2 * uid(dre);
}

int RandomY()
{
	default_random_engine dre(time(0));
	uniform_int_distribution<> uid(1, 10);

	return 2 * uid(dre);
}

void DrawBlack(int x, int y)
{
	movetoxy(x, y);
	cout << "%";
}

void DrawWhite(int x, int y)
{
	movetoxy(x, y);
	cout << "#";
}

void DrawBlank(int x, int y)
{
	movetoxy(x, y);
	cout << " ";
}

int Start(int& BX, int& BY, int& WX, int& WY)
{
	movetoxy(1, 22);
	cout << "input command: ";
	int judge = 0;
	char Direction = _getwch();
	cout << Direction;
	switch (Direction)
	{
	case('w'):
		BY -= 2;
		if (BY < 2)
		{
			cout<<"\a";
			judge = 1;
		}

		else if (BX == WX && BY == WY)
			BY += 2;

		else
		{
			DrawBlack(BX, BY);
			DrawBlank(BX, BY + 2);
		}
		break;
	case('a'):
		BX -= 2;
		if (BX < 2)
		{
			cout << "\a";

			judge = 1;
		}

		else if (BX == WX && BY == WY)
			BX += 2;

		else
		{
			DrawBlack(BX, BY);
			DrawBlank(BX + 2, BY);
		}
		break;
	case('s'):
		BY += 2;
		if (BY > 20)
		{
			cout << "\a";

			judge = 1;
		}

		else if (BX == WX && BY == WY)
			BY -= 2;

		else
		{
			DrawBlack(BX, BY);
			DrawBlank(BX, BY - 2);
		}
		break;
	case('d'):
		BX += 2;
		if (BX > 20)
		{
			cout << "\a";

			judge = 1;
		}

		else if (BX == WX && BY == WY)
			BX -= 2;

		else
		{
			DrawBlack(BX, BY);
			DrawBlank(BX - 2, BY);
		}
		break;

	case('i'):
		WY -= 2;
		if (WY < 2)
		{
			cout << "\a";

			judge = 1;
		}

		else if (BX == WX && BY == WY)
			WY += 2;

		else
		{
			DrawWhite(WX, WY);
			DrawBlank(WX, WY + 2);
		}
		break;

	case('j'):
		WX -= 2;
		if (WX < 2)
		{
			cout << "\a";

			judge = 1;
		}
		else if (BX == WX && BY == WY)
			WX += 2;

		else
		{
			DrawWhite(WX, WY);
			DrawBlank(WX + 2, WY);
		}
		break;

	case('k'):
		WY += 2;
		if (WY > 20)
		{
			cout << "\a";

			judge = 1;
		}

		else if (BX == WX && BY == WY)
			WY -= 2;

		else
		{
			DrawWhite(WX, WY);
			DrawBlank(WX, WY - 2);
		}
		break;

	case('l'):
		WX += 2;
		if (WX > 20)
		{
			cout << "\a";

			judge = 1;
		}

		else if (BX == WX && BY == WY)
			WX -= 2;

		else
		{
			DrawWhite(WX, WY);
			DrawBlank(WX - 2, WY);
		}
		break;
	case('q'):
		movetoxy(1, 7);
		judge = 1;
		break;
	}
	return judge;
}


int main()
{
	int BX = 0, BY = 0, WX = 0, WY = 0;

	BX = RandomX();
	BY = RandomY();
	while (1)
	{
		WX = RandomX();
		WY = RandomY();
		if (WX != BX && WY != BY)
			break;
	}
	Drawboard();
	DrawBlack(BX, BY);
	DrawWhite(WX, WY);

	while (1)
	{
		if ((Start(BX, BY, WX, WY)) == 1)
			break;
	}
	movetoxy(1, 23);
}
