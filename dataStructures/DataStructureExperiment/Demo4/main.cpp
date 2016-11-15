#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <list>

using namespace std;

/**章４－图的建立和使用
 * time   : 2016．11．14
 * author : @`13
 * */

// 图的遍历（默认按照无向图来写
// 1.1 图的表示方法
// 邻接表

//　数据结构
//一个是顶点表，包括顶点和指向下一个邻接点的指针
//一个是边表， 数据结构跟顶点不同，存储的是顶点的序号，和指向下一个的指针

//  构造过程：
//  刚开始的时候把顶点表初始化，
//  指针指向null。然后边表插入进来，
//  是插入到前一个，也就是直接插入到firstedge指向的下一个，
//  而后面的后移

#ifndef MAX_VERTEX_NUM
    #define MAX_VERTEX_NUM 10
#endif

typedef char VertexType;    // 定点数据类型
typedef struct node   //　边表节点
{
   int adjvex;        // 定点序号[下标
   node* next;        // 下一条变
}EdgeNode;

typedef struct     //　顶点表节点
{
   VertexType vertex;    // 定点数据(表示
   EdgeNode* firstedge;  // 顶点指向的第一条边
}VertexNode;

typedef VertexNode AdjList[MAX_VERTEX_NUM]; // 顶点集，有最大上限，而且固定容量
                                            // 换成指针，参数->malloc?

typedef struct          // 图
{
    AdjList adjlist;    // 顶点集
    int Vertex_num;     // 顶点数
    int Edge_num;       // 边数
}Graph;

void CreateGraph(Graph* G)      // 构造一个图，简化了malloc判断
/** 图的构造（邻接表 */
{
    // 获取定点和边数
    int i,j,k;
    int a;
    EdgeNode *s;
    printf("读入顶点数和边数：");
    scanf("%d,%d",&G->Vertex_num,&G->Edge_num);
    // 构建定点表
    for (i=0;i<G->Vertex_num;i++)
    {
        fflush(stdin);  // 清空缓冲
        printf("建立顶点表：");
        cin>>G->adjlist[i].vertex;
        //G->adjlist[i].vertex= (VertexType) getchar();
        G->adjlist[i].firstedge=NULL;   // 第一条边指向空
    }
    // 构建边表
    printf("建立边表\n");
    for (k=0;k<G->Edge_num;k++)
    {
        printf("读入(vi-vj)的顶点对序号");
        scanf("%d,%d",&i,&j);
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvex=j;
        s->next=G->adjlist[i].firstedge;  //插入表头
        G->adjlist[i].firstedge=s;
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvex=i;
        s->next=G->adjlist[j].firstedge;
        G->adjlist[j].firstedge=s;
    }
}

// 1.1 图的表示方法
// 邻接矩阵
// 顶点集合一维数组
// 边的权值集合二维数组
// 顶点数和边数
#ifndef MAX_VERTEX_NUM
    #define MAX_VERTEX_NUM 10
#endif

typedef char VertexType ;  //顶点类型
typedef int EdgeType;      //边上的权值类型
typedef struct
{
    VertexType Vexter[MAX_VERTEX_NUM];
    EdgeType Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int Vexter_num;
    int Edge_num;
}Graph_A;

void CreateGraph_A(Graph_A* G)
/** 图的建立(邻接表 */
{
    int i,j,k,w=0,p;
    printf("输入顶点数和边数");
    scanf("%d,%d",&G->Vexter_num,&G->Edge_num);
    // 顶点表建立
    for ( p=0;p<G->Vexter_num;p++)
    {
          fflush(stdin);       //清除缓冲区
          printf("输入顶点信息");
          cin>>G->Vexter[p];
    }
    printf("邻接矩阵初始化完成\n");
    for ( i=1;i<=G->Vexter_num;i++)
        for ( j=1;j<=G->Vexter_num;j++)
           G->Edge[i][j]=0;
    // 边矩阵建立（全矩阵
    for ( k=0;k<G->Edge_num;k++)
    {
        printf("读入两个顶点(i,j[序号)之间边的值w:");
        scanf("%d,%d,%d",&i,&j,&w);
        G->Edge[i][j]=w;
        G->Edge[j][i]=w;
    }
}

// 1.２ 图的遍历
//  邻接表－深度优先遍历(DFS),广度优先遍历(BFS)
//  邻接矩阵－深度优先遍历(DFS)

