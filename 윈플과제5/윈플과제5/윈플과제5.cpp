#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void ShowTimeBar()
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 6; ++j)
			cout << "■";
		cout << "\n";
	}
}

void movetoxy(int col, int row)
{

	COORD position = { col - 1,row - 1 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}


int main()
{
	cout << "Counter begin\n";
	ShowTimeBar();

	int firstX, firstY, n = 1;
	int NowX, NowY;
	firstX = 1, firstY = 2;
	movetoxy(1, 2);

	cout << "□";
	clock_t endWait;

	int waitMili = 1000;
	
	endWait = clock() + waitMili;
	char c = _getwch();
	while (n != 12)
	{
		if (clock() >= endWait)
		{
			firstX += 2;
			NowX = firstX + 2;
			NowY = firstY - 1;
			while (NowX > 1)
			{
				NowX -= 2;
				NowY += 1;
				if (NowX <= 11 && NowY <= 8)
				{
					movetoxy(NowX, NowY);
					cout << "□";
				}
			}
			endWait = clock() + waitMili;
			n += 1;
		}

	}

	cout << "\nCounter end\n";
}