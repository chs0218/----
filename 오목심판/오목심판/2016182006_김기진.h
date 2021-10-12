#pragma once

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Judgment.h"

typedef struct _POS_2016182006
{
	int xpos;
	int ypos;
}POS_2016182006;

using namespace std;
void WhiteAttack_2016182006KKJ(int *x, int* y);
void WhiteDefence_2016182006KKJ(int x, int y);
void BlackAttack_2016182006KKJ(int *x, int* y);
void BlackDefence_2016182006KKJ(int x, int y);
int howManyStone_2016182006KKJ();
POS_2016182006 checking_2016182006(int Player);
POS_2016182006 AnalyzeStoneStat_2016182006KKJ(int Player);
int FoulChecking_2016182006KKJ(POS_2016182006 temp);
int BoardInfo_2016182006[MapSize+1][MapSize+1] = { 0 }; //진짜 수의 정보를 담고 있는 배열





POS_2016182006 RuleBase_2016182006KKJ(int Player)
{
	int Nplayer;
	int Scount;
	POS_2016182006 temppos;
	if (Player == WhitePlayer)
	{
		Nplayer = BlackPlayer;

	}
	else
	{
		Nplayer = WhitePlayer;
	}
	Scount = howManyStone_2016182006KKJ();
	temppos = checking_2016182006(Player);
	if (temppos.xpos != -1)
	{
		return temppos;
	}

	for (int i = 0; i < MapSize + 1; i++)
	{

		for(int j=0;j<MapSize+1;j++)
		{
			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i][j + 1] == Nplayer && BoardInfo_2016182006[i][j + 2] == Nplayer)
			{
				if (j + 3 <= MapSize && j > 0)
				{
					if (BoardInfo_2016182006[i][j + 3] == 0 && BoardInfo_2016182006[i][j - 1] == 0)
					{
						POS_2016182006 temp;
						temp.xpos = i;
						temp.ypos = j + 3;
						if (Player == BlackPlayer)
						{
							if (FoulChecking_2016182006KKJ(temp) == false)
							{
								continue;
							}
						}
						return temp;
					}

				}
				
			}


			if (BoardInfo_2016182006[i][j] == 0 && BoardInfo_2016182006[i][j + 1] == Nplayer && BoardInfo_2016182006[i][j + 2] == 0 && BoardInfo_2016182006[i][j + 3] == Nplayer && BoardInfo_2016182006[i][j + 4] == Nplayer
				&&BoardInfo_2016182006[i][j+5]==0)
			{
				POS_2016182006 temp;
				temp.xpos = i;
				temp.ypos = j + 2;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}

			if (BoardInfo_2016182006[i][j] == 0 && BoardInfo_2016182006[i][j + 1] == Nplayer && BoardInfo_2016182006[i][j + 2] == Nplayer && BoardInfo_2016182006[i][j + 3] == 0
				&& BoardInfo_2016182006[i][j + 4] == Nplayer && BoardInfo_2016182006[i][j + 5] == 0)
			{
				POS_2016182006 temp;
				temp.xpos = i;
				temp.ypos = j + 3;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}




			if (BoardInfo_2016182006[i][j] == 0 && BoardInfo_2016182006[i+1][j] == Nplayer && BoardInfo_2016182006[i+2][j] == 0 && BoardInfo_2016182006[i+3][j] == Nplayer && BoardInfo_2016182006[i+4][j] == Nplayer
				&& BoardInfo_2016182006[i+5][j] == 0)
			{
				POS_2016182006 temp;
				temp.xpos = i+2;
				temp.ypos = j;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}

			if (BoardInfo_2016182006[i][j] == 0 && BoardInfo_2016182006[i+1][j] == Nplayer && BoardInfo_2016182006[i+2][j] == Nplayer && BoardInfo_2016182006[i+3][j] == 0
				&& BoardInfo_2016182006[i+4][j] == Nplayer && BoardInfo_2016182006[i+5][j] == 0)
			{
				POS_2016182006 temp;
				temp.xpos = i+3;
				temp.ypos = j;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}



			if (BoardInfo_2016182006[i][j] == 0 && BoardInfo_2016182006[i + 1][j+1] == Nplayer && BoardInfo_2016182006[i + 2][j+2] == 0 && BoardInfo_2016182006[i + 3][j+3] == Nplayer && BoardInfo_2016182006[i + 4][j+4] == Nplayer
				&& BoardInfo_2016182006[i + 5][j+5] == 0)
			{
				POS_2016182006 temp;
				temp.xpos = i + 2;
				temp.ypos = j+2;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}

			if (BoardInfo_2016182006[i][j] == 0 && BoardInfo_2016182006[i + 1][j+1] == Nplayer && BoardInfo_2016182006[i + 2][j+2] == Nplayer && BoardInfo_2016182006[i + 3][j+3] == 0
				&& BoardInfo_2016182006[i + 4][j+4] == Nplayer && BoardInfo_2016182006[i + 5][j+5] == 0)
			{
				POS_2016182006 temp;
				temp.xpos = i + 3;
				temp.ypos = j+3;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}


			if (BoardInfo_2016182006[i][j] == 0 && BoardInfo_2016182006[i -1][j + 1] == Nplayer && BoardInfo_2016182006[i - 2][j + 2] == 0 && BoardInfo_2016182006[i - 3][j + 3] == Nplayer && BoardInfo_2016182006[i - 4][j + 4] == Nplayer
				&& BoardInfo_2016182006[i - 5][j + 5] == 0)
			{
				POS_2016182006 temp;
				temp.xpos = i - 2;
				temp.ypos = j + 2;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}

			if (BoardInfo_2016182006[i][j] == 0 && BoardInfo_2016182006[i - 1][j + 1] == Nplayer && BoardInfo_2016182006[i - 2][j + 2] == Nplayer && BoardInfo_2016182006[i - 3][j + 3] == 0
				&& BoardInfo_2016182006[i - 4][j + 4] == Nplayer && BoardInfo_2016182006[i - 5][j + 5] == 0)
			{
				POS_2016182006 temp;
				temp.xpos = i - 3;
				temp.ypos = j + 3;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}






			if(BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i][j + 1] == Nplayer && BoardInfo_2016182006[i][j + 2] == Nplayer 
				&&BoardInfo_2016182006[i][j+3]==Nplayer)
			{

				if (j + 4 <= MapSize)
				{
					if (BoardInfo_2016182006[i][j + 4] == 0)
					{
						POS_2016182006 temp;
						temp.xpos = i;
						temp.ypos = j + 4;
						if (Player == BlackPlayer)
						{
							if (FoulChecking_2016182006KKJ(temp) == false)
							{
								continue;
							}
						}
						return temp;
					}
				}
				else if (j-1 > 0 && BoardInfo_2016182006[i][j - 1] == 0)
				{
					POS_2016182006 temp;
					temp.xpos = i;
					temp.ypos = j - 1;
					if (Player == BlackPlayer)
					{
						if (FoulChecking_2016182006KKJ(temp) == false)
						{
							continue;
						}
					}
					return temp;
				}

			}







			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i+1][j] == Nplayer && BoardInfo_2016182006[i+2][j] == Nplayer)
			{
				if (i + 3 <= MapSize && i > 0)
				{
					if (BoardInfo_2016182006[i+3][j] == 0 && BoardInfo_2016182006[i-1][j] == 0)
					{
						POS_2016182006 temp;
						temp.xpos = i+3;
						temp.ypos = j;
						if (Player == BlackPlayer)
						{
							if (FoulChecking_2016182006KKJ(temp) == false)
							{
								continue;
							}
						}
						return temp;
					}

				}

			}


			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i + 1][j] == Nplayer && BoardInfo_2016182006[i + 2][j] == Nplayer
				&&BoardInfo_2016182006[i+4][j]==Nplayer)
			{

				if (i + 4 <= MapSize)
				{
					if (BoardInfo_2016182006[i + 4][j] == 0)
					{
						POS_2016182006 temp;
						temp.xpos = i + 4;
						temp.ypos = j;
						if (Player == BlackPlayer)
						{
							if (FoulChecking_2016182006KKJ(temp) == false)
							{
								continue;
							}
						}
						return temp;
					}
				}
				else if (i > 0 && BoardInfo_2016182006[i - 1][j] == 0)
				{
					POS_2016182006 temp;
					temp.xpos = i - 1;
					temp.ypos = j;
					if (Player == BlackPlayer)
					{
						if (FoulChecking_2016182006KKJ(temp) == false)
						{
							continue;
						}
					}
					return temp;
				}

			}







			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i + 1][j+1] == Nplayer && BoardInfo_2016182006[i + 2][j+2] == Nplayer)
			{
				if ((i + 3 <= MapSize && i+3 <= MapSize)&&(i>0&&j>0))
				{
					if (BoardInfo_2016182006[i -1][j-1] == 0 && BoardInfo_2016182006[i + 3][j+3] == 0)
					{
						POS_2016182006 temp;
						temp.xpos = i + 3;
						temp.ypos = j+3;
						if (Player == BlackPlayer)
						{
							if (FoulChecking_2016182006KKJ(temp) == false)
							{
								continue;
							}
						}
						return temp;
					}

				}

			}

			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i + 1][j + 1] == Nplayer && BoardInfo_2016182006[i + 2][j + 2] == Nplayer
				&& BoardInfo_2016182006[i + 3][j + 3] == Nplayer)
			{
				if (i + 4 <= MapSize && j + 4 <= MapSize)
				{
					if (BoardInfo_2016182006[i + 4][j + 4] == 0)
					{
						POS_2016182006 temp;
						temp.xpos = i + 4;
						temp.ypos = j + 4;
						if (Player == BlackPlayer)
						{
							if (FoulChecking_2016182006KKJ(temp) == false)
							{
								continue;
							}
						}
						return temp;
					}
				}
				if (i-1 >= 0 && j-1 >= 0)
				{
					if (BoardInfo_2016182006[i - 1][j - 1] == 0)
					{
						POS_2016182006 temp;
						temp.xpos = i - 1;
						temp.ypos = j - 1;
						if (Player == BlackPlayer)
						{
							if (FoulChecking_2016182006KKJ(temp) == false)
							{
								continue;
							}
						}
						return temp;
					}
				}
			}






			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i - 1][j + 1] == Nplayer && BoardInfo_2016182006[i - 2][j + 2] == Nplayer)
			{
				if ((i + 1 <= MapSize && j > 0) && (i - 3 >= 0 && j + 3 <= MapSize))
				{
					if (BoardInfo_2016182006[i + 1][j - 1] == 0 && BoardInfo_2016182006[i - 3][j + 3] == 0)
					{
						POS_2016182006 temp;
						temp.xpos = i + 1;
						temp.ypos = j - 1;
						if (Player == BlackPlayer)
						{
							if (FoulChecking_2016182006KKJ(temp) == false)
							{
								continue;
							}
						}
						return temp;
					}

				}
			}




			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i - 1][j + 1] == Nplayer && BoardInfo_2016182006[i - 2][j + 2] == Nplayer
				&&BoardInfo_2016182006[i-3][j+3]==Nplayer)
			{
				if (i - 4 >= 0 && j + 4 <= MapSize)
				{
					if (BoardInfo_2016182006[i - 4][j + 4] == 0)
					{
						POS_2016182006 temp;
						temp.xpos = i - 4;
						temp.ypos = j + 4;
						if (Player == BlackPlayer)
						{
							if (FoulChecking_2016182006KKJ(temp) == false)
							{
								continue;
							}
						}
						return temp;
					}
				}
				else if (i + 1 <= MapSize && j - 1 >= 0)
				{
					if (BoardInfo_2016182006[i + 1][j - 1] == 0)
					{
						POS_2016182006 temp;
						temp.xpos = i + 1;
						temp.ypos = j - 1;
						if (Player == BlackPlayer)
						{
							if (FoulChecking_2016182006KKJ(temp) == false)
							{
								continue;
							}
						}
						return temp;
					}
				}
			}







			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i][j + 1] == 0 && BoardInfo_2016182006[i][j + 2] == Nplayer&&BoardInfo_2016182006[i][j+3]==Nplayer
				&&BoardInfo_2016182006[i][j]==Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i;
				temp.ypos = j+1;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}
			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i][j + 1] == Nplayer && BoardInfo_2016182006[i][j + 2] == 0 && BoardInfo_2016182006[i][j + 3] == Nplayer
				&& BoardInfo_2016182006[i][j] == Nplayer)
			{

				POS_2016182006 temp;
				temp.xpos = i;
				temp.ypos = j+2;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;


			}
			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i][j + 1] == Nplayer && BoardInfo_2016182006[i][j + 2] == Nplayer && BoardInfo_2016182006[i][j + 3] == 0
				&& BoardInfo_2016182006[i][j] == Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i;
				temp.ypos = j+3;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}


			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i + 1][j] == 0 && BoardInfo_2016182006[i + 2][j] == Nplayer && BoardInfo_2016182006[i + 3][j] == Nplayer
				&& BoardInfo_2016182006[i + 4][j] == Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i +1;
				temp.ypos = j;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}

			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i + 1][j] == Nplayer && BoardInfo_2016182006[i + 2][j] == 0 && BoardInfo_2016182006[i + 3][j] == Nplayer
				&& BoardInfo_2016182006[i + 4][j] == Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i + 2;
				temp.ypos = j;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}
			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i + 1][j] == Nplayer && BoardInfo_2016182006[i + 2][j] == Nplayer && BoardInfo_2016182006[i + 3][j] == 0
				&& BoardInfo_2016182006[i + 4][j] == Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i + 3;
				temp.ypos = j;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}


			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i + 1][j + 1] == 0 && BoardInfo_2016182006[i + 2][j + 2] == Nplayer && BoardInfo_2016182006[i + 3][j + 3] == Nplayer
				&& BoardInfo_2016182006[i + 4][j + 4] == Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i + 1;
				temp.ypos = j+1;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}
			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i + 1][j + 1] == Nplayer && BoardInfo_2016182006[i + 2][j + 2] == 0 && BoardInfo_2016182006[i + 3][j + 3] == Nplayer
				&& BoardInfo_2016182006[i + 4][j + 4] == Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i + 2;
				temp.ypos = j+2;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}
			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i + 1][j + 1] == Nplayer && BoardInfo_2016182006[i + 2][j + 2] == Nplayer && BoardInfo_2016182006[i + 3][j + 3] == 0
				&& BoardInfo_2016182006[i + 4][j + 4] == Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i + 3;
				temp.ypos = j+3;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}



			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i - 1][j + 1] == 0 && BoardInfo_2016182006[i - 2][j + 2] == Nplayer && BoardInfo_2016182006[i - 3][j + 3] == Nplayer
				&& BoardInfo_2016182006[i - 4][j + 4] == Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i - 1;
				temp.ypos = j + 1;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}
			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i - 1][j + 1] == Nplayer && BoardInfo_2016182006[i - 2][j + 2] == 0 && BoardInfo_2016182006[i - 3][j + 3] == Nplayer
				&& BoardInfo_2016182006[i - 4][j + 4] == Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i - 2;
				temp.ypos = j + 2;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}

			if (BoardInfo_2016182006[i][j] == Nplayer && BoardInfo_2016182006[i - 1][j + 1] == Nplayer && BoardInfo_2016182006[i - 2][j + 2] == Nplayer && BoardInfo_2016182006[i - 3][j + 3] == 0
				&& BoardInfo_2016182006[i - 4][j + 4] == Nplayer)
			{
				POS_2016182006 temp;
				temp.xpos = i - 3;
				temp.ypos = j + 3;
				if (Player == BlackPlayer)
				{
					if (FoulChecking_2016182006KKJ(temp) == false)
					{
						continue;
					}
				}
				return temp;
			}
			
		}
	}
	
	if (Scount <= 2)
	{
		srand(time(NULL));
		int tempx;
		int tempy;
		while (1)
		{
			tempx = rand() % 3 + 8;
			tempy = rand() % 3 + 8;

			if (BoardInfo_2016182006[tempx][tempy] == 0)
			{
				POS_2016182006 temp;
				temp.xpos = tempx;
				temp.ypos = tempy;
				return temp;
			}
		}
	}

	else
	{
		return AnalyzeStoneStat_2016182006KKJ(Player);
	}

}






