// Author: zsh  github.com/zshorz
// 2019.10.28

/// 质数筛选-欧拉线性筛  O(N)

#include<cstdio>
const int SIZE = 10000 + 1; // 筛取上限10000
int main()
{
    int check[SIZE] = {0}; // 0代表是素数
    int prime[SIZE] = {0}; //升序存放素数
    int pos = 0; // 记素数在prime中存放的下标

    for (int i = 2; i < SIZE ; i++)
    {
        if (!check[i])//如果i是素数
        {
            prime[pos++] = i;
        }
        for (int j = 0; j < pos && i*prime[j] < SIZE; j++)
        {
            check[i*prime[j]] = 1;//筛掉
            if (i % prime[j] == 0) break;//如果i是后者倍数，不再乘下一个素数
            //比如2*2后不再2*3，因为3*2等于6
            //3*3后不再3*5，因为5*3=15
        }
    }
    //输出
    for (int i = 0, k = 1; i < pos; i++, k++)
    {
        printf("%4d ", prime[i]);
        if (!(k%10)) printf("\n");
    }
    printf("\n");
    return 0;
}
