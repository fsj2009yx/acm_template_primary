#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define endl '\n'

void solve()
{
    // 离散化
    int ans = 0;
    int n;
    cin >> n;

    vector<int> a;

    a.push_back(-1e9);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        a.push_back(x);
    }
    a.push_back(-1e9);

    auto it = unique(a.begin(), a.end());
    a.erase(it, a.end());

    for (int i = 1; i < a.size() - 1; i++)
    {
        if (a[i] > a[i - 1] && a[i] > a[i + 1])
        {
            ans++;
        }
    }

    cout << ans << endl;
}

int main()
{
#define int long long
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
    {
        /* code */
        solve();
    }
    return 0;
}
