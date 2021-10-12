/*
#include <iostream>
#include <time.h>

bool GameSet = false;
// 야구게임을 만들거야
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
		std::cout << count << "스트라이크, ";
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
		std::cout << count << "볼입니다." << std::endl << std::endl;
	}

	void GetNumber()
	{
		std::cout << "정답숫자는 " << number[0] << number[1] << number[2] << number[3] << "입니다." << std::endl;
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
		std::cout << "공격하실 4자리 숫자를 입력해주세요 (3자리 숫자를 입력하실 경우 천의 자리 숫자가 0으로 간주됩니다.) :";
		std::cin >> num;

		if (std::cin.fail())
		{
			std::cout << "숫자를 잘 못 입력하셨습니다." << std::endl;
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
					std::cout << "숫자를 잘 못 입력하셨습니다." << std::endl;
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
	std::cout << "야구게임을 시작합니다." << std::endl;
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
			std::cout << "게임에서 승리하셨습니다." << std::endl;
			break;
		}
	}
	delete GrandNumber;
	return 0;
}*/

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
 
 
 
typedef struct ListNode {  //연결 리스트의 노드의 구조
	int coef;
	int expon;
	struct ListNode *link;
}ListNode;
 
typedef struct ListHeader {   //연결 리스트 헤더
	int length;
	ListNode *head;
	ListNode *tail;
}ListHeader;
 
void init(ListHeader *plist)   //초기화 함수
{
	plist->length = 0;
	plist->head = plist->tail = NULL;
}
 
void insert_node_last(ListHeader *plist, int coef, int expon)   ///plist는 연결 리스트의 헤더를 가리키는 포인터, coef 계수, expon은 지수이다.
{
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));   //temp는 다항식에 추가할 노드이다.
	if (temp == NULL) perror("메모리 할당 에러"); //safe coding.
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
void poly_add(ListHeader *plist1, ListHeader *plist2, ListHeader *plist3)   //plist3=plist1+plist2 이다.
{
	ListNode *a = plist1->head;   //a는 다항식 1의 인덱스
	ListNode *b = plist2->head;   //b는 다항식 2의 인덱스
	int sum;
	while (a && b) {
		if (a->expon == b->expon) {   //a의 차수와 b의 차수가 같을 때
			sum = a->coef + b->coef;
			if (sum != 0) insert_node_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) {   //a의 차수가 b의 차수보다 클 때
			insert_node_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else {   //a의 차수가 b의 차수보다 작을 때
			insert_node_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
 
	for (; a != NULL; a = a->link)   //a나 b중의 하나가 먼저 끝나게 되면 남아있는 항들을 모두 결과다항식으로 복사.
		insert_node_last(plist3, a->coef, a->expon);
	for (; b != NULL; b = b->link)
		insert_node_last(plist3, b->coef, b->expon);
}
 
void poly_multifly(ListHeader* plist1, ListHeader* plist2, ListHeader* plist3)   //plist3=plist1*plist2
{
	ListNode *a = plist1->head;   //a는 다항식 1의 인덱스
	ListHeader *d;
	d = (ListHeader *)malloc(sizeof(ListHeader));  //d는 a의 한 항과 b의 모든 항을 곱한 값을 저장하는 다항식.
	ListHeader *temp3;
	temp3 = (ListHeader *)malloc(sizeof(ListHeader));  //temp3은 다항식d들의 합을 저장하는 다항식 
	for (; a != NULL; a = a->link)
	{
		ListNode *b = plist2->head;   //b는 다항식 2의 인덱스
		for (; b != NULL; b = b->link) {
			insert_node_last(d, (a->coef) * (b->coef), (a->expon) + (b->expon));   // 다항식 2에 a의 한 항을 곱한 결과 값을 저장하는 다항식 d
		}
		poly_add(plist3, d, temp3);
		plist3->head = temp3->head;   //temp3 다항식을 plist3에 값을 복사.
		init(temp3);
		init(d);   //temp3과 d를 초기화.
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
		fprintf(out, "%d %d\n", z->coef, z->expon);   //C 다항식 출력
	ListNode* x = (&D)->head;
	for (; x != NULL; x = x->link)
		fprintf(out, "%d %d\n", x->coef, x->expon);   //D 다항식 출력
	fclose(in); fclose(out);
 
 
}