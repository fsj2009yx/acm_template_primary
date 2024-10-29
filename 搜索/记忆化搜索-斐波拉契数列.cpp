#include <iostream>
#include <vector>

using namespace std;
/*
    记忆化搜索通过使用一个额外的数据结构（如数组或哈希表）来存储已经计算过的结果。
    在递归调用时，首先检查是否已有计算结果，如果有则直接返回，减少递归深度。
*/
// 记忆化数组
vector<int> memo;

// 递归函数，计算 Fibonacci 数
int fibonacci(int n) 
{
    // 如果已计算，直接返回结果
    if (memo[n] != -1) 
    {
        return memo[n];
    }
    // 基本情况
    if (n <= 1)
    {
        return n;
    }
    // 递归计算并存储结果
    memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return memo[n];
}

int main() {
    int n;
    cout << "请输入 n (计算第 n 个斐波那契数): ";
    cin >> n;

    // 初始化记忆化数组
    memo.resize(n + 1, -1);

    // 计算并输出结果
    cout << "Fibonacci(" << n << ") = " << fibonacci(n) << endl;

    return 0;
}
