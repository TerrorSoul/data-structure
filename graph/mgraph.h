#include <limits.h>

typedef int QElemType;
#include "../stack_and_queue/sqqueue.h"
typedef char ElemType;
#include "../tree_and_bitree/cstree.h"

// - - - - - 图的数组（邻接矩阵）存储表示 - - - - -
#define INFINITY INT_MAX    // 最大值
#define MAX_VERTEX_NUM 20    // 最大顶点个数
typedef enum {DG, DN, UDG, UDN} GraphKind;    // {有向图，有向网，无向图，无向网}
typedef int InfoType;
typedef char VertexType;
typedef struct {
    int adj;    // int 是顶点关系类型。对无权图，用 1 或 0 表示相邻否；对带权图，则为权值类型
    InfoType *info;    // 该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];    // 顶点向量
    AdjMatrix arcs;    // 邻接矩阵
    int vexnum, arcnum;    // 图的当前顶点数和弧数
    GraphKind kind;    // 图的种类标志
}MGraph;

// - - - - - 基本操作的算法描述 - - - - -
int LocateVex_M(MGraph G, VertexType u);
Status CreateDG_M(MGraph *G) {
    // 采用数组（邻接矩阵）表示法，构造有向图 G
    int IncInfo;
    printf("输入顶点数、弧数和弧是否有相关信息：");
    scanf("%d %d %d", &G->vexnum, &G->arcnum, &IncInfo);    // IncInfo 为 0 则各弧不含其他信息
    getchar();
    for (int i = 0; i < G->vexnum; ++i) {
        printf("输入第 %d 个顶点：", i + 1);
        scanf("%c", &G->vexs[i]);
        getchar();
    }
    for (int i = 0; i < G->vexnum; ++i)    // 初始化邻接矩阵
	    for (int j = 0; j < G->vexnum; ++j) {
            G->arcs[i][j].adj = 0;    // {adj, info}
            G->arcs[i][j].info = NULL;
        }
    for (int k = 0; k < G->arcnum; ++k) {    // 构造邻接矩阵
        VertexType v1, v2;
	    printf("输入第 %d 条边依附的顶点：", k + 1);
	    scanf("%c %c", &v1, &v2);    // 输入一条边依附的顶点及权值
	    getchar();
	    int i = LocateVex_M(*G, v1), j = LocateVex_M(*G, v2);    // 确定 v1 和 v2 在 G 中位置
	    G->arcs[i][j].adj = 1;    // 弧<v1，v2>的权值
	    if (IncInfo) {    // 若弧含有相关信息，则输入
	        G->arcs[i][j].info = (InfoType *)malloc(sizeof(InfoType));
	        scanf("%d", G->arcs[i][j].info);
	    }
    }
    return OK;
}// CreateDG_M
Status CreateDN_M(MGraph *G) {
    // 采用数组（邻接矩阵）表示法，构造有向网 G
    int IncInfo;
    printf("输入顶点数、弧数和弧是否有相关信息：");
    scanf("%d %d %d", &G->vexnum, &G->arcnum, &IncInfo);    // IncInfo 为 0 则各弧不含其他信息
    getchar();
    for (int i = 0; i < G->vexnum; ++i) {
        printf("输入第 %d 个顶点：", i + 1);
        scanf("%c", &G->vexs[i]);
        getchar();
    }
    for (int i = 0; i < G->vexnum; ++i)    // 初始化邻接矩阵
	    for (int j = 0; j < G->vexnum; ++j) {
            G->arcs[i][j].adj = INFINITY;    // {adj, info}
            G->arcs[i][j].info = NULL;
	    }
    for (int k = 0; k < G->arcnum; ++k) {    // 构造邻接矩阵
        VertexType v1, v2;
	    int w;
	    printf("输入第 %d 条边依附的顶点及权值：", k + 1);
	    scanf("%c %c %d", &v1, &v2, &w);    // 输入一条边依附的顶点及权值
	    getchar();
	    int i = LocateVex_M(*G, v1), j = LocateVex_M(*G, v2);    // 确定 v1 和 v2 在 G 中位置
	    G->arcs[i][j].adj = w;    // 弧<v1，v2>的权值
	    if (IncInfo) {    // 若弧含有相关信息，则输入
	        G->arcs[i][j].info = (InfoType *)malloc(sizeof(InfoType));
	        scanf("%d", G->arcs[i][j].info);
	    }
    }
    return OK;
}// CreateDN_M
Status CreateUDG_M(MGraph *G) {
    // 采用数组（邻接矩阵）表示法，构造无向图 G
    int IncInfo;
    printf("输入顶点数、弧数和弧是否有相关信息：");
    scanf("%d %d %d", &G->vexnum, &G->arcnum, &IncInfo);    // IncInfo 为 0 则各弧不含其他信息
    getchar();
    for (int i = 0; i < G->vexnum; ++i) {
        printf("输入第 %d 个顶点：", i + 1);
        scanf("%c", &G->vexs[i]);
        getchar();
    }
    for (int i = 0; i < G->vexnum; ++i)    // 初始化邻接矩阵
	    for (int j = 0; j < G->vexnum; ++j) {
            G->arcs[i][j].adj = 0;    // {adj, info}
            G->arcs[i][j].info = NULL;
	    }
    for (int k = 0; k < G->arcnum; ++k) {    // 构造邻接矩阵
        VertexType v1, v2;
	    printf("输入第 %d 条边依附的顶点：", k + 1);
	    scanf("%c %c", &v1, &v2);    // 输入一条边依附的顶点及权值
	    getchar();
	    int i = LocateVex_M(*G, v1), j = LocateVex_M(*G, v2);    // 确定 v1 和 v2 在 G 中位置
	    G->arcs[i][j].adj = 1;    // 弧<v1，v2>的权值
	    if (IncInfo) {    // 若弧含有相关信息，则输入
	        G->arcs[i][j].info = (InfoType *)malloc(sizeof(InfoType));
	        scanf("%d", G->arcs[i][j].info);
	    }
	    G->arcs[j][i] = G->arcs[i][j];    // 置<v1，v2>的对称弧<v2，v1>
    }
    return OK;
}// CreateUDG_M
Status CreateUDN_M(MGraph *G) {
    // 采用数组（邻接矩阵）表示法，构造无向网 G
    int IncInfo;
    printf("输入顶点数、弧数和弧是否有相关信息：");
    scanf("%d %d %d", &G->vexnum, &G->arcnum, &IncInfo);    // IncInfo 为 0 则各弧不含其他信息
    getchar();
    for (int i = 0; i < G->vexnum; ++i) {
        printf("输入第 %d 个顶点：", i + 1);
        scanf("%c", &G->vexs[i]);
        getchar();
    }
    for (int i = 0; i < G->vexnum; ++i)    // 初始化邻接矩阵
	    for (int j = 0; j < G->vexnum; ++j) {
            G->arcs[i][j].adj = INFINITY;    // {adj, info}
            G->arcs[i][j].info = NULL;
	    }
    for (int k = 0; k < G->arcnum; ++k) {    // 构造邻接矩阵
        VertexType v1, v2;
	    int w;
	    printf("输入第 %d 条边依附的顶点及权值：", k + 1);
	    scanf("%c %c %d", &v1, &v2, &w);    // 输入一条边依附的顶点及权值
	    getchar();
	    int i = LocateVex_M(*G, v1), j = LocateVex_M(*G, v2);    // 确定 v1 和 v2 在 G 中位置
	    G->arcs[i][j].adj = w;    // 弧<v1，v2>的权值
	    if (IncInfo) {    // 若弧含有相关信息，则输入
	        G->arcs[i][j].info = (InfoType *)malloc(sizeof(InfoType));
	        scanf("%d", G->arcs[i][j].info);
	    }
	    G->arcs[j][i] = G->arcs[i][j];    // 置<v1，v2>的对称弧<v2，v1>
    }
    return OK;
}// CreateUDN_M
Status CreateGraph_M(MGraph *G) {
    // 采用数组（邻接矩阵）表示法，构造图 G
    int kind;
    printf("输入图的类型（0：有向图，1：有向网，2：无向图，3：无向网）：");
    scanf("%d", &kind);
    getchar();
    switch(kind) {
        case 0:
	    G->kind = DG;
            return CreateDG_M(G);    // 构造有向图 G
	case 1:
	    G->kind = DN;
	    return CreateDN_M(G);    // 构造有向网 G
	case 2:
	    G->kind = UDG;
	    return CreateUDG_M(G);    // 构造无向图 G
	case 3:
	    G->kind = UDN;
	    return CreateUDN_M(G);    // 构造无向网 G
	default: return ERROR;
    }
}// CreateGraph_M

