#include <bits/stdc++.h>
using namespace std;

struct trie
{
    int nex[100000][26], cnt;
    bool exist[100000]; // 标记该节点是否为某个字符串的结尾

    // 插入字符串 s，长度为 l
    void insert(char *s, int l)
    {
        int p = 0; // 从根节点开始（0号节点）
        for (int i = 0; i < l; i++)
        {
            int c = s[i] - 'a'; // 将字符映射到 0~25
            if (!nex[p][c])
                nex[p][c] = ++cnt; // 如果没有这条边，就新建节点
            p = nex[p][c];         // 移动到下一个节点
        }
        exist[p] = true; // 标记这个节点是一个单词的结尾
    }

    // 查询字符串 s 是否存在
    bool find(char *s, int l)
    {
        int p = 0;
        for (int i = 0; i < l; i++)
        {
            int c = s[i] - 'a';
            if (!nex[p][c])
                return false; // 中途断了，说明不存在
            p = nex[p][c];
        }
        return exist[p]; // 必须是“完整单词结尾”
    }
};

trie t; // 定义一棵 Trie 树

int main()
{
    // 初始化（重要！）
    memset(t.nex, 0, sizeof(t.nex));
    memset(t.exist, false, sizeof(t.exist));
    t.cnt = 0;

    // 插入字符串
    char s1[] = "apple";
    t.insert(s1, strlen(s1));

    char s2[] = "app";
    t.insert(s2, strlen(s2));

    // 查询
    cout << t.find("apple", 5) << endl; // 1（存在）
    cout << t.find("app", 3) << endl;   // 1（存在）
    cout << t.find("ap", 2) << endl;    // 0（不是完整单词）

    return 0;
}