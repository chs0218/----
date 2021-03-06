#include <iostream>
#include <conio.h>

using namespace std;

int input(char* sentence, int n)
{
	char ninput;

	for (int i = 0; i < 100; ++i)
	{
		ninput = _getwche();
		sentence[i] = ninput;
		if (ninput == 13)
		{
			sentence[i + 1] = '\0';
			n = i - 1;
			break;
		}
	}

	return n;
}

int correctspace(char* sentence, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (sentence[i] == ' '&&sentence[i + 1] == ' ')
		{
			for (int j = i + 1; j < n + 1; ++j)
			{
				sentence[j] = sentence[j + 1];
				i -= 1;
			}
			n -= 1;
		}
	}
	sentence[n + 1] = '\0';
	return n;
}

int areyouspecial(char* sentence, int n)
{
	int judge = 0;
	for (int i = 0; i < n; ++i)
	{
		if (sentence[i] <= 45 && sentence[i] >= 33)
			judge = 1;
		else if (sentence[i] == '\t')
			judge = 1;
	}
	return judge;
}

int howmanyword(char* sentence, int n)
{
	int wordn = 1;

	for (int i = 0; i < n; ++i)
		if (sentence[i] == ' ')
		{
			++wordn;
		}
	if (sentence[0] == ' ')
		--wordn;
	if (sentence[n - 1] == ' ')
		--wordn;
	return wordn;
}

void lastcorrection(char* sentence, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (sentence[i] == 'E' || sentence[i] == 'e')
		{
			for (int j = i; j >= 0; --j)
			{
				if (sentence[j] <= 'z' && sentence[j] >= 'a')
					sentence[j] = toupper(sentence[j]);
				if (sentence[j] == ' ')
					j = -1;
			}

			for (int j = i; j <= n; ++j)
			{
				if (sentence[j] <= 'z' && sentence[j] >= 'a')
					sentence[j] = toupper(sentence[j]);
				if (sentence[j] == ' ')
					j = n + 1;
			}
		}
	}
}

void output(char* sentence, int judge, int n, int wordn)
{

	if (judge == 1)
		cout << "\nResult: Error: Special character is included.\n";
	else if (sentence[n] != '.')
		cout << "\nResult: Error: the sentence is not ended.\n";
	else if (sentence[n] == '.')
	{
		cout << "\nNew sentence: " << sentence;
		cout << "\nResult: " << wordn << " words\n";
	}
}

int main()
{
	char* sentence = new  char[100];
	int n = 0, wordn = 1, judge = 0;
	cout << "input sentence: ";

	n = input(sentence, n);
	n = correctspace(sentence, n);
	judge = areyouspecial(sentence, n);
	wordn = howmanyword(sentence, n);
	lastcorrection(sentence, n);
	output(sentence, judge, n, wordn);
}
