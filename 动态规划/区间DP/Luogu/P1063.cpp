#include <bits/stdc++.h>
using namespace std;

int n;
int f1[205][205];

// f[i][i]表示区间 [i,j] 内的所有石子合并到一起的最大得分

int dp[205];

int ans_max = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    dp[0] = 1;
    // 原题在环上
    // 先将环破开，变成链
    // 破环成链，dp[i]表示第i个点的权值
    // 由于是环，dp[i] = dp[i + n]
    // 等于开了两倍的链
    for (int i = 1; i <= n; i++)
    {
        cin >> dp[i];
        dp[i + n] = dp[i];
    }

    // 数组存放的是珠子的左右边界，最大长度应该为n+1，即

    for (int len = 2; len <= n + 1; len++) // 枚举区间长度
    {
        for (int i = 1; i + len - 1 <= 2 * n; i++) // 枚举区间起点
        {
            int j = len + i - 1;                       // 假如len为2，i为1，j为2
            for (int k = i + 1; k <= len + i - 2; k++) // 此时合并不合法，所以这里没有满足循环条件
            {
                f1[i][j] = max(f1[i][j], f1[i][k] + f1[k][j] + dp[i] * dp[k] * dp[j]);
            }
        }
    }

    // 由于破环成链×2倍，最值要比较f(1,n),f(2,n+1),f(3,n+2),f(4,n+3)……f(n-1,2n-2)中的最大值和最小值
    for (int i = 1; i <= n; i++)
    {
        ans_max = max(ans_max, f1[i][i + n]);
    }
    // 输出
    cout << ans_max << endl;
}