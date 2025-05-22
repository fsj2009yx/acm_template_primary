// 如果令f[n]表示从1到n区间内数组的最大子数组和
//  f[n] = max(f[n-1]+a[n],a[n])

/*
    如果只取最大，只需要两个变量来存储当前的最大值和当前的子数组和即可

Kadane’s 算法思想：
遍历数组的每个元素，不断维护两个变量：
    curr_sum：以当前元素结尾的最大子数组和
    max_sum：全局最大子数组和

每一步：
    curr_sum = max(a[i], curr_sum + a[i]);
    max_sum = max(max_sum, curr_sum);
含义：
    curr_sum + a[i]：表示把当前元素加入当前子数组
    a[i]：重新开始一个新的子数组
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    ll max_sum = a[1], curr_sum = a[1];
    for (int i = 2; i <= n; i++)
    {
        curr_sum = max(a[i], curr_sum + a[i]);
        max_sum = max(max_sum, curr_sum);
    }

    cout << max_sum << endl;
    return 0;
}