#pragma once
struct Point {
	int x;
	int y;
};

//���� : 1-�� 2-�� 0-��ĭ
int board_2016182039[19][19]{};

//�Ͻ���
bool black_start = false;
bool white_start = false;

//�״� �ڸ��� ����ϴ� ����ü
Point stack[19 * 19];
int stack_num = 0;
Point Wstack[19 * 19];
int Wstack_num = 0;

//�ٵ��ǿ� �ΰ� ���⺯���� �����ϴ� �Լ�
void set(int x, int y, int type) {
	board_2016182039[x][y] = type;
	if (type == 1)
		stack[stack_num++] = { x,y };
	else
		Wstack[Wstack_num++] = { x,y };
}


//�ĺ� ��ǥ�� ��ȿ���� �˻��ϴ� �Լ�
bool vaildPos(int x_pos, int y_pos) {
	if (x_pos >= 0 && x_pos <= 18 && y_pos >= 0 && y_pos <= 18 && board_2016182039[x_pos][y_pos] == 0)
		return true;

	return false;
}


//�ٵ����� �Ѿ �η��� �ϴ��� �˻�
bool crossedge(int x_pos, int y_pos) {
	if (x_pos < 0 || x_pos > 18 || y_pos < 0 || y_pos > 18)
		return true;

	return false;
}




//�ĺ� ��ǥ ...
Point target;
bool targeted = false;


//�Ϲ� �˻� �Լ�
void horizon3check(int x, int y, int enemy_type, int search_cnt) {
	if (targeted)
		return;

	Point pnt[30];
	int pnt_cnt = 0;
	int type_cnt[3]{ 0 };

	for (int i = 0; i < search_cnt; ++i) {
		if (crossedge(x, y))
			return;

		pnt[pnt_cnt].x = x;
		pnt[pnt_cnt].y = y;
		pnt_cnt++;
		type_cnt[board_2016182039[x][y]]++;
		x++;
	}


	if (type_cnt[enemy_type] == search_cnt) {
		if (vaildPos(pnt[0].x - 1, pnt[0].y)) {
			target = { pnt[0].x - 1 , pnt[0].y };
			targeted = true;
		}

		else if (vaildPos(pnt[search_cnt-1].x + 1, pnt[search_cnt-1].y)) {
			target = { pnt[search_cnt - 1].x + 1 , pnt[search_cnt - 1].y };
			targeted = true;
		}

		
	}
	
}

void vertical3check(int x, int y, int enemy_type, int search_cnt) {
	if (targeted)
		return;

	Point pnt[30];
	int pnt_cnt = 0;
	int type_cnt[3]{ 0 };


	for (int i = 0; i < search_cnt; ++i) {
		if (crossedge(x, y))
			return;

		pnt[pnt_cnt].x = x;
		pnt[pnt_cnt].y = y;
		pnt_cnt++;
		type_cnt[board_2016182039[x][y]]++;
		y++;
	}


	if (type_cnt[enemy_type] == search_cnt) {
		if (vaildPos(pnt[0].x, pnt[0].y - 1)) {
			target = { pnt[0].x , pnt[0].y - 1 };
			targeted = true;
		}

		else if (vaildPos(pnt[search_cnt-1].x, pnt[search_cnt-1].y + 1)) {
			target = { pnt[search_cnt - 1].x , pnt[search_cnt - 1].y + 1 };
			targeted = true;
		}


	}

}

void diag1_3check(int x, int y, int enemy_type, int search_cnt) {
	if (targeted)
		return;

	Point pnt[30];
	int pnt_cnt = 0;
	int type_cnt[3]{ 0 };


	if (crossedge(x, y))
		return;
	x++;
	y++;
	diag1_3check(x, y, enemy_type, search_cnt);
	x--;
	y--;

	for (int i = 0; i < search_cnt; ++i) {
		if (crossedge(x, y))
			return;

		pnt[pnt_cnt].x = x;
		pnt[pnt_cnt].y = y;
		pnt_cnt++;
		type_cnt[board_2016182039[x][y]]++;
		x++;
		y++;
	}

	if (type_cnt[enemy_type] == search_cnt) {
		if (search_cnt == 4) {
  			int x = 0;
		}
		if (vaildPos(pnt[0].x - 1, pnt[0].y - 1)) {
			target = { pnt[0].x - 1 , pnt[0].y - 1 };
			targeted = true;
		}

		else if (vaildPos(pnt[search_cnt-1].x+1, pnt[search_cnt-1].y+1)) {
			target = { pnt[search_cnt-1].x+1, pnt[search_cnt-1].y+1};
			targeted = true;
		}
	}

}

