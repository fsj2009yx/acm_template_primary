#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> P; // 结束时间first 占用算力second
int n, m, h[200005];
priority_queue<P, vector<P>, greater<P>> pq[200005]; // 堆

// 大根堆
priority_queue<int> max_heap; // 大根堆

/*
    greater<P>: 这是一个比较函数对象，用来定义元素之间的排序规则。
    通过使用 greater<P>，我们实际上创建了一个最小堆（minimum heap）
    也就是说，堆顶的元素是最小的元素。如果使用 less<P> 则会形成最大堆（maximum heap）

    vector<P>: 这是底层容器的类型，用来实际存储优先队列中的元素。
    priority_queue 默认使用的底层容器是 vector，你可以在这里指定不同的容器，
    只要该容器支持随机访问迭代器并且提供了必要的操作如 front(), push_back() 和 pop_back() 等

*/

// 这里维护了一个堆数组，每个堆存储了对应一个计算机
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> h[i];
    while (m--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        while (!pq[b].empty() && pq[b].top().first <= a)
        { // 将已完成的任务删除
            h[b] += pq[b].top().second;
            pq[b].pop();
        }
        if (h[b] < d)
            cout << -1 << endl;
        else
        { // 分配
            h[b] -= d;
            pq[b].push(P(a + c, d)); // 注意是结束时间
            // 将任务的结束时间和占用算力放入堆中
            // 堆顶是最小的结束时间，保证了最小的结束时间在前面
            // 保证算力的释放
            cout << h[b] << endl;
        }
    }
    return 0;
}
