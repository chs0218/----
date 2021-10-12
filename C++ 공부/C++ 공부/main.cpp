/*
#include <iostream>
#include <time.h>

bool GameSet = false;
// �߱������� ����ž�
class Baseball {
	int number[4];
	int count = 0;
public:
	Baseball(int num[])
	{
		memcpy(number, num, sizeof(int) * 4);
	}
	void HowmanyStrike(const int AttackNumber[])
	{
		count = 0;

		for (int i = 0; i < 4; ++i)
		{
			if (number[i] == AttackNumber[i])
				++count;
		}

		if (count == 4)
			GameSet = true;
		std::cout << count << "��Ʈ����ũ, ";
	}

	void HowmanyBall(const int AttackNumber[])
	{
		count = 0;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (AttackNumber[i] == number[j])
				{
					++count;
					j = 5;
				}
			}
		}
		std::cout << count << "���Դϴ�." << std::endl << std::endl;
	}

	void GetNumber()
	{
		std::cout << "������ڴ� " << number[0] << number[1] << number[2] << number[3] << "�Դϴ�." << std::endl;
	}
};

bool PerfectNumber(const int AtkNumber[])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = i + 1; j < 4; ++j)
		{
			if (AtkNumber[i] == AtkNumber[j])
				return false;
		}
	}
}

void Interface(int AttackNumber[]){
	int num = 0;

	while(1)
	{
		std::cout << "�����Ͻ� 4�ڸ� ���ڸ� �Է����ּ��� (3�ڸ� ���ڸ� �Է��Ͻ� ��� õ�� �ڸ� ���ڰ� 0���� ���ֵ˴ϴ�.) :";
		std::cin >> num;

		if (std::cin.fail())
		{
			std::cout << "���ڸ� �� �� �Է��ϼ̽��ϴ�." << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		else
		{
			if (num >= 123 && num <= 9999)
			{
				AttackNumber[0] = num / 1000;
				AttackNumber[1] = num % 1000 / 100;
				AttackNumber[2] = num % 100 / 10;
				AttackNumber[3] = num % 10;

				if (PerfectNumber(AttackNumber))
					break;
				else
					std::cout << "���ڸ� �� �� �Է��ϼ̽��ϴ�." << std::endl;
			}
		}
	}
}
void setNumber(int SettingNumber[])
{
	SettingNumber[0] = rand() % 9;
	while (1)
	{
		SettingNumber[1] = rand() % 9 + 0;
		if (SettingNumber[0] != SettingNumber[1])
			break;
	}

	while (1)
	{
		SettingNumber[2] = rand() % 9 + 0;
		if (SettingNumber[0] != SettingNumber[2] && SettingNumber[1] != SettingNumber[2])
			break;
	}

	while (1)
	{
		SettingNumber[3] = rand() % 9 + 0;
		if (SettingNumber[3] != SettingNumber[0] && SettingNumber[3] != SettingNumber[1] && SettingNumber[3] != SettingNumber[2])
			break;
	}
}

int main()
{
	int AtkNumber[4] = { 0, 0, 0, 0};
	srand((unsigned int)time(0));
	std::cout << "�߱������� �����մϴ�." << std::endl;
	setNumber(AtkNumber);

	Baseball* GrandNumber = new Baseball(AtkNumber);
	GrandNumber->GetNumber();
	while (1)
	{
		Interface(AtkNumber);
		GrandNumber->HowmanyStrike(AtkNumber);
		GrandNumber->HowmanyBall(AtkNumber);
		if (GameSet)
		{
			std::cout << "���ӿ��� �¸��ϼ̽��ϴ�." << std::endl;
			break;
		}
	}
	delete GrandNumber;
	return 0;
}*/

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
 
 
 
typedef struct ListNode {  //���� ����Ʈ�� ����� ����
	int coef;
	int expon;
	struct ListNode *link;
}ListNode;
 
