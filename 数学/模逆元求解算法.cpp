// 模定义下的除法：
/*
    由于模运算的特殊性，它不像普通的除法那样简单。在模
    𝑚
    m 下，除以一个数并不等于直接用这个数去“除”，而是要乘以它的模逆元（modular inverse）。

    （a/b)mod n == (a * b^(-1))mod n
*/

/*
    扩展欧几里得定理：
    ax + by = gcd(a, b)

*/

#include <iostream>
#include <tuple>
typedef long long ll;

// 扩展欧几里得算法
// 返回 gcd(a, b)，并计算出满足 ax + by = gcd(a, b) 的整数 x 和 y
std::tuple<long long, long long, long long> extendedGCD(long long a, long long b)
{
    if (b == 0)
        return {a, 1, 0};
    auto [gcd, x1, y1] = extendedGCD(b, a % b);
    return {gcd, y1, x1 - (a / b) * y1};
}

// 计算 b 在模 m 下的逆元：即求 b^{-1} mod m
// 要求 gcd(b, m) == 1
long long modInverse(long long b, long long m)
{
    auto [gcd, x, _] = extendedGCD(b, m);
    if (gcd != 1)
    {
        throw std::invalid_argument("Inverse does not exist (b and m are not coprime)");
    }
    // 保证结果是正数
    return (x % m + m) % m;
}

// 示例用法
int main()
{
    long long b = 3;
    long long m = 7;
    try
    {
        long long inverse = modInverse(b, m);
        std::cout << "The modular inverse of " << b << " mod " << m << " is " << inverse << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

// 费马小定理：
/*
    如果 p 是质数，a 是整数，且 a 和 p 互质，则有：
    a^(p-1) ≡ 1 (mod p)
    这意味着 a^(p-2) ≡ a^(-1) (mod p)，即 a 的模逆元可以通过 a^(p-2) 来计算。
    这在计算机科学中非常有用，尤其是在处理大数时。
*/

// 多数情况下mod为质数，所以使用费马小定理计算模逆元更高效。

ll qpow(ll base, ll exp, ll mod)
{
    ll res = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp & 1)
            res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// 计算 a 在模 mod 下的乘法逆元（mod 必须是质数）
ll modInverse(ll a, ll mod)
{
    return qpow(a, mod - 2, mod);
}

// 线性求模逆元：
/*
    针对求一连串数字对于一个modp的逆元，
    可以使用线性求模逆元的方法来提高效率。

    https://www.luogu.com.cn/problem/solution/P3811

*/

inv[1] = 1;
for (int i = 2; i < p; ++i)
    inv[i] = (p - p / i) * inv[p % i] % p;