Status DestroyGraph_M(MGraph *G) {
    // 销毁图 G
    for (int i = 0; i < G->vexnum; ++i) G->vexs[i] = ' ';
    for (int i = 0; i < G->vexnum; ++i)
	    for (int j = 0; j < G->vexnum; ++j) {
	        if (G->arcs[i][j].info) {
		        free(G->arcs[i][j].info);
		        G->arcs[i][j].info = NULL;
	        }
		    G->arcs[i][j].adj = INFINITY;
        }
    G->vexnum = G->arcnum = 0;
    return OK;
}// DestroyGraph_M

int LocateVex_M(MGraph G, VertexType u) {
    // 若 G 中存在顶点 u，则返回该顶点在图中位置；否则返回其他信息
    int i = 0;
    for (; i < G.vexnum; ++i)
	if (G.vexs[i] == u) return i;
    return -1;
}// LocateVex_M

VertexType GetVex_M(MGraph G, int v) {
    // 返回 v 的值
    return G.vexs[v];
}// GetVex_M

Status PutVex_M(MGraph *G, int v, VertexType value) {
    // 对 v 赋值 value
    G->vexs[v] = value;
    return OK;
}// PutVex_M

int FirstAdjVex_M(MGraph G, int v) {
    // 返回 v 的第一个邻接顶点。若顶点在 G 中没有邻接顶点，则返回“空”
    for (int i = 0; i < G.vexnum; ++i)
	if (G.arcs[v][i].adj != INFINITY && G.arcs[v][i].adj != 0) return i;
    return -1;
}// FirstAdjVex_M

