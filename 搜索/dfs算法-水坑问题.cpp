/*
    题目链接：https://www.luogu.com.cn/problem/P1596
*/
#include <iostream>
#include <vector>

using namespace std;

// 定义网格的大小
int N, M;
// 用于表示田地的网格。二维字符数组，'W'表示有水（水坑），'.'表示旱地。
vector<vector<char>> field;

// 用于方向移动的数组，分别表示八个方向：上下左右、四个对角线方向。
// dx 和 dy 数组定义了相对移动的坐标偏移。
int dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 }; // 对应的行偏移（纵向移动）
int dy[] = { 0, 1, -1, 1, -1, 0, 1, -1 }; // 对应的列偏移（横向移动）

// 深度优先搜索（DFS）函数，从当前水坑点 (x, y) 出发，遍历与之相邻的水坑
void dfs(int x, int y) 
{
    // 将当前网格位置标记为已访问。此处用 '.' 表示已经处理过的水坑。
    field[x][y] = '*';

    // 遍历八个可能的方向，检查相邻的水坑格子
    for (int i = 0; i < 8; ++i) 
    {
        // 新的网格坐标：根据当前方向计算出相邻的格子坐标 (nx, ny)
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 检查相邻格子是否在网格范围内，并且该格子是未访问过的水坑（'W'）
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && field[nx][ny] == '@')
        {
            // 如果条件满足，则递归调用 DFS，继续处理相连的水坑区域
            dfs(nx, ny);
        }
    }
}

int main()
{
    // 读取输入的网格大小 N 和 M
    cin >> N >> M;

    // 初始化二维网格 field，大小为 N×M
    field.resize(N, vector<char>(M));

    // 从标准输入中读取 N 行，每行包含 M 个字符，表示田地的水和旱地布局
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> field[i][j]; // 读取每个字符，'W'表示水，'.'表示旱地
        }
    }

    // 计数水坑数量的变量
    int puddles = 0;

    // 遍历整个网格，检查每个位置是否是一个未访问过的水坑（'W'）
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j) 
        {
            // 如果当前格子是水坑（'W'），则我们发现了一个新的水坑
            if (field[i][j] == 'W') 
            {
                // 通过 DFS 将与当前水坑相连的所有水坑格子标记为已访问
                dfs(i, j);

                // 每调用一次 DFS，说明发现了一个新的独立水坑，水坑数量加1
                ++puddles;
            }
        }
    }

    // 输出水坑的总数量
    cout << puddles << endl;

    return 0;
}
