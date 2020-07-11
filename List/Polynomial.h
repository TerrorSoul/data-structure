#include <stdio.h>
#include <stdlib.h>

typedef struct {    // 项的表示，多项式的项作为 LinkList 的数据元素
    float coef;    // 系数
    int expn;    // 指数
}term, ElemType;    // 两个类型名，term 用于本 ADT，ElemType 为 LinkList 的数据对象名
#include "LinkList.h"

typedef LinkList polynomial;    // 用带头结点的有序链表表示多项式

// - - - - - 基本操作的算法描述 - - - - -
Status compare(term a, term b) {
    // 依 a 的指数值 < (或 =)(或 >) b 的指数值，分别返回 -1、0 和 +1
    return a.expn >= b.expn ? TRUE : FALSE;
}// cmp
void CreatPolyn(polynomial *P, int m) {
    // 输入 m 项的系数和指数，建立表示一元多项式的有序链表 P
    InitList_L(P);
    Link h = GetHead_L(*P), q, s;
    term e = {0.0, -1};
    SetCurElem_L(&h, e);    // 设置头结点的数据元素
    for (int i = 1; i <= m; ++i) {    // 依次输入 m 个非零项
	printf("请输入第 %d 项的系数和指数：", i);
	scanf("%f %d", &e.coef, &e.expn);
	MakeNode(&s, e);
	if (q = LocateElem_L(*P, e, compare))    // 当前链表中不存在该指数项
	    InsBefore_L(P, &q, s);    // 生成结点并插入链表
	else {
	    Append_L(P, s);
	}
    }
}// CreatPolyn

void DestroyPolyn(polynomial *P) {
    // 销毁一元多项式 P
    DestroyList_L(P);
}// DestroyPolyn

Status printPolyn(Link p) {
    printf("(%.1f)x^%d ", p->data.coef, p->data.expn);
}
void PrintPolyn(polynomial P) {
    // 打印输出一元多项式 P
    ListTraverse_L(P, printPolyn);
}// PrintPolyn

int PolynLength(polynomial P) {
    // 返回一元多项式 P 中的项数
    return P.len;
}// PolynLength

int cmp(term a, term b) {
    // 依 a 的指数值 < (或 =)(或 >) b 的指数值，分别返回 -1、0 和 +1
    return a.expn < b.expn ? -1 : a.expn == b.expn ? 0 : 1;
}// cmp
void AddPolyn(polynomial *Pa, polynomial *Pb) {
    // 完成多项式相加运算，即：Pa = Pa + Pb，并销毁一元多项式 Pb
    Link ha = GetHead_L(*Pa), hb = GetHead_L(*Pb);    // ha 和 hb 分别指向 Pa 和 Pb 的头结点
    Link qa = NextPos_L(*Pa, ha), qb = NextPos_L(*Pb, hb);    // qa 和 qb 分别指向 Pa 和 Pb 中当前结点
    while (qa && qb) {    // qa 和 qb 均非空
        ElemType a = GetCurElem_L(qa), b = GetCurElem_L(qb);    // a 和 b 为两表中当前比较元素
	switch (cmp(a, b)) {
	    case -1:    // 多项式 PA 中当前结点的指数值小
		ha = qa;
		qa = NextPos_L(*Pa, qa);
		break;
	    case 0: {    // 两者的指数值相等
                term sum = {a.coef + b.coef, a.expn};
		if (sum.coef != 0.0) {    // 修改多项式 PA 中当前结点的系数值
		    SetCurElem_L(&qa, sum);
		    ha = qa;
		} else {    // 删除多项式 PA 中当前结点
		    DelFirst_L(ha, &qa);
		    FreeNode(&qa);
		    --Pa->len;
		}
		DelFirst_L(hb, &qb);
		FreeNode(&qb);
                --Pb->len;
		qb = NextPos_L(*Pb, hb);
		qa = NextPos_L(*Pa, ha);
		break;
	    }
	    case 1:    // 多项式 PB 中当前结点的指数值小
		DelFirst_L(hb, &qb);
		InsFirst_L(ha, qb);
		--Pb->len;
		qb = NextPos_L(*Pb, hb);
		ha = NextPos_L(*Pa, ha);
		break;
	}// switch
    }// while
    if (!ListEmpty_L(*Pb)) Append_L(Pa, qb);    // 链接Pb 中剩余结点
    FreeNode(&hb);    // 释放 Pb 的头结点
}// AddPolyn

Status CoefNegative(Link p) {
    // 将 p 所指结点的系数变为其相反数
    p->data.coef *= -1;
    return OK;
}// MultiplyInt
void SubtractPolyn(polynomial *Pa, polynomial *Pb) {
    // 完成多项式相减运算，即：Pa = Pa - Pb，并销毁一元多项式 Pb
    ListTraverse_L(*Pb, CoefNegative);
    AddPolyn(Pa, Pb);
}// SubtractPolyn

polynomial* multiply(polynomial *Pa, Link q) {
    polynomial *Pb = (polynomial*)malloc(sizeof(polynomial));
    InitList_L(Pb);
    Link qa = GetHead_L(*Pa), qb = GetHead_L(*Pb), s;
    ElemType e = {0.0, -1};
    SetCurElem_L(&qb, e);    // 设置头结点的数据元素
    while (qa = NextPos_L(*Pa, qa)) {
       e = GetCurElem_L(qa);
       e.coef *= q->data.coef;
       e.expn += q->data.expn;
       MakeNode(&s, e);
       Append_L(Pb, s);
    }// while
    return Pb;
}// multiply
void MultiplyPolyn(polynomial *Pa, polynomial *Pb) {
    // 完成多项式相乘运算，即：Pa = Pa x Pb，并销毁一元多项式 Pb
    Link qb = GetHead_L(*Pb);
    qb = NextPos_L(*Pb, qb);
    polynomial *result = multiply(Pa, qb);
    while (qb = NextPos_L(*Pb, qb)) {
        polynomial *temp = multiply(Pa, qb);
	AddPolyn(result, temp);
    }// while
    DestroyPolyn(Pa);
    DestroyPolyn(Pb);
    *Pa = *result;
}// MultiplyPolyn
