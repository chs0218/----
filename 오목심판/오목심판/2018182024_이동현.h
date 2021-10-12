#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <random>

// ���� 19*19 ��



int LDH_Board[19][19] = { 0, };

// ���� 1  ���浹 2   ��Ʈ 3   ��� 4   ���� 5   ������ 6

typedef struct Stone {
	int x;
	int y;
}Hint;

typedef struct CStone {
	int count;
}Check;

int hstack_ldh = 0;
int wstack_ldh = 0;


Hint Hint_ldh[100];			// ���ƾ� �Ұ��� ����Ǵ� ����		ä�� ������ ����Ŵ
Hint Warning_ldh[20];		// �ٷ� ���ƾ� �� ���� ����Ǵ� ����	ä�� ������ ����Ŵ

Check Check_ldh[13][13];

int checky_ldh = 0;
int checkx_ldh = 0;
int maxstone_ldh = 0;

int checkstone_ldh = 9;

void BlackAttack_2018182024(int *x, int *y)
{
	int rx, ry;

	hstack_ldh = 0;				// �Ź� �˻���� �Ҷ����� ������ 0���� ����
	wstack_ldh = 0;	
	checkx_ldh = 0;
	checky_ldh = 0;
	checkstone_ldh = 0;


	srand((unsigned int)time(NULL));

	if (LDH_Board[13][13] == 0) {			// �� ó���� ��� ��		13,13 �� ����ִ��� �Ǵ��� ������� ������ �� ó�� �� ���ʰ� �ƴ�
		*x = 13;
		*y = 13;

		LDH_Board[13][13] = 1;
	}

	else {								// ù���� �ƴ϶��


		// ---------- ���� �˻� ------------------

		for (int dy = 0; dy < 19; dy++) {					// �鵹 ���� �˻�
			for (int dx = 0; dx < 19; dx++) {

				if (LDH_Board[dy][dx] == 2) {									// �鵹�� �ִٸ�

					if (dx < 18 && LDH_Board[dy][dx + 1] == 2) {						// �鵹 ���� 2�� ����

						if (dx < 17 && LDH_Board[dy][dx + 2] == 2) {						//  �鵹 @ @ @

							if (dx < 16 && LDH_Board[dy][dx + 3] == 2) {		// �鵹 @ @ @ @

								if (dx == 0 && (LDH_Board[dy][dx + 4] == 0 || LDH_Board[dy][dx + 4] == 3)) {		// ���� ���� ����  @ @ @ @
									LDH_Board[dy][dx + 4] = 4;

									Warning_ldh[wstack_ldh].x = dx + 4;		// ���ÿ� ����
									Warning_ldh[wstack_ldh].y = dy;
									wstack_ldh++;
								}

								else if (dx == 15 && (LDH_Board[dy][dx - 1] == 0 || LDH_Board[dy][dx - 1] == 3)) {	// ������ ���� ���� @ @ @ @
									LDH_Board[dy][dx - 1] = 4;

									Warning_ldh[wstack_ldh].x = dx - 1;
									Warning_ldh[wstack_ldh].y = dy;
									wstack_ldh++;
								}

								else if (dx > 0 && dx < 15) {												// ���� ���� ���� @ @ @ @
									if (LDH_Board[dy][dx - 1] == 0 || LDH_Board[dy][dx - 1] == 3) {				// ������ ��
										LDH_Board[dy][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}

									if (LDH_Board[dy][dx + 4] == 0 || LDH_Board[dy][dx + 4] == 3) {				// �������� ��
										LDH_Board[dy][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}
								}

							}		// 4�� ���� ����

							// ----------- 3�� ���� ---------------- //

							if (dx < 15 && LDH_Board[dy][dx + 4] == 2) {			// @ @ @ 0 @ ����
								
								if (dx == 0) {			// ���� ���� ���� @ @ @ 0 @
									if (LDH_Board[dy][dx + 3] == 0 || LDH_Board[dy][dx + 3] == 3) {
										LDH_Board[dy][dx + 3] = 4;

										Warning_ldh[wstack_ldh].x = dx + 3;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}
								}

								else {						// ������ ���� ���� @ @ @ 0 @ or ���� ���� ���� @ @ @ 0 @
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

							}		// @ @ @ 0 @ ���� �˻� ����

							else {			 // @ @ @ ����		@ @ @ �� ��ĭ �������� �鵹 �� �ƴ�

								if (dx == 0) {							// ���� ���� ���� @ @ @	

									if (LDH_Board[dy][dx + 3] == 0) {		// �������� �������
										LDH_Board[dy][dx + 3] = 3;

										Hint_ldh[hstack_ldh].x = dx + 3;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}

								else if (dx == 16) {					// ������ ���� ���� @ @ @

									if (LDH_Board[dy][dx - 1] == 0) {		// ������ �������
										LDH_Board[dy][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}

								else if (dx > 0 && dx < 16) {									// ���� ���� ���� @ @ @

									if (LDH_Board[dy][dx + 3] == 0) {		// �������� �������
										LDH_Board[dy][dx + 3] = 3;

										Hint_ldh[hstack_ldh].x = dx + 3;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}

									if (LDH_Board[dy][dx - 1] == 0) {		// ������ �������
										LDH_Board[dy][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}
							}

						}		// 3�� ���ӵȰ� �˻� ����

						else if (dx < 16 && LDH_Board[dy][dx+3] == 2) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

							if (dx < 15 && LDH_Board[dy][dx + 4] == 2 && (LDH_Board[dy][dx + 2] == 0 || LDH_Board[dy][dx + 2] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
								LDH_Board[dy][dx + 2] = 4;

								Warning_ldh[wstack_ldh].x = dx + 2;
								Warning_ldh[wstack_ldh].y = dy;
								wstack_ldh++;
							}

							else if (dx == 0 && LDH_Board[dy][dx + 2] == 0) {		// ������ ���� @ @ 0 @								 ������ ���̰� ���̰� ����־�� üũ��
							
								if (LDH_Board[dy][dx + 4] == 0) {			// @ @ 0 @ �� �������� ���������
									LDH_Board[dy][dx + 4] = 3;

									Hint_ldh[hstack_ldh].x = dx + 4;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}
							}

							else if ((dx == 15) && LDH_Board[dy][dx + 2] == 0) {	// �������� ���� @ @ 0 @
								
								if (LDH_Board[dy][dx - 1] == 0) {				// @ @ 0 @ �� ������ ���������
									LDH_Board[dy][dx - 1] = 3;

									Hint_ldh[hstack_ldh].x = dx - 1;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}
							}

							else if (dx > 0 && dx < 15) {				// ���� ������ ���� @ @ 0 @
																		// @ @ 0 @ ���� ���� ���� ���ٸ� !�� ����
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

						}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����
						

					}		// 2�� ���� ����

					// ------------------- 1�� �� ���� �˻� ------------

					else if (dx < 18 && LDH_Board[dy][dx + 1] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??
						
						if (dx < 17 && LDH_Board[dy][dx + 2] == 2) {		// @ 0 @ ����

							if (dx < 16 && LDH_Board[dy][dx + 3] == 2) {		// @ 0 @ @ ����

								if (dx < 15 && LDH_Board[dy][dx + 4] == 2) {		// @ 0 @ @ @ ����

									if (LDH_Board[dy][dx + 1] == 0 || LDH_Board[dy][dx + 1] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
										LDH_Board[dy][dx + 1] = 4;

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;

										// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dx+5�� ����ִ��� �˻��� �ʿ� x
									}

								}		//  @ 0 @ @ @ ���� �˻� ����

								else if (dx < 16) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

									if (dx == 0) {				// ���� ���� ���� @ 0 @ @
										
										if (LDH_Board[dy][dx + 4] == 0) {				// �������� ������ �ƿ� �����Ƿ� �����ʸ� �˻�
											LDH_Board[dy][dx + 4] = 3;

											Hint_ldh[hstack_ldh].x = dx + 4;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

									}

									else if (dx == 15) {		// ������ ���� ���� @ 0 @ @

										if (LDH_Board[dy][dx - 1] == 0) {				// ������ ������ �ƿ� �����Ƿ� �����ʸ� �˻�
											LDH_Board[dy][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

									}

									else if (dx > 0 && dx < 15) {						// ���� ���� ���� @ 0 @ @

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

								}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


							} // @ 0 @ @ ���� �˻� ����

						}	// @ 0 @ ���� �˻� ����

					}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

				}		// 1�� ���� ����


			}
		}

		// ---------- ���� �˻� ------------------



		// ---------- ���� �˻� ------------------

		for (int dx = 0; dx < 19; dx++) {					// �鵹 ���� �˻�
			for (int dy = 0; dy < 19; dy++) {

				if (LDH_Board[dy][dx] == 2) {									// �鵹�� �ִٸ�

					if (dy < 18 && LDH_Board[dy + 1][dx] == 2) {						// �鵹 ���� 2�� ����

						if (dy < 17 && LDH_Board[dy + 2][dx] == 2) {						//  �鵹 @ @ @

							if (dy < 16 && LDH_Board[dy + 3][dx] == 2) {		// �鵹 @ @ @ @

								if (dy == 0 && (LDH_Board[dy + 4][dx] == 0 || LDH_Board[dy + 4][dx] == 3)) {		// ���� ���� ����  @ @ @ @
									LDH_Board[dy + 4][dx] = 4;

									Warning_ldh[wstack_ldh].x = dx;		// ���ÿ� ����
									Warning_ldh[wstack_ldh].y = dy + 4;
									wstack_ldh++;
								}

								else if (dy == 15 && (LDH_Board[dy - 1][dx] == 0 || LDH_Board[dy - 1][dx] == 3)) {	// �Ʒ��� ���� ���� @ @ @ @
									LDH_Board[dy - 1][dx] = 4;

									Warning_ldh[wstack_ldh].x = dx;
									Warning_ldh[wstack_ldh].y = dy - 1;
									wstack_ldh++;
								}

								else if (dy > 0 && dy < 15) {												// ���� ���� ���� @ @ @ @
									if (LDH_Board[dy - 1][dx] == 0 || LDH_Board[dy - 1][dx] == 3) {				// ������ ��
										LDH_Board[dy - 1][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx] == 0 || LDH_Board[dy + 4][dx] == 3) {				// �Ʒ����� ��
										LDH_Board[dy + 4][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}
								}

							}		// 4�� ���� ����

							// ----------- 3�� ���� ---------------- //

							if (dy < 15 && LDH_Board[dy + 4][dx] == 2) {			// @ @ @ 0 @ ����

								if (dy == 0) {			// ���� ���� ���� @ @ @ 0 @
									if (LDH_Board[dy + 3][dx] == 0 || LDH_Board[dy + 3][dx] == 3) {
										LDH_Board[dy + 3][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 3;
										wstack_ldh++;
									}
								}

								else {						// �Ʒ��� ���� ���� @ @ @ 0 @ or ���� ���� ���� @ @ @ 0 @
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

							}		// @ @ @ 0 @ ���� �˻� ����

							else {			 // @ @ @ ����

								if (dy == 0) {							// ���� ���� ���� @ @ @	

									if (LDH_Board[dy + 3][dx] == 0) {		// �Ʒ����� �������
										LDH_Board[dy + 3][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy + 3;
										hstack_ldh++;
									}
								}

								else if (dy == 16) {					// �Ʒ��� ���� ���� @ @ @

									if (LDH_Board[dy - 1][dx] == 0) {		// ������ �������
										LDH_Board[dy - 1][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dy < 16) {									// ���� ���� ���� @ @ @

									if (LDH_Board[dy + 3][dx] == 0) {		// �Ʒ����� �������
										LDH_Board[dy + 3][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy + 3;
										hstack_ldh++;
									}

									if (LDH_Board[dy - 1][dx] == 0) {		// ������ �������
										LDH_Board[dy - 1][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}
							}

						}		// 3�� ���ӵȰ� �˻� ����

						else if (dy < 16 && LDH_Board[dy + 3][dx] == 2) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

							if (dy < 15 && LDH_Board[dy + 4][dx] == 2 && (LDH_Board[dy + 2][dx] == 0 || LDH_Board[dy + 2][dx] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
								LDH_Board[dy + 2][dx] = 4;

								Warning_ldh[wstack_ldh].x = dx;
								Warning_ldh[wstack_ldh].y = dy + 2;
								wstack_ldh++;
							}

							else if (dy == 0 && LDH_Board[dy + 2][dx] == 0) {		// ������ ���� @ @ 0 @								 ������ ���̰� ���̰� ����־�� üũ��
								
								if (LDH_Board[dy + 4][dx] == 0) {			// @ @ 0 @ �� �Ʒ����� ���������			������ ���� ��� �Ʒ��� ������ �����Ƿ� �Ʒ��� �˻���
									LDH_Board[dy + 4][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy + 4;
									hstack_ldh++;
								}
							}

							else if (dy == 15 && LDH_Board[dy + 2][dx] == 0) {		// �Ʒ����� ���� @ @ 0 @
								
								if (LDH_Board[dy - 1][dx] == 0) {					// @ @ 0 @ �� ������ ���������		�Ʒ����� ���� ��� ���� ������ �����Ƿ� �Ʒ��� �˻���
									LDH_Board[dy - 1][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy - 1;
									hstack_ldh++;
								}
							}		

							else if (dy > 0 && dy < 15) {				// ���� ������ ���� @ @ 0 @
																		// @ @ 0 @ ���� ���� ���� ���ٸ� !�� ����
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

						}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


					}		// 2�� ���� ����

					// ------------------- 1�� �� ���� �˻� ------------

					else if (dy < 18 && LDH_Board[dy + 1][dx] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

						if (dy < 17 && LDH_Board[dy + 2][dx] == 2) {		// @ 0 @ ����

							if (dy < 16 && LDH_Board[dy + 3][dx] == 2) {		// @ 0 @ @ ����

								if (dy < 15 && LDH_Board[dy + 4][dx] == 2) {		// @ 0 @ @ @ ����

									if (LDH_Board[dy + 1][dx] == 0 || LDH_Board[dy + 1][dx] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
										LDH_Board[dy + 1][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 1;
										wstack_ldh++;

										// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dy+5�� ����ִ��� �˻��� �ʿ� x
									}

								}		//  @ 0 @ @ @ ���� �˻� ����

								else if (dy < 16) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

									if (dy == 0) {				// ���� ���� ���� @ 0 @ @

										if (LDH_Board[dy + 4][dx] == 0) {				// �Ʒ����� ������ �ƿ� �����Ƿ� �Ʒ��ʸ� �˻�
											LDH_Board[dy + 4][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy + 4;
											hstack_ldh++;
										}

									}

									else if (dy == 15) {		// �Ʒ��� ���� ���� @ 0 @ @

										if (LDH_Board[dy - 1][dx] == 0) {				// ������ ������ �ƿ� �����Ƿ� ���ʸ� �˻�
											LDH_Board[dy - 1][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}

									}

									else if (dy > 0 && dy < 15) {						// ���� ���� ���� @ 0 @ @

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

								}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


							} // @ 0 @ @ ���� �˻� ����

						}	// @ 0 @ ���� �˻� ����

					}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

				}		// 1�� ���� ����


			}
		}

		// ---------- ���� �˻� ------------------



		// ---------- �밢�� �˻� ------------------

		for (int i = 0; i < 19; i++) {		// ���� �ϴ� �밢�� ���� ����
			for (int dy = 0, dx = i; dx < 19; dx++, dy++) {				// i = dx�� ������

				
				if (i < 15) {		// i�� 15���� �۾ƾ� ���� �Ʒ� �밢������ ��  5���� �� �� ����

					if (LDH_Board[dy][dx] == 2) {									// �鵹�� �ִٸ�

						if (dx < 18 && LDH_Board[dy + 1][dx + 1] == 2) {						// �鵹 ���� 2�� ����

							if (dx < 17 && LDH_Board[dy + 2][dx + 2] == 2) {						//  �鵹 @ @ @

								if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 2) {		// �鵹 @ @ @ @

									if (dy == 0 && (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3)) {		// ���� ���� �پ� ������ �Ʒ��� ��������  @ @ @ @
										LDH_Board[dy + 4][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;		// ���ÿ� ����
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dx == 15 && (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3)) {		// ������ �Ʒ��� �������� @ @ @ @ �� ������ ���� �پ��ִ� ���
										LDH_Board[dy - 1][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dy > 0 && dx < 15) {												// ���� ���� ���� @ @ @ @
										if (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3) {				// ���� ���� ��
											LDH_Board[dy - 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3) {				// ������ �Ʒ��� ��
											LDH_Board[dy + 4][dx + 4] = 4;

											Warning_ldh[wstack_ldh].x = dx + 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4�� ���� ����

								// ----------- 3�� ���� ---------------- //


								if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 2) {			// @ @ @ 0 @ ����								// dx + 4 �� 18�� �Ѿ�� �޸� �׼��� �źΰ� �Ͼ�°�?  	ex)  LDH_Board[20][20]==2   ????		 dx�� ���� �˻��� �ذ�

									if (dy == 0) {			// ���� ���� ���� @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// ���� ���� ���� ���� @ @ @ 0 @
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

								}		// @ @ @ 0 @ ���� �˻� ����

								else {			 // @ @ @ ����		@ @ @ �� ��ĭ �������� �鵹 �� �ƴ�

									if (dy == 0) {							// ���� ���� ���� @ @ @	

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// ������ �Ʒ��� �������
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dx == 16) {					// ������ ���� ���� @ @ @

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// ���� ���� �������
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dy > 0 && dx < 16) {									// ���� ���� ���� @ @ @

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// ������ �Ʒ��� �������
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// ���� ���� �������
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3�� ���ӵȰ� �˻� ����

							else if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 2) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

								if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 2 && (LDH_Board[dy + 2][dx + 2] == 0 || LDH_Board[dy + 2][dx + 2] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
									LDH_Board[dy + 2][dx + 2] = 4;

									Warning_ldh[wstack_ldh].x = dx + 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dy == 0 && LDH_Board[dy + 2][dx + 2] == 0) {		// ���� ���� ���� @ @ 0 @						 ���� ���� ���̰� ���̰� ����־�� üũ��

									if (LDH_Board[dy + 4][dx + 4] == 0) {			// @ @ 0 @ �� �������� ���������
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dx == 15) && LDH_Board[dy + 2][dx + 2] == 0) {	// ������ ���� ���� @ @ 0 @

									if (LDH_Board[dy - 1][dx - 1] == 0) {				// @ @ 0 @ �� ������ ���������
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dx < 15) {				// ���� ������ ���� @ @ 0 @
																			// @ @ 0 @ ���� ���� ���� ���ٸ� 3���� ����
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

							}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


						}		// 2�� ���� ����

						// ------------------- 1�� �� ���� �˻� ------------

						else if (dx < 18 && LDH_Board[dy + 1][dx + 1] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

							if (dx < 17 && LDH_Board[dy + 2][dx + 2] == 2) {		// @ 0 @ ����

								if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 2) {		// @ 0 @ @ ����

									if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 2) {		// @ 0 @ @ @ ����

										if (LDH_Board[dy + 1][dx + 1] == 0 || LDH_Board[dy + 1][dx + 1] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
											LDH_Board[dy + 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dx+5�� ����ִ��� �˻��� �ʿ� x
										}

									}		//  @ 0 @ @ @ ���� �˻� ����

									else if (dx < 16) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

										if (dy == 0) {				// ���� ���� ���� @ 0 @ @

											if (LDH_Board[dy + 4][dx + 4] == 0) {				// �������� ������ �ƿ� �����Ƿ� �����ʸ� �˻�
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dx == 15) {		// ������ ���� ���� @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {				// ������ ������ �ƿ� �����Ƿ� �����ʸ� �˻�
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy > 0 && dx < 15) {						// ���� ���� ���� @ 0 @ @

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

									}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


								} // @ 0 @ @ ���� �˻� ����

							}	// @ 0 @ ���� �˻� ����

						}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

					}		// 1�� ���� ����

				}		// i < 15 ����

			}
		}


		for (int i = 1; i < 19; i++) {		// ���� �ϴ� �밢�� ���� �Ʒ���
			for (int dx = 0, dy = i; dy < 19; dx++, dy++) {				// i = dy�� ������				 ������ dy�� dx���� ŭ


				if (i < 15) {		// i�� 15���� �۾ƾ� ���� �Ʒ� �밢������ ��  5���� �� �� ����

					if (LDH_Board[dy][dx] == 2) {									// �鵹�� �ִٸ�

						if (dy < 18 && LDH_Board[dy + 1][dx + 1] == 2) {						// �鵹 ���� 2�� ����

							if (dy < 17 && LDH_Board[dy + 2][dx + 2] == 2) {						//  �鵹 @ @ @

								if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 2) {		// �鵹 @ @ @ @

									if (dx == 0 && (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3)) {		// ���� ���� �پ� ������ �Ʒ��� ��������  @ @ @ @
										LDH_Board[dy + 4][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;		// ���ÿ� ����
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dy == 15 && (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3)) {		// ������ �Ʒ��� �������� @ @ @ @ �� �Ʒ��� ���� �پ��ִ� ���
										LDH_Board[dy - 1][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx > 0 && dy < 15) {												// ���� ���� ���� @ @ @ @
										if (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3) {				// ���� ���� ��
											LDH_Board[dy - 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3) {				// ������ �Ʒ��� ��
											LDH_Board[dy + 4][dx + 4] = 4;

											Warning_ldh[wstack_ldh].x = dx + 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4�� ���� ����

								// ----------- 3�� ���� ---------------- //


								if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 2) {			// @ @ @ 0 @ ����								// dx + 4 �� 18�� �Ѿ�� �޸� �׼��� �źΰ� �Ͼ�°�?  	ex)  LDH_Board[20][20]==2   ????		 dx�� ���� �˻��� �ذ�

									if (dx == 0) {			// ���� ���� ���� @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// ���� ���� ���� ���� @ @ @ 0 @
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

								}		// @ @ @ 0 @ ���� �˻� ����

								else {			 // @ @ @ ����		@ @ @ �� ��ĭ �������� �鵹 �� �ƴ�

									if (dx == 0) {							// ���� ���� ���� @ @ @	

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// ������ �Ʒ��� �������
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dy == 16) {					// �Ʒ��� ���� ���� @ @ @

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// ���� ���� �������
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dx > 0 && dy < 16) {									// ���� ���� ���� @ @ @

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// ������ �Ʒ��� �������
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// ���� ���� �������
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3�� ���ӵȰ� �˻� ����

							else if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 2) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

								if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 2 && (LDH_Board[dy + 2][dx + 2] == 0 || LDH_Board[dy + 2][dx + 2] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
									LDH_Board[dy + 2][dx + 2] = 4;

									Warning_ldh[wstack_ldh].x = dx + 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dx == 0 && LDH_Board[dy + 2][dx + 2] == 0) {		// ���� ���� ���� @ @ 0 @						 ���� ���� ���̰� ���̰� ����־�� üũ��

									if (LDH_Board[dy + 4][dx + 4] == 0) {			// @ @ 0 @ �� �������� ���������
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dy == 15) && LDH_Board[dy + 2][dx + 2] == 0) {	// �Ʒ��� ���� ���� @ @ 0 @

									if (LDH_Board[dy - 1][dx - 1] == 0) {				// @ @ 0 @ �� ������ ���������
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dx > 0 && dy < 15) {				// ���� ������ ���� @ @ 0 @
																			// @ @ 0 @ ���� ���� ���� ���ٸ� 3���� ����
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

							}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


						}		// 2�� ���� ����

						// ------------------- 1�� �� ���� �˻� ------------

						else if (dy < 18 && LDH_Board[dy + 1][dx + 1] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

							if (dy < 17 && LDH_Board[dy + 2][dx + 2] == 2) {		// @ 0 @ ����

								if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 2) {		// @ 0 @ @ ����

									if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 2) {		// @ 0 @ @ @ ����

										if (LDH_Board[dy + 1][dx + 1] == 0 || LDH_Board[dy + 1][dx + 1] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
											LDH_Board[dy + 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dx+5�� ����ִ��� �˻��� �ʿ� x
										}

									}		//  @ 0 @ @ @ ���� �˻� ����

									else if (dy < 16) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

										if (dx == 0) {				// ���� ���� ���� @ 0 @ @

											if (LDH_Board[dy + 4][dx + 4] == 0) {				// �������� ������ �ƿ� �����Ƿ� �����ʸ� �˻�		������ i<15 �̹Ƿ� ���� ���� ���� dy=15 �� ��� �˻� ��ü�� ���� ����
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dy == 15) {		// �Ʒ��� ���� ���� @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {				// ������ ������ �ƿ� �����Ƿ� �����ʸ� �˻�
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dx > 0 && dy < 15) {						// ���� ���� ���� @ 0 @ @

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

									}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


								} // @ 0 @ @ ���� �˻� ����

							}	// @ 0 @ ���� �˻� ����

						}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

					}		// 1�� ���� ����

				}		// i < 15 ����

			}
		}


		for (int i = 0; i < 19; i++) {		// ���� �ϴ� �밢�� ���� ����
			for (int dy = 0, dx = i; dx >= 0; dx--, dy++) {				// i = dx�� ������	


				if (i > 3) {		// i�� 3���� Ŀ�� ���� �ϴ����� �� 5���� �� �� ����						dx �� 3���� Ŭ �� �˻�

					if (LDH_Board[dy][dx] == 2) {									// �鵹�� �ִٸ�

						if (dx > 0 && LDH_Board[dy + 1][dx - 1] == 2) {						// �鵹 ���� 2�� ����

							if (dx > 1 && LDH_Board[dy + 2][dx - 2] == 2) {						//  �鵹 @ @ @

								if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 2) {		// �鵹 @ @ @ @

									if (dy == 0 && (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3)) {		// ���� ���� �پ� ���� �Ʒ��� ��������  @ @ @ @
										LDH_Board[dy + 4][dx - 4] = 4;															// ���� �Ʒ��� ��

										Warning_ldh[wstack_ldh].x = dx - 4;		// ���ÿ� ����
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dx == 3 && (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3)) {		// ���� �Ʒ��� �������� @ @ @ @ �� ���� ���� �پ��ִ� ���
										LDH_Board[dy - 1][dx + 1] = 4;																// ������ ���� ��

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx > 3 && dy > 0) {												// ���� ���� ���� @ @ @ @
										if (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3) {				// ������ ���� ��
											LDH_Board[dy - 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3) {				// ���� �Ʒ��� ��
											LDH_Board[dy + 4][dx - 4] = 4;

											Warning_ldh[wstack_ldh].x = dx - 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4�� ���� ����

								// ----------- 3�� ���� ---------------- //


								if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 2) {			// @ @ @ 0 @ ����								// dx + 4 �� 18�� �Ѿ�� �޸� �׼��� �źΰ� �Ͼ�°�?  	ex)  LDH_Board[20][20]==2   ????		 dx�� ���� �˻��� �ذ�

									if (dy == 0) {			// ���� ���� ���� @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// ���� ���� ���� ���� @ @ @ 0 @
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

								}		// @ @ @ 0 @ ���� �˻� ����

								else {			 // @ @ @ ����		@ @ @ �� ��ĭ ������ �鵹 �� �ƴ�

									if (dy == 0) {							// ���� ���� ���� @ @ @	

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// ���� �Ʒ��� �������
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dx == 2) {					// ���� ���� ���� @ @ @

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// ������ ���� �������
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dy > 0 && dx > 2) {									// ���� ���� ���� @ @ @

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// ���� �Ʒ��� �������
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// ������ ���� �������
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3�� ���ӵȰ� �˻� ����

							else if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 2) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

								if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 2 && (LDH_Board[dy + 2][dx - 2] == 0 || LDH_Board[dy + 2][dx - 2] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
									LDH_Board[dy + 2][dx - 2] = 4;

									Warning_ldh[wstack_ldh].x = dx - 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dy == 0 && LDH_Board[dy + 2][dx - 2] == 0) {		// ���� ���� ���� @ @ 0 @						 ������ ���� ���̰� ���̰� ����־�� üũ��

									if (LDH_Board[dy + 4][dx - 4] == 0) {			// @ @ 0 @ �� ���� �Ʒ��� ���������
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dx == 3) && LDH_Board[dy + 2][dx - 2] == 0) {	// ���� ���� ���� @ @ 0 @

									if (LDH_Board[dy - 1][dx + 1] == 0) {				// @ @ 0 @ �� ������ ���� ���������
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dx > 3) {				// ���� ������ ���� @ @ 0 @
																			// @ @ 0 @ ���� ���� ���� ���ٸ� 3���� ����
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

							}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


						}		// 2�� ���� ����

						// ------------------- 1�� �� ���� �˻� ------------

						else if (dx > 0 && LDH_Board[dy + 1][dx - 1] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

							if (dx > 1 && LDH_Board[dy + 2][dx - 2] == 2) {		// @ 0 @ ����

								if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 2) {		// @ 0 @ @ ����

									if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 2) {		// @ 0 @ @ @ ����

										if (LDH_Board[dy + 1][dx - 1] == 0 || LDH_Board[dy + 1][dx - 1] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
											LDH_Board[dy + 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dx+5�� ����ִ��� �˻��� �ʿ� x
										}

									}		//  @ 0 @ @ @ ���� �˻� ����

									else if (dx > 2) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

										if (dy == 0) {				// ���� ���� ���� @ 0 @ @

											if (LDH_Board[dy + 4][dx - 4] == 0) {				// ���� �Ʒ��� ������ �ƿ� �����Ƿ� ���ʸ� �˻�		������ i>3 �̹Ƿ� ���� ���� ���� dx=3 �� ��� �˻� ��ü�� ���� ����
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dx == 3) {		// ���� ���� ���� @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {				// ������ ���� ������ �ƿ� �����Ƿ� �����ʸ� �˻�
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy > 0 && dx > 3) {						// ���� ���� ���� @ 0 @ @

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

									}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


								} // @ 0 @ @ ���� �˻� ����

							}	// @ 0 @ ���� �˻� ����

						}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

					}	// 1�� ���� ����

				}	// i > 3 ����

			}
		}


		for (int i = 1; i < 19; i++) {		// ���� �ϴ� �밢�� ���� �Ʒ���
			for (int dx = 18, dy = i; dy < 19; dx--, dy++) {				// i = dy�� ������	


				if (i < 15) {		// i�� 15���� �۾ƾ� ���� �ϴ����� �� 5���� �� �� ����	

					if (LDH_Board[dy][dx] == 2) {									// �鵹�� �ִٸ�

						if (dy < 18 && LDH_Board[dy + 1][dx - 1] == 2) {						// �鵹 ���� 2�� ����

							if (dy < 17 && LDH_Board[dy + 2][dx - 2] == 2) {						//  �鵹 @ @ @

								if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 2) {		// �鵹 @ @ @ @

									if (dx == 18 && (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3)) {		// ������ ���� �پ� ���� �Ʒ��� ��������  @ @ @ @
										LDH_Board[dy + 4][dx - 4] = 4;															// ���� �Ʒ��� ��

										Warning_ldh[wstack_ldh].x = dx - 4;		// ���ÿ� ����
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dy == 15 && (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3)) {		// ���� �Ʒ��� �������� @ @ @ @ �� �Ʒ��� ���� �پ��ִ� ���
										LDH_Board[dy - 1][dx + 1] = 4;																// ������ ���� ��

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx < 18 && dy < 15) {												// ���� ���� ���� @ @ @ @
										if (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3) {				// ������ ���� ��
											LDH_Board[dy - 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3) {				// ���� �Ʒ��� ��
											LDH_Board[dy + 4][dx - 4] = 4;

											Warning_ldh[wstack_ldh].x = dx - 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4�� ���� ����

								// ----------- 3�� ���� ---------------- //


								if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 2) {			// @ @ @ 0 @ ����	

									if (dx == 18) {			// ������ ���� ���� @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// ������ ���� ���� ���� @ @ @ 0 @
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

								}		// @ @ @ 0 @ ���� �˻� ����

								else {			 // @ @ @ ����		@ @ @ �� ��ĭ ������ �鵹 �� �ƴ�

									if (dx == 18) {							// ������ ���� ���� @ @ @	

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// ���� �Ʒ��� �������
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dy == 16) {					// �Ʒ� ���� ���� @ @ @

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// ������ ���� �������
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dx < 18 && dy < 16) {									// ���� ���� ���� @ @ @

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// ���� �Ʒ��� �������
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// ������ ���� �������
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3�� ���ӵȰ� �˻� ����

							else if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 2) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

								if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 2 && (LDH_Board[dy + 2][dx - 2] == 0 || LDH_Board[dy + 2][dx - 2] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
									LDH_Board[dy + 2][dx - 2] = 4;

									Warning_ldh[wstack_ldh].x = dx - 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dx == 18 && LDH_Board[dy + 2][dx - 2] == 0) {		// ������ ���� ���� @ @ 0 @						 ������ ���� ���̰� ���̰� ����־�� üũ��

									if (LDH_Board[dy + 4][dx - 4] == 0) {			// @ @ 0 @ �� ���� �Ʒ��� ���������
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dy == 15) && LDH_Board[dy + 2][dx - 2] == 0) {	// �Ʒ��� ���� ���� @ @ 0 @

									if (LDH_Board[dy - 1][dx + 1] == 0) {				// @ @ 0 @ �� ������ ���� ���������
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy < 15 && dx < 18) {				// ���� ������ ���� @ @ 0 @
																			// @ @ 0 @ ���� ���� ���� ���ٸ� 3���� ����
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

							}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


						}		// 2�� ���� ����

						// ------------------- 1�� �� ���� �˻� ------------

						else if (dy < 18 && LDH_Board[dy + 1][dx - 1] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

							if (dy < 17 && LDH_Board[dy + 2][dx - 2] == 2) {		// @ 0 @ ����

								if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 2) {		// @ 0 @ @ ����

									if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 2) {		// @ 0 @ @ @ ����

										if (LDH_Board[dy + 1][dx - 1] == 0 || LDH_Board[dy + 1][dx - 1] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
											LDH_Board[dy + 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dx+5�� ����ִ��� �˻��� �ʿ� x
										}

									}		//  @ 0 @ @ @ ���� �˻� ����

									else if (dy < 16) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

										if (dx == 18) {				// ������ ���� ���� @ 0 @ @

											if (LDH_Board[dy + 4][dx - 4] == 0) {				// ���� �Ʒ��� ������ �ƿ� �����Ƿ� ���ʸ� �˻�		������ i<15 �̹Ƿ� ������ ���� ���� dy=15 �� ��� �˻� ��ü�� ���� ����
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dy == 15) {		// �Ʒ��� ���� ���� @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {				// ������ ���� ������ �ƿ� �����Ƿ� �����ʸ� �˻�
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy < 15 && dx < 18) {						// ���� ���� ���� @ 0 @ @

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

									}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


								} // @ 0 @ @ ���� �˻� ����

							}	// @ 0 @ ���� �˻� ����

						}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

					}	// 1�� ���� ����

				}	// i < 15 ����

			}
		}

		// ---------- �밢�� �˻� ------------------


		// �ӽ� ���� ---------------------


		if (wstack_ldh > 0) {		//	�ٷ� �־��� ���� ������
			*x = Warning_ldh[0].x;	
			*y = Warning_ldh[0].y;

			LDH_Board[*y][*x] = 1;

		}
		
		else if (hstack_ldh > 0) {		// ���ƾ� �� ���� ������
			*x = Hint_ldh[0].x;
			*y = Hint_ldh[0].y;

			LDH_Board[*y][*x] = 1;
		}

		else {									// ���ƾ� �� ���� ������


			for (int i = 0; i < 13; i++) {
				for (int j = 0; j < 13; j++) {
					Check_ldh[i][j].count = 0;
				}
			}

			for (int dy = 0; dy < 13; dy += 3) {						// 7*7 ¥�� ������ ������ �� ���� ������ ��
				for (int dx = 0; dx < 13; dx += 3) {

					for (int i = 0; i < 7; i++) {							// 7 * 7 ĭ�� ���� �ڱ� ���� ��
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


			for (int dy = 0; dy < 13; dy++) {							// ������ ���� ���� ���� ������� ã�Ƴ�
				for (int dx = 0; dx < 13; dx++) {

					if (Check_ldh[dy][dx].count > maxstone_ldh) {
						maxstone_ldh = Check_ldh[dy][dx].count;
					}

				}
			}

			for (int dy = 0; dy < 13; dy++) {							// ���� ���� ���� ����������� ã�Ƴ�
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

	hstack_ldh = 0;				// �Ź� �˻���� �Ҷ����� ������ 0���� ����
	wstack_ldh = 0;
	checkx_ldh = 0;
	checky_ldh = 0;
	checkstone_ldh = 0;

	srand((unsigned int)time(NULL));

	if (LDH_Board[9][9] == 0) {			// �� ó���� ��� ��		9,9 �� ����ִ��� �Ǵ��� ������� ������ �ٸ� ���� ��
		*x = 9;
		*y = 9;

		LDH_Board[9][9] = 2;
	}

	else {								// ù���� �ƴ϶��


		// ---------- ���� �˻� ------------------

		for (int dy = 0; dy < 19; dy++) {					// �浹 ���� �˻�
			for (int dx = 0; dx < 19; dx++) {

				if (LDH_Board[dy][dx] == 1) {									// �浹�� �ִٸ�

					if (dx < 18 && LDH_Board[dy][dx + 1] == 1) {						// �浹 ���� 2�� ����

						if (dx < 17 && LDH_Board[dy][dx + 2] == 1) {						//  �鵹 @ @ @

							if (dx < 16 && LDH_Board[dy][dx + 3] == 1) {		// �鵹 @ @ @ @

								if (dx == 0 && (LDH_Board[dy][dx + 4] == 0 || LDH_Board[dy][dx + 4] == 3)) {		// ���� ���� ����  @ @ @ @
									LDH_Board[dy][dx + 4] = 4;

									Warning_ldh[wstack_ldh].x = dx + 4;		// ���ÿ� ����
									Warning_ldh[wstack_ldh].y = dy;
									wstack_ldh++;
								}

								else if (dx == 15 && (LDH_Board[dy][dx - 1] == 0 || LDH_Board[dy][dx - 1] == 3)) {	// ������ ���� ���� @ @ @ @
									LDH_Board[dy][dx - 1] = 4;

									Warning_ldh[wstack_ldh].x = dx - 1;
									Warning_ldh[wstack_ldh].y = dy;
									wstack_ldh++;
								}

								else if (dx > 0 && dx < 15) {												// ���� ���� ���� @ @ @ @
									if (LDH_Board[dy][dx - 1] == 0 || LDH_Board[dy][dx - 1] == 3) {				// ������ ��
										LDH_Board[dy][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}

									if (LDH_Board[dy][dx + 4] == 0 || LDH_Board[dy][dx + 4] == 3) {				// �������� ��
										LDH_Board[dy][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}
								}

							}		// 4�� ���� ����

							// ----------- 3�� ���� ---------------- //

							if (dx < 15 && LDH_Board[dy][dx + 4] == 1) {			// @ @ @ 0 @ ����

								if (dx == 0) {			// ���� ���� ���� @ @ @ 0 @
									if (LDH_Board[dy][dx + 3] == 0 || LDH_Board[dy][dx + 3] == 3) {
										LDH_Board[dy][dx + 3] = 4;

										Warning_ldh[wstack_ldh].x = dx + 3;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;
									}
								}

								else {						// ������ ���� ���� @ @ @ 0 @ or ���� ���� ���� @ @ @ 0 @
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

							}		// @ @ @ 0 @ ���� �˻� ����

							else {			 // @ @ @ ����		@ @ @ �� ��ĭ �������� �鵹 �� �ƴ�

								if (dx == 0) {							// ���� ���� ���� @ @ @	

									if (LDH_Board[dy][dx + 3] == 0) {		// �������� �������
										LDH_Board[dy][dx + 3] = 3;

										Hint_ldh[hstack_ldh].x = dx + 3;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}

								else if (dx == 16) {					// ������ ���� ���� @ @ @

									if (LDH_Board[dy][dx - 1] == 0) {		// ������ �������
										LDH_Board[dy][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}

								else if (dx > 0 && dx < 16) {									// ���� ���� ���� @ @ @

									if (LDH_Board[dy][dx + 3] == 0) {		// �������� �������
										LDH_Board[dy][dx + 3] = 3;

										Hint_ldh[hstack_ldh].x = dx + 3;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}

									if (LDH_Board[dy][dx - 1] == 0) {		// ������ �������
										LDH_Board[dy][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy;
										hstack_ldh++;
									}
								}
							}

						}		// 3�� ���ӵȰ� �˻� ����

						else if (dx < 16 && LDH_Board[dy][dx + 3] == 1) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

							if (dx < 15 && LDH_Board[dy][dx + 4] == 1 && (LDH_Board[dy][dx + 2] == 0 || LDH_Board[dy][dx + 2] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
								LDH_Board[dy][dx + 2] = 4;

								Warning_ldh[wstack_ldh].x = dx + 2;
								Warning_ldh[wstack_ldh].y = dy;
								wstack_ldh++;
							}

							else if (dx == 0 && LDH_Board[dy][dx + 2] == 0) {		// ������ ���� @ @ 0 @								 ������ ���̰� ���̰� ����־�� üũ��

								if (LDH_Board[dy][dx + 4] == 0) {			// @ @ 0 @ �� �������� ���������
									LDH_Board[dy][dx + 4] = 3;

									Hint_ldh[hstack_ldh].x = dx + 4;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}
							}

							else if ((dx == 15) && LDH_Board[dy][dx + 2] == 0) {	// �������� ���� @ @ 0 @

								if (LDH_Board[dy][dx - 1] == 0) {				// @ @ 0 @ �� ������ ���������
									LDH_Board[dy][dx - 1] = 3;

									Hint_ldh[hstack_ldh].x = dx - 1;
									Hint_ldh[hstack_ldh].y = dy;
									hstack_ldh++;
								}
							}

							else if (dx > 0 && dx < 15) {				// ���� ������ ���� @ @ 0 @
																		// @ @ 0 @ ���� ���� ���� ���ٸ� !�� ����
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

						}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


					}		// 2�� ���� ����

					// ------------------- 1�� �� ���� �˻� ------------

					else if (dx < 18 && LDH_Board[dy][dx + 1] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

						if (dx < 17 && LDH_Board[dy][dx + 2] == 1) {		// @ 0 @ ����

							if (dx < 16 && LDH_Board[dy][dx + 3] == 1) {		// @ 0 @ @ ����

								if (dx < 15 && LDH_Board[dy][dx + 4] == 1) {		// @ 0 @ @ @ ����

									if (LDH_Board[dy][dx + 1] == 0 || LDH_Board[dy][dx + 1] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
										LDH_Board[dy][dx + 1] = 4;

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy;
										wstack_ldh++;

										// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dx+5�� ����ִ��� �˻��� �ʿ� x
									}

								}		//  @ 0 @ @ @ ���� �˻� ����

								else if (dx < 16) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

									if (dx == 0) {				// ���� ���� ���� @ 0 @ @

										if (LDH_Board[dy][dx + 4] == 0) {				// �������� ������ �ƿ� �����Ƿ� �����ʸ� �˻�
											LDH_Board[dy][dx + 4] = 3;

											Hint_ldh[hstack_ldh].x = dx + 4;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

									}

									else if (dx == 15) {		// ������ ���� ���� @ 0 @ @

										if (LDH_Board[dy][dx - 1] == 0) {				// ������ ������ �ƿ� �����Ƿ� �����ʸ� �˻�
											LDH_Board[dy][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy;
											hstack_ldh++;
										}

									}

									else if (dx > 0 && dx < 15) {						// ���� ���� ���� @ 0 @ @

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

								}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


							} // @ 0 @ @ ���� �˻� ����

						}	// @ 0 @ ���� �˻� ����

					}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

				}		// 1�� ���� ����


			}
		}

		// ---------- ���� �˻� ------------------



		// ---------- ���� �˻� ------------------

		for (int dx = 0; dx < 19; dx++) {					// �鵹 ���� �˻�
			for (int dy = 0; dy < 19; dy++) {

				if (LDH_Board[dy][dx] == 1) {									// �鵹�� �ִٸ�

					if (dy < 18 && LDH_Board[dy + 1][dx] == 1) {						// �鵹 ���� 2�� ����

						if (dy < 17 && LDH_Board[dy + 2][dx] == 1) {						//  �鵹 @ @ @

							if (dy < 16 && LDH_Board[dy + 3][dx] == 1) {		// �鵹 @ @ @ @

								if (dy == 0 && (LDH_Board[dy + 4][dx] == 0 || LDH_Board[dy + 4][dx] == 3)) {		// ���� ���� ����  @ @ @ @
									LDH_Board[dy + 4][dx] = 4;

									Warning_ldh[wstack_ldh].x = dx;		// ���ÿ� ����
									Warning_ldh[wstack_ldh].y = dy + 4;
									wstack_ldh++;
								}

								else if (dy == 15 && (LDH_Board[dy - 1][dx] == 0 || LDH_Board[dy - 1][dx] == 3)) {	// �Ʒ��� ���� ���� @ @ @ @
									LDH_Board[dy - 1][dx] = 4;

									Warning_ldh[wstack_ldh].x = dx;
									Warning_ldh[wstack_ldh].y = dy - 1;
									wstack_ldh++;
								}

								else if (dy > 0 && dy < 15) {												// ���� ���� ���� @ @ @ @
									if (LDH_Board[dy - 1][dx] == 0 || LDH_Board[dy - 1][dx] == 3) {				// ������ ��
										LDH_Board[dy - 1][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									if (LDH_Board[dy + 4][dx] == 0 || LDH_Board[dy + 4][dx] == 3) {				// �Ʒ����� ��
										LDH_Board[dy + 4][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}
								}

							}		// 4�� ���� ����

							// ----------- 3�� ���� ---------------- //

							if (dy < 15 && LDH_Board[dy + 4][dx] == 1) {			// @ @ @ 0 @ ����

								if (dy == 0) {			// ���� ���� ���� @ @ @ 0 @
									if (LDH_Board[dy + 3][dx] == 0 || LDH_Board[dy + 3][dx] == 3) {
										LDH_Board[dy + 3][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 3;
										wstack_ldh++;
									}
								}

								else {						// �Ʒ��� ���� ���� @ @ @ 0 @ or ���� ���� ���� @ @ @ 0 @
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

							}		// @ @ @ 0 @ ���� �˻� ����

							else {			 // @ @ @ ����

								if (dy == 0) {							// ���� ���� ���� @ @ @	

									if (LDH_Board[dy + 3][dx] == 0) {		// �Ʒ����� �������
										LDH_Board[dy + 3][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy + 3;
										hstack_ldh++;
									}
								}

								else if (dy == 16) {					// �Ʒ��� ���� ���� @ @ @

									if (LDH_Board[dy - 1][dx] == 0) {		// ������ �������
										LDH_Board[dy - 1][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dy < 16) {									// ���� ���� ���� @ @ @

									if (LDH_Board[dy + 3][dx] == 0) {		// �Ʒ����� �������
										LDH_Board[dy + 3][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy + 3;
										hstack_ldh++;
									}

									if (LDH_Board[dy - 1][dx] == 0) {		// ������ �������
										LDH_Board[dy - 1][dx] = 3;

										Hint_ldh[hstack_ldh].x = dx;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}
							}

						}		// 3�� ���ӵȰ� �˻� ����

						else if (dy < 16 && LDH_Board[dy + 3][dx] == 1) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

							if (dy < 15 && LDH_Board[dy + 4][dx] == 1 && (LDH_Board[dy + 2][dx] == 0 || LDH_Board[dy + 2][dx] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
								LDH_Board[dy + 2][dx] = 4;

								Warning_ldh[wstack_ldh].x = dx;
								Warning_ldh[wstack_ldh].y = dy + 2;
								wstack_ldh++;
							}

							else if (dy == 0 && LDH_Board[dy + 2][dx] == 0) {		// ������ ���� @ @ 0 @								 ������ ���̰� ���̰� ����־�� üũ��

								if (LDH_Board[dy + 4][dx] == 0) {			// @ @ 0 @ �� �Ʒ����� ���������			������ ���� ��� �Ʒ��� ������ �����Ƿ� �Ʒ��� �˻���
									LDH_Board[dy + 4][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy + 4;
									hstack_ldh++;
								}
							}

							else if (dy == 15 && LDH_Board[dy + 2][dx] == 0) {		// �Ʒ����� ���� @ @ 0 @

								if (LDH_Board[dy - 1][dx] == 0) {					// @ @ 0 @ �� ������ ���������		�Ʒ����� ���� ��� ���� ������ �����Ƿ� �Ʒ��� �˻���
									LDH_Board[dy - 1][dx] = 3;

									Hint_ldh[hstack_ldh].x = dx;
									Hint_ldh[hstack_ldh].y = dy - 1;
									hstack_ldh++;
								}
							}

							else if (dy > 0 && dy < 15) {				// ���� ������ ���� @ @ 0 @
																		// @ @ 0 @ ���� ���� ���� ���ٸ� !�� ����
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

						}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


					}		// 2�� ���� ����

					// ------------------- 1�� �� ���� �˻� ------------

					else if (dy < 18 && LDH_Board[dy + 1][dx] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

						if (dy < 17 && LDH_Board[dy + 2][dx] == 1) {		// @ 0 @ ����

							if (dy < 16 && LDH_Board[dy + 3][dx] == 1) {		// @ 0 @ @ ����

								if (dy < 15 && LDH_Board[dy + 4][dx] == 1) {		// @ 0 @ @ @ ����

									if (LDH_Board[dy + 1][dx] == 0 || LDH_Board[dy + 1][dx] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
										LDH_Board[dy + 1][dx] = 4;

										Warning_ldh[wstack_ldh].x = dx;
										Warning_ldh[wstack_ldh].y = dy + 1;
										wstack_ldh++;

										// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dy+5�� ����ִ��� �˻��� �ʿ� x
									}

								}		//  @ 0 @ @ @ ���� �˻� ����

								else if (dy < 16) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

									if (dy == 0) {				// ���� ���� ���� @ 0 @ @

										if (LDH_Board[dy + 4][dx] == 0) {				// �Ʒ����� ������ �ƿ� �����Ƿ� �Ʒ��ʸ� �˻�
											LDH_Board[dy + 4][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy + 4;
											hstack_ldh++;
										}

									}

									else if (dy == 15) {		// �Ʒ��� ���� ���� @ 0 @ @

										if (LDH_Board[dy - 1][dx] == 0) {				// ������ ������ �ƿ� �����Ƿ� ���ʸ� �˻�
											LDH_Board[dy - 1][dx] = 3;

											Hint_ldh[hstack_ldh].x = dx;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}

									}

									else if (dy > 0 && dy < 15) {						// ���� ���� ���� @ 0 @ @

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

								}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


							} // @ 0 @ @ ���� �˻� ����

						}	// @ 0 @ ���� �˻� ����

					}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

				}		// 1�� ���� ����


			}
		}

		// ---------- ���� �˻� ------------------



		// ---------- �밢�� �˻� ------------------

		for (int i = 0; i < 19; i++) {		// ���� �ϴ� �밢�� ���� ����
			for (int dy = 0, dx = i; dx < 19; dx++, dy++) {				// i = dx�� ������


				if (i < 15) {		// i�� 15���� �۾ƾ� ���� �Ʒ� �밢������ ��  5���� �� �� ����

					if (LDH_Board[dy][dx] == 1) {									// �鵹�� �ִٸ�

						if (dx < 18 && LDH_Board[dy + 1][dx + 1] == 1) {						// �鵹 ���� 2�� ����

							if (dx < 17 && LDH_Board[dy + 2][dx + 2] == 1) {						//  �鵹 @ @ @

								if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 1) {		// �鵹 @ @ @ @

									if (dy == 0 && (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3)) {		// ���� ���� �پ� ������ �Ʒ��� ��������  @ @ @ @
										LDH_Board[dy + 4][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;		// ���ÿ� ����
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dx == 15 && (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3)) {		// ������ �Ʒ��� �������� @ @ @ @ �� ������ ���� �پ��ִ� ���
										LDH_Board[dy - 1][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dy > 0 && dx < 15) {												// ���� ���� ���� @ @ @ @
										if (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3) {				// ���� ���� ��
											LDH_Board[dy - 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3) {				// ������ �Ʒ��� ��
											LDH_Board[dy + 4][dx + 4] = 4;

											Warning_ldh[wstack_ldh].x = dx + 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4�� ���� ����

								// ----------- 3�� ���� ---------------- //


								if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 1) {			// @ @ @ 0 @ ����								// dx + 4 �� 18�� �Ѿ�� �޸� �׼��� �źΰ� �Ͼ�°�?  	ex)  LDH_Board[20][20]==2   ????		 dx�� ���� �˻��� �ذ�

									if (dy == 0) {			// ���� ���� ���� @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// ���� ���� ���� ���� @ @ @ 0 @
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

								}		// @ @ @ 0 @ ���� �˻� ����

								else {			 // @ @ @ ����		@ @ @ �� ��ĭ �������� �鵹 �� �ƴ�

									if (dy == 0) {							// ���� ���� ���� @ @ @	

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// ������ �Ʒ��� �������
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dx == 16) {					// ������ ���� ���� @ @ @

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// ���� ���� �������
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dy > 0 && dx < 16) {									// ���� ���� ���� @ @ @

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// ������ �Ʒ��� �������
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// ���� ���� �������
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3�� ���ӵȰ� �˻� ����

							else if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 1) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

								if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 1 && (LDH_Board[dy + 2][dx + 2] == 0 || LDH_Board[dy + 2][dx + 2] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
									LDH_Board[dy + 2][dx + 2] = 4;

									Warning_ldh[wstack_ldh].x = dx + 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dy == 0 && LDH_Board[dy + 2][dx + 2] == 0) {		// ���� ���� ���� @ @ 0 @						 ���� ���� ���̰� ���̰� ����־�� üũ��

									if (LDH_Board[dy + 4][dx + 4] == 0) {			// @ @ 0 @ �� �������� ���������
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dx == 15) && LDH_Board[dy + 2][dx + 2] == 0) {	// ������ ���� ���� @ @ 0 @

									if (LDH_Board[dy - 1][dx - 1] == 0) {				// @ @ 0 @ �� ������ ���������
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dx < 15) {				// ���� ������ ���� @ @ 0 @
																			// @ @ 0 @ ���� ���� ���� ���ٸ� 3���� ����
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

							}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


						}		// 2�� ���� ����

						// ------------------- 1�� �� ���� �˻� ------------

						else if (dx < 18 && LDH_Board[dy + 1][dx + 1] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

							if (dx < 17 && LDH_Board[dy + 2][dx + 2] == 1) {		// @ 0 @ ����

								if (dx < 16 && LDH_Board[dy + 3][dx + 3] == 1) {		// @ 0 @ @ ����

									if (dx < 15 && LDH_Board[dy + 4][dx + 4] == 1) {		// @ 0 @ @ @ ����

										if (LDH_Board[dy + 1][dx + 1] == 0 || LDH_Board[dy + 1][dx + 1] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
											LDH_Board[dy + 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dx+5�� ����ִ��� �˻��� �ʿ� x
										}

									}		//  @ 0 @ @ @ ���� �˻� ����

									else if (dx < 16) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

										if (dy == 0) {				// ���� ���� ���� @ 0 @ @

											if (LDH_Board[dy + 4][dx + 4] == 0) {				// �������� ������ �ƿ� �����Ƿ� �����ʸ� �˻�
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dx == 15) {		// ������ ���� ���� @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {				// ������ ������ �ƿ� �����Ƿ� �����ʸ� �˻�
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy > 0 && dx < 15) {						// ���� ���� ���� @ 0 @ @

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

									}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


								} // @ 0 @ @ ���� �˻� ����

							}	// @ 0 @ ���� �˻� ����

						}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

					}		// 1�� ���� ����

				}		// i < 15 ����

			}
		}


		for (int i = 1; i < 19; i++) {		// ���� �ϴ� �밢�� ���� �Ʒ���
			for (int dx = 0, dy = i; dy < 19; dx++, dy++) {				// i = dy�� ������				 ������ dy�� dx���� ŭ


				if (i < 15) {		// i�� 15���� �۾ƾ� ���� �Ʒ� �밢������ ��  5���� �� �� ����

					if (LDH_Board[dy][dx] == 1) {									// �鵹�� �ִٸ�

						if (dy < 18 && LDH_Board[dy + 1][dx + 1] == 1) {						// �鵹 ���� 2�� ����

							if (dy < 17 && LDH_Board[dy + 2][dx + 2] == 1) {						//  �鵹 @ @ @

								if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 1) {		// �鵹 @ @ @ @

									if (dx == 0 && (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3)) {		// ���� ���� �پ� ������ �Ʒ��� ��������  @ @ @ @
										LDH_Board[dy + 4][dx + 4] = 4;

										Warning_ldh[wstack_ldh].x = dx + 4;		// ���ÿ� ����
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dy == 15 && (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3)) {		// ������ �Ʒ��� �������� @ @ @ @ �� �Ʒ��� ���� �پ��ִ� ���
										LDH_Board[dy - 1][dx - 1] = 4;

										Warning_ldh[wstack_ldh].x = dx - 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx > 0 && dy < 15) {												// ���� ���� ���� @ @ @ @
										if (LDH_Board[dy - 1][dx - 1] == 0 || LDH_Board[dy - 1][dx - 1] == 3) {				// ���� ���� ��
											LDH_Board[dy - 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx + 4] == 0 || LDH_Board[dy + 4][dx + 4] == 3) {				// ������ �Ʒ��� ��
											LDH_Board[dy + 4][dx + 4] = 4;

											Warning_ldh[wstack_ldh].x = dx + 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4�� ���� ����

								// ----------- 3�� ���� ---------------- //


								if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 1) {			// @ @ @ 0 @ ����								// dx + 4 �� 18�� �Ѿ�� �޸� �׼��� �źΰ� �Ͼ�°�?  	ex)  LDH_Board[20][20]==2   ????		 dx�� ���� �˻��� �ذ�

									if (dx == 0) {			// ���� ���� ���� @ @ @ 0 @
										if (LDH_Board[dy + 3][dx + 3] == 0 || LDH_Board[dy + 3][dx + 3] == 3) {
											LDH_Board[dy + 3][dx + 3] = 4;

											Warning_ldh[wstack_ldh].x = dx + 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// ���� ���� ���� ���� @ @ @ 0 @
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

								}		// @ @ @ 0 @ ���� �˻� ����

								else {			 // @ @ @ ����		@ @ @ �� ��ĭ �������� �鵹 �� �ƴ�

									if (dx == 0) {							// ���� ���� ���� @ @ @	

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// ������ �Ʒ��� �������
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dy == 16) {					// �Ʒ��� ���� ���� @ @ @

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// ���� ���� �������
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dx > 0 && dy < 16) {									// ���� ���� ���� @ @ @

										if (LDH_Board[dy + 3][dx + 3] == 0) {		// ������ �Ʒ��� �������
											LDH_Board[dy + 3][dx + 3] = 3;

											Hint_ldh[hstack_ldh].x = dx + 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx - 1] == 0) {		// ���� ���� �������
											LDH_Board[dy - 1][dx - 1] = 3;

											Hint_ldh[hstack_ldh].x = dx - 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3�� ���ӵȰ� �˻� ����

							else if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 1) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

								if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 1 && (LDH_Board[dy + 2][dx + 2] == 0 || LDH_Board[dy + 2][dx + 2] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
									LDH_Board[dy + 2][dx + 2] = 4;

									Warning_ldh[wstack_ldh].x = dx + 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dx == 0 && LDH_Board[dy + 2][dx + 2] == 0) {		// ���� ���� ���� @ @ 0 @						 ���� ���� ���̰� ���̰� ����־�� üũ��

									if (LDH_Board[dy + 4][dx + 4] == 0) {			// @ @ 0 @ �� �������� ���������
										LDH_Board[dy + 4][dx + 4] = 3;

										Hint_ldh[hstack_ldh].x = dx + 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dy == 15) && LDH_Board[dy + 2][dx + 2] == 0) {	// �Ʒ��� ���� ���� @ @ 0 @

									if (LDH_Board[dy - 1][dx - 1] == 0) {				// @ @ 0 @ �� ������ ���������
										LDH_Board[dy - 1][dx - 1] = 3;

										Hint_ldh[hstack_ldh].x = dx - 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dx > 0 && dy < 15) {				// ���� ������ ���� @ @ 0 @
																			// @ @ 0 @ ���� ���� ���� ���ٸ� 3���� ����
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

							}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


						}		// 2�� ���� ����

						// ------------------- 1�� �� ���� �˻� ------------

						else if (dy < 18 && LDH_Board[dy + 1][dx + 1] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

							if (dy < 17 && LDH_Board[dy + 2][dx + 2] == 1) {		// @ 0 @ ����

								if (dy < 16 && LDH_Board[dy + 3][dx + 3] == 1) {		// @ 0 @ @ ����

									if (dy < 15 && LDH_Board[dy + 4][dx + 4] == 1) {		// @ 0 @ @ @ ����

										if (LDH_Board[dy + 1][dx + 1] == 0 || LDH_Board[dy + 1][dx + 1] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
											LDH_Board[dy + 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dx+5�� ����ִ��� �˻��� �ʿ� x
										}

									}		//  @ 0 @ @ @ ���� �˻� ����

									else if (dy < 16) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

										if (dx == 0) {				// ���� ���� ���� @ 0 @ @

											if (LDH_Board[dy + 4][dx + 4] == 0) {				// �������� ������ �ƿ� �����Ƿ� �����ʸ� �˻�		������ i<15 �̹Ƿ� ���� ���� ���� dy=15 �� ��� �˻� ��ü�� ���� ����
												LDH_Board[dy + 4][dx + 4] = 3;

												Hint_ldh[hstack_ldh].x = dx + 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dy == 15) {		// �Ʒ��� ���� ���� @ 0 @ @

											if (LDH_Board[dy - 1][dx - 1] == 0) {				// ������ ������ �ƿ� �����Ƿ� �����ʸ� �˻�
												LDH_Board[dy - 1][dx - 1] = 3;

												Hint_ldh[hstack_ldh].x = dx - 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dx > 0 && dy < 15) {						// ���� ���� ���� @ 0 @ @

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

									}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


								} // @ 0 @ @ ���� �˻� ����

							}	// @ 0 @ ���� �˻� ����

						}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

					}		// 1�� ���� ����

				}		// i < 15 ����

			}
		}


		for (int i = 0; i < 19; i++) {		// ���� �ϴ� �밢�� ���� ����
			for (int dy = 0, dx = i; dx >= 0; dx--, dy++) {				// i = dx�� ������	


				if (i > 3) {		// i�� 3���� Ŀ�� ���� �ϴ����� �� 5���� �� �� ����						dx �� 3���� Ŭ �� �˻�

					if (LDH_Board[dy][dx] == 1) {									// �鵹�� �ִٸ�

						if (dx > 0 && LDH_Board[dy + 1][dx - 1] == 1) {						// �鵹 ���� 2�� ����

							if (dx > 1 && LDH_Board[dy + 2][dx - 2] == 1) {						//  �鵹 @ @ @

								if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 1) {		// �鵹 @ @ @ @

									if (dy == 0 && (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3)) {		// ���� ���� �پ� ���� �Ʒ��� ��������  @ @ @ @
										LDH_Board[dy + 4][dx - 4] = 4;															// ���� �Ʒ��� ��

										Warning_ldh[wstack_ldh].x = dx - 4;		// ���ÿ� ����
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dx == 3 && (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3)) {		// ���� �Ʒ��� �������� @ @ @ @ �� ���� ���� �پ��ִ� ���
										LDH_Board[dy - 1][dx + 1] = 4;																// ������ ���� ��

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx > 3 && dy > 0) {												// ���� ���� ���� @ @ @ @
										if (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3) {				// ������ ���� ��
											LDH_Board[dy - 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3) {				// ���� �Ʒ��� ��
											LDH_Board[dy + 4][dx - 4] = 4;

											Warning_ldh[wstack_ldh].x = dx - 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4�� ���� ����

								// ----------- 3�� ���� ---------------- //


								if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 1) {			// @ @ @ 0 @ ����								// dx + 4 �� 18�� �Ѿ�� �޸� �׼��� �źΰ� �Ͼ�°�?  	ex)  LDH_Board[20][20]==2   ????		 dx�� ���� �˻��� �ذ�

									if (dy == 0) {			// ���� ���� ���� @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// ���� ���� ���� ���� @ @ @ 0 @
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

								}		// @ @ @ 0 @ ���� �˻� ����

								else {			 // @ @ @ ����		@ @ @ �� ��ĭ ������ �鵹 �� �ƴ�

									if (dy == 0) {							// ���� ���� ���� @ @ @	

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// ���� �Ʒ��� �������
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dx == 1) {					// ���� ���� ���� @ @ @

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// ������ ���� �������
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dy > 0 && dx > 2) {									// ���� ���� ���� @ @ @

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// ���� �Ʒ��� �������
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// ������ ���� �������
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3�� ���ӵȰ� �˻� ����

							else if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 1) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

								if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 1 && (LDH_Board[dy + 2][dx - 2] == 0 || LDH_Board[dy + 2][dx - 2] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
									LDH_Board[dy + 2][dx - 2] = 4;

									Warning_ldh[wstack_ldh].x = dx - 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dy == 0 && LDH_Board[dy + 2][dx - 2] == 0) {		// ���� ���� ���� @ @ 0 @						 ������ ���� ���̰� ���̰� ����־�� üũ��

									if (LDH_Board[dy + 4][dx - 4] == 0) {			// @ @ 0 @ �� ���� �Ʒ��� ���������
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dx == 3) && LDH_Board[dy + 2][dx - 2] == 0) {	// ���� ���� ���� @ @ 0 @

									if (LDH_Board[dy - 1][dx + 1] == 0) {				// @ @ 0 @ �� ������ ���� ���������
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy > 0 && dx > 3) {				// ���� ������ ���� @ @ 0 @
																			// @ @ 0 @ ���� ���� ���� ���ٸ� 3���� ����
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

							}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


						}		// 2�� ���� ����

						// ------------------- 1�� �� ���� �˻� ------------

						else if (dx > 0 && LDH_Board[dy + 1][dx - 1] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

							if (dx > 1 && LDH_Board[dy + 2][dx - 2] == 1) {		// @ 0 @ ����

								if (dx > 2 && LDH_Board[dy + 3][dx - 3] == 1) {		// @ 0 @ @ ����

									if (dx > 3 && LDH_Board[dy + 4][dx - 4] == 1) {		// @ 0 @ @ @ ����

										if (LDH_Board[dy + 1][dx - 1] == 0 || LDH_Board[dy + 1][dx - 1] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
											LDH_Board[dy + 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dx+5�� ����ִ��� �˻��� �ʿ� x
										}

									}		//  @ 0 @ @ @ ���� �˻� ����

									else if (dx > 2) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

										if (dy == 0) {				// ���� ���� ���� @ 0 @ @

											if (LDH_Board[dy + 4][dx - 4] == 0) {				// ���� �Ʒ��� ������ �ƿ� �����Ƿ� ���ʸ� �˻�		������ i>3 �̹Ƿ� ���� ���� ���� dx=3 �� ��� �˻� ��ü�� ���� ����
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dx == 3) {		// ���� ���� ���� @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {				// ������ ���� ������ �ƿ� �����Ƿ� �����ʸ� �˻�
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy > 0 && dx > 3) {						// ���� ���� ���� @ 0 @ @

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

									}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


								} // @ 0 @ @ ���� �˻� ����

							}	// @ 0 @ ���� �˻� ����

						}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

					}	// 1�� ���� ����

				}	// i > 3 ����

			}
		}


		for (int i = 1; i < 19; i++) {		// ���� �ϴ� �밢�� ���� �Ʒ���
			for (int dx = 18, dy = i; dy < 19; dx--, dy++) {				// i = dy�� ������	


				if (i < 15) {		// i�� 15���� �۾ƾ� ���� �ϴ����� �� 5���� �� �� ����	

					if (LDH_Board[dy][dx] == 1) {									// �鵹�� �ִٸ�

						if (dy < 18 && LDH_Board[dy + 1][dx - 1] == 1) {						// �鵹 ���� 2�� ����

							if (dy < 17 && LDH_Board[dy + 2][dx - 2] == 1) {						//  �鵹 @ @ @

								if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 1) {		// �鵹 @ @ @ @

									if (dx == 18 && (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3)) {		// ������ ���� �پ� ���� �Ʒ��� ��������  @ @ @ @
										LDH_Board[dy + 4][dx - 4] = 4;															// ���� �Ʒ��� ��

										Warning_ldh[wstack_ldh].x = dx - 4;		// ���ÿ� ����
										Warning_ldh[wstack_ldh].y = dy + 4;
										wstack_ldh++;
									}

									else if (dy == 15 && (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3)) {		// ���� �Ʒ��� �������� @ @ @ @ �� �Ʒ��� ���� �پ��ִ� ���
										LDH_Board[dy - 1][dx + 1] = 4;																// ������ ���� ��

										Warning_ldh[wstack_ldh].x = dx + 1;
										Warning_ldh[wstack_ldh].y = dy - 1;
										wstack_ldh++;
									}

									else if (dx < 18 && dy < 15) {												// ���� ���� ���� @ @ @ @
										if (LDH_Board[dy - 1][dx + 1] == 0 || LDH_Board[dy - 1][dx + 1] == 3) {				// ������ ���� ��
											LDH_Board[dy - 1][dx + 1] = 4;

											Warning_ldh[wstack_ldh].x = dx + 1;
											Warning_ldh[wstack_ldh].y = dy - 1;
											wstack_ldh++;
										}

										if (LDH_Board[dy + 4][dx - 4] == 0 || LDH_Board[dy + 4][dx - 4] == 3) {				// ���� �Ʒ��� ��
											LDH_Board[dy + 4][dx - 4] = 4;

											Warning_ldh[wstack_ldh].x = dx - 4;
											Warning_ldh[wstack_ldh].y = dy + 4;
											wstack_ldh++;
										}
									}

								}		// 4�� ���� ����

								// ----------- 3�� ���� ---------------- //


								if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 1) {			// @ @ @ 0 @ ����	

									if (dx == 18) {			// ������ ���� ���� @ @ @ 0 @
										if (LDH_Board[dy + 3][dx - 3] == 0 || LDH_Board[dy + 3][dx - 3] == 3) {
											LDH_Board[dy + 3][dx - 3] = 4;

											Warning_ldh[wstack_ldh].x = dx - 3;
											Warning_ldh[wstack_ldh].y = dy + 3;
											wstack_ldh++;
										}
									}

									else {						// ������ ���� ���� ���� @ @ @ 0 @
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

								}		// @ @ @ 0 @ ���� �˻� ����

								else {			 // @ @ @ ����		@ @ @ �� ��ĭ ������ �鵹 �� �ƴ�

									if (dx == 18) {							// ������ ���� ���� @ @ @	

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// ���� �Ʒ��� �������
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}
									}

									else if (dy == 16) {					// �Ʒ� ���� ���� @ @ @

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// ������ ���� �������
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}

									else if (dx < 18 && dy < 16) {									// ���� ���� ���� @ @ @

										if (LDH_Board[dy + 3][dx - 3] == 0) {		// ���� �Ʒ��� �������
											LDH_Board[dy + 3][dx - 3] = 3;

											Hint_ldh[hstack_ldh].x = dx - 3;
											Hint_ldh[hstack_ldh].y = dy + 3;
											hstack_ldh++;
										}

										if (LDH_Board[dy - 1][dx + 1] == 0) {		// ������ ���� �������
											LDH_Board[dy - 1][dx + 1] = 3;

											Hint_ldh[hstack_ldh].x = dx + 1;
											Hint_ldh[hstack_ldh].y = dy - 1;
											hstack_ldh++;
										}
									}
								}

							}		// 3�� ���ӵȰ� �˻� ����

							else if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 1) {			// 3ĭ �ٷ� ������ �ƴ� @ @ 0 @ ��Ȳ

								if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 1 && (LDH_Board[dy + 2][dx - 2] == 0 || LDH_Board[dy + 2][dx - 2] == 3)) {		// @ @ 0 @ @ ��Ȳ �� ��
									LDH_Board[dy + 2][dx - 2] = 4;

									Warning_ldh[wstack_ldh].x = dx - 2;
									Warning_ldh[wstack_ldh].y = dy + 2;
									wstack_ldh++;
								}

								else if (dx == 18 && LDH_Board[dy + 2][dx - 2] == 0) {		// ������ ���� ���� @ @ 0 @						 ������ ���� ���̰� ���̰� ����־�� üũ��

									if (LDH_Board[dy + 4][dx - 4] == 0) {			// @ @ 0 @ �� ���� �Ʒ��� ���������
										LDH_Board[dy + 4][dx - 4] = 3;

										Hint_ldh[hstack_ldh].x = dx - 4;
										Hint_ldh[hstack_ldh].y = dy + 4;
										hstack_ldh++;
									}
								}

								else if ((dy == 15) && LDH_Board[dy + 2][dx - 2] == 0) {	// �Ʒ��� ���� ���� @ @ 0 @

									if (LDH_Board[dy - 1][dx + 1] == 0) {				// @ @ 0 @ �� ������ ���� ���������
										LDH_Board[dy - 1][dx + 1] = 3;

										Hint_ldh[hstack_ldh].x = dx + 1;
										Hint_ldh[hstack_ldh].y = dy - 1;
										hstack_ldh++;
									}
								}

								else if (dy < 15 && dx < 18) {				// ���� ������ ���� @ @ 0 @
																			// @ @ 0 @ ���� ���� ���� ���ٸ� 3���� ����
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

							}	// @ @ 0 @ ~		 2ĭ���� �� 1ĭ��� ���� �˻� ����


						}		// 2�� ���� ����

						// ------------------- 1�� �� ���� �˻� ------------

						else if (dy < 18 && LDH_Board[dy + 1][dx - 1] == 0) {		// 1�� �ְ� ��ĭ ����ִ� ����  @ 0 ??

							if (dy < 17 && LDH_Board[dy + 2][dx - 2] == 1) {		// @ 0 @ ����

								if (dy < 16 && LDH_Board[dy + 3][dx - 3] == 1) {		// @ 0 @ @ ����

									if (dy < 15 && LDH_Board[dy + 4][dx - 4] == 1) {		// @ 0 @ @ @ ����

										if (LDH_Board[dy + 1][dx - 1] == 0 || LDH_Board[dy + 1][dx - 1] == 3) {		// ���̰� ����ִٸ�			���� �ٳ� �Ⱥٳ� �����Ƿ� �̰͸� �˻���
											LDH_Board[dy + 1][dx - 1] = 4;

											Warning_ldh[wstack_ldh].x = dx - 1;
											Warning_ldh[wstack_ldh].y = dy + 1;
											wstack_ldh++;

											// ���� 3ĭ �˻翡�� ������ �˻��ϹǷ� dx+5�� ����ִ��� �˻��� �ʿ� x
										}

									}		//  @ 0 @ @ @ ���� �˻� ����

									else if (dy < 16) {		// @ 0 @ @  ����  �� �ٷεڿ� @�� �ƴ�

										if (dx == 18) {				// ������ ���� ���� @ 0 @ @

											if (LDH_Board[dy + 4][dx - 4] == 0) {				// ���� �Ʒ��� ������ �ƿ� �����Ƿ� ���ʸ� �˻�		������ i<15 �̹Ƿ� ������ ���� ���� dy=15 �� ��� �˻� ��ü�� ���� ����
												LDH_Board[dy + 4][dx - 4] = 3;

												Hint_ldh[hstack_ldh].x = dx - 4;
												Hint_ldh[hstack_ldh].y = dy + 4;
												hstack_ldh++;
											}

										}

										else if (dy == 15) {		// �Ʒ��� ���� ���� @ 0 @ @

											if (LDH_Board[dy - 1][dx + 1] == 0) {				// ������ ���� ������ �ƿ� �����Ƿ� �����ʸ� �˻�
												LDH_Board[dy - 1][dx + 1] = 3;

												Hint_ldh[hstack_ldh].x = dx + 1;
												Hint_ldh[hstack_ldh].y = dy - 1;
												hstack_ldh++;
											}

										}

										else if (dy < 15 && dx < 18) {						// ���� ���� ���� @ 0 @ @

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

									}		// @ 0 @ @,  �ٷεڿ� @�� �ƴ� ���� �˻� ����


								} // @ 0 @ @ ���� �˻� ����

							}	// @ 0 @ ���� �˻� ����

						}	// 1ĭ �ְ� ����ĭ�� ��ĭ�� ���� �˻� ����

					}	// 1�� ���� ����

				}	// i < 15 ����

			}
		}

		// ---------- �밢�� �˻� ------------------


		// �ӽ� ���� ---------------------


		if (wstack_ldh > 0) {		//	�ٷ� �־��� ���� ������
			*x = Warning_ldh[0].x;
			*y = Warning_ldh[0].y;

			LDH_Board[*y][*x] = 2;
		}

		else if (hstack_ldh > 0) {		// ���ƾ� �� ���� ������
			*x = Hint_ldh[0].x;
			*y = Hint_ldh[0].y;

			LDH_Board[*y][*x] = 2;
		}

		else {									// ���ƾ� �� ���� ������

			for (int i = 0; i < 13; i++) {
				for (int j = 0; j < 13; j++) {
					Check_ldh[i][j].count = 0;
				}
			}

			for (int dy = 0; dy < 13; dy+=3) {						// 7*7 ¥�� ������ ������ �� ���� ������ ��
				for (int dx = 0; dx < 13; dx+=3) {

					for (int i = 0; i < 7; i++) {							// 7 * 7 ĭ�� ���� �ڱ� ���� ��
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


			for (int dy = 0; dy < 13; dy++) {							// ������ ���� ���� ���� ������� ã�Ƴ�
				for (int dx = 0; dx < 13; dx++) {

					if (Check_ldh[dy][dx].count > maxstone_ldh) {
						maxstone_ldh = Check_ldh[dy][dx].count;
					}

				}
			}

			for (int dy = 0; dy < 13; dy++) {							// ���� ���� ���� ����������� ã�Ƴ�
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

				if (checkstone_ldh > 30) {					// ������ ���� ������ �ٸ� �������� �Ѿ
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