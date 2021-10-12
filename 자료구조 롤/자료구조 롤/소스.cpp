#include <iostream>
#include <locale.h>

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

int Check(const char str1[], const char str2[])
{
	int re = 0;

	for (int i = 0; i < 10; ++i)
	{
		if (str1[i] != str2[i])
		{
			re = 1;
			break;
		}

		else if (str2[i] == '\0')
			break;
	}

	return re;
}

int NameCheck(const wchar_t str1[], const wchar_t str2[])
{
	int re = 0;

	for (int i = 0; i < 10; ++i)
	{
		if (str1[i] != str2[i])
		{
			re = 1;
			break;
		}

		else if (str2[i] == '\0')
			break;
	}

	return re;
}

int GetCommand(char command[])
{
	if (Check(command, "Search") == 0)
		return 1;

	else if (Check(command, "Insert") == 0)
		return 2;

	else if (Check(command, "Delete") == 0)
		return 3;

	else if (Check(command, "DeleteAll") == 0)
		return 4;

	else if (Check(command, "PrintAll") == 0)
		return 5;

	else if (Check(command, "FindMaxHp") == 0)
		return 6;

	else if (Check(command, "SortByHp") == 0)
		return 7;

	else
		return 0;
}

void Search(LolDic lol[], int DicNum)
{
	wchar_t Champ[20];
	cout << "찾을 챔피언의 이름을 입력해주세요: ";
	wcin >> Champ;
	for (int i = 0; i < DicNum; ++i)
	{
		if (NameCheck(Champ, lol[i].Name) == 0)
		{
			lol[i].print();
			break;
		}

		else if (i == DicNum - 1)
			cout << "해당 챔피언은 존재하지 않습니다.\n";
	}
}

void mystrcpy(wchar_t str1[], wchar_t str2[], int n)
{
	for (int i = 0; i < n; ++i)
		str1[i] = str2[i];
	str1[n] = '\0';
}


void Insert(LolDic lol[], int* DicNum)
{
	wchar_t Name[20], position[30];
	int HP = 0, MP = 0, Speed = 0, Range = 0;
	int error = 0;
	cout << "추가할 챔피언의 이름을 입력해주세요: ";

	wcin >> Name;

	for (int i = 0; i < *DicNum; ++i)
		if (NameCheck(Name, lol[i].Name) == 0)
		{
			cout << "이미 존재하는 챔피언의 이름입니다." << endl;
			error = 1;
			break;
		}

	if (error == 1)
		return;

	while (HP==0)
	{
		cout << "추가할 챔피언의 HP를 입력해주세요: ";
		cin >> HP;
		if (!cin)
		{
			cout << "숫자가 아닙니다" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
	
	while (MP == 0)
	{
		cout << "추가할 챔피언의 MP를 입력해주세요: ";
		cin >> MP;
		if (!cin)
		{
			cout << "숫자가 아닙니다" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
	
	while (Speed == 0)
	{
		cout << "추가할 챔피언의 Speed를 입력해주세요: ";
		cin >> Speed;
		if (!cin)
		{
			cout << "숫자가 아닙니다" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}

	while (Range == 0)
	{
		cout << "추가할 챔피언의 Range를 입력해주세요: ";
		cin >> Range;

		if (!cin)
		{
			cout << "숫자가 아닙니다" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}

	cout << "추가할 챔피언의 Position를 입력해주세요: ";
	wcin >> position;

	mystrcpy(lol[*DicNum].Name, Name, sizeof(Name) / sizeof(wchar_t));

	lol[*DicNum].HP = HP;
	lol[*DicNum].MP = MP;
	lol[*DicNum].Speed = Speed;
	lol[*DicNum].Range = Range;
	mystrcpy(lol[*DicNum].Position, position, sizeof(position) / sizeof(wchar_t));

	*DicNum += 1;
}

void Delete(LolDic lol[], int* DicNum)
{
	wchar_t Champ[20];
	int num = 0;
	cout << "찾을 챔피언의 이름을 입력해주세요: ";
	wcin >> Champ;
	for (int i = 0; i < *DicNum; ++i)
	{
		if (NameCheck(Champ, lol[i].Name) == 0)
		{
			num = i;
			break;
		}

		else if (i == *DicNum - 1)
			cout << "해당 챔피언은 존재하지 않습니다.\n";
	}
	if(num!=0)
		for (int i = num; i < *DicNum; ++i)
			lol[i] = lol[i + 1];

	--*DicNum;
}

void DeleteAll(LolDic lol[], int* DicNum)
{
	wchar_t DelPosition[30];

	cout << "삭제할 포지션을 입력해 주세요: ";
	wcin >> DelPosition;
	for (int i = 0; i < *DicNum; ++i)
	{
		if (NameCheck(DelPosition, lol[i].Position) == 0)
		{
			for (int j = i; j < *DicNum; ++j)
				lol[j] = lol[j + 1];

			--*DicNum;
			--i;
		}
	}
}

void PrintAll(LolDic lol[], int DicNum)
{
	for (int i = 0; i < DicNum; ++i)
		lol[i].print();
}

void FindMaxHp(LolDic lol[], int DicNum)
{
	int MaxHp = 0;
	for (int i = 0; i < DicNum; ++i)
	{
		if (lol[i].HP > MaxHp)
			MaxHp = lol[i].HP;
	}

	for (int i = 0; i < DicNum; ++i)
	{
		if (lol[i].HP == MaxHp)
			lol[i].print();
	}
}

void SortByHp(LolDic lol[], int Dicnum)
{
	qsort(lol, Dicnum, sizeof(LolDic), [](const void* p, const void* q) {return ((LolDic*)p)->HP - ((LolDic*)q)->HP; });
}

int ProgramStart(LolDic lol[], int *DicNum)
{
	

	char command[10];
	int re = 0;
	cout << "명령을 입력해 주세요(Search, Insert, Delete, DeleteAll, PrintAll, FindMaxHp, SortByHp): ";
	
	cin >> command;
	
	switch (GetCommand(command))
	{
	case 1:
		Search(lol, *DicNum);
		break;
	case 2:
		Insert(lol, &*DicNum);
		break;
	case 3:
		Delete(lol, &*DicNum);
		break;
	case 4:
		DeleteAll(lol, &*DicNum);
		break;
	case 5:
		PrintAll(lol, *DicNum);
		break;
	case 6:
		FindMaxHp(lol, *DicNum);
		break;
	case 7:
		SortByHp(lol, *DicNum);
		break;
	default:
		break;
	}

	return 1;
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

	int Game = 1, DicNum = 20;

	_wsetlocale(LC_ALL, L"Korean");

	while (Game==1)
	{
		Game = ProgramStart(lol, &DicNum);
	}

}
