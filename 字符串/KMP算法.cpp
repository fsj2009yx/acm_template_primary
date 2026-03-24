#include <iostream>
#include <string>
using namespace std;

const int N = 100010, M = 1000010;

int n, m;
int ne[N];
string s, p;

void get_Next(string s, int ne[])
{
	int j = 0;
	ne[0] = 0; // ��ʼ��
	for (int i = 1; i < s.size(); i++)
	{
		while (j > 0 && s[i] != s[j])
			j = ne[j - 1];
		if (s[i] == s[j])
			j++;
		ne[i] = j;
	}
}

int main()
{
	cin >> n >> p >> m >> s;

	get_Next(p, ne);

	for (int i = 0, j = 0; i < m; i++)
	{
		while (j > 0 && s[i] != p[j])
			j = ne[j - 1];
		if (s[i] == p[j])
			j++;
		if (j == n)
		{
			cout << i - n + 1 << " ";
			j = ne[j - 1];
		}
	}

	return 0;
}
