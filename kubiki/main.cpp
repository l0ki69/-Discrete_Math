#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <ctime>

using namespace std;

void print(vector <vector <int>> c, int size);

void matrix(vector <vector <int>>& c, int size, vector <string> buf, int n, string word)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (((i == 0) && (j > 1) && (j <= (n + 1))) || ((j == 1) && (i > 1) && (i > (n + 1)))) { c[i][j] = 1; continue; }
		}
	} 
	bool bl;
	int k = -1;
	for (int i = 0; i < buf.size(); i++)
	{
		for (int j = 0; j < word.size(); j++)
		{
			k = buf[i].find(word[j]);
			if (k >= 0)
			{
				c[i+2][j+n+2] = 1;
			}
		}
	}
//	print(c,size);
//	system("pause>>NULL");
}

int bfs(vector <int>& p, int n, vector <vector <int>> c)
{
	p.clear();
	vector <int> used(n, -1);
	queue <int> q;
	used.at(0) = 0; q.push(0);
	int now = 0;
	bool bl = true;

	while (bl)
	{
		now = q.front();
		q.pop();
		if (now == 1) { bl = false; break; }

		for (int i = 0; i < n; i++)
		{
			if ((c[now][i] > 0) && (used[i] == -1))
			{
				q.push(i);
				used.at(i) = now;
				if (i == 1) { bl = false; break; }
			}
		}
		if (q.empty())
		{
			bl = false;
			break;
		}
		if (q.back() == 1) bl = false;
	}

	if (used[1] == -1) { return 0; }
	int min = 0;

	int i = 1;
	min = c[used.at(i)][i];
	while (i != 0) {
		if (c[used.at(i)][i] < min)
		{
			min = c[used.at(i)][i];
		}
		p.push_back(i);
		i = used.at(i);
	}
	p.push_back(0);

	return min;
}

void print(vector <vector <int>> c, int size)
{
	cout << "    ";
	for (int i = 0; i < size; i++) cout << i << " ";
	cout << endl;
	for (int i = 0; i < size * 2 + 4; i++) cout << '-';
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << i << " | ";
		for (int j = 0; j < size; j++)
		{
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	system("pause>>NULL");
}
int main()
{
	int s = 0;
	string s1;
	setlocale(LC_ALL, "Rus");
	string change[8]{ "1","2","3", "4", "5", "6", "7","8" };
	string in, out;
	for (int ii = 0; ii < 8; ii++)
	{
		unsigned int start_time2 = clock();
		in = "D:\\tests\\kubiki\\test" + change[ii];
		in = in + ".in";
		out = "D:\\tests\\kubiki\\test" + change[ii];
		out = out + ".out";
		cout << "-----------------------------" << endl;
		cout << "фаил # " << ii + 1 << endl;

		ifstream fin(in);
		ifstream fout(out);
		int n;
		string word;
		fout >> s1;
		fin >> n;
		fin >> word;

		int size = 0;
		size = n + word.size() + 2;
		vector <vector <int>> c(size, vector<int>(size, 0));
		vector <vector <int>> f(size, vector<int>(size, 0));

		//----------------------------------------------------------------------------------

		vector <string> buf;
		string str;
		while (!fin.eof())
		{
			fin >> str;
			buf.push_back(str);
		}
		buf.pop_back();

		//--------------------------------------------------------------------------------------

		matrix(c, size, buf, n, word);

		//	print(c,size);

		vector <int> p;
		int w;
		int k = 0;


		while (w = bfs(p, size, c))
		{

			for (int i = 0; i < p.size() - 1; i++)
			{
				int a = p.at(i + 1);
				int b = p.at(i);
				f[a][b] += w;
				f[b][a] -= w;
				c[a][b] -= w;
				c[b][a] += w;
			}
		}
		s = 0;
		for (int i = 0; i < size; i++) {
			s += f[0][i];
		}
		string h;
		if (s == word.size()) h = "YES"; else h = "NO";
		cout << "правильный ответ - " << s1 << endl;
		cout << "получившийся ответ " << h << endl;
		fin.close();
		fout.close();
		unsigned int end_time2 = clock();
		double time = (double)(end_time2 - start_time2) / 1000;
		//if (time > 1) time = 0.999;
		cout << "время работы - " << time << "  секунд" << endl;
		cout << "-----------------------------" << endl;
	}


	system("pause>>NUll");
	return 0;
}