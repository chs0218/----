#include <iostream>
#include <Windows.h>

bool First = false;

int LastBlackX_2018180044 = 0, LastBlackY_2018180044 = 0;
int LastWhiteX_2018180044 = 0, LastWhiteY_2018180044 = 0;


int Board_2018180044[19][19] = { 0 };

void movetoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int WhitePoint(int x, int y)
{
	int p = 0;

	if (Board_2018180044[x][y] != 0)
		return -1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (Board_2018180044[x - 1 + i][y - 1 + j] == 2)
			{
				p += 1;
			}
		}
	}
	return p;
}

int BlackPoint(int x, int y)
{
	int p = 0;

	if (Board_2018180044[x][y] != 0)
		return -1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (Board_2018180044[x - 1 + i][y - 1 + j] == 1)
			{
				p += 1;
			}
		}
	}
	return p;
}

void CountStone(int* x, int* y, int* cs, int* Black, int* White, int* MaxBlack, int* MaxWhite, int BlackLocation[2], int WhiteLocation[2], int restart[2], BOOL A, BOOL Diag)
{
	switch (*cs)
	{
	case 0:
		switch (Board_2018180044[*x][*y])
		{
		case 0:
		case 4:

			break;
		case 1:
			*Black = 1;
			*cs = 1;
			break;

		case 2:
			*White = 1;
			*cs = 2;
			break;
		}
		break;
	case 1:
		switch (Board_2018180044[*x][*y])
		{
		case 0:
		case 4:
			++*Black;
			restart[0] = *x;
			restart[1] = *y;
			*cs = 3;
			break;
		case 1:
			++*Black;
			break;

		case 2:
			*White = 1;
			if (*Black > *MaxBlack)
			{
				BlackLocation[0] = *x;
				BlackLocation[1] = *y;
				*MaxBlack = *Black;
			}
			*Black = 0;
			*cs = 2;
			break;
		}
		break;
	case 2:
		switch (Board_2018180044[*x][*y])
		{
		case 0:
		case 4:
			++*White;
			restart[0] = *x;
			restart[1] = *y;
			*cs = 4;
			break;
		case 1:
			*Black = 1;
			if (*White > *MaxWhite)
			{
				WhiteLocation[0] = *x;
				WhiteLocation[1] = *y;
				*MaxWhite = *White;
			}
			*White = 0;
			*cs = 1;
			break;
		case 2:
			++*White;
			break;
		}
		break;
	case 3:
		switch (Board_2018180044[*x][*y])
		{
		case 0:
		case 4:
			if (*Black > *MaxBlack)
			{
				BlackLocation[0] = *x;
				BlackLocation[1] = *y;
				*MaxBlack = *Black;
				*Black = 0;
			}
			*x = restart[0];
			*y = restart[1];
			*cs = 0;
			break;
		case 1:
			++*Black;
			break;

		case 2:
			*White = 1;
			if (*Black > *MaxBlack)
			{
				BlackLocation[0] = *x;
				BlackLocation[1] = *y;
				*MaxBlack = *Black;
			}
			*Black = 0;
			*cs = 2;
			break;
		}
		break;
	case 4:
		switch (Board_2018180044[*x][*y])
		{
		case 0:
		case 4:
			if (*White > *MaxWhite)
			{
				WhiteLocation[0] = *x;
				WhiteLocation[1] = *y;
				*MaxWhite = *White;
			}
			*White = 0;
			*x = restart[0];
			*y = restart[1];
			*cs = 0;
			break;
		case 1:
			*Black = 1;
			if (*White > *MaxWhite)
			{
				WhiteLocation[0] = *x;
				WhiteLocation[1] = *y;
				*MaxWhite = *White;
			}
			*White = 0;
			*cs = 1;
			break;
		case 2:
			++*White;
			break;
		}
		break;
	}
	if (!Diag)
	{
		if (A)
		{
			if (*x == 18)
			{
				if (*Black > *MaxBlack)
				{
					BlackLocation[0] = *x + 1;
					BlackLocation[1] = *y;
					*MaxBlack = *Black;
				}

				if (*White > *MaxWhite)
				{
					WhiteLocation[0] = *x + 1;
					WhiteLocation[1] = *y;
					*MaxWhite = *White;
				}
			}
		}

		else
		{
			if (*y == 18)
			{
				if (*Black > *MaxBlack)
				{
					BlackLocation[0] = *x;
					BlackLocation[1] = *y + 1;
					*MaxBlack = *Black;
				}

				if (*White > *MaxWhite)
				{
					WhiteLocation[0] = *x;
					WhiteLocation[1] = *y + 1;
					*MaxWhite = *White;
				}
			}
		}
	}

	else
	{
		if (A)
		{
			if (*x == 0 || *y == 18)
			{
				if (*Black > *MaxBlack)
				{
					BlackLocation[0] = *x - 1;
					BlackLocation[1] = *y + 1;
					*MaxBlack = *Black;
				}

				if (*White > *MaxWhite)
				{
					WhiteLocation[0] = *x - 1;
					WhiteLocation[1] = *y + 1;
					*MaxWhite = *White;
				}
			}
		}

		else
		{
			if (*x == 18 || *y == 18)
			{
				if (*Black > *MaxBlack)
				{
					BlackLocation[0] = *x + 1;
					BlackLocation[1] = *y + 1;
					*MaxBlack = *Black;
				}

				if (*White > *MaxWhite)
				{
					WhiteLocation[0] = *x + 1;
					WhiteLocation[1] = *y + 1;
					*MaxWhite = *White;
				}
			}
		}
	}
}

