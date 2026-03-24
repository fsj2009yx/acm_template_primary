#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

// 求区间中位数，本质求第K小

// 维护两个堆，一个大根堆存储较小的一半元素，一个小根堆存储较大的一半元素，使用priority_queue实现

// 注意该代码解决的是在线第K小问题，输入是一个流式输入，每次输入一个数，要求输出当前的中位数
int n;
int a[N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    priority_queue<int> max_heap;                            // 大根堆，存储较小的一半元素
    priority_queue<int, vector<int>, greater<int>> min_heap; // 小根堆

    for (int i = 1; i <= n; i++)
    {
        if (max_heap.empty() || a[i] <= max_heap.top())
            max_heap.push(a[i]);
        else
            min_heap.push(a[i]);

        // 平衡两个堆的大小，使得它们的元素数量相差不超过1
        if (max_heap.size() > min_heap.size() + 1)
        {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
        else if (min_heap.size() > max_heap.size())
        {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }

        // 输出当前的中位数
        if (i & 1)
        {
            if (max_heap.size() >= min_heap.size())
                cout << max_heap.top() << endl;
            else
                cout << min_heap.top() << endl;
        }
    }
}