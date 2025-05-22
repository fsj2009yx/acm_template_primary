#include <bits/stdc++.h>
using namespace std;

int n;
int f1[205][205];
int f2[205][205];

// f[i][i]表示区间 [i,j] 内的所有石子合并到一起的最大得分

int dp[205];
int sum[205];

int ans_max = 0;
int ans_min = 0x3f3f3f3f;

int main()
{
    cin >> n;
    dp[0] = 0;
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

    // 初始化
    for (int i = 1; i <= 2 * n; i++)
    {
        // 前缀和，用于优化求和计算
        sum[i] = sum[i - 1] + dp[i];
        // 初始化边界
        f1[i][i] = 0;
        f2[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) // 枚举区间长度
    {
        for (int i = 1; i <= 2 * n - len; i++) // 枚举区间起点
        {
            int j = len + i - 1;
            f2[i][j] = 0x3f3f3f3f;
            for (int k = i; k < j; k++)
            {
                f1[i][j] = max(f1[i][j], f1[i][k] + f1[k + 1][j] + sum[j] - sum[i - 1]);
                f2[i][j] = min(f2[i][j], f2[i][k] + f2[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }

    // 由于破环成链×2倍，最值要比较f(1,n),f(2,n+1),f(3,n+2),f(4,n+3)……f(n-1,2n-2)中的最大值和最小值
    for (int i = 1; i <= n; i++)
    {
        ans_max = max(ans_max, f1[i][i + n - 1]);
        ans_min = min(ans_min, f2[i][i + n - 1]);
    }
    // 输出
    cout << ans_min << endl;
    cout << ans_max << endl;
}