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
	cout << "ã�� è�Ǿ��� �̸��� �Է����ּ���: ";
	wcin >> Champ;
	for (int i = 0; i < DicNum; ++i)
	{
		if (NameCheck(Champ, lol[i].Name) == 0)
		{
			lol[i].print();
			break;
		}

		else if (i == DicNum - 1)
			cout << "�ش� è�Ǿ��� �������� �ʽ��ϴ�.\n";
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
	cout << "�߰��� è�Ǿ��� �̸��� �Է����ּ���: ";

	wcin >> Name;

	for (int i = 0; i < *DicNum; ++i)
		if (NameCheck(Name, lol[i].Name) == 0)
		{
			cout << "�̹� �����ϴ� è�Ǿ��� �̸��Դϴ�." << endl;
			error = 1;
			break;
		}

	if (error == 1)
		return;

	while (HP==0)
	{
		cout << "�߰��� è�Ǿ��� HP�� �Է����ּ���: ";
		cin >> HP;
		if (!cin)
		{
			cout << "���ڰ� �ƴմϴ�" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
	
	while (MP == 0)
	{
		cout << "�߰��� è�Ǿ��� MP�� �Է����ּ���: ";
		cin >> MP;
		if (!cin)
		{
			cout << "���ڰ� �ƴմϴ�" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
	
	while (Speed == 0)
	{
		cout << "�߰��� è�Ǿ��� Speed�� �Է����ּ���: ";
		cin >> Speed;
		if (!cin)
		{
			cout << "���ڰ� �ƴմϴ�" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}

	while (Range == 0)
	{
		cout << "�߰��� è�Ǿ��� Range�� �Է����ּ���: ";
		cin >> Range;

		if (!cin)
		{
			cout << "���ڰ� �ƴմϴ�" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}

	cout << "�߰��� è�Ǿ��� Position�� �Է����ּ���: ";
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
	cout << "ã�� è�Ǿ��� �̸��� �Է����ּ���: ";
	wcin >> Champ;
	for (int i = 0; i < *DicNum; ++i)
	{
		if (NameCheck(Champ, lol[i].Name) == 0)
		{
			num = i;
			break;
		}

		else if (i == *DicNum - 1)
			cout << "�ش� è�Ǿ��� �������� �ʽ��ϴ�.\n";
	}
	if(num!=0)
		for (int i = num; i < *DicNum; ++i)
			lol[i] = lol[i + 1];

	--*DicNum;
}

void DeleteAll(LolDic lol[], int* DicNum)
{
	wchar_t DelPosition[30];

	cout << "������ �������� �Է��� �ּ���: ";
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
	cout << "����� �Է��� �ּ���(Search, Insert, Delete, DeleteAll, PrintAll, FindMaxHp, SortByHp): ";
	
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
	  {L"����",    616,   0, 340, 175, L"ž"},
	  {L"�ٸ��콺", 582, 263, 340, 175, L"ž"},
	  {L"���", 593, 270, 345, 125, L"����"},
	  {L"�丯", 580, 300, 340,   175, L"ž"},
	  {L"�ִ�",    524, 418, 335, 625, L"�̵�"},
	  {L"����", 526, 459,   340, 525, L"�̵�"},
	  {L"����̸�", 537, 0, 330, 450,   L"ž"},
	  {L"��ī��", 601, 320, 335, 125, L"����"},
	  {L"�ֽ�",    539, 280, 325, 600, L"��"},
	  {L"�ھ�",    561, 340, 325, 525, L"��"},
	  {L"��", 556, 300, 330, 550, L"��"},
	  {L"���̸ӵ���", 488, 385, 340, 550, L"ž"},
	  {L"�ʰ���", 574, 272, 345   , 125, L"ž"},
	  {L"�ٷ罺", 499, 360, 330   , 575, L"��"},
	  {L"�귣��", 520, 469, 340   , 550, L"����"},
	  {L"�ƿ췼���� ��", 510, 350, 325, 550, L"�̵�"},
	  {L"������",   561, 325, 350, 125,   L"ž"},
	  {L"������", 525, 468,   335, 550, L"�̵�"},
	  {L"������", 520, 469,   340, 525, L"�̵�"},
	  {L"����",    490, 480, 330, 550, L"����"}
	};

	int Game = 1, DicNum = 20;

	_wsetlocale(LC_ALL, L"Korean");

	while (Game==1)
	{
		Game = ProgramStart(lol, &DicNum);
	}

}
