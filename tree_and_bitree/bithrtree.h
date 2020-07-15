// - - - - - 二叉树的二叉线索存储表示 - - - - -
typedef enum { Link, Thread }PointerTag;    // Link == 0：指针，Thread == 1：线索
typedef struct BiThrNode {
    TElemType data;
    struct BiThrNode *lchild, *rchild;    // 左右孩子指针
    PointerTag LTag, RTag;    // 左右标志
}BiThrNode, *BiThrTree;

Status CreateBiThrTree(BiThrTree *T) {
    // 按先序次序输入二叉线索树中结点的值（一个字符），空格字符表示空树，
    // 构造二叉链表表示的二叉线索树 T
    char ch;
    scanf("%c", &ch);
    if (ch == ' ') *T = NULL;
    else {
        if (!(*T = (BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
	(*T)->data = ch;    // 生成根结点
	CreateBiThrTree(&(*T)->lchild);    // 构造左子树
	CreateBiThrTree(&(*T)->rchild);    // 构造右子树
	if ((*T)->lchild) (*T)->LTag = Link;
	if ((*T)->rchild) (*T)->RTag = Link;
    }
    return OK;
}// CreateBiThrTree

Status InOrderTraverse_Thr(BiThrTree T, Status (*visit)(TElemType e)) {
    // T 指向头结点，头结点的左链 lchild 指向根结点，可参见线索化算法
    // 中序遍历二叉线索树 T 的非递归算法，对每个数据元素调用函数 visit
    BiThrTree p = T->lchild;    // p 指向根结点
    while (p != T) {    // 空树或遍历结束时，p == T
        while (p->LTag == Link) p = p->lchild;
	if (!visit(p->data)) return ERROR;    // 访问其左子树为空的结点
	while (p->RTag == Thread && p->rchild != T) {
	    p = p->rchild;
	    if (!visit(p->data)) return ERROR;    // 访问后继结点
	}
	p = p->rchild;
    }
    return OK;
}// InOrderTraverse_Thr

void InThreading(BiThrTree p, BiThrTree *pre) {
    if (p) {
        InThreading(p->lchild, pre);    // 左子树线索化
	if (!p->lchild) {    // 前驱线索
	    p->LTag = Thread;
	    p->lchild = *pre;
	}
	if (!(*pre)->rchild) {    // 后继线索
	    (*pre)->RTag = Thread;
	    (*pre)->rchild = p;
	}
	*pre = p;    // 保持 pre 指向 p 的前驱
	InThreading(p->rchild, pre);    // 右子树线索化
    }
}// InThreading

Status InOrderThreading(BiThrTree *Thrt, BiThrTree T) {
    // 中序遍历二叉树 T，并将其中序线索化，Thrt 指向头结点
    if (!(*Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);    // 建头结点
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;
    (*Thrt)->rchild = *Thrt;    // 右指针回指
    if (!T) (*Thrt)->lchild = *Thrt;    // 若二叉树空，则左指针回指
    else {
        (*Thrt)->lchild = T;
	BiThrTree pre = *Thrt;
	InThreading(T, &pre);    // 中序遍历进行中序线索化
	pre->rchild = *Thrt;
	pre->RTag = Thread;    // 最后一个结点线索化
	(*Thrt)->rchild = pre;
    }
    return OK;
}// InOrderThreading