int NextAdjVex_M(MGraph G, int v, int w) {
    // 返回 v 的（相对于 w 的）下一个邻接顶点。若 w 是 v 的最后一个邻接点，则返回“空”
    for (int i = w + 1; i < G.vexnum; ++i)
	if (G.arcs[v][i].adj != INFINITY && G.arcs[v][i].adj != 0) return i;
    return -1;
}// NextAdjVex_M

Status InsertVex_M(MGraph *G, VertexType v) {
    // 在图 G 中增添新顶点 v
    G->vexs[G->vexnum] = v;
    for (int i = 0; i <= G->vexnum; ++i) {
	G->arcs[G->vexnum][i].adj = G->kind == DG || G->kind == UDG ? 0 : INFINITY;
	G->arcs[G->vexnum][i].info = NULL;
    }
    for (int i = 0; i < G->vexnum; ++i) {
        G->arcs[i][G->vexnum].adj = G->kind == DG || G->kind == UDG ? 0 : INFINITY;
	G->arcs[i][G->vexnum].info = NULL;
    }
    ++G->vexnum;
    return OK;
}// InsertVex_M

Status DeleteVex_M(MGraph *G, VertexType v) {
    // 删除 G 中顶点 v 及其相关的弧
    int i = LocateVex_M(*G, v);
    for (int j = 0; j < G->vexnum; ++j)
	if (G->arcs[i][j].adj != INFINITY)
	    --G->arcnum;
    if (G->kind == DG || G->kind == DN)
	for (int j = 0; j < G->vexnum; ++j)
            if (j != i && G->arcs[j][i].adj != INFINITY)
		--G->arcnum;
    for (int j = i; j < G->vexnum; ++j)
	for (int k = 0; k < G->vexnum; ++k)
	    G->arcs[j][k] = G->arcs[j + 1][k];
    for (int j = 0; j < G->vexnum - 1; ++j)
        for (int k = i; k < G->vexnum; ++k)
	    G->arcs[j][k] = G->arcs[j][k + 1];
    --G->vexnum;
    return OK;
}// DeleteVex_M