void WhiteAttack_2016182006KKJ(int *x, int* y)
{
	POS_2016182006 tempStone;
	tempStone= RuleBase_2016182006KKJ(WhitePlayer);
	*x = tempStone.xpos;
	*y = tempStone.ypos;


	BoardInfo_2016182006[*x][*y] = WhitePlayer;
	
}

void WhiteDefence_2016182006KKJ(int x, int y)
{
	BoardInfo_2016182006[x][y] = BlackPlayer;

}


void BlackAttack_2016182006KKJ(int *x, int* y)
{
	POS_2016182006 tempStone;
	tempStone = RuleBase_2016182006KKJ(BlackPlayer);
	*x = tempStone.xpos;
	*y = tempStone.ypos;

	BoardInfo_2016182006[*x][*y] = BlackPlayer;
}



void BlackDefence_2016182006KKJ(int x, int y)
{
	BoardInfo_2016182006[x][y] = WhitePlayer;
}

void mytestAttack(int *x, int* y)
{
	POS_2016182006 tempStone;
	cin >> tempStone.xpos;
	cin >> tempStone.ypos;
	*x = tempStone.xpos;
	*y = tempStone.ypos;

	BoardInfo_2016182006[*x][*y] = BlackPlayer;
}



void myTestDefence(int x, int y)
{
	BoardInfo_2016182006[x][y] = WhitePlayer;
}



