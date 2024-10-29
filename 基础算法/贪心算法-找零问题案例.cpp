#include <iostream>
#include <vector>
#include <algorithm> // for sort function

using namespace std;

int minCoins(vector<int>& coins, int amount) {
    // 首先对硬币面值从大到小排序
    sort(coins.rbegin(), coins.rend());

    int count = 0;  // 记录硬币总数
    for (int coin : coins) {
        if (amount == 0) {
            break;
        }
        // 使用尽可能多的当前面值硬币
        count += amount / coin;
        amount %= coin;
    }

    // 如果最终剩余的金额无法凑出，返回 -1
    return (amount == 0) ? count : -1;
}

int main() {
    vector<int> coins = { 1, 5, 10, 25 }; // 定义硬币面值
    int amount = 63; // 要凑出的金额

    int result = minCoins(coins, amount);

    if (result != -1) {
        cout << "最少需要 " << result << " 枚硬币" << endl;
    }
    else {
        cout << "无法凑出该金额" << endl;
    }

    return 0;
}