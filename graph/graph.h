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
Status CreateUDN_M(MGraph *G) {
    // 采用数组（邻接矩阵）表示法，构造无向网 G
    int IncInfo;
    scanf("%d %d %d", &G->vexnum, &G->arcnum, &IncInfo);    // IncInfo 为 0 则各弧不含其他信息
    for (int i = 0; i < G->vexnum; ++i) scanf("%c", &G->vexs[i]);
    for (int i = 0; i < G->vexnum; ++i)    // 初始化邻接矩阵
	for (int j = 0; j < G->vexnum; ++j)
            G->arcs[i][j] = {INFINITY, NULL};    // {adj, info}
    for (int k = 0; k < G->arcnum; ++k) {    // 构造邻接矩阵
        VertexType v1, v2;
	int = w;
	scanf("%c %c %d", &v1, &v2, &w);    // 输入一条边依附的顶点及权值
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
    scanf("%d", &G->kind);
    switch(G->kind) {
        case DG: return CreateDG_M(G);    // 构造有向图 G
	case DN: return CreateDN_M(G);    // 构造有向网 G
	case UDG: return CreateUDG_M(G);    // 构造无向图 G
	case UDN: return CreateUDN_M(G);    // 构造无向网 G
	default: return ERROR;
    }
}// CreateGraph_M

Status DestroyGraph_M(MGraph *G) {
    // 销毁图 G
    for (int i = 0; i < G->vexnum; ++i) G->vexs[i] = ' ';
    for (int i = 0; i < G->vexnum; ++i)
	for (int j = 0; j < G->vexnum; ++j)
	    if (G->arcs[i][j].info) {
		free(G->arcs[i][j].info);
		G->arcs[i][j].info = NULL;
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

VertexType GetVex_M(MGraph G, VertexType v) {
    // 返回 v 的值
    return v;
}// GetVex_M

Status PutVex_M(MGraph *G, VertexType v, VertexType value) {
    // 对 v 赋值 value
    int i = LocateVex_M(*G, v);
    G->vexs[i] = value;
    return OK;
}// PutVex_M

VertexType FirstAdjVex_M(MGraph G, VertexType v) {
    // 返回 v 的第一个邻接顶点。若顶点在 G 中没有邻接顶点，则返回“空”
    int i = LocateVex_M(G, v);
    for (int j = 0; j < G.vexnum; ++j)
	if (j != i && G.arcs[i][j].adj != INFINITY) return G.vexs[j];
    return ' ';
}// FirstAdjVex_M

VertexType NextAdjVex_M(MGraph G, VertexType v, VertexType w) {
    // 返回 v 的（相对于 w 的）下一个邻接顶点。若 w 是 v 的最后一个邻接点，则返回“空”
    int i = LocateVex_M(G, v);
    for (int j = LocateVex_M(G, w) + 1; j < G.vexnum; ++j)
	if (j != i && G.arcs[i][j].adj != INFINITY) return G.vexs[j];
    return ' ';
}// NextAdjVex_M

Status InsertVex_M(MGraph *G, VertexType v) {
    // 在图 G 中增添新顶点 v

}// InsertVex_M

Status DeleteVex_M(MGraph *G, VertexType v) {
    // 删除 G 中顶点 v 及其相关的弧
}// DeleteVex_M

Status InsertArc_M(MGraph *G, VertexType v, VertexType w) {
    // 在 G 中增添弧<v，w>，若 G 是无向的，则还增添对称弧<w，v>
}// InsertArc_M

Status DeleteArc_M(MGraph *G, VertexType v, VertexType w) {
    // 在 G 中删除弧<v，w>，若 G 是无向的，则还删除对称弧<w，v>
}// DeleteArc_M

Status DFSTraverse_M(MGraph G, Status (*visit)()) {
    // 对图进行深度优先遍历。在遍历过程中对每个顶点调用函数 visit 一次
    // 且一次。一旦 visit() 失败，则操作失败
}// DFSTraverse_M

Status BFSTraverse_M(MGraph G, Status (*visit)()) {
    // 对图进行广度优先遍历。在遍历过程中对每个顶点调用函数 visit 一次
    // 且仅一次。一旦 visit() 失败，则操作失败
}// BFSTraverse_M
