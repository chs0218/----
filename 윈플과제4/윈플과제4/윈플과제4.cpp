#include <iostream>
#include <fstream>
#include <random>
#include <windows.h>
#include <time.h>

using namespace std;

struct Point
{
	int x, y;
	Point()
	{
		x = 0; y = 0;
	}

	Point(int a, int b)
	{
		x = a, y = b;
	}

	Point(const Point& other)
	{
		x = other.x;
		y = other.y;
	}

	void show()
	{
		cout << "x: " << x << "y: " << y << endl;
	}

};

struct Shape
{
	Point p1, p2;
	int width, height, area;

	Shape()
	{
		p1.x = 0, p1.y = 0;
		p2.x = 0, p2.y = 0;
		width = 0, height = 0, area = 0;
	}

	Shape(Point P1, Point P2, int Width, int Height, int Area) : p1{ P1 }, p2{ P2 }, width{ Width }, height{ Height }, area{ Area }
	{
	}

	void show()
	{
		cout << width << "(가로) " << height << "(세로) " << area << "(면적)" << endl;
	}
};

int calwidth(Point p1, Point p2)
{
	if (p1.x > p2.x)
		return p1.x - p2.x;
	else
		return p2.x - p1.x;

}

int calheight(Point p1, Point p2)
{
	if (p1.y > p2.y)
		return p1.y - p2.y;

	else
		return p2.y - p1.y;
}

int calarea(int width, int height)
{
	return width * height;
}

int collide(Shape a, Shape b)
{
	if (a.p1.x > a.p2.x)
	{
		if ((a.p2.x <= b.p1.x&&b.p1.x <= a.p1.x) || (a.p2.x <= b.p2.x&&b.p1.x <= a.p1.x))
			return 1;
	}
	else
	{
		if ((a.p1.x <= b.p1.x&&b.p1.x <= a.p2.x) || (a.p1.x <= b.p2.x&&b.p1.x <= a.p2.x))
			return 1;
	}

	if (a.p1.y > a.p2.y)
	{
		if ((a.p2.y <= b.p1.y&&b.p1.y <= a.p1.y) || (a.p2.y <= b.p2.y&&b.p2.y <= a.p1.y))
			return 1;
	}
	else
	{
		if ((a.p1.y <= b.p1.y&&b.p1.y <= a.p2.y) || (a.p1.y <= b.p2.y&&b.p2.y <= a.p2.y))
			return 1;
	}

}

ostream& operator<<(ostream& os, const Shape& shape)
{
	os << shape.p1.x << " " << shape.p1.y << " " << shape.p2.x << " " << shape.p2.y << " " <<
		shape.width << "(가로) " << shape.height << "(세로) " << shape.area << "(면적)" << endl;
	return os;
}


