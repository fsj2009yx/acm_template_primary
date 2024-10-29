// 递推算法实现斐波拉契数列
#include<iostream>
using namespace std;

int main() 
{
    int n;
    cin >> n;
    long long*a = new long long [n+1];
    a[0] = 0;
    a[1] = 1;
    for(int i = 2; i <= n; i++)
    {
        a[i] = a[i-1] + a[i-2];
    }
    for(int i = 1; i <= n; i++)
    {
        cout << i << " " << a[i] <<endl;
    }
    delete[] a;
    return 0;
}