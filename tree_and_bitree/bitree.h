// - - - - - 二叉树的二叉链表存储表示 - - - - -
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;    // 左右孩子指针
}BiTNode, *BiTree;

typedef BiTree SElemType;
typedef BiTree QElemType;
#include "../stack_and_queue/sqstack.h"
#include "../stack_and_queue/linkqueue.h"

// - - - - - 基本操作的算法描述 - - - - -
Status InitBiTree(BiTree *T) {
    // 构造空二叉树 T
    if(!(*T = (BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
    (*T)->lchild = NULL;
    (*T)->rchild = NULL;
    return OK;
}// InitBiTree

Status DestroyBiTree(BiTree *T) {
    // 销毁二叉树 T
    if ((*T)->lchild) DestroyBiTree(&((*T)->lchild));
    if ((*T)->rchild) DestroyBiTree(&((*T)->rchild));
    free(*T);
    *T = NULL;
}// DestroyBiTree

Status CreatBiTree(BiTree *T) {
    // 按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树，
    // 构造二叉链表表示的二叉树 T
    char ch;
    scanf("%c", &ch);
    if (ch == ' ') *T = NULL;
    else {
        if (!(*T = (BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
	(*T)->data = ch;    // 生成根结点
	CreatBiTree(&(*T)->lchild);    // 构造左子树
	CreatBiTree(&(*T)->rchild);    // 构造右子树
    }
    return OK;
}// CreatBiTree

Status ClearBiTree(BiTree *T) {
    // 将二叉树 T 清为空树
    DestroyBiTree(T);
}// ClearBiTree

Status BiTreeEmpty(BiTree T) {
    // 若 T 为空二叉树，则返回 TRUE，否则返回 FALSE
    return T == NULL ? TRUE : FALSE;
}// BiTreeEmpty

int depth(BiTree T, int d) {
    if (T == NULL) return d;
    else {
        int ld = depth(T->lchild, d + 1), rd = depth(T->rchild, d + 1);
	return ld > rd ? ld : rd;
    }
}// depth
int BiTreeDepth(BiTree T) {
    // 返回 T 的深度
    return depth(T, 0);
}// BiTreeDepth

BiTree Root(BiTree T) {
    // 返回 T 的根
    return T;
}// Root

TElemType Value(BiTree T, BiTree e) {
    // 返回 e 的值
    return e->data;
}// Value

Status Assign(BiTree T, BiTree *e, TElemType value) {
    // 结点 e 赋值为 value
    (*e)->data = value;
    return OK;
}// Assign

BiTree Parent(BiTree T, BiTree e) {
    // 若 e 是 T 的非根结点，则返回它的双亲，否则返回“空”
    if (T == NULL || T == e) return NULL;
    else if (T->lchild == e || T ->rchild == e) return T;
    else {
        BiTree lp = Parent(T->lchild, e), rp = Parent(T->rchild, e);
	return lp == NULL ? rp : lp;
    }
}// Parent

BiTree LeftChild(BiTree T, BiTree e) {
    // 返回 e 的左孩子。若 e 无左孩子，则返回“空”
    return e->lchild;
}// LeftChild

BiTree RightChild(BiTree T, BiTree e) {
    // 返回 e 的右孩子。若 e 无右孩子，则返回“空”
    return e->rchild;
}// RightChild

BiTree LeftSibling(BiTree T, BiTree e) {
    // 返回 e 的左兄弟。若 e 是 T 的左孩子或无左兄弟，则返回“空”
    BiTree parent = Parent(T, e);
    if (parent == NULL || parent->lchild == e) return NULL;
    else return parent->lchild;
}// LeftSibling

BiTree RightSibling(BiTree T, BiTree e) {
    // 返回 e 的右兄弟。若 e 是 T 的右孩子或无右兄弟，则返回“空”
    BiTree parent = Parent(T, e);
    if (parent == NULL || parent->rchild == e) return NULL;
    else return parent->rchild;
}// RightSibling

Status InsertChild(BiTree T, BiTree p, int LR, BiTree c) {
    // 根据 LR 为 0 或 1，插入 c 为 T 中 p 所指结点的左或右子树。p 所指结点的原有左或右子树则成为 c 的右子树
    BiTree temp;
    if (LR == 0) {
        temp = p->lchild;
	p->lchild = c;
    } else {
        temp = p->rchild;
	p->rchild = c;
    }
    if (temp == NULL) return OK;
    else return InsertChild(T, c, 1, temp);
}// InsertChild

Status DeleteChild(BiTree T, BiTree p, int LR) {
    // 根据 LR 为 0 或 1，删除 T 中 p 所指结点的左或右子树
    if (LR == 0) {
        DestroyBiTree(&p->lchild);
        p->lchild = NULL;
    } else {
        DestroyBiTree(&p->rchild);
	p->rchild = NULL;
    }
    return OK;
}// DeleteChild

Status PreOrderTraverse_R(BiTree T, Status (*visit)(TElemType e)) {
    // 采用二叉链表存储结构，visit 是对结点操作的应用函数
    // 先序遍历二叉树 T 的递归算法，对每个结点调用函数 visit 一次且仅一次
    // 一旦 visit() 失败，则操作失败
    if (T) {
        if (visit(T->data))
	    if (PreOrderTraverse_R(T->lchild, visit))
		if (PreOrderTraverse_R(T->rchild, visit))
	            return OK;
	return ERROR;
    } else return OK;
}// PreOrderTraverse_R

Status InOrderTraverse_R(BiTree T, Status (*visit)(TElemType e)) {
    // 采用二叉链表存储结构，visit 是对结点操作的应用函数
    // 中序遍历二叉树 T 的递归算法，对每个结点调用函数 visit 一次且仅一次
    // 一旦 visit() 失败，则操作失败
    if (T) {
        if (InOrderTraverse_R(T->lchild, visit))
	    if (visit(T->data))
		if (InOrderTraverse_R(T->rchild, visit))
	            return OK;
	return ERROR;
    } else return OK;
}// InOrderTraverse_R

Status PostOrderTraverse_R(BiTree T, Status (*visit)(TElemType e)) {
    // 采用二叉链表存储结构，visit 是对结点操作的应用函数
    // 后序遍历二叉树 T 的递归算法，对每个结点调用函数 visit 一次且仅一次
    // 一旦 visit() 失败，则操作失败
    if (T) {
        if (PostOrderTraverse_R(T->lchild, visit))
	    if (PostOrderTraverse_R(T->rchild, visit))
		if (visit(T->data))
	            return OK;
	return ERROR;
    } else return OK;
}// PostOrderTraverse_R

Status PreOrderTraverse_I(BiTree T, Status (*visit)(TElemType e)) {
    // 采用二叉链表存储结构，visit 是对结点操作的应用函数
    // 先序遍历二叉树 T 的迭代算法，对每个结点调用函数 visit 一次且仅一次
    // 一旦 visit() 失败，则操作失败
    SqStack S;
    InitStack(&S);
    Push(&S, T);    // 根指针进栈
    BiTree p;
    while (!StackEmpty(S)) {
        Pop(&S, &p);
	if (!visit(p->data)) return ERROR;
	if (p->rchild) Push(&S, p->rchild);
	if (p->lchild) Push(&S, p->lchild);
    }
}// PreOrderTraverse_I

Status InOrderTraverse_I1(BiTree T, Status (*visit)(TElemType e)) {
    // 采用二叉链表存储结构，visit 是对结点操作的应用函数
    // 中序遍历二叉树 T 的迭代算法，对每个结点调用函数 visit 一次且仅一次
    // 一旦 visit() 失败，则操作失败
    SqStack S;
    InitStack(&S);
    Push(&S, T);    // 根指针进栈
    BiTree p;
    while (!StackEmpty(S)) {
        while (GetTop(S, &p) && p) Push(&S, p->lchild);    // 向左走到尽头
	Pop(&S, &p);    // 空指针退栈
	if (!StackEmpty(S)) {    // 访问结点，向右一步
	    Pop(&S, &p);
	    if (!visit(p->data)) return ERROR;
	    Push(&S, p->rchild);
	}// if
    }// while
    return OK;
}// InOrderTraverse_I1

Status InOrderTraverse_I2(BiTree T, Status (*visit)(TElemType e)) {
    // 采用二叉链表存储结构，visit 是对结点操作的应用函数
    // 中序遍历二叉树 T 的迭代算法，对每个结点调用函数 visit 一次且仅一次
    // 一旦 visit() 失败，则操作失败
    SqStack S;
    InitStack(&S);
    BiTree p = T;
    while (p || !StackEmpty(S)) {
        if (p) {
	    Push(&S, p);
	    p = p->lchild;    // 根指针进栈，遍历左子树
	} else {    // 根指针退栈，访问根结点，遍历右子树
	    Pop(&S, &p);
	    if (!visit(p->data)) return ERROR;
	    p = p->rchild;
	}// else
    }// while
    return OK;
}// InOrderTraverse_I2
	
Status PostOrderTraverse_I(BiTree T, Status (*visit)(TElemType e)) {
    // 采用二叉链表存储结构，visit 是对结点操作的应用函数
    // 后序遍历二叉树 T 的迭代算法，对每个结点调用函数 visit 一次且仅一次
    // 一旦 visit() 失败，则操作失败
    SqStack S;
    InitStack(&S);
    BiTree p = T, r;
    while (p || !StackEmpty(S)) {
	if (p) {
	    Push(&S, p);
	    p = p->lchild;    // 根指针进栈，遍历左子树
	} else {
	    GetTop(S, &p);
	    if (p->rchild && p->rchild != r)    // 右子树存在，未被访问
		p = p->rchild;
	    else {
	        Pop(&S, &p);
		if (!visit(p->data)) return ERROR;
		r = p;
		p = NULL;
	    }
	}
    }// while
    return OK;
}// PostOrderTraverse_I

Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e)) {
    // 采用二叉链表存储结构，visit 是对结点操作的应用函数
    // 层序遍历二叉树 T，对每个结点调用函数 visit 一次且仅一次
    // 一旦 visit() 失败，则操作失败
    LinkQueue Q;
    InitQueue_L(&Q);
    EnQueue_L(&Q, T);
    BiTree p;
    while (!QueueEmpty_L(Q)) {
        DeQueue_L(&Q, &p);
	if (!visit(p->data)) return ERROR;
	if (p->lchild) EnQueue_L(&Q, p->lchild);
	if (p->rchild) EnQueue_L(&Q, p->rchild);
    }// while
    return OK;
}// LevelOrderTraverse