// 最初思路：
void dfs_x(Graph *G, int v, int *isV, int vn, int t)
/** 图的深度优先遍历（遍历过程[有瑕疵
 * @param G　图游标
 * @param v　递归开始位置
 * @param isV　遍历矩阵
 * @param vn 顶点数
 * @param t 次数*/
{
    v%=vn;      // 边界处理
    // 访问
    if(!isV[v])
    {
        isV[v] = 1; // 访问节点
        printf("第%d访问的顶点：%c\n",t+1 ,G->adjlist[v].vertex);
        ++t;
    }

    if(t<vn)    // 判断是否遍历完成
    {
        node* cur;  // 边表游标
        cur = G->adjlist[v].firstedge;
        if(cur!=NULL)   // 有邻接顶点
        {
            while (cur)
            {// 找到第一个未访问的节点
                if (!isV[cur->adjvex])
                {
                    v = cur->adjvex;
                    dfs_x(G, v, isV, vn, t);
                }
                else
                    cur = cur->next;
            }
            goto e; //　如果都访问了就换下一个没访问的节点[简单处理
        }
        else
        { e:
            v++;
            dfs_x(G, v, isV, vn, t);
        }
    }
    else    // 遍历完成
        return;
}

void GraphDFS_x(Graph* G)
/** 图的深度优先遍历[~循环 */
{
    Graph* cur = G;                 // 临时游标
    int v;                          // 开始访问的位置
    int Vertex_num = G->Vertex_num; // 读取边节点
    int visited[Vertex_num] = {0};  // 是否访问过
    cout<<"请输入从第几个节点开始访问：";
    cin>>v;
    dfs_x(cur, v - 1, visited, Vertex_num, 0);
}

void dfs(Graph *G, int v, int *isV)
/** 图的深度优先遍历[递归
 * @param G　图
 * @param v　访问位置
 * @param isV 访问数组 */
{
    isV[v] = 1;
    printf("深度优先遍历:结点%c\n", G->adjlist[v].vertex);
    EdgeNode *p = G->adjlist[v].firstedge;
    while(p != nullptr)
    {
        if(!isV[p->adjvex])
            dfs(G, p->adjvex, isV);
        p = p->next;
    }
}

// 优化后
void GraphDFS(Graph *G)
/** 图的深度优先遍历 */
{
    int i;
    int visited[G->Vertex_num] = {0};
    for(i = 0; i < G->Vertex_num; i++)
        if(!visited[i])
            dfs(G, i, visited);
}

void bfs(Graph* G, int v, int* isV, int vn, int t)
/** 图的广度优先遍历（遍历过程
 * @param G　图游标
 * @param v　递归开始位置
 * @param isV　遍历矩阵
 * @param vn 顶点数
 * @param t 次数*/
{
    v%=vn;
    node* cur;
    if(!isV[v])     //未访问过
    {// 访问这个节点
        isV[v] = 1;//遍历
        cout<<"访问了节点:"<<G->adjlist[v].vertex<<endl;
        t++;
    }
    cur = G->adjlist[v].firstedge;
    while(cur)
    {// 访问这个节点的所有相邻节点
        cur = G->adjlist[v].firstedge;
        if(!isV[cur->adjvex])
        {
            isV[cur->adjvex] = 1;t++;
            cout<<"访问了节点:"<<G->adjlist[cur->adjvex].vertex<<endl;
        }
        cur = cur->next;
    }
    if (t<vn)   // 还有顶点尚未访问
        bfs(G,++v,isV,vn,t);
    else        // 访问了全部节点
        return;
}

void GraphBFS(Graph* G)
/** 图的广度优先遍历 */
{
    int v;
    Graph* cur = G;                     //　临时游标
    int Vertex_num = G->Vertex_num; // 读取边节点
    int visited[Vertex_num] = {0};  // 是否访问过
    cout<<"请输入从第几个节点开始访问：";
    cin>>v;
    bfs(G,v-1,visited,Vertex_num,0);
}

void dfs_a(Graph_A *G, int v, int* isV)
/** 图的深度优先遍历[邻接矩阵
 * @param G　图
 * @param v　访问位置
 * @param isV 访问数组 */
{
    if(!isV[v])
    {// 访问
        isV[v] = 1;
        cout<<"深度优先遍历:顶点"<<G->Vexter[v]<<endl;
    }
    // 递归深度遍历
    int j;
    for(j=0;j<G->Vexter_num;j++)
        if(G->Edge[v][j]!=0&&isV[j]==0)
            dfs_a(G,j,isV);
}

void GraphDFS_A(Graph_A* G)
/** 图的深度优先遍历[邻接矩阵 */
{   //初始化visited数组
    int visited[G->Vexter_num] = {0};
    //深度优先搜索
    int i;
    for(i=0;i<G->Vexter_num;i++)
        if(!visited[i]) // 寻找尚未被访问的节点
            dfs_a(G,i,visited);
}

// 2.1 图的最小生成树
//  最小生成树的生成算法
//      1) kruskal算法：依次选择最小的且不会产生环的边加入到集合中[贪心算法
//      2) prim算法   ：选择集合节点中与非集合节点最小的一条边加入到集合

