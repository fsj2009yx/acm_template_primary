#include <iostream>
#include <vector>
using namespace std;

// 差分数组结构体
struct DifferenceArray {
    vector<int> diff; // 差分数组
    int n;           // 数组大小

    // 构造函数，初始化差分数组
    DifferenceArray(int size) : n(size) {
        diff.resize(n + 1, 0); // 比原有数组多一位用于处理边界
    }

    // 更新区间 [left, right] 的值
    void update(int left, int right, int value) {
        diff[left] += value; // 在左边界加上值
        if (right + 1 < n) {
            diff[right + 1] -= value; // 在右边界的下一个位置减去值
        }
    }

    // 获取最终数组
    vector<int> result() {
        vector<int> arr(n);
        arr[0] = diff[0]; // 第一个元素

        // 根据差分数组计算最终数组
        for (int i = 1; i < n; ++i) {
            arr[i] = arr[i - 1] + diff[i]; // 当前值等于前一个值加上差分值
        }

        return arr; // 返回计算后的数组
    }
};

int main() {
    int n = 10; // 数组大小
    DifferenceArray da(n); // 创建差分数组对象

    // 示例：更新多个区间
    da.update(2, 5, 3); // 区间 [2, 5] 增加 3
    da.update(3, 7, 2); // 区间 [3, 7] 增加 2
    da.update(0, 4, 1); // 区间 [0, 4] 增加 1

    // 获取最终数组
    vector<int> result = da.result();

    // 输出结果
    for (int val : result) {
        cout << val << " "; // 打印数组元素
    }
    cout << endl;

    return 0;
}