void diag2_3check(int x, int y, int enemy_type, int search_cnt) {
	if (targeted)
		return;

	Point pnt[30];
	int pnt_cnt = 0;
	int type_cnt[3]{ 0 };


	if (crossedge(x, y))
		return;
	x--;
	y++;
	diag2_3check(x, y, enemy_type, search_cnt);
	x++;
	y--;

	for (int i = 0; i < search_cnt; ++i) {
		if (crossedge(x, y))
			return;

		pnt[pnt_cnt].x = x;
		pnt[pnt_cnt].y = y;
		pnt_cnt++;
		type_cnt[board_2016182039[x][y]]++;
		x--;
		y++;
	}


	if (type_cnt[enemy_type] == search_cnt) {
		if (vaildPos(pnt[0].x + 1, pnt[0].y - 1)) {
			target = { pnt[0].x + 1 , pnt[0].y - 1 };
			targeted = true;
		}

		else if (vaildPos(pnt[search_cnt - 1].x - 1, pnt[search_cnt - 1].y + 1)) {
			target = { pnt[search_cnt - 1].x - 1, pnt[search_cnt - 1].y + 1 };
			targeted = true;
		}
	}

}



// �߰� ��ĭ ���� �ϴ� �Լ��� ������
void horizon_hole_check(int x, int y, int enemy_type, int search_cnt) {
	if (targeted)
		return;

	Point pnt[30];
	int pnt_cnt = 0;
	int type_cnt[3]{ 0 };

	for (int i = 0; i < search_cnt; ++i) {
		if (crossedge(x, y))
			return;

		pnt[pnt_cnt].x = x;
		pnt[pnt_cnt].y = y;
		pnt_cnt++;
		type_cnt[board_2016182039[x][y]]++;
		x++;
	}


	if (type_cnt[enemy_type] == search_cnt - 1 && type_cnt[0] == 1) {
		int px, py;
		for (int i = 0; i < pnt_cnt; ++i) {
			if (board_2016182039[pnt[i].x][pnt[i].y] == 0) {
				px = pnt[i].x;
				py = pnt[i].y;
			}
		}

		if (vaildPos(px, py)) {
			target = { px , py };
			targeted = true;
		}
	}

}

void vertical_hole_check(int x, int y, int enemy_type, int search_cnt) {
	if (targeted)
		return;

	Point pnt[30];
	int pnt_cnt = 0;
	int type_cnt[3]{ 0 };


	for (int i = 0; i < search_cnt; ++i) {
		if (crossedge(x, y))
			return;

		pnt[pnt_cnt].x = x;
		pnt[pnt_cnt].y = y;
		pnt_cnt++;
		type_cnt[board_2016182039[x][y]]++;
		y++;
	}


	if (type_cnt[enemy_type] == search_cnt - 1 && type_cnt[0] == 1) {
		int px, py;
		for (int i = 0; i < pnt_cnt; ++i) {
			if (board_2016182039[pnt[i].x][pnt[i].y] == 0) {
				px = pnt[i].x;
				py = pnt[i].y;
			}
		}

		if (vaildPos(px, py)) {
			target = { px , py };
			targeted = true;
		}
	}

}

void diag1_hole_check(int x, int y, int enemy_type, int search_cnt) {
	if (targeted)
		return;

	Point pnt[30];
	int pnt_cnt = 0;
	int type_cnt[3]{ 0 };


	if (crossedge(x, y))
		return;
	x++;
	y++;
	diag1_3check(x, y, enemy_type, search_cnt);
	x--;
	y--;

	for (int i = 0; i < search_cnt; ++i) {
		if (crossedge(x, y))
			return;

		pnt[pnt_cnt].x = x;
		pnt[pnt_cnt].y = y;
		pnt_cnt++;
		type_cnt[board_2016182039[x][y]]++;
		x++;
		y++;
	}

	if (type_cnt[enemy_type] == search_cnt - 1 && type_cnt[0] == 1) {
		int px, py;
		for (int i = 0; i < pnt_cnt; ++i) {
			if (board_2016182039[pnt[i].x][pnt[i].y] == 0) {
				px = pnt[i].x;
				py = pnt[i].y;
			}
		}

		if (vaildPos(px, py)) {
			target = { px , py };
			targeted = true;
		}
	}

}

