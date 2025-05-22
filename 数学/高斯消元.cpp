#include <bits/stdc++.h>
using namespace std;

// 定义常量 N 为最大变量数，eps 为判断浮点数等于 0 的误差范围
const int N = 105;
double a[N][N]; // 系数矩阵（增广矩阵）
double x[N];    // 解向量
double eps = 1e-6;

// 高斯消元主函数，n 个方程，m 个变量
int solve(int n, int m)
{
    int c = 0; // 当前处理的列
    int r;     // 当前处理的行
    for (r = 0; r < n && c < m; r++, c++)
    {
        // 找到当前列中绝对值最大的行，用于主元选择
        int maxr = r;
        for (int i = r + 1; i < n; i++)
        {
            if (abs(a[i][c]) > abs(a[maxr][c]))
                maxr = i;
        }

        // 将最大值所在行与当前行交换
        if (maxr != r)
            swap(a[r], a[maxr]);

        // 如果主元接近于0，跳过该列（代表可能是自由变量）
        if (fabs(a[r][c]) < eps)
        {
            r--;
            continue;
        }

        // 消元：将下面所有行第 c 列消为 0
        for (int i = r + 1; i < n; i++)
        {
            if (fabs(a[i][c]) > eps)
            {
                double k = a[i][c] / a[r][c]; // 计算消元因子
                for (int j = c; j <= m; j++)  // 注意：j要到m，包括常数项
                    a[i][j] -= a[r][j] * k;
                a[i][c] = 0; // 强制设为0避免精度误差
            }
        }
    }

    // 检查是否存在矛盾（例如：0x + 0y + 0z = 非0）
    for (int i = r; i < n; i++)
    {
        if (fabs(a[i][m]) > eps)
            return -1; // 无解
    }

    // 若不满秩，存在自由变量（无穷多解）
    if (r < m)
        return m - r; // 返回自由元个数

    // 回代求解
    for (int i = m - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < m; j++)
            a[i][m] -= a[i][j] * x[j];
        x[i] = a[i][m] / a[i][i];
    }

    return 0; // 有唯一解
}

int main()
{
    int n;
    cin >> n; // 输入方程个数

    // 输入增广矩阵（系数 + 常数项）
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cin >> a[i][j];
        }
    }

    int pan = solve(n, n); // 求解

    // 根据返回值判断解的情况
    if (pan != 0)
    {
        cout << "No Solution";
        return 0;
    }

    // 输出唯一解（保留两位小数）
    for (int i = 0; i < n; i++)
    {
        printf("%.2lf\n", x[i]);
    }
}
