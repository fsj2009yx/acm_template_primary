// 分组背包
// 同一组的物品只能选一个

#include <bits/stdc++.h>
using namespace std;
int v, n, t;
int x;
int g[205][205]; // g[i][j]表示第i组的第j个物品的物品序号
int i, j, k;
int w[10001], z[10001]; // w[i]表示第i个物品的体积，z[i]表示第i个物品的价值
int b[10001];           // 存储每组的物品数量
int dp[10001] = {0};    // dp[i]表示体积为i时的最大价值
int main()
{
    cin >> v >> n; // 总容积和物品数量
    for (i = 1; i <= n; i++)
    {
        cin >> w[i] >> z[i] >> x;
        t = max(t, x);
        b[x]++;
        g[x][b[x]] = i; // 存储序号用于dp时查找
    }

    // 等同于用一个map存储每个组对应的物品
    for (i = 1; i <= t; i++)
    {
        for (j = v; j >= 0; j--)
        {
            for (k = 1; k <= b[i]; k++)
            {
                if (j >= w[g[i][k]])
                {
                    dp[j] = max(dp[j], dp[j - w[g[i][k]]] + z[g[i][k]]); // 每组中选择一个物品，使得价值最大
                }
            }
        }
    }
    cout << dp[v];
    return 0;
}