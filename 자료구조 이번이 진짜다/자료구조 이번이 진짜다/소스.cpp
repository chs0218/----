#include <iostream>

using namespace std;

struct LolDic
{
	wchar_t Name[20];
	int HP, MP, Speed, Range;
	wchar_t Position[30];

	void print()
	{
		wcout << "Name: " << Name << " HP: " << HP << " MP: " << MP << " Speed: " << Speed << " Range: " << Range << " Position: " << Position << endl;
	}
};

int mystrstr(const wchar_t str1[], const wchar_t str2[])
{
	int re = 0;

	for (int i = 0; i < 20; ++i)
	{
		if (str1[i] != str2[i])
		{
			re = 1;
			break;
		}
		else if (str1[i] == '\0')
			break;
	}

	return re;
}

void mystrcpy(wchar_t str1[], wchar_t str2[])
{
	for (int i = 0; i < 20; ++i)
	{
		str1[i] = str2[i];
		if (str2[i] == '\0')
			break;
	}
}

int CheckCommand(const wchar_t command[])
{
	if (mystrstr(L"Search", command) == 0)
		return 1;
	else if (mystrstr(L"Insert", command) == 0)
		return 2;
	else if (mystrstr(L"Delete", command) == 0)
		return 3;
	else if (mystrstr(L"DeleteAll", command) == 0)
		return 4;
	else if (mystrstr(L"PrintAll", command) == 0)
		return 5;
	else if (mystrstr(L"FindMaxHp", command) == 0)
		return 6;
	else if (mystrstr(L"SortByHp", command) == 0)
		return 7;
	else
		return 0;
}

void Search(LolDic lol[], const int Dicnum)
{
	wchar_t name[20];
	cout << "찾으실 챔피언의 이름을 입력해 주세요: ";
	wcin >> name;

	for (int i = 0; i < Dicnum; ++i)
	{
		if (mystrstr(lol[i].Name, name) == 0)
		{
			lol[i].print();
			break;
		}
		else if (i == Dicnum - 1)
			cout << "해당 챔피언은 존재하지 않습니다." << endl;
	}
}

void Delete(LolDic lol[], int* Dicnum)
{
	wchar_t name[20];
	cout << "지우실 챔피언의 이름을 입력해 주세요: ";
	wcin >> name;

	for (int i = 0; i < *Dicnum; ++i)
	{
		if (mystrstr(lol[i].Name, name) == 0)
		{
			lol[i] = lol[*Dicnum - 1];
			*Dicnum -= 1;
			break;
		}
		else if (i == *Dicnum - 1)
			cout << "해당 챔피언은 존재하지 않습니다." << endl;
	}
}

void Insert(LolDic lol[], int* Dicnum)
{
	wchar_t name[20];
	int hp = 0, mp = 0, speed = 0, range = 0;
	wchar_t position[30];

	cout << "추가할 챔피언의 이름을 입력해 주세요: ";
	wcin >> name;

	cout << "추가할 챔피언의 HP를 입력해주세요: ";
	while (hp == 0)
	{
		cin >> hp;
		if (!cin)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "숫자를 입력해주세요\n";
		}
	}

	cout << "추가할 챔피언의 MP를 입력해주세요: ";

	while (mp == 0)
	{
		cin >> mp;
		if (!cin)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "숫자를 입력해주세요\n";
		}
	}

	cout << "추가할 챔피언의 Speed를 입력해주세요: ";

	while (speed == 0)
	{
		cin >> speed;
		if (!cin)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "숫자를 입력해주세요\n";
		}
	}

	cout << "추가할 챔피언의 Range를 입력해주세요: ";


	while (range == 0)
	{
		cin >> range;
		if (!cin)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "숫자를 입력해주세요\n";
		}
	}
	cout << "추가할 챔피언의 Position을 입력해주세요: ";
	wcin >> position;

	mystrcpy(lol[*Dicnum].Name, name);
	lol[*Dicnum].HP = hp;
	lol[*Dicnum].MP = mp;
	lol[*Dicnum].Speed = speed;
	lol[*Dicnum].Range = range;
	mystrcpy(lol[*Dicnum].Position, position);

	++*Dicnum;
}