void MaxXStone_2018180044()
{
	int x = 0, y = 0;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (y < 19)
	{
		while (x < 19)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, TRUE, FALSE);
			++x;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{

			if (MaxBlack > MaxWhite)
			{
				if (MaxBlack > 3)
				{
					for (int j = BlackLocation[0] - MaxBlack - 1; j < BlackLocation[0] + 1; ++j)
					{
						if (Board_2018180044[j][y] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[j - 1][y] < 4)
							{
								if (j > BlackLocation[0] - MaxBlack && j < BlackLocation[0])
								{
									Board_2018180044[j][y] = 9;
								}
								else
								{
									Board_2018180044[j][y] = 7;
								}
							}
						}

						else if (Board_2018180044[j][y] >= 4 && (-1 < j && j < 19))
						{
							Board_2018180044[j][y] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[0] - MaxWhite - 1; j < WhiteLocation[0] + 1; ++j)
					{
						if (Board_2018180044[j][y] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[j - 1][y] < 4)
							{
								if (j > WhiteLocation[0] - MaxWhite && j < WhiteLocation[0])
									Board_2018180044[j][y] = 6;
								else
									Board_2018180044[j][y] = 4;
							}
							else if (Board_2018180044[j][y] >= 4 && (-1 < j && j < 19))
							{
								Board_2018180044[j][y] += 2;
							}
						}
					}
				}
			}

			else
			{
				if (MaxBlack > 3)
				{
					for (int j = BlackLocation[0] - MaxBlack - 1; j < BlackLocation[0] + 1; ++j)
					{
						if (Board_2018180044[j - 1][y] < 4)
						{
							if (j > BlackLocation[0] - MaxBlack && j < BlackLocation[0])
							{
								Board_2018180044[j][y] = 9;

							}
							else
							{
								Board_2018180044[j][y] = 7;
							}
						}
					}
				}
				
				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[0] - MaxWhite - 1; j < WhiteLocation[0] + 1; ++j)
					{
						if (Board_2018180044[j][y] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[j - 1][y] < 4)
							{
								if (j > WhiteLocation[0] - MaxWhite && j < WhiteLocation[0])
									Board_2018180044[j][y] = 6;
								else
									Board_2018180044[j][y] = 4;
							}
							else if (Board_2018180044[j][y] >= 4 && (-1 < j && j < 19))
							{
								Board_2018180044[j][y] += 2;
							}
						}
					}
				}
			}
		}

		x = 0;
		++y;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	}

}