//  邻接矩阵－kruskal算法（稀疏）:
/** 邻接矩阵－kruskal算法 伪代码*/
// while(集合中的顶点数<总顶点数-1)
//      if(这条边的权值是非集合中最短的&&这条边的两个点最多只有一条访问过)
//          将这个点加入集合

//  邻接矩阵－prim算法（稠密）:
#ifndef pri_flag    // 记录是否时联通图的变量
    #define pri_flag 100000
#endif
int pri(Graph_A *G, int v, int vn_now, int vn, int *isV, int *vv, int tc)
/**  邻接矩阵－prim算法构造最小生成树[递归
 * @param G 图
 * @param v 访问节点下标
 * @param vn_now 目前访问过的个数
 * @param vn 节点个数
 * @param isV 访问数组
 * @param vv 访问
 * @return tc 路径总权值
 * */
{
    //　访问节点
    isV[v] = 1;
    vv[vn_now] = v;
    cout<<"prim算法访问节点："<<G->Vexter[v]<<endl;
    vn_now++;
    // 判断是否完成
    if (vn_now==vn)
        return  tc;
    // 寻找下个节点
    //      临时记录变量
    int e_min = pri_flag; // 最小边权值记录变量
    int v_next = -1;    // 下一次访问位置
    //      寻找下一个节点
    for(int i=0;i<vn_now;i++)
    // 遍历目前所有访问过的节点 - vv[i]
        for(int j=0;j<vn;j++)
        // 遍历这些节点与未访问过节点的距离 - cost：G->Edge[vv[i]][j]
            if(!isV[j])  // 这些节点与未访问过的节点的距离
                 if(G->Edge[vv[i]][j]<e_min&&G->Edge[vv[i]][j]) // 边权值默认为0
                {   // 找到比以之前存储过权值更小的边 则访问下一个边
                    e_min = G->Edge[vv[i]][j];
                    v_next = j;
                }
    // 处理下一个节点-递归
    //cout<<"e_min:"<<e_min<<endl;
    if(e_min!=pri_flag)    // 找到了下一个相邻的要访问的节点
        tc += e_min;
    else
    {// 遍历中没有发现与现有节点集合相连的节点-自动按序号去访问下一个节点
        // cout<<"找不到下一个相邻节点"<<endl;   // 这个地方可能会重复多次输出,蠢！
        tc += pri_flag;                         // 改为加等一个较大的数，作为标记 %操作即可
        for(int l=0;l<vn;l++)
            if(!isV[l])
            {// 寻找第一个没访问过的点
                v_next = l;
                break; }
    }
    //cout<<"tc:"<<tc<<endl;
    pri(G,v_next,vn_now,vn,isV,vv,tc);  // 递归过程
}

//  邻接矩阵－prim算法:(默认从第一个顶点开始
void GraphPrim(Graph_A *G)
/**  邻接矩阵－prim算法构造最小生成树 */
{
    cout<<"prim算法开始："<<endl;
    int visited[G->Vexter_num] = {0}; // 初始化访问数组
    int Vexter_visited[G->Vexter_num] = {0};  // 访问顺序数组
    int total_edge_cost = pri(G, 0, 0, G->Vexter_num, visited, Vexter_visited, 0);
    if(total_edge_cost==0)
        cout<<"图G有且仅有一个根节点"<<endl;
    else if(total_edge_cost>pri_flag)
        cout<<"图G是非联通图"<<endl;
    else
        cout<<"图G是联通图,最小生成树权值为："<<total_edge_cost<<endl;
}
// 2.2 图的最小生成树（实际问题
// 思路：利用图的邻接矩阵表示和上面实现的pri最小生成树算法即可轻松解决这个问题
// * 没啥意思 就不再重写上面的结构体和这个题的实现代码了

// 思路及伪代码
//  初始化时
//      定点数=N,边数=N(N-1)/2
//      用一个含有（城市名称：String city,城市横坐标 double pos_x,城市横坐标 double pos_x）
//      的结构体来表示节点
//      输入全部节点后,循环生成每个城市之间的距离 EdgeType = double
//      Edge = pow(pow(abs(city1_x-citi2_x),2)+pow(abs(city1_y-citi2_y),2)),1/2)
//  之后利用pri算法取得最小生成数权值,即为最小费用

void cityInit()
/** 初始化城市图 */
{/*...*/}

void cityWaySolution()
/** 解决城市问题 */
{/*pri(Graph_A city);*/}


int main()
{
    // 初始化图的时候需要先为变量申请内存空间
    Graph_A* G= (Graph_A*)malloc(sizeof(Graph_A));
    CreateGraph_A(G);
    GraphPrim(G);
    return 0;
}