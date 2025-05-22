#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define endl '\n'

void solve()
{
    int n, x;
    cin >> n >> x;

    int bits = __builtin_popcount(x); // 计算 x 的二进制中 1 的个数

    // 分三种情况：

    // n<=bits,直接输出x
    // 当 n≤bits时，在数组元素中简单地分配不同的 2 的幂次是最优的，因此可实现的最小和为 x
    // 2的幂次没有进位，所以总和和 x 相同
    if (n <= bits)
    {
        cout << x << endl;
        return;
    }

    // n>bits，
    // 在额外的 n−bits元素中只添加 1 显然是有益的
    // 如果 x和 n−bits的奇偶性不同，我们还需要增加一个 1，使它们的 XOR等于 0

    if (!((n - bits) & 1)) // n-bits是偶数
    {
        // 直接输出 x + (n - bits)
        cout << x + (n - bits) << endl;
    }
    else
    {
        if (x > 1)
        {
            // 直接输出 x + (n - bits) + 1
            cout << x + (n - bits) + 1 << endl;
            return;
        }

        if (x == 1)
        {
            cout << 3 + n << endl;
            return;
        }

        else
        {
            if (n == 1)
            {
                cout << -1 << endl;
                return;
            }
            else
            {
                cout << n + 3 << endl;
                return;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}