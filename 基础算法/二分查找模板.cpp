#include<bits/stdc++.h>
using namespace std;
int binarySearch(vector<int>& arr, int left, int right, int target) 
{
    int mid;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid] == target)
        {
            return mid;// 找到
        }
        else if (arr[mid] < target)// 说明在右边
        {
            left = mid + 1;
        }
        else// 说明在左边
        {
            right = mid;
        }
    }
    return -1;// 未找到
}