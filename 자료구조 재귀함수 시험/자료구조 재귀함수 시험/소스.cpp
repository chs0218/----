#include <iostream>
#include <string>

using namespace std;

char Search[] = "Search";
char Insert[] = "Insert";
char Delete[] = "Delete";
char DeleteAll[] = "DeleteAll";
char PrintAll[] = "PrintAll";
char FindMaxHp[] = "FindMaxHp";
char SortByHp[] = "SortByHp";

struct LolDic
{
	wchar_t name[50];
	int HP = 0, MP, Speed, Range;
	wchar_t Position[50];

	void print()
	{
		wcout << "Name: " << name << " HP: " << HP << " MP: " << MP << " Speed: " << Speed << " Range: " << Range << " Position: " << Position << endl;
	}
};

void CommandSearch(LolDic lol[], wchar_t* name, const int DicNum)
{
	if (wcsstr(lol[DicNum].name, name) == lol[DicNum].name)
		lol[DicNum].print();

	else if (DicNum == 0)
		cout << "존재하지 않는 챔피언입니다\n";

	else
		CommandSearch(lol, name, DicNum - 1);
}

void ProcessDelete(LolDic lol[], int DicNum, int n)
{
	lol[n] = lol[n + 1];


	if (n == DicNum - 1)
		return;
	else
		ProcessDelete(lol, DicNum, n + 1);
}

void CommandDelete(LolDic lol[], wchar_t* name, int DicNum, const int cstDicNum)
{
	if (wcsstr(lol[DicNum].name, name) == lol[DicNum].name)
		ProcessDelete(lol, cstDicNum, DicNum);

	else if(DicNum==0)
		cout << "존재하지 않는 챔피언입니다\n";

	else
		CommandDelete(lol, name, DicNum - 1, cstDicNum);
}

void CommandDeleteAll(LolDic lol[], wchar_t* position, int DicNum, const int cstDicNum, int* n)
{
	if (wcsstr(lol[DicNum].Position, position) == lol[DicNum].Position)
	{
		ProcessDelete(lol, cstDicNum, DicNum);
		++*n;
	}
	
	if (DicNum == 0)
		return;

	else
		CommandDeleteAll(lol, position, DicNum - 1, cstDicNum, &*n);
}

void CommandPrintAll(LolDic lol[], const int DicNum)
{
	if (DicNum == 0)
		return;
	else
	{
		CommandPrintAll(lol, DicNum - 1);
		lol[DicNum-1].print();
	}
}


int FindCommand(char* command)
{
	if (strstr(Search, command) == Search)
		return 0;

	else if (strstr(Insert, command) == Insert)
		return 1;

	else if (strstr(Delete, command) == Delete)
		return 2;

	else if (strstr(DeleteAll, command) == DeleteAll)
		return 3;

	else if (strstr(PrintAll, command) == PrintAll)
		return 4;

	else if (strstr(FindMaxHp, command) == FindMaxHp)
		return 5;

	else if (strstr(SortByHp, command) == SortByHp)
		return 6;

	else
		return 7;
}


void GetBlank(LolDic lol[], int* num)
{
	if (lol[*num].HP == 0)
		return;

	else
	{
		++*num;
		GetBlank(lol, &*num);
		return;
	}
}

void NameSearch(LolDic lol[], wchar_t* name, const int DicNum, int* Error)
{
	if (wcsstr(lol[DicNum].name, name) == lol[DicNum].name)
		*Error = 1;

	else if (DicNum == 0)
		return;

	else
		NameSearch(lol, name, DicNum - 1, &*Error);
}

void CommandInsert(LolDic lol[], int* DicNum)
{
	int num = 0;
	GetBlank(lol, &num);
	wchar_t Name[20], position[30];
	int HP = 0, MP = 0, Speed = 0, Range = 0;
	int error = 0;
	cout << "추가할 챔피언의 이름을 입력해주세요: ";

	wcin >> Name;

	NameSearch(lol, Name, *DicNum, &error);

	if (error == 1)
	{
		cout << "이미 존재하는 챔피언의 이름입니다." << endl;

		return;
	}
	while (HP == 0)
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
	wcscpy(lol[num].name, Name);

	lol[num].HP = HP;
	lol[num].MP = MP;
	lol[num].Speed = Speed;
	lol[num].Range = Range;
	wcscpy(lol[num].Position, position);

	*DicNum += 1;
}

void CommandFindMaxHp(LolDic lol[], int DicNum, int* MaxHp)
{

	if (lol[DicNum].HP > *MaxHp)
		*MaxHp = lol[DicNum].HP;

	if (DicNum == 0)
		return;
	else
		CommandFindMaxHp(lol, DicNum - 1, &*MaxHp);
}

void PrintMaxHp(LolDic lol[], int DicNum, int MaxHp)
{
	if (lol[DicNum].HP == MaxHp)
		lol[DicNum].print();

	if (DicNum == 0)
		return;
	else
		PrintMaxHp(lol, DicNum - 1, MaxHp);

}
void ProcessDelete(LolDic lol[], int* n, int DicNum)
{
	lol[*n] = lol[*n + 1];
	++*n;
	if (*n == DicNum)
		return;
	else
		ProcessDelete(lol, &*n, DicNum);
}

void swap(LolDic* A, LolDic* B)
{
	LolDic tmp = *A;
	*A = *B;
	*B = tmp;
}

void sort(LolDic lol[], int DicNum)
{
	if (DicNum == 1)
		return;
	for (int i = 0; i < DicNum - 1; i++)
		if (lol[i].HP < lol[i + 1].HP)
			swap(&lol[i], &lol[i + 1]);


	sort(lol, DicNum - 1);
}

int GameStart(LolDic lol[], int* DicNum)
{
	char command[20];
	wchar_t name[50];
	wchar_t position[50];
	int n = 0, MaxHp = 0;
	cout << "명령을 입력해주세요(Search, Insert, Delete, DeleteAll, PrintAll, FindMaxHp, SortByHp): ";
	cin >> command;

	switch (FindCommand(command))
	{
	case 0:
		cout << "찾으실 챔피언의 이름을 입력해주세요: ";
		wcin.ignore();
		wcin.getline(name, 50);
		CommandSearch(lol, name, *DicNum);
		break;

	case 1:
		CommandInsert(lol, &*DicNum);
		break;

	case 2:
		cout << "삭제할 챔피언의 이름을 입력해주세요: ";
		wcin.ignore();
		wcin.getline(name, 50);
		CommandDelete(lol, name, *DicNum, *DicNum);
		--*DicNum;
		break;

	case 3:
		cout << "삭제할 포지션을 입력해주세요: ";
		wcin.ignore();
		wcin.getline(position, 50);
		CommandDeleteAll(lol, position, *DicNum, *DicNum, &n);
		*DicNum -= n;
		break;

	case 4:
		CommandPrintAll(lol, *DicNum);
		break;
	
	case 5:
		CommandFindMaxHp(lol, *DicNum, &MaxHp);
		PrintMaxHp(lol, *DicNum, MaxHp);
		break;
	
	case 6:
		sort(lol, *DicNum);
		break;

	default:
		cout << "존재하지 않는 명령입니다.\n";
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

	int DicNum = 20, Game = 0;

	_wsetlocale(LC_ALL, L"Korean");

	while (1)
	{
		Game = GameStart(lol, &DicNum);
		if (Game == 1)
			break;
	}
}