Status InsertArc_M(MGraph *G, VertexType v, VertexType w) {
    // 在 G 中增添弧<v，w>，若 G 是无向的，则还增添对称弧<w，v>
    int i = LocateVex_M(*G, v), j = LocateVex_M(*G, w), adj;    // 确定 v 和 w 在 G 中位置
    scanf("%d", &adj);
    G->arcs[i][j].adj = adj;
    if (G->kind == UDG || G->kind == UDN) G->arcs[j][i].adj = adj;
    ++G->arcnum;
    return OK;
}// InsertArc_M

Status DeleteArc_M(MGraph *G, VertexType v, VertexType w) {
    // 在 G 中删除弧<v，w>，若 G 是无向的，则还删除对称弧<w，v>
    int i = LocateVex_M(*G, v), j = LocateVex_M(*G, w);    //确定 v 和 w 在 G 中位置
    G->arcs[i][j].adj = INFINITY;
    G->arcs[i][j].info = NULL;
    if (G->kind == UDG || G->kind == UDN) {
        G->arcs[j][i].adj = INFINITY;
        G->arcs[j][i].info = NULL;
    }
    --G->arcnum;
    return OK;
}// DeleteArc_M

void DFS_M(MGraph G, int v, int visited[], Status (*visit)(VertexType u)) {
    // 从第 v 个顶点出发递归地深度优先遍历图 G
    visited[v] = 1;
    visit(G.vexs[v]);    // 访问第 v 个顶点
    for (int w = FirstAdjVex_M(G, v); w >= 0; w = NextAdjVex_M(G, v, w))
	if (!visited[w]) DFS_M(G, w, visited, visit);    // 对 v 的尚未访问的邻接顶点 w 递归调用 DFS
}// DFS_M
Status DFSTraverse_M(MGraph G, Status (*visit)(VertexType u)) {
    // 对图进行深度优先遍历。在遍历过程中对每个顶点调用函数 visit 一次
    // 且一次。一旦 visit() 失败，则操作失败
    int visited[G.vexnum];
    for (int v = 0; v < G.vexnum; ++v) visited[v] = 0;    // 访问标志数组初始化
    for (int v = 0; v < G.vexnum; ++v)
	if (!visited[v]) DFS_M(G, v, visited, visit);    // 对尚未访问的顶点调用 DFS
    return OK;
}// DFSTraverse_M

Status BFSTraverse_M(MGraph G, Status (*visit)(VertexType u)) {
    // 对图进行广度优先遍历。在遍历过程中对每个顶点调用函数 visit 一次
    // 且仅一次。一旦 visit() 失败，则操作失败
    int visited[G.vexnum];
    for (int v = 0; v < G.vexnum; ++v) visited[v] = 0;
    SqQueue Q;
    InitQueue_Sq(&Q);    // 置空的辅助队列 Q
    for (int v = 0; v < G.vexnum; ++v)
	if (!visited[v]) {    // v 尚未访问
	    visited[v] = 1;
	    visit(G.vexs[v]);
	    EnQueue_Sq(&Q, v);    // v 入队列
            while (!QueueEmpty_Sq(Q)) {
		int u;
	        DeQueue_Sq(&Q, &u);    // 队头元素出队并置为 u
		for (int w = FirstAdjVex_M(G, u); w >= 0; w = NextAdjVex_M(G, u, w))
	            if (!visited[w]) {    // w 为 u 的尚未访问的邻接顶点
		        visited[w] = 1;
			visit(G.vexs[w]);
			EnQueue_Sq(&Q, w);
		    }// if
	    }// while
	}// if
    return OK;
}// BFSTraverse_M

