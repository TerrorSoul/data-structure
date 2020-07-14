#include <limits.h>
#include <string.h>

// - - - - - 赫夫曼树和赫夫曼编码的存储表示 - - - - -
typedef struct {
    unsigned int weight;
    unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;    // 动态分配数组存储赫夫曼树
typedef char **HuffmanCode;    // 动态分配数组存储赫夫曼编码表

//  - - - - - 求赫夫曼编码的算法描述 - - - - -
void HuffmanCoding(HuffmanTree *HT, HuffmanCode *HC, int *w, int n) {
    // w 存放 n 个字符的权值（均 > 0），构造赫夫曼树 HT，并求出 n 个字符的赫夫曼编码 HC
    if (n <= 1) return;
    int m = 2 * n - 1, i = 1;
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));    // 0 号单元未用
    HuffmanTree p = (*HT) + 1;
    for (; i <= n; ++i, ++p, ++w) {
	p->weight = *w;
	p->parent = p->lchild = p->rchild = 0;
    }
    for (; i <= m; ++i, ++p) {
	p->weight = p->parent = p->lchild = p->rchild = 0;
    }
    for (i = n + 1; i <= m; ++i) {
        // 在 HT[1..i-1]选择 parent 为 0 且 weight 最小的两个结点，其序号分别为 s1 和 s2
	int w1 = INT_MAX, s1, w2 = INT_MAX, s2;
	for (int j = 1; j < i; ++j) {
	    if ((*HT)[j].parent == 0) {
	        if ((*HT)[j].weight < w1) {
		    if (w1 < w2) {
		        w2 = w1;
			s2 = s1;
		    }
		    w1 = (*HT)[j].weight;
		    s1 = j;
	        }
	        else if ((*HT)[j].weight < w2) {
		    w2 = (*HT)[j].weight;
		    s2 = j;
	        }
	    }
	}
	(*HT)[s1].parent = i;
	(*HT)[s2].parent = i;
	(*HT)[i].lchild = s1;
	(*HT)[i].rchild = s2;
	(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
    // - - - - - 从叶子到根逆向求每个字符的赫夫曼编码 - - - - -
    *HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));    // 分配 n 个字符编码的头指针向量
    char *cd = (char *)malloc(n * sizeof(char));    // 分配求编码的工作空间
    cd[n - 1] = '\0';    // 编码结束符
    for (int i = 1; i <= n; ++i) {    // 逐个字符求赫夫曼编码
        int start = n - 1;
	for (int c = i, f = (*HT)[i].parent; f != 0; c = f, f = (*HT)[f].parent)    // 从叶子到根逆向求编码
	    if ((*HT)[f].lchild == c) cd[--start] = '0';
	    else cd[--start] = '1';
	(*HC)[i] = (char *)malloc((n - start) * sizeof(char));    // 为第 i 个字符编码分配空间
	strcpy((*HC)[i], &cd[start]);    // 从 cd 复制编码（串）到 HC
    }
    free(cd);
}// HuffmanCoding
