// 当Q次数远小于N时，可以允许单次query的时间复杂度较高，
// 使用分块维护每个块内的数值和排序信息，修改时直接修改边界段和打标记
// 块内查询时直接遍历，块间查询时用二分查找，时间复杂度 O(N√N) 或 O(Q√NlogN)，适合 Q 较小的情况
// 用线段树是更快但是空间复杂度更高的做法，适合 Q 较大的情况

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n, q;
int a[MAXN], t[MAXN];
int belong[MAXN];
int st[2005], ed[2005];
int delta[2005];
int block, num;

void Sort(int k)
{
    for (int i = st[k]; i <= ed[k]; i++)
        t[i] = a[i];
    sort(t + st[k], t + ed[k] + 1);
}

void Modify(int l, int r, int c)
{
    int x = belong[l], y = belong[r];
    if (x == y) // 区间在一个块内就直接修改
    {
        for (int i = l; i <= r; i++)
            a[i] += c;
        Sort(x);
        return;
    }
    for (int i = l; i <= ed[x]; i++)
        a[i] += c; // 直接修改起始段
    for (int i = st[y]; i <= r; i++)
        a[i] += c; // 直接修改结束段
    for (int i = x + 1; i < y; i++)
        delta[i] += c; // 中间的块整体打上标记
    Sort(x);
    Sort(y);
}

int Answer(int l, int r, int c)
{
    int ans = 0, x = belong[l], y = belong[r];
    if (x == y)
    {
        for (int i = l; i <= r; i++)
            if (a[i] + delta[x] >= c)
                ans++;
        return ans;
    }
    for (int i = l; i <= ed[x]; i++)
        if (a[i] + delta[x] >= c)
            ans++;
    for (int i = st[y]; i <= r; i++)
        if (a[i] + delta[y] >= c)
            ans++;
    for (int i = x + 1; i <= y - 1; i++)
        ans +=
            ed[i] - (lower_bound(t + st[i], t + ed[i] + 1, c - delta[i]) - t) + 1;
    // 用 lower_bound 找出中间每一个整块中第一个大于等于 c 的数的位置
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    block = sqrt(n);
    num = (n - 1) / block + 1;

    for (int i = 1; i <= num; i++)
    {
        st[i] = (i - 1) * block + 1;
        ed[i] = min(i * block, n);
        for (int j = st[i]; j <= ed[i]; j++)
            belong[j] = i;
        Sort(i);
    }

    while (q--)
    {
        char op;
        int l, r, x;
        cin >> op >> l >> r >> x;

        if (op == 'M')
            Modify(l, r, x);
        else
            cout << Answer(l, r, x) << "\n";
    }

    return 0;
}