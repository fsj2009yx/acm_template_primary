#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;

int f[MAXN][MAXN], s[MAXN], n, m;

// 链式前向星需要的结构
struct Edge
{
    int v, next;
} e[MAXN];           // 注意这里数组大小要能容纳所有边
int head[MAXN], cnt; // head[i] 表示第 i 个节点的第一条边编号，cnt 全局边计数

// f[i][j] 表示以 i 为根的子树选 j 门课的最大收益

int dfs(int u)
{
    int p = 1;
    // p表示目前已经合并进来的子树节点数
    f[u][1] = s[u];
    for (int i = head[u]; i != 0; i = e[i].next)
    {
        int v = e[i].v;
        int siz = dfs(v);

        // m+1是为了包括虚拟空节点
        for (int i = min(p, m + 1); i; i--)
            // j 表示从当前子树 v 里额外选择的课程数。
            // 范围是 1 ~ siz（v 子树最多 siz 门），并且 i+j 不能超过 m+1（状态空间上限）。
            // 每次尝试把 f[v][j] 合并进 f[u][i]。
            for (int j = 1; j <= siz && i + j <= m + 1; j++)
                f[u][i + j] = max(f[u][i + j], f[u][i] + f[v][j]);
        p += siz;
    }
    return p;
}

// 加边函数
void add_edge(int u, int v)
{
    e[++cnt] = {v, head[u]}; // 新边的 next 指向原来的第一条边
    head[u] = cnt;           // head[u] 指向新加的边
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;

    memset(head, 0, sizeof(head));
    cnt = 0;

    for (int i = 1; i <= n; i++)
    {
        int k;
        cin >> k >> s[i];
        add_edge(k, i); // 建树
    }

    dfs(0);
    cout << f[0][m + 1];
    return 0;
}
