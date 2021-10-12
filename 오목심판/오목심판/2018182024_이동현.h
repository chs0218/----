#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <random>

// 오목 19*19 판



int LDH_Board[19][19] = { 0, };

// 내돌 1  상대방돌 2   힌트 3   경고 4   공격 5   끝내기 6

typedef struct Stone {
	int x;
	int y;
}Hint;

typedef struct CStone {
	int count;
}Check;

int hstack_ldh = 0;
int wstack_ldh = 0;


Hint Hint_ldh[100];			// 막아야 할곳이 저장되는 스택		채울 공간을 가리킴
Hint Warning_ldh[20];		// 바로 막아야 할 곳이 저장되는 스택	채울 공간을 가리킴

Check Check_ldh[13][13];

int checky_ldh = 0;
int checkx_ldh = 0;
int maxstone_ldh = 0;

int checkstone_ldh = 9;

void BlackAttack_2018182024(int *x, int *y)
{
	int rx, ry;

	hstack_ldh = 0;				// 매번 검사시작 할때마다 스택을 0으로 만듬
	wstack_ldh = 0;	
	checkx_ldh = 0;
	checky_ldh = 0;
	checkstone_ldh = 0;


	srand((unsigned int)time(NULL));

	if (LDH_Board[13][13] == 0) {			// 맨 처음엔 가운데 둠		13,13 가 비어있는지 판단함 비어있지 않으면 맨 처음 둘 차례가 아님
		*x = 13;
		*y = 13;

		LDH_Board[13][13] = 1;
	}

	else {								// 첫턴이 아니라면


		// ---------- 가로 검사 ------------------

		for (int dy = 0; dy < 19; dy++) {					// 백돌 가로 검사
			for (int dx = 0; dx < 19; dx++) {

				if (LDH_Board[dy][dx] == 2) {									// 백돌이 있다면

					if (dx < 18 && LDH_Board[dy][dx + 1] == 2) {						// 백돌 현재 2개 연속

						if (dx < 17 && LDH_Board[dy][dx + 2] == 2) {						//  백돌 @ @ @

							if (dx < 16 && LDH_Board[dy][dx + 3] == 2) {		// 백돌 @ @ @ @

								if (dx == 0 && (LDH_Board[dy][dx + 4] == 0 || LDH_Board[dy][dx + 4] == 3)) {		// 왼쪽 벽에 붙은  @ @ @ @
									LDH_Board[dy][dx + 4] = 4;

									Warning_ldh[wstack_ldh].x = dx + 4;		// 스택에 저장
									Warning_ldh[wstack_ldh].y = dy;
									wstack_ldh++;
								}

								else if (dx == 15 && (LDH_Board[dy][dx - 1] == 0 || LDH_Board[dy][dx - 1] == 3)) {	// 오른쪽 벽에 붙은 @ @ @ @
									LDH_Board[dy][dx - 1] = 4;

									Warning_ldh[wstack_ldh].x = dx - 1;
									Warning_ldh[wstack_ldh].y = dy;
									wstack_ldh++;
								}

								else if (dx > 0 && dx < 15) {												// 벽에 붙지 않은 @ @ @ @
									if (LDH_Board[dy][dx - 1] == 0 || LDH_Board[dy][dx - 1] == 3) {				// 왼쪽이 빔
										LDH_Board[dy][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}

									if (LDH_Board[dy][dx + 4] == 0 || LDH_Board[dy][dx + 4] == 3) {				// 오른쪽이 빔
										LDH_Board[dy][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}
								}

							}		// 4개 연속 닫음

							// ----------- 3개 연속 ---------------- //

							if (dx < 15 && LDH_Board[dy][dx + 4] == 2) {			// @ @ @ 0 @ 상태
								
								if (dx == 0) {			// 왼쪽 벽에 붙은 @ @ @ 0 @
									if (LDH_Board[dy][dx + 3] == 0 || LDH_Board[dy][dx + 3] == 3) {
										LDH_Board[dy][dx + 3] = 4;

										Warning_ldh[wstack_ldh].x = dx + 3;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}
								}

								else {						// 오른쪽 벽에 붙은 @ @ @ 0 @ or 벽에 붙지 않은 @ @ @ 0 @
									if (LDH_Board[dy][dx + 3] == 0 || LDH_Board[dy][dx + 3] == 3) {
										LDH_Board[dy][dx + 3] = 4;

										Warning_ldh[wstack_ldh].x = dx + 3;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}

									if (LDH_Board[dy][dx - 1] == 0) {
										LDH_Board[dy][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}

							}		// @ @ @ 0 @ 상태 검사 닫음

							else {			 // @ @ @ 상태		@ @ @ 의 두칸 오른쪽은 백돌 이 아님

								if (dx == 0) {							// 왼쪽 벽에 붙은 @ @ @	

									if (LDH_Board[dy][dx + 3] == 0) {		// 오른쪽이 비어있음
										LDH_Board[dy][dx + 3] = 3;

										Hint_ldh[hstack_ldh].x = dx + 3;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}

								else if (dx == 16) {					// 오른쪽 벽에 붙은 @ @ @

									if (LDH_Board[dy][dx - 1] == 0) {		// 왼쪽이 비어있음
										LDH_Board[dy][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}

								else if (dx > 0 && dx < 16) {									// 벽에 붙지 않은 @ @ @

									if (LDH_Board[dy][dx + 3] == 0) {		// 오른쪽이 비어있음
										LDH_Board[dy][dx + 3] = 3;

										Hint_ldh[hstack_ldh].x = dx + 3;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}

									if (LDH_Board[dy][dx - 1] == 0) {		// 왼쪽이 비어있음
										LDH_Board[dy][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}
							}

						}		// 3개 연속된것 검사 닫음

						else if (dx < 16 && LDH_Board[dy][dx+3] == 2) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

							if (dx < 15 && LDH_Board[dy][dx + 4] == 2 && (LDH_Board[dy][dx + 2] == 0 || LDH_Board[dy][dx + 2] == 3)) {		// @ @ 0 @ @ 상황 일 때
								LDH_Board[dy][dx + 2] = 4;

								Warning_ldh[wstack_ldh].x = dx + 2;
								Warning_ldh[wstack_ldh].y = dy;
								wstack_ldh++;
							}

							else if (dx == 0 && LDH_Board[dy][dx + 2] == 0) {		// 왼쪽이 벽인 @ @ 0 @								 왼쪽이 벽이고 사이가 비어있어야 체크함
							
								if (LDH_Board[dy][dx + 4] == 0) {			// @ @ 0 @ 의 오른쪽이 비어있으면
									LDH_Board[dy][dx + 4] = 3;

									Hint_ldh[hstack_ldh].x = dx + 4;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}
							}

							else if ((dx == 15) && LDH_Board[dy][dx + 2] == 0) {	// 오른쪽이 벽인 @ @ 0 @
								
								if (LDH_Board[dy][dx - 1] == 0) {				// @ @ 0 @ 의 왼쪽이 비어있으면
									LDH_Board[dy][dx - 1] = 3;

									Hint_ldh[hstack_ldh].x = dx - 1;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}
							}

							else if (dx > 0 && dx < 15) {				// 벽에 막히지 않은 @ @ 0 @
																		// @ @ 0 @ 에서 막힌 곳이 없다면 !로 만듬
								if (LDH_Board[dy][dx - 1] == 0) {
									LDH_Board[dy][dx - 1] = 3;

									Hint_ldh[hstack_ldh].x = dx - 1;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}

								if (LDH_Board[dy][dx + 2] == 0) {
									LDH_Board[dy][dx + 2] = 3;

									Hint_ldh[hstack_ldh].x = dx + 2;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}

								if (LDH_Board[dy][dx + 4] == 0) {
									LDH_Board[dy][dx + 4] = 3;

									Hint_ldh[hstack_ldh].x = dx + 4;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}
							}

						}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음
						

					}		// 2개 연속 닫음

					// ------------------- 1개 후 연속 검사 ------------

					else if (dx < 18 && LDH_Board[dy][dx + 1] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??
						
						if (dx < 17 && LDH_Board[dy][dx + 2] == 2) {		// @ 0 @ 상태

							if (dx < 16 && LDH_Board[dy][dx + 3] == 2) {		// @ 0 @ @ 상태

								if (dx < 15 && LDH_Board[dy][dx + 4] == 2) {		// @ 0 @ @ @ 상태

									if (LDH_Board[dy][dx + 1] == 0 || LDH_Board[dy][dx + 1] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
										LDH_Board[dy][dx + 1] = 4;

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;

										// 위에 3칸 검사에서 다음걸 검사하므로 dx+5가 비어있는지 검사할 필요 x
									}

								}		//  @ 0 @ @ @ 상태 검사 닫음

								else if (dx < 16) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

									if (dx == 0) {				// 왼쪽 벽에 붙은 @ 0 @ @
										
										if (LDH_Board[dy][dx + 4] == 0) {				// 오른쪽을 막으면 아예 막히므로 오른쪽만 검사
											LDH_Board[dy][dx + 4] = 3;

											Hint_ldh[hstack_ldh].x = dx + 4;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

									}

									else if (dx == 15) {		// 오른쪽 벽에 붙은 @ 0 @ @

										if (LDH_Board[dy][dx - 1] == 0) {				// 왼쪽을 막으면 아예 막히므로 오른쪽만 검사
											LDH_Board[dy][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

									}

									else if (dx > 0 && dx < 15) {						// 벽에 붙지 않은 @ 0 @ @

										if (LDH_Board[dy][dx - 1] == 0) {	
											LDH_Board[dy][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

										if (LDH_Board[dy][dx + 4] == 0) {	
											LDH_Board[dy][dx + 4] = 3;

											Hint_ldh[hstack_ldh].x = dx + 4;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

										if (LDH_Board[dy][dx + 1] == 0) {
											LDH_Board[dy][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

									}

								}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


							} // @ 0 @ @ 상태 검사 닫음

						}	// @ 0 @ 상태 검사 닫음

					}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

				}		// 1개 연속 닫음


			}
		}

		// ---------- 가로 검사 ------------------



		// ---------- 세로 검사 ------------------

		for (int dx = 0; dx < 19; dx++) {					// 백돌 세로 검사
			for (int dy = 0; dy < 19; dy++) {

				if (LDH_Board[dy][dx] == 2) {									// 백돌이 있다면

					if (dy < 18 && LDH_Board[dy + 1][dx] == 2) {						// 백돌 현재 2개 연속

						if (dy < 17 && LDH_Board[dy + 2][dx] == 2) {						//  백돌 @ @ @

							if (dy < 16 && LDH_Board[dy + 3][dx] == 2) {		// 백돌 @ @ @ @

								if (dy == 0 && (LDH_Board[dy + 4][dx] == 0 || LDH_Board[dy + 4][dx] == 3)) {		// 위쪽 벽에 붙은  @ @ @ @
									LDH_Board[dy + 4][dx] = 4;

									Warning_ldh[wstack_ldh].x = dx;		// 스택에 저장
									Warning_ldh[wstack_ldh].y = dy + 4;
									wstack_ldh++;
								}

								else if (dy == 15 && (LDH_Board[dy - 1][dx] == 0 || LDH_Board[dy - 1][dx] == 3)) {	// 아래쪽 벽에 붙은 @ @ @ @
									LDH_Board[dy - 1][dx] = 4;

									Warning_ldh[wstack_ldh].x = dx;
									Warning_ldh[wstack_ldh].y = dy - 1;
									wstack_ldh++;
								}

								else if (dy > 0 && dy < 15) {												// 벽에 붙지 않은 @ @ @ @
									if (LDH_Board[dy - 1][dx] == 0 || LDH_Board[dy - 1][dx] == 3) {				// 위쪽이 빔
										LDH_Board[dy - 1][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx] == 0 || LDH_Board[dy + 4][dx] == 3) {				// 아래쪽이 빔
										LDH_Board[dy + 4][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}
								}

							}		// 4개 연속 닫음

							// ----------- 3개 연속 ---------------- //

							if (dy < 15 && LDH_Board[dy + 4][dx] == 2) {			// @ @ @ 0 @ 상태

								if (dy == 0) {			// 위쪽 벽에 붙은 @ @ @ 0 @
									if (LDH_Board[dy + 3][dx] == 0 || LDH_Board[dy + 3][dx] == 3) {
										LDH_Board[dy + 3][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 3;
										wstack_ldh++;
									}
								}

								else {						// 아래쪽 벽에 붙은 @ @ @ 0 @ or 벽에 붙지 않은 @ @ @ 0 @
									if (LDH_Board[dy + 3][dx] == 0 || LDH_Board[dy + 3][dx] == 3) {
										LDH_Board[dy + 3][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 3;
										wstack_ldh++;
									}

									if (LDH_Board[dy - 1][dx] == 0) {
										LDH_Board[dy - 1][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

							}		// @ @ @ 0 @ 상태 검사 닫음

							else {			 // @ @ @ 상태

								if (dy == 0) {							// 위쪽 벽에 붙은 @ @ @	

									if (LDH_Board[dy + 3][dx] == 0) {		// 아래쪽이 비어있음
										LDH_Board[dy + 3][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy + 3;
										hstack_ldh++;
									}
								}

								else if (dy == 16) {					// 아래쪽 벽에 붙은 @ @ @

									if (LDH_Board[dy - 1][dx] == 0) {		// 위쪽이 비어있음
										LDH_Board[dy - 1][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dy < 16) {									// 벽에 붙지 않은 @ @ @

									if (LDH_Board[dy + 3][dx] == 0) {		// 아래쪽이 비어있음
										LDH_Board[dy + 3][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy + 3;
										hstack_ldh++;
									}

									if (LDH_Board[dy - 1][dx] == 0) {		// 위쪽이 비어있음
										LDH_Board[dy - 1][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}
							}

						}		// 3개 연속된것 검사 닫음

						else if (dy < 16 && LDH_Board[dy + 3][dx] == 2) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

							if (dy < 15 && LDH_Board[dy + 4][dx] == 2 && (LDH_Board[dy + 2][dx] == 0 || LDH_Board[dy + 2][dx] == 3)) {		// @ @ 0 @ @ 상황 일 때
								LDH_Board[dy + 2][dx] = 4;

								Warning_ldh[wstack_ldh].x = dx;
								Warning_ldh[wstack_ldh].y = dy + 2;
								wstack_ldh++;
							}

							else if (dy == 0 && LDH_Board[dy + 2][dx] == 0) {		// 위쪽이 벽인 @ @ 0 @								 위쪽이 벽이고 사이가 비어있어야 체크함
								
								if (LDH_Board[dy + 4][dx] == 0) {			// @ @ 0 @ 의 아래쪽이 비어있으면			위쪽이 벽인 경우 아래만 막으면 막히므로 아래만 검사함
									LDH_Board[dy + 4][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy + 4;
									hstack_ldh++;
								}
							}

							else if (dy == 15 && LDH_Board[dy + 2][dx] == 0) {		// 아래쪽이 벽인 @ @ 0 @
								
								if (LDH_Board[dy - 1][dx] == 0) {					// @ @ 0 @ 의 왼쪽이 비어있으면		아래쪽이 벽인 경우 위만 막으면 막히므로 아래만 검사함
									LDH_Board[dy - 1][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy - 1;
									hstack_ldh++;
								}
							}		

							else if (dy > 0 && dy < 15) {				// 벽에 막히지 않은 @ @ 0 @
																		// @ @ 0 @ 에서 막힌 곳이 없다면 !로 만듬
								if (LDH_Board[dy - 1][dx] == 0) {
									LDH_Board[dy - 1][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy - 1;
									hstack_ldh++;
								}

								if (LDH_Board[dy + 2][dx] == 0) {
									LDH_Board[dy + 2][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy + 2;
									hstack_ldh++;
								}

								if (LDH_Board[dy + 4][dx] == 0) {
									LDH_Board[dy + 4][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy + 4;
									hstack_ldh++;
								}
							}

						}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


					}		// 2개 연속 닫음

					// ------------------- 1개 후 연속 검사 ------------

					else if (dy < 18 && LDH_Board[dy + 1][dx] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

						if (dy < 17 && LDH_Board[dy + 2][dx] == 2) {		// @ 0 @ 상태

							if (dy < 16 && LDH_Board[dy + 3][dx] == 2) {		// @ 0 @ @ 상태

								if (dy < 15 && LDH_Board[dy + 4][dx] == 2) {		// @ 0 @ @ @ 상태

									if (LDH_Board[dy + 1][dx] == 0 || LDH_Board[dy + 1][dx] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
										LDH_Board[dy + 1][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 1;
										wstack_ldh++;

										// 위에 3칸 검사에서 다음걸 검사하므로 dy+5가 비어있는지 검사할 필요 x
									}

								}		//  @ 0 @ @ @ 상태 검사 닫음

								else if (dy < 16) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

									if (dy == 0) {				// 위쪽 벽에 붙은 @ 0 @ @

										if (LDH_Board[dy + 4][dx] == 0) {				// 아래쪽을 막으면 아예 막히므로 아래쪽만 검사
											LDH_Board[dy + 4][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy + 4;
											hstack_ldh++;
										}

									}

									else if (dy == 15) {		// 아래쪽 벽에 붙은 @ 0 @ @

										if (LDH_Board[dy - 1][dx] == 0) {				// 위쪽을 막으면 아예 막히므로 위쪽만 검사
											LDH_Board[dy - 1][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}

									}

									else if (dy > 0 && dy < 15) {						// 벽에 붙지 않은 @ 0 @ @

										if (LDH_Board[dy - 1][dx] == 0) {
											LDH_Board[dy - 1][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx] == 0) {
											LDH_Board[dy + 4][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy + 4;
											hstack_ldh++;
										}

										if (LDH_Board[dy + 1][dx] == 0) {
											LDH_Board[dy + 1][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy + 1;
											hstack_ldh++;
										}

									}

								}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


							} // @ 0 @ @ 상태 검사 닫음

						}	// @ 0 @ 상태 검사 닫음

					}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

				}		// 1개 연속 닫음


			}
		}

		// ---------- 세로 검사 ------------------



		// ---------- 대각선 검사 ------------------

		for (int i = 0; i < 19; i++) {		// 우측 하단 대각선 기준 위쪽
			for (int dy = 0, dx = i; dx < 19; dx++, dy++) {				// i = dx의 시작점

				
				if (i < 15) {		// i가 15보다 작아야 우측 아래 대각선으로 돌  5개를 둘 수 있음

					if (LDH_Board[dy][dx] == 2) {									// 백돌이 있다면

						if (dx < 18 && LDH_Board[dy + 1][dx + 1] == 2) {						// 백돌 현재 2개 연속

							if (dx < 17 && LDH_Board[dy + 2][dx + 2] == 2) {						//  백돌 @ @ @

								if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 2) {		// 백돌 @ @ @ @

									if (dy == 0 && (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3)) {		// 위쪽 벽에 붙어 오른쪽 아래로 내려가는  @ @ @ @
										LDH_Board[dy + 4][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;		// 스택에 저장
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dx == 15 && (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3)) {		// 오른쪽 아래로 내려가는 @ @ @ @ 가 오른쪽 벽에 붙어있는 경우
										LDH_Board[dy - 1][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dy > 0 && dx < 15) {												// 벽에 붙지 않은 @ @ @ @
										if (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3) {				// 왼쪽 위가 빔
											LDH_Board[dy - 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3) {				// 오른쪽 아래가 빔
											LDH_Board[dy + 4][dx + 4] = 4;

											Warning_ldh[wstack_ldh].x = dx + 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4개 연속 닫음

								// ----------- 3개 연속 ---------------- //


								if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 2) {			// @ @ @ 0 @ 상태								// dx + 4 가 18을 넘어가면 메모리 액세스 거부가 일어나는가?  	ex)  LDH_Board[20][20]==2   ????		 dx를 먼저 검사해 해결

									if (dy == 0) {			// 위쪽 벽에 붙은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// 위쪽 벽에 붙지 않은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

								}		// @ @ @ 0 @ 상태 검사 닫음

								else {			 // @ @ @ 상태		@ @ @ 의 두칸 오른쪽은 백돌 이 아님

									if (dy == 0) {							// 위쪽 벽에 붙은 @ @ @	

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// 오른쪽 아래가 비어있음
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dx == 16) {					// 오른쪽 벽에 붙은 @ @ @

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// 왼쪽 위가 비어있음
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dy > 0 && dx < 16) {									// 벽에 붙지 않은 @ @ @

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// 오른쪽 아래가 비어있음
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// 왼쪽 위가 비어있음
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3개 연속된것 검사 닫음

							else if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 2) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

								if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 2 && (LDH_Board[dy + 2][dx + 2] == 0 || LDH_Board[dy + 2][dx + 2] == 3)) {		// @ @ 0 @ @ 상황 일 때
									LDH_Board[dy + 2][dx + 2] = 4;

									Warning_ldh[wstack_ldh].x = dx + 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dy == 0 && LDH_Board[dy + 2][dx + 2] == 0) {		// 위쪽 벽에 붙은 @ @ 0 @						 왼쪽 위가 벽이고 사이가 비어있어야 체크함

									if (LDH_Board[dy + 4][dx + 4] == 0) {			// @ @ 0 @ 의 오른쪽이 비어있으면
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dx == 15) && LDH_Board[dy + 2][dx + 2] == 0) {	// 오른쪽 벽에 붙은 @ @ 0 @

									if (LDH_Board[dy - 1][dx - 1] == 0) {				// @ @ 0 @ 의 왼쪽이 비어있으면
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dx < 15) {				// 벽에 막히지 않은 @ @ 0 @
																			// @ @ 0 @ 에서 막힌 곳이 없다면 3으로 만듬
									if (LDH_Board[dy - 1][dx - 1] == 0) {
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 2][dx + 2] == 0) {
										LDH_Board[dy + 2][dx + 2] = 3;

										Hint_ldh[hstack_ldh].x = dx + 2;
										Hint_ldh[hstack_ldh].y = dy + 2;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx + 4] == 0) {
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

							}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


						}		// 2개 연속 닫음

						// ------------------- 1개 후 연속 검사 ------------

						else if (dx < 18 && LDH_Board[dy + 1][dx + 1] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

							if (dx < 17 && LDH_Board[dy + 2][dx + 2] == 2) {		// @ 0 @ 상태

								if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 2) {		// @ 0 @ @ 상태

									if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 2) {		// @ 0 @ @ @ 상태

										if (LDH_Board[dy + 1][dx + 1] == 0 || LDH_Board[dy + 1][dx + 1] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
											LDH_Board[dy + 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// 위에 3칸 검사에서 다음걸 검사하므로 dx+5가 비어있는지 검사할 필요 x
										}

									}		//  @ 0 @ @ @ 상태 검사 닫음

									else if (dx < 16) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

										if (dy == 0) {				// 위쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy + 4][dx + 4] == 0) {				// 오른쪽을 막으면 아예 막히므로 오른쪽만 검사
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dx == 15) {		// 오른쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {				// 왼쪽을 막으면 아예 막히므로 오른쪽만 검사
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy > 0 && dx < 15) {						// 벽에 붙지 않은 @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 4][dx + 4] == 0) {
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 1][dx + 1] == 0) {
												LDH_Board[dy + 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy + 1;
												hstack_ldh++;
											}

										}

									}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


								} // @ 0 @ @ 상태 검사 닫음

							}	// @ 0 @ 상태 검사 닫음

						}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

					}		// 1개 연속 닫음

				}		// i < 15 닫음

			}
		}


		for (int i = 1; i < 19; i++) {		// 우측 하단 대각선 기준 아래쪽
			for (int dx = 0, dy = i; dy < 19; dx++, dy++) {				// i = dy의 시작점				 무조건 dy가 dx보다 큼


				if (i < 15) {		// i가 15보다 작아야 우측 아래 대각선으로 돌  5개를 둘 수 있음

					if (LDH_Board[dy][dx] == 2) {									// 백돌이 있다면

						if (dy < 18 && LDH_Board[dy + 1][dx + 1] == 2) {						// 백돌 현재 2개 연속

							if (dy < 17 && LDH_Board[dy + 2][dx + 2] == 2) {						//  백돌 @ @ @

								if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 2) {		// 백돌 @ @ @ @

									if (dx == 0 && (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3)) {		// 왼쪽 벽에 붙어 오른쪽 아래로 내려가는  @ @ @ @
										LDH_Board[dy + 4][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;		// 스택에 저장
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dy == 15 && (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3)) {		// 오른쪽 아래로 내려가는 @ @ @ @ 가 아래쪽 벽에 붙어있는 경우
										LDH_Board[dy - 1][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx > 0 && dy < 15) {												// 벽에 붙지 않은 @ @ @ @
										if (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3) {				// 왼쪽 위가 빔
											LDH_Board[dy - 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3) {				// 오른쪽 아래가 빔
											LDH_Board[dy + 4][dx + 4] = 4;

											Warning_ldh[wstack_ldh].x = dx + 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4개 연속 닫음

								// ----------- 3개 연속 ---------------- //


								if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 2) {			// @ @ @ 0 @ 상태								// dx + 4 가 18을 넘어가면 메모리 액세스 거부가 일어나는가?  	ex)  LDH_Board[20][20]==2   ????		 dx를 먼저 검사해 해결

									if (dx == 0) {			// 왼쪽 벽에 붙은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// 왼쪽 벽에 붙지 않은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

								}		// @ @ @ 0 @ 상태 검사 닫음

								else {			 // @ @ @ 상태		@ @ @ 의 두칸 오른쪽은 백돌 이 아님

									if (dx == 0) {							// 왼쪽 벽에 붙은 @ @ @	

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// 오른쪽 아래가 비어있음
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dy == 16) {					// 아래쪽 벽에 붙은 @ @ @

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// 왼쪽 위가 비어있음
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dx > 0 && dy < 16) {									// 벽에 붙지 않은 @ @ @

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// 오른쪽 아래가 비어있음
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// 왼쪽 위가 비어있음
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3개 연속된것 검사 닫음

							else if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 2) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

								if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 2 && (LDH_Board[dy + 2][dx + 2] == 0 || LDH_Board[dy + 2][dx + 2] == 3)) {		// @ @ 0 @ @ 상황 일 때
									LDH_Board[dy + 2][dx + 2] = 4;

									Warning_ldh[wstack_ldh].x = dx + 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dx == 0 && LDH_Board[dy + 2][dx + 2] == 0) {		// 왼쪽 벽에 붙은 @ @ 0 @						 왼쪽 위가 벽이고 사이가 비어있어야 체크함

									if (LDH_Board[dy + 4][dx + 4] == 0) {			// @ @ 0 @ 의 오른쪽이 비어있으면
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dy == 15) && LDH_Board[dy + 2][dx + 2] == 0) {	// 아래쪽 벽에 붙은 @ @ 0 @

									if (LDH_Board[dy - 1][dx - 1] == 0) {				// @ @ 0 @ 의 왼쪽이 비어있으면
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dx > 0 && dy < 15) {				// 벽에 막히지 않은 @ @ 0 @
																			// @ @ 0 @ 에서 막힌 곳이 없다면 3으로 만듬
									if (LDH_Board[dy - 1][dx - 1] == 0) {
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 2][dx + 2] == 0) {
										LDH_Board[dy + 2][dx + 2] = 3;

										Hint_ldh[hstack_ldh].x = dx + 2;
										Hint_ldh[hstack_ldh].y = dy + 2;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx + 4] == 0) {
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

							}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


						}		// 2개 연속 닫음

						// ------------------- 1개 후 연속 검사 ------------

						else if (dy < 18 && LDH_Board[dy + 1][dx + 1] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

							if (dy < 17 && LDH_Board[dy + 2][dx + 2] == 2) {		// @ 0 @ 상태

								if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 2) {		// @ 0 @ @ 상태

									if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 2) {		// @ 0 @ @ @ 상태

										if (LDH_Board[dy + 1][dx + 1] == 0 || LDH_Board[dy + 1][dx + 1] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
											LDH_Board[dy + 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// 위에 3칸 검사에서 다음걸 검사하므로 dx+5가 비어있는지 검사할 필요 x
										}

									}		//  @ 0 @ @ @ 상태 검사 닫음

									else if (dy < 16) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

										if (dx == 0) {				// 왼쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy + 4][dx + 4] == 0) {				// 오른쪽을 막으면 아예 막히므로 오른쪽만 검사		위에서 i<15 이므로 왼쪽 벽에 붙은 dy=15 일 경우 검사 자체를 하지 않음
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dy == 15) {		// 아래쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {				// 왼쪽을 막으면 아예 막히므로 오른쪽만 검사
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dx > 0 && dy < 15) {						// 벽에 붙지 않은 @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 4][dx + 4] == 0) {
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 1][dx + 1] == 0) {
												LDH_Board[dy + 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy + 1;
												hstack_ldh++;
											}

										}

									}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


								} // @ 0 @ @ 상태 검사 닫음

							}	// @ 0 @ 상태 검사 닫음

						}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

					}		// 1개 연속 닫음

				}		// i < 15 닫음

			}
		}


		for (int i = 0; i < 19; i++) {		// 좌측 하단 대각선 기준 위쪽
			for (int dy = 0, dx = i; dx >= 0; dx--, dy++) {				// i = dx의 시작점	


				if (i > 3) {		// i가 3보다 커야 좌측 하단으로 돌 5개를 둘 수 있음						dx 가 3보다 클 때 검사

					if (LDH_Board[dy][dx] == 2) {									// 백돌이 있다면

						if (dx > 0 && LDH_Board[dy + 1][dx - 1] == 2) {						// 백돌 현재 2개 연속

							if (dx > 1 && LDH_Board[dy + 2][dx - 2] == 2) {						//  백돌 @ @ @

								if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 2) {		// 백돌 @ @ @ @

									if (dy == 0 && (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3)) {		// 위쪽 벽에 붙어 왼쪽 아래로 내려가는  @ @ @ @
										LDH_Board[dy + 4][dx - 4] = 4;															// 왼쪽 아래가 빔

										Warning_ldh[wstack_ldh].x = dx - 4;		// 스택에 저장
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dx == 3 && (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3)) {		// 왼쪽 아래로 내려가는 @ @ @ @ 가 왼쪽 벽에 붙어있는 경우
										LDH_Board[dy - 1][dx + 1] = 4;																// 오른쪽 위가 빔

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx > 3 && dy > 0) {												// 벽에 붙지 않은 @ @ @ @
										if (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3) {				// 오른쪽 위가 빔
											LDH_Board[dy - 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3) {				// 왼쪽 아래가 빔
											LDH_Board[dy + 4][dx - 4] = 4;

											Warning_ldh[wstack_ldh].x = dx - 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4개 연속 닫음

								// ----------- 3개 연속 ---------------- //


								if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 2) {			// @ @ @ 0 @ 상태								// dx + 4 가 18을 넘어가면 메모리 액세스 거부가 일어나는가?  	ex)  LDH_Board[20][20]==2   ????		 dx를 먼저 검사해 해결

									if (dy == 0) {			// 위쪽 벽에 붙은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// 위쪽 벽에 붙지 않은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

								}		// @ @ @ 0 @ 상태 검사 닫음

								else {			 // @ @ @ 상태		@ @ @ 의 두칸 왼쪽은 백돌 이 아님

									if (dy == 0) {							// 위쪽 벽에 붙은 @ @ @	

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// 왼쪽 아래가 비어있음
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dx == 2) {					// 왼쪽 벽에 붙은 @ @ @

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// 오른쪽 위가 비어있음
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dy > 0 && dx > 2) {									// 벽에 붙지 않은 @ @ @

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// 왼쪽 아래가 비어있음
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// 오른쪽 위가 비어있음
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3개 연속된것 검사 닫음

							else if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 2) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

								if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 2 && (LDH_Board[dy + 2][dx - 2] == 0 || LDH_Board[dy + 2][dx - 2] == 3)) {		// @ @ 0 @ @ 상황 일 때
									LDH_Board[dy + 2][dx - 2] = 4;

									Warning_ldh[wstack_ldh].x = dx - 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dy == 0 && LDH_Board[dy + 2][dx - 2] == 0) {		// 위쪽 벽에 붙은 @ @ 0 @						 오른쪽 위가 벽이고 사이가 비어있어야 체크함

									if (LDH_Board[dy + 4][dx - 4] == 0) {			// @ @ 0 @ 의 왼쪽 아래가 비어있으면
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dx == 3) && LDH_Board[dy + 2][dx - 2] == 0) {	// 왼쪽 벽에 붙은 @ @ 0 @

									if (LDH_Board[dy - 1][dx + 1] == 0) {				// @ @ 0 @ 의 오른쪽 위가 비어있으면
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dx > 3) {				// 벽에 막히지 않은 @ @ 0 @
																			// @ @ 0 @ 에서 막힌 곳이 없다면 3으로 만듬
									if (LDH_Board[dy - 1][dx + 1] == 0) {
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 2][dx - 2] == 0) {
										LDH_Board[dy + 2][dx - 2] = 3;

										Hint_ldh[hstack_ldh].x = dx - 2;
										Hint_ldh[hstack_ldh].y = dy + 2;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx - 4] == 0) {
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

							}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


						}		// 2개 연속 닫음

						// ------------------- 1개 후 연속 검사 ------------

						else if (dx > 0 && LDH_Board[dy + 1][dx - 1] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

							if (dx > 1 && LDH_Board[dy + 2][dx - 2] == 2) {		// @ 0 @ 상태

								if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 2) {		// @ 0 @ @ 상태

									if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 2) {		// @ 0 @ @ @ 상태

										if (LDH_Board[dy + 1][dx - 1] == 0 || LDH_Board[dy + 1][dx - 1] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
											LDH_Board[dy + 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// 위에 3칸 검사에서 다음걸 검사하므로 dx+5가 비어있는지 검사할 필요 x
										}

									}		//  @ 0 @ @ @ 상태 검사 닫음

									else if (dx > 2) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

										if (dy == 0) {				// 위쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy + 4][dx - 4] == 0) {				// 왼쪽 아래를 막으면 아예 막히므로 왼쪽만 검사		위에서 i>3 이므로 위쪽 벽에 붙은 dx=3 일 경우 검사 자체를 하지 않음
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dx == 3) {		// 왼쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {				// 오른쪽 위를 막으면 아예 막히므로 오른쪽만 검사
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy > 0 && dx > 3) {						// 벽에 붙지 않은 @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 4][dx - 4] == 0) {
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 1][dx - 1] == 0) {
												LDH_Board[dy + 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy + 1;
												hstack_ldh++;
											}

										}

									}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


								} // @ 0 @ @ 상태 검사 닫음

							}	// @ 0 @ 상태 검사 닫음

						}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

					}	// 1개 연속 닫음

				}	// i > 3 닫음

			}
		}


		for (int i = 1; i < 19; i++) {		// 좌측 하단 대각선 기준 아래쪽
			for (int dx = 18, dy = i; dy < 19; dx--, dy++) {				// i = dy의 시작점	


				if (i < 15) {		// i가 15보다 작아야 좌측 하단으로 돌 5개를 둘 수 있음	

					if (LDH_Board[dy][dx] == 2) {									// 백돌이 있다면

						if (dy < 18 && LDH_Board[dy + 1][dx - 1] == 2) {						// 백돌 현재 2개 연속

							if (dy < 17 && LDH_Board[dy + 2][dx - 2] == 2) {						//  백돌 @ @ @

								if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 2) {		// 백돌 @ @ @ @

									if (dx == 18 && (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3)) {		// 오른쪽 벽에 붙어 왼쪽 아래로 내려가는  @ @ @ @
										LDH_Board[dy + 4][dx - 4] = 4;															// 왼쪽 아래가 빔

										Warning_ldh[wstack_ldh].x = dx - 4;		// 스택에 저장
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dy == 15 && (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3)) {		// 왼쪽 아래로 내려가는 @ @ @ @ 가 아래쪽 벽에 붙어있는 경우
										LDH_Board[dy - 1][dx + 1] = 4;																// 오른쪽 위가 빔

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx < 18 && dy < 15) {												// 벽에 붙지 않은 @ @ @ @
										if (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3) {				// 오른쪽 위가 빔
											LDH_Board[dy - 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3) {				// 왼쪽 아래가 빔
											LDH_Board[dy + 4][dx - 4] = 4;

											Warning_ldh[wstack_ldh].x = dx - 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4개 연속 닫음

								// ----------- 3개 연속 ---------------- //


								if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 2) {			// @ @ @ 0 @ 상태	

									if (dx == 18) {			// 오른쪽 벽에 붙은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// 오른쪽 벽에 붙지 않은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

								}		// @ @ @ 0 @ 상태 검사 닫음

								else {			 // @ @ @ 상태		@ @ @ 의 두칸 왼쪽은 백돌 이 아님

									if (dx == 18) {							// 오른쪽 벽에 붙은 @ @ @	

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// 왼쪽 아래가 비어있음
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dy == 16) {					// 아래 벽에 붙은 @ @ @

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// 오른쪽 위가 비어있음
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dx < 18 && dy < 16) {									// 벽에 붙지 않은 @ @ @

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// 왼쪽 아래가 비어있음
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// 오른쪽 위가 비어있음
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3개 연속된것 검사 닫음

							else if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 2) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

								if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 2 && (LDH_Board[dy + 2][dx - 2] == 0 || LDH_Board[dy + 2][dx - 2] == 3)) {		// @ @ 0 @ @ 상황 일 때
									LDH_Board[dy + 2][dx - 2] = 4;

									Warning_ldh[wstack_ldh].x = dx - 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dx == 18 && LDH_Board[dy + 2][dx - 2] == 0) {		// 오른쪽 벽에 붙은 @ @ 0 @						 오른쪽 위가 벽이고 사이가 비어있어야 체크함

									if (LDH_Board[dy + 4][dx - 4] == 0) {			// @ @ 0 @ 의 왼쪽 아래가 비어있으면
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dy == 15) && LDH_Board[dy + 2][dx - 2] == 0) {	// 아래쪽 벽에 붙은 @ @ 0 @

									if (LDH_Board[dy - 1][dx + 1] == 0) {				// @ @ 0 @ 의 오른쪽 위가 비어있으면
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy < 15 && dx < 18) {				// 벽에 막히지 않은 @ @ 0 @
																			// @ @ 0 @ 에서 막힌 곳이 없다면 3으로 만듬
									if (LDH_Board[dy - 1][dx + 1] == 0) {
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 2][dx - 2] == 0) {
										LDH_Board[dy + 2][dx - 2] = 3;

										Hint_ldh[hstack_ldh].x = dx - 2;
										Hint_ldh[hstack_ldh].y = dy + 2;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx - 4] == 0) {
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

							}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


						}		// 2개 연속 닫음

						// ------------------- 1개 후 연속 검사 ------------

						else if (dy < 18 && LDH_Board[dy + 1][dx - 1] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

							if (dy < 17 && LDH_Board[dy + 2][dx - 2] == 2) {		// @ 0 @ 상태

								if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 2) {		// @ 0 @ @ 상태

									if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 2) {		// @ 0 @ @ @ 상태

										if (LDH_Board[dy + 1][dx - 1] == 0 || LDH_Board[dy + 1][dx - 1] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
											LDH_Board[dy + 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// 위에 3칸 검사에서 다음걸 검사하므로 dx+5가 비어있는지 검사할 필요 x
										}

									}		//  @ 0 @ @ @ 상태 검사 닫음

									else if (dy < 16) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

										if (dx == 18) {				// 오른쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy + 4][dx - 4] == 0) {				// 왼쪽 아래를 막으면 아예 막히므로 왼쪽만 검사		위에서 i<15 이므로 오른쪽 벽에 붙은 dy=15 일 경우 검사 자체를 하지 않음
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dy == 15) {		// 아래쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {				// 오른쪽 위를 막으면 아예 막히므로 오른쪽만 검사
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy < 15 && dx < 18) {						// 벽에 붙지 않은 @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 4][dx - 4] == 0) {
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 1][dx - 1] == 0) {
												LDH_Board[dy + 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy + 1;
												hstack_ldh++;
											}

										}

									}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


								} // @ 0 @ @ 상태 검사 닫음

							}	// @ 0 @ 상태 검사 닫음

						}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

					}	// 1개 연속 닫음

				}	// i < 15 닫음

			}
		}

		// ---------- 대각선 검사 ------------------


		// 임시 공격 ---------------------


		if (wstack_ldh > 0) {		//	바로 둬야할 곳이 있으면
			*x = Warning_ldh[0].x;	
			*y = Warning_ldh[0].y;

			LDH_Board[*y][*x] = 1;

		}
		
		else if (hstack_ldh > 0) {		// 막아야 할 곳이 있으면
			*x = Hint_ldh[0].x;
			*y = Hint_ldh[0].y;

			LDH_Board[*y][*x] = 1;
		}

		else {									// 막아야 할 곳이 없으면


			for (int i = 0; i < 13; i++) {
				for (int j = 0; j < 13; j++) {
					Check_ldh[i][j].count = 0;
				}
			}

			for (int dy = 0; dy < 13; dy += 3) {						// 7*7 짜리 판으로 나누어 내 돌의 갯수를 셈
				for (int dx = 0; dx < 13; dx += 3) {

					for (int i = 0; i < 7; i++) {							// 7 * 7 칸에 속한 자기 돌을 셈
						for (int j = 0; j < 7; j++) {

							if (LDH_Board[dy + i][dx + j] == 1) {
								Check_ldh[checky_ldh][checkx_ldh].count++;

							}

						}
					}

					checkx_ldh++;
				}

				checkx_ldh = 0;
				checky_ldh++;
			}


			for (int dy = 0; dy < 13; dy++) {							// 구역중 가장 많은 돌이 몇개인지를 찾아냄
				for (int dx = 0; dx < 13; dx++) {

					if (Check_ldh[dy][dx].count > maxstone_ldh) {
						maxstone_ldh = Check_ldh[dy][dx].count;
					}

				}
			}

			for (int dy = 0; dy < 13; dy++) {							// 가장 많은 돌이 어느구역인지 찾아냄
				for (int dx = 0; dx < 13; dx++) {

					if (Check_ldh[dy][dx].count == maxstone_ldh) {
						checky_ldh = dy;
						checkx_ldh = dx;
						break;
					}

				}
			}

			while (1) {
				rx = rand() % 7 + checkx_ldh;
				ry = rand() % 7 + checky_ldh;

				for (int dy = checky_ldh; dy < checky_ldh + 7; dy++) {
					for (int dx = checkx_ldh; dx < checkx_ldh + 7; dx++) {
						if (LDH_Board[dy][dx] == 1 || LDH_Board[dy][dx] == 2) {
							checkstone_ldh++;
						}
					}
				}

				if (checkstone_ldh > 30) {
					checkx_ldh = rand() % 12;
					checky_ldh = rand() % 12;
				}

				if (LDH_Board[ry][rx] != 1 && LDH_Board[ry][rx] != 2) {
					break;
				}
			}

			*x = rx;
			*y = ry;

			LDH_Board[*y][*x] = 1;

		}


	}

}

void BlackDefence_2018182024(int x, int y)
{
	LDH_Board[y][x] = 2;
}

void WhiteAttack_2018182024(int *x, int *y)
{
	int rx, ry;

	hstack_ldh = 0;				// 매번 검사시작 할때마다 스택을 0으로 만듬
	wstack_ldh = 0;
	checkx_ldh = 0;
	checky_ldh = 0;
	checkstone_ldh = 0;

	srand((unsigned int)time(NULL));

	if (LDH_Board[9][9] == 0) {			// 맨 처음엔 가운데 둠		9,9 가 비어있는지 판단함 비어있지 않으면 다른 곳에 둠
		*x = 9;
		*y = 9;

		LDH_Board[9][9] = 2;
	}

	else {								// 첫턴이 아니라면


		// ---------- 가로 검사 ------------------

		for (int dy = 0; dy < 19; dy++) {					// 흑돌 가로 검사
			for (int dx = 0; dx < 19; dx++) {

				if (LDH_Board[dy][dx] == 1) {									// 흑돌이 있다면

					if (dx < 18 && LDH_Board[dy][dx + 1] == 1) {						// 흑돌 현재 2개 연속

						if (dx < 17 && LDH_Board[dy][dx + 2] == 1) {						//  백돌 @ @ @

							if (dx < 16 && LDH_Board[dy][dx + 3] == 1) {		// 백돌 @ @ @ @

								if (dx == 0 && (LDH_Board[dy][dx + 4] == 0 || LDH_Board[dy][dx + 4] == 3)) {		// 왼쪽 벽에 붙은  @ @ @ @
									LDH_Board[dy][dx + 4] = 4;

									Warning_ldh[wstack_ldh].x = dx + 4;		// 스택에 저장
									Warning_ldh[wstack_ldh].y = dy;
									wstack_ldh++;
								}

								else if (dx == 15 && (LDH_Board[dy][dx - 1] == 0 || LDH_Board[dy][dx - 1] == 3)) {	// 오른쪽 벽에 붙은 @ @ @ @
									LDH_Board[dy][dx - 1] = 4;

									Warning_ldh[wstack_ldh].x = dx - 1;
									Warning_ldh[wstack_ldh].y = dy;
									wstack_ldh++;
								}

								else if (dx > 0 && dx < 15) {												// 벽에 붙지 않은 @ @ @ @
									if (LDH_Board[dy][dx - 1] == 0 || LDH_Board[dy][dx - 1] == 3) {				// 왼쪽이 빔
										LDH_Board[dy][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}

									if (LDH_Board[dy][dx + 4] == 0 || LDH_Board[dy][dx + 4] == 3) {				// 오른쪽이 빔
										LDH_Board[dy][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}
								}

							}		// 4개 연속 닫음

							// ----------- 3개 연속 ---------------- //

							if (dx < 15 && LDH_Board[dy][dx + 4] == 1) {			// @ @ @ 0 @ 상태

								if (dx == 0) {			// 왼쪽 벽에 붙은 @ @ @ 0 @
									if (LDH_Board[dy][dx + 3] == 0 || LDH_Board[dy][dx + 3] == 3) {
										LDH_Board[dy][dx + 3] = 4;

										Warning_ldh[wstack_ldh].x = dx + 3;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}
								}

								else {						// 오른쪽 벽에 붙은 @ @ @ 0 @ or 벽에 붙지 않은 @ @ @ 0 @
									if (LDH_Board[dy][dx + 3] == 0 || LDH_Board[dy][dx + 3] == 3) {
										LDH_Board[dy][dx + 3] = 4;

										Warning_ldh[wstack_ldh].x = dx + 3;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}

									if (LDH_Board[dy][dx - 1] == 0) {
										LDH_Board[dy][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}

							}		// @ @ @ 0 @ 상태 검사 닫음

							else {			 // @ @ @ 상태		@ @ @ 의 두칸 오른쪽은 백돌 이 아님

								if (dx == 0) {							// 왼쪽 벽에 붙은 @ @ @	

									if (LDH_Board[dy][dx + 3] == 0) {		// 오른쪽이 비어있음
										LDH_Board[dy][dx + 3] = 3;

										Hint_ldh[hstack_ldh].x = dx + 3;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}

								else if (dx == 16) {					// 오른쪽 벽에 붙은 @ @ @

									if (LDH_Board[dy][dx - 1] == 0) {		// 왼쪽이 비어있음
										LDH_Board[dy][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}

								else if (dx > 0 && dx < 16) {									// 벽에 붙지 않은 @ @ @

									if (LDH_Board[dy][dx + 3] == 0) {		// 오른쪽이 비어있음
										LDH_Board[dy][dx + 3] = 3;

										Hint_ldh[hstack_ldh].x = dx + 3;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}

									if (LDH_Board[dy][dx - 1] == 0) {		// 왼쪽이 비어있음
										LDH_Board[dy][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}
							}

						}		// 3개 연속된것 검사 닫음

						else if (dx < 16 && LDH_Board[dy][dx + 3] == 1) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

							if (dx < 15 && LDH_Board[dy][dx + 4] == 1 && (LDH_Board[dy][dx + 2] == 0 || LDH_Board[dy][dx + 2] == 3)) {		// @ @ 0 @ @ 상황 일 때
								LDH_Board[dy][dx + 2] = 4;

								Warning_ldh[wstack_ldh].x = dx + 2;
								Warning_ldh[wstack_ldh].y = dy;
								wstack_ldh++;
							}

							else if (dx == 0 && LDH_Board[dy][dx + 2] == 0) {		// 왼쪽이 벽인 @ @ 0 @								 왼쪽이 벽이고 사이가 비어있어야 체크함

								if (LDH_Board[dy][dx + 4] == 0) {			// @ @ 0 @ 의 오른쪽이 비어있으면
									LDH_Board[dy][dx + 4] = 3;

									Hint_ldh[hstack_ldh].x = dx + 4;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}
							}

							else if ((dx == 15) && LDH_Board[dy][dx + 2] == 0) {	// 오른쪽이 벽인 @ @ 0 @

								if (LDH_Board[dy][dx - 1] == 0) {				// @ @ 0 @ 의 왼쪽이 비어있으면
									LDH_Board[dy][dx - 1] = 3;

									Hint_ldh[hstack_ldh].x = dx - 1;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}
							}

							else if (dx > 0 && dx < 15) {				// 벽에 막히지 않은 @ @ 0 @
																		// @ @ 0 @ 에서 막힌 곳이 없다면 !로 만듬
								if (LDH_Board[dy][dx - 1] == 0) {
									LDH_Board[dy][dx - 1] = 3;

									Hint_ldh[hstack_ldh].x = dx - 1;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}

								if (LDH_Board[dy][dx + 2] == 0) {
									LDH_Board[dy][dx + 2] = 3;

									Hint_ldh[hstack_ldh].x = dx + 2;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}

								if (LDH_Board[dy][dx + 4] == 0) {
									LDH_Board[dy][dx + 4] = 3;

									Hint_ldh[hstack_ldh].x = dx + 4;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}
							}

						}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


					}		// 2개 연속 닫음

					// ------------------- 1개 후 연속 검사 ------------

					else if (dx < 18 && LDH_Board[dy][dx + 1] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

						if (dx < 17 && LDH_Board[dy][dx + 2] == 1) {		// @ 0 @ 상태

							if (dx < 16 && LDH_Board[dy][dx + 3] == 1) {		// @ 0 @ @ 상태

								if (dx < 15 && LDH_Board[dy][dx + 4] == 1) {		// @ 0 @ @ @ 상태

									if (LDH_Board[dy][dx + 1] == 0 || LDH_Board[dy][dx + 1] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
										LDH_Board[dy][dx + 1] = 4;

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;

										// 위에 3칸 검사에서 다음걸 검사하므로 dx+5가 비어있는지 검사할 필요 x
									}

								}		//  @ 0 @ @ @ 상태 검사 닫음

								else if (dx < 16) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

									if (dx == 0) {				// 왼쪽 벽에 붙은 @ 0 @ @

										if (LDH_Board[dy][dx + 4] == 0) {				// 오른쪽을 막으면 아예 막히므로 오른쪽만 검사
											LDH_Board[dy][dx + 4] = 3;

											Hint_ldh[hstack_ldh].x = dx + 4;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

									}

									else if (dx == 15) {		// 오른쪽 벽에 붙은 @ 0 @ @

										if (LDH_Board[dy][dx - 1] == 0) {				// 왼쪽을 막으면 아예 막히므로 오른쪽만 검사
											LDH_Board[dy][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

									}

									else if (dx > 0 && dx < 15) {						// 벽에 붙지 않은 @ 0 @ @

										if (LDH_Board[dy][dx - 1] == 0) {
											LDH_Board[dy][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

										if (LDH_Board[dy][dx + 4] == 0) {
											LDH_Board[dy][dx + 4] = 3;

											Hint_ldh[hstack_ldh].x = dx + 4;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

										if (LDH_Board[dy][dx + 1] == 0) {
											LDH_Board[dy][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

									}

								}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


							} // @ 0 @ @ 상태 검사 닫음

						}	// @ 0 @ 상태 검사 닫음

					}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

				}		// 1개 연속 닫음


			}
		}

		// ---------- 가로 검사 ------------------



		// ---------- 세로 검사 ------------------

		for (int dx = 0; dx < 19; dx++) {					// 백돌 세로 검사
			for (int dy = 0; dy < 19; dy++) {

				if (LDH_Board[dy][dx] == 1) {									// 백돌이 있다면

					if (dy < 18 && LDH_Board[dy + 1][dx] == 1) {						// 백돌 현재 2개 연속

						if (dy < 17 && LDH_Board[dy + 2][dx] == 1) {						//  백돌 @ @ @

							if (dy < 16 && LDH_Board[dy + 3][dx] == 1) {		// 백돌 @ @ @ @

								if (dy == 0 && (LDH_Board[dy + 4][dx] == 0 || LDH_Board[dy + 4][dx] == 3)) {		// 위쪽 벽에 붙은  @ @ @ @
									LDH_Board[dy + 4][dx] = 4;

									Warning_ldh[wstack_ldh].x = dx;		// 스택에 저장
									Warning_ldh[wstack_ldh].y = dy + 4;
									wstack_ldh++;
								}

								else if (dy == 15 && (LDH_Board[dy - 1][dx] == 0 || LDH_Board[dy - 1][dx] == 3)) {	// 아래쪽 벽에 붙은 @ @ @ @
									LDH_Board[dy - 1][dx] = 4;

									Warning_ldh[wstack_ldh].x = dx;
									Warning_ldh[wstack_ldh].y = dy - 1;
									wstack_ldh++;
								}

								else if (dy > 0 && dy < 15) {												// 벽에 붙지 않은 @ @ @ @
									if (LDH_Board[dy - 1][dx] == 0 || LDH_Board[dy - 1][dx] == 3) {				// 위쪽이 빔
										LDH_Board[dy - 1][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx] == 0 || LDH_Board[dy + 4][dx] == 3) {				// 아래쪽이 빔
										LDH_Board[dy + 4][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}
								}

							}		// 4개 연속 닫음

							// ----------- 3개 연속 ---------------- //

							if (dy < 15 && LDH_Board[dy + 4][dx] == 1) {			// @ @ @ 0 @ 상태

								if (dy == 0) {			// 위쪽 벽에 붙은 @ @ @ 0 @
									if (LDH_Board[dy + 3][dx] == 0 || LDH_Board[dy + 3][dx] == 3) {
										LDH_Board[dy + 3][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 3;
										wstack_ldh++;
									}
								}

								else {						// 아래쪽 벽에 붙은 @ @ @ 0 @ or 벽에 붙지 않은 @ @ @ 0 @
									if (LDH_Board[dy + 3][dx] == 0 || LDH_Board[dy + 3][dx] == 3) {
										LDH_Board[dy + 3][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 3;
										wstack_ldh++;
									}

									if (LDH_Board[dy - 1][dx] == 0) {
										LDH_Board[dy - 1][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

							}		// @ @ @ 0 @ 상태 검사 닫음

							else {			 // @ @ @ 상태

								if (dy == 0) {							// 위쪽 벽에 붙은 @ @ @	

									if (LDH_Board[dy + 3][dx] == 0) {		// 아래쪽이 비어있음
										LDH_Board[dy + 3][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy + 3;
										hstack_ldh++;
									}
								}

								else if (dy == 16) {					// 아래쪽 벽에 붙은 @ @ @

									if (LDH_Board[dy - 1][dx] == 0) {		// 위쪽이 비어있음
										LDH_Board[dy - 1][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dy < 16) {									// 벽에 붙지 않은 @ @ @

									if (LDH_Board[dy + 3][dx] == 0) {		// 아래쪽이 비어있음
										LDH_Board[dy + 3][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy + 3;
										hstack_ldh++;
									}

									if (LDH_Board[dy - 1][dx] == 0) {		// 위쪽이 비어있음
										LDH_Board[dy - 1][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}
							}

						}		// 3개 연속된것 검사 닫음

						else if (dy < 16 && LDH_Board[dy + 3][dx] == 1) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

							if (dy < 15 && LDH_Board[dy + 4][dx] == 1 && (LDH_Board[dy + 2][dx] == 0 || LDH_Board[dy + 2][dx] == 3)) {		// @ @ 0 @ @ 상황 일 때
								LDH_Board[dy + 2][dx] = 4;

								Warning_ldh[wstack_ldh].x = dx;
								Warning_ldh[wstack_ldh].y = dy + 2;
								wstack_ldh++;
							}

							else if (dy == 0 && LDH_Board[dy + 2][dx] == 0) {		// 위쪽이 벽인 @ @ 0 @								 위쪽이 벽이고 사이가 비어있어야 체크함

								if (LDH_Board[dy + 4][dx] == 0) {			// @ @ 0 @ 의 아래쪽이 비어있으면			위쪽이 벽인 경우 아래만 막으면 막히므로 아래만 검사함
									LDH_Board[dy + 4][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy + 4;
									hstack_ldh++;
								}
							}

							else if (dy == 15 && LDH_Board[dy + 2][dx] == 0) {		// 아래쪽이 벽인 @ @ 0 @

								if (LDH_Board[dy - 1][dx] == 0) {					// @ @ 0 @ 의 왼쪽이 비어있으면		아래쪽이 벽인 경우 위만 막으면 막히므로 아래만 검사함
									LDH_Board[dy - 1][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy - 1;
									hstack_ldh++;
								}
							}

							else if (dy > 0 && dy < 15) {				// 벽에 막히지 않은 @ @ 0 @
																		// @ @ 0 @ 에서 막힌 곳이 없다면 !로 만듬
								if (LDH_Board[dy - 1][dx] == 0) {
									LDH_Board[dy - 1][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy - 1;
									hstack_ldh++;
								}

								if (LDH_Board[dy + 2][dx] == 0) {
									LDH_Board[dy + 2][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy + 2;
									hstack_ldh++;
								}

								if (LDH_Board[dy + 4][dx] == 0) {
									LDH_Board[dy + 4][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy + 4;
									hstack_ldh++;
								}
							}

						}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


					}		// 2개 연속 닫음

					// ------------------- 1개 후 연속 검사 ------------

					else if (dy < 18 && LDH_Board[dy + 1][dx] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

						if (dy < 17 && LDH_Board[dy + 2][dx] == 1) {		// @ 0 @ 상태

							if (dy < 16 && LDH_Board[dy + 3][dx] == 1) {		// @ 0 @ @ 상태

								if (dy < 15 && LDH_Board[dy + 4][dx] == 1) {		// @ 0 @ @ @ 상태

									if (LDH_Board[dy + 1][dx] == 0 || LDH_Board[dy + 1][dx] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
										LDH_Board[dy + 1][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 1;
										wstack_ldh++;

										// 위에 3칸 검사에서 다음걸 검사하므로 dy+5가 비어있는지 검사할 필요 x
									}

								}		//  @ 0 @ @ @ 상태 검사 닫음

								else if (dy < 16) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

									if (dy == 0) {				// 위쪽 벽에 붙은 @ 0 @ @

										if (LDH_Board[dy + 4][dx] == 0) {				// 아래쪽을 막으면 아예 막히므로 아래쪽만 검사
											LDH_Board[dy + 4][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy + 4;
											hstack_ldh++;
										}

									}

									else if (dy == 15) {		// 아래쪽 벽에 붙은 @ 0 @ @

										if (LDH_Board[dy - 1][dx] == 0) {				// 위쪽을 막으면 아예 막히므로 위쪽만 검사
											LDH_Board[dy - 1][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}

									}

									else if (dy > 0 && dy < 15) {						// 벽에 붙지 않은 @ 0 @ @

										if (LDH_Board[dy - 1][dx] == 0) {
											LDH_Board[dy - 1][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx] == 0) {
											LDH_Board[dy + 4][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy + 4;
											hstack_ldh++;
										}

										if (LDH_Board[dy + 1][dx] == 0) {
											LDH_Board[dy + 1][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy + 1;
											hstack_ldh++;
										}

									}

								}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


							} // @ 0 @ @ 상태 검사 닫음

						}	// @ 0 @ 상태 검사 닫음

					}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

				}		// 1개 연속 닫음


			}
		}

		// ---------- 세로 검사 ------------------



		// ---------- 대각선 검사 ------------------

		for (int i = 0; i < 19; i++) {		// 우측 하단 대각선 기준 위쪽
			for (int dy = 0, dx = i; dx < 19; dx++, dy++) {				// i = dx의 시작점


				if (i < 15) {		// i가 15보다 작아야 우측 아래 대각선으로 돌  5개를 둘 수 있음

					if (LDH_Board[dy][dx] == 1) {									// 백돌이 있다면

						if (dx < 18 && LDH_Board[dy + 1][dx + 1] == 1) {						// 백돌 현재 2개 연속

							if (dx < 17 && LDH_Board[dy + 2][dx + 2] == 1) {						//  백돌 @ @ @

								if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 1) {		// 백돌 @ @ @ @

									if (dy == 0 && (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3)) {		// 위쪽 벽에 붙어 오른쪽 아래로 내려가는  @ @ @ @
										LDH_Board[dy + 4][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;		// 스택에 저장
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dx == 15 && (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3)) {		// 오른쪽 아래로 내려가는 @ @ @ @ 가 오른쪽 벽에 붙어있는 경우
										LDH_Board[dy - 1][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dy > 0 && dx < 15) {												// 벽에 붙지 않은 @ @ @ @
										if (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3) {				// 왼쪽 위가 빔
											LDH_Board[dy - 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3) {				// 오른쪽 아래가 빔
											LDH_Board[dy + 4][dx + 4] = 4;

											Warning_ldh[wstack_ldh].x = dx + 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4개 연속 닫음

								// ----------- 3개 연속 ---------------- //


								if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 1) {			// @ @ @ 0 @ 상태								// dx + 4 가 18을 넘어가면 메모리 액세스 거부가 일어나는가?  	ex)  LDH_Board[20][20]==2   ????		 dx를 먼저 검사해 해결

									if (dy == 0) {			// 위쪽 벽에 붙은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// 위쪽 벽에 붙지 않은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

								}		// @ @ @ 0 @ 상태 검사 닫음

								else {			 // @ @ @ 상태		@ @ @ 의 두칸 오른쪽은 백돌 이 아님

									if (dy == 0) {							// 위쪽 벽에 붙은 @ @ @	

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// 오른쪽 아래가 비어있음
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dx == 16) {					// 오른쪽 벽에 붙은 @ @ @

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// 왼쪽 위가 비어있음
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dy > 0 && dx < 16) {									// 벽에 붙지 않은 @ @ @

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// 오른쪽 아래가 비어있음
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// 왼쪽 위가 비어있음
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3개 연속된것 검사 닫음

							else if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 1) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

								if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 1 && (LDH_Board[dy + 2][dx + 2] == 0 || LDH_Board[dy + 2][dx + 2] == 3)) {		// @ @ 0 @ @ 상황 일 때
									LDH_Board[dy + 2][dx + 2] = 4;

									Warning_ldh[wstack_ldh].x = dx + 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dy == 0 && LDH_Board[dy + 2][dx + 2] == 0) {		// 위쪽 벽에 붙은 @ @ 0 @						 왼쪽 위가 벽이고 사이가 비어있어야 체크함

									if (LDH_Board[dy + 4][dx + 4] == 0) {			// @ @ 0 @ 의 오른쪽이 비어있으면
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dx == 15) && LDH_Board[dy + 2][dx + 2] == 0) {	// 오른쪽 벽에 붙은 @ @ 0 @

									if (LDH_Board[dy - 1][dx - 1] == 0) {				// @ @ 0 @ 의 왼쪽이 비어있으면
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dx < 15) {				// 벽에 막히지 않은 @ @ 0 @
																			// @ @ 0 @ 에서 막힌 곳이 없다면 3으로 만듬
									if (LDH_Board[dy - 1][dx - 1] == 0) {
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 2][dx + 2] == 0) {
										LDH_Board[dy + 2][dx + 2] = 3;

										Hint_ldh[hstack_ldh].x = dx + 2;
										Hint_ldh[hstack_ldh].y = dy + 2;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx + 4] == 0) {
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

							}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


						}		// 2개 연속 닫음

						// ------------------- 1개 후 연속 검사 ------------

						else if (dx < 18 && LDH_Board[dy + 1][dx + 1] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

							if (dx < 17 && LDH_Board[dy + 2][dx + 2] == 1) {		// @ 0 @ 상태

								if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 1) {		// @ 0 @ @ 상태

									if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 1) {		// @ 0 @ @ @ 상태

										if (LDH_Board[dy + 1][dx + 1] == 0 || LDH_Board[dy + 1][dx + 1] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
											LDH_Board[dy + 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// 위에 3칸 검사에서 다음걸 검사하므로 dx+5가 비어있는지 검사할 필요 x
										}

									}		//  @ 0 @ @ @ 상태 검사 닫음

									else if (dx < 16) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

										if (dy == 0) {				// 위쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy + 4][dx + 4] == 0) {				// 오른쪽을 막으면 아예 막히므로 오른쪽만 검사
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dx == 15) {		// 오른쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {				// 왼쪽을 막으면 아예 막히므로 오른쪽만 검사
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy > 0 && dx < 15) {						// 벽에 붙지 않은 @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 4][dx + 4] == 0) {
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 1][dx + 1] == 0) {
												LDH_Board[dy + 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy + 1;
												hstack_ldh++;
											}

										}

									}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


								} // @ 0 @ @ 상태 검사 닫음

							}	// @ 0 @ 상태 검사 닫음

						}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

					}		// 1개 연속 닫음

				}		// i < 15 닫음

			}
		}


		for (int i = 1; i < 19; i++) {		// 우측 하단 대각선 기준 아래쪽
			for (int dx = 0, dy = i; dy < 19; dx++, dy++) {				// i = dy의 시작점				 무조건 dy가 dx보다 큼


				if (i < 15) {		// i가 15보다 작아야 우측 아래 대각선으로 돌  5개를 둘 수 있음

					if (LDH_Board[dy][dx] == 1) {									// 백돌이 있다면

						if (dy < 18 && LDH_Board[dy + 1][dx + 1] == 1) {						// 백돌 현재 2개 연속

							if (dy < 17 && LDH_Board[dy + 2][dx + 2] == 1) {						//  백돌 @ @ @

								if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 1) {		// 백돌 @ @ @ @

									if (dx == 0 && (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3)) {		// 왼쪽 벽에 붙어 오른쪽 아래로 내려가는  @ @ @ @
										LDH_Board[dy + 4][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;		// 스택에 저장
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dy == 15 && (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3)) {		// 오른쪽 아래로 내려가는 @ @ @ @ 가 아래쪽 벽에 붙어있는 경우
										LDH_Board[dy - 1][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx > 0 && dy < 15) {												// 벽에 붙지 않은 @ @ @ @
										if (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3) {				// 왼쪽 위가 빔
											LDH_Board[dy - 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3) {				// 오른쪽 아래가 빔
											LDH_Board[dy + 4][dx + 4] = 4;

											Warning_ldh[wstack_ldh].x = dx + 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4개 연속 닫음

								// ----------- 3개 연속 ---------------- //


								if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 1) {			// @ @ @ 0 @ 상태								// dx + 4 가 18을 넘어가면 메모리 액세스 거부가 일어나는가?  	ex)  LDH_Board[20][20]==2   ????		 dx를 먼저 검사해 해결

									if (dx == 0) {			// 왼쪽 벽에 붙은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// 왼쪽 벽에 붙지 않은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

								}		// @ @ @ 0 @ 상태 검사 닫음

								else {			 // @ @ @ 상태		@ @ @ 의 두칸 오른쪽은 백돌 이 아님

									if (dx == 0) {							// 왼쪽 벽에 붙은 @ @ @	

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// 오른쪽 아래가 비어있음
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dy == 16) {					// 아래쪽 벽에 붙은 @ @ @

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// 왼쪽 위가 비어있음
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dx > 0 && dy < 16) {									// 벽에 붙지 않은 @ @ @

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// 오른쪽 아래가 비어있음
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// 왼쪽 위가 비어있음
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3개 연속된것 검사 닫음

							else if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 1) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

								if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 1 && (LDH_Board[dy + 2][dx + 2] == 0 || LDH_Board[dy + 2][dx + 2] == 3)) {		// @ @ 0 @ @ 상황 일 때
									LDH_Board[dy + 2][dx + 2] = 4;

									Warning_ldh[wstack_ldh].x = dx + 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dx == 0 && LDH_Board[dy + 2][dx + 2] == 0) {		// 왼쪽 벽에 붙은 @ @ 0 @						 왼쪽 위가 벽이고 사이가 비어있어야 체크함

									if (LDH_Board[dy + 4][dx + 4] == 0) {			// @ @ 0 @ 의 오른쪽이 비어있으면
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dy == 15) && LDH_Board[dy + 2][dx + 2] == 0) {	// 아래쪽 벽에 붙은 @ @ 0 @

									if (LDH_Board[dy - 1][dx - 1] == 0) {				// @ @ 0 @ 의 왼쪽이 비어있으면
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dx > 0 && dy < 15) {				// 벽에 막히지 않은 @ @ 0 @
																			// @ @ 0 @ 에서 막힌 곳이 없다면 3으로 만듬
									if (LDH_Board[dy - 1][dx - 1] == 0) {
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 2][dx + 2] == 0) {
										LDH_Board[dy + 2][dx + 2] = 3;

										Hint_ldh[hstack_ldh].x = dx + 2;
										Hint_ldh[hstack_ldh].y = dy + 2;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx + 4] == 0) {
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

							}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


						}		// 2개 연속 닫음

						// ------------------- 1개 후 연속 검사 ------------

						else if (dy < 18 && LDH_Board[dy + 1][dx + 1] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

							if (dy < 17 && LDH_Board[dy + 2][dx + 2] == 1) {		// @ 0 @ 상태

								if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 1) {		// @ 0 @ @ 상태

									if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 1) {		// @ 0 @ @ @ 상태

										if (LDH_Board[dy + 1][dx + 1] == 0 || LDH_Board[dy + 1][dx + 1] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
											LDH_Board[dy + 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// 위에 3칸 검사에서 다음걸 검사하므로 dx+5가 비어있는지 검사할 필요 x
										}

									}		//  @ 0 @ @ @ 상태 검사 닫음

									else if (dy < 16) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

										if (dx == 0) {				// 왼쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy + 4][dx + 4] == 0) {				// 오른쪽을 막으면 아예 막히므로 오른쪽만 검사		위에서 i<15 이므로 왼쪽 벽에 붙은 dy=15 일 경우 검사 자체를 하지 않음
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dy == 15) {		// 아래쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {				// 왼쪽을 막으면 아예 막히므로 오른쪽만 검사
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dx > 0 && dy < 15) {						// 벽에 붙지 않은 @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 4][dx + 4] == 0) {
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 1][dx + 1] == 0) {
												LDH_Board[dy + 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy + 1;
												hstack_ldh++;
											}

										}

									}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


								} // @ 0 @ @ 상태 검사 닫음

							}	// @ 0 @ 상태 검사 닫음

						}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

					}		// 1개 연속 닫음

				}		// i < 15 닫음

			}
		}


		for (int i = 0; i < 19; i++) {		// 좌측 하단 대각선 기준 위쪽
			for (int dy = 0, dx = i; dx >= 0; dx--, dy++) {				// i = dx의 시작점	


				if (i > 3) {		// i가 3보다 커야 좌측 하단으로 돌 5개를 둘 수 있음						dx 가 3보다 클 때 검사

					if (LDH_Board[dy][dx] == 1) {									// 백돌이 있다면

						if (dx > 0 && LDH_Board[dy + 1][dx - 1] == 1) {						// 백돌 현재 2개 연속

							if (dx > 1 && LDH_Board[dy + 2][dx - 2] == 1) {						//  백돌 @ @ @

								if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 1) {		// 백돌 @ @ @ @

									if (dy == 0 && (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3)) {		// 위쪽 벽에 붙어 왼쪽 아래로 내려가는  @ @ @ @
										LDH_Board[dy + 4][dx - 4] = 4;															// 왼쪽 아래가 빔

										Warning_ldh[wstack_ldh].x = dx - 4;		// 스택에 저장
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dx == 3 && (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3)) {		// 왼쪽 아래로 내려가는 @ @ @ @ 가 왼쪽 벽에 붙어있는 경우
										LDH_Board[dy - 1][dx + 1] = 4;																// 오른쪽 위가 빔

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx > 3 && dy > 0) {												// 벽에 붙지 않은 @ @ @ @
										if (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3) {				// 오른쪽 위가 빔
											LDH_Board[dy - 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3) {				// 왼쪽 아래가 빔
											LDH_Board[dy + 4][dx - 4] = 4;

											Warning_ldh[wstack_ldh].x = dx - 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4개 연속 닫음

								// ----------- 3개 연속 ---------------- //


								if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 1) {			// @ @ @ 0 @ 상태								// dx + 4 가 18을 넘어가면 메모리 액세스 거부가 일어나는가?  	ex)  LDH_Board[20][20]==2   ????		 dx를 먼저 검사해 해결

									if (dy == 0) {			// 위쪽 벽에 붙은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// 위쪽 벽에 붙지 않은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

								}		// @ @ @ 0 @ 상태 검사 닫음

								else {			 // @ @ @ 상태		@ @ @ 의 두칸 왼쪽은 백돌 이 아님

									if (dy == 0) {							// 위쪽 벽에 붙은 @ @ @	

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// 왼쪽 아래가 비어있음
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dx == 1) {					// 왼쪽 벽에 붙은 @ @ @

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// 오른쪽 위가 비어있음
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dy > 0 && dx > 2) {									// 벽에 붙지 않은 @ @ @

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// 왼쪽 아래가 비어있음
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// 오른쪽 위가 비어있음
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3개 연속된것 검사 닫음

							else if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 1) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

								if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 1 && (LDH_Board[dy + 2][dx - 2] == 0 || LDH_Board[dy + 2][dx - 2] == 3)) {		// @ @ 0 @ @ 상황 일 때
									LDH_Board[dy + 2][dx - 2] = 4;

									Warning_ldh[wstack_ldh].x = dx - 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dy == 0 && LDH_Board[dy + 2][dx - 2] == 0) {		// 위쪽 벽에 붙은 @ @ 0 @						 오른쪽 위가 벽이고 사이가 비어있어야 체크함

									if (LDH_Board[dy + 4][dx - 4] == 0) {			// @ @ 0 @ 의 왼쪽 아래가 비어있으면
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dx == 3) && LDH_Board[dy + 2][dx - 2] == 0) {	// 왼쪽 벽에 붙은 @ @ 0 @

									if (LDH_Board[dy - 1][dx + 1] == 0) {				// @ @ 0 @ 의 오른쪽 위가 비어있으면
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dx > 3) {				// 벽에 막히지 않은 @ @ 0 @
																			// @ @ 0 @ 에서 막힌 곳이 없다면 3으로 만듬
									if (LDH_Board[dy - 1][dx + 1] == 0) {
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 2][dx - 2] == 0) {
										LDH_Board[dy + 2][dx - 2] = 3;

										Hint_ldh[hstack_ldh].x = dx - 2;
										Hint_ldh[hstack_ldh].y = dy + 2;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx - 4] == 0) {
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

							}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


						}		// 2개 연속 닫음

						// ------------------- 1개 후 연속 검사 ------------

						else if (dx > 0 && LDH_Board[dy + 1][dx - 1] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

							if (dx > 1 && LDH_Board[dy + 2][dx - 2] == 1) {		// @ 0 @ 상태

								if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 1) {		// @ 0 @ @ 상태

									if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 1) {		// @ 0 @ @ @ 상태

										if (LDH_Board[dy + 1][dx - 1] == 0 || LDH_Board[dy + 1][dx - 1] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
											LDH_Board[dy + 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// 위에 3칸 검사에서 다음걸 검사하므로 dx+5가 비어있는지 검사할 필요 x
										}

									}		//  @ 0 @ @ @ 상태 검사 닫음

									else if (dx > 2) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

										if (dy == 0) {				// 위쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy + 4][dx - 4] == 0) {				// 왼쪽 아래를 막으면 아예 막히므로 왼쪽만 검사		위에서 i>3 이므로 위쪽 벽에 붙은 dx=3 일 경우 검사 자체를 하지 않음
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dx == 3) {		// 왼쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {				// 오른쪽 위를 막으면 아예 막히므로 오른쪽만 검사
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy > 0 && dx > 3) {						// 벽에 붙지 않은 @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 4][dx - 4] == 0) {
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 1][dx - 1] == 0) {
												LDH_Board[dy + 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy + 1;
												hstack_ldh++;
											}

										}

									}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


								} // @ 0 @ @ 상태 검사 닫음

							}	// @ 0 @ 상태 검사 닫음

						}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

					}	// 1개 연속 닫음

				}	// i > 3 닫음

			}
		}


		for (int i = 1; i < 19; i++) {		// 좌측 하단 대각선 기준 아래쪽
			for (int dx = 18, dy = i; dy < 19; dx--, dy++) {				// i = dy의 시작점	


				if (i < 15) {		// i가 15보다 작아야 좌측 하단으로 돌 5개를 둘 수 있음	

					if (LDH_Board[dy][dx] == 1) {									// 백돌이 있다면

						if (dy < 18 && LDH_Board[dy + 1][dx - 1] == 1) {						// 백돌 현재 2개 연속

							if (dy < 17 && LDH_Board[dy + 2][dx - 2] == 1) {						//  백돌 @ @ @

								if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 1) {		// 백돌 @ @ @ @

									if (dx == 18 && (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3)) {		// 오른쪽 벽에 붙어 왼쪽 아래로 내려가는  @ @ @ @
										LDH_Board[dy + 4][dx - 4] = 4;															// 왼쪽 아래가 빔

										Warning_ldh[wstack_ldh].x = dx - 4;		// 스택에 저장
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dy == 15 && (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3)) {		// 왼쪽 아래로 내려가는 @ @ @ @ 가 아래쪽 벽에 붙어있는 경우
										LDH_Board[dy - 1][dx + 1] = 4;																// 오른쪽 위가 빔

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx < 18 && dy < 15) {												// 벽에 붙지 않은 @ @ @ @
										if (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3) {				// 오른쪽 위가 빔
											LDH_Board[dy - 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3) {				// 왼쪽 아래가 빔
											LDH_Board[dy + 4][dx - 4] = 4;

											Warning_ldh[wstack_ldh].x = dx - 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4개 연속 닫음

								// ----------- 3개 연속 ---------------- //


								if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 1) {			// @ @ @ 0 @ 상태	

									if (dx == 18) {			// 오른쪽 벽에 붙은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// 오른쪽 벽에 붙지 않은 @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

								}		// @ @ @ 0 @ 상태 검사 닫음

								else {			 // @ @ @ 상태		@ @ @ 의 두칸 왼쪽은 백돌 이 아님

									if (dx == 18) {							// 오른쪽 벽에 붙은 @ @ @	

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// 왼쪽 아래가 비어있음
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dy == 16) {					// 아래 벽에 붙은 @ @ @

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// 오른쪽 위가 비어있음
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dx < 18 && dy < 16) {									// 벽에 붙지 않은 @ @ @

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// 왼쪽 아래가 비어있음
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// 오른쪽 위가 비어있음
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3개 연속된것 검사 닫음

							else if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 1) {			// 3칸 바로 연속이 아닌 @ @ 0 @ 상황

								if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 1 && (LDH_Board[dy + 2][dx - 2] == 0 || LDH_Board[dy + 2][dx - 2] == 3)) {		// @ @ 0 @ @ 상황 일 때
									LDH_Board[dy + 2][dx - 2] = 4;

									Warning_ldh[wstack_ldh].x = dx - 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dx == 18 && LDH_Board[dy + 2][dx - 2] == 0) {		// 오른쪽 벽에 붙은 @ @ 0 @						 오른쪽 위가 벽이고 사이가 비어있어야 체크함

									if (LDH_Board[dy + 4][dx - 4] == 0) {			// @ @ 0 @ 의 왼쪽 아래가 비어있으면
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dy == 15) && LDH_Board[dy + 2][dx - 2] == 0) {	// 아래쪽 벽에 붙은 @ @ 0 @

									if (LDH_Board[dy - 1][dx + 1] == 0) {				// @ @ 0 @ 의 오른쪽 위가 비어있으면
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy < 15 && dx < 18) {				// 벽에 막히지 않은 @ @ 0 @
																			// @ @ 0 @ 에서 막힌 곳이 없다면 3으로 만듬
									if (LDH_Board[dy - 1][dx + 1] == 0) {
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 2][dx - 2] == 0) {
										LDH_Board[dy + 2][dx - 2] = 3;

										Hint_ldh[hstack_ldh].x = dx - 2;
										Hint_ldh[hstack_ldh].y = dy + 2;
										hstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx - 4] == 0) {
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

							}	// @ @ 0 @ ~		 2칸연속 후 1칸띄고 연속 검사 닫음


						}		// 2개 연속 닫음

						// ------------------- 1개 후 연속 검사 ------------

						else if (dy < 18 && LDH_Board[dy + 1][dx - 1] == 0) {		// 1개 있고 한칸 띄어있는 상태  @ 0 ??

							if (dy < 17 && LDH_Board[dy + 2][dx - 2] == 1) {		// @ 0 @ 상태

								if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 1) {		// @ 0 @ @ 상태

									if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 1) {		// @ 0 @ @ @ 상태

										if (LDH_Board[dy + 1][dx - 1] == 0 || LDH_Board[dy + 1][dx - 1] == 3) {		// 사이가 비어있다면			벽에 붙나 안붙나 같으므로 이것만 검사함
											LDH_Board[dy + 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// 위에 3칸 검사에서 다음걸 검사하므로 dx+5가 비어있는지 검사할 필요 x
										}

									}		//  @ 0 @ @ @ 상태 검사 닫음

									else if (dy < 16) {		// @ 0 @ @  상태  이 바로뒤에 @가 아님

										if (dx == 18) {				// 오른쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy + 4][dx - 4] == 0) {				// 왼쪽 아래를 막으면 아예 막히므로 왼쪽만 검사		위에서 i<15 이므로 오른쪽 벽에 붙은 dy=15 일 경우 검사 자체를 하지 않음
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dy == 15) {		// 아래쪽 벽에 붙은 @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {				// 오른쪽 위를 막으면 아예 막히므로 오른쪽만 검사
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy < 15 && dx < 18) {						// 벽에 붙지 않은 @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 4][dx - 4] == 0) {
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

											if (LDH_Board[dy + 1][dx - 1] == 0) {
												LDH_Board[dy + 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy + 1;
												hstack_ldh++;
											}

										}

									}		// @ 0 @ @,  바로뒤에 @가 아닌 상태 검사 닫음


								} // @ 0 @ @ 상태 검사 닫음

							}	// @ 0 @ 상태 검사 닫음

						}	// 1칸 있고 다음칸이 빈칸인 상태 검사 닫음

					}	// 1개 연속 닫음

				}	// i < 15 닫음

			}
		}

		// ---------- 대각선 검사 ------------------


		// 임시 공격 ---------------------


		if (wstack_ldh > 0) {		//	바로 둬야할 곳이 있으면
			*x = Warning_ldh[0].x;
			*y = Warning_ldh[0].y;

			LDH_Board[*y][*x] = 2;
		}

		else if (hstack_ldh > 0) {		// 막아야 할 곳이 있으면
			*x = Hint_ldh[0].x;
			*y = Hint_ldh[0].y;

			LDH_Board[*y][*x] = 2;
		}

		else {									// 막아야 할 곳이 없으면

			for (int i = 0; i < 13; i++) {
				for (int j = 0; j < 13; j++) {
					Check_ldh[i][j].count = 0;
				}
			}

			for (int dy = 0; dy < 13; dy+=3) {						// 7*7 짜리 판으로 나누어 내 돌의 갯수를 셈
				for (int dx = 0; dx < 13; dx+=3) {

					for (int i = 0; i < 7; i++) {							// 7 * 7 칸에 속한 자기 돌을 셈
						for (int j = 0; j < 7; j++) {

							if (LDH_Board[dy + i][dx + j] == 2) {
								Check_ldh[checky_ldh][checkx_ldh].count++;

							}

						}
					}

					checkx_ldh++;
				}

				checkx_ldh = 0;
				checky_ldh++;
			}


			for (int dy = 0; dy < 13; dy++) {							// 구역중 가장 많은 돌이 몇개인지를 찾아냄
				for (int dx = 0; dx < 13; dx++) {

					if (Check_ldh[dy][dx].count > maxstone_ldh) {
						maxstone_ldh = Check_ldh[dy][dx].count;
					}

				}
			}

			for (int dy = 0; dy < 13; dy++) {							// 가장 많은 돌이 어느구역인지 찾아냄
				for (int dx = 0; dx < 13; dx++) {

					if (Check_ldh[dy][dx].count == maxstone_ldh) {
						checky_ldh = dy;
						checkx_ldh = dx;
						break;
					}

				}
			}

			while (1) {
				rx = rand() % 7 + checkx_ldh;
				ry = rand() % 7 + checky_ldh;

				for (int dy = checky_ldh; dy < checky_ldh + 7; dy++) {
					for (int dx = checkx_ldh; dx < checkx_ldh + 7; dx++) {
						if (LDH_Board[dy][dx] == 1 || LDH_Board[dy][dx] == 2) {
							checkstone_ldh++;
						}
					}
				}

				if (checkstone_ldh > 30) {					// 구역의 돌이 많으면 다른 구역으로 넘어감
					checkx_ldh = rand() % 12;
					checky_ldh = rand() % 12;
				}

				if (LDH_Board[ry][rx] != 1 && LDH_Board[ry][rx] != 2) {
					break;
				}
			}

			*x = rx;
			*y = ry;

			LDH_Board[*y][*x] = 2;
		}


	}

}

void WhiteDefence_2018182024(int x, int y)
{
	LDH_Board[y][x] = 1;
}