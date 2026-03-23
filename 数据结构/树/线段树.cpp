// 维护 区间信息 的数据结构
// 线段树可以在 𝑂(log⁡𝑁)的时间复杂度内实现单点修改、区间修改、区间查询（区间求和，求区间最大值，求区间最小值）等操作．

#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000001
typedef long long ll;
ll n, m, a[MAXN], ans[MAXN << 2], tag[MAXN << 2]; // 4倍空间
// ans[i]表示线段树节点i的区间信息，tag[i]表示线段树节点i的懒标记
// 求和场景中，实际意义是ans[i]表示线段树节点i的区间和，tag[i]表示线段树节点i的区间增量

// 线段树的节点数为4倍的原数组长度
// 线段树的节点编号从1开始，左子树为2p，右子树为2p+1
inline ll ls(ll x)
{
    return x << 1;
}
// 右子树编号为2p+1
inline ll rs(ll x)
{
    return x << 1 | 1;
}

// 输入
void scan()
{
    cin >> n >> m;
    for (ll i = 1; i <= n; i++)
        cin >> a[i]; // 读入数组
}

// 左右子节点汇集父节点信息
inline void push_up(ll p)
{
    ans[p] = ans[ls(p)] + ans[rs(p)];
}
void build(ll p, ll l, ll r)
{
    tag[p] = 0;
    if (l == r)
    {
        ans[p] = a[l];
        return;
    }
    ll mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    push_up(p);
}
inline void f(ll p, ll l, ll r, ll k)
{
    tag[p] = tag[p] + k;
    // 先修改父节点的区间信息，再打标记，后续访问子节点时传递信息
    ans[p] = ans[p] + k * (r - l + 1);
}

// 向下传递懒标记
inline void push_down(ll p, ll l, ll r)
{
    ll mid = (l + r) >> 1;
    f(ls(p), l, mid, tag[p]);
    f(rs(p), mid + 1, r, tag[p]);
    tag[p] = 0;
}

// 区间修改，增加k
inline void update(ll nl, ll nr, ll l, ll r, ll p, ll k)
{
    if (nl <= l && r <= nr)
    {
        ans[p] += k * (r - l + 1);
        tag[p] += k;
        return;
    }
    push_down(p, l, r);
    ll mid = (l + r) >> 1;
    if (nl <= mid)
        update(nl, nr, l, mid, ls(p), k);
    if (nr > mid)
        update(nl, nr, mid + 1, r, rs(p), k);
    push_up(p);
}

// 区间查询，求区间和
ll query(ll q_x, ll q_y, ll l, ll r, ll p)
{
    ll res = 0;
    if (q_x <= l && r <= q_y)
        return ans[p];
    ll mid = (l + r) >> 1;
    push_down(p, l, r);
    if (q_x <= mid)
        res += query(q_x, q_y, l, mid, ls(p));
    if (q_y > mid)
        res += query(q_x, q_y, mid + 1, r, rs(p));
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll a1, b, c, d, e, f;
    scan();
    build(1, 1, n);
    while (m--)
    {
        cin >> a1; // 1表示修改，2表示查询
        switch (a1)
        {
        case 1:
        {
            cin >> b >> c >> d; // b,c,d分别表示区间的左端点，右端点，修改值
            update(b, c, 1, n, 1, d);
            break;
        }
        case 2:
        {
            cin >> e >> f; // e,f分别表示区间的左端点，右端点
            printf("%lld\n", query(e, f, 1, n, 1));
            break;
        }
        }
    }
    return 0;
}