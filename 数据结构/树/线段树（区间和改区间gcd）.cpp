// 掌握修改方式，代码仅供参考

// 维护 区间信息 的数据结构
// 线段树可以在 𝑂(log⁡𝑁)的时间复杂度内实现单点修改、区间修改、区间查询（区间求和，求区间最大值，求区间最小值）等操作．
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}

const int N = 1e6 + 10;
int n;
ll mod = 998244353;
ll a[N], res;
struct Tree
{
    int l, r;
    ll gcd;
} tree[N * 4];

// tag表示懒标记，ans表示区间信息
// gcd不能懒标记，加法是父节点直接修改+打标记，需要访问子节点在传递信息
// 而gcd需要访问子节点才能修改父节点

// tag[MAXN << 2];

// 线段树的节点数为4倍的原数组长度
// 线段树的节点编号从1开始，左子树为2p，右子树为2p+1

void pushup(int p)
{
    tree[p].gcd = gcd(tree[p << 1].gcd, tree[p << 1 | 1].gcd);
}

void build(int p, int l, int r)
{
    tree[p] = {l, r};
    if (l == r)
    {
        tree[p].gcd = a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(p << 1, l, m), build(p << 1 | 1, m + 1, r);
    pushup(p);
}

ll query(int p, int l, int r)
{
    if (tree[p].l >= l && tree[p].r <= r)
        return tree[p].gcd;
    int m = (tree[p].l + tree[p].r) >> 1;
    ll res = 0;
    if (l <= m)
        res = gcd(res, query(p << 1, l, r)) % mod;
    if (m < r)
        res = gcd(res, query(p << 1 | 1, l, r)) % mod;
    return res % mod;
}
