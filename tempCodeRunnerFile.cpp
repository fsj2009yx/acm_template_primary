#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX_SIZE = 1020;
#define endl '\n'
#define int long long

int n;
int t;

int a[MAX_SIZE][MAX_SIZE];

void solve()
{
    cin >> n;
    int count = 1;
    int temp = n;

    int nn = 510;
    a[nn][nn] = 0;

    int nn_temp_up;
    int nn_temp_down;

    for (int i = 2; i <= n; i++)
    {
        int start = i * i - 1; // 奇数和偶数，一左上一右下
        if (i & 1)
        {
            nn_temp_up = nn - i / 2;     // 角 508
            nn_temp_down = nn + (i / 2); // 角 512
            int temp = (i - 1) * (i - 1);
            for (int j = nn_temp_up + 1; j <= nn_temp_down; j++)
            {
                a[nn_temp_up][j] = temp + j - nn_temp_up - 1;
                a[j][nn_temp_up] = a[nn_temp_up][j] + i - 1;
            }

            a[nn_temp_up][nn_temp_up] = i * i - 1;
        }
        else
        {
            nn_temp_down = nn + i / 2;     // 角 511
            nn_temp_up = nn - (i / 2 - 1); // 角 510
            int temp = (i - 1) * (i - 1);
            for (int j = nn_temp_down - 1; j >= nn_temp_up; j--)
            {
                a[j][nn_temp_down] = temp + nn_temp_down - j - 1;
                a[nn_temp_down][j] = a[j][nn_temp_down] + i - 1;
            }

            a[nn_temp_down][nn_temp_down] = i * i - 1;
        }
    }

    for (int i = nn_temp_up; i <= nn_temp_down; i++)
    {
        for (int j = nn_temp_up; j <= nn_temp_down; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}