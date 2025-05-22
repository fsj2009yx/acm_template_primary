#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
// 高精度加法
string addHighPrecision(const string &s1, const string &s2)
{
	int a[N], b[N], c[N];
	int j = 1, k = 1;
	for (int i = s1.size() - 1; i >= 0; i--)
		a[j++] = s1[i] - '0';
	for (int i = s2.size() - 1; i >= 0; i--)
		b[k++] = s2[i] - '0';

	int ma = max(s1.size(), s2.size());
	int ans = 0;
	for (int i = 1; i <= ma; i++)
	{
		ans = ans + (a[i] + b[i]);
		c[i] = ans % 10; // 处理个位
		ans = ans / 10;	 // 处理进位
	}

	if (ans)
		c[++ma] = ans; // 处理最高位

	string result;
	for (int i = ma; i >= 1; i--)
	{
		result += to_string(c[i]);
	}
	return result;
}

// 高精度减法
string subHighPrecision(string &s1, string &s2)
{
	int a[N], b[N], c[N], flag = 0;
	string result;

	if (s1.size() < s2.size() || s1.size() == s2.size() && atoi(s1.c_str()) < atoi(s2.c_str()))
	{
		// atoi 函数只能处理整数值的范围是 -2147483648 到 2147483647，如果整数的位数超过了这个范围，就会导致溢出。
		// 届时使用高精度比较函数
		flag = 1;
		swap(s1, s2); // 保证s1永远是大于s2
	}

	int j = 1, k = 1;
	for (int i = s1.size() - 1; i >= 0; i--)
		a[j++] = s1[i] - '0';
	for (int i = s2.size() - 1; i >= 0; i--)
		b[k++] = s2[i] - '0';

	int ma = max(s1.size(), s2.size());
	for (int i = 1; i <= ma; i++)
	{
		if (a[i] - b[i] < 0)
		{
			a[i] = a[i] + 10;
			a[i + 1] = a[i + 1] - 1;
		}
		c[i] = a[i] - b[i];
	}

	while (c[ma] == 0 && ma > 1)
		ma--;

	if (flag == 1)
		result += "-";

	for (int i = ma; i >= 1; i--)
	{
		result += to_string(c[i]);
	}

	return result;
}

// 高精度乘法
string mulHighPrecision(const string &s1, const string &s2)
{

	int a[N], b[N], s[N], c[N];

	int j = 1, k = 1;
	for (int i = s1.size() - 1; i >= 0; i--)
		a[j++] = s1[i] - '0';
	for (int i = s2.size() - 1; i >= 0; i--)
		b[k++] = s2[i] - '0';

	for (int i = 1; i <= s1.size(); i++)
	{
		for (int j = 1; j <= s2.size(); j++)
		{
			s[i + j - 1] += a[i] * b[j]; // 单个数组逐一相乘
		}
	}
	int ma = s1.size() + s2.size() - 1; // 记录一下最高位数
	int ans = 0;
	for (int i = 1; i <= ma; i++) // 高精度算法的核心
	{
		ans = ans + s[i];
		c[i] = ans % 10;
		ans = ans / 10;
	}
	if (ans)
		c[++ma] = ans; // 考虑进位的情况
	while (c[ma] == 0 && ma > 1)
		ma--; // 前导0的处理

	string result;
	for (int i = ma; i >= 1; i--)
	{
		result += to_string(c[i]);
	}
	return result;
}

string div(string a, int b) // 高精度a除以单精度b
{
	string r, ans;
	int d = 0;
	if (a == "0")
		return a; // 特判
	for (int i = 0; i < a.size(); i++)
	{
		r += (d * 10 + a[i] - '0') / b + '0'; // 求出商
		d = (d * 10 + (a[i] - '0')) % b;	  // 求出余数
	}
	int p = 0;
	for (int i = 0; i < r.size(); i++)
		if (r[i] != '0')
		{
			p = i;
			break;
		}
	return r.substr(p);
}

// 高精度比较，返回1，0，-1分别表示大于，等于，小于
int cmpHighPrecision(const string &s1, const string &s2)
{
	int ma = s1.size();
	int mb = s2.size();
	if (ma > mb)
	{
		return 1;
	}
	else if (ma < mb)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i <= ma; i++)
		{
			if (s1[i] > s2[i])
			{
				return 1;
			}
			else if (s1[i] < s2[i])
			{
				return -1;
			}
		}
		return 0;
	}
}

// 使用示例
int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	cout << mulHighPrecision(s1, s2) << endl;
	return 0;
}