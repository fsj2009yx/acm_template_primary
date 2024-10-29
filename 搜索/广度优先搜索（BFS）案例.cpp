/*
 给定一个无向图，找到从起始节点到目标节点的最短路径。我们将使用一个简单的整数图来演示。

 问题描述：
    给定一个无向图，图的每个节点用整数表示。
    我们需要找到从起始节点 start 到目标节点 target 的最短路径。
    如果路径存在，返回路径长度；如果不存在，返回 -1。
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

// 使用邻接表表示无向图
class Graph {
public:
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> bfs(int start, int target) {
        if (start == target) return { 0 };

        queue<int> que;
        unordered_set<int> visited;
        unordered_map<int, int> distance; // 存储每个节点到起始节点的距离

        que.push(start);
        visited.insert(start);
        distance[start] = 0;

        while (!que.empty()) {
            int node = que.front();
            que.pop();

            for (int neighbor : adj[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    distance[neighbor] = distance[node] + 1;
                    que.push(neighbor);

                    // 如果找到了目标节点，返回距离
                    if (neighbor == target) {
                        return { distance[neighbor] };
                    }
                }
            }
        }

        return { -1 }; // 如果未找到目标节点
    }

private:
    unordered_map<int, vector<int>> adj; // 邻接表
};

int main() {
    Graph graph;

    // 构建图
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(2, 5);

    int start = 1;
    int target = 5;

    vector<int> result = graph.bfs(start, target);

    if (result[0] != -1) {
        cout << "Shortest path length from " << start << " to " << target << " is: " << result[0] << endl;
    }
    else {
        cout << "There is no path from " << start << " to " << target << "." << endl;
    }

    return 0;
}
