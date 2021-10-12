#include <iostream>
#include <string>

char Search[] = "Search";
char Insert[] = "Insert";
char Delete[] = "Delete";
char DeleteAll[] = "DeleteAll";
char PrintAll[] = "PrintAll";
char FindMaxHp[] = "FindMaxHp";
char SortByHp[] = "SortByHp";


using namespace std;

struct LolDic {
	wchar_t name[50];
	int HP, MP, Speed, Range;
	wchar_t Position[50];
	LolDic* LeftChild;
	LolDic* RightChild;

	void print()
	{
		wcout << "Name: " << name << " HP: " << HP << " MP: " << MP << " Speed: " << Speed << " Range: " << Range << " Position: " << Position << endl;
	}
};

LolDic* BTaddLolDic(LolDic* root, const wchar_t Name[50], int HP, int MP, int Speed, int Range, const wchar_t position[50])
{
	if (root == NULL)
	{
		root = new LolDic;
		root->LeftChild = NULL;
		root->RightChild = NULL;
		wcscpy(root->name, Name);
		root->HP = HP;
		root->MP = MP;
		root->Speed = Speed;
		root->Range = Range;
		wcscpy(root->Position, position);
		return root;
	}
	else
	{
		if (wcscmp(root->name, Name) > 0)
			root->LeftChild = BTaddLolDic(root->LeftChild, Name, HP, MP, Speed, Range, position);
		else
			root->RightChild = BTaddLolDic(root->RightChild, Name, HP, MP, Speed, Range, position);
	}
	return root;
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
//void ProcessDelete(LolDic* target)
//{
//	LolDic* tmp = target->next;
//	target->next = tmp->next;
//	delete tmp;
//}

void CommandPrintAll(LolDic* root)
{
	if (root == NULL)
		return;
	CommandPrintAll(root->LeftChild);
	root->print();
	CommandPrintAll(root->RightChild);
}

//void CommandSearch(LolDic* root, wchar_t name[50])
//{
//	int Found = 0;
//	LolDic* p;
//	for (p = root; p->next != root; p = p->next)
//	{
//		if (wcsstr(p->next->name, name) == p->next->name)
//		{
//			p->next->print();
//			Found += 1;
//		}
//	}
//
//	if (Found == 0)
//		cout << "�������� �ʴ� è�Ǿ� �Դϴ�." << endl;
//}
//
//void CommandInsert(LolDic root[])
//{
//	wchar_t name[20], position[30];
//	int HP = 0, MP = 0, Speed = 0, Range = 0;
//	int error = 0;
//	cout << "�߰��� è�Ǿ��� �̸��� �Է����ּ���: ";
//
//	wcin >> name;
//
//	LolDic* p;
//
//	for (p = root; p->next != root; p = p->next)
//	{
//		if (wcsstr(p->next->name, name) == p->next->name)
//		{
//			++error;
//		}
//	}
//
//
//	if (error != 0)
//		cout << "�̹� �����ϴ� è�Ǿ��Դϴ�" << endl;
//
//
//	else
//	{
//		while (HP == 0)
//		{
//			cout << "�߰��� è�Ǿ��� HP�� �Է����ּ���: ";
//			cin >> HP;
//			if (!cin)
//			{
//				cout << "���ڰ� �ƴմϴ�" << endl;
//				cin.clear();
//				cin.ignore(INT_MAX, '\n');
//			}
//		}
//
//		while (MP == 0)
//		{
//			cout << "�߰��� è�Ǿ��� MP�� �Է����ּ���: ";
//			cin >> MP;
//			if (!cin)
//			{
//				cout << "���ڰ� �ƴմϴ�" << endl;
//				cin.clear();
//				cin.ignore(INT_MAX, '\n');
//			}
//		}
//
//		while (Speed == 0)
//		{
//			cout << "�߰��� è�Ǿ��� Speed�� �Է����ּ���: ";
//			cin >> Speed;
//			if (!cin)
//			{
//				cout << "���ڰ� �ƴմϴ�" << endl;
//				cin.clear();
//				cin.ignore(INT_MAX, '\n');
//			}
//		}
//
//		while (Range == 0)
//		{
//			cout << "�߰��� è�Ǿ��� Range�� �Է����ּ���: ";
//			cin >> Range;
//
//			if (!cin)
//			{
//				cout << "���ڰ� �ƴմϴ�" << endl;
//				cin.clear();
//				cin.ignore(INT_MAX, '\n');
//			}
//		}
//
//		cout << "�߰��� è�Ǿ��� Position�� �Է����ּ���: ";
//
//		wcin >> position;
//
//		BTaddLolDic(root, name, HP, MP, Speed, Range, position);
//	}
//}
//
//void CommandDelete(LolDic* root, wchar_t name[50])
//{
//	int Found = 0;
//	LolDic* p;
//	for (p = root; p->next != root; p = p->next)
//	{
//		if (wcsstr(p->next->name, name) == p->next->name)
//		{
//			ProcessDelete(p);
//			Found += 1;
//			break;
//		}
//	}
//
//	if (Found == 0)
//		cout << "�������� �ʴ� è�Ǿ� �Դϴ�." << endl;
//}
//
//void CommandDeleteAll(LolDic* root, wchar_t Position[50])
//{
//	int Found = 0;
//	LolDic* p;
//	for (p = root; p->next != root; p = p->next)
//	{
//		while (1)
//		{
//			if (wcsstr(p->next->Position, Position) == p->next->Position)
//			{
//				ProcessDelete(p);
//				Found += 1;
//			}
//			else
//				break;
//		}
//	}
//
//	if (Found == 0)
//		cout << "�������� �ʴ� è�Ǿ� �Դϴ�." << endl;
//}
//
//void CommandFindMaxHp(LolDic* root)
//{
//	int MaxHP = 0;
//	LolDic* p;
//
//	for (p = root; p->next != root; p = p->next)
//	{
//		if (MaxHP < p->next->HP)
//			MaxHP = p->next->HP;
//	}
//
//	for (p = root; p->next != root; p = p->next)
//	{
//		if (MaxHP == p->next->HP)
//			p->next->print();
//	}
//}
//
//void Swap(LolDic* p, LolDic* q)
//{
//	LolDic tmp;
//
//	tmp.HP = p->HP;
//	tmp.MP = p->MP;
//	wcscpy(tmp.Position, p->Position);
//	wcscpy(tmp.name, p->name);
//	tmp.Range = p->Range;
//	tmp.Speed = p->Speed;
//
//	p->HP = q->HP;
//	p->MP = q->MP;
//	wcscpy(p->Position, q->Position);
//	wcscpy(p->name, q->name);
//	p->Range = q->Range;
//	p->Speed = q->Speed;
//
//	q->HP = tmp.HP;
//	q->MP = tmp.MP;
//	wcscpy(q->Position, tmp.Position);
//	wcscpy(q->name, tmp.name);
//	q->Range = tmp.Range;
//	q->Speed = tmp.Speed;
//	
//}
//
//void CommandSort(LolDic* root)
//{
//	LolDic* p;
//	LolDic* q;
//	int i = 0;
//	for (p = root; p->next != root; p = p->next)
//	{
//		for (q = p; q->next != root; q = q->next)
//		{
//			if (p->next->HP < q->next->HP)
//			{
//				Swap(p->next, q->next);
//			}
//		}
//	}
//}

int GameStart(LolDic* root)
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
		/*CommandSearch(root, name);*/
		break;

	case 1:
		/*CommandInsert(root);*/
		break;

	case 2:
		cout << "������ è�Ǿ��� �̸��� �Է����ּ���: ";
		wcin.ignore();
		wcin.getline(name, 50);
		/*CommandDelete(root, name);*/
		break;

	case 3:
		cout << "������ �������� �Է����ּ���: ";
		wcin.ignore();
		wcin.getline(position, 50);
		/*CommandDeleteAll(root, position);*/
		break;

	case 4:
		CommandPrintAll(root);
		break;

	case 5:
		/*CommandFindMaxHp(root);*/
		break;

	case 6:
		/*CommandSort(root);*/
		break;

	default:
		cout << "�������� �ʴ� ����Դϴ�.\n";
		break;
	}

	return 0;

}