int howManyStone_2016182006KKJ()
{
	int count = 0;
	for (int i = 0; i < MapSize+1; i++)
	{
		for (int j = 0; j < MapSize + 1; j++)
		{
			if (BoardInfo_2016182006[i][j] != 0)
			{
				count++;
			}
		}
	}
	return count;
}

POS_2016182006 AnalyzeStoneStat_2016182006KKJ(int Player)
{
	int Nplayer;
	int StoneCount = 0;
	int TempCount = 0;
	POS_2016182006 TempPos;

	int temp = 0;
	if (Player == WhitePlayer)
	{
		Nplayer = BlackPlayer;

	}
	else
	{
		Nplayer = WhitePlayer;
	}
	
	for (int i = 0; i < MapSize + 1; i++)
	{
		for (int j = 0; j < MapSize + 1; j++)
		{
			if (BoardInfo_2016182006[i][j] == 0)
			{
				if (j+1 <= MapSize)
				{
					if (BoardInfo_2016182006[i][j + 1] == Player)
					{
						TempCount += 100;
					}
					if (BoardInfo_2016182006[i][j + 1] == 0)
					{
						TempCount += 25;
					}
					else if(BoardInfo_2016182006[i][j+1]==Nplayer)
					{
						TempCount -= 100;
					}
				
				}
				if (j - 1 >= 0)
				{
					if (BoardInfo_2016182006[i][j - 1] == Player)
					{
						TempCount += 100;
					}
					if (BoardInfo_2016182006[i][j - 1] == 0)
					{
						TempCount += 25;
					}
					else if (BoardInfo_2016182006[i][j-1]==Nplayer)
					{
						TempCount -= 100;
					}
				}
			
				if (i + 1 <= MapSize)
				{
					if (BoardInfo_2016182006[i+1][j] == Player)
					{
						TempCount += 100;
					}
					if (BoardInfo_2016182006[i+1][j] == 0)
					{
						TempCount += 25;
					}
					else if(BoardInfo_2016182006[i+1][j]==Nplayer)
					{
						TempCount -= 100;
					}
				}

				if (i -1 >=0)
				{
					if (BoardInfo_2016182006[i - 1][j] == Player)
					{
						TempCount += 100;
					}
					if (BoardInfo_2016182006[i-1][j] == 0)
					{
						TempCount += 25;
					}
					else if(BoardInfo_2016182006[i-1][j]==Nplayer)
					{
						TempCount -= 100;
					}
				}

				if (i + 1 <= MapSize && j + 1 <= MapSize)
				{
					if (BoardInfo_2016182006[i + 1][j + 1] == Player)
					{
						TempCount += 100;
					}
					if (BoardInfo_2016182006[i+1][j + 1] == 0)
					{
						TempCount += 25;
					}
					else if(BoardInfo_2016182006[i+1][j+1]==Nplayer)
					{
						TempCount -= 100;
					}
				}

				if (i - 1 >= 0 && j - 1 >= 0)
				{
					if (BoardInfo_2016182006[i - 1][j - 1] == Player)
					{
						TempCount += 100;
					}
					if (BoardInfo_2016182006[i-1][j-1] == 0)
					{
						TempCount += 25;
					}
					else if(BoardInfo_2016182006[i-1][j-1]==Nplayer)
					{
						TempCount -= 100;
					}
				}

				if (i + 1 <= MapSize && j - 1 >= 0)
				{
					if (BoardInfo_2016182006[i + 1][j - 1] == Player)
					{
						TempCount += 100;
					}
					if (BoardInfo_2016182006[i+1][j- 1] == 0)
					{
						TempCount += 25;
					}
					else if(BoardInfo_2016182006[i+1][j-1]==Nplayer)
					{
						TempCount -= 100;
					}
				}
				 
				if (i - 1 >= 0 && j + 1 <= MapSize)
				{
					if (BoardInfo_2016182006[i - 1][j + 1] == Player)
					{
						TempCount += 100;
					}
					if (BoardInfo_2016182006[i-1][j + 1] == 0)
					{
						TempCount += 25;
					}
					else if(BoardInfo_2016182006[i-1][j+1]==Nplayer)
					{
						TempCount -= 100;
					}
				}

				if (TempCount >= StoneCount)
				{
					TempPos.xpos = i;
					TempPos.ypos = j;

					if (Player == BlackPlayer)
					{
						if (FoulChecking_2016182006KKJ(TempPos) == false)
						{
							continue;
						}
					}
					StoneCount = TempCount;
				}
				TempCount = 0;

			}
		}
	}
	
		return TempPos;
	
}





