// - - - - - 树的二叉链表（孩子 - 兄弟）存储表示 - - - - -
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

typedef CSTree QElemType;
#include "../stack_and_queue/sqqueue.h"

Status LevelOrderTraverse_CS(CSTree T, Status (*visit)(ElemType e)) {
    // 层序遍历（孩子兄弟表示法）树
    SqQueue Q;
    InitQueue_Sq(&Q);
    while (T) {
        EnQueue_Sq(&Q, T);
	T = T->nextsibling;
    }
    CSTree p;
    while (!QueueEmpty_Sq(Q)) {
        DeQueue_Sq(&Q, &p);
	if (!visit(p->data)) return ERROR;
	p = p->firstchild;
	while (p) {
	    EnQueue_Sq(&Q, p);
	    p = p->nextsibling;
	}
    }// while
    return OK;
}// LevelOrderTraverse_CS
