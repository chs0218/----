#include <random>
#include "2018180029_이관민.h"

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

	/* 열린 두개의 삼삼 */
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
				/* 현재 자리에 플레이어 돌이 있다면 */
				if (board[tempY][tempX] == mPlayer)
				{
					/* 현재 빈칸을 지나오지 않았다면 first의 돌을 증가시킨다.*/
					if (empty)
						Point[way].first++;
					else /* 빈칸을 지나왔다면 second 증가. */
						Point[way].second++;
				}
				/* 현재 자리가 빈칸 이라면 */
				else if (board[tempY][tempX] == 0)
				{
					/* 아직 빈칸을 지나오지 않았다면 */
					if (empty)
					{
						/* 빈칸 자리를 저장 */
						emptyPos.first = tempX;
						emptyPos.second = tempY;

						if (flag)
						{
							/* 이 빈칸이 유효한 자리가 아니라면 숫자를 더 이상 세지 않는다. */
							if (Foul44(tempX, tempY, 0, mPlayer) || Foul33(tempX, tempY, 0, mPlayer) || Foul66(tempX, tempY, 0, mPlayer))
							{
								checkWeight[way] = 1.0f;
								break;
							}
							/* 유효한 자리라면 그냥 빈칸을 지나왔다고 표시하고 */
							/* 다음 자리가 상대 돌 이라면 이전에 돌들이 연속되여 있다는 소리기 때문에 공격 포인트가 된다.*/
							else
							{
								//	if (mMap[PosttempY][PosttempX] != 0 && mMap[PosttempY][PosttempX] != mPlayer)
									/* 다음 자리가 벽이 아니라면 상대 돌이면 */
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
						/* 빈자리의 유효성을 확인할때는 빈자리는 그냥 빈자리다. */
						else
							empty = false;
					}
					/* 이미 빈칸을 한번 지나왔다면 */
					else
					{
						/* 빈칸의 다음칸이 다른 플레이어라면 가중치 0.5인 막힘을 표시한다. */
						/* 다음 칸이 빈칸이나 같은 돌이라면 막히지 않았다. */
						if (flag)
						{
							if (board[PosttempY][PosttempX] == mPlayer && board[PretempY][PretempX] == mPlayer)
								board[emptyPos.second][emptyPos.first] = mPlayer;
							/*유효하지 않다면 막힘 체크. */
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
				/* 다른 플레이어 돌을 만났다면  */
				else
				{
					/* 이전 돌이 빈칸이라면 */
					if (board[PretempY][PretempX] == 0)
					{
						/* 빈칸뒤에 다른 돌인데 앞에 놓은 돌이 하나도 없다면 막기 1.5 */
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
			/* 칸을 넘어감. */
			else
			{
				/* 넘어가기 전 돌이 플레이어돌이라면 막힌것을 표시한다.*/
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
	/*닫힌 44도 44다. */
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
				/* 현재 자리에 플레이어 돌이 있다면 */
				if (board[tempY][tempX] == mPlayer)
				{
					/* 현재 빈칸을 지나오지 않았다면 first의 돌을 증가시킨다.*/
					if (empty)
						Point[way].first++;
					else /* 빈칸을 지나왔다면 second 증가. */
						Point[way].second++;
				}
				/* 현재 자리가 빈칸 이라면 */
				else if (board[tempY][tempX] == 0)
				{
					/* 아직 빈칸을 지나오지 않았다면 */
					if (empty)
					{
						/* 빈칸 자리를 저장 */
						emptyPos.first = tempX;
						emptyPos.second = tempY;

						if (flag)
						{
							/* 이 빈칸이 유효한 자리가 아니라면 숫자를 더 이상 세지 않는다. */
							if (Foul44(tempX, tempY, 0, mPlayer) || Foul33(tempX, tempY, 0, mPlayer) || Foul66(tempX, tempY, 0, mPlayer))
							{
								check[way] = true;
								break;
							}
							else
							{
								empty = false;
								/* 빈칸 다음에 플레이어 돌이 있거나 이전에 플레이어 돌이 있으면 (연속된 돌이 된다면) 공격할수 있는 자리라고 생각한다. */
								/* 두칸 연속 빈칸은 소용 없으므로 &&로 걸른다. */
								if ((board[PosttempY][PosttempX] == mPlayer || board[PretempY][PretempX] == mPlayer) && board[PosttempY][PosttempX] != 0)
									attackPoint[way]++;
							}
						}
						/* 빈칸이 유효한 자리라면 빈칸을 지나 왔다고 표시한다. */
						else
							empty = false;
					}
					/* 이미 빈칸을 한번 지나왔다면 */
					else
					{
						/* 이미 지나온 돌의 개수가 2개라면 빈칸에 대한 유효 검사를 해야한다. 여기에 놓을수 없게 되면 막힌걸로 친다. */
						if (Point[way].first + Point[way].second == 2)
						{
							/* 만약 두번째 빈칸 다음칸이 플레이어 돌이라면 이전에 빈칸을 플레이어의 돌로 채워 넣은뒤 검사한다. (6목을 검사하기위해) */
							/* 다음칸에 플레이어돌이 없는데 빈칸에 돌을 두고 반대편 6목으로 인해 문제가 발생할수 있음. */
							if (board[PosttempY][PosttempX] == mPlayer)
							{
								board[emptyPos.second][emptyPos.first] = mPlayer;
							}
							if (flag)
							{						/*유효하지 않다면 막힘 체크. */
								if (Foul44(tempX, tempY, 0, mPlayer) || Foul33(tempX, tempY, 0, mPlayer) || Foul66(tempX, tempY, 0, mPlayer))
									check[way] = true;
							}
							/* 빈칸에 임시로 넣었던 돌을 다시 빈칸으로 만든다. */
							if (board[PosttempY][PosttempX] == mPlayer)
							{
								board[emptyPos.second][emptyPos.first] = 0;
							}
						}
						/* 두번째 빈칸까지 지나온 돌이 3개라면 두번째 빈칸은 유효하던 아니던 상관없다. 첫번째 빈칸의 유효 검사가 필요하다. */
						else if (Point[way].first + Point[way].second == 3)
						{
							/* 유효하지 않다면 첫번째 빈칸 뒤에 돌의 숫자는 무의미하다.*/
							if (flag)
							{
								if (Foul44(tempX, tempY, 0, mPlayer) || Foul33(tempX, tempY, 0, mPlayer) || Foul66(tempX, tempY, 0, mPlayer))
								{
									check[way] = true;
									/* 빈칸 이후의 돌을 0으로 변경. */
									Point[way].second = 0;
								}
							}
						}
						break;
					}
				}
				/* 빈칸도 아니고 내 돌도 아니면 상대방 돌이라는 뜻*/
				else
				{
					check[way] = true;
					break;
				}

			}
			else /* 범위를 넘어간 돌 체크*/
			{
				/*44는 벽에서 한칸 떨어져있으면 굳이 막힘 표시 안해도 될듯함.
				범위를 넘어갔는데 이전에 돌이 플레이어 돌이면 막혔다고 표시한다. */
				if (board[PretempY][PretempX] == mPlayer)
					check[way] = true;

				/* 범위가 넘어갔으니 더이상 이동할 필요 없다. */
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

	/* 옆에 다른 돌이 붙어있을때 0으로 만드는 것을 수정해야함. 아니면 승리 검사 함수를 따로 만들던지*/
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
