#include <random>
#include "2018180029_�̰���.h"

using namespace LKM;

extern void gotoxy(int x, int y);

AI::AI() : player(1), enemy(-1) {
	for (auto& some : board) {
		for (auto& one : some) {
			one = NULL;
		}
	}
	size = MapSize + 1;
	now = { size / 2, size / 2 };
	last = now;
	turn = 1;
}

AI::~AI() {
}

void LKM::AI::BlackAttack(int * x, int * y)
{
	bWhite = false;

	last = now;

	*x = now.x;
	*y = now.y;

	putStone(now.x, now.y, player);
}

void LKM::AI::BlackDefend(int x, int y)
{
	bWhite = false;
	lastEnemyAtk = enemyAtk;
	enemyAtk.x = x;
	enemyAtk.y = y;
	
	putStone(x, y, enemy);

	if (findDefendPoint()) {
		gotoxy(50, 1);
		if (bWhite) {
			std::cout << "find Defend Point White " << now.x << ' ' << now.y;
		}
		else
			std::cout << "find Defend Point White " << now.x << ' ' << now.y;
	}
	else
		seqPointAttack();
}

void LKM::AI::WhiteAttack(int * x, int * y)
{
	bWhite = true;
	last = now;

	*x = now.x;
	*y = now.y;
	putStone(now.x, now.y, player);
}

void LKM::AI::WhiteDefend(int x, int y)
{
	bWhite = true;
	lastEnemyAtk = enemyAtk;
	enemyAtk.x = x;
	enemyAtk.y = y;
	
	putStone(x, y, enemy);

	if (findDefendPoint()) {
	}
	else
		seqPointAttack();
}


AI black;
AI white;

void LKM::BlackAttack(int* x, int* y) {
	black.BlackAttack(x, y);
}
void LKM::BlackDefend(int x, int y) {
	black.BlackDefend(x, y);
}
void LKM::WhiteAttack(int* x, int* y) {
	white.WhiteAttack(x, y);
}
void LKM::WhiteDefend(int x, int y) {
	white.WhiteDefend(x, y);
}


bool LKM::AI::Foul(int positionX, int positionY)
{
	if (!isEmpty(positionX, positionY)) {
		return true;
	}
	bool val = false;
	val = putStone(positionX, positionY, player);
	int foul = false;

	if (!bWhite)
	{
		foul = Foul66(positionX, positionY, 1, player);
		if (foul == false)
			foul = Foul44(positionX, positionY, 1, player);

		if (foul == false)
			foul = Foul33(positionX, positionY, 1, player);
	}
	if (val) {
		board[positionY][positionX] = NULL;
	}
	return foul;
}

