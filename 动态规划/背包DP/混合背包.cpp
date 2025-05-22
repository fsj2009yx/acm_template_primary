#include <bits/stdc++.h>
using namespace std;

const int N = 10005;
int cnt[N];     // 每种樱花树可以可以看的次数
int t[N], c[N]; // t[i]表示第i种樱花树的时间，c[i]表示第i种樱花树的美丽值
int f[N][N];    // f[i][j]表示在时间i内看j种樱花树的最大美丽值

string time1, time2;
int T;
int n;
int main()
{
    cin >> time1 >> time2 >> n;
    istringstream s1(time1), s2(time2);
    int h1, m1, h2, m2;
    char ch;
    s1 >> h1 >> ch >> m1;
    s2 >> h2 >> ch >> m2;
    int t1 = h1 * 60 + m1, t2 = h2 * 60 + m2;
    T = t2 - t1;
    /*
    每行三个正整数：看完第 i 棵树的耗费时间 T，第 i 棵树的美学值 C，看第 i 棵树的次数 P​
    */
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i] >> c[i] >> cnt[i];
    }

    // 边界
    for (int i = 0; i <= T; i++)
    {
        f[i][0] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        f[0][i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        if (cnt[i] == 0) // 完全背包
        {
            for (int j = 1; j <= T; j++)
            {
                f[j][i] = f[j][i - 1];
                for (int k = 1; k * t[i] <= j; k++)
                {
                    f[j][i] = max(f[j][i], f[j - k * t[i]][i - 1] + k * c[i]);
                }
            }
        }
        else // 做cnt[i]次0-1背包
        {
            for (int j = 1; j <= T; j++)
            {
                f[j][i] = f[j][i - 1];
                for (int k = 1; k <= cnt[i] && k * t[i] <= j; k++)
                {
                    f[j][i] = max(f[j][i], f[j - k * t[i]][i - 1] + k * c[i]);
                }
            }
        }
    }
    cout << f[T][n] << endl;
}