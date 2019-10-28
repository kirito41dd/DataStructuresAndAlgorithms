// Author: zsh  github.com/zshorz
// 2019.10.28

/// 主席树
/// 详解：https://blog.csdn.net/creatorx/article/details/75446472
#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define maxn 100010
int n,cnt;//n用来记录树的叶子有多少（原数组大小），cnt用来开辟新节点
struct node{
    int L,R;//分别指向左右子树，（不是这个节点代表的区间，区间会在递归时自动对应）
    int sum;//存放该节点管辖区域的信息，这个样例表示有管辖区间有多少个数
    node(){sum=0;}
}Tree[maxn*20];//存放主席树
int root[maxn];//存放多棵树的根节点
void init(){//初始化主席树,空树的情况
    cnt=1;
    root[0]=0;
    Tree[0].L=Tree[0].R=Tree[0].sum=0;
}
//更新前使root[i]=root[i-1],rt=root[i];先复制前面树的结构
void update(int num,int & rt,int l,int r)
{//num要插入的数，rt当前根节点，l,r当前区间
    Tree[cnt++]=Tree[rt];//开辟新节点，并复制上一个状态结构
    rt=cnt-1;//将节点绑上去
    Tree[rt].sum++;//更新当前节点，因为插入了num，管辖范围多了一个数
    if(l==r) return;
    int mid = (l+r)>>1;
    //判断num应该插入左子树还是右子树
    if(num <= mid) update(num,Tree[rt].L,l,mid);
    else update(num,Tree[rt].R,mid+1,r);
}
int query(int i,int j,int k,int l,int r)
{//i,j查询区间（两个节点之间），k关键字（这里是第k小的数字），l,r当前区间，返回位置（离散化后其实是对应的，值相等）
    int d=Tree[Tree[j].L].sum - Tree[Tree[i].L].sum;//表示区间ij的节点左子树管辖数子个数
    if(l==r)return l;
    int mid=(l+r)>>1;
    if(k<=d) return query(Tree[i].L,Tree[j].L,k,l,mid);
    else return     query(Tree[i].R,Tree[j].R,k-d,mid+1,r);
 //区间0-j - 区间0-i 的个数 = 区间ij的个数
}
struct value{
    int x, id;
}Value[maxn];
bool cmp(value v1, value v2){return v1.x < v2.x;}
int Rank[maxn];int m;//原数组离散之后的数组
int main(){
    init();
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&Value[i].x );
        Value[i].id=i;
    }
    //离散化
    sort(Value+1,Value+1+n,cmp);
    for(int i=1;i<=n;i++){
        Rank[Value[i].id]=i;
    }
    for(int i=1;i<=n;i++){
        root[i]=root[i-1];
        update(Rank[i],root[i],1,n);

    }
    int left,right,k;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&left,&right,&k );
        printf("%d\n",Value[query(root[left-1],root[right],k,1,n)].x);
    }
    return 0;
}
/*poj2104 查询区间第k小
7 3
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3
Sample Output
5
6
3
*/
