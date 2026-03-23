// 链式前向星是常用存图方式之一
// 下面的例子是求树上两点的最近公共祖先（LCA）问题，使用倍增算法实现

#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int LOG = 20;

struct Edge
{
    int to;
    int next;
} edge[N * 2];

int head[N];
int cnt;

int depth[N];
int fa[N][LOG];

void addEdge(int u, int v)
{
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void dfs(int u, int father)
{
    fa[u][0] = father;
    depth[u] = depth[father] + 1;

    for (int k = 1; k < LOG; k++)
        fa[u][k] = fa[fa[u][k - 1]][k - 1];

    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == father)
            continue;

        dfs(v, u);
    }
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);

    for (int k = LOG - 1; k >= 0; k--)
        if (depth[u] - (1 << k) >= depth[v])
            u = fa[u][k];

    if (u == v)
        return u;

    for (int k = LOG - 1; k >= 0; k--)
    {
        if (fa[u][k] != fa[v][k])
        {
            u = fa[u][k];
            v = fa[v][k];
        }
    }

    return fa[u][0];
}

int main()
{
    int n, m, root;
    cin >> n >> m >> root;

    memset(head, -1, sizeof(head));

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        addEdge(u, v);
        addEdge(v, u);
    }

    dfs(root, 0);

    while (m--)
    {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
}