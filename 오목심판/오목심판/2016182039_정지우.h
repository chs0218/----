#pragma once
struct Point {
	int x;
	int y;
};

//보드 : 1-흑 2-백 0-빈칸
int board_2016182039[19][19]{};

//턴시작
bool black_start = false;
bool white_start = false;

//뒀던 자리를 기억하는 구조체
Point stack[19 * 19];
int stack_num = 0;
Point Wstack[19 * 19];
int Wstack_num = 0;

//바둑판에 두고 여기변수를 조정하는 함수
void set(int x, int y, int type) {
	board_2016182039[x][y] = type;
	if (type == 1)
		stack[stack_num++] = { x,y };
	else
		Wstack[Wstack_num++] = { x,y };
}


//후보 좌표가 유효한지 검사하는 함수
bool vaildPos(int x_pos, int y_pos) {
	if (x_pos >= 0 && x_pos <= 18 && y_pos >= 0 && y_pos <= 18 && board_2016182039[x_pos][y_pos] == 0)
		return true;

	return false;
}


//바둑판을 넘어서 두려고 하는지 검사
bool crossedge(int x_pos, int y_pos) {
	if (x_pos < 0 || x_pos > 18 || y_pos < 0 || y_pos > 18)
		return true;

	return false;
}




//후보 좌표 ...
Point target;
bool targeted = false;


//일반 검사 함수
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



// 중간 빈칸 추출 하는 함수를 만들자
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

	//첫 턴이면 중앙에 놓자..
	if (!black_start) {
		*x = 7;
		*y = 3;
		set(7, 3, 1);
		black_start = true;
		return;
	}

	//첫 턴이 아니라면...
	
	

	//4목으로 끝낼수 있는 수 검사
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

	//5목이 되는데 중간에 빈칸이 있는 곳
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

	//방어 검사
	//5목이 되는데 중간에 빈칸이 있는 곳
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

	//4연속놓여진 돌 검사
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

	//다음 3연속 검사

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


	//내가 뒀던 돌들의 좌표를 순회하며 그 곳으로 부터 한칸 떨어진.. 놓을 곳을 찾자
	int x_pos, y_pos;
	for (int i = 0; i < stack_num; ++i) {
		//뒀던 돌의 8방향으로 검사한다
		//x좌표 1개당 y좌표 3개씩 3번 반복...
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

		//x값을 증가시켜 위 아래 검사
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

		//x값 증가, 오른쪽 검사
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

	//그래도 못 찾으면 죽긴 하는데 그럴 일은 없을 것 같다.
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

	//첫 턴이 아니라면...

	//4목으로 끝낼수 있는 수 검사
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

	//5목이 되는데 중간에 빈칸이 있는 곳
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

	//방어 검사

	//5목이 되는데 중간에 빈칸이 있는 곳
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

	//4연속 놓여진 돌 검사

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

	//3연속놓여진 돌 검사

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


	//내가 뒀던 돌들의 좌표를 순회하며 그 곳으로 부터 한칸 떨어진.. 놓을 곳을 찾자
	int x_pos, y_pos;
	for (int i = 0; i < Wstack_num; ++i) {
		//뒀던 돌의 8방향으로 검사한다
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

		//x값을 증가시켜 위 아래 검사
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

		//x값 증가, 오른쪽 검사
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