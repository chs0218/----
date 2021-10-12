/*
// 윈도우 프로그래밍 워밍업 1번
#include <iostream>
#include <time.h> // srand((unsigned int)time(0))
#include <conio.h> // kbhit(), getch()
#define KB_UP 72
#define KB_DOWN 80
#define KB_ENTER 13
#define KB_A 97
#define KB_D 100
#define KB_T 116
#define KB_S 115
#define KB_M 109
#define KB_N 110
#define KB_R 114
#define KB_P 112
#define KB_Q 113

int compareA(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int compareB(const void* a, const void* b)
{
	return -(*(int*)a - *(int*)b);
}


void printMessage(const bool Select)
{
	if (Select)
	{
		std::cout << "> 1 - 50보다 작은 랜덤한 숫자를 행렬에 입력" << std::endl;
		std::cout << "  2 - A ~ Z, a ~ z 사이의 랜덤한 알파뱃을 행렬에 입력" << std::endl;
	}

	else
	{
		std::cout << "  1 - 50보다 작은 랜덤한 숫자를 행렬에 입력" << std::endl;
		std::cout << "> 2 - A ~ Z, a ~ z 사이의 랜덤한 알파뱃을 행렬에 입력" << std::endl;
	}
}

void Interface(bool& Select)
{
	int KB_code = 0;
	printMessage(Select);
	while (KB_code != KB_ENTER)
	{
		if (kbhit())
		{
			system("cls");
			KB_code = getch();

			switch (KB_code)
			{
			case KB_UP:
				Select = !Select;
				break;

			case KB_DOWN:
				Select = !Select;
				break;
			}
			printMessage(Select);
		}

	}
}

void setvalue(const bool Select, int Base[][5])
{
	srand((unsigned int)time(0));

	if (Select)
	{
		int isDuplicate[50] = { 0 };
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				while (1)
				{
					Base[i][j] = rand() % 49 + 1;
					if (isDuplicate[Base[i][j]] == 0)
					{
						isDuplicate[Base[i][j]] = 1;
						break;
					}
				}
			}
		}
	}

	else
	{
		int isDuplicate[52] = { 0 };

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				while (1)
				{
					Base[i][j] = rand() % 52 + 65;
					{
						if (isDuplicate[Base[i][j] - 65] == 0)
						{
							isDuplicate[Base[i][j] - 65] = 1;

							if (Base[i][j] > 90)
								Base[i][j] += 6;

							break;
						}
					}
				}
			}
		}
	}
}

void printValue(const bool Select, const int Base[][5])
{
	if (Select)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
				std::cout << Base[i][j] << " ";
			std::cout << std::endl;
		}
	}

	else
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
				std::cout << (char)Base[i][j] << " ";
			std::cout << std::endl;
		}
	}
}

void CommandA(int Base[][5])
{
	qsort(Base, 20, sizeof(int), compareA);
}

void CommandD(int Base[][5])
{
	qsort(Base, 20, sizeof(int), compareB);
}

void CommandT(const bool Select, const int Base[][5])
{
	if (Select)
	{
		for (int i = 0; i < 4; ++i)
		{
			
			for (int j = 0; j < 5; ++j)
			{
				if (Base[i][j] % 2 == 0)
					std::cout << Base[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << std::endl;
		}
	}

	else
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (Base[i][j] % 2 == 0)
					std::cout << (char)Base[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << std::endl;
		}
	}
}

void CommandS(const bool Select, const int Base[][5])
{
	if (Select)
	{
		for (int i = 0; i < 4; ++i)
		{

			for (int j = 0; j < 5; ++j)
			{
				if (Base[i][j] % 2 != 0)
					std::cout << Base[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << std::endl;
		}
	}

	else
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (Base[i][j] % 2 != 0)
					std::cout << (char)Base[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << std::endl;
		}
	}
}

void CommandM(const bool Select, const int Base[][5])
{
	int Max = Base[0][0];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (Max < Base[i][j])
				Max = Base[i][j];
		}
	}

	if (Select)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (Base[i][j] == Max)
					std::cout << Base[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << std::endl;
		}
	}

	else
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (Base[i][j] == Max)
					std::cout << (char)Base[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << std::endl;
		}
	}
}

void CommandN(const bool Select, const int Base[][5])
{
	int Minimum = Base[0][0];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (Minimum > Base[i][j])
				Minimum = Base[i][j];
		}
	}

	if (Select)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (Base[i][j] == Minimum)
					std::cout << Base[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << std::endl;
		}
	}

	else
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (Base[i][j] == Minimum)
					std::cout << (char)Base[i][j] << " ";
				else
					std::cout << "0 ";
			}
			std::cout << std::endl;
		}
	}
}

void CommandR(int Base[][5])
{
	int r;
	int tmp;
	srand((unsigned int)time(0));
	for (int i = 0; i < 20; ++i)
	{
		r = rand() % (20 - i) + i;
		tmp = Base[i / 5][i % 5];
		Base[i / 5][i % 5] = Base[r / 5][r % 5];
		Base[r / 5][r % 5] = tmp;
	}
}

int main()
{
	bool Select = true;
	int Base[4][5] = { 0 };
	int Command = 0;

	Interface(Select);
	setvalue(Select, Base);

	while (Command != KB_Q)
	{
		std::cout << "명령을 입력해주세요: " << std::endl;
		Command = getch();
		switch (Command)
		{
		case KB_A:
			CommandA(Base);
			printValue(Select, Base);
			break;
		case KB_D:
			CommandD(Base);
			printValue(Select, Base);
			break;
		case KB_T:
			CommandT(Select, Base);
			break;
		case KB_S:
			CommandS(Select, Base);
			break;
		case KB_M:
			CommandM(Select, Base);
			break;
		case KB_N:
			CommandN(Select, Base);
			break;
		case KB_R:
			CommandR(Base);
			printValue(Select, Base);
			break;
		case KB_P:
			system("cls");
			Interface(Select);
			setvalue(Select, Base);
			break;
		}
	}
	
}*/

