#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <ctime>

using namespace std;

int f[1000][1000];
int c[1000][1000];
int n;

void clear()
{
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			f[i][j] = 0;
			c[i][j] = 0;
		}
	}
}

int bfs(vector <int>& p)
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
		if (now == 1) { bl = false; break;}

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

int main()
{
	int s = 0, s1 = 0;
	setlocale(LC_ALL, "Rus");
	string change[8]{"1","2","3", "4", "5", "6", "7","8"};
	string in, out;
	for (int ii = 0; ii < 8; ii++) 
	{
		unsigned int start_time2 = clock();
		in = "D:\\tests\\max_flow\\test" + change[ii];
		in = in + ".in";
		out = "D:\\tests\\max_flow\\test" + change[ii];
		out = out + ".out";
		cout << "-----------------------------" << endl;
		cout << "фаил # " << ii+1 << endl;

		ifstream fin(in);
		ifstream fout(out);

		fout >> s1;
		fin >> n;

		vector <int> p;
		int w;
		clear();

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				fin >> c[i][j];
			}
		}

		while (w = bfs(p))
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
		for (int i = 0; i < n ; i++) {
			s += f[0][i];
		}

		cout << "правильный ответ - " << s1 << endl;
		cout << "получившийся ответ " << s << endl;
		fin.close();
		fout.close();
		unsigned int end_time2 = clock();
		cout << "врем¤ работы - " << (double)(end_time2 - start_time2) / 1000 << "  секунд" << endl;
		cout << "-----------------------------" << endl;
	}


	system("pause>>NUll");
	return 0;
}