#include <iostream>	
#include <iterator>

#define MAX 19
#define WHITE 1
#define BLACK -1

using namespace std;

// 1번
//int main() {
//	for (int i = 0; i < 19; i++) {
//		for (int j = 0; j < 19; j++) {
//			printf("+ ");
//		}
//		printf("\n");
//	}
//}

// 2번

struct Locate
{
	int x = NULL;
	int y = NULL;
};

struct Stone
{
	int count = 0;
	Locate* locate;
	int type;

	Stone() {
		type = 0;
	}

	Stone(int _type) {
		type = _type;
		if (_type == WHITE)
			locate = new Locate[180];
		else if (_type == BLACK)
			locate = new Locate[181];
	}
	~Stone() {
		delete[] locate;
	}
};

struct Board
{
	int is_filled[MAX][MAX];
	Locate* Filled_locate;
	int count = 0;
	int Size_lo = 0;

	Board() {
		Size_lo = 3;
		Filled_locate = new Locate[Size_lo];
	}
	~Board() {
		delete[] Filled_locate;
	}
};



void PrintBoard();
void PrintBoard(const Board& _Board);
bool Check_place(const Stone& _stone, const Locate* is_fill, const int& _count);
void SetBoard(Board& _Board, const Locate& _locate, const bool& _isturnWhite);

int main() {

	PrintBoard();
	Board M_Board;

	Stone Black = { BLACK };
	Stone White = { WHITE };

	Stone& N_stone = Black;

	bool is_turnWhite = false;

	while (true) {
		if (is_turnWhite)
			N_stone = White;
		else
			N_stone = Black;

		scanf_s("%d %d", &N_stone.locate[N_stone.count].x, &N_stone.locate[N_stone.count].y);
		if ((N_stone.locate[N_stone.count].x < 0 || N_stone.locate[N_stone.count].x > 18) || (N_stone.locate[N_stone.count].y < 0 || N_stone.locate[N_stone.count].y > 18)) {
			printf("범위에서 벗어남\n");
		}
		else {
			if (Check_place(N_stone, M_Board.Filled_locate, M_Board.count)) {
				SetBoard(M_Board, N_stone.locate[N_stone.count], is_turnWhite);
				PrintBoard(M_Board);
				cout << "_stone.count : " << N_stone.count << " Black.count : " << Black.count << " White.count : " << White.count << endl;
				N_stone.count++;
				cout << "_stone.count : " << N_stone.count << " Black.count : " << Black.count << " White.count : " << White.count << endl;
				M_Board.count++;
				is_turnWhite = !is_turnWhite;
				cout << "검은돌 : " << Black.count << " " << "흰색돌 : " << White.count << endl;
			}
			else {
				printf("이미 돌이 놓여 있습니다.\n");
			}
		}
	}
}

bool Check_place(const Stone& _stone, const Locate* is_fill, const int& _count) {
	cout << "_stone.count : " << _stone.count << endl;
	for (int i = 0; i < _count; i++) {
		if ((_stone.locate[_stone.count].x == is_fill[i].x) && (_stone.locate[_stone.count].y == is_fill[i].y))
			return false;
	}
	return true;
}

void PrintBoard() {
	system("cls");
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			printf("+ ");
		}
		printf("\n");
	}
}

void PrintBoard(const Board& _Board) {
	system("cls");
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {

			switch (_Board.is_filled[i][j])
			{
			case 1:
				printf("●");
				break;
			case -1:
				printf("○");
				break;
			default:
				printf("+ ");
				break;
			}
		}
		printf("\n");
	}
}

void SetBoard(Board& _Board, const Locate& _locate, const bool& _isturnWhite) {
	_Board.is_filled[_locate.x][_locate.y] = (_isturnWhite) ? 1 : -1;
	if (_Board.Size_lo > _Board.count)
		_Board.Filled_locate[_Board.count] = _locate;
	else {
		Locate* temp = _Board.Filled_locate;
		_Board.Size_lo = _Board.Size_lo * 3;
		_Board.Filled_locate = new Locate[_Board.Size_lo];
		for (int i = 0; i < _Board.count; i++)
			_Board.Filled_locate[i] = temp[i];
		_Board.Filled_locate[_Board.count] = _locate;
	}
}