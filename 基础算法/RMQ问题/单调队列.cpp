// https://www.luogu.com.cn/problem/P1886
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'

// 滑动窗口/单调队列
// 维护一个单调队列，求区间最大值和最小值
struct Monotone_queue
{
    static const int maxn = 1000001;
    int n, k, a[maxn];
    int q[maxn], head, tail, p[maxn];

    void read()
    {
        cin >> n >> k;
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
    }

    void monotone_max() // 单调最大值
    {
        head = 1;
        tail = 0;
        for (int i = 1; i <= n; ++i)
        {
            while (head <= tail && q[tail] <= a[i])
                tail--;
            q[++tail] = a[i];
            p[tail] = i;
            while (p[head] <= i - k)
                head++;
            if (i >= k)
                cout << q[head] << " ";
        }
        cout << endl;
    }

    void monotone_min()
    {
        head = 1;
        tail = 0;
        // head要严格对应首元素，tail要严格对应尾元素，所以当tail >= head时，说明有元素。而一开始队列为空，说一要这样赋值
        for (int i = 1; i <= n; ++i)
        {
            while (head <= tail && q[tail] >= a[i]) // 队内有元素且队尾元素大于等于当前元素，说明队尾元素不可能成为最小值了
                tail--;                             // 出队
            // 清理结束后，当前元素入队
            q[++tail] = a[i];
            // 队尾对应的原数列的下标
            p[tail] = i;
            cout << "head: " << head << " tail: " << tail << endl;
            cout << "head_num: " << q[head] << " tail_num: " << q[tail] << endl;
            while (p[head] <= i - k)
                head++; // 如果队头元素的下标小于等于当前元素的下标减去k，说明队头元素不在当前窗口内了，队头出队
            if (i >= k)
                cout << q[head] << " ";
        }
        cout << endl;
    }
} worker;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    worker.read();
    worker.monotone_min();
    return 0;
}