// 윈도우 프로그래밍 워밍업 2번
#include <iostream>
#include <time.h>
#include <conio.h>

#define LENGTH 60

void MakeSentence(char* sentence)
{
	bool Space = false;

	for (int i = 0; i < LENGTH; ++i)
	{
		if (sentence[i] == ' ')
		{
			if (Space)
			{
				for (int j = i; j < LENGTH - 1; ++j)
					sentence[j] = sentence[j + 1];
				--i;
			}

			else
				Space = true;
		}

		else
			Space = false;
	}

	if (sentence[0] == ' ')
	{
		for (int i = 0; i < LENGTH - 1; ++i)
		{
			sentence[i] = sentence[i + 1];
		}
	}
}

void CommandE(char* sentence)
{
	int Word = 0;

	for (int i = 0; i < LENGTH; ++i)
	{
		if (sentence[i] == 'e' || sentence[i] == 'E')
		{
			for (int j = Word; j < LENGTH; ++j)
			{
				if ((int)sentence[j] > 96 && (int)sentence[j] < 123)
					sentence[j] -= 32;

				else if (sentence[j] == ' ')
					break;

			}
		}

		else if (sentence[i] == ' ')
			Word = i + 1;

	}
}

void CommandF(char* sentence)
{
	srand((unsigned)time(0));
	int n = 0;
	for (int i = 0; i < LENGTH; ++i)
	{
		if (sentence[i] == ' ')
		{
			n = rand() % 4;
			switch (n)
			{
			case 0:
				sentence[i] = '@';
				break;
			case 1:
				sentence[i] = '%';
				break;
			case 2:
				sentence[i] = '#';
				break;
			case 3:
				sentence[i] = '.';
				break;
			}
		}
	}
}

void CommandL(const char* sentence)
{
	int n = 1;

	for (int i = 0; i < LENGTH; ++i)
	{
		if (sentence[i] == ' ')
			++n;
	}

	std::cout << "단어의 개수는 " << n << "개 입니다." << std::endl;
}

void CommandC(char* sentence)
{
	for (int i = 0; i < LENGTH; ++i)
	{
		if ((int)sentence[i] > 64 && (int)sentence[i] < 91)
			sentence[i] += 32;

		else if ((int)sentence[i] > 96 && (int)sentence[i] < 123)
			sentence[i] -= 32;

	}
}

int main()
{
	int Command = 0;
	char* sentence = new char[LENGTH];
	
	std::cout << "Input Sentence: ";
	std::cin.getline(sentence, LENGTH);
	MakeSentence(sentence);
	
	while (Command != 81 && Command != 113)
	{
		std::cout << "명령을 입력해주세요: " << std::endl;
		Command = getch();
		switch (Command)
		{
		case 69:
		case 101:
			CommandE(sentence);
			std::cout << sentence << std::endl;
			break;
		case 70:
		case 102:
			CommandF(sentence);
			std::cout << sentence << std::endl;
			break;
		case 76:
		case 108:
			CommandL(sentence);
			std::cout << sentence << std::endl;
			break;
		case 67:
		case 99:
			CommandC(sentence);
			std::cout << sentence << std::endl;
			break;
		}
	}

	delete[] sentence;
}