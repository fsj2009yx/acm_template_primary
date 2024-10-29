#include <iostream>
#include <vector>

using namespace std;

vector<int> a(510);   // 存储每次选出来的数据
vector<int> book(510); // 标记是否被访问
int ans = 0; // 记录符合条件的次数
int k, n;    // k为选择的数量，n为总数

void dfs(int cur)
{
    if (cur == k) // k个数已经选完，可以进行输出等相关操作
    {
        for (int i = 0; i < cur; i++) 
        {
            cout << a[i] << " ";
        }
        cout << endl;
        ans++;
        return;
    }

    for (int i = 0; i < n; i++) { // 遍历 n个数，并从中选择k个数
        if (!book[i]) { // 若没有被访问
            book[i] = 1; // 标记已被访问
            a[cur] = i+1;  // 选定本数，并加入数组
            dfs(cur + 1);  // 递归，cur+1
            book[i] = 0;  // 释放，标记为没被访问，方便下次引用
        }
    }
}

int main() 
{
    cout << "请输入n和k" << endl;
    cin >> n >> k;
    dfs(0);
    cout << "答案为" << ans << endl;
    return 0;
}