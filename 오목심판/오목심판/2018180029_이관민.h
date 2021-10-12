#pragma once
#include "Judgment.h"

namespace LKM {
	class AI {
		const int player;
		const int enemy;
		char board[20][20];
		int map[19][19];
		int size;
		int turn;
		bool bWhite;

		POINT last;
		POINT now;

		POINT lastEnemyAtk;
		POINT enemyAtk;

		bool Foul(int positionX, int positionY);
		int Foul33(int positionX, int positionY, bool flag, int mPlayer);
		int Foul44(int positionX, int positionY, bool flag, int mPlayer);
		int Foul66(int positionX, int positionY, bool flag, int mPlayer);

		bool findDefendPoint();
		bool testValidity(int x, int y);
		int getPointSome(int x, int y);
		bool isEmpty(int x, int y);

		bool tacPointAttack();
		void ranPointAttack();
		void seqPointAttack();
		bool putStone(int x, int y, int type);
	public:
		AI();
		~AI();
		void BlackAttack(int* x, int* y);
		void BlackDefend(int x, int y);
		void WhiteAttack(int* x, int* y);
		void WhiteDefend(int x, int y);
	};

	void BlackAttack(int* x, int* y);
	void BlackDefend(int x, int y);
	void WhiteAttack(int* x, int* y);
	void WhiteDefend(int x, int y);
}