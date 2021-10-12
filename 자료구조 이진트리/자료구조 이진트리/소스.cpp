#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

struct LolDic {
	string name;
	int HP, ATK, DEF;
	string Position;
	LolDic* LeftChild;
	LolDic* RightChild;

	void print()
	{
		cout << "Name: " << name << " HP: " << HP << " ATK: " << ATK << " DEF: " << DEF << " Position: " << Position << endl;
	}
};

void SL_PrintAll(LolDic* root)
{
	LolDic* p;
	for (p = root; p->RightChild != root; p = p->RightChild)
	{
		p->RightChild->print();
	}
}

void SLaddLolDic(LolDic* root, string name, int HP, int ATK, int DEF, string Position)
{
	LolDic* p = new LolDic;
	p->RightChild = root->RightChild;
	p->HP = HP;
	p->ATK = ATK;
	p->DEF = DEF;
	p->name = name;
	p->Position = Position;
	root->RightChild = p;
}

void Swap(LolDic* p, LolDic* q)
{
	LolDic tmp;

	tmp.HP = p->HP;
	tmp.ATK = p->ATK;
	tmp.DEF = p->DEF;
	tmp.Position = p->Position;
	tmp.name = p->name;

	p->HP = q->HP;
	p->DEF = q->DEF;
	p->ATK = q->ATK;
	p->Position = q->Position;
	p->name = q->name;

	q->HP = tmp.HP;
	q->DEF = tmp.DEF;
	q->ATK = tmp.ATK;
	q->Position = tmp.Position;
	q->name = tmp.name;
}

void ProcessDelete(LolDic* target)
{
	LolDic* tmp = target->RightChild;
	target->RightChild = tmp->RightChild;
	delete tmp;
}

void CommandSL_SortName(LolDic* root)
{
	LolDic* p;
	LolDic* q;

	for (p = root; p->RightChild != root; p = p->RightChild)
	{
		for (q = p; q->RightChild != root; q = q->RightChild)
		{
			if (p->RightChild->name.compare(q->RightChild->name) > 0)
			{
				Swap(p->RightChild, q->RightChild);
			}
		}
	}

}

void SL_Delete(LolDic* root)
{
	LolDic* p;
	p = root;
	while (p->RightChild != root)
	{
		ProcessDelete(p);
	}
	delete root;
}

LolDic* BTaddLolDic(LolDic* root, string Name, int HP, int ATK, int DEF, string position)
{
	if (root == NULL)
	{
		root = new LolDic;
		root->LeftChild = NULL;
		root->RightChild = NULL;
		root->name = Name;
		root->HP = HP;
		root->ATK = ATK;
		root->DEF = DEF;
		root->Position = position;
		return root;
	}
	else
	{
		if (root->name.compare(Name) > 0)
			root->LeftChild = BTaddLolDic(root->LeftChild, Name, HP, ATK, DEF, position);
		else
			root->LeftChild = BTaddLolDic(root->LeftChild, Name, HP, ATK, DEF, position);
	}
	return root;
}

void BT_CommandPrintAll(LolDic* root)
{
	if (root == NULL)
		return;
	BT_CommandPrintAll(root->LeftChild);
	root->print();
	BT_CommandPrintAll(root->RightChild);

}

void BT_CommandSearchByName(LolDic* root, string name)
{
	if (root == NULL)
		return;
	BT_CommandSearchByName(root->LeftChild, name);
	if (root->name.compare(name) == 0)
		root->print();
	BT_CommandSearchByName(root->RightChild, name);
}

int NameCheck(LolDic* root, string name, int* Namecheck)
{
	if (root == NULL)
		return 0;
	NameCheck(root->LeftChild, name, &*Namecheck);
	if (root->name.compare(name) == 0)
		*Namecheck = 1;
	NameCheck(root->RightChild, name, &*Namecheck);
	return 0;
}

void BT_CommandInsert(LolDic* root)
{
	string name, position;
	int Namecheck = 0;
	int HP = 0, ATK = 0, DEF = 0;
	cout << "추가할 챔피언의 이름을 입력해주세요: ";
	cin >> name;
	NameCheck(root, name, &Namecheck);
	if (Namecheck == 1)
	{
		cout << "이미 존재하는 챔피언입니다." << endl;
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
	while (ATK == 0)
	{
		cout << "추가할 챔피언의 ATK를 입력해주세요: ";
		cin >> ATK;
		if (!cin)
		{
			cout << "숫자가 아닙니다" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
	while (DEF == 0)
	{
		cout << "추가할 챔피언의 DEF를 입력해주세요: ";
		cin >> DEF;
		if (!cin)
		{
			cout << "숫자가 아닙니다" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
	cout << "추가할 챔피언의 Position을 입력해주세요: ";
	cin >> position;
	root = BTaddLolDic(root, name, HP, ATK, DEF, position);
}

LolDic* findMinNode(LolDic* root)
{
	LolDic* tmp = root;
	while (tmp->LeftChild != NULL)
		tmp = tmp->LeftChild;
	return tmp;
}


LolDic* BT_Delete(LolDic* root, string name)
{
	LolDic* tNode = NULL;
	if (root == NULL)
		return NULL;

	if (root->name.compare(name) < 0)
		root->LeftChild = BT_Delete(root->LeftChild, name);
	else if (root->name.compare(name) > 0)
		root->RightChild = BT_Delete(root->RightChild, name);
	else
	{
		if (root->RightChild != NULL && root->LeftChild != NULL)
		{
			tNode = findMinNode(root->RightChild);
			root->name = tNode->name;
			root->ATK = tNode->ATK;
			root->DEF = tNode->DEF;
			root->HP = tNode->HP;
			root->Position = tNode->Position;
			root->RightChild = BT_Delete(root->RightChild, tNode->name);
		}
		else
		{
			tNode = (root->LeftChild == NULL) ? root->RightChild : root->LeftChild;
			free(root);
			return tNode;
		}
	}
	return root;
}


int main()
{

	ifstream SLinFile("LolDic.txt");
	string name, position;
	int HP, ATK, DEF;

	LolDic* root = new LolDic;

	root->RightChild = root;

	while (!SLinFile.eof())
	{
		SLinFile >> position >> name >> HP >> ATK >> DEF;
		SLaddLolDic(root, name, HP, ATK, DEF, position);
	}
	SLinFile.close();

	SL_PrintAll(root);
	cout << "===================Sort후==============================\n";
	chrono::system_clock::time_point start = chrono::system_clock::now();
	CommandSL_SortName(root);
	chrono::duration<double> sec = chrono::system_clock::now() - start;
	SL_PrintAll(root);
	cout << "걸린시간: " << sec.count() << " seconds" << endl;
	cout << "=======================================================\n";

	SL_Delete(root);

	root = NULL;

	ifstream BTinFile("LolDic.txt");

	while (!BTinFile.eof())
	{
		BTinFile >> position >> name >> HP >> ATK >> DEF;
		root = BTaddLolDic(root, name, HP, ATK, DEF, position);
	}
	BTinFile.close();

	BT_CommandPrintAll(root);

	cout << "======================SearchByName=====================\n";
	cout << "찾으실 챔피언의 이름을 입력해주세요: ";
	cin >> name;
	BT_CommandSearchByName(root, name);

	cout << "=========================insert========================\n";
	BT_CommandInsert(root);
	BT_CommandPrintAll(root);
	cout << "=========================Delete========================\n";
	cout << "삭제하실 챔피언의 이름을 입력해주세요: ";
	cin >> name;
	root = BT_Delete(root, name);
	BT_CommandPrintAll(root);
}