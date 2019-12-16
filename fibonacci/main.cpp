#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <ctime>
#include<windows.h>

using namespace std;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


unsigned long long fib_n(unsigned long long n, unsigned long long m)
{
	unsigned long long a = 0, b = 1;

	while (n != 0)
	{
		a = a + b;

		b = a - b;
		if ((a > m) && (b > m))
		{
			a %= m;
			b %= m;
		}
		n--;
	}
	return a;
}

unsigned long long fib(unsigned long long n, unsigned long long m)
{
	unsigned long long a = 1, ta,
		b = 1, tb,
		c = 1, rc = 0, tc,
		d = 0, rd = 1;

	while (n)
	{
		if (n & 1) 
		{
			tc = rc;
			rc = rc*a + rd*c;
			rd = tc*b + rd*d;
		}
		ta = a; tb = b; tc = c;

		a = a*a + b*c;
		b = ta*b + b*d;
		c = c*ta + d*c;
		d = tc*tb + d*d;

		if ((a > m) && (b > m) && (c > m) && (d > m))
		{
			a %= m;
			b %= m;
			c %= m;
			d %= m;
		}
		if ((rc > m) && (rd > m))
		{
			rc %= m;
			rd %= m;
		}

		n >>= 1;
	}

	return rc%m;
}

#define MinIndex 1
#define MaxIndex 410

int main()
{
	unsigned long long s1,s = 0;
	setlocale(LC_ALL, "Rus");
	string change;
	string in, out;

	unsigned long long n, m;

	double abctime = 0;

	for (unsigned long long ii = MinIndex; ii < MaxIndex+1; ii++)
	{
		unsigned int start_time2 = clock();

		change = to_string(ii);

		in = "D:\\tests\\fibonacci\\test" + change + ".in";
		out = "D:\\tests\\fibonacci\\test" + change + ".out";
		cout << "-----------------------------" << endl;
		cout << "фаил # " << ii << endl;

		ifstream fin(in);
		ifstream fout(out);

		fout >> s1;

		fin >> n;
		fin >> m;

	//	cout << "число фибоначчи № " << n << " = " << fib_n(n,m) << endl;
	//	cout << "число фибоначчи № " << n << " по модулю " << m << " = " << fib_n(n,m) % m << endl;

		s = fib(n,m);

		if (s == s1) SetColor(Blue, Black); else SetColor(Red, Black);
		cout << "правильный ответ - " << s1 << endl;
		cout << "получившийся ответ " << s << endl;
		fin.close();
		fout.close();
		unsigned int end_time2 = clock();
		double time = (double)(end_time2 - start_time2) / 1000;
		cout << "время работы - " << time << "  секунд" << endl;
		cout << "-----------------------------" << endl;
		abctime += time;
	}

	cout << "время потраченное на все тесты = " << abctime << endl;
	system("pause>>NUll");
	return 0;
}