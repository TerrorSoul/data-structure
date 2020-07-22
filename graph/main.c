#include <stdio.h>
#include <stdlib.h>

#include "../predefined.h"
#include "mgraph.h"

Status PrintVex(VertexType u) {
    printf("%c ", u);
    return OK;
}
Status PrintElem(ElemType e) {
    printf("%c ", e);
    return OK;
}

int main(int argc, char *argv[]) {
    /*
     输入图的类型（0：有向图，1：有向网，2：无向图，3：无向网）：2
     输入顶点数、弧数和弧是否有相关信息：8 9 0
     输入第 1 个顶点：1
     输入第 2 个顶点：2
     输入第 3 个顶点：3
     输入第 4 个顶点：4
     输入第 5 个顶点：5
     输入第 6 个顶点：6
     输入第 7 个顶点：7
     输入第 8 个顶点：8
     输入第 1 条边依附的顶点：1 2
     输入第 2 条边依附的顶点：1 3
     输入第 3 条边依附的顶点：2 4
     输入第 4 条边依附的顶点：2 5
     输入第 5 条边依附的顶点：3 6
     输入第 6 条边依附的顶点：3 7
     输入第 7 条边依附的顶点：4 8
     输入第 8 条边依附的顶点：5 8
     输入第 9 条边依附的顶点：6 7
     图构造完成
     深度优先遍历结果为：1 2 4 8 5 3 6 7
     广度优先遍历结果为：1 2 3 4 5 6 7 8
     */
    MGraph G1;
    CreateGraph_M(&G1);
    printf("图构造完成\n");
    printf("深度优先遍历结果为：");
    DFSTraverse_M(G1, PrintVex);
    printf("\n广度优先遍历结果为：");
    BFSTraverse_M(G1, PrintVex);
    DestroyGraph_M(&G1);
    printf("\n");

    /*
     输入图的类型（0：有向图，1：有向网，2：无向图，3：无向网）：2
     输入顶点数、弧数和弧是否有相关信息：13 13 0
     输入第 1 个顶点：a
     输入第 2 个顶点：b
     输入第 3 个顶点：c
     输入第 4 个顶点：d
     输入第 5 个顶点：e
     输入第 6 个顶点：f
     输入第 7 个顶点：g
     输入第 8 个顶点：h
     输入第 9 个顶点：i
     输入第 10 个顶点：j
     输入第 11 个顶点：k
     输入第 12 个顶点：l
     输入第 13 个顶点：m
     输入第 1 条边依附的顶点：a b
     输入第 2 条边依附的顶点：a c
     输入第 3 条边依附的顶点：a f
     输入第 4 条边依附的顶点：a l
     输入第 5 条边依附的顶点：b m
     输入第 6 条边依附的顶点：d e
     输入第 7 条边依附的顶点：g h
     输入第 8 条边依附的顶点：g i
     输入第 9 条边依附的顶点：g k
     输入第 10 条边依附的顶点：h k
     输入第 11 条边依附的顶点：j l
     输入第 12 条边依附的顶点：j m
     输入第 13 条边依附的顶点：l m
     图构造完成
     深度优先生成森林的层序遍历结果为:a d g b c f e h i m k j l
     */
    MGraph G2;
    CSTree T;
    CreateGraph_M(&G2);
    printf("图构造完成\n");
    printf("深度优先生成森林的层序遍历结果为:");
    DFSForest_M(G2, &T);
    LevelOrderTraverse_CS(T, PrintElem);
    DestroyGraph_M(&G2);
    printf("\n");

    /*
     输入图的类型（0：有向图，1：有向网，2：无向图，3：无向网）：3
     输入顶点数、弧数和弧是否有相关信息：6 10 0
     输入第 1 个顶点：1
     输入第 2 个顶点：2
     输入第 3 个顶点：3
     输入第 4 个顶点：4
     输入第 5 个顶点：5
     输入第 6 个顶点：6
     输入第 1 条边依附的顶点及权值：1 2 6
     输入第 2 条边依附的顶点及权值：1 3 1
     输入第 3 条边依附的顶点及权值：1 4 5
     输入第 4 条边依附的顶点及权值：2 3 5
     输入第 5 条边依附的顶点及权值：2 5 3
     输入第 6 条边依附的顶点及权值：3 4 5
     输入第 7 条边依附的顶点及权值：3 5 6
     输入第 8 条边依附的顶点及权值：3 6 4
     输入第 9 条边依附的顶点及权值：4 6 2
     输入第 10 条边依附的顶点及权值：5 6 6
     图构造完成
     1 3
     3 6
     6 4
     3 2
     2 5
     */
    MGraph G3;
    CreateGraph_M(&G3);
    printf("图构造完成\n");
    MiniSpanTree_PRIM(G3, G3.vexs[0]);
    DestroyGraph_M(&G3);

    return 0;
}
