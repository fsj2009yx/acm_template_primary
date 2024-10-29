#include <cmath>     // 包含数学函数库
#include <cstdlib>   // 包含随机数函数库
#include <ctime>     // 包含时间函数库，用于生成随机种子
#include <iomanip>   // 包含格式化输出库
#include <iostream>  // 包含输入输出流库

// 设置常量 N 为 10005，表示最多支持的点的数量
constexpr int N = 10005;
int n, x[N], y[N], w[N];   // n 是点的数量，x 和 y 分别存储每个点的横纵坐标，w 存储每个点的权重
double ansx, ansy, dis;    // ansx 和 ansy 分别表示当前最佳点的横纵坐标，dis 表示当前最小距离加权和

// 生成 0 到 1 之间的随机小数
double Rand() { return (double)rand() / RAND_MAX; }

// 计算给定点 (xx, yy) 到所有点的加权欧几里得距离和
double calc(double xx, double yy) {
    double res = 0;
    for (int i = 1; i <= n; ++i) {
        // 计算当前点与点 (xx, yy) 的横纵坐标差值
        double dx = x[i] - xx, dy = y[i] - yy;
        // 加权计算欧几里得距离，并累加到结果 res 中
        res += sqrt(dx * dx + dy * dy) * w[i];
    }
    // 如果当前的距离加权和小于全局最小距离，则更新最优解
    if (res < dis) dis = res, ansx = xx, ansy = yy;
    return res;  // 返回当前计算的距离加权和
}

// 模拟退火算法，寻找加权距离和最小的点 (ansx, ansy)
void simulateAnneal() {
    double t = 100000;       // 初始温度设置为 100000
    double nowx = ansx, nowy = ansy;  // 当前点初始化为已知的最佳点

    // 模拟退火主循环，温度 t 每次逐渐下降，直到低于 0.001
    while (t > 0.001) {
        // 在当前点附近随机生成下一个点 (nxtx, nxty)
        double nxtx = nowx + t * (Rand() * 2 - 1);
        double nxty = nowy + t * (Rand() * 2 - 1);

        // 计算新旧点的加权距离和的差值 delta
        double delta = calc(nxtx, nxty) - calc(nowx, nowy);

        // 如果满足接受条件，则更新当前点为新点 (nxtx, nxty)
        if (exp(-delta / t) > Rand()) nowx = nxtx, nowy = nxty;

        // 温度逐渐下降，模拟退火过程
        t *= 0.97;
    }

    // 额外的微调阶段，进一步优化当前最优解
    for (int i = 1; i <= 1000; ++i) {
        double nxtx = ansx + t * (Rand() * 2 - 1);
        double nxty = ansy + t * (Rand() * 2 - 1);
        calc(nxtx, nxty);  // 尝试计算新的点并更新最优解
    }
}

int main() {
    // 优化输入输出
    std::cin.tie(nullptr)->sync_with_stdio(false);
    srand(0);  // 随机种子设置为固定值 0 (在实际应用中应使用随机种子以避免重复随机序列)

    // 读取输入：n 表示点的数量，接着读取每个点的坐标 (x[i], y[i]) 和权重 w[i]
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> x[i] >> y[i] >> w[i];
        // 初始化最佳点为所有点的坐标平均值
        ansx += x[i], ansy += y[i];
    }

    // 计算初始的平均点，并初始化最小加权距离和 dis
    ansx /= n, ansy /= n, dis = calc(ansx, ansy);

    // 调用模拟退火算法，寻找最优解
    simulateAnneal();

    // 输出计算得到的最佳点坐标，保留三位小数
    std::cout << std::fixed << std::setprecision(3) << ansx << ' ' << ansy << '\n';

    return 0;
}
