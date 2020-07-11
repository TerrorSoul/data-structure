#include <stdio.h>
#include <stdlib.h>

#include "predefined.h"
typedef int ElemType;
#include "List/SqList.h"
#include "List/LinkList.h"

Status PrintElem(ElemType e) {
    printf("%d ", e);
    return OK;
}// PrintElem

int compare(ElemType e1, ElemType e2) {
    return e1 < e2 ? -1 : e1 == e2 ? 0 : 1;
}// compare

int main(int argc, char *argv[]) {
    SqList sqList;
    InitList_Sq(&sqList);
    for (int i = 0; i < 10; ++i) ListInsert_Sq(&sqList, i + 1, i);
    int length = ListLength_Sq(sqList);
    printf("顺序线性表的长度为：%d\n", length);
    printf("顺序线性表的内容为：");
    ListTraverse_Sq(sqList, PrintElem);
    printf("\n");
    DestroyList_Sq(&sqList);

    LinkList linkList1, linkList2, linkList3;
    InitList_L(&linkList1);
    InitList_L(&linkList2);
    for (int i = 0; i < 10; ++i) {
        Link p;
	MakeNode(&p, i);
	Append_L(&linkList1, p);
    }
    length = ListLength_L(linkList1);
    printf("线性链表1的长度为：%d\n", length);
    printf("线性链表1的内容为：");
    ListTraverse_L(linkList1, PrintElem);
    printf("\n");
    for (int i = 0; i < 10; ++i)
        ListInsert_L(&linkList2, i + 1, i * i);
    length = ListLength_L(linkList2);
    printf("线性链表2的长度为：%d\n", length);
    printf("线性链表2的内容为：");
    ListTraverse_L(linkList2, PrintElem);
    printf("\n");
    if (MergeList_L(&linkList1, &linkList2, &linkList3, compare)) {
        length = ListLength_L(linkList3);
        printf("线性链表3的长度为：%d\n", length);
        printf("线性链表3的内容为：");
        ListTraverse_L(linkList3, PrintElem);
        printf("\n");
    }

    return 0;
}
