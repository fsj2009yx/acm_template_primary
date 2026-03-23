#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;

struct Node
{
    int val;
    int key; // 随机优先级
    int l, r;
    int size;
} t[MAXN];

int root, tot;

int newnode(int val)
{
    ++tot;
    t[tot].val = val;
    t[tot].key = rand();
    t[tot].l = t[tot].r = 0;
    t[tot].size = 1;
    return tot;
}

void pushup(int p)
{
    t[p].size = t[t[p].l].size + t[t[p].r].size + 1;
}

void split(int p, int val, int &x, int &y)
{
    if (!p)
    {
        x = y = 0;
        return;
    }
    if (t[p].val <= val)
    {
        x = p;
        split(t[p].r, val, t[p].r, y);
        pushup(p);
    }
    else
    {
        y = p;
        split(t[p].l, val, x, t[p].l);
        pushup(p);
    }
}

int merge(int x, int y)
{
    if (!x || !y)
        return x + y;
    if (t[x].key < t[y].key)
    {
        t[x].r = merge(t[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        t[y].l = merge(x, t[y].l);
        pushup(y);
        return y;
    }
}

void insert(int val)
{
    int x, y;
    split(root, val, x, y);
    root = merge(merge(x, newnode(val)), y);
}

void del(int val)
{
    int x, y, z;
    split(root, val, x, z);
    split(x, val - 1, x, y);
    y = merge(t[y].l, t[y].r);
    root = merge(merge(x, y), z);
}

int get_rank(int val)
{
    int x, y;
    split(root, val - 1, x, y);
    int ans = t[x].size + 1;
    root = merge(x, y);
    return ans;
}

int get_kth(int p, int k)
{
    while (p)
    {
        if (t[t[p].l].size + 1 == k)
            return t[p].val;
        else if (k <= t[t[p].l].size)
            p = t[p].l;
        else
        {
            k -= t[t[p].l].size + 1;
            p = t[p].r;
        }
    }
    return -1;
}

int predecessor(int val)
{
    int x, y;
    split(root, val - 1, x, y);
    int p = x;
    while (t[p].r)
        p = t[p].r;
    int ans = t[p].val;
    root = merge(x, y);
    return ans;
}

int successor(int val)
{
    int x, y;
    split(root, val, x, y);
    int p = y;
    while (t[p].l)
        p = t[p].l;
    int ans = t[p].val;
    root = merge(x, y);
    return ans;
}

int main()
{
    // 使用rand()时一定要先调用srand函数设置随机数种子，否则每次运行程序时生成的随机数序列都是一样的。
    srand(time(NULL));
}