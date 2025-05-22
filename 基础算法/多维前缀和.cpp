#include <bits/stdc++.h>
using namespace std;

int N, A[10000], B[10000];
// 一维前缀和
/*
    可以使用标准库函数 std::partial_sum
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> output(input.size());
    std::partial_sum(input.begin(), input.end(), output.begin());
*/
void partialSum()
{
    // 前缀和数组的第一项和原数组的第一项是相等的。
    B[0] = A[0];

    for (int i = 1; i < N; i++)
    {
        // 前缀和数组的第 i 项 = 原数组的 0 到 i-1 项的和 + 原数组的第 i 项。
        B[i] = B[i - 1] + A[i];
    }

    for (int i = 0; i < N; i++)
    {
        cout << B[i] << " ";
    }
}

// 二维前缀和，以例题最大正方形为例(下面代码只为该题解答，不可直接做板子)
// https://www.luogu.com.cn/problem/P1387
void doublePartialSum()
{
    int n, m;
    cin >> n >> m;

    int a[103][103];
    int b[103][103]; // 前缀和数组，相当于上文的 sum[]
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            b[i][j] =
                b[i][j - 1] + b[i - 1][j] - b[i - 1][j - 1] + a[i][j]; // 求前缀和
        }
    }

    int ans = 0;

    int l = 1;
    while (l <= min(n, m))
    { // 判断条件
        for (int i = l; i <= n; i++)
        {
            for (int j = l; j <= m; j++)
            {
                if (b[i][j] - b[i - l][j] - b[i][j - l] + b[i - l][j - l] == l * l)
                {
                    ans = max(ans, l); // 在这里统计答案
                }
            }
        }
        l++;
    }
    cout << ans << endl;
}

// 三维前缀和
/*
    k维前缀和就等于k次求和。所以，一个显然的算法是，每次只考虑一个维度;
    固定所有其它维度，然后求若干个一维前缀和，
*/
// 代码实现
void threePartialSum()
{
    // 输入三个整数 N1, N2, N3，表示三维数组的尺寸
    int N1, N2, N3;
    std::cin >> N1 >> N2 >> N3;
    // 初始化一个三维数组 a，大小为 (N1+1) x (N2+1) x (N3+1)，用于存储输入数据
    std::vector<std::vector<std::vector<int>>> a(
        N1 + 1, std::vector<std::vector<int>>(N2 + 1, std::vector<int>(N3 + 1)));
    // 输入三维数组的元素
    for (int i = 1; i <= N1; ++i)
        for (int j = 1; j <= N2; ++j)
            for (int k = 1; k <= N3; ++k)
                std::cin >> a[i][j][k];
    // 创建一个三维数组 ps，用于存储前缀和
    auto ps = a;
    // 对于第三维进行前缀和计算
    for (int i = 1; i <= N1; ++i)
        for (int j = 1; j <= N2; ++j)
            for (int k = 1; k <= N3; ++k)
                ps[i][j][k] += ps[i][j][k - 1]; // 将当前元素加上前一个元素
    // 对于第二维进行前缀和计算
    for (int i = 1; i <= N1; ++i)
        for (int j = 1; j <= N2; ++j)
            for (int k = 1; k <= N3; ++k)
                ps[i][j][k] += ps[i][j - 1][k]; // 将当前元素加上前一行的对应元素
    // 对于第一维进行前缀和计算
    for (int i = 1; i <= N1; ++i)
        for (int j = 1; j <= N2; ++j)
            for (int k = 1; k <= N3; ++k)
                ps[i][j][k] += ps[i - 1][j][k]; // 将当前元素加上前一层的对应元素
    // 输出前缀和结果
    for (int i = 1; i <= N1; ++i)
    {
        for (int j = 1; j <= N2; ++j)
        {
            for (int k = 1; k <= N3; ++k)
            {
                std::cout << ps[i][j][k] << ' '; // 输出前缀和
            }
            std::cout << '\n'; // 换行
        }
        std::cout << '\n'; // 每层之间空行
    }
}