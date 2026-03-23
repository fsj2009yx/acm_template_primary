#include <bits/stdc++.h>
using namespace std;

// 可持久化线段树，也叫主席树，主要用于解决区间 k 大小问题，
// 主要解决 1：区间修改，2：区间查询，3：历史版本查询等问题
// 比如区间第k小，每次修改后都生成一个新的版本，查询时指定版本号即可查询历史版本的区间信息

constexpr int MAXN = 1e5; // 数据范围
int tot, n, m;
int sum[(MAXN << 5) + 10], rt[MAXN + 10], ls[(MAXN << 5) + 10],
    rs[(MAXN << 5) + 10];
int a[MAXN + 10], ind[MAXN + 10], len;

int getid(const int &val)
{ // 离散化
    return lower_bound(ind + 1, ind + len + 1, val) - ind;
}

int build(int l, int r)
{ // 建树
    int root = ++tot;
    if (l == r)
        return root;
    int mid = l + r >> 1;
    ls[root] = build(l, mid);
    rs[root] = build(mid + 1, r);
    return root; // 返回该子树的根节点
}

int update(int k, int l, int r, int root)
{ // 插入操作
    int dir = ++tot;
    ls[dir] = ls[root], rs[dir] = rs[root], sum[dir] = sum[root] + 1;
    if (l == r)
        return dir;
    int mid = l + r >> 1;
    if (k <= mid)
        ls[dir] = update(k, l, mid, ls[dir]);
    else
        rs[dir] = update(k, mid + 1, r, rs[dir]);
    return dir;
}

int query(int u, int v, int l, int r, int k)
{ // 查询操作
    int mid = l + r >> 1,
        x = sum[ls[v]] - sum[ls[u]]; // 通过区间减法得到左儿子中所存储的数值个数
    if (l == r)
        return l;
    if (k <= x) // 若 k 小于等于 x ，则说明第 k 小的数字存储在在左儿子中
        return query(ls[u], ls[v], l, mid, k);
    else // 否则说明在右儿子中
        return query(rs[u], rs[v], mid + 1, r, k - x);
}

void init()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    memcpy(ind, a, sizeof ind);
    sort(ind + 1, ind + n + 1);
    len = unique(ind + 1, ind + n + 1) - ind - 1;
    rt[0] = build(1, len);
    for (int i = 1; i <= n; ++i)
        rt[i] = update(getid(a[i]), 1, len, rt[i - 1]);
}

int l, r, k;

void work()
{
    while (m--)
    {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", ind[query(rt[l - 1], rt[r], 1, len, k)]); // 回答询问
    }
}

int main()
{
    init();
    work();
    return 0;
}