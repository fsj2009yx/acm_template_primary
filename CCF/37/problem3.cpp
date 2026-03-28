#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1e9 + 7;
struct Node
{
    ll len = 0;
    vector<string> ne;
    bool flag = false;
};
int n, op;
unordered_map<string, Node> mp;
unordered_map<string, ll> vis;

ll dfs(string s)
{
    if (mp[s].flag == true)
        return mp[s].len;
    else if (vis[s] != 0)
        return vis[s];
    ll res = mp[s].len % mod;
    for (auto v : mp[s].ne)
    {
        res += dfs(v);
        res %= mod;
    }
    vis[s] = res;
    return res;
}

int main()
{
    cin >> n;
    getchar();
    for (int i = 1; i <= n; i++)
    {
        vis.clear();
        string s, key, value;
        getline(cin, s);
        Node temp;
        stringstream ss(s);
        ss >> op;
        if (op == 1)
        {
            ss >> key;
            temp.flag = true;
            while (ss >> value)
            {
                if (value[0] == '$')
                {
                    temp.len += dfs(value.substr(1));
                    temp.len %= mod;
                }
                else
                    temp.len = (temp.len + value.size()) % mod;
            }
            mp[key] = temp;
        }
        else if (op == 2)
        {
            ss >> key;
            while (ss >> value)
            {
                if (value[0] == '$')
                    temp.ne.push_back(value.substr(1));
                else
                    temp.len = (temp.len + value.size()) % mod;
            }
            mp[key] = temp;
        }
        else
        {
            ss >> key;
            cout << dfs(key) << endl;
        }
    }
}