void diag2_hole_check(int x, int y, int enemy_type, int search_cnt) {
	if (targeted)
		return;

	Point pnt[30];
	int pnt_cnt = 0;
	int type_cnt[3]{ 0 };


	if (crossedge(x, y))
		return;
	x--;
	y++;
	diag2_3check(x, y, enemy_type, search_cnt);
	x++;
	y--;

	for (int i = 0; i < search_cnt; ++i) {
		if (crossedge(x, y))
			return;

		pnt[pnt_cnt].x = x;
		pnt[pnt_cnt].y = y;
		pnt_cnt++;
		type_cnt[board_2016182039[x][y]]++;
		x--;
		y++;
	}


	if (type_cnt[enemy_type] == search_cnt - 1 && type_cnt[0] == 1) {
		int px, py;
		for (int i = 0; i < pnt_cnt; ++i) {
			if (board_2016182039[pnt[i].x][pnt[i].y] == 0) {
				px = pnt[i].x;
				py = pnt[i].y;
			}
		}

		if (vaildPos(px, py)) {
			target = { px , py };
			targeted = true;
		}
	}

}










void BlackAttack_2016182039(int* x, int* y) {

	//ù ���̸� �߾ӿ� ����..
	if (!black_start) {
		*x = 7;
		*y = 3;
		set(7, 3, 1);
		black_start = true;
		return;
	}

	//ù ���� �ƴ϶��...
	
	

	//4������ ������ �ִ� �� �˻�
	for (int y = 0; y <= 18; ++y) {
		for (int x = 0; x <= 18; ++x) {
			horizon3check(x, y, 1, 4);
			vertical3check(x, y, 1, 4);
		}
	}

	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(0, 19 - 1 - i, 1, 4);
	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(i, 0, 1, 4);

	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1, 19 - 1 - i, 1, 4);
	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1 - i, 0, 1, 4);

	if (targeted) {
		*x = target.x;
		*y = target.y;
		set(target.x, target.y, 1);
		targeted = false;
		return;
	}

	//5���� �Ǵµ� �߰��� ��ĭ�� �ִ� ��
	for (int y = 0; y <= 18; ++y) {
		for (int x = 0; x <= 18; ++x) {
			horizon_hole_check(x, y, 1, 5);
			vertical_hole_check(x, y, 1, 5);
		}
	}

	for (int i = 0; i <= 19 - 1; ++i)
		diag1_hole_check(0, 19 - 1 - i, 1, 5);
	for (int i = 0; i <= 19 - 1; ++i)
		diag1_hole_check(i, 0, 1, 5);

	for (int i = 0; i <= 19; ++i)
		diag2_hole_check(19 - 1, 19 - 1 - i, 1, 5);
	for (int i = 0; i <= 19; ++i)
		diag2_hole_check(19 - 1 - i, 0, 1, 5);

	if (targeted) {
		*x = target.x;
		*y = target.y;
		set(target.x, target.y, 1);
		targeted = false;
		return;
	}

	//��� �˻�
	//5���� �Ǵµ� �߰��� ��ĭ�� �ִ� ��
	for (int y = 0; y <= 18; ++y) {
		for (int x = 0; x <= 18; ++x) {
			horizon_hole_check(x, y, 2, 5);
			vertical_hole_check(x, y, 2, 5);
		}
	}

	for (int i = 0; i <= 19 - 1; ++i)
		diag1_hole_check(0, 19 - 1 - i, 2, 5);
	for (int i = 0; i <= 19 - 1; ++i)
		diag1_hole_check(i, 0, 2, 5);

	for (int i = 0; i <= 19; ++i)
		diag2_hole_check(19 - 1, 19 - 1 - i, 2, 5);
	for (int i = 0; i <= 19; ++i)
		diag2_hole_check(19 - 1 - i, 0, 2, 5);

	if (targeted) {
		*x = target.x;
		*y = target.y;
		set(target.x, target.y, 1);
		targeted = false;
		return;
	}

	//4���ӳ����� �� �˻�
	for (int y = 0; y <= 18; ++y) {
		for (int x = 0; x <= 18; ++x) {
			horizon3check(x, y, 2, 4);
			vertical3check(x, y, 2, 4);
		}
	}

	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(0, 19 - 1 - i, 2, 4);
	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(i, 0, 2, 4);

	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1, 19 - 1 - i, 2, 4);
	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1 - i, 0, 2, 4);

	if (targeted) {
		*x = target.x;
		*y = target.y;
		set(target.x, target.y, 1);
		targeted = false;
		return;
	}

	//���� 3���� �˻�

	for (int y = 0; y <= 18; ++y) {
		for (int x = 0; x <= 18; ++x) {
			horizon3check(x, y, 2, 3);
			vertical3check(x, y, 2, 3);
		}
	}

	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(0, 19 - 1 - i, 2, 3);
	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(i, 0, 2, 3);

	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1, 19 - 1 - i, 2, 3);
	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1 - i, 0, 2, 3);

	if (targeted) {
		*x = target.x;
		*y = target.y;
		set(target.x, target.y, 1);
		targeted = false;
		return;
	}


	//���� �״� ������ ��ǥ�� ��ȸ�ϸ� �� ������ ���� ��ĭ ������.. ���� ���� ã��
	int x_pos, y_pos;
	for (int i = 0; i < stack_num; ++i) {
		//�״� ���� 8�������� �˻��Ѵ�
		//x��ǥ 1���� y��ǥ 3���� 3�� �ݺ�...
		x_pos = stack[i].x - 1;
		y_pos = stack[i].y - 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 1);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = stack[i].y;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 1);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = stack[i].y + 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 1);
			*x = x_pos;
			*y = y_pos;
			return;
		}

		//x���� �������� �� �Ʒ� �˻�
		x_pos = stack[i].x;
		y_pos = stack[i].y - 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 1);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = stack[i].y;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 1);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = stack[i].y + 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 1);
			*x = x_pos;
			*y = y_pos;
			return;
		}

		//x�� ����, ������ �˻�
		x_pos = stack[i].x + 1;
		y_pos = stack[i].y - 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 1);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = stack[i].y;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 1);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = stack[i].y + 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 1);
			*x = x_pos;
			*y = y_pos;
			return;
		}

	}

	//�׷��� �� ã���� �ױ� �ϴµ� �׷� ���� ���� �� ����.
}


