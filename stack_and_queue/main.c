#include <stdio.h>
#include <stdlib.h>

#include "../predefined.h"
typedef int SElemType;
typedef int QElemType;
#include "sqstack.h"
#include "linkqueue.h"
#include "sqqueue.h"

Status PrintSElem(SElemType e) {
    printf("%d ", e);
}// PrintSElem

Status PrintQElem(QElemType e) {
    printf("%d ", e);
}// PrintQElem

int main(int argc, char *argv[]) {
    // 栈
    SqStack S;
    InitStack(&S);
    for (int i = 0; i < 10; ++i) Push(&S, i);
    printf("栈的内容为：");
    StackTraverse(S, PrintSElem);
    printf("\n弹出 3 个元素后，栈的内容为：");
    int temp;
    for (int i = 0; i < 3; ++i) Pop(&S, &temp);
    StackTraverse(S, PrintSElem);
    GetTop(S, &temp);
    printf("\n栈顶元素为：%d\n", temp);
    DestroyStack(&S);

    // 单链队列
    LinkQueue LQ;
    InitQueue_L(&LQ);
    for (int i = 0; i < 10; ++i) EnQueue_L(&LQ, i);
    printf("单链队列的内容为：");
    QueueTraverse_L(LQ, PrintQElem);
    printf("\n弹出 3 个元素后，单链队列的内容为：");
    for (int i = 0; i < 3; ++i) DeQueue_L(&LQ, &temp);
    QueueTraverse_L(LQ, PrintQElem);
    GetHead_L(LQ, &temp);
    printf("\n队头元素为：%d\n", temp);
    DestroyQueue_L(&LQ);

    // 循环队列
    SqQueue SQ;
    InitQueue_Sq(&SQ);
    for (int i = 0; i < 10; ++i) EnQueue_Sq(&SQ, i);
    printf("循环队列的内容为：");
    QueueTraverse_Sq(SQ, PrintQElem);
    printf("\n弹出 3 个元素后，循环队列的内容为：");
    for (int i = 0; i < 3; ++i) DeQueue_Sq(&SQ, &temp);
    QueueTraverse_Sq(SQ, PrintQElem);
    GetHead_Sq(SQ, &temp);
    printf("\n队头元素为：%d\n", temp);
    DestroyQueue_Sq(&SQ);

    return 0;
}
