#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>

using namespace std;

// 定义表示图的邻接表结构
typedef pair<int, int> Edge; // first: 边的权重, second: 相邻顶点
typedef vector<vector<Edge>> Graph;

// Prim 算法，返回最小生成树的总权值
int prim(const Graph &graph)
{
    int totalWeight = 0;
    vector<bool> visited(graph.size(), false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap;

    // 从第一个顶点开始
    minHeap.push({0, 0});

    while (!minHeap.empty())
    {
        auto [weight, u] = minHeap.top();
        minHeap.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        totalWeight += weight;

        for (const auto &[nextWeight, v] : graph[u])
        {
            if (!visited[v])
            {
                minHeap.push({nextWeight, v});
            }
        }
    }

    return totalWeight;
}

int main()
{
    // 示例图的邻接表表示
    Graph graph = {
        {{1, 1}, {3, 2}},         // 顶点 0 的邻接边
        {{1, 0}, {2, 2}, {4, 3}}, // 顶点 1 的邻接边
        {{3, 0}, {2, 1}, {5, 3}}, // 顶点 2 的邻接边
        {{4, 1}, {5, 2}}          // 顶点 3 的邻接边
    };

    int totalWeight = prim(graph);
    cout << "最小生成树的总权值: " << totalWeight << endl;

    return 0;
}
