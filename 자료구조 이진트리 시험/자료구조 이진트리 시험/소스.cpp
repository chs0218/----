#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

struct LolDic
{
	string Name;
	string Position;
	int HP, ATK, DEF;
	LolDic* RightChild;
	LolDic* LeftChild;
	void print()
	{
		cout << "Position: " << Position << " Name: " << Name << " HP: " << HP << " ATK: " << ATK << " DEF: " << DEF << endl;
	}
};

void SLaddLolDic(LolDic* head, string tmpName, string tmpPosition, int tmpHP, int tmpATK, int tmpDEF)
{
	LolDic* p = new LolDic;
	p->RightChild = head->RightChild;
	p->Name = tmpName;
	p->Position = tmpPosition;
	p->HP = tmpHP;
	p->ATK = tmpATK;
	p->DEF = tmpDEF;
	head->RightChild = p;
}

void SLprintAll(LolDic* head)
{
	LolDic* p;
	for (p = head; p->RightChild != head; p = p->RightChild)
	{
		p->RightChild->print();
	}
}

void SLswap(LolDic* a, LolDic* b)
{
	LolDic tmp;
	tmp.HP = a->HP;
	tmp.ATK = a->ATK;
	tmp.DEF = a->DEF;
	tmp.Name = a->Name;
	tmp.Position = a->Position;
	a->HP = b->HP;
	a->ATK = b->ATK;
	a->DEF = b->DEF;
	a->Name = b->Name;
	a->Position = b->Position;
	b->HP = tmp.HP;
	b->ATK = tmp.ATK;
	b->DEF = tmp.DEF;
	b->Name = tmp.Name;
	b->Position = tmp.Position;
}

void SLsort(LolDic* head)
{
	LolDic* p;
	LolDic* q;
	for (p = head; p->RightChild != head; p = p->RightChild)
	{
		for (q = p->RightChild; q->RightChild != head; q = q->RightChild)
		{
			if (p->RightChild->Name.compare(q->RightChild->Name) > 0)
				SLswap(p->RightChild, q->RightChild);
		}
	}
}

void SLDeleteProcess(LolDic* target)
{
	LolDic* p = target->RightChild;
	target->RightChild = p->RightChild;
	delete p;
}

void SL_Delete(LolDic* head)
{
	LolDic* p;
	p = head;
	while (p->RightChild != head)
	{
		SLDeleteProcess(p);
	}
	delete head;
}

LolDic* BTaddLolDic(LolDic* root, string tmpName, string tmpPosition, int tmpHP, int tmpATK, int tmpDEF)
{
	if (root == NULL)
	{
		root = new LolDic;
		root->Name = tmpName;
		root->Position = tmpPosition;
		root->HP = tmpHP;
		root->ATK = tmpATK;
		root->DEF = tmpDEF;
		root->RightChild = NULL;
		root->LeftChild = NULL;
		return root;
	}

	else
	{
		if (root->Name.compare(tmpName) > 0)
			root->LeftChild = BTaddLolDic(root->LeftChild, tmpName, tmpPosition, tmpHP, tmpATK, tmpDEF);
		else
			root->RightChild = BTaddLolDic(root->RightChild, tmpName, tmpPosition, tmpHP, tmpATK, tmpDEF);
	}

	return root;
}

void BT_Print(LolDic* root)
{
	if (root == NULL)
		return;

	BT_Print(root->LeftChild);
	root->print();
	BT_Print(root->RightChild);
}

void BT_SortByName(LolDic* root)
{
	if (root == NULL)
		return;

	BT_SortByName(root->LeftChild);
	BT_SortByName(root->RightChild);
}

void BT_PrintAll(LolDic* root, int* n)
{
	if (root == NULL)
		return;

	BT_PrintAll(root->LeftChild, &*n);
	++*n;
	if (*n == 10000)
	{
		root->print();
		*n = 0;
	}
	BT_PrintAll(root->RightChild, &*n);
}

void BT_SearchByName(LolDic* root, string targetName)
{
	if (root == NULL)
		return;

	BT_SearchByName(root->LeftChild, targetName);
	if (root->Name.compare(targetName) == 0)
		root->print();
	BT_SearchByName(root->RightChild, targetName);
}

void CheckName(LolDic* root, int* checkName, string targetName)
{
	if (root == NULL)
		return;
	CheckName(root->LeftChild, &*checkName, targetName);
	if (root->Name.compare(targetName) == 0)
		*checkName = 1;
	CheckName(root->RightChild, &*checkName, targetName);
}

