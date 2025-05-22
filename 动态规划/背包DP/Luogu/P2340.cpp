#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
typedef long long ll;

int dp[800010]; // dp[i]表示情商为i时的最大智商

// 800010数值较大，使用一维dp数组

int main()
{
    int n;
    cin >> n;
    vector<int> iq(n + 1); // 智商
    vector<int> eq(n + 1); // 情商

    for (int i = 1; i <= n; i++)
    {
        cin >> iq[i] >> eq[i];
    }

    // 假定偏移量为400000，dp数组大小为800010
    int offset = 400000;

    // 初始化dp数组为负无穷
    for (int i = 0; i < 800010; i++)
    {
        dp[i] = ~0x3f3f3f3f; // 负无穷
    }

    // 初始化
    dp[0 + offset] = 0; // 情商为0时，智商为0

    // 先求ip和最大的情况
    for (int i = 1; i <= n; i++)
    {
        if (eq[i] > 0)
        {
            for (int j = 800000; j >= eq[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - eq[i]] + iq[i]);
            }
        }
        else
        {
            // 负数需要正向DP
            for (int j = 0; j <= 800000 + eq[i]; j++)
            {
                dp[j] = max(dp[j], dp[j - eq[i]] + iq[i]);
            }
        }
    }

    int ans = 0;

    // 从标准0值开始遍历，保证eq和大于等于0
    for (int i = offset; i < 800010; i++)
    {
        if (dp[i] >= 0)                         // 要求iq总和为正数
            ans = max(ans, dp[i] + i - offset); // iq+eq
    }

    cout << ans << endl; // 输出最大值
}