#include <iostream>
#include <string>
using namespace std;

const int N = 100010, M = 1000010;

int n, m;
int ne[N];
string s, p;

void get_Next(string s, int ne[]) // 这个函数对字符串s进行预处理得到next数组
{
	int j = 0;
	ne[0] = 0; // 初始化
	for (int i = 1; i < s.size(); i++)
	{ // i指针指向的是后缀末尾，j指针指向的是前缀末尾
		while (j > 0 && s[i] != s[j])
			j = ne[j - 1]; // 前后缀不相同，去找j前一位的最长相等前后缀
		if (s[i] == s[j])
			j++;   // 前后缀相同，j指针后移
		ne[i] = j; // 更新next数组
	}
}

int main()
{
	cin >> n >> p >> m >> s;
	// 变量分别为 待匹配串的长度，模式串，模式串的长度，待匹配串
	get_Next(p, ne);
	// 输出所有匹配的位置的下标
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
