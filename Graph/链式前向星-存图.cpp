// Author: zsh  github.com/zshorz
// 2019.10.28

/// 存图方法-链式前向星

#include <stdio.h>
#include <string.h>

//最大顶点数与最大边数
const int V=100;
const int E=100;

//边结构体定义
struct Edge{
    int to;   // 这条边的另一个顶点
    int next; // 指向下一条边的数组下标，-1为不存在；
    int len;  // 权值
};

//head[i] 表示顶点i的边的数组下标，-1表示无边；
int head[V];//第一条边
Edge edge[E];

//链式向前星初始化，之初始化顶点数组
void init(){
    memset(head, -1, sizeof(head));
}

//增加边的方式
//加入a—>b,权值l;
int id;
inline void AddEdge(int a,int b,int l=0){
    edge[id].to=b;
    edge[id].next=head[a]; //和下面一行将新边作为a的第一条边;
    head[a]=id;
    edge[id].len=l;
    id++;//只给edge数组开新空间用
}

/// 遍历从a出发的边 得到下一个点和权值
/// for(int i=head[a];i!=-1;i=edge[i].next){
///     //edge[i] 即为当前边
/// }

