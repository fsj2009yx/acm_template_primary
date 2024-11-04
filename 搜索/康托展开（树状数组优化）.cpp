#include <cstdio>
#include <iostream>
using namespace std;
#define int long long
#define lowbit(x) x & -x
#define endl "\n"
const int N = 1e6 + 7;
const int mod = 998244353;
int a[N];
int n, m;
int jc[N];
int tr[N];
void init()
{
    jc[1] = 1;
    for (int i = 2; i <= 1e6; i++)
    {
        jc[i] = jc[i - 1] * i % mod;
    }
}
void add(int x)
{
    for (int i = x; i <= n; i += lowbit(i))
    {
        tr[i] += 1;
    }
}
int query(int x)
{
    int res = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        res += tr[i];
    }
    return res;
}
void contor()
{
    int sum = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        sum = (sum + ((a[i] - 1) - query(a[i] - 1)) * jc[n - i] % mod) % mod;
        add(a[i]);
    }
    // cout << query(4);
    cout << sum << endl;
}

signed main()
{
    init();
    scanf("%d", &n);
    contor();
    return 0;
}