void MaxYStone_2018180044()
{
	int x = 0, y = 0;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (x < 19)
	{
		while (y < 19)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, FALSE, FALSE);
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack >= MaxWhite)
			{
				if (MaxBlack > 3)
				{
					for (int j = BlackLocation[1] - MaxBlack - 1; j < BlackLocation[1] + 1; ++j)
					{
						if (Board_2018180044[x][j] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[x][j - 1] < 4)
							{
								if (j > BlackLocation[1] - MaxBlack && j < BlackLocation[1])
								{
										Board_2018180044[x][j] = 9;
								}
								else
								{
										Board_2018180044[x][j] = 7;
								}
							}

						}

						else if (Board_2018180044[x][j] >= 4 && (-1 < j && j < 19))
						{
							Board_2018180044[x][j] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[1] - MaxWhite - 1; j < WhiteLocation[1] + 1; ++j)
					{
						if (Board_2018180044[x][j] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[x][j - 1] < 4)
							{
								if (j > WhiteLocation[1] - MaxWhite && j < WhiteLocation[1])
									Board_2018180044[x][j] = 6;
								else
									Board_2018180044[x][j] = 4;
							}
						}
						else if(Board_2018180044[x][j]>=4&& (-1 < j && j < 19))
						{
							Board_2018180044[x][j] += 2;
						}
					}
				}
			}

			else
			{
				if (MaxBlack > 3)
				{
					for (int j = BlackLocation[1] - MaxBlack - 1; j < BlackLocation[1] + 1; ++j)
					{
						if (Board_2018180044[x][j] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[x][j - 1] < 4)
							{
								if (j > BlackLocation[1] - MaxBlack && j < BlackLocation[1])
								{
									Board_2018180044[x][j] = 9;
								}
								else
								{
									Board_2018180044[x][j] = 7;
								}
							}

						}

						else if (Board_2018180044[x][j] >= 4 && (-1 < j && j < 19))
						{
							Board_2018180044[x][j] = 0;
						}
					}
				}

				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[1] - MaxWhite - 1; j < WhiteLocation[1] + 1; ++j)
					{
						if (Board_2018180044[x][j] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[x][j - 1] < 4)
							{
								if (j > WhiteLocation[1] - MaxWhite && j < WhiteLocation[1])
									Board_2018180044[x][j] = 6;
								else
									Board_2018180044[x][j] = 4;
							}
						}
						else if (Board_2018180044[x][j] >= 4 && (-1 < j && j < 19))
						{
							Board_2018180044[x][j] += 2;
						}
					}
				}
			}
		}

		y = 0;
		++x;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	}
}

