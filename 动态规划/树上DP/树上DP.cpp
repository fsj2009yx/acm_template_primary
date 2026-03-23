#include <bits/stdc++.h>
using namespace std;

// 链式前向星
struct edge
{
    int v, next;
} e[6005];

// f[x][0]表示x不选,f[x][1]表示x选

int n, cnt, ans;
int head[6005]; // 邻接表表头
int f[6005][2]; // DP数组: f[x][0], f[x][1]
int vis[6005];  // 标记是否访问过
int is_h[6005]; // 标记某节点是否是别人的孩子

// head[u]表示节点u的第一条边在e数组中的位置

void addedge(int u, int v)
{ // 建图
    e[++cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

void calc(int k)
{
    vis[k] = 1;
    for (int i = head[k]; i; i = e[i].next)
    { // 枚举该结点的每个子结点
        if (vis[e[i].v])
            continue;
        calc(e[i].v);
        f[k][1] += f[e[i].v][0];
        f[k][0] += max(f[e[i].v][0], f[e[i].v][1]); // 转移方程
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> f[i][1];
    for (int i = 1; i < n; i++)
    {
        int l, k;
        cin >> l >> k;
        is_h[l] = 1;
        addedge(k, l);
    }
    for (int i = 1; i <= n; i++)
        // 这里一直找到根结点，直到找到一个不是别人的孩子的节点，才比较
        // 由于题目中说了只有一个根节点，所以找到第一个不是别人的孩子的节点就行
        if (!is_h[i])
        { // 从根结点开始DFS
            calc(i);
            cout << max(f[i][1], f[i][0]);
            return 0;
        }
}