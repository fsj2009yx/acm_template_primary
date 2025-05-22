#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
#define endl '\n'

int M, n;

const long long mod = 1e9 + 7; // 取模的值

struct node
{
    ll m[110][110];
} ans, res;

node mul(node A, node B)
{
    node temp;
    for (int i = 0; i < n; i++)
    { // 初始化为0
        for (int j = 0; j < n; j++)
        {
            temp.m[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    { // 矩阵乘法+取模
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                temp.m[i][j] = (temp.m[i][j] + 1LL * A.m[i][k] * B.m[k][j] % mod) % mod;
            }
        }
    }
    return temp;
}

void quickpower(int M)
{
    // 初始化单位矩阵
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ans.m[i][j] = (i == j ? 1 : 0);
        }
    }

    while (M)
    {
        if (M & 1)
        {
            ans = mul(ans, res);
        }
        res = mul(res, res);
        M >>= 1;
    }
}

int main()
{
    cin >> n >> M;
    for (int i = 0; i < n; i++)
    { // 输入初始矩阵
        for (int j = 0; j < n; j++)
        {
            cin >> res.m[i][j];
        }
    }

    quickpower(M); // 执行矩阵快速幂

    for (int i = 0; i < n; i++)
    { // 输出结果
        for (int j = 0; j < n; j++)
        {
            printf("%d ", ans.m[i][j]);
        }
        printf("\n");
    }
    return 0;
}