int	LKM::AI::Foul33(int positionX, int positionY, bool flag, int mPlayer)
{
	int movePoint[8][2] = { { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };
	int tempX, tempY;
	int PretempX, PretempY;
	int PosttempX, PosttempY;
	int foulLine33 = 0;

	bool empty;
	float attackPoint[8] = { 0, };
	pair<int, int> Point[8];
	pair<int, int> emptyPos;
	bool check[8] = { false, };
	float checkWeight[8] = { 0.0f, };

	/* ���� �ΰ��� ��� */
	for (int way = 0; way < 8; ++way)
	{
		tempX = positionX;
		tempY = positionY;
		empty = true;

		for (int move = 0; move < 6; ++move)
		{

			tempX += movePoint[way][0];
			tempY += movePoint[way][1];

			PosttempX = tempX + movePoint[way][0];
			PosttempY = tempY + movePoint[way][1];

			PretempX = tempX - movePoint[way][0];
			PretempY = tempY - movePoint[way][1];

			if (VirtualMapMin <= tempX && tempX <= VirtualMapMax && VirtualMapMin <= tempY && tempY <= VirtualMapMax)
			{
				/* ���� �ڸ��� �÷��̾� ���� �ִٸ� */
				if (board[tempY][tempX] == mPlayer)
				{
					/* ���� ��ĭ�� �������� �ʾҴٸ� first�� ���� ������Ų��.*/
					if (empty)
						Point[way].first++;
					else /* ��ĭ�� �����Դٸ� second ����. */
						Point[way].second++;
				}
				/* ���� �ڸ��� ��ĭ �̶�� */
				else if (board[tempY][tempX] == 0)
				{
					/* ���� ��ĭ�� �������� �ʾҴٸ� */
					if (empty)
					{
						/* ��ĭ �ڸ��� ���� */
						emptyPos.first = tempX;
						emptyPos.second = tempY;

						if (flag)
						{
							/* �� ��ĭ�� ��ȿ�� �ڸ��� �ƴ϶�� ���ڸ� �� �̻� ���� �ʴ´�. */
							if (Foul44(tempX, tempY, 0, mPlayer) || Foul33(tempX, tempY, 0, mPlayer) || Foul66(tempX, tempY, 0, mPlayer))
							{
								checkWeight[way] = 1.0f;
								break;
							}
							/* ��ȿ�� �ڸ���� �׳� ��ĭ�� �����Դٰ� ǥ���ϰ� */
							/* ���� �ڸ��� ��� �� �̶�� ������ ������ ���ӵǿ� �ִٴ� �Ҹ��� ������ ���� ����Ʈ�� �ȴ�.*/
							else
							{
								//	if (mMap[PosttempY][PosttempX] != 0 && mMap[PosttempY][PosttempX] != mPlayer)
									/* ���� �ڸ��� ���� �ƴ϶�� ��� ���̸� */
								if (10 <= PosttempX && PosttempX <= 27 && 10 <= PosttempY && PosttempY <= 27)
								{
									attackPoint[way] = 0.5f;
								}
								else
								{

								}
								empty = false;
							}
						}
						/* ���ڸ��� ��ȿ���� Ȯ���Ҷ��� ���ڸ��� �׳� ���ڸ���. */
						else
							empty = false;
					}
					/* �̹� ��ĭ�� �ѹ� �����Դٸ� */
					else
					{
						/* ��ĭ�� ����ĭ�� �ٸ� �÷��̾��� ����ġ 0.5�� ������ ǥ���Ѵ�. */
						/* ���� ĭ�� ��ĭ�̳� ���� ���̶�� ������ �ʾҴ�. */
						if (flag)
						{
							if (board[PosttempY][PosttempX] == mPlayer && board[PretempY][PretempX] == mPlayer)
								board[emptyPos.second][emptyPos.first] = mPlayer;
							/*��ȿ���� �ʴٸ� ���� üũ. */
							if (Foul44(tempX, tempY, 0, mPlayer) || Foul33(tempX, tempY, 0, mPlayer) || Foul66(tempX, tempY, 0, mPlayer))
							{
								checkWeight[way] = 1.5f;
							}
							if (board[PosttempY][PosttempX] == mPlayer && board[PretempY][PretempX] == mPlayer)
								board[emptyPos.second][emptyPos.first] = 0;

							if (board[PosttempY][PosttempX] != 0 && board[PosttempY][PosttempX] != mPlayer)
							{
								checkWeight[way] = 0.5f;
							}
						}
						break;

					}
				}
				/* �ٸ� �÷��̾� ���� �����ٸ�  */
				else
				{
					/* ���� ���� ��ĭ�̶�� */
					if (board[PretempY][PretempX] == 0)
					{
						/* ��ĭ�ڿ� �ٸ� ���ε� �տ� ���� ���� �ϳ��� ���ٸ� ���� 1.5 */
						if (Point[way].first == 0)
							checkWeight[way] = 1.5f;
						else if (Point[way].first == 1)
							checkWeight[way] = 1.0f;
						else
							checkWeight[way] = 0.5f;
					}
					else
						checkWeight[way] = 1.5f;
					break;
				}
			}
			/* ĭ�� �Ѿ. */
			else
			{
				/* �Ѿ�� �� ���� �÷��̾�̶�� �������� ǥ���Ѵ�.*/
				if (board[PretempY][PretempX] == mPlayer)
					checkWeight[way] = 1.5f;
				else
					checkWeight[way] = 0.5f;

				break;
			}
		}
	}


	//cout << "flag  " << flag << "   weight  ";
	for (int i = 0; i < 4; ++i)
	{
		/*	if (flag)
			{
				cout << checkWeight[i] << " " << checkWeight[i + 4] << " ";
				cout << attackPoint[i] << " " << attackPoint[i + 4] << "     ";
			}*/
		if (checkWeight[i] + checkWeight[i + 4] - attackPoint[i] - attackPoint[i + 4] >= 0.5f)
			check[i] = true;
	}
	/*if (flag)
		cout << endl;*/

	int count = 0;
	int count1 = 0;
	int count2 = 0;
	int c = 0;

	for (int i = 0; i < 4; ++i)
	{
		/*	if (flag)
			{
				cout << i << "  " << Point[i].first << "  " << Point[i].second << "  " << check[i] << endl;
				cout << i << "  " << Point[i + 4].first << "  " << Point[i + 4].second << "  " << check[i + 4] << endl;
			}*/
		count = Point[i].first + Point[i + 4].first;
		if (count < 2)
		{
			count1 = Point[i].first + Point[i].second + Point[i + 4].first;
			if (2 == count1)
			{
				count = count1;


			}
			count2 = Point[i + 4].first + Point[i + 4].second + Point[i].first;
			if (2 == count2)
			{
				count = count2;

			}
		}


		if (2 == count)
		{
			if (Point[i].first + Point[i].second + Point[i + 4].first > 2)
				foulLine33--;
			else if (Point[i].first + Point[i + 4].second + Point[i + 4].first > 2)
				foulLine33--;

			foulLine33++;
			if (check[i])
				c++;
			if (check[i + 4])
				c++;
		}
	}

	if (foulLine33 - c <= 1)
		foulLine33 = 0;
	if (1 < foulLine33)
		return 33;
	else
		return 0;

}

int	AI::Foul44(int positionX, int positionY, bool flag, int mPlayer)
{
	int movePoint[8][2] = { { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };
	int tempX, tempY;
	int PretempX, PretempY;
	int PosttempX, PosttempY;
	int foulLine44 = 0;

	bool empty;
	pair<int, int> Point[8];
	pair<int, int> emptyPos;

	int attackPoint[8] = { 0 , };

	bool check[8] = { false, };
	/*���� 44�� 44��. */
	for (int way = 0; way < 8; ++way)
	{
		tempX = positionX;
		tempY = positionY;
		empty = true;
		for (int move = 0; move < 6; ++move)
		{
			tempX += movePoint[way][0];
			tempY += movePoint[way][1];

			PosttempX = tempX + movePoint[way][0];
			PosttempY = tempY + movePoint[way][1];

			PretempX = tempX - movePoint[way][0];
			PretempY = tempY - movePoint[way][1];

			if (VirtualMapMin <= tempX && tempX <= VirtualMapMax && VirtualMapMin <= tempY && tempY <= VirtualMapMax)
			{
				/* ���� �ڸ��� �÷��̾� ���� �ִٸ� */
				if (board[tempY][tempX] == mPlayer)
				{
					/* ���� ��ĭ�� �������� �ʾҴٸ� first�� ���� ������Ų��.*/
					if (empty)
						Point[way].first++;
					else /* ��ĭ�� �����Դٸ� second ����. */
						Point[way].second++;
				}
				/* ���� �ڸ��� ��ĭ �̶�� */
				else if (board[tempY][tempX] == 0)
				{
					/* ���� ��ĭ�� �������� �ʾҴٸ� */
					if (empty)
					{
						/* ��ĭ �ڸ��� ���� */
						emptyPos.first = tempX;
						emptyPos.second = tempY;

						if (flag)
						{
							/* �� ��ĭ�� ��ȿ�� �ڸ��� �ƴ϶�� ���ڸ� �� �̻� ���� �ʴ´�. */
							if (Foul44(tempX, tempY, 0, mPlayer) || Foul33(tempX, tempY, 0, mPlayer) || Foul66(tempX, tempY, 0, mPlayer))
							{
								check[way] = true;
								break;
							}
							else
							{
								empty = false;
								/* ��ĭ ������ �÷��̾� ���� �ְų� ������ �÷��̾� ���� ������ (���ӵ� ���� �ȴٸ�) �����Ҽ� �ִ� �ڸ���� �����Ѵ�. */
								/* ��ĭ ���� ��ĭ�� �ҿ� �����Ƿ� &&�� �ɸ���. */
								if ((board[PosttempY][PosttempX] == mPlayer || board[PretempY][PretempX] == mPlayer) && board[PosttempY][PosttempX] != 0)
									attackPoint[way]++;
							}
						}
						/* ��ĭ�� ��ȿ�� �ڸ���� ��ĭ�� ���� �Դٰ� ǥ���Ѵ�. */
						else
							empty = false;
					}
					/* �̹� ��ĭ�� �ѹ� �����Դٸ� */
					else
					{
						/* �̹� ������ ���� ������ 2����� ��ĭ�� ���� ��ȿ �˻縦 �ؾ��Ѵ�. ���⿡ ������ ���� �Ǹ� �����ɷ� ģ��. */
						if (Point[way].first + Point[way].second == 2)
						{
							/* ���� �ι�° ��ĭ ����ĭ�� �÷��̾� ���̶�� ������ ��ĭ�� �÷��̾��� ���� ä�� ������ �˻��Ѵ�. (6���� �˻��ϱ�����) */
							/* ����ĭ�� �÷��̾�� ���µ� ��ĭ�� ���� �ΰ� �ݴ��� 6������ ���� ������ �߻��Ҽ� ����. */
							if (board[PosttempY][PosttempX] == mPlayer)
							{
								board[emptyPos.second][emptyPos.first] = mPlayer;
							}
							if (flag)
							{						/*��ȿ���� �ʴٸ� ���� üũ. */
								if (Foul44(tempX, tempY, 0, mPlayer) || Foul33(tempX, tempY, 0, mPlayer) || Foul66(tempX, tempY, 0, mPlayer))
									check[way] = true;
							}
							/* ��ĭ�� �ӽ÷� �־��� ���� �ٽ� ��ĭ���� �����. */
							if (board[PosttempY][PosttempX] == mPlayer)
							{
								board[emptyPos.second][emptyPos.first] = 0;
							}
						}
						/* �ι�° ��ĭ���� ������ ���� 3����� �ι�° ��ĭ�� ��ȿ�ϴ� �ƴϴ� �������. ù��° ��ĭ�� ��ȿ �˻簡 �ʿ��ϴ�. */
						else if (Point[way].first + Point[way].second == 3)
						{
							/* ��ȿ���� �ʴٸ� ù��° ��ĭ �ڿ� ���� ���ڴ� ���ǹ��ϴ�.*/
							if (flag)
							{
								if (Foul44(tempX, tempY, 0, mPlayer) || Foul33(tempX, tempY, 0, mPlayer) || Foul66(tempX, tempY, 0, mPlayer))
								{
									check[way] = true;
									/* ��ĭ ������ ���� 0���� ����. */
									Point[way].second = 0;
								}
							}
						}
						break;
					}
				}
				/* ��ĭ�� �ƴϰ� �� ���� �ƴϸ� ���� ���̶�� ��*/
				else
				{
					check[way] = true;
					break;
				}

			}
			else /* ������ �Ѿ �� üũ*/
			{
				/*44�� ������ ��ĭ ������������ ���� ���� ǥ�� ���ص� �ɵ���.
				������ �Ѿ�µ� ������ ���� �÷��̾� ���̸� �����ٰ� ǥ���Ѵ�. */
				if (board[PretempY][PretempX] == mPlayer)
					check[way] = true;

				/* ������ �Ѿ���� ���̻� �̵��� �ʿ� ����. */
				break;
			}
		}
	}
	int count = 0;
	int count1 = 0;
	int count2 = 0;
	int c = 0;
	for (int i = 0; i < 4; ++i)
	{
		/*	if (flag)
			{
				cout << i << "  " << Point[i].first << "  " << Point[i].second << "  " << check[i] << endl;
				cout << i << "  " << Point[i + 4].first << "  " << Point[i + 4].second << "  " << check[i + 4] << endl;
			}*/

		count = Point[i].first + Point[i + 4].first;

		if (count < 3)
		{
			count1 = Point[i].first + Point[i].second + Point[i + 4].first;
			if (3 == count1)
			{
				foulLine44++;
				if (check[i])
					c++;
				if (check[i + 4])
					c *= 2;
				if (attackPoint[i])
					c--;
				if (attackPoint[i + 4])
					c--;
			}
			count2 = Point[i + 4].first + Point[i + 4].second + Point[i].first;
			if (3 == count2)
			{
				foulLine44++;
				if (check[i + 4])
					c++;
				if (check[i])
					c *= 2;
				if (attackPoint[i])
					c--;
				if (attackPoint[i + 4])
					c--;
			}
		}
		if (3 == count)
		{
			foulLine44++;
			if (abs((check[i] - attackPoint[i]) > 0) && abs((check[i + 4] - attackPoint[i + 4]) > 0))
			{
				foulLine44--;
			}
			else
			{
				if (check[i])
					c++;
				if (check[i + 4])
					c++;
				if (attackPoint[i])
					c--;
				if (attackPoint[i + 4])
					c--;
			}
		}
	}
	if (c < 0)
		c = 0;
	//if (flag)
//		cout << "44 : " << foulLine44 << "  " << c << "   " <<   endl;
	if (abs(foulLine44 * 2 - c) <= 1)
	{
		foulLine44 = 0;
	}

	if (1 < foulLine44)
		return 44;
	else
		return 0;
}


int	AI::Foul66(int positionX, int positionY, bool flag, int mPlayer)
{
	int movePoint[8][2] = { { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };
	int tempX, tempY;
	int foulLine66 = 0;

	bool empty;
	pair<int, int> Point[8];
	bool check[8] = { false, };

	for (int way = 0; way < 8; ++way)
	{
		tempX = positionX;
		tempY = positionY;
		empty = true;
		for (int move = 0; move < 6; ++move)
		{
			tempX += movePoint[way][0];
			tempY += movePoint[way][1];
			if (VirtualMapMin <= tempX && tempX <= VirtualMapMax && VirtualMapMin <= tempY && tempY <= VirtualMapMax)
			{
				if (board[tempY][tempX] == mPlayer)
					Point[way].first++;
				else
					break;
			}
			else
			{
				check[way] = true;
				break;
			}
		}
	}

	/* ���� �ٸ� ���� �پ������� 0���� ����� ���� �����ؾ���. �ƴϸ� �¸� �˻� �Լ��� ���� �������*/
	int count;

	int c = 0;

	for (int i = 0; i < 4; ++i)
	{
		//if (flag)
		//{
		//	cout << i << "  " << Point[i].first << "  " << Point[i].second << "  " << check[i] << endl;
		//	cout << i << "  " << Point[i + 4].first << "  " << Point[i + 4].second << "  " << check[i + 4] << endl;
		//}
		count = Point[i].first + Point[i + 4].first;
		if (5 <= count)
			break;
	}
	/*if (flag)
		cout << "66 : " << foulLine66 << "  " << c << endl;*/


	if (5 <= count)
	{
		if (mPlayer == BlackPlayer)
			return -66;
		if (mPlayer == WhitePlayer)
			return 66;

		return 0;
	}
	else
		return 0;
}

bool LKM::AI::findDefendPoint()
{
	for (int i = 1; i < size - 1; ++i) {
		for (int j = 1; j < size - 1; ++j) {
			if (board[i][j] == enemy) {
				for (int ii = -1; ii <= 1; ++ii) {
					if (board[i + ii][j - 1] == enemy && board[i - ii][j + 1] == enemy) {
						if (testValidity(j - 2, i + ii * 2) && isEmpty(j - 2, i + ii * 2)) {
							now = { j - 2, i + ii * 2 };
							return true;
						}
						else if (testValidity(j + 2, i - ii * 2) && isEmpty(j + 2, i - ii * 2)) {
							now = { j + 2, i - ii * 2 };
							return true;
						}
					}
				}
				if (board[i + 1][j] == enemy && board[i - 1][j] == enemy) {
					if (testValidity(j, i + 2) && isEmpty(j , i + 2)) {
						now = { j, i + 2 };
						return true;
					}
					else if (testValidity(j, i - 2) && isEmpty(j, i - 2)) {
						now = { j, i - 2 };
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool LKM::AI::testValidity(int x, int y)
{
	if (x >= size || x < 0 || y >= size || y < 0)
		return false;
	else
		return true;
}

int LKM::AI::getPointSome(int x, int y)
{
	if (testValidity(x, y)) {
		return -1;
	}
	else {
		return board[y][x];
	}
}

bool LKM::AI::isEmpty(int x, int y)
{
	if (testValidity(x, y)) {
		return board[y][x] == NULL;
	}
	else {
		return false;
	}
}

bool LKM::AI::tacPointAttack()
{
	return false;
}

void LKM::AI::ranPointAttack()
{
	static std::mt19937_64 re;
	static std::uniform_int_distribution<int> uid;
	POINT temp = { uid(re) % size , uid(re) % size };
	int s = 0;
	while (Foul(temp.x, temp.y)) {
		if (s >= size) {
			temp = { uid(re) % size , uid(re) % size };
		}
		temp = { (temp.x + 1) % size , (temp.y + 1) % size };
		s++;
	}
	now = temp;
}

void LKM::AI::seqPointAttack()
{
	POINT temp = { 1, 1 };
	while (Foul(temp.x, temp.y)) {
		temp.x++;
		if (temp.x >= size) {
			temp.x = 1;
			temp.y++;
		}
		if (temp.y >= size) {
			temp = { 0, 0 };
			break;
		}
	}
	now = temp;
}

bool LKM::AI::putStone(int x, int y, int type)
{
	if (testValidity(x, y)) {
		board[y][x] = type;
		return true;
	}
	else
		return false;
}