void BlackMaxXStone_2018180044()
{
	int x = 0, y = 0;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (y < 19)
	{
		while (x < 19)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, TRUE, FALSE);
			++x;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{

			if (MaxBlack > MaxWhite)
			{
				if (MaxBlack >= 3)
				{
					for (int j = BlackLocation[0] - MaxBlack - 1; j < BlackLocation[0] + 1; ++j)
					{
						if (Board_2018180044[j][y] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[j - 1][y] < 4)
							{
								if (j > BlackLocation[0] - MaxBlack && j < BlackLocation[0])
									Board_2018180044[j][y] = 6;
								else
									Board_2018180044[j][y] = 4;
							}
						}

						else if (Board_2018180044[j][y] >= 4 && (-1 < j && j < 19))
						{
							Board_2018180044[j][y] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[0] - MaxWhite - 1; j < WhiteLocation[0] + 1; ++j)
					{
						if (Board_2018180044[j][y] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[j - 1][y] < 4)
							{
								if (j > WhiteLocation[0] - MaxWhite && j < WhiteLocation[0])
									Board_2018180044[j][y] = 9;
								else
									Board_2018180044[j][y] = 7;
							}
							else if (Board_2018180044[j][y] >= 4 && (-1 < j && j < 19))
							{
								Board_2018180044[j][y] += 2;
							}
						}
					}
				}
			}

			else
			{
				if (MaxBlack >= 3)
				{
					for (int j = BlackLocation[0] - MaxBlack - 1; j < BlackLocation[0] + 1; ++j)
					{
						if (Board_2018180044[j][y] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[j - 1][y] < 4)
							{
								if (j > BlackLocation[0] - MaxBlack && j < BlackLocation[0])
									Board_2018180044[j][y] = 6;
								else
									Board_2018180044[j][y] = 4;
							}
						}

						else if (Board_2018180044[j][y] >= 4 && (-1 < j && j < 19))
						{
							Board_2018180044[j][y] += 2;
						}
					}
				}

				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[0] - MaxWhite - 1; j < WhiteLocation[0] + 1; ++j)
					{
						if (Board_2018180044[j][y] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[j - 1][y] < 4)
							{
								if (j > WhiteLocation[0] - MaxWhite && j < WhiteLocation[0])
									Board_2018180044[j][y] = 9;
								else
									Board_2018180044[j][y] = 7;
							}
							else if (Board_2018180044[j][y] >= 4 && (-1 < j && j < 19))
							{
								Board_2018180044[j][y] += 2;
							}
						}
					}
				}
			}
		}

		x = 0;
		++y;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	}

}

void BlackMaxYStone_2018180044()
{
	int x = 0, y = 0;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (x < 19)
	{
		while (y < 19)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, FALSE, FALSE);
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack >= MaxWhite)
			{
				if (MaxBlack >= 3)
				{
					for (int j = BlackLocation[1] - MaxBlack - 1; j < BlackLocation[1] + 1; ++j)
					{
						if (Board_2018180044[x][j] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[x][j - 1] < 4)
							{
								if (j > BlackLocation[1] - MaxBlack && j < BlackLocation[1])
									Board_2018180044[x][j] = 6;
								else
									Board_2018180044[x][j] = 4;
							}

						}

						else if (Board_2018180044[x][j] >= 4 && (-1 < j && j < 19))
						{
							Board_2018180044[x][j] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[1] - MaxWhite - 1; j < WhiteLocation[1] + 1; ++j)
					{
						if (Board_2018180044[x][j] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[x][j - 1] < 4)
							{
								if (j > WhiteLocation[1] - MaxWhite && j < WhiteLocation[1])
									Board_2018180044[x][j] = 9;
								else
									Board_2018180044[x][j] = 7;
							}
						}
						else if(Board_2018180044[x][j]>=4&& (-1 < j && j < 19))
						{
							Board_2018180044[x][j] += 2;
						}
					}
				}
			}

			else
			{
				if (MaxBlack >= 3)
				{
					for (int j = BlackLocation[1] - MaxBlack - 1; j < BlackLocation[1] + 1; ++j)
					{
						if (Board_2018180044[x][j] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[x][j - 1] < 4)
							{
								if (j > BlackLocation[1] - MaxBlack && j < BlackLocation[1])
									Board_2018180044[x][j] = 6;
								else
									Board_2018180044[x][j] = 4;
							}

						}

						else if (Board_2018180044[x][j] >= 4 && (-1 < j && j < 19))
						{
							Board_2018180044[x][j] = 0;
						}
					}
				}

				if (MaxWhite > 3)
				{
					for (int j = WhiteLocation[1] - MaxWhite - 1; j < WhiteLocation[1] + 1; ++j)
					{
						if (Board_2018180044[x][j] == 0 && (-1 < j && j < 19))
						{
							if (Board_2018180044[x][j - 1] < 4)
							{
								if (j > WhiteLocation[1] - MaxWhite && j < WhiteLocation[1])
									Board_2018180044[x][j] = 9;
								else
									Board_2018180044[x][j] = 7;
							}
						}
						else if (Board_2018180044[x][j] >= 4 && (-1 < j && j < 19))
						{
							Board_2018180044[x][j] += 2;
						}
					}
				}
			}
		}

		y = 0;
		++x;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	}
}

