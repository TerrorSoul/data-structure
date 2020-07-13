// - - - - - 栈的顺序存储表示 - - - - -
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef struct {
    SElemType *base;    // 在栈构造之前和销毁之后，base 的值为 NULL
    SElemType *top;    // 栈顶指针
    int stacksize;    // 当前已分配的存储空间，以元素为单位
}SqStack;

// - - - - - 基本操作的算法描述 - - - - -
Status InitStack(SqStack *S) {
    // 构造一个空栈 S
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S->base) exit(OVERFLOW);    // 存储分配失败
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}// InitStack

Status DestroyStack(SqStack *S) {
    // 销毁栈 S，S 不再存在
    free(S->base);
    S->base = NULL;
    S->top = S->base;
    S->stacksize = 0;
    return OK;
}// DestroyStack

Status ClearStack(SqStack *S) {
    // 把 S 置为空栈
    S->top = S->base;
}// ClearStack

Status StackEmpty(SqStack S) {
    // 若栈 S 为空栈，则返回 TRUE，否则返回 FALSE
    return S.top == S.base ? TRUE : FALSE;
}// StackEmpty

int StackLength(SqStack S) {
    // 返回 S 的元素个数，即栈的长度
    return S.top - S.base;
}// StackLength

Status GetTop(SqStack S, SElemType *e) {
    // 若栈不空，则用 e 返回 S 的栈顶元素，并返回 OK；否则返回 ERROR
    if (StackEmpty(S)) return ERROR;
    *e = *(S.top - 1);
    return OK;
}// GetTop

Status Push(SqStack *S, SElemType e) {
    // 插入元素 e 为新的栈顶元素
    if (StackLength(*S) >= S->stacksize) {    // 栈满，追加存储空间
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
	if (!S->base) exit(OVERFLOW);    // 存储分配失败
	S->top = S->base + S->stacksize;
	S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;
    return OK;
}// Push

Status Pop(SqStack *S, SElemType *e) {
    // 若栈不空，则删除 S 的栈顶元素，用 e 返回其值，并返回 OK；否则返回 ERROR
    if (StackEmpty(*S)) return ERROR;
    *e = *--S->top;
    return OK;
}// Pop

Status StackTraverse(SqStack S, Status(*visit)()) {
    // 从栈底到栈顶依次对栈中每个元素调用函数 visit()。一旦 visit() 失败，则操作失败
    while (S.base != S.top) {
        if (!visit(*(S.base++))) return ERROR;
    }
    return OK;
}// StackTraverse
