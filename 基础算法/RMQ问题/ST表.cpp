// 用于RMQ问题，即在一个数组中，给定两个下标L和R，求出L到R之间的最小、最大值
// ST表可以做到 \Theta(n\log n) 预处理，\Theta(1) 回答每个询问
// ST 表：用于快速处理静态区间最大值查询（RMQ）
// 时间复杂度：预处理 O(n log n)，查询 O(1)

#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5; // 最大数据范围
const int logN = 17;      // log2(MAXN) 向上取整即可（2^17 ≈ 131072）

int f[MAXN][logN + 1]; // ST 表：f[i][j] 表示区间 [i, i + 2^j - 1] 的最大值
int Logn[MAXN];        // 预处理 log 值：Logn[i] = floor(log2(i))

void pre()
{ // 预处理 Logn 数组，计算所有 1~MAXN 的 log2 值
    Logn[1] = 0;
    Logn[2] = 1;
    for (int i = 3; i < MAXN; i++)
    {
        Logn[i] = Logn[i >> 1] + 1; // 利用性质 log2(i) = log2(i/2) + 1
    }
}

int main()
{
    ios::sync_with_stdio(false); // 提高输入输出效率
    cin.tie(nullptr);            // 取消 cin 与 cout 的绑定

    int n, m;
    cin >> n >> m; // 输入数组长度 n 和查询次数 m

    for (int i = 1; i <= n; i++)
        cin >> f[i][0]; // 输入原始数组，作为 ST 表第 0 层（长度为 2^0=1 的区间）

    pre(); // 初始化 Logn 数组

    // 构建 ST 表：每一层 j 表示区间长度为 2^j
    for (int j = 1; j <= logN; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            // 区间 [i, i+2^j-1] 的最大值 = max([i, i+2^{j-1}-1], [i+2^{j-1}, i+2^j-1])
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);

    // 查询 m 次
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;           // 查询区间 [x, y]
        int s = Logn[y - x + 1]; // 区间长度对应的最大 2^s，使得 2^s <= y - x + 1
        // 利用两个长度为 2^s 的区间拼出原区间：[x, x+2^s-1] 和 [y-2^s+1, y]
        cout << max(f[x][s], f[y - (1 << s) + 1][s]) << '\n';
    }

    return 0;
}
