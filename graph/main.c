#include <stdio.h>
#include <stdlib.h>

#include "../predefined.h"
#include "mgraph.h"

Status PrintVex(VertexType u) {
    printf("%c ", u);
    return OK;
}
Status PrintElem(ElemType e) {
    printf("%d ", e);
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
    printf("\n");

    MGraph G2;
    CSTree T;
    CreateGraph_M(&G2);
    printf("图构造完成\n");
    printf("深度优先生成森林的层序遍历结果为:");
    DFSForest_M(G2, &T);
    LevelOrderTraverse_CS(T, PrintElem);
    printf("\n");

    return 0;
}
