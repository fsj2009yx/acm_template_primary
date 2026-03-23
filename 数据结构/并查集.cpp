#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int fa[N];
int n, m;

// 路径压缩
int find(int x)
{
    if (fa[x] == x)
        return x;
    else
        return fa[x] = find(fa[x]);
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        fa[i] = i; // 初始化
    for (int i = 1; i <= m; ++i)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
        {                             // 合并操作
            x = find(x), y = find(y); // 查询各自的代表元素
            if (x == y)
                continue; // 如果已经在同一个集合，跳过
            fa[x] = y;    // 这里的合并顺序可以任意
        }
        else
        {                             // 查询操作的一种变形
            x = find(x), y = find(y); // 查询各自的代表元素
            if (x == y)
                cout << "Y" << endl; // 是否在同一个集合
            else
                cout << "N" << endl;
        }
    }
    return 0;
}