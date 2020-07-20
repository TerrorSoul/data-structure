#ifndef SQQUEUE
#define SQQUEUE

// - - - - - 循环队列——队列的顺序存储结构 - - - - -
#define MAXQSIZE 100    // 最大队列长度
typedef struct {
    QElemType *base;    // 初始化的动态分配存储空间
    int front;    // 头指针，若队列不空，指向队列头元素
    int rear;    // 尾指针，若队列不空，指向队列尾元素的下一个元素
}SqQueue;

// - - - - - 循环队列的基本操作的算法描述 - - - - -
Status InitQueue_Sq(SqQueue *Q) {
    // 构造一个空队列 Q
    Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q->base) exit(OVERFLOW);    // 存储分配失败
    Q->front = Q->rear = 0;
    return OK;
}// InitQueue_Sq

Status DestroyQueue_Sq(SqQueue *Q) {
    // 销毁队列 Q，Q不再存在
    free(Q->base);
    Q->front = Q->rear = 0;
    return OK;
}// DestroyQueue_Sq

Status ClearQueue_Sq(SqQueue *Q) {
    // 将 Q 清为空队列
    Q->front = Q->rear = 0;
}// ClearQueue_Sq

Status QueueEmpty_Sq(SqQueue Q) {
    // 若队列 Q 为空队列，则返回 TRUE，否则返回 FALSE
    return Q.front == Q.rear ? TRUE : FALSE;
}// QueueEmpty_Sq

int QueueLength_Sq(SqQueue Q) {
    // 返回 Q 的元素个数，即为队列的长度
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}// QueueLength_Sq

Status GetHead_Sq(SqQueue Q, QElemType *e) {
    // 若队列不空，则用 e 返回 Q 的队头元素，并返回 OK；否则返回 ERROR
    if (QueueEmpty_Sq(Q)) return ERROR;
    *e = Q.base[Q.front];
    return OK;
}// GetHead_Sq

Status EnQueue_Sq(SqQueue *Q, QElemType e) {
    // 插入元素 e 为 Q 的新的队尾元素
    if ((Q->rear + 1) % MAXQSIZE == Q->front) return ERROR;    // 队列满
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXQSIZE;
    return OK;
}// EnQueue_Sq

Status DeQueue_Sq(SqQueue *Q, QElemType *e) {
    // 若队列不空，则删除 Q 的队头元素，用 e 返回其值，并返回 OK；
    // 否则返回 ERROR
    if (QueueEmpty_Sq(*Q)) return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAXQSIZE;
    return OK;
}// DeQueue_Sq

Status QueueTraverse_Sq(SqQueue Q, Status(*visit)()) {
    // 从队头到队尾依次对队列 Q 中每个元素调用函数 visit()。一旦 visit 失败，则操作失败。
    while (Q.front != Q.rear) {
        if (!visit(*(Q.base + Q.front))) return ERROR;
	Q.front = (Q.front + 1) % MAXQSIZE;
    }
    return OK;
}// QueueTraverse_Sq

#endif
