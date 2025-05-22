#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph
{
public:
    // 存储图的边
    struct Edge
    {
        int u, v, weight;
        bool operator<(const Edge &other) const
        {
            return weight < other.weight; // 按边的权重排序
        }
    };

    int V;              // 顶点数
    vector<Edge> edges; // 图的所有边

    // 构造函数，初始化顶点数
    Graph(int V) : V(V) {}

    // 添加边
    void addEdge(int u, int v, int weight)
    {
        edges.push_back({u, v, weight});
    }

    // 并查集查找操作
    int find(int parent[], int i)
    {
        if (parent[i] == -1)
        {
            return i; // 如果当前节点是根节点，返回自己
        }
        return find(parent, parent[i]); // 否则递归查找
    }

    // 并查集合并操作
    void Union(int parent[], int x, int y)
    {
        int xroot = find(parent, x);
        int yroot = find(parent, y);
        if (xroot != yroot)
        {
            parent[xroot] = yroot; // 将一个集合的根节点指向另一个根节点
        }
    }

    // 克鲁斯卡尔算法求最小生成树
    void kruskal()
    {
        vector<Edge> mst; // 最小生成树的边集合

        // 将所有边按权重升序排序
        sort(edges.begin(), edges.end());

        // 初始化并查集
        int parent[V];
        fill(parent, parent + V, -1);

        // 处理所有边
        for (auto &edge : edges)
        {
            int u = edge.u;
            int v = edge.v;

            // 检查是否会形成环
            int set_u = find(parent, u);
            int set_v = find(parent, v);

            // 如果u和v不在同一个集合中，说明不会形成环，可以加入最小生成树
            if (set_u != set_v)
            {
                mst.push_back(edge);
                Union(parent, set_u, set_v);
            }

            // 如果最小生成树已经包含V-1条边，算法结束
            if (mst.size() == V - 1)
                break;
        }

        // 输出最小生成树的边
        cout << "最小生成树的边：\n";
        int totalWeight = 0;
        for (auto &edge : mst)
        {
            cout << edge.u << " - " << edge.v << " 权值: " << edge.weight << endl;
            totalWeight += edge.weight;
        }
        cout << "最小生成树的总权值: " << totalWeight << endl;
    }
};

int main()
{
    Graph g(5);

    // 添加边，表示一个带权无向图
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    // 执行克鲁斯卡尔算法，输出最小生成树
    g.kruskal();

    return 0;
}