// - - - - - 树的二叉链表（孩子 - 兄弟）存储表示 - - - - -
typedef struct CSNode {
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;

// - - - - - 循环队列——队列的顺序存储结构 - - - - -
#define MAXQSIZE 100    // 最大队列长度
typedef struct {
    CSTree *base;    // 初始化的动态分配存储空间
    int front;    // 头指针，若队列不空，指向队列头元素
    int rear;    // 尾指针，若队列不空，指向队列尾元素的下一个元素
}Queue;

// - - - - - 循环队列的基本操作的算法描述 - - - - -
Status InitQueue(Queue *Q) {
    // 构造一个空队列 Q
    Q->base = (CSTree *)malloc(MAXQSIZE * sizeof(CSTree));
    if (!Q->base) exit(OVERFLOW);    // 存储分配失败
    Q->front = Q->rear = 0;
    return OK;
}// InitQueue

Status DestroyQueue(Queue *Q) {
    // 销毁队列 Q，Q不再存在
    free(Q->base);
    Q->front = Q->rear = 0;
    return OK;
}// DestroyQueue

Status QueueEmpty(Queue Q) {
    // 若队列 Q 为空队列，则返回 TRUE，否则返回 FALSE
    return Q.front == Q.rear ? TRUE : FALSE;
}// QueueEmpty

Status EnQueue(Queue *Q, CSTree e) {
    // 插入元素 e 为 Q 的新的队尾元素
    if ((Q->rear + 1) % MAXQSIZE == Q->front) return ERROR;    // 队列满
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXQSIZE;
    return OK;
}// EnQueue

Status DeQueue(Queue *Q, CSTree *e) {
    // 若队列不空，则删除 Q 的队头元素，用 e 返回其值，并返回 OK；
    // 否则返回 ERROR
    if (QueueEmpty(*Q)) return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAXQSIZE;
    return OK;
}// DeQueue

Status LevelOrderTraverse_CS(CSTree T, Status (*visit)(ElemType e)) {
    // 层序遍历（孩子兄弟表示法）树
    Queue Q;
    InitQueue(&Q);
    while (T) {
        EnQueue(&Q, T);
	T = T->nextsibling;
    }
    CSTree p;
    while (!QueueEmpty(Q)) {
        DeQueue(&Q, &p);
	    if (!visit(p->data)) return ERROR;
	    p = p->firstchild;
	    while (p) {
	        EnQueue(&Q, p);
	        p = p->nextsibling;
	    }
    }// while
    return OK;
}// LevelOrderTraverse_CS
