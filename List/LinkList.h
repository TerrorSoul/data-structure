// 一个带头结点的线性链表类型定义如下
typedef struct LNode{    // 结点类型
    ElemType data;
    struct LNode *next;
}*Link, *Position;

typedef struct {    // 链表类型
    Link head, tail;    // 分别指向线性链表中的头结点和最后一个结点
    int len;    // 指示线性链表中数据元素的个数
}LinkList;

Status MakeNode(Link *p, ElemType e) {
    // 分配由 p 指向的值为 e 的结点，并返回 OK；若分配失败，则返回 ERROR
    *p = (Link)malloc(sizeof(struct LNode));
    if (!*p) return ERROR;
    (*p)->data = e;
    (*p)->next = NULL;
    return OK;
}// MakeNode

void FreeNode(Link *p) {
    // 释放 p 所指结点
    free(*p);
    *p = NULL;
}// FreeNode


Status InitList_L(LinkList *L) {
    // 构造一个空的线性链表 L
    if (!MakeNode(&L->head, 0)) return ERROR;
    L->tail = NULL;
    L->len = 0;
    return OK;
}// InitList_L

Status ClearList_L(LinkList*);
Status DestroyList_L(LinkList *L) {
    // 销毁线性链表 L，L不再存在
    ClearList_L(L);
    FreeNode(&L->head);
    return OK;
}// DestroyList_L

Status ClearList_L(LinkList *L) {
    // 将线性链表 L 重置为空表，并释放原链表的结点空间
    Link head = L->head;
    for (Link p = head->next, temp; p != NULL; p = temp) {
        temp = p->next;
	FreeNode(&p);
    }
    L->head->next = NULL;
    L->len = 0;
    return OK;
}// ClearList_L

Status InsFirst_L(Link h, Link s) {
    // 已知 h 指向线性链表的头结点，将 s 所指结点插入在第一个结点之前
    s->next = h->next;
    h->next = s;
    return OK;
}// InsFirst_L

Status DelFirst_L(Link h, Link *q) {
    // 已知 h 指向线性链表的头结点，删除链表中的第一个结点并以 q 返回
    *q = h->next;
    h->next = h->next->next;
    (*q)->next = NULL;
    return OK;
}// DelFirst_L

Status Append_L(LinkList *L, Link s) {
    // 将指针 s 所指（彼此以指针相链）的一串结点链接在线性链表 L 的最后一个结点
    // 之后，并改变链表 L 的尾指针指向新的尾结点
    if (L->tail == NULL) L->head->next = s;
    else L->tail->next = s;
    for (++L->len; s->next != NULL; s = s->next) ++L->len;
    L->tail = s;
    return OK;
}// Append_L

Status Remove_L(LinkList *L, Link *q) {
    // 删除线性链表 L 中的尾结点并以 q 返回，改变链表 L 的尾指针指向新的尾结点
    *q = L->tail;
    Link p = L->head;
    for (; p->next != L->tail; p = p->next);
    L->tail = p;
    --L->len;
    return OK;
}// Remove_L

Status InsBefore_L(LinkList *L, Link *p, Link s) {
    // 已知 p 指向线性链表 L 中的一个结点，将 s 所指结点插入在 p 所指结点之前，
    // 并修改指针 p 指向新插入的结点
    Link q = L->head;
    for (; q->next != *p; q = q->next);
    q->next = s;
    s->next = *p;
    ++L->len;
    *p = s;
    return OK;
}// InsBefore_L

Status InsAfter_L(LinkList *L, Link *p, Link s) {
    // 已知 p 指向线性链表 L 中的一个结点，将 s 所指结点插入在 p 所指结点之后，
    // 并修改指针 p 指向新插入的结点
    s->next = (*p)->next;
    (*p)->next = s;
    if (L->tail == *p) L->tail = s;
    ++L->len;
    *p = s;
    return OK;
}// InsAfter_L

Status SetCurElem_L(Link *p, ElemType e) {
    // 已知 p 指向线性链表中的一个结点，用 e 更新 p 所指结点中数据元素的值
    (*p)->data = e;
    return OK;
}// SetCurElem_L

ElemType GetCurElem_L(Link p) {
    // 已知 p 指向线性链表中的一个结点，返回 p 所指结点中数据元素的值
    return p->data;
}// GetCurElem_L

