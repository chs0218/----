#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

struct LolDic {
	char name[15];
	int hp, mp, speed, range;
	char position[30];
};

void print(LolDic temp)
{
	printf("이름: %s, HP: %d, MP: %d, SPEED: %d, RANGE: %d, 포지션: %s\n", name, hp, mp, speed, range, position);
}

int input()
{
	char command[10] = "NONE";
	int judge = 0;
	for (int i = 0; i < 10; ++i)
	{
		command[i] = _getwch();
		printf("%c", command[i]);
		if (command[i] == 13)
		{
			command[i] = '\0';
			break;
		}
		if (i == 9)
			judge = 1;
	}

	if (judge == 1)
		return 0;

	if (strstr(command, "Search") == command && command[6] == '\0')
		return 1;
	if (strstr(command, "Insert") == command && command[6] == '\0')
		return 2;
	if (strstr(command, "Delete") == command && command[6] == '\0')
		return 3;
	if (strstr(command, "DeleteAll") == command && command[9] == '\0')
		return 4;
	if (strstr(command, "PrintAll") == command && command[8] == '\0')
		return 5;
	if (strstr(command, "FindMaxHP") == command && command[9] == '\0')
		return 6;
	if (strstr(command, "SortByHp") == command && command[8] == '\0')
		return 7;
	if (strstr(command, "Quit") == command && command[4] == '\0')
		return 8;

	return 0;
}

void Swap(LolDic* A, LolDic* B)
{
	LolDic tmp = *A;
	*A = *B;
	*B = tmp;
}

void Delete(LolDic* LOL, int DelNum, int* DicNum)
{
	for (int i = DelNum; i < *DicNum; ++i)
		LOL[i] = LOL[i + 1];
	--*DicNum;
}