int FoulChecking_2016182006KKJ(POS_2016182006 temp)
{
	int count = 0;
	int BoardTemp[MapSize + 1][MapSize + 1];
	for (int i = 0; i < MapSize + 1; i++)
	{
		for (int j = 0; j < MapSize + 1; j++)
		{
			BoardTemp[i][j] = BoardInfo_2016182006[i][j];
		}
	}
	BoardTemp[temp.xpos][temp.ypos] = BlackPlayer;



	for (int i = 0; i < MapSize + 1; i++)
	{
		for (int j = 0; j < MapSize + 1; j++)
		{
			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j] == 0 && BoardTemp[i + 2][j] == BlackPlayer && BoardTemp[i + 3][j] == BlackPlayer && BoardTemp[i + 4][j] == BlackPlayer
				&& BoardTemp[i + 5][j] == 0 && BoardTemp[i + 6][j] == 0) // XXOOOXX 한수 허용하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j] == BlackPlayer && BoardTemp[i + 2][j] == 0 && BoardTemp[i + 3][j] == BlackPlayer && BoardTemp[i + 4][j] == BlackPlayer
				&& BoardTemp[i + 5][j] == 0)//XOXOOX 한수 허용 하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j] == BlackPlayer && BoardTemp[i + 2][j] == BlackPlayer && BoardTemp[i + 3][j] == 0 && BoardTemp[i + 4][j] == BlackPlayer
				&& BoardTemp[i + 5][j] == 0)//XOOXOX
			{
				count++;
			}

			





			if (BoardTemp[i][j] == 0 && BoardTemp[i][j + 1] == 0 && BoardTemp[i][j + 2] == BlackPlayer && BoardTemp[i][j + 3] == BlackPlayer && BoardTemp[i][j + 4] == BlackPlayer
				&& BoardTemp[i][j + 5] == 0 && BoardTemp[i + 6][j] == 0) // XXOOOXX 한수 허용하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i][j + 1] == BlackPlayer && BoardTemp[i][j + 2] == 0 && BoardTemp[i][j + 3] == BlackPlayer && BoardTemp[i][j + 4] == BlackPlayer
				&& BoardTemp[i][j + 5] == 0)//XOXOOX 한수 허용 하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i][j + 1] == BlackPlayer && BoardTemp[i][j + 2] == BlackPlayer && BoardTemp[i][j + 3] == 0 && BoardTemp[i][j + 4] == BlackPlayer
				&& BoardTemp[i][j + 5] == 0)//XOOXOX
			{
				count++;
			}





			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j + 1] == 0 && BoardTemp[i + 2][j + 2] == BlackPlayer && BoardTemp[i + 3][j + 3] == BlackPlayer && BoardTemp[i + 4][j + 4] == BlackPlayer
				&& BoardTemp[i + 5][j + 5] == 0 && BoardTemp[i + 6][j + 6] == 0) // XXOOOXX 한수 허용하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j + 1] == BlackPlayer && BoardTemp[i + 2][j + 2] == 0 && BoardTemp[i + 3][j + 3] == BlackPlayer && BoardTemp[i + 4][j + 4] == BlackPlayer
				&& BoardTemp[i + 5][j + 5] == 0)//XOXOOX 한수 허용 하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j + 1] == BlackPlayer && BoardTemp[i + 2][j + 2] == BlackPlayer && BoardTemp[i + 3][j + 3] == 0 && BoardTemp[i + 4][j + 4] == BlackPlayer
				&& BoardTemp[i + 5][j + 5] == 0)//XOOXOX
			{
				count++;
			}



			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j - 1] == 0 && BoardTemp[i + 2][j - 2] == BlackPlayer && BoardTemp[i + 3][j - 3] == BlackPlayer && BoardTemp[i + 4][j - 4] == BlackPlayer
				&& BoardTemp[i + 5][j - 5] == 0 && BoardTemp[i + 6][j - 6] == 0) // XXOOOXX 한수 허용하면 열린사 
			{
				count++;

			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j - 1] == BlackPlayer && BoardTemp[i + 2][j - 2] == 0 && BoardTemp[i + 3][j - 3] == BlackPlayer && BoardTemp[i + 4][j - 4] == BlackPlayer
				&& BoardTemp[i + 5][j - 5] == 0)//XOXOOX 한수 허용 하면 열린사 
			{
				count++;

			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j - 1] == BlackPlayer && BoardTemp[i + 2][j - 2] == BlackPlayer && BoardTemp[i + 3][j - 3] == 0 && BoardTemp[i + 4][j - 4] == BlackPlayer
				&& BoardTemp[i + 5][j - 5] == 0)//XOOXOX
			{
				count++;

			}



		}
	}
	if (count >= 2)
	{
		return false;
	}
	else
		return true;
	
}

