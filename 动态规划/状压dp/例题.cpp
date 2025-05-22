// https://loj.ac/p/2153
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

// n: 棋盘行数（也是列数）
// K: 要放置的国王总数
int n, K;

// 状态：表示一行上国王的放置情况

// 每个 sti[i] 是一种合法的一行国王放置方式
int sti[600], sta[600], cnt;

// f[i][l][j]: 摆到第 i 行，已放 l 个国王，且第 i 行的状态为 j 编号，对应的合法方案数
long long f[10][85][600];

// dfs 预处理一行中所有合法的放法（不相邻的放国王方式）
void dfs(int x, int num, int cur)
{
    if (cur >= n)
    {
        // 当前状态完成，存入状态数组
        sti[++cnt] = x; // 记录当前状态的掩码
        sta[cnt] = num; // 记录当前状态放了多少个国王
        return;
    }

    // ① 当前格放国王，则跳过下一个位置（cur + 2）
    dfs(x | (1 << cur), num + 1, cur + 2);

    // ② 当前格不放国王，继续下一个格子（cur + 1）
    dfs(x, num, cur + 1);
}

int main()
{
    // 读取棋盘大小和国王数量
    cin >> n >> K;

    // 预处理一行中所有合法的状态
    dfs(0, 0, 0);

    // 初始化第一行的状态
    // f[1][sta[i]][i] = 1 表示第一行选择第 i 个状态，并放了 sta[i] 个国王，方案为 1 种
    for (int i = 1; i <= cnt; i++)
        f[1][sta[i]][i] = 1;

    // 开始进行动态规划
    for (int i = 2; i <= n; i++)               // 遍历每一行（从第2行开始）
        for (int j = 1; j <= cnt; j++)         // 当前行使用第 j 个状态
            for (int k = K; k >= sta[j]; k--)  // 总共已放 k 个国王，至少要容得下当前状态的国王数
                for (int x = 1; x <= cnt; x++) // 枚举上一行的所有状态 x
                    // 检查状态 j（当前行）与状态 x（上一行）之间是否冲突
                    if (
                        !(sti[j] & sti[x]) &&        // 同一列不能同时放国王
                        !((sti[j] << 1) & sti[x]) && // 左上与右下不能同时放（对角线冲突）
                        !((sti[j] >> 1) & sti[x])    // 右上与左下不能同时放（对角线冲突）
                    )
                        // 状态合法，累加方案数
                        f[i][k][j] += f[i - 1][k - sta[j]][x];

    // 最终统计所有在第 n 行，放置了 K 个国王的所有合法状态的总和
    long long sum = 0;
    for (int j = 1; j <= cnt; j++)
        sum += f[n][K][j];

    // 输出最终答案
    cout << sum;

    return 0;
}
