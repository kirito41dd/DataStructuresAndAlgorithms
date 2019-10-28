// Author: zsh  github.com/zshorz
// 2019.10.28

/// 快速幂 O(logN) N为指数

#include<stdio.h>
#include<iostream>
#include <math.h>
//以b==11为例，b=>1011,二进制从右向左算，但乘出来的顺序是 a^(2^0)*a^(2^1)*a^(2^3)，
//是从左向右的。我们不断的让base*=base目的即是累乘，以便随时对ans做出贡献
using namespace std;
long long Qpower(int a,int b);
int main()
{
    //cout<<Qpower(2,10);
    for(int i=0;i<10;i++)
    {
        int n=1;
        cout<<n;
        n++;
    }
    return 0;
}
long long Qpower(int a,int b)
{
    long long  ans=1,base=a;
    const int mmmod=1e9+7;

    while(b!=0)
    {
        if(b&1==1)ans=((ans%mmmod)*(base%mmmod))%mmmod;
        base=((base%mmmod)*(base%mmmod))%mmmod;
        b>>=1;
    }
    return ans;
}
