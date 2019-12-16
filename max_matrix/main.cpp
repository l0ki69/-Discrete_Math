#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <ctime>

using namespace std;


void matrix(vector <int> N, vector <int> M, int size, vector <vector <int>>& c)
{
//	int n = N.size();
//	int m = M.size();

/*	int size = 0;
	if (m > n) size = m + 2; else size = n + 2; */

	int En = 0, Em = 0;
	for (int i = 0; i < N.size(); i++)
	{
		En += N.at(i);
	}
	for (int i = 0; i < M.size(); i++)
	{
		Em += M.at(i);
	}
	//int maxE = (Em > En ? Em : En);
	int maxE = En;

/*	vector <vector <int>> c(size,vector<int>(size,0));
	vector <vector <int>> f(size, vector<int>(size,0)); */


	int nn = 0;
	int mm = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j) { c[i][j] = 0; continue; }

			if (j == 0) { c[i][j] = 0; continue; }

			if (i == 1) { c[i][j] = 0; continue; }

			if ((i == 0) && (j > 1) && (mm < M.size()))
			{
				c[i][j] = M.at(mm);
				mm++;
				continue;
			}
			else if ((i == 0) && (j > 1)) c[i][j] = 0;

			if ((j == 1) && (i > 1) && (nn < N.size()))
			{
				c[i][j] = N.at(nn);
				nn++;
				continue;
			}
			else if ((j == 1) && (i > 1)) c[i][j] = 0;

			if ((i > 1) && (j > 1)) c[i][j] = maxE; 
		}
	}
}

int bfs(vector <int>& p,int n, vector <vector <int>>& c)
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

int main()
{
	int s = 0, s1 = 0;
	setlocale(LC_ALL, "Rus");
	string change[8]{ "1","2","3", "4", "5", "6", "7","8" };
	string in, out;
	for (int ii = 0; ii < 5; ii++)
	{
		unsigned int start_time2 = clock();
		in = "D:\\tests\\max_matrix\\test" + change[ii];
		in = in + ".in";
		out = "D:\\tests\\max_matrix\\test" + change[ii];
		out = out + ".out";
		cout << "-----------------------------" << endl;
		cout << "фаил # " << ii + 1 << endl;

		ifstream fin(in);
		ifstream fout(out);

		fout >> s1;
		int n = 0, m = 0;
		fin >> n;
		fin >> m;

		vector <int> N;
		vector <int> M;

		int temp;
		for (int i = 0; i < n; i++)
		{
			fin >> temp;
			N.push_back(temp);
		}
		for (int i = 0; i < m; i++)
		{
			fin >> temp;
			M.push_back(temp);
		}

		int size = 0;
		if (m > n) size = m + 2; else size = n + 2;
		vector <vector <int>> c(size, vector<int>(size, 0));
		vector <vector <int>> f(size, vector<int>(size, 0));

		matrix(N,M,size,c);

		int w;

		vector <int> p;

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

	/*	int max1 = 0;
		int max2 = 0;

		for (int i = 0; i < n; i++)
		{
			max1 += N.at(i);
		}
		for (int i = 0; i < m; i++)
		{
			max2 += M.at(i);
		}

		cout << "max1 = " << max1 << endl;
		cout << "max2 = " << max2 << endl;

		if (max1 < max2) 
		{
			s = max1;
		}
		else s = max2;  */
	

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