int FoulCheck_2016182006KKJ(POS_2016182006 temp)
{
	int count = 0;
	int BoardTemp[MapSize + 1][MapSize + 1];
	for (int i = 0; i < MapSize + 1; i++)
	{
		for (int j = 0; j < MapSize + 1; j++)
		{
			BoardTemp[i][j] = BoardInfo_2016182006[i][j];
		}
	}
	BoardTemp[temp.xpos][temp.ypos] = BlackPlayer;



	for (int i = 0; i < MapSize + 1; i++)
	{
		for (int j = 0; j < MapSize + 1; j++)
		{
			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j] == 0 && BoardTemp[i + 2][j] == BlackPlayer && BoardTemp[i + 3][j] == BlackPlayer && BoardTemp[i + 4][j] == BlackPlayer
				&& BoardTemp[i + 5][j] == 0 && BoardTemp[i + 6][j] == 0) // XXOOOXX 한수 허용하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j] == BlackPlayer && BoardTemp[i + 2][j] == 0 && BoardTemp[i + 3][j] == BlackPlayer && BoardTemp[i + 4][j] == BlackPlayer
				&& BoardTemp[i + 5][j] == 0)//XOXOOX 한수 허용 하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j] == BlackPlayer && BoardTemp[i + 2][j] == BlackPlayer && BoardTemp[i + 3][j] == 0 && BoardTemp[i + 4][j] == BlackPlayer
				&& BoardTemp[i + 5][j] == 0)//XOOXOX
			{
				count++;
			}

			





			if (BoardTemp[i][j] == 0 && BoardTemp[i][j + 1] == 0 && BoardTemp[i][j + 2] == BlackPlayer && BoardTemp[i][j + 3] == BlackPlayer && BoardTemp[i][j + 4] == BlackPlayer
				&& BoardTemp[i][j + 5] == 0 && BoardTemp[i + 6][j] == 0) // XXOOOXX 한수 허용하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i][j + 1] == BlackPlayer && BoardTemp[i][j + 2] == 0 && BoardTemp[i][j + 3] == BlackPlayer && BoardTemp[i][j + 4] == BlackPlayer
				&& BoardTemp[i][j + 5] == 0)//XOXOOX 한수 허용 하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i][j + 1] == BlackPlayer && BoardTemp[i][j + 2] == BlackPlayer && BoardTemp[i][j + 3] == 0 && BoardTemp[i][j + 4] == BlackPlayer
				&& BoardTemp[i][j + 5] == 0)//XOOXOX
			{
				count++;
			}





			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j + 1] == 0 && BoardTemp[i + 2][j + 2] == BlackPlayer && BoardTemp[i + 3][j + 3] == BlackPlayer && BoardTemp[i + 4][j + 4] == BlackPlayer
				&& BoardTemp[i + 5][j + 5] == 0 && BoardTemp[i + 6][j + 6] == 0) // XXOOOXX 한수 허용하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j + 1] == BlackPlayer && BoardTemp[i + 2][j + 2] == 0 && BoardTemp[i + 3][j + 3] == BlackPlayer && BoardTemp[i + 4][j + 4] == BlackPlayer
				&& BoardTemp[i + 5][j + 5] == 0)//XOXOOX 한수 허용 하면 열린사 
			{
				count++;
			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j + 1] == BlackPlayer && BoardTemp[i + 2][j + 2] == BlackPlayer && BoardTemp[i + 3][j + 3] == 0 && BoardTemp[i + 4][j + 4] == BlackPlayer
				&& BoardTemp[i + 5][j + 5] == 0)//XOOXOX
			{
				count++;
			}



			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j - 1] == 0 && BoardTemp[i + 2][j - 2] == BlackPlayer && BoardTemp[i + 3][j - 3] == BlackPlayer && BoardTemp[i + 4][j - 4] == BlackPlayer
				&& BoardTemp[i + 5][j - 5] == 0 && BoardTemp[i + 6][j - 6] == 0) // XXOOOXX 한수 허용하면 열린사 
			{
				count++;

			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j - 1] == BlackPlayer && BoardTemp[i + 2][j - 2] == 0 && BoardTemp[i + 3][j - 3] == BlackPlayer && BoardTemp[i + 4][j - 4] == BlackPlayer
				&& BoardTemp[i + 5][j - 5] == 0)//XOXOOX 한수 허용 하면 열린사 
			{
				count++;

			}

			if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j - 1] == BlackPlayer && BoardTemp[i + 2][j - 2] == BlackPlayer && BoardTemp[i + 3][j - 3] == 0 && BoardTemp[i + 4][j - 4] == BlackPlayer
				&& BoardTemp[i + 5][j - 5] == 0)//XOOXOX
			{
				count++;

			}



		}
	}
	if (count >= 2)
	{
		return false;
	}
	else
		return true;
	
}



