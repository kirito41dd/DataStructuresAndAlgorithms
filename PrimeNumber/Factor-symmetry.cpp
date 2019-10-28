// Author: zsh  github.com/zshorz
// 2019.10.28

/// 质数筛选-因子对称  O(NlogN) = N/2 + N/3+ ... + N/N
/// 36 = 2 x 18
/// 36 = 3 x 12
/// 36 = 4 x 9
/// 36 = 6 x 6 以这里为中线开始对称
/// 36 = 9 x 4
/// 36 = 12 x 3
/// 36 = 18 x 2


#include<stdio.h>
#include<iostream>
#include <math.h>

using namespace std;
int main()
{
    const int num = 10000;
    int a[num];
    for (int i = 0; i < num; i++)
    {
        a[i] = i;
    }
    a[0] = 0;
    a[1] = 0;
    for (int i = 0; i < sqrt(num); i++)
    {
        if(a[i] == 0)continue;
        for (int j = i*i; j < num; j += i)//这里开始位置是i的平方
        {
            a[j] = 0;
        }
    }

    for (int i = 0; i < num; i++)
    {
        if (a[i] != 0) cout << a[i] << endl;;
    }

    return 0;
}
