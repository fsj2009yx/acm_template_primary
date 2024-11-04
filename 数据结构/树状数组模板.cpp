// https://blog.csdn.net/qq_73792226/article/details/134731712?ops_request_misc=%257B%2522request%255Fid%2522%253A%252282070888-8C0C-4AFE-B5CB-04FAD361CC0D%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=82070888-8C0C-4AFE-B5CB-04FAD361CC0D&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-134731712-null-null.142^v100^pc_search_result_base8&utm_term=%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80&spm=1018.2226.3001.4187
#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 10;
int n, m; // n为数组长度

struct BIT
{
    int c[N] = {0};

    inline int lowbit(int x) { return x & (-x); }
    void add_dandian(int x, int k) // 单点修改，对a[x]加k
    {
        for (int i = x; i <= n; i += lowbit(i))
            c[i] += k; // 树状数组中a[x]的祖先节点都要加k
    }
    int search(int left, int right) // 区间查询,返回区间[left,right]的和
    {
        int ans = 0;
        for (int i = left - 1; i; i -= lowbit(i))
            ans -= c[i];
        for (int i = right; i; i -= lowbit(i))
            ans += c[i];
        return ans;
    }
    void update(int left, int right, int k) // 区间修改，对区间[left,right]加k
    {
        add_dandian(left, k);
        add_dandian(right + 1, -k);
    }
    int query(int x) // 单点查询，返回a[x]的值
    {
        int ans = 0;
        for (int i = x; i; i -= lowbit(i))
            ans += c[i];
        return ans;
    }
};
int main()
{
    cin >> n >> m;
    BIT bit;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        bit.add_dandian(i, x);
    }
    while (m--)
    {
        int x, y, k;
        cin >> x >> y >> k;
        if (x == 1)
        {
            bit.add_dandian(y, k);
        }
        else if (x == 2)
        {
            cout << bit.search(y, k) << '\n';
        }
    }
}