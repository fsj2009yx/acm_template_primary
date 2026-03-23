#include <bits/stdc++.h>
using namespace std;

// 链式前向星
struct edge
{
    int v, next;
} e[1000010 << 1];

// f[x][0]表示x不选,f[x][1]表示x选

int cnt;
int head[1000010 << 1]; // 邻接表表头
long long n, sz[1000010], dep[1000010];
long long f[1000010];

// head[u]表示节点u的第一条边在e数组中的位置

void addedge(int u, int v, int w = 0)
{ // 建图
    e[++cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

// 换根dp，常见于树形dp中根节点不固定的题目
// 通常需要两次dfs，第一次dfs计算以某节点为根的子树信息，第二次dfs将父节点的信息传递给子节点
void dfs(int u, int fa)
{ // 预处理dfs
    sz[u] = 1;
    dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if (v != fa)
        {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

void get_ans(int u, int fa)
{ // 第二次dfs换根dp
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].v;
        if (v != fa)
        {
            f[v] = f[u] - sz[v] * 2 + n;
            get_ans(v, u);
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }

    dfs(1, 1);
    for (int i = 1; i <= n; i++)
        f[1] += dep[i];
    get_ans(1, 1);
    long long int ans = -1;
    int id;
    for (int i = 1; i <= n; i++)
    {
        if (f[i] > ans)
        {
            ans = f[i];
            id = i;
        }
    }
    cout << id << '\n';
    return 0;
}