void BlackDefense_2016182039(int x, int y) {
	board_2016182039[x][y] = 2;


}


void WhiteAttack_2016182039(int* x, int* y) {
	if (!white_start) {
		if (board_2016182039[12][14] == 0) {
			*x = 12;
			*y = 14;
			set(12, 14, 2);
		}
		else {
			*x = 11;
			*y = 14;
			set(11, 14, 2);
		}

		white_start = true;
		return;
	}

	//ù ���� �ƴ϶��...

	//4������ ������ �ִ� �� �˻�
	for (int y = 0; y <= 18; ++y) {
		for (int x = 0; x <= 18; ++x) {
			horizon3check(x, y, 2, 4);
			vertical3check(x, y, 2, 4);
		}
	}

	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(0, 19 - 1 - i, 2, 4);
	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(i, 0, 2, 4);

	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1, 19 - 1 - i, 2, 4);
	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1 - i, 0, 2, 4);

	if (targeted) {
		*x = target.x;
		*y = target.y;
		set(target.x, target.y, 2);
		targeted = false;
		return;
	}

	//5���� �Ǵµ� �߰��� ��ĭ�� �ִ� ��
	for (int y = 0; y <= 18; ++y) {
		for (int x = 0; x <= 18; ++x) {
			horizon_hole_check(x, y, 2, 5);
			vertical_hole_check(x, y, 2, 5);
		}
	}

	for (int i = 0; i <= 19 - 1; ++i)
		diag1_hole_check(0, 19 - 1 - i, 2, 5);
	for (int i = 0; i <= 19 - 1; ++i)
		diag1_hole_check(i, 0, 2, 5);

	for (int i = 0; i <= 19; ++i)
		diag2_hole_check(19 - 1, 19 - 1 - i, 2, 5);
	for (int i = 0; i <= 19; ++i)
		diag2_hole_check(19 - 1 - i, 0, 2, 5);

	if (targeted) {
		*x = target.x;
		*y = target.y;
		set(target.x, target.y, 2);
		targeted = false;
		return;
	}

	//��� �˻�

	//5���� �Ǵµ� �߰��� ��ĭ�� �ִ� ��
	for (int y = 0; y <= 18; ++y) {
		for (int x = 0; x <= 18; ++x) {
			horizon_hole_check(x, y, 1, 5);
			vertical_hole_check(x, y, 1, 5);
		}
	}

	for (int i = 0; i <= 19 - 1; ++i)
		diag1_hole_check(0, 19 - 1 - i, 1, 5);
	for (int i = 0; i <= 19 - 1; ++i)
		diag1_hole_check(i, 0, 1, 5);

	for (int i = 0; i <= 19; ++i)
		diag2_hole_check(19 - 1, 19 - 1 - i, 1, 5);
	for (int i = 0; i <= 19; ++i)
		diag2_hole_check(19 - 1 - i, 0, 1, 5);

	if (targeted) {
		*x = target.x;
		*y = target.y;
		set(target.x, target.y, 2);
		targeted = false;
		return;
	}

	//4���� ������ �� �˻�

	for (int y = 0; y <= 18; ++y) {
		for (int x = 0; x <= 18; ++x) {
			horizon3check(x, y, 1, 4);
			vertical3check(x, y, 1, 4);
		}
	}

	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(0, 19 - 1 - i, 1, 4);
	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(i, 0, 1, 4);

	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1, 19 - 1 - i, 1, 4);
	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1 - i, 0, 1, 4);

	if (targeted) {
		*x = target.x;
		*y = target.y;
		set(target.x, target.y, 2);
		targeted = false;
		return;
	}

	//3���ӳ����� �� �˻�

	for (int y = 0; y <= 18; ++y) {
		for (int x = 0; x <= 18; ++x) {
			horizon3check(x, y, 1, 3);
			vertical3check(x, y, 1,3);
		}
	}

	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(0, 19 - 1 - i, 1,3);
	for (int i = 0; i <= 19 - 1; ++i)
		diag1_3check(i, 0, 1,3);

	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1, 19 - 1 - i, 1,3);
	for (int i = 0; i <= 19; ++i)
		diag2_3check(19 - 1 - i, 0, 1,3);




	if (targeted) {
		*x = target.x;
		*y = target.y;
		set(target.x, target.y, 2);
		targeted = false;
		return;
	}


	//���� �״� ������ ��ǥ�� ��ȸ�ϸ� �� ������ ���� ��ĭ ������.. ���� ���� ã��
	int x_pos, y_pos;
	for (int i = 0; i < Wstack_num; ++i) {
		//�״� ���� 8�������� �˻��Ѵ�
		x_pos = Wstack[i].x - 1;
		y_pos = Wstack[i].y - 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 2);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = Wstack[i].y;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 2);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = Wstack[i].y + 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 2);
			*x = x_pos;
			*y = y_pos;
			return;
		}

		//x���� �������� �� �Ʒ� �˻�
		x_pos = Wstack[i].x;
		y_pos = Wstack[i].y - 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 2);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = Wstack[i].y;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 2);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = Wstack[i].y + 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 2);
			*x = x_pos;
			*y = y_pos;
			return;
		}

		//x�� ����, ������ �˻�
		x_pos = Wstack[i].x + 1;
		y_pos = Wstack[i].y - 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 2);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = Wstack[i].y;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 2);
			*x = x_pos;
			*y = y_pos;
			return;
		}
		y_pos = Wstack[i].y + 1;
		if (vaildPos(x_pos, y_pos)) {
			set(x_pos, y_pos, 2);
			*x = x_pos;
			*y = y_pos;
			return;
		}

	}
}


void WhiteDefense_2016182039(int x, int y) {
	board_2016182039[x][y] = 1;
}