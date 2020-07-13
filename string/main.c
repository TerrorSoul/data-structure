#include <stdio.h>
#include <stdlib.h>

#include "../predefined.h"
#include "sstring.h"
#include "hstring.h"

void Print_S(SString S) {
    for (int i = 1; i <= S[0]; ++i) printf("%c", S[i]);
}

void Print_H(HString S) {
    for (int i = 0; i < S.length; ++i) printf("%c", S.ch[i]);
}

int main(int argc, char *argv[]) {
    // 串的定长顺序存储
    SString SStr;
    StrAssign_S(&SStr, "abcdefghijklmnopqrstuvwxyz");
    printf("SStr 的内容为：");
    Print_S(SStr);
    printf("\n");
    StrDelete_S(&SStr, 3, 5);
    printf("从串 SStr 中删除第 3 个字符起长度为 5 的子串后，内容为：");
    Print_S(SStr);
    printf("\n");
    DestroyString_S(&SStr);

    // 串的堆分配存储
    HString HStr = {NULL, 0};
    StrAssign_H(&HStr, "abcdefghijklmnopqrstuvwxyz");
    printf("HStr 的内容为：");
    Print_H(HStr);
    printf("\n");
    StrDelete_H(&HStr, 3, 5);
    printf("从串 HStr 中删除第 3 个字符起长度为 5 的子串后，内容为：");
    Print_H(HStr);
    printf("\n");
    DestroyString_H(&HStr);

    return 0;
}
