// - - - - - 线性表的动态分配顺序存储结构 - - - - -
#define LIST_INIT_SIZE 100    // 线性表存储空间的初始分配量
#define LISTINCREMENT 10    // 线性表存储空间的分配增量
typedef struct {
    ElemType *elem;    // 存储空间基址
    int length;    // 当前长度
    int listsize;    // 当前分配的存储容量（以 sizeof(ElemType)为单位）
}SqList;

Status InitList_Sq(SqList *L) {
    // 构造一个空的线性表 L。
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L->elem) exit(OVERFLOW);    // 存储分配失败
    L->length = 0;    // 空表长度为 0
    L->listsize = LIST_INIT_SIZE;    // 初始存储容量
    return OK;
}// InitList_Sq

Status DestroyList_Sq(SqList *L) {
    // 销毁线性表 L。
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    return OK;
}// DestroyList_Sq

Status ClearList_Sq(SqList *L) {
    // 将 L 重置为空表。
    L->length = 0;
    return OK;
}// ClearList_Sq

int ListEmpty_Sq(SqList L) {
    // 若 L 为空表，则返回 TRUE，否则返回 FALSE。
    return L.length == 0 ? TRUE : FALSE;
}// ListEmpty_Sq

int ListLength_Sq(SqList L) {
    // 返回 L 中数据元素个数。
    return L.length;
}// ListLength_Sq

Status GetElem_Sq(SqList L, int i, ElemType *e) {
    // 用 e 返回 L 中第 i 个数据元素的值。
    *e = L.elem[i - 1];
    return OK;
}// GetElem_Sq

int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType)) {
    // 在顺序线性表 L 中查找第 1 个值与 e 满足 compare() 的元素的位序
    // 若找到，则返回其在 L 中的位序，否则返回 0
    int i = 1;    // i 的初值为第 1 个元素的位序
    ElemType *p = L.elem;    // p 的初值为第 1 个元素的存储位置
    while (i <= L.length && !(*compare)(*p++, e)) ++i;
    if (i <= L.length) return i;
    else return 0;
}// LocateElem_Sq

Status equal(ElemType e1, ElemType e2) {
    return e1 == e2 ? TRUE : FALSE;
}// equal
Status PriorElem_Sq(SqList L, ElemType cur_e, ElemType *pre_e) {
    // 若 cur_e 是 L 的数据元素，且不是第一个，则用 pre_e 返回它的前驱，否则操作失败，pre_e 无定义
    int i = LocateElem_Sq(L, cur_e, equal);
    if (i > 1) {
        GetElem_Sq(L, i - 1, pre_e);
	return OK;
    } else return ERROR;
}// PriorElem_Sq

Status NextElem_Sq(SqList L, ElemType cur_e, ElemType *next_e) {
    // 若 cur_e 是 L 的数据元素，且不是最后一个，则用 next_e 返回它的后继，否则操作失败，next_e 无定义
    int i = LocateElem_Sq(L, cur_e, equal);
    if (i < L.length) {
        GetElem_Sq(L, i + 1, next_e);
	return OK;
    } else return ERROR;
}// NextElem_Sq

Status ListInsert_Sq(SqList *L, int i, ElemType e) {
    // 在顺序线性表 L 中第 i 个位置之前插入新的元素 e，
    // i 的合法值为 1 <= i <= ListLength_Sq(L) + 1
    if (i < 1 || i > L->length + 1) return ERROR;    // i 值不合法
    if (L->length >= L->listsize) {    // 当前存储空间已满，增加分配
	ElemType *newbase = (ElemType *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
	if (!newbase) exit(OVERFLOW);    // 存储分配失败
	L->elem = newbase;    // 新基址
	L->listsize += LISTINCREMENT;    // 增加存储容量
    }
    ElemType *q = &(L->elem[i - 1]);    // q 为插入位置
    for (ElemType *p = &(L->elem[L->length - 1]); p >= q; --p) *(p + 1) = *p;    // 插入位置及之后的元素右移
    *q = e;    // 插入 e
    ++L->length;    // 表长增 1
    return OK;
}// ListInsert_Sq

Status ListDelete_Sq(SqList *L, int i, ElemType *e) {
    // 在顺序线性表 L 中删除第 i 个元素，并用 e 返回其值
    // i 的合法值为 1 <= i <= ListLength_Sq(L)
    if (i < 1 || i > L->length) return ERROR;    // i 值不合法
    ElemType *p = &(L->elem[i - 1]);    // p 为被删除元素的位置
    *e = *p;    // 被删除元素的值赋给 e
    ElemType *q = L->elem + L->length - 1;    // 表尾元素的位置
    for (++p; p <= q; ++p) *(p - 1) = *p;    // 被删除元素之后的元素左移
    --L->length;    // 表长减 1
    return OK;
}// ListDelete_Sq

Status ListTraverse_Sq(SqList L, Status (*visit)()) {
    // 依次对 L 的每个数据元素调用函数 visit()。一旦 visit() 失败，则操作失败。
    ElemType *q = L.elem + L.length - 1;
    for (ElemType *p = L.elem; p <= q; ++p)
	if (!visit(p)) return ERROR;
    return OK;
}// ListTraverse_Sq

void MergeList_Sq(SqList La, SqList Lb, SqList *Lc) {
    // 已知顺序线性表 La 和 Lb 的元素按值非递减排列
    // 归并 La 和 Lb 得到新的顺序线性表 Lc，Lc 的元素也按值非递减排列
    ElemType *pa = La.elem, *pb = Lb.elem;
    Lc->listsize = Lc->length = La.length + Lb.length;
    Lc->elem = (ElemType *)malloc(Lc->listsize * sizeof(ElemType));
    if (!Lc->elem) exit(OVERFLOW);    // 存储分配失败
    ElemType *pa_last = La.elem + La.length - 1, *pb_last = Lb.elem + Lb.length - 1, *pc = Lc->elem;
    while (pa <= pa_last && pb <= pb_last) {    // 归并
	if (*pa <= *pb) *pc++ = *pa++;
	else *pc++ = *pb++;
    }
    while (pa <= pa_last) *pc++ = *pa++;    // 插入 La 的剩余元素
    while (pb <= pb_last) *pc++ = *pb++;    // 插入 Lb 的剩余元素
}// MergeList_Sq
