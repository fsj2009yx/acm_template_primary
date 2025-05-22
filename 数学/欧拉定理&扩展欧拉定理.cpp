#include <bits/stdc++.h>

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// 计算欧拉函数 phi(n)：小于 n 且与 n 互质的正整数个数
int euler_phi(int n)
{
    int res = n;
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            res = res / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        res = res / n * (n - 1); // 如果还有一个大于 sqrt(n) 的质因子
    return res;
}

// 计算 (a^b) % mod
long long qpow(long long a, long long b, long long mod)
{
    long long res = 1;
    a %= mod;
    while (b)
    {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 欧拉定理
//  a 与 mod 互质时，计算 a^b % mod，自动对 b 取模 phi(mod)
long long euler_theorem(long long a, long long b, long long mod)
{
    long long phi_mod = euler_phi(mod);
    return qpow(a, b % phi_mod, mod);
}

//  扩展欧拉定理：支持 a 与 mod 不互质的情况
long long power_extend(long long a, long long b, long long mod)
{
    if (mod == 1)
        return 0;
    int phi_mod = euler_phi(mod);
    if (gcd(a, mod) == 1)
        return qpow(a, b % phi_mod, mod); // 欧拉定理
    else
        return qpow(a, b, mod); // 不互质时不能降幂
}