void BT_Insert(LolDic* root)
{
	int checkName = 0;
	string tmpName, tmpPosition;
	int tmpHP = 0, tmpATK = 0, tmpDEF = 0;

	cout << "추가할 챔피언의 이름을 입력해주세요: ";
	cin >> tmpName;

	CheckName(root, &checkName, tmpName);

	if (checkName == 1)
	{
		cout << "이미 존재하는 챔피언입니다" << endl;
		return;
	}

	cout << "추가할 챔피언의 Position을 입력해주세요: ";
	cin >> tmpPosition;

	while (tmpHP == 0)
	{
		cout << "추가할 챔피언의 HP를 입력해주세요: ";
		cin >> tmpHP;
		if (!cin)
		{
			cout << "숫자가 아닙니다" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}

	while (tmpATK == 0)
	{
		cout << "추가할 챔피언의 ATK를 입력해주세요: ";
		cin >> tmpATK;
		if (!cin)
		{
			cout << "숫자가 아닙니다" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}

	while (tmpDEF == 0)
	{
		cout << "추가할 챔피언의 DEF를 입력해주세요: ";
		cin >> tmpDEF;
		if (!cin)
		{
			cout << "숫자가 아닙니다" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}

	chrono::system_clock::time_point start = chrono::system_clock::now();

	BTaddLolDic(root, tmpName, tmpPosition, tmpHP, tmpATK, tmpDEF);

	chrono::duration<double> sec = chrono::system_clock::now() - start;

	cout << "걸린시간: " << sec.count() << " seconds" << endl;
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

	if (root->Name.compare(name) > 0)
		root->LeftChild = BT_Delete(root->LeftChild, name);
	else if (root->Name.compare(name) < 0)
		root->RightChild = BT_Delete(root->RightChild, name);
	else
	{
		if (root->RightChild != NULL && root->LeftChild != NULL)
		{
			tNode = findMinNode(root->RightChild);
			root->Name = tNode->Name;
			root->ATK = tNode->ATK;
			root->DEF = tNode->DEF;
			root->HP = tNode->HP;
			root->Position = tNode->Position;
			root->RightChild = BT_Delete(root->RightChild, tNode->Name);
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
	int n = 0;
	LolDic* head = new LolDic;
	head->RightChild = head;
	string tmpName, tmpPosition;
	int tmpHP, tmpATK, tmpDEF;

	ifstream SLin("LolDic.txt");
	/*while (n<5000)
	{
		SLin >> tmpPosition >> tmpName >> tmpHP >> tmpATK >> tmpDEF;
		SLaddLolDic(head, tmpName, tmpPosition, tmpHP, tmpATK, tmpDEF);
		++n;
	}*/
	SLin.close();
	/*cout << "===Sort===" << endl;*/
	chrono::system_clock::time_point start = chrono::system_clock::now();
	/*SLsort(head);*/
	chrono::duration<double> sec = chrono::system_clock::now() - start;
	cout << "걸린시간: " << sec.count() << " seconds" << endl;
	SL_Delete(head);
	LolDic* root;
	root = NULL;
	ifstream BTin("LolDic.txt");
	n = 0;
	while (n < 1000000)
	{
		BTin >> tmpPosition >> tmpName >> tmpHP >> tmpATK >> tmpDEF;
		root = BTaddLolDic(root, tmpName, tmpPosition, tmpHP, tmpATK, tmpDEF);
		++n;
	}
	while (1)
	{
		cout << "=====BTSearchByName=====" << endl;
		cout << "찾으실 챔피언의 이름을 입력해주세요: ";
		cin >> tmpName;
		start = chrono::system_clock::now();
		BT_SearchByName(root, tmpName);
		sec = chrono::system_clock::now() - start;
		cout << "걸린시간: " << sec.count() << " seconds" << endl;
		cout << "========Insert========" << endl;
		BT_Insert(root);
		cout << "=======Delete========" << endl;
		cout << "삭제할 챔피언의 이름을 입력해주세요: ";
		cin >> tmpName;
		start = chrono::system_clock::now();
		root = BT_Delete(root, tmpName);
		sec = chrono::system_clock::now() - start;
		cout << "걸린시간: " << sec.count() << " seconds" << endl;
		cout << "========PrintAll========" << endl;
		n = 0;
		start = chrono::system_clock::now();
		BT_PrintAll(root, &n);
		sec = chrono::system_clock::now() - start;
		cout << "걸린시간: " << sec.count() << " seconds" << endl;

		cout << "========SortByName_BT========" << endl;
		start = chrono::system_clock::now();
		BT_SortByName(root);
		cout << "걸린시간: " << sec.count() << " seconds" << endl;

		n = 0;
		cout << "======================종료하시겠습니까? 1번:종료=============" << endl;
		cin >> n;
		if (n == 1)
			break;
	}
}