#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAXN = 100005;

struct Edge
{
    int to, nxt;
};

int head[MAXN], tot;
Edge e[MAXN * 2];
int node_size[MAXN]; // 节点的子树大小（包括节点本身）
int weight[MAXN];    // 节点的重量，即所有子树大小的最大值
int centroid[2];     // 用于记录树的重心（存的是节点编号）
int n;               // 节点总数

void addEdge(int u, int v)
{
    e[tot] = {v, head[u]};
    head[u] = tot++;
}

// 求树的重心

void GetCentroid(int cur, int fa)
{
    node_size[cur] = 1;
    weight[cur] = 0;
    for (int i = head[cur]; i != -1; i = e[i].nxt)
    {
        int to = e[i].to;
        if (to != fa)
        {
            GetCentroid(to, cur);
            node_size[cur] += node_size[to];
            weight[cur] = max(weight[cur], node_size[to]);
        }
    }
    weight[cur] = max(weight[cur], n - node_size[cur]);
    if (weight[cur] <= n / 2)
    {
        centroid[centroid[0] != 0] = cur;
    }
}

// 计算距离和

long long ComputeDistanceSum(int cur, int fa, int depth)
{
    long long sum = depth;
    for (int i = head[cur]; i != -1; i = e[i].nxt)
    {
        int to = e[i].to;
        if (to != fa)
        {
            sum += ComputeDistanceSum(to, cur, depth + 1);
        }
    }
    return sum;
}

int main()
{
    memset(head, -1, sizeof(head));
    tot = 0;
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    centroid[0] = centroid[1] = 0;
    GetCentroid(1, -1);
    ll sum1 = ComputeDistanceSum(centroid[0], -1, 0);
    if (centroid[1] == 0)
    {
        cout << "Centroid: " << centroid[0] << endl;
        cout << "Distance sum: " << sum1 << endl;
    }
    else
    {
        cout << "Centroids: " << centroid[0] << " and " << centroid[1] << endl;
        cout << "Distance sum: " << min(sum1, ComputeDistanceSum(centroid[1], -1, 0)) << endl;
    }
    return 0;
}