POS_2016182006 checking_2016182006(int Player)
{
	POS_2016182006 temppos;
	POS_2016182006 Garbage;
	Garbage.xpos = -1;
	Garbage.ypos = -1;
	int Nplayer;
	if (Player == BlackPlayer)
	{
		Nplayer = WhitePlayer;
	}
	else
	{
		Nplayer = BlackPlayer;
	}


	int count = 0;
	int BoardTemp[MapSize + 1][MapSize + 1];
	for (int i = 0; i < MapSize + 1; i++)
	{
		for (int j = 0; j < MapSize + 1; j++)
		{
			BoardTemp[i][j] = BoardInfo_2016182006[i][j];
		}
	}
	

	for (int k = 0; k < MapSize + 1; k++)
	{
		for (int j = 0; j < MapSize + 1; j++)
		{
			BoardTemp[k][j] = Nplayer;
			for (int i = 0; i < MapSize + 1; i++)
			{
				for (int j = 0; j < MapSize + 1; j++)
				{

					if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j] == 0 && BoardTemp[i + 2][j] == Nplayer && BoardTemp[i + 3][j] == Nplayer && BoardTemp[i + 4][j] == Nplayer
						&& BoardTemp[i + 5][j] == 0 && BoardTemp[i + 6][j] == 0) // XXOOOXX 한수 허용하면 열린사 
					{
						count++;
					}

					if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j] == Nplayer && BoardTemp[i + 2][j] == 0 && BoardTemp[i + 3][j] == Nplayer && BoardTemp[i + 4][j] == Nplayer
						&& BoardTemp[i + 5][j] == 0)//XOXOOX 한수 허용 하면 열린사 
					{
						count++;
					}

					if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j] == Nplayer && BoardTemp[i + 2][j] == Nplayer && BoardTemp[i + 3][j] == 0 && BoardTemp[i + 4][j] == Nplayer
						&& BoardTemp[i + 5][j] == 0)//XOOXOX
					{
						count++;
					}







					if (BoardTemp[i][j] == 0 && BoardTemp[i][j + 1] == 0 && BoardTemp[i][j + 2] == Nplayer && BoardTemp[i][j + 3] == Nplayer && BoardTemp[i][j + 4] == Nplayer
						&& BoardTemp[i][j + 5] == 0 && BoardTemp[i + 6][j] == 0) // XXOOOXX 한수 허용하면 열린사 
					{
						count++;
					}

					if (BoardTemp[i][j] == 0 && BoardTemp[i][j + 1] == Nplayer && BoardTemp[i][j + 2] == 0 && BoardTemp[i][j + 3] == Nplayer && BoardTemp[i][j + 4] == Nplayer
						&& BoardTemp[i][j + 5] == 0)//XOXOOX 한수 허용 하면 열린사 
					{
						count++;
					}

					if (BoardTemp[i][j] == 0 && BoardTemp[i][j + 1] == Nplayer && BoardTemp[i][j + 2] == Nplayer && BoardTemp[i][j + 3] == 0 && BoardTemp[i][j + 4] == Nplayer
						&& BoardTemp[i][j + 5] == 0)//XOOXOX
					{
						count++;
					}





					if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j + 1] == 0 && BoardTemp[i + 2][j + 2] == Nplayer && BoardTemp[i + 3][j + 3] == Nplayer && BoardTemp[i + 4][j + 4] == Nplayer
						&& BoardTemp[i + 5][j + 5] == 0 && BoardTemp[i + 6][j + 6] == 0) // XXOOOXX 한수 허용하면 열린사 
					{
						count++;
					}

					if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j + 1] == Nplayer && BoardTemp[i + 2][j + 2] == 0 && BoardTemp[i + 3][j + 3] == Nplayer && BoardTemp[i + 4][j + 4] == Nplayer
						&& BoardTemp[i + 5][j + 5] == 0)//XOXOOX 한수 허용 하면 열린사 
					{
						count++;
					}

					if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j + 1] == Nplayer && BoardTemp[i + 2][j + 2] == Nplayer && BoardTemp[i + 3][j + 3] == 0 && BoardTemp[i + 4][j + 4] == Nplayer
						&& BoardTemp[i + 5][j + 5] == 0)//XOOXOX
					{
						count++;
					}



					if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j - 1] == 0 && BoardTemp[i + 2][j - 2] == Nplayer && BoardTemp[i + 3][j - 3] == Nplayer && BoardTemp[i + 4][j - 4] == Nplayer
						&& BoardTemp[i + 5][j - 5] == 0 && BoardTemp[i + 6][j - 6] == 0) // XXOOOXX 한수 허용하면 열린사 
					{
						count++;

					}

					if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j - 1] == Nplayer && BoardTemp[i + 2][j - 2] == 0 && BoardTemp[i + 3][j - 3] == Nplayer && BoardTemp[i + 4][j - 4] == Nplayer
						&& BoardTemp[i + 5][j - 5] == 0)//XOXOOX 한수 허용 하면 열린사 
					{
						count++;

					}

					if (BoardTemp[i][j] == 0 && BoardTemp[i + 1][j - 1] == Nplayer && BoardTemp[i + 2][j - 2] == Nplayer && BoardTemp[i + 3][j - 3] == 0 && BoardTemp[i + 4][j - 4] == Nplayer
						&& BoardTemp[i + 5][j - 5] == 0)//XOOXOX
					{
						count++;

					}
					if (count >= 2)
					{
						temppos.xpos = i;
						temppos.ypos = j;
						return temppos;
					}



				}
			}
		}
	}
	
	return Garbage;
	

}














