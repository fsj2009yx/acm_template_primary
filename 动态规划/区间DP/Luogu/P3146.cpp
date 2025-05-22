#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> dp(n + 1, 0);
    // vector<int> sum(n + 1, 0); // 前缀和

    vector<vector<int>> f(n + 1, vector<int>(n + 1, 0)); // f1[i][j]表示区间[i,j]的最大值

    vector<vector<bool>> merge(n + 1, vector<bool>(n + 1, false)); // merge[i][j]表示区间[i,j]是否可以合并

    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        cin >> dp[i];
    }

    for (int i = 1; i <= n; i++)
    {
        // sum[i] = sum[i - 1] + dp[i]; // 前缀和
        f[i][i] = dp[i];    // 初始化边界
        merge[i][i] = true; // 初始化为true
    }

    for (int len = 2; len <= n; ++len)
    {
        for (int i = 1; i + len - 1 <= n; ++i)
        {
            int j = i + len - 1;
            for (int k = i; k < j; ++k)
            {
                if (merge[i][k] && merge[k + 1][j] && f[i][k] == f[k + 1][j])
                {
                    merge[i][j] = true;
                    f[i][j] = f[i][k] + 1;
                    break; // 一旦能合并就退出（只关心是否能合并）
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            if (merge[i][j])
                ans = max(ans, f[i][j]);

    cout << ans << endl;
    return 0;
}