void MaxRDiagStone_2018180044()
{
	int x = 0, y = 0;
	int StartY = 18;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (StartY >= 0)
	{
		y = StartY;
		while (y < 19)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, FALSE, TRUE);
			++x;
			++y;
		}
		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
								{
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 9;
								}
								else
								{
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 7;
								}
							}
						}

						else if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 6;

								else
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}

			else
			{
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
								{
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 9;
								}
								else
								{	
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 7;
								}
							}
						}

						else if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 0;
						}
					}
				}

				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 6;

								else
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}
		}
		x = 0;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		--StartY;
	}
}

void BlackMaxRDiagStone_2018180044()
{
	int x = 0, y = 0;
	int StartY = 18;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (StartY >= 0)
	{
		y = StartY;
		while (y < 19)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, FALSE, TRUE);
			++x;
			++y;
		}
		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				if (MaxBlack >= 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 6;
								else
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 9;

								else
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 7;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}

			else
			{
				if (MaxBlack >= 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 6;
								else
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 0;
						}
					}
				}

				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 9;

								else
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 7;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}
		}
		x = 0;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		--StartY;
	}
}

void MaxRDiagStone2_2018180044()
{
	int x = 0, y = 0;
	int StartX = 1;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };
	while (StartX < 19)
	{
		x = StartX;
		while (x < 19)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, FALSE, TRUE);
			++x;
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
								{
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 9;
								}
								else
								{
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 7;
								}
							}
						}

						else if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 6;
								else
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}
			else
			{
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
								{
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 9;
								}
								else
								{
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 7;
								}
							}
						}

						else if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 0;
						}
					}
				}
				
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 6;
								else
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}
		}

		y = 0;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		++StartX;

	}
}

void BlackMaxRDiagStone2_2018180044()
{
	int x = 0, y = 0;
	int StartX = 1;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };
	while (StartX < 19)
	{
		x = StartX;
		while (x < 19)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, FALSE, TRUE);
			++x;
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				if (MaxBlack >= 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 6;
								else
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 9;
								else
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 7;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}
			else
			{
				if (MaxBlack >= 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] == 0 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] - i - 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 6;
								else
									Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] - i > -1 && BlackLocation[0] - i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] - i][BlackLocation[1] - i] = 0;
						}
					}
				}

				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] - i - 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 9;
								else
									Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] = 7;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] - i > -1 && WhiteLocation[0] - i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] - i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}
		}

		y = 0;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		++StartX;

	}
}

void MaxLDiagStone_2018180044()
{
	int x = 0, y = 0;
	int StartX = 0;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (StartX < 19)
	{
		x = StartX;
		while (x >= 0)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, TRUE, TRUE);
			--x;
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
								{
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 9;
								}
								else
								{
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 7;
								}
							}
						}

						else if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 6;
								else
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}

			else
			{
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
								{
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 9;
								}
								else
								{
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 7;
								}
							}
						}

						else if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 0;
						}
					}
				}

				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 6;
								else
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}
		}

		y = 0;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		++StartX;
	}
}

void BlackMaxLDiagStone_2018180044()
{
	int x = 0, y = 0;
	int StartX = 0;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (StartX < 19)
	{
		x = StartX;
		while (x >= 0)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, TRUE, TRUE);
			--x;
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				if (MaxBlack >= 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 6;
								else
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 9;
								else
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 7;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}

			else
			{
				if (MaxBlack >= 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 6;
								else
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 0;
						}
					}
				}

				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 9;
								else
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 7;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] += 2;
						}
					}
				}
			}
		}

		y = 0;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		++StartX;
	}
}