int main()
{
	LolDic* root = NULL;

	root = BTaddLolDic(root, L"����", 616, 0, 340, 175, L"ž");
	root = BTaddLolDic(root, L"�ٸ��콺", 582, 263, 340, 175, L"ž");
	root = BTaddLolDic(root, L"���", 593, 270, 345, 125, L"����");
	root = BTaddLolDic(root, L"�丯", 580, 300, 340, 175, L"ž");
	root = BTaddLolDic(root, L"�ִ�", 524, 418, 335, 625, L"�̵�");
	root = BTaddLolDic(root, L"����", 526, 459, 340, 525, L"�̵�");
	root = BTaddLolDic(root, L"����̸�", 537, 0, 330, 450, L"ž");
	root = BTaddLolDic(root, L"��ī��", 601, 320, 335, 125, L"����");
	root = BTaddLolDic(root, L"�ֽ�", 539, 280, 325, 600, L"��");
	root = BTaddLolDic(root, L"�ھ�", 561, 340, 325, 525, L"��");
	root = BTaddLolDic(root, L"��", 556, 300, 330, 550, L"��");
	root = BTaddLolDic(root, L"���̸ӵ���", 488, 385, 340, 550, L"ž");
	root = BTaddLolDic(root, L"�ʰ���", 574, 272, 345, 125, L"ž");
	root = BTaddLolDic(root, L"�ٷ罺", 499, 360, 330, 575, L"��");
	root = BTaddLolDic(root, L"�귣��", 520, 469, 340, 550, L"����");
	root = BTaddLolDic(root, L"�ƿ췼���� ��", 510, 350, 325, 550, L"�̵�");
	root = BTaddLolDic(root, L"������", 561, 325, 350, 125, L"ž");
	root = BTaddLolDic(root, L"������", 525, 468, 335, 550, L"�̵�");
	root = BTaddLolDic(root, L"����", 490, 480, 330, 550, L"����");
	root = BTaddLolDic(root, L"������", 520, 469, 340, 525, L"�̵�");


	int Game = 0;

	_wsetlocale(LC_ALL, L"Korean");

	while (1)
	{
		Game = GameStart(root);
		if (Game == 1)
			break;
	}
}