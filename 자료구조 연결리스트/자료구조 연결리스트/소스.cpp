#include <iostream>

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
	struct LolDic* next;
	void print()
	{
		wcout << "Name: " << name << " HP: " << HP << " MP: " << MP << " Speed: " << Speed << " Range: " << Range << " Position: " << Position << endl;
	}
};

void addLolDic(struct LolDic *target, const wchar_t name[50], int HP, int MP, int Speed, int Range, const wchar_t Position[50])
{
	LolDic *newNode = new LolDic;
	newNode->next = target->next;
	wcscpy(newNode->name, name);
	newNode->HP = HP;
	newNode->MP = MP;
	newNode->Speed = Speed;
	newNode->Range = Range;
	wcscpy(newNode->Position, Position);

	target->next = newNode;	
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

void CommandSearch(LolDic head[], wchar_t* name)
{
	LolDic* p;
	int num = 0;

	for (p = head; p->next != head; p = p->next)
	{
		if (wcsstr(p->name, name) == p->name)
		{
			p->print();
			++num;
		}
	}

	if (wcsstr(p->name, name) == p->name)
	{
		p->print();
		++num;
	}

	if (num == 0)
		cout << "�������� �ʴ� è�Ǿ��Դϴ�" << endl;
}

void CommandInsert(LolDic head[])
{
	wchar_t name[20], position[30];
	int HP = 0, MP = 0, Speed = 0, Range = 0;
	int error = 0;
	cout << "�߰��� è�Ǿ��� �̸��� �Է����ּ���: ";

	wcin >> name;

	LolDic* p;

	for (p = head; p->next != head; p = p->next)
	{
		if (wcsstr(p->name, name) == p->name)
		{
			++error;
		}
	}

	if (wcsstr(p->name, name) == p->name)
	{
		p->print();
		++error;
	}


	if (error != 0)
		cout << "�̹� �����ϴ� è�Ǿ��Դϴ�" << endl;


	else
	{
		while (HP == 0)
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

		addLolDic(head, name, HP, MP, Speed, Range, position);
	}
}

void removenext(LolDic* target)
{
	LolDic* removeDic = target->next;
	target->next = removeDic->next;
	free(removeDic);
}

void CommandDelete(LolDic head[], wchar_t* name)
{
	LolDic* p;

	for (p = head; p->next != head; p = p->next)
	{
		if (wcsstr(p->next->name, name) == p->next->name)
		{
			removenext(p);
		}
	}
}

void CommandDeleteAll(LolDic head[], wchar_t* position)
{
	LolDic* p;

	for (p = head; p->next != head; p = p->next)
	{
		while (1)
		{
			if (wcsstr(p->next->Position, position) == p->next->Position)
			{
				removenext(p);
			}

			else
				break;
		}
	}

}

void CommandPrintAll(LolDic head[])
{
	LolDic* p;

	for (p = head->next; p->next != head; p = p->next)
	{
		p->print();
	}
	p->print();
}

void CommandFindMaxHp(LolDic head[], int* MaxHP)
{
	LolDic* p;
	for (p = head->next; p->next != head; p = p->next)
	{
		if (p->HP > *MaxHP)
			*MaxHP = p->HP;
	}

	if (p->HP > *MaxHP)
		*MaxHP = p->HP;
}

void PrintMaxHP(LolDic head[], int MaxHP)
{
	LolDic *p;
	for (p = head->next; p->next != head; p = p->next)
	{
		if (p->HP == MaxHP)
			p->print();
	}
	if (p->HP == MaxHP)
		p->print();
}


void sort(LolDic head[])
{
	LolDic* tmp;
	LolDic* tmp2;
	LolDic* tmp3;
	LolDic* p;
	LolDic* q;
	LolDic* r = head;

	int count = 0;
	while (r->next->next->next != head)
	{

		while (1)
		{
			count = 0;
			p = r;

			for (q = p->next; q->next != head; q = q->next)
			{
				tmp = p->next;
				tmp2 = q->next;
				tmp3 = q->next->next;

				if (p->next->HP < q->next->HP)
				{
					count = 1;
					p->next = q->next;
					q->next = tmp;
					tmp2->next = tmp->next;
					tmp->next = tmp3;
				}
			}

			if (p->next->HP < q->next->HP)
			{
				count = 1;
				p->next = q->next;
				q->next = tmp;
				tmp2->next = tmp->next;
				tmp->next = tmp3;
			}

			if (count == 0)
				break;
		}
		r = r->next;
	}

}

int GameStart(LolDic head[])
{
	LolDic* tmp = new LolDic;

	LolDic* p = head->next->next->next;

	LolDic* q = head->next->next;
	char command[20];
	wchar_t name[50];
	wchar_t position[50];
	int MaxHp = 0;
	cout << "����� �Է����ּ���(Search, Insert, Delete, DeleteAll, PrintAll, FindMaxHp, SortByHp): ";
	cin >> command;

	switch (FindCommand(command))
	{
	case 0:
		cout << "ã���� è�Ǿ��� �̸��� �Է����ּ���: ";
		wcin.ignore();
		wcin.getline(name, 50);
		CommandSearch(head, name);
		break;

	case 1:
		CommandInsert(head);
		break;

	case 2:
		cout << "������ è�Ǿ��� �̸��� �Է����ּ���: ";
		wcin.ignore();
		wcin.getline(name, 50);
		CommandDelete(head, name);
		break;
	
	case 3:
		cout << "������ �������� �Է����ּ���: ";
		wcin.ignore();
		wcin.getline(position, 50);
		CommandDeleteAll(head, position);
		break;
		
	case 4:
		CommandPrintAll(head);
		break;
		
	case 5:
		CommandFindMaxHp(head, &MaxHp);
		PrintMaxHP(head, MaxHp);
		break;
	
	case 6:
		sort(head);
		break;

	default:
		cout << "�������� �ʴ� ����Դϴ�.\n";
		break;
	}

	return 0;
}

int main()
{
	struct LolDic *head = new LolDic;
	head->next = head;

	addLolDic(head, L"����", 616, 0, 340, 175, L"ž");
	addLolDic(head, L"�ٸ��콺", 582, 263, 340, 175, L"ž");
	addLolDic(head, L"���", 593, 270, 345, 125, L"����");
	addLolDic(head, L"�丯", 580, 300, 340, 175, L"ž");
	addLolDic(head, L"�ִ�", 524, 418, 335, 625, L"�̵�");
	addLolDic(head, L"����", 526, 459, 340, 525, L"�̵�");
	addLolDic(head, L"����̸�", 537, 0, 330, 450, L"ž");
	addLolDic(head, L"��ī��", 601, 320, 335, 125, L"����");
	addLolDic(head, L"�ֽ�", 539, 280, 325, 600, L"��");
	addLolDic(head, L"�ھ�", 561, 340, 325, 525, L"��");
	addLolDic(head, L"��", 556, 300, 330, 550, L"��");
	addLolDic(head, L"���̸ӵ���", 488, 385, 340, 550, L"ž");
	addLolDic(head, L"�ʰ���", 574, 272, 345, 125, L"ž");
	addLolDic(head, L"�ٷ罺", 499, 360, 330, 575, L"��");
	addLolDic(head, L"�귣��", 520, 469, 340, 550, L"����");
	addLolDic(head, L"�ƿ췼���� ��", 510, 350, 325, 550, L"�̵�");
	addLolDic(head, L"������", 561, 325, 350, 125, L"ž");
	addLolDic(head, L"������", 525, 468, 335, 550, L"�̵�");
	addLolDic(head, L"������", 520, 469, 340, 525, L"�̵�");
	addLolDic(head, L"����", 490, 480, 330, 550, L"����");


	int Game = 0;

	_wsetlocale(LC_ALL, L"Korean");

	while (1)
	{
		Game = GameStart(head);
		if (Game == 1)
			break;
	}

	

	free(head);


}

/*

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
		cout << "�������� �ʴ� è�Ǿ��Դϴ�\n";

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
		cout << "�������� �ʴ� è�Ǿ��Դϴ�\n";

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
	cout << "�߰��� è�Ǿ��� �̸��� �Է����ּ���: ";

	wcin >> Name;

	NameSearch(lol, Name, *DicNum, &error);

	if (error == 1)
	{
		cout << "�̹� �����ϴ� è�Ǿ��� �̸��Դϴ�." << endl;

		return;
	}
	while (HP == 0)
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
	cout << "����� �Է����ּ���(Search, Insert, Delete, DeleteAll, PrintAll, FindMaxHp, SortByHp): ";
	cin >> command;

	switch (FindCommand(command))
	{
	case 0:
		cout << "ã���� è�Ǿ��� �̸��� �Է����ּ���: ";
		wcin.ignore();
		wcin.getline(name, 50);
		CommandSearch(lol, name, *DicNum);
		break;

	case 1:
		CommandInsert(lol, &*DicNum);
		break;

	case 2:
		cout << "������ è�Ǿ��� �̸��� �Է����ּ���: ";
		wcin.ignore();
		wcin.getline(name, 50);
		CommandDelete(lol, name, *DicNum, *DicNum);
		--*DicNum;
		break;

	case 3:
		cout << "������ �������� �Է����ּ���: ";
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
		cout << "�������� �ʴ� ����Դϴ�.\n";
		break;
	}

	return 0;
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

	int DicNum = 20, Game = 0;

	_wsetlocale(LC_ALL, L"Korean");

	while (1)
	{
		Game = GameStart(lol, &DicNum);
		if (Game == 1)
			break;
	}
}

*/