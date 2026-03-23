#include <bits/stdc++.h>
using namespace std;

// 划分树常数比主席树更小，查询速度更快
// 支持区间第K小查询，和区间排名
// 但是不支持修改，求和，动态插入，持久化等操作
int read()
{
    int w = 0;
    bool s = 0;
    char c = getchar();
    while (!isdigit(c))
    {
        s = (c == '-');
        c = getchar();
    }
    while (isdigit(c))
    {
        w = w * 10 + c - '0';
        c = getchar();
    }
    return s ? -w : w;
}
const int N = 200005, M = 20;
int n, m;
struct Tree
{
#define mid ((le + ri) >> 1)
#define lson le, mid, dep + 1
#define rson mid + 1, ri, dep + 1
    struct Node
    {
        int num[N], toleft[N];
    };
    Node t[M];
    int sorted[N];
    void build(int le, int ri, int dep)
    {
        if (le == ri)
        {
            return;
        }
        int key = sorted[mid];
        int equ = mid - le + 1;
        for (int i = le; i <= ri; i++)
        {
            if (t[dep].num[i] < key)
            {
                equ--;
            }
        }
        int tl = 0;
        int it1 = le - 1, it2 = mid;
        for (int i = le; i <= ri; i++)
        {
            int now = t[dep].num[i];
            if (now < key || (now == key && equ))
            {
                if (now == key)
                {
                    equ--;
                }
                tl++;
                t[dep + 1].num[++it1] = now;
            }
            else
            {
                t[dep + 1].num[++it2] = now;
            }
            t[dep].toleft[i] = tl;
        }
        build(lson);
        build(rson);
    }
    int query(int le, int ri, int dep, int x, int y, int z)
    {
        if (le == ri)
        {
            return t[dep].num[le];
        }
        int tl = 0, del = t[dep].toleft[y];
        if (le != x)
        {
            tl = t[dep].toleft[x - 1];
            del -= tl;
        }
        int nx, ny;
        if (del >= z)
        {
            nx = le + tl;
            ny = nx + del - 1;
            return query(lson, nx, ny, z);
        }
        else
        {
            nx = mid + 1 + x - tl - le;
            ny = nx + y - x - del;
            return query(rson, nx, ny, z - del);
        }
    }
};
Tree T;
int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
    {
        T.t[0].num[i] = read();
        T.sorted[i] = T.t[0].num[i];
    }
    sort(T.sorted + 1, T.sorted + 1 + n);
    T.build(1, n, 0);
    int x, y, z;
    for (int i = 1; i <= m; i++)
    {
        x = read(), y = read(), z = read();
        int ans = T.query(1, n, 0, x, y, z);
        printf("%d\n", ans);
    }
    return 0;
}