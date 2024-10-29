#include <iostream>
#include <vector>

struct MergeSort {
    // 主排序函数
    void sort(std::vector<int>& arr) {
        if (!arr.empty()) {
            mergeSort(arr, 0, arr.size() - 1);
        }
    }

private:
    // 合并两个已排序的子数组
    void merge(std::vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1; // 左子数组的大小
        int n2 = right - mid;    // 右子数组的大小

        std::vector<int> L(n1);  // 创建左子数组
        std::vector<int> R(n2);  // 创建右子数组

        // 将数据拷贝到临时数组 L[] 和 R[]
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        // 合并临时数组
        int i = 0; // 初始索引 L
        int j = 0; // 初始索引 R
        int k = left; // 初始索引合并后的数组

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        // 复制 L[] 中剩余的元素
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        // 复制 R[] 中剩余的元素
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    // 归并排序函数
    void mergeSort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            // 递归排序左右半部分
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            // 合并已排序的部分
            merge(arr, left, mid, right);
        }
    }
};

// 主函数
int main() {
    std::vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    std::cout << "原数组: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    MergeSort sorter;
    sorter.sort(arr); // 调用排序函数

    std::cout << "排序后的数组: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
