// 将一个元素插入单调栈时，为了维护栈的单调性，需要在保证将该元素插入到栈顶后整个栈满足单调性的前提下弹出最少的元素。

// 单调栈应用：https://www.luogu.com.cn/problem/P1901

#include <bits/stdc++.h>
using namespace std;

stack<int> s;

int n;
int main()
{
    cin >> n;
    map<int, int> mp;
    vector<int> height(n);
    map<int, int> ans;

    for (int i = 0; i < n; i++)
    {
        int h, v;
        cin >> h >> v;
        height[i] = h;
        mp[h] = v;
    }

    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && height[i] > s.top())
        {
            int t = s.top();
            ans[height[i]] += mp[t];
            s.pop();
        }
        if (!s.empty() && height[i] < s.top())
        {
            ans[s.top()] += mp[height[i]];
        }

        s.push(height[i]);
    }

    int res = 0;
    for (auto i : ans)
    {
        res = max(res, i.second);
    }

    cout << res << endl;
}

// 使用数组实现单调栈
// 区别在于数组实现单调栈时,可访问栈内元素

vector<int> nextGreaterElement(const vector<int> &nums)
{
    int n = nums.size();
    vector<int> res(n, -1); // 初始化为 -1 表示没有更大元素
    vector<int> stk;        // 单调栈，存储的是下标

    for (int i = 0; i < n; ++i)
    {
        // 如果当前元素大于栈顶元素，则说明当前元素是栈顶的“下一个更大元素”
        while (!stk.empty() && nums[i] > nums[stk.back()])
        {
            res[stk.back()] = nums[i];
            stk.pop_back();
        }
        stk.push_back(i); // 将当前下标入栈
    }

    return res;
}