//
// Created by Giperx on 2022/11/27.
//
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
#define INFINE 99999 // 定义最大
// 邻接表
struct ArcNode // 边信息
{
    int adjvex;           // 有向边的 目标顶点 下标（从1开始）
    int weight;           // 边的权值
    struct ArcNode *next; // 邻接表，指向下一个邻接边信息
};

struct VertexNode // 顶点
{
    int vertex;         // 顶点下标（1 ~）
    ArcNode *firstedge; // 有向边信息节点指针（源为vertex）
};

struct AdjList // 图
{
    vector<VertexNode> adjlist; // 顶点数组
    int vexnum;                 // 顶点数　
    int arcnum;                 // 边数
};

// 图的初始化
void createGraph(AdjList &G)
{
    cout << "输入顶点数 边数：" << endl;
    cin >> G.vexnum >> G.arcnum;
    // 初始化G的顶点数组
    for (int i = 0; i <= G.vexnum; i++)
    { // 下标从1开始，所以初始化vexnum + 1个顶点（0无作用）
        VertexNode *tmp = new VertexNode;
        tmp->vertex = i, tmp->firstedge = nullptr;
        G.adjlist.emplace_back(*tmp);
    }
    // 边信息
    //  n1:源顶点     n2:目标顶点   we:权重（距离）
    int n1, n2, we;
    cout << "输入边信息：（a b we）：" << endl; // a -> b  weight: we
    for (int i = 0; i < G.arcnum; i++)
    {
        cin >> n1 >> n2 >> we;
        // 初始化一个边节点，目标顶点为n2
        ArcNode *tmp = new ArcNode;
        tmp->adjvex = n2, tmp->weight = we;
        // 头插法 将边信息节点插入
        // 节约时间（尾插要一直遍历到尾部插入）
        tmp->next = G.adjlist[n1].firstedge;
        G.adjlist[n1].firstedge = tmp;
    }
}

// 获取两顶点之间权重weight（距离）
int getWeight(AdjList &G, int n1, int n2)
{
    if (n1 == n2)
        return 0;

    ArcNode *tmp = G.adjlist[n1].firstedge;
    while (tmp)
    {
        if (tmp->adjvex == n2)
            return tmp->weight;
        tmp = tmp->next;
    }
    // 两点之间没有边，返回INFINE
    return INFINE;
}

// 迪杰斯特拉算法（朴素）
// G={V,E}   V：点集合   E:边集合
// 初始化时 令 S={某源点ear}, T=V-S= {其余顶点}，T中顶点对应的距离（ear， Vi）值
//          若存在，d(ear,Vi)为弧上的权值， dist【i】
//          若不存在，d(ear,Vi)为 无穷大， dist【i】
// 循环 n - 1次（n个点）：
//  从T中选取一个与S中顶点 有关联边 且 权值最小 的顶点 pos，加入到 S中
//      (这里使用 flag数组来确定 是否属于 S集合，true为属于）
//      (等于是 每次 选取 T点集中 dist最小的顶点 作为 pos 加入 S，既 flag置为 true)
//  对其余T中顶点Vi的距离值进行修改：若加进 pos 作中间顶点，从ear -> pos -> Vi 的距离值缩短，则 更新dist
//      (等于是 找出所有 pos -> Vi 边（有边连接的）， 再加上原来源ear -> pos 权重，
//      对比dist数组，如果权重更小则更新 => 更新dist最短路径长度，更新prev数组 更新前驱顶点为pos)
void Dijkstra(AdjList &G, int ear, vector<int> &prev, vector<int> &dist)
{
    // 初始化
    // flag数组记录 某点是否纳入已找到点集合
    // prev数组记录 前驱顶点下标
    // dist数组记录 从源顶点ear 到 i顶点的最短路径
    vector<bool> flag(G.adjlist.size() + 1, false);
    for (int i = 1; i <= G.vexnum; i++)
        dist[i] = getWeight(G, ear, i), prev[i] = ear;
    flag[ear] = true, prev[ear] = 0;
    // 开始
    for (int i = 2; i <= G.vexnum; i++)
    {
        int pos = 1; // 未纳入的距离最小的顶点
        int weiMin = INFINE;
        for (int j = 1; j <= G.vexnum; j++)
        {
            if (!flag[j] && dist[j] < weiMin)
            {
                weiMin = dist[j], pos = j;
            }
        }

        flag[pos] = true;
        for (int j = 1; j <= G.vexnum; j++)
        {
            if (!flag[j])
            { // 未纳入点集中，找到pos到这些点的距离，与dist数组比较是否更新
                int tmpWei = getWeight(G, pos, j);
                if (tmpWei != INFINE)
                    tmpWei = tmpWei + weiMin; // 两点距离应该为ear -> pos -> j
                if (tmpWei < dist[j])
                {
                    dist[j] = tmpWei; // 距离更小则更新dist
                    prev[j] = pos;    // 前顶点更新为pos
                }
            }
        }
    }
}

// 找路径
void pathDist(vector<int> &prev, vector<int> &dist, int ear)
{
    // prev数组中为1有2种情况（djikstra初始化过程的时候全赋值为1，后续一直未改变）：
    // 1：从ear到 顶点 只有 ear -> 顶点 这一条路最短
    // 2：无法从ear到达的顶点
    for (int i = 1; i <= prev.size() - 1; i++)
    {
        stack<int> trace;
        if (ear == i)
            continue;
        cout << ear << " 到 " << i;
        // 无连通
        if (dist[i] == INFINE)
        {
            cout << "无连通" << endl;
            continue;
        }
        cout << "最短距离：" << dist[i] << "  最短路径：";
        int tmp = i;
        while (tmp)
        { //  源顶点prev是0
            trace.push(tmp);
            tmp = prev[tmp];
        }
        // 开始出栈, 栈顶一定是ear源顶点
        cout << trace.top();
        trace.pop();
        while (!trace.empty())
        {
            cout << " -> " << trace.top();
            trace.pop();
        }
        cout << endl;
    }
}
int main()
{
    AdjList G;
    createGraph(G);
    // prev数组记录 前驱顶点下标
    vector<int> prev(G.vexnum + 1, 0);
    // dist数组记录 从源顶点ear 到 i顶点的最短路径
    vector<int> dist(G.vexnum + 1, INFINE);
    // 从源点ear 出发，到达其余所有点的最短路径
    cout << "输入源顶点ear：";
    int ear;
    cin >> ear;
    Dijkstra(G, ear, prev, dist);
    pathDist(prev, dist, ear);
    //    for(int &x:prev) cout << x << ' ';
    //    for(int &x:dist) cout << x << ' ';
    return 0;
}