int main()
{

	default_random_engine dre(time(0));
	uniform_int_distribution<> uid(1, 100);

	ofstream out("Number.txt");

	for (int i = 0; i < 80; ++i)
		out << uid(dre) << endl;

	out.close();

	ifstream in("Number.txt");
	
	Point* point = new Point[40];
	for (int i = 0; i < 40; ++i)
	{
		int tmpx, tmpy;
		in >> tmpx >> tmpy;
		point[i] = Point(tmpx, tmpy);
	}

	in.close();

	Shape* shape = new Shape[20];
	Shape* tmp = new Shape[20];
	Shape* tmp1 = new Shape[2];
	default_random_engine dre1(time(0));
	uniform_int_distribution<> uid1(0, 39);

	/*{
		int a = 0, b = 0, c = 0, d = 0;


		while (a == b)

		{
			a = uid1(dre1);
			b = uid1(dre1);
		}

		int width = calwidth(point[a], point[b]);
		int height = calheight(point[a], point[b]);
		shape[0] = Shape(point[a], point[b], width, height, calarea(width, height));

		while (c == d)
		{
			c = uid1(dre1);
			d = uid1(dre1);
		}

		width = calwidth(point[c], point[d]);
		height = calheight(point[c], point[d]);
		shape[1] = Shape(point[c], point[d], width, height, calarea(width, height));

	}*/
	
	for (int i = 0; i < 20; ++i)
	{
		int width, height;
		width = calwidth(point[2 * i], point[2 * i + 1]);
		height = calheight(point[2 * i], point[2 * i + 1]);
		shape[i] = { point[2 * i], point[2 * i + 1], width, height, calarea(width,height) };
	}

	char c = 'a';

	while (c != 'Q' && c != 'q')
	{

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "Input command: ";
		c = _getwch();
		cout << c << endl;
		switch (c)
		{
		case('a'):
			qsort(shape, 20, sizeof(shape[0]), [](const void *m, const void *n)
			{
				Shape* p = (Shape*)m;
				Shape* q = (Shape*)n;
				return p->area - q->area;
			});

			for (int i = 0; i < 20; ++i)
			{
				cout << shape[i] << endl;
			}
			break;

		case('A'):
			qsort(shape, 20, sizeof(shape[0]), [](const void *m, const void *n)
			{
				Shape* p = (Shape*)m;
				Shape* q = (Shape*)n;
				return p->area - q->area;
			});

			for (int i = 0; i < 20; ++i)
			{
				cout << shape[i] << endl;
			}
			break;

		case('d'):
			qsort(shape, 20, sizeof(shape[0]), [](const void *m, const void *n)
			{
				Shape* p = (Shape*)m;
				Shape* q = (Shape*)n;
				return p->width - q->width;
			});


			for (int i = 0; i < 20; ++i)
			{
				cout << shape[i] << endl;
			}
			break;

		case('D'):
			qsort(shape, 20, sizeof(shape[0]), [](const void *m, const void *n)
			{
				Shape* p = (Shape*)m;
				Shape* q = (Shape*)n;
				return p->width - q->width;
			});


			for (int i = 0; i < 20; ++i)
			{
				cout << shape[i] << endl;
			}
			break;

		case('s'):
		{
			ofstream out("Shape.txt");
			for (int i = 0; i < 20; ++i)
				out << shape[i].p1.x << " " << shape[i].p1.y << " " << shape[i].p2.x << " " << shape[i].p2.y << " " <<
				shape[i].width << " " << shape[i].height << " " << shape[i].area << endl;
		}
		out.close();
		cout << "saved in the file\n";
		break;

		case('S'):
		{
			ofstream out("Shape.txt");
			for (int i = 0; i < 20; ++i)
				out << shape[i].p1.x << " " << shape[i].p1.y << " " << shape[i].p2.x << " " << shape[i].p2.y << " " <<
				shape[i].width << " " << shape[i].height << " " << shape[i].area << endl;
		}
		out.close();
		cout << "saved in the file\n";
		break;

		case('r'):
		{

			ifstream in1("Shape.txt");
			/*int p1x, p1y, p2x, p2y, width, height, area;
			int p1x1, p1y1, p2x1, p2y1, width1, height1, area1;

			in1 >> p1x >> p1y >> p2x >> p2y >> width >> height >> area;
			Point tmp1, tmp2, tmp3, tmp4;
			tmp1 = { p1x, p1y };
			tmp2 = { p2x, p2y };

			tmp[0] = { tmp1, tmp2, width, height, area };


			in1 >> p1x1 >> p1y1 >> p2x1 >> p2y1 >> width1 >> height1 >> area1;

			tmp3 = { p1x1, p1y1 };
			tmp4 = { p2x1, p2y1 };

			tmp[1] = { tmp3, tmp4, width1, height1, area1 };

			in1.close();
			for (int i = 0; i < 2; ++i)
				cout << tmp[i] << endl;*/
			int p1x, p1y, p2x, p2y, width, height, area;
			for (int i = 0; i < 20; ++i)
			{
				in1 >> p1x >> p1y >> p2x >> p2y >> width >> height >> area;
				Point tmp1, tmp2;

				tmp1 = { p1x, p1y };
				tmp2 = { p2x, p2y };

				tmp[i] = { tmp1, tmp2, width, height, area };
			}

			default_random_engine dre(time(0));
			uniform_int_distribution<> uid(0, 19);

			int a, b;
			a = uid(dre);
			while (1)
			{
				b = uid(dre);
				if (b != a)
					break;
			}
			tmp1[0] = tmp[a];

			tmp1[1] = tmp[b];
			for (int i = 0; i < 20; ++i)
				cout << tmp[i] << endl;
			cout << "=============================================================collide\n";
			for (int i = 0; i < 2; ++i)
				cout << tmp1[i] << endl;
			if (collide(tmp1[0], tmp1[1]) == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "Two rectangle is collide!\n";
			}
			break;
		}


		case('R'):
		{
			int p1x, p1y, p2x, p2y, width, height, area;
			int p1x1, p1y1, p2x1, p2y1, width1, height1, area1;


			ifstream in1("Shape.txt");
			in1 >> p1x >> p1y >> p2x >> p2y >> width >> height >> area;
			Point tmp1, tmp2, tmp3, tmp4;
			tmp1 = { p1x, p1y };
			tmp2 = { p2x, p2y };

			shape[0] = { tmp1, tmp2, width, height, area };


			in1 >> p1x1 >> p1y1 >> p2x1 >> p2y1 >> width1 >> height1 >> area1;

			tmp3 = { p1x1, p1y1 };
			tmp4 = { p2x1, p2y1 };

			shape[1] = { tmp3, tmp4, width1, height1, area1 };
			in1.close();
			for (int i = 0; i < 2; ++i)
				cout << shape[i] << endl;

			if (collide(shape[0], shape[1]) == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "Two rectangle is collide!\n";
			}
			break;
		}

		}

	}

	cout << "quit the program\n";

	delete[] point;
	delete[] shape;
	delete[] tmp;
}
