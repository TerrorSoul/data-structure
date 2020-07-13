// - - - - - 单链队列——队列的链式存储结构 - - - - -
typedef struct QNode {
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;
typedef struct {
    QueuePtr front;    // 队头指针
    QueuePtr rear;    // 队尾指针
}LinkQueue;

// - - - - - 基本操作的算法描述 - - - - -
Status InitQueue_L(LinkQueue *Q) {
    // 构造一个空队列 Q
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q->front) exit(OVERFLOW);    // 存储分配失败
    Q->front->next = NULL;
    return OK;
}// InitQueue_L

Status DestroyQueue_L(LinkQueue *Q) {
    // 销毁队列 Q，Q 不再存在
    while (Q->front) {
        Q->rear = Q->front->next;
	free(Q->front);
	Q->front = Q->rear;
    }
    return OK;
}// DestroyQueue_L

Status ClearQueue_L(LinkQueue *Q) {
    // 将 Q 清为空队列
    QueuePtr p = Q->front->next;
    while (p) {
        Q->rear = p->next;
	free(p);
	p = Q->rear;
    }
    Q->rear = Q->front;
    return OK;
}// ClearQueue_L

Status QueueEmpty_L(LinkQueue Q) {
    // 若队列 Q 为空队列，则返回 TRUE，否则返回 FALSE
    return Q.front == Q.rear ? TRUE : FALSE;
}// QueueEmpty_L

int QueueLength_L(LinkQueue Q) {
    // 返回 Q 的元素个数，即为队列的长度
    int i = 0;
    for (Q.front = Q.front->next; Q.front; ++i, Q.front = Q.front->next);
    return i;
}// QueueLength_L

Status GetHead_L(LinkQueue Q, QElemType *e) {
    // 若队列不空，则用 e 返回 Q 的队头元素，并返回 OK；否则返回 ERROR
    if (QueueEmpty_L(Q)) return ERROR;
    *e = Q.front->next->data;
    return OK;
}// GetHead_L

Status EnQueue_L(LinkQueue *Q, QElemType e) {
    // 插入元素 e 为 Q 的新的队尾元素
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p) exit(OVERFLOW);    // 存储分配失败
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}// EnQueue_L

Status DeQueue_L(LinkQueue *Q, QElemType *e) {
    // 若队列不空，则删除 Q 的队头元素，用 e 返回其值，并返回 OK；
    // 否则返回 ERROR
    if (QueueEmpty_L(*Q)) return ERROR;
    QueuePtr p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) Q->rear = Q->front;
    free(p);
    return OK;
}// DeQueue_L

Status QueueTraverse_L(LinkQueue Q, Status(*visit)()) {
    // 从队头到队尾依次对队列 Q 中每个元素调用函数 visit()。一旦 visit 失败，则操作失败
    Q.front = Q.front->next;
    while (Q.front) {
	Q.rear = Q.front->next;
	if (!visit(Q.front->data)) return ERROR;
	Q.front = Q.rear;
    }
    return OK;
}// QueueTraverse_L