void MaxLDiagStone2_2018180044()
{
	int x = 18, y = 0;
	int StartY = 1;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (StartY < 19)
	{
		y = StartY;
		while (y < 19)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, TRUE, TRUE);
			--x;
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
								{
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 9;
								}
								else
								{
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 7;
								}
							}
						}

						else if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 6;
								else
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 4;
							}
						}

						else if(Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] += 2;
						}

					}
				}
			}
			else
			{
				if (MaxBlack > 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
								{
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 9;
								}
								else
								{
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 7;
								}
							}
						}
					}
				}

				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 6;
								else
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] += 2;
						}

					}
				}
			}
		}

		x = 18;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		++StartY;
	}
}

void BlackMaxLDiagStone2_2018180044()
{
	int x = 18, y = 0;
	int StartY = 1;
	int cs = 0;
	int Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
	int BlackLocation[2] = { 0 }, WhiteLocation[2] = { 0 }, restart[2] = { 0 };

	while (StartY < 19)
	{
		y = StartY;
		while (y < 19)
		{
			CountStone(&x, &y, &cs, &Black, &White, &MaxBlack, &MaxWhite, BlackLocation, WhiteLocation, restart, TRUE, TRUE);
			--x;
			++y;
		}

		if (MaxBlack != 0 || MaxWhite != 0)
		{
			if (MaxBlack > MaxWhite)
			{
				if (MaxBlack >= 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 6;
								else
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 0;
						}
					}
				}
			}

			else if (MaxBlack < MaxWhite)
			{
				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 9;
								else
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 7;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] += 2;
						}

					}
				}
			}
			else
			{
				if (MaxBlack >= 3)
				{
					for (int i = MaxBlack + 1; i > -1; --i)
					{
						if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] == 0 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							if (Board_2018180044[BlackLocation[0] + i + 1][BlackLocation[1] - i - 1] != 4)
							{
								if (i <= MaxBlack && i > 0)
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 6;
								else
									Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 4;
							}
						}

						else if (Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] >= 4 && (BlackLocation[0] + i > -1 && BlackLocation[0] + i < 19) && (BlackLocation[1] - i > -1 && BlackLocation[1] - i < 19))
						{
							Board_2018180044[BlackLocation[0] + i][BlackLocation[1] - i] = 0;
						}
					}
				}

				if (MaxWhite > 3)
				{
					for (int i = MaxWhite + 1; i > -1; --i)
					{
						if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] == 0 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							if (Board_2018180044[WhiteLocation[0] + i + 1][WhiteLocation[1] - i - 1] != 4)
							{
								if (i <= MaxWhite && i > 0)
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 9;
								else
									Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] = 7;
							}
						}

						else if (Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] >= 4 && (WhiteLocation[0] + i > -1 && WhiteLocation[0] + i < 19) && (WhiteLocation[1] - i > -1 && WhiteLocation[1] - i < 19))
						{
							Board_2018180044[WhiteLocation[0] + i][WhiteLocation[1] - i] += 2;
						}

					}
				}
			}
		}

		x = 18;
		cs = 0;
		Black = 0, White = 0, MaxBlack = 0, MaxWhite = 0;
		++StartY;
	}
}
void SetBoard_2018180044()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Board_2018180044[i][j] >= 4)
				Board_2018180044[i][j] = 0;
		}
	}
}