int main()
{
	LolDic lol[100] = {
   {"Garen",    616,   0, 340, 175, "top"},
   {"Darius", 582, 263, 340, 175, "top"},
   {"Udyr", 593, 270, 345, 125, "jungle"},
   {"Yorick", 580, 300, 340,   175, "top"},
   {"Annie",    524, 418, 335, 625, "mid"},
   {"Xerath", 526, 459,   340, 525, "mid, sup"},
   {"Vladimir", 537, 0, 330, 450,   "top, mid"},
   {"Skarner", 601, 320, 335, 125, "jungle"},
   {"Ashe",    539, 280, 325, 600, "bot"},
   {"Xayah",    561, 340, 325, 525, "bot"},
   {"Jhin", 556, 300, 330, 550, "bot"},
   {"Heimerdinger", 488, 385, 340, 550, "top"},
   {"Cho'Gath", 574, 272, 345   , 125, "top"},
   {"Varus", 499, 360, 330   , 575, "bot"},
   {"Brand", 520, 469, 340   , 550, "sup"},
   {"Aurelion Sol", 510, 350, 325, 550, "mid"},
   {"Nasus",   561, 325, 350, 125,   "top"},
   {"Swain", 525, 468,   335, 550, "mid"},
   {"Vel'Koz", 520, 469,   340, 525, "mid, sup"},
   {"Lux",    490, 480, 330, 550, "mid, sup"}
	};

	int command = 0, DicNum = 20, Namelength = 0;
	char name[15];
	int MaxHp = 0, Delnum = -1;
	char Position[30] = {};
	int AHP = 0, AMP = 0, ARG = 0, ASD = 0;
	while (command != 8)
	{
		printf("원하시는 명령을 입력해주세요(Search, Insert, Delete, DeleteAll, PrintAll, FindMaxHP, SortByHp, Quit): ");
		command = input();
		switch (command)
		{
		case(1):
			printf("\n찾을 챔피언의 이름을 입력해주세요: ");
			for (int i = 0; i < 15; ++i)
			{
				name[i] = _getwch();
				printf("%c", name[i]);
				if (name[i] == 13)
				{
					Namelength = i;
					name[i] = '\0';
					break;
				}
				if (i == 14)
				{
					name[i] = '\0';
					break;
				}
			}

			for (int i = 0; i < DicNum; ++i)
			{
				if (strstr(lol[i].name, name) == lol[i].name && lol[i].name[Namelength] == '\0')
				{
					printf("\n");
					lol[i].print();
					break;
				}
				if (i == DicNum - 1)
					printf("\n해당 챔피언은 존재하지 않습니다.\n");
			}
			break;
		case(2):
			printf("\n추가할 챔피언의 이릅을 입력해주세요(영문 15자 내): ");
			for (int i = 0; i < 15; ++i)
			{
				name[i] = _getwch();
				printf("%c", name[i]);
				if (name[i] == 13)
				{
					Namelength = i;
					name[i] = '\0';
					break;
				}
				if (i == 14)
				{
					name[i] = '\0';
					break;
				}
			}
			printf("\n추가할 챔피언의 HP을 입력해주세요: ");
			scanf_s("%d", &AHP);
			printf("\n추가할 챔피언의 MP을 입력해주세요: ");
			scanf_s("%d", &AMP);
			printf("\n추가할 챔피언의 SPEED를 입력해주세요: ");
			scanf_s("%d", &ASD);
			printf("\n추가할 챔피언의 Range를 입력해주세요: ");
			scanf_s("%d", &ARG);
			printf("\n추가할 챔피언의 Position을 입력해주세요: ");
			for (int i = 0; i < 30; ++i)
			{
				Position[i] = (char)_getwch();
				printf("%c", Position[i]);
				if (Position[i] == 13)
				{
					Position[i] = '\0';
					break;
				}
				if (i == 14)
				{
					Position[i] = '\0';
					break;
				}
			}
			strcpy_s(lol[DicNum].name, name);
			strcpy_s(lol[DicNum].position, Position);
			lol[DicNum].hp = AHP;
			lol[DicNum].mp = AMP;
			lol[DicNum].speed = ASD;
			lol[DicNum].range = ARG;


			++DicNum;

			break;
		case(3):
			printf("\n삭제할 챔피언의 이름을 입력해주세요: ");
			for (int i = 0; i < 15; ++i)
			{
				name[i] = _getwch();
				printf("%c", name[i]);
				if (name[i] == 13)
				{
					Namelength = i;
					name[i] = '\0';
					break;
				}
				if (i == 14)
				{
					name[i] = '\0';
					break;
				}
			}
			for (int i = 0; i < DicNum; ++i)
			{
				if (strstr(lol[i].name, name) == lol[i].name && lol[i].name[Namelength] == '\0')
				{
					Delnum = i;
					break;
				}

				if (i == DicNum - 1)
					printf("\n해당 챔피언은 존재하지 않습니다.\n");
			}
			Delete(lol, Delnum, &DicNum);
			break;
		case(4):
			printf("\n삭제할 포지션을 입력해주세요(top, jungle, mid, bot, sup): ");
			for (int i = 0; i < 6; ++i)
			{
				Position[i] = _getwch();
				printf("%c", Position[i]);
				if (Position[i] == 13)
				{
					Namelength = i;

					Position[i] = '\0';

					break;
				}
				if (i == 10)
				{
					name[i] = '\0';
					break;
				}
			}
			for (int i = 0; i < DicNum; ++i)
			{
				if (strstr(lol[i].position, Position) > 0)
				{
					Delete(lol, i, &DicNum);
					--i;
				}
			}
			break;
		case(5):
			printf("\n");
			for (int i = 0; i < DicNum; ++i)
				lol[i].print();
			break;
		case(6):
			for (int i = 0; i < DicNum; ++i)
				if (lol[i].hp > MaxHp)
					MaxHp = lol[i].hp;
			for (int i = 0; i < DicNum; ++i)
				if (lol[i].hp == MaxHp)
				{
					printf("\n");
					lol[i].print();
				}
			break;
		case(7):
			for (int i = 0; i < DicNum; ++i)
			{
				for (int j = 0; j < DicNum; ++j)
					if (lol[i].hp < lol[j].hp)
					{
						Swap(&lol[i], &lol[j]);
					}
			}
			break;
		case(8):
			break;
		}

		printf("\n");
	}
}