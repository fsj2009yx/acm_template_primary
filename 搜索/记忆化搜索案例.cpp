/*
  题目链接：https://www.luogu.com.cn/problem/P1057
*/

#include <iostream>
#include <cstring> // 用于初始化数组
using namespace std;

const int MAX_N = 30;
const int MAX_M = 30;

int dp[MAX_N + 1][MAX_M + 1][MAX_M + 1]; // 记忆化数组，用于存储中间结果

// 记忆化搜索函数
int dfs(int current, int steps, int n, int m) {
    // 如果已经传了m次，检查是否回到1号（小蛮）
    if (steps == m) {
        return current == 1 ? 1 : 0;
    }

    // 如果这个状态已经计算过，直接返回结果
    if (dp[current][steps][m] != -1) {
        return dp[current][steps][m];
    }

    // 初始化计数器
    int count = 0;

    // 传给左边的同学 (如果是1号，则左边为n号)
    int left_neighbor = (current == 1) ? n : current - 1;
    count += dfs(left_neighbor, steps + 1, n, m);

    // 传给右边的同学 (如果是n号，则右边为1号)
    int right_neighbor = (current == n) ? 1 : current + 1;
    count += dfs(right_neighbor, steps + 1, n, m);

    // 存储当前状态的结果
    return dp[current][steps][m] = count;
}

int main() {
    int n, m;

    // 输入n个同学，传m次球
    cin >> n >> m;

    // 初始化记忆化数组为-1，表示还没有计算过
    memset(dp, -1, sizeof(dp));

    // 从1号同学（小蛮）开始传球，传了0次球
    int result = dfs(1, 0, n, m);

    // 输出结果
    cout << result << endl;

    return 0;
}
