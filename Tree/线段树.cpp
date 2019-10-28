// Author: zsh  github.com/zshorz
// 2019.10.28

/// 线段树 O(logN)
/// 详解：https://blog.csdn.net/zearot/article/details/48299459

#include <iostream>
using namespace std;
#define maxn 100007
//sum求和 add懒惰标记
int sum[maxn<<2],add[maxn<<2];//线段树一般开4被原数组数组大小,2^log2(n)
int A[maxn],n;//存放原数组，下标[1，n]
//pushup更新节点信息，这里是求和
void pushup(int rt){sum[rt]=sum[rt<<1]+sum[rt<<1|1];}
//build函数建树
void build(int l=1,int r=n,int rt=1){//根节点是1，rt表示当前节点，lr表示当前节点表示的区间
    if(l==r){sum[rt]=A[l];return;}//若达到叶节点
    int m=(l+r)>>1;//区间中点
    //左右递归，构造子节点
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    //更新当前节点信息（子节点改变了，父节点也要变）
    pushup(rt);
}
//点修改，假设A[L]+=C;（A数组其实不用变，只修改线段树就行）
void pushdown(int rt,int ln,int rn){//ln,rn为左子树，右子树的数字数量。
    if(add[rt]){
        //下推标记
        add[rt<<1]+=add[rt];
        add[rt<<1|1]+=add[rt];
        //修改子节点的sum使之与对应的add相对应
        sum[rt<<1]+=add[rt]*ln;
        sum[rt<<1|1]+=add[rt]*rn;
        //清除本节点标记
        add[rt]=0;
    }
}
void update1(int L,int C,int l=1,int r=n,int rt=1){//l,r表示当前节点区间，rt表示当前节点编号
    if(l==r){//到达叶节点，修改
        sum[rt]+=C;
        return;
    }
    int m=(l+r)>>1;
    pushdown(rt,m-l+1,r-m);//下推标记(只有点和区间混合修改才用这个，因为只修改单点用不到add)
    //根据田间判断往左还是往右更新
    if(L<=m) update1(L,C,l,m,rt<<1);
    else     update1(L,C,m+1,r,rt<<1|1);
    pushup(rt);//子节点变了，本节点也要跟新
}
//区间修改，假设A[L,R]+=C
void update2(int L,int R,int C,int l=1,int r=n,int rt=1){
    if(L<=l && r<=R){//如果当前区间完全属于要更改区间
        sum[rt]+=C*(r-l+1);//跟新数字和，向上保持正确性
        add[rt]+=C;//增加add标记，表示本区间sum正确，子区间仍需要根据add的值修改
        return;
    }
    int m=(l+r)>>1;
    pushdown(rt,m-l+1,r-m);//下推标记
    //这里判断左右子树跟[L,R]有无交集，有交集才递归
    if(L <= m) update2(L,R,C,l,m,rt<<1);
    if(R > m)  update2(L,R,C,m+1,r,rt<<1|1);
    pushup(rt);//更新新本节点信息
}
//区间查询，询问A[L,R]的和
int query(int L,int R,int l=1,int r=n,int rt=1){
    if(L<=l && r<=R){//在区间内，直接返回
        return sum[rt];
    }
    int m=(l+r)>>1;
    //下推标记，否则sum可能不正确
    pushdown(rt,m-l+1,r-m);
    //累计答案
    int ans=0;
    if(L <= m)ans+=query(L,R,l,m,rt<<1);
    if(R > m) ans+=query(L,R,m+1,r,rt<<1|1);
    return ans;
}
int main()
{
    n=10;
    for(int i=1;i<=n;i++){A[i]=i;}
    build(1,n,1);
    update2(1,10,1,1,10,1);
    update1(1,100,1,10,1);
    cout<<query(1,10)<<endl;

}
