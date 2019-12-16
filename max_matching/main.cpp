#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <ctime>

using namespace std;

void matrix(vector <vector <int>>& c, int size, vector <vector <int>> buf,int n, int m)
{
	c[0][1] = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j) { c[i][j] = 0; continue; }
			if ((j == 0) || (i == 1)) { c[i][j] = 0; continue; }
			if (((i == 0) && (j > 1) && (j <= (n + 1))) || ((j == 1) && (i > 1) && (i > (n + 1)))) { c[i][j] = 1; continue; }
		}
	}
	for (int i = 0; i < buf.size(); i++)
	{
		if (buf[i][0] == 0) continue;
		for (int j = 1; j < buf[i][0]+1; j++)
		{
			c[i + 2][buf[i][j] + n + 2] = 1;
		}
	}
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
	int s = 0, s1 = 0;
	setlocale(LC_ALL, "Rus");
	string change[8]{ "1","2","3", "4", "5", "6", "7","8" };
	string in, out;
	for (int ii = 6; ii < 7; ii++)
	{
		unsigned int start_time2 = clock();
		in = "D:\\tests\\max_matching\\test" + change[ii];
		in = in + ".in";
		out = "D:\\tests\\max_matching\\test" + change[ii];
		out = out + ".out";
		cout << "-----------------------------" << endl;
		cout << "фаил # " << ii + 1 << endl;

		ifstream fin(in);
		ifstream fout(out);
		int n, m;
		fout >> s1;
		fin >> n;
		fin >> m;

		int size = 0;
		size = n + m + 2;
		vector <vector <int>> c(size, vector<int>(size, 0));
		vector <vector <int>> f(size, vector<int>(size, 0));

//----------------------------------------------------------------------------------
		vector <vector <int>> buf(n, vector <int>());
		int k = -1;
		while (!fin.eof())
		{
			char ch[20000];
			fin.getline(ch, 20000,'\n');

			int i = 0;
			while (ch[i] != '\0')
			{
				int j = i;
				string str;
				while (ch[j] != ' ')
				{
					str += ch[j];
					i++;
					j++;
				}
				i++;
				buf[k].push_back(atoi(str.c_str()));
			}
			k++;
		}
//--------------------------------------------------------------------------------------

		matrix(c, size, buf,n,m);
		
	//	print(c,size);

		vector <int> p;
		int w;
		k = 0;
		
		

		while (w = bfs(p,size,c))
		{
			if (ii == 4)
			{
				(k % 100 == 0 ? cout << k << endl : cout << k << " ");
				k++;
			}
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