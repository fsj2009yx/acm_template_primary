#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

// 扩展欧几里得算法，用于求解 ax + by = gcd(a, b)
// 同时返回 gcd(a, b) 和系数 x, y
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1; // 当 b 为 0 时，gcd(a, b) = a，此时 x = 1, y = 0
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x); // 递归调用
    y -= (a / b) * x;             // 更新 y 的值
    return d;
}

// 计算 a 在模 m 下的乘法逆元，即求满足 a * x ≡ 1 (mod m) 的 x
ll mod_inverse(ll a, ll m)
{
    ll x, y;
    ll g = exgcd(a, m, x, y);
    if (g != 1)
    {
        // 如果 a 和 m 不互质，则逆元不存在
        return -1;
    }
    else
    {
        // 保证结果为正整数
        return (x % m + m) % m;
    }
}

// 中国剩余定理主函数，返回最小的正整数解
ll CRT(const vector<ll> &a, const vector<ll> &b)
{
    ll M = 1; // 所有模数的乘积
    for (ll ai : a)
    {
        M *= ai;
    }

    ll result = 0;
    for (size_t i = 0; i < a.size(); ++i)
    {
        ll Mi = M / a[i];               // 计算 M_i
        ll inv = mod_inverse(Mi, a[i]); // 计算 M_i 在模 a[i] 下的逆元
        if (inv == -1)
        {
            // 如果逆元不存在，说明输入不符合要求
            return -1;
        }
        result = (result + b[i] * Mi % M * inv % M) % M;
    }

    // 保证结果为正整数
    return (result + M) % M;
}

int main()
{
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i] >> b[i]; // 输入模数和对应的余数
    }

    ll ans = CRT(a, b);
    if (ans == -1)
    {
        cout << "无解" << endl;
    }
    else
    {
        cout << ans << endl;
    }

    return 0;
}
