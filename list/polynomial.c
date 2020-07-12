#include <stdio.h>
#include <stdlib.h>

#include "../predefined.h"
#include "polynomial.h"

int main(int argc, char *argv[]) {
    polynomial P1, P2, P3, P4;
    CreatPolyn(&P1, 3);
    printf("一元多项式 P1 的内容为：");
    PrintPolyn(P1);
    printf("\n");
    CreatPolyn(&P2, 3);
    printf("一元多项式 P2 的内容为：");
    PrintPolyn(P2);
    printf("\n");
    CreatPolyn(&P3, 3);
    printf("一元多项式 P3 的内容为：");
    PrintPolyn(P3);
    printf("\n");
    CreatPolyn(&P4, 3);
    printf("一元多项式 P4 的内容为：");
    PrintPolyn(P4);
    printf("\n");
    AddPolyn(&P1, &P2);
    printf("P1 和 P2 相加得 P1 为：");
    PrintPolyn(P1);
    printf("\n");
    SubtractPolyn(&P1, &P3);
    printf("P1 和 P3 相减得 P1 为：");
    PrintPolyn(P1);
    printf("\n");
    MultiplyPolyn(&P1, &P4);
    printf("P1 和 P4 相乘得 P1 为：");
    PrintPolyn(P1);
    printf("\n");
    DestroyPolyn(&P1);

    return 0;
}
