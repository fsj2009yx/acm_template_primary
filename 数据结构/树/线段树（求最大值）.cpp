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
    // n,m对应M和D
    cin >> n >> m;
}

// 左右子节点汇集父节点信息
inline void push_up(ll p)
{
    ans[p] = max(ans[ls(p)], ans[rs(p)]);
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

// p表示当前节点编号，l,r表示当前节点维护的区间，k表示要增加的值
inline void f(ll p, ll l, ll r, ll k)
{
    tag[p] = tag[p] + k;
    // 先修改父节点的区间信息，再打标记，后续访问子节点时传递信息
    ans[p] += k;
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
// nl,nr表示要修改的区间，l,r表示当前节点维护的区间，p表示当前节点编号，k表示要增加的值
inline void update(ll nl, ll nr, ll l, ll r, ll p, ll k)
{
    if (nl <= l && r <= nr)
    {
        ans[p] += k;
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

// 单点修改，修改位置pos的值为val
// pos表示要修改的位置，val表示要修改的值，l,r表示当前节点维护的区间，p表示当前节点编号
inline void update_single(ll pos, ll val, ll l, ll r, ll p)
{
    if (l == r)
    {
        ans[p] = val;
        return;
    }
    ll mid = (l + r) >> 1;
    if (pos <= mid)
        update_single(pos, val, l, mid, ls(p));
    else
        update_single(pos, val, mid + 1, r, rs(p));
    push_up(p);
}

// 区间查询，求区间和

// q_x,q_y表示要查询的区间，l,r表示当前节点维护的区间，p表示当前节点编号
ll query(ll q_x, ll q_y, ll l, ll r, ll p)
{
    ll res = 0;
    if (q_x <= l && r <= q_y)
        return ans[p];
    ll mid = (l + r) >> 1;
    push_down(p, l, r);
    if (q_x <= mid)
        res = max(res, query(q_x, q_y, l, mid, ls(p)));
    if (q_y > mid)
        res = max(res, query(q_x, q_y, mid + 1, r, rs(p)));
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    char op;
    ll b, last_ans = 0, c, d, L, f;
    ll lens = 0; // 持续增长的数组长度
    scan();
    build(1, 1, n);

    int count = n;
    while (count--)
    {
        cin >> op;
        switch (op)
        {
        case 'A':
        {
            cin >> b; // 要插入的数
            lens++;
            update_single(lens, (b + last_ans) % m, 1, n, 1);
            break;
        }
        case 'Q':
        {
            // 即L
            cin >> L;
            f = lens - min(lens, L) + 1; // 即R
            last_ans = query(f, lens, 1, n, 1);
            printf("%lld\n", last_ans);
            break;
        }
        }
    }
    return 0;
}