void DeleteAll(LolDic lol[], int* Dicnum)
{
	wchar_t position[30];
	cout << "삭제할 포지션을 입력해주세요: ";
	wcin >> position;
	for (int i = 0; i < *Dicnum; ++i)
	{
		if (mystrstr(lol[i].Name, position)==0)
		{
			lol[i] = lol[*Dicnum - 1];
			--*Dicnum;
			--i;
		}
	}
}

void PrintAll(LolDic lol[], const int Dicnum)
{
	for (int i = 0; i < Dicnum; ++i)
	{
		lol[i].print();
	}
}

void FindMaxHp(LolDic lol[], const int Dicnum)
{
	int maxHP = 0;
	for (int i = 0; i < Dicnum; ++i)
	{
		if (lol[i].HP > maxHP)
			maxHP = lol[i].HP;
	}

	for (int i = 0; i < Dicnum; ++i)
	{
		if (lol[i].HP == maxHP)
			lol[i].print();
	}
}

void SortByHp(LolDic lol[], const int Dicnum)
{
	qsort(lol, Dicnum, sizeof(LolDic), [](const void* p, const void *q) {
		return ((LolDic*)p)->HP - ((LolDic*)q)->HP;
	});
}

int StartGame(LolDic lol[], int* Dicnum)
{
	wchar_t command[20];

	cout << "명령을 입력해 주세요:(Search, Insert, Delete, DeleteAll, PrintAll, FindMaxHp, SortByHp): ";
	wcin >> command;

	switch (CheckCommand(command))
	{
	case 1:
		Search(lol, *Dicnum);
		break;
	case 2:
		Insert(lol, &*Dicnum);
		break;
	case 3:
		Delete(lol, &*Dicnum);
		break;
	case 4:
		DeleteAll(lol, &*Dicnum);
		break;
	case 5:
		PrintAll(lol, *Dicnum);
		break;
	case 6:
		FindMaxHp(lol, *Dicnum);
		break;
	case 7:
		SortByHp(lol, *Dicnum);
		break;
	default:
		cout << "존재하지 않는 명령 입니다\n";
		break;
	}

	return 0;

}

int main()
{
	LolDic lol[100] = {
	  {L"가렌",    616,   0, 340, 175, L"탑"},
	  {L"다리우스", 582, 263, 340, 175, L"탑"},
	  {L"우디르", 593, 270, 345, 125, L"정글"},
	  {L"요릭", 580, 300, 340,   175, L"탑"},
	  {L"애니",    524, 418, 335, 625, L"미드"},
	  {L"제라스", 526, 459,   340, 525, L"미드"},
	  {L"블라디미르", 537, 0, 330, 450,   L"탑"},
	  {L"스카너", 601, 320, 335, 125, L"정글"},
	  {L"애쉬",    539, 280, 325, 600, L"봇"},
	  {L"자야",    561, 340, 325, 525, L"봇"},
	  {L"진", 556, 300, 330, 550, L"봇"},
	  {L"하이머딩거", 488, 385, 340, 550, L"탑"},
	  {L"초가스", 574, 272, 345   , 125, L"탑"},
	  {L"바루스", 499, 360, 330   , 575, L"봇"},
	  {L"브랜드", 520, 469, 340   , 550, L"서폿"},
	  {L"아우렐리온 솔", 510, 350, 325, 550, L"미드"},
	  {L"나서스",   561, 325, 350, 125,   L"탑"},
	  {L"스웨인", 525, 468,   335, 550, L"미드"},
	  {L"벨코즈", 520, 469,   340, 525, L"미드"},
	  {L"럭스",    490, 480, 330, 550, L"서폿"}
	};

	int GameStart = 0, Dicnum = 20;


	_wsetlocale(LC_ALL, L"Korean");

	while (GameStart==0)
	{

		GameStart = StartGame(lol, &Dicnum);
	}
}