Status ListEmpty_L(LinkList L) {
    // 若线性链表 L 为空表，则返回 TRUE，否则返回 FALSE
    return L.len == 0 ? TRUE : FALSE;
}// ListEmpty_L

int ListLength_L(LinkList L) {
    // 返回线性链表 L 中元素个数
    return L.len;
}// ListLength_L

Position GetHead_L(LinkList L) {
    // 返回线性链表 L 中头结点的位置
    return L.head;
}// GetHead_L

Position GetLast_L(LinkList L) {
    // 返回线性链表 L 中最后一个结点的位置
    return L.tail;
}// GetLast_L

Position PriorPos_L(LinkList L, Link p) {
    // 已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接前驱的位置，
    // 若无前驱，则返回NULL
    Link prior = NULL;
    for (Link cur = L.head; cur != p; prior = cur, cur = prior->next);
    return prior;
}// PriorPos_L

Position NextPos_L(LinkList L, Link p) {
    // 已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接后继的位置，
    // 若无后继，则返回NULL
    return p->next;
}// NextPos_L

Status LocatePos_L(LinkList L, int i, Link *p) {
    // 返回 p 指示线性链表 L 中第 i 个结点的位置并返回 OK，i 值不合法时返回 ERROR
    if (i < 0 || i > L.len) return ERROR;
    *p = L.head;
    for (int j = 1; j <= i; ++j) *p = (*p)->next;
    return OK;
}// LocatePos_L

Position LocateElem_L(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType)) {
    // 返回线性链表 L 中第 1 个与 e 满足函数 compare() 判定关系的元素的位置，
    // 若不存在这样的元素，则返回 NULL
    Link p = L.head;
    for (p = p->next; p != NULL; p = p->next)
	if (compare(p->data, e)) break;
    return p;
}// LocateElem_L

Status ListTraverse_L(LinkList L, Status (*visit)()) {
    // 依次对 L 的每个元素调用函数 visit()。一旦 visit() 失败，则操作失败。
    Link p = L.head;
    for (p = p->next; p != NULL; p = p->next)
	if (!visit(p->data)) return ERROR;
    return OK;
}// ListTraverse_L

Status ListInsert_L(LinkList *L, int i, ElemType e) {
    // 在带头结点的单链线性表 L 的第 i 个元素之前插入元素 e
    Link h, s;
    if (!LocatePos_L(*L, i - 1, &h)) return ERROR;    // i 值不合法
    if (!MakeNode(&s, e)) return ERROR;    // 结点存储分配失败
    InsFirst_L(h, s);    // 对于从第 i 个结点开始的链表，第 i - 1 个结点是它的头结点
    if (++L->len == 1) L->tail = s;
    return OK;
}// ListInsert_L

Status MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc, int (*compare)(ElemType, ElemType)) {
    // 已知单链线性表 La 和 Lb 的元素按值非递减排列
    // 归并 La 和 Lb 得到新的单链线性表 Lc，Lc 的元素也按值非递减排列。
    if (!InitList_L(Lc)) return ERROR;    // 存储空间分配失败
    Position ha = GetHead_L(*La), hb = GetHead_L(*Lb);    // ha 和 hb 分别指向 La 和 Lb 的头结点
    Position pa = NextPos_L(*La, ha), pb = NextPos_L(*Lb, hb), q;    // pa 和 pb 分别指向 La 和 Lb 中当前结点
    while (pa && pb) {    // La 和 Lb 均非空
        ElemType a = GetCurElem_L(pa), b = GetCurElem_L(pb);    // a 和 b 为两表中当前比较元素
	if (compare(a, b) <= 0) {    // a <= b
	    DelFirst_L(ha, &q);
	    Append_L(Lc, q);
	    pa = NextPos_L(*La, ha);
	} else {    // a > b
	    DelFirst_L(hb, &q);
	    Append_L(Lc, q);
	    pb = NextPos_L(*Lb, hb);
	}
    }// while
    if (pa) Append_L(Lc, pa);    // 链接 La 中剩余结点
    else Append_L(Lc, pb);    // 链接 Lb 中剩余结点
    FreeNode(&ha);
    FreeNode(&hb);    // 释放 La 和 Lb 的头结点
    return OK;
}// MergeList_L
