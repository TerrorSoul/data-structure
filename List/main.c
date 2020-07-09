#include "SqList.h"

int main(int argc, char *argv[]) {
    SqList L;
    InitList_Sq(&L);
    for (int i = 0; i < 10; ++i) ListInsert_Sq(&L, i + 1, i);
    
    int length = ListLength_Sq(L);
    printf("顺序线性表的长度为：%d\n", length);
    printf("顺序线性表的内容为：");
    for (int i = 1; i <= length; ++i) {
        int e;
	GetElem_Sq(L, i, &e);
	printf("%d ", e);
    }
    printf("\n");

    DestroyList_Sq(&L);

    return 0;
}
