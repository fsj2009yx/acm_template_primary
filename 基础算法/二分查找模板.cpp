#include <bits/stdc++.h>
using namespace std;
int binarySearch(vector<int> &arr, int left, int right, int target)
{
    int mid;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid] == target)
        {
            return mid; // 找到
        }
        else if (arr[mid] < target) // 说明在右边
        {
            left = mid + 1;
        }
        else // 说明在左边
        {
            right = mid;
        }
    }
    return -1; // 未找到
}
// 左侧二分查找
// 在target值在数组中有多个时，返回最左侧的target值的下标
int leftBinarySearch(vector<int> &arr, int left, int right, int target)
{
    int mid;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid] == target)
        {
            if (mid > left && arr[mid - 1] == target)
            {
                right = mid;
            }
            else
            {
                return mid;
            }
        }
        else if (arr[mid] < target) // 说明在右边
        {
            left = mid + 1;
        }
        else // 说明在左边
        {
            right = mid;
        }
    }
    return -1; // 未找到
}