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
//		cout << "존재하지 않는 챔피언 입니다." << endl;
//}
//
//void CommandInsert(LolDic root[])
//{
//	wchar_t name[20], position[30];
//	int HP = 0, MP = 0, Speed = 0, Range = 0;
//	int error = 0;
//	cout << "추가할 챔피언의 이름을 입력해주세요: ";
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
//		cout << "이미 존재하는 챔피언입니다" << endl;
//
//
//	else
//	{
//		while (HP == 0)
//		{
//			cout << "추가할 챔피언의 HP를 입력해주세요: ";
//			cin >> HP;
//			if (!cin)
//			{
//				cout << "숫자가 아닙니다" << endl;
//				cin.clear();
//				cin.ignore(INT_MAX, '\n');
//			}
//		}
//
//		while (MP == 0)
//		{
//			cout << "추가할 챔피언의 MP를 입력해주세요: ";
//			cin >> MP;
//			if (!cin)
//			{
//				cout << "숫자가 아닙니다" << endl;
//				cin.clear();
//				cin.ignore(INT_MAX, '\n');
//			}
//		}
//
//		while (Speed == 0)
//		{
//			cout << "추가할 챔피언의 Speed를 입력해주세요: ";
//			cin >> Speed;
//			if (!cin)
//			{
//				cout << "숫자가 아닙니다" << endl;
//				cin.clear();
//				cin.ignore(INT_MAX, '\n');
//			}
//		}
//
//		while (Range == 0)
//		{
//			cout << "추가할 챔피언의 Range를 입력해주세요: ";
//			cin >> Range;
//
//			if (!cin)
//			{
//				cout << "숫자가 아닙니다" << endl;
//				cin.clear();
//				cin.ignore(INT_MAX, '\n');
//			}
//		}
//
//		cout << "추가할 챔피언의 Position를 입력해주세요: ";
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
//		cout << "존재하지 않는 챔피언 입니다." << endl;
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
//		cout << "존재하지 않는 챔피언 입니다." << endl;
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
	cout << "명령을 입력해주세요(Search, Insert, Delete, DeleteAll, PrintAll, FindMaxHp, SortByHp): ";
	cin >> command;

	switch (FindCommand(command))
	{
	case 0:
		cout << "찾으실 챔피언의 이름을 입력해주세요: ";
		wcin.ignore();
		wcin.getline(name, 50);
		/*CommandSearch(root, name);*/
		break;

	case 1:
		/*CommandInsert(root);*/
		break;

	case 2:
		cout << "삭제할 챔피언의 이름을 입력해주세요: ";
		wcin.ignore();
		wcin.getline(name, 50);
		/*CommandDelete(root, name);*/
		break;

	case 3:
		cout << "삭제할 포지션을 입력해주세요: ";
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
		cout << "존재하지 않는 명령입니다.\n";
		break;
	}

	return 0;

}

int main()
{
	LolDic* root = NULL;

	root = BTaddLolDic(root, L"가렌", 616, 0, 340, 175, L"탑");
	root = BTaddLolDic(root, L"다리우스", 582, 263, 340, 175, L"탑");
	root = BTaddLolDic(root, L"우디르", 593, 270, 345, 125, L"정글");
	root = BTaddLolDic(root, L"요릭", 580, 300, 340, 175, L"탑");
	root = BTaddLolDic(root, L"애니", 524, 418, 335, 625, L"미드");
	root = BTaddLolDic(root, L"제라스", 526, 459, 340, 525, L"미드");
	root = BTaddLolDic(root, L"블라디미르", 537, 0, 330, 450, L"탑");
	root = BTaddLolDic(root, L"스카너", 601, 320, 335, 125, L"정글");
	root = BTaddLolDic(root, L"애쉬", 539, 280, 325, 600, L"봇");
	root = BTaddLolDic(root, L"자야", 561, 340, 325, 525, L"봇");
	root = BTaddLolDic(root, L"진", 556, 300, 330, 550, L"봇");
	root = BTaddLolDic(root, L"하이머딩거", 488, 385, 340, 550, L"탑");
	root = BTaddLolDic(root, L"초가스", 574, 272, 345, 125, L"탑");
	root = BTaddLolDic(root, L"바루스", 499, 360, 330, 575, L"봇");
	root = BTaddLolDic(root, L"브랜드", 520, 469, 340, 550, L"서폿");
	root = BTaddLolDic(root, L"아우렐리온 솔", 510, 350, 325, 550, L"미드");
	root = BTaddLolDic(root, L"나서스", 561, 325, 350, 125, L"탑");
	root = BTaddLolDic(root, L"스웨인", 525, 468, 335, 550, L"미드");
	root = BTaddLolDic(root, L"럭스", 490, 480, 330, 550, L"서폿");
	root = BTaddLolDic(root, L"벨코즈", 520, 469, 340, 525, L"미드");


	int Game = 0;

	_wsetlocale(LC_ALL, L"Korean");

	while (1)
	{
		Game = GameStart(root);
		if (Game == 1)
			break;
	}
}