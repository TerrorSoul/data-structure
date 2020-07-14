#include <stdio.h>
#include <stdlib.h>

#include "../predefined.h"
typedef char TElemType;
#include "bitree.h"
#include "huffmantree.h"

Status PrintTElem(TElemType e) {
    printf("%c", e);
}// PrintTElem

int main(int argc, char *argv[]) {
    // 二叉树	
    BiTree T;
    CreatBiTree(&T);
    printf("递归的先序遍历结果为：");
    PreOrderTraverse_R(T, PrintTElem);
    printf("\n");
    printf("递归的中序遍历结果为：");
    InOrderTraverse_R(T, PrintTElem);
    printf("\n");
    printf("递归的后序遍历结果为：");
    PostOrderTraverse_R(T, PrintTElem);
    printf("\n");
    printf("迭代的先序遍历结果为：");
    PreOrderTraverse_I(T, PrintTElem);
    printf("\n");
    printf("迭代的中序遍历结果1为：");
    InOrderTraverse_I1(T, PrintTElem);
    printf("\n");
    printf("迭代的中序遍历结果2为：");
    InOrderTraverse_I2(T, PrintTElem);
    printf("\n");
    printf("迭代的后序遍历结果为：");
    PostOrderTraverse_I(T, PrintTElem);
    printf("\n");
    printf("迭代的层序遍历结果为：");
    LevelOrderTraverse(T, PrintTElem);
    printf("\n\n");

    // 求赫夫曼编码
    int w[] = {5, 29, 7, 8, 14, 23, 3, 11};
    HuffmanTree HT;
    HuffmanCode HC;
    HuffmanCoding(&HT, &HC, w, 8);
    for (int i = 0; i < 8; ++i) printf("%d ", w[i]);
    printf("的赫夫曼编码为：\n");
    for (int i = 1; i <= 8; ++i) printf("%d：%s\n", i, HC[i]);
    free(HT);
    free(HC);

    return 0;
}
