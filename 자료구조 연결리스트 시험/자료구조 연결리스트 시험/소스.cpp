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

struct LolDic {
	wchar_t name[50];
	int HP, MP, Speed, Range;
	wchar_t Position[50];
	LolDic* next;

	void print()
	{
		wcout << "Name: " << name << " HP: " << HP << " MP: " << MP << " Speed: " << Speed << " Range: " << Range << " Position: " << Position << endl;
	}
};

void addLolDic(LolDic* head, const wchar_t name[50], int HP, int MP, int Speed, int Range, const wchar_t Position[50])
{
	LolDic* p = new LolDic;
	p->next = head->next;
	p->HP = HP;
	p->MP = MP;
	p->Speed = Speed;
	p->Range = Range;
	wcscpy(p->name, name);
	wcscpy(p->Position, Position);
	head->next = p;
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

void CommandPrintAll(LolDic* head)
{
	LolDic* p;
	for (p = head; p->next != head; p = p->next)
	{
		p->next->print();
	}

}

void CommandSearch(LolDic* head, wchar_t name[50])
{
	LolDic* p;
	int Found = 0;
	for (p = head; p->next != head; p = p->next)
	{
		if (wcsstr(p->next->name, name) == p->next->name)
		{
			p->next->print();
			Found = 1;
			break;
		}
	}
	if(Found==0)
		cout << "�������� �ʴ� è�Ǿ� �Դϴ�" << endl;
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
		if (wcsstr(p->next->name, name) == p->next->name)
		{
			++error;
		}
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

void ProcessDelete(LolDic* target)
{
	LolDic* Delete = target->next;

	target->next = Delete->next;

	free(Delete);
}

void CommandDelete(LolDic* head, wchar_t name[50])
{
	LolDic* p;
	int Found = 0;
	for (p = head; p->next != head; p = p->next)
	{
		if (wcsstr(p->next->name, name) == p->next->name)
		{
			ProcessDelete(p);
			++Found;
		}
	}

	if (Found == 0)
		cout << "�������� �ʴ� è�Ǿ� �Դϴ�" << endl;
}

void CommandDeleteAll(LolDic* head, wchar_t Position[50])
{
	LolDic* p;

	for (p = head; p->next != head; p = p->next)
	{
		while (1)
		{
			if (wcsstr(p->next->Position, Position) == p->next->Position)
			{
				ProcessDelete(p);
			}

			else break;
		}
	}
}

void CommandFindMaxHp(LolDic* head)
{
	LolDic* p;
	int MaxHp = 0;
	for (p = head; p->next != head; p = p->next)
	{
		if (MaxHp<p->next->HP)
		{
			MaxHp = p->next->HP;
		}
	}

	for (p = head; p->next != head; p = p->next)
	{
		if ( p->next->HP== MaxHp)
		{
			p->next->print();
		}
	}

}


void sort(LolDic* head)
{
	LolDic* tmp;
	LolDic* tmp2;
	LolDic* tmp3;
	LolDic* p;
	LolDic* q;
	LolDic* r = head;

	int count = 0;
	while (r-> next ->next ->next != head)
	{

		while (1)
		{
			count = 0;
			p = r;

			for (q = p->next; q->next != head; q = q->next)
			{
				tmp = p->next;

				tmp2 = q->next;
				tmp3 = tmp2->next;

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


int GameStart(LolDic* head)
{
	char command[20];
	wchar_t name[50];
	wchar_t position[50];
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
		CommandFindMaxHp(head);
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
	LolDic* head = new LolDic;

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
	addLolDic(head, L"����", 490, 480, 330, 550, L"����");
	addLolDic(head, L"������", 520, 469, 340, 525, L"�̵�");


	int Game = 0;

	_wsetlocale(LC_ALL, L"Korean");

	while (1)
	{
		Game = GameStart(head);
		if (Game == 1)
			break;
	}
}