void WhiteAttack_2018180044CHS(int *x, int *y)
{
	int MaxBoard = -1;
	int maxPoint = 1;
	int tmpx = *x;
	int tmpy = *y;

	SetBoard_2018180044();
	MaxXStone_2018180044();
	MaxYStone_2018180044();
	MaxRDiagStone_2018180044();
	MaxRDiagStone2_2018180044();
	MaxLDiagStone_2018180044();
	MaxLDiagStone2_2018180044();

	for (int i = 0; i < 18; ++i)
	{
		for (int j = 0; j < 18; ++j)
		{
			if (Board_2018180044[i][j] >= 4 && Board_2018180044[i][j] > MaxBoard)
			{
				*x = i;
				*y = j;
				MaxBoard = Board_2018180044[i][j];
			}
		}
	}

	if (tmpx == *x && tmpy == *y)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (i == 1 && j == 1)
					break;

				if (LastWhiteX_2018180044 - 1 + i > -1 && LastWhiteX_2018180044 - 1 + i < 19 && LastWhiteY_2018180044 - 1 + j > -1 && LastWhiteY_2018180044 - 1 + j < 19 && WhitePoint(LastWhiteX_2018180044 - 1 + i, LastWhiteY_2018180044 - 1 + j) >= maxPoint)
				{
					*x = LastWhiteX_2018180044 - 1 + i;
					*y = LastWhiteY_2018180044 - 1 + j;
					maxPoint = WhitePoint(LastWhiteX_2018180044 - 1 + i, LastWhiteY_2018180044 - 1 + j);
				}
			}
		}
	}

	if (tmpx == *x && tmpy == *y)
	{
		while (1)
		{
			*x = rand() % 19;
			*y = rand() % 19;
			if (Board_2018180044[*x][*y] != 2 && Board_2018180044[*x][*y] != 1)
				break;
		}
	}

	if (!First)
	{
		while (1)
		{
			*x = LastBlackX_2018180044 - 1 + rand() % 3;
			*y = LastBlackY_2018180044 - 1 + rand() % 3;
			if (Board_2018180044[*x][*y] != 2 && Board_2018180044[*x][*y] != 1)
				break;
		}
		First = true;
	}

	LastWhiteX_2018180044 = *x;
	LastWhiteY_2018180044 = *y;

	Board_2018180044[*x][*y] = 2;
}

void BlackAttack_2018180044CHS(int *x, int *y)
{
	int MaxBoard = -1;
	int maxPoint = 1;
	int tmpx = *x;
	int tmpy = *y;
	;

	SetBoard_2018180044();
	BlackMaxXStone_2018180044();
	BlackMaxYStone_2018180044();
	BlackMaxRDiagStone_2018180044();
	BlackMaxRDiagStone2_2018180044();
	BlackMaxLDiagStone_2018180044();
	BlackMaxLDiagStone2_2018180044();

	movetoxy(0, 40);
	for (int i = 0; i < 18; ++i)
	{
		for (int j = 0; j < 18; ++j)
		{
			if (Board_2018180044[i][j] >= 4 && Board_2018180044[i][j] > MaxBoard)
			{
				*x = i;
				*y = j;
				MaxBoard = Board_2018180044[i][j];
			}
		}
	}

	if (tmpx == *x && tmpy == *y)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{

				if (i == 1 && j == 1)
				{

				}

				else if ((LastBlackX_2018180044 - 1 + i) > -1 && (LastBlackX_2018180044 - 1 + i) < 19 && (LastBlackY_2018180044 - 1 + j) > -1 && (LastBlackY_2018180044 - 1 + j) < 19 && BlackPoint(LastBlackX_2018180044 - 1 + i, LastBlackY_2018180044 - 1 + j) >= maxPoint)
				{
					*x = LastBlackX_2018180044 - 1 + i;
					*y = LastBlackY_2018180044 - 1 + j;
					maxPoint = BlackPoint(LastBlackX_2018180044 - 1 + i, LastBlackY_2018180044 - 1 + j);
				}

			}
		}
	}


	if (tmpx == *x && tmpy == *y)
	{
		while (1)
		{
			*x = rand() % 19;
			*y = rand() % 19;
			if (Board_2018180044[*x][*y] != 2 && Board_2018180044[*x][*y] != 1)
				break;
		}
	}

	if (!First)
	{
		*x = 9;
		*y = 9;
		First = true;
	}

	LastBlackX_2018180044 = *x;
	LastBlackY_2018180044 = *y;

	Board_2018180044[*x][*y] = 1;
}

void WhiteDefence_2018180044CHS(int x, int y)
{
	Board_2018180044[x][y] = 1;
	LastBlackX_2018180044 = x;
	LastBlackY_2018180044 = y;
}

void BlackDefence_2018180044CHS(int x, int y)
{
	Board_2018180044[x][y] = 2;
	LastWhiteX_2018180044 = x;
	LastWhiteY_2018180044 = y;
}