void DFSTree_M(MGraph G, int v, CSTree *T, int visited[]) {
    // 从第 v 个顶点出发深度优先遍历图 G，建立以 T 为根的生成树
    visited[v] = 1;
    int first = 1;
    CSTree p, q;
    for (int w = FirstAdjVex_M(G, v); w >= 0; w = NextAdjVex_M(G, v, w))
        if (!visited[w]) {
	    p = (CSTree)malloc(sizeof(CSNode));    // 分配孩子结点
	    p->data = GetVex_M(G, w);
	    p->firstchild = p->nextsibling = NULL;
	    if (first) {    // w 是 v 的第一个未被访问的邻接顶点
	        (*T)->firstchild = p;    // 是根的左孩子结点
		    first = 0;
	    } else {    // w 是 v 的其他未被访问的邻接顶点
	        q->nextsibling = p;    // 是上一邻接顶点的右兄弟结点
	    }
	    q = p;
	    DFSTree_M(G, w, &q, visited);    // 从第 w 个顶点出发深度优先遍历图 G，建立子生成树 q
	}// if
}// DFSTree_M
void DFSForest_M(MGraph G, CSTree *T) {
    // 建立无向图 G 的深度优先生成森林的（最左）孩子（右）兄弟链表 T
    *T = NULL;
    int visited[G.vexnum];
    for (int v = 0; v < G.vexnum; ++v) visited[v] = 0;
    CSTree p, q;
    for (int v = 0; v < G.vexnum; ++v)
        if (!visited[v]) {
	        p = (CSTree)malloc(sizeof(CSNode));    // 分配根结点
	        p->data = GetVex_M(G, v);    // 给该结点赋值
	        p->firstchild = p->nextsibling = NULL;
	        if (!(*T)) *T = p;    // 是第一棵生成树的根（T 的根）
	        else q->nextsibling = p;    // 是其他生成树的根（前一棵的根的“兄弟”）
	        q = p;    // q 指示当前生成树的根
	        DFSTree_M(G, v, &p, visited);    // 建立以 p 为根的生成树
	    }
}// DFSForest_M
struct {
    VertexType adjvex;
    int lowcost;
 }closedge[MAX_VERTEX_NUM];
void MiniSpanTree_PRIM(MGraph G, VertexType u) {
    // 用普里姆算法从第 u 个顶点出发构造网 G 的最小生成树 T，输出 T 的各条边
    // 记录从顶点集 U 到 V - U 的代价最小的边的辅助数组定义：
    int k = LocateVex_M(G, u), lowcost;
    for (int i = 0; i < G.vexnum; ++i)    // 辅助数组初始化
	    if (i != k) {
	        closedge[i].adjvex = u;
	        closedge[i].lowcost = G.arcs[k][i].adj;
	    }
    closedge[k].lowcost = 0;    // 初始，U = { u }
    for (int i = 1; i < G.vexnum; ++i) {    // 选择其余 G.vexnum - 1 个顶点
        lowcost = INFINITY;
	    for (int j = 0; j < G.vexnum; ++j) {    // 求出 T 的下一个结点：第 k 结点
            if (closedge[j].lowcost > 0 && closedge[j].lowcost < lowcost) {
	            lowcost = closedge[j].lowcost;
		        k = j;
	        }
        }
        // 此时 closedge[k].lowcost = MIN{ closedge[vi].lowcost | closedge[vi].lowcost > 0, vi 属于 V - U}
	    printf("%c %c\n", closedge[k].adjvex, G.vexs[k]);    // 输出生成树的边
	    closedge[k].lowcost = 0;    // 第 k 顶点并入 U 集
	    for (int j = 0; j < G.vexnum; ++j)
            if (G.arcs[k][j].adj < closedge[j].lowcost) {    // 新顶点并入 U 后重新选择最小边
		        closedge[j].adjvex = G.vexs[k];
		        closedge[j].lowcost = G.arcs[k][j].adj;
	        }
    }
}// MiniSpanTree_PRIM
