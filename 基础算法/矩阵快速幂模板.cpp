#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int M,n;

struct node//定义一个矩阵类型的结构体
{
    int m[100][100];
} ans,res;//ans是结果，res是最初的方阵
node mul(node A,node B)
{
    int i,j,k;
    node temp;//定义一个临时矩阵，存放A*B的结果
    for(i=0; i<n; i++)//先全部定义为0
    {
        for(j=0; j<n; j++)
        {
            temp.m[i][j] = 0;
        }
    }
    for(i=0; i<n; i++)//矩阵相乘的代码
    {
        for(j=0; j<n; j++)
        {
            for(k=0; k<n; k++)
            {
                temp.m[i][j] += A.m[i][k] * B.m[k][j];
            }
        }
    }
    return temp;
}
void quickpower(int M,int n)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(i == j)
            {
                ans.m[i][j] = 1;
            }
            else
                ans.m[i][j] = 0;
        }
    }//这里是思想的转换，之前我们定义为1去计算，所以我们先初始化ans为
    //单位矩阵，我们知道单位矩阵与任何矩阵的乘积为其本身
    while(M)//快速幂的步骤
    {
        if(M & 1)
        {
            ans = mul(ans,res);
        }
        res = mul(res,res);
        M = M >> 1;
    }
}
int main()
{
    cin>>n;//方阵的阶数
    cin>>M;//指数
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            cin>>res.m[i][j];//初始化方阵res
        }
    }
    quickpower(M,n);//进行快速幂
    for(i=0; i<n; i++)//输出
    {
        for(j=0; j<n; j++)
        {
            printf("%d ",ans.m[i][j]);
        }
        printf("\n");
    }
    return 0;
}