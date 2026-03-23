#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10, mod = 998244353;

ll n, a[N], res;               // n: 数组长度   a[]: 原始数组   res: 最终答案
ll last, stlast;               // 下面两个变量只在合并 gcd 区间时临时用
vector<pair<ll, ll>> vp1, vp2; // vp1: 上一次迭代留下的 (gcd值 , 最左下标) 列表
                               // vp2: 本轮新算出的列表

/* ---------- 工具函数 ---------- */
ll gcd(ll a, ll b)
{ // 手写 gcd，递归写法
    return b ? gcd(b, a % b) : a;
}

/* ---------- 主函数 ---------- */
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    /* 初始化：以第 1 个数为右端点时只有一个区间 [1,1] */
    vp1.emplace_back(a[1], 1); // (gcd, left) = (a1, 1)
    res = a[1];                // 只有一个区间的和就是 a1

    /* 从第 2 个数开始扫描右端点 i */
    for (int i = 2; i <= n; ++i)
    {
        vp2.clear(); // 准备本轮的新列表

        /* 1) 先把 [i,i] 这个新区间放进去 */
        vp2.emplace_back(a[i], i);
        last = a[i], stlast = i; // last 记录“上一个”gcd 值，方便合并相同值

        /* 2) 把 vp1 中所有区间和 a[i] 再取一次 gcd，并合并相邻且值相同的区间 */
        for (auto v : vp1)
        {
            ll num = v.first;     // 之前的 gcd 值
            ll st = v.second;     // 这个 gcd 对应的最左端点
            num = gcd(num, a[i]); // 新 gcd
            if (num != last)
            { // 与上一个不同，新开一段
                vp2.emplace_back(num, st);
            }
            else
            { // 与上一个相同，向左延长区间
                vp2.back().second = st;
            }
            last = num; // 更新“上一个”gcd 值
        }

        /* 3) 计算“以 i 为右端点的所有区间”对答案的贡献 */
        last = i + 1; // last 先设成一个哨兵，便于公式写差分
        for (auto v : vp2)
        {
            ll g = v.first;  // 当前这段的 gcd
            ll l = v.second; // 这段区间的最左端点
            /* 区间 [l, last-1] 内的所有左端点 j 都对应 gcd = g
               个数 = (last - l)
               这个区间对答案的贡献 = g * Σ_{j=l}^{last-1} j
               Σ_{j=l}^{last-1} j = (l + last - 1) * (last - l) / 2   */
            ll temp = (last + l - 1) * (last - l) / 2 % mod;
            res = (res + g * i % mod * temp % mod) % mod;
            last = l; // 向左推进
        }

        /* 4) 把 vp2 变成下一轮用的 vp1 */
        vp1.swap(vp2);
    }

    cout << res << '\n';
    return 0;
}
