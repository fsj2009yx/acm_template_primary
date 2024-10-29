long long fastPowerMod(long long base, long long exp, long long mod) 
{
    long long result = 1;
    base = base % mod;  // 防止 base 超过 mod

    while (exp) {
        // 如果 exp 是奇数，则将当前 base 乘入结果
        if (exp & 1) {
            result = (result * base) % mod;
        }
        // 平方 base
        base = (base * base) % mod;
        // exp 右移一位，相当于 exp = exp // 2
        exp >>= 1;
    }

    return result;
}