typedef struct ListHeader {   //���� ����Ʈ ���
	int length;
	ListNode *head;
	ListNode *tail;
}ListHeader;
 
void init(ListHeader *plist)   //�ʱ�ȭ �Լ�
{
	plist->length = 0;
	plist->head = plist->tail = NULL;
}
 
void insert_node_last(ListHeader *plist, int coef, int expon)   ///plist�� ���� ����Ʈ�� ����� ����Ű�� ������, coef ���, expon�� �����̴�.
{
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));   //temp�� ���׽Ŀ� �߰��� ����̴�.
	if (temp == NULL) perror("�޸� �Ҵ� ����"); //safe coding.
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->length++;
}
void poly_add(ListHeader *plist1, ListHeader *plist2, ListHeader *plist3)   //plist3=plist1+plist2 �̴�.
{
	ListNode *a = plist1->head;   //a�� ���׽� 1�� �ε���
	ListNode *b = plist2->head;   //b�� ���׽� 2�� �ε���
	int sum;
	while (a && b) {
		if (a->expon == b->expon) {   //a�� ������ b�� ������ ���� ��
			sum = a->coef + b->coef;
			if (sum != 0) insert_node_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) {   //a�� ������ b�� �������� Ŭ ��
			insert_node_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else {   //a�� ������ b�� �������� ���� ��
			insert_node_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
 
	for (; a != NULL; a = a->link)   //a�� b���� �ϳ��� ���� ������ �Ǹ� �����ִ� �׵��� ��� ������׽����� ����.
		insert_node_last(plist3, a->coef, a->expon);
	for (; b != NULL; b = b->link)
		insert_node_last(plist3, b->coef, b->expon);
}
 
void poly_multifly(ListHeader* plist1, ListHeader* plist2, ListHeader* plist3)   //plist3=plist1*plist2
{
	ListNode *a = plist1->head;   //a�� ���׽� 1�� �ε���
	ListHeader *d;
	d = (ListHeader *)malloc(sizeof(ListHeader));  //d�� a�� �� �װ� b�� ��� ���� ���� ���� �����ϴ� ���׽�.
	ListHeader *temp3;
	temp3 = (ListHeader *)malloc(sizeof(ListHeader));  //temp3�� ���׽�d���� ���� �����ϴ� ���׽� 
	for (; a != NULL; a = a->link)
	{
		ListNode *b = plist2->head;   //b�� ���׽� 2�� �ε���
		for (; b != NULL; b = b->link) {
			insert_node_last(d, (a->coef) * (b->coef), (a->expon) + (b->expon));   // ���׽� 2�� a�� �� ���� ���� ��� ���� �����ϴ� ���׽� d
		}
		poly_add(plist3, d, temp3);
		plist3->head = temp3->head;   //temp3 ���׽��� plist3�� ���� ����.
		init(temp3);
		init(d);   //temp3�� d�� �ʱ�ȭ.
	}
}
 
void main()
{
	ListHeader A, B, C, D;
	init(&A);
	init(&B);
	init(&C);
	init(&D);
	int i, coef, exp;
	FILE* in;
	in = fopen("input.txt", "r");
	for(i=0;i<4;i++)
	{
		fscanf_s(in, "%d %d", &coef, &exp);
		insert_node_last(&A, coef, exp);
	}
	for (i = 0; i < 3; i++)
	{
		fscanf_s(in, "%d %d", &coef, &exp);
		insert_node_last(&B, coef, exp);
	}
	poly_add(&A, &B, &C);
	poly_multifly(&A, &B, &D);
	FILE* out;
	out = fopen("output.txt", "w");
	ListNode* z = (&C)->head;
	for (; z != NULL; z = z->link)
		fprintf(out, "%d %d\n", z->coef, z->expon);   //C ���׽� ���
	ListNode* x = (&D)->head;
	for (; x != NULL; x = x->link)
		fprintf(out, "%d %d\n", x->coef, x->expon);   //D ���׽� ���
	fclose(in); fclose(out);
 
 
}