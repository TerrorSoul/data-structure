// - - - - - 串的堆分配存储表示 - - - - -
typedef struct {
    char *ch;    // 若是非空串，则按串长分配存储区，否则 ch 为 NULL
    int length;    // 串长度
}HString;

// - - - - - 基本操作的算法描述 - - - - -
Status StrAssign_H(HString *T, char *chars) {
    // 生成一个其值等于串常量 chars 的串 T
    if (T->ch) free(T->ch);    // 释放 T 原有空间
    int i = 0;
    for (char *c = chars; *c; ++i, ++c);    // 求 chars 的长度 i
    if (!i) {
        T->ch = NULL;
	T->length = 0;
    } else {
        if (!(T->ch = (char *)malloc(i * sizeof(char)))) exit(OVERFLOW);
	for (int j = 0; j < i; ++j) T->ch[j] = chars[j];
	T->length = i;
    }
    return OK;
}// StrAssign_H

Status StrCopy_H(HString *T, HString S) {
    // 由串 S 复制得串 T
    if (T->ch) free(T->ch);    // 释放 T 原有空间
    if (!S.length) {
        T->ch = NULL;
	T->length = 0;
    } else {
        if (!(T->ch = (char *)malloc(S.length * sizeof(char)))) exit(OVERFLOW);
        for (int i = 0; i < S.length; ++i) T->ch[i] = S.ch[i];
	T->length = S.length;
    }
    return OK;
}// StrCopy_H

Status StrEmpty_H(HString S) {
    // 若 S 为空串，则返回 TRUE，否则返回 FALSE
    return S.length == 0 ? TRUE : FALSE;
}// StrEmpty_H

int StrCompare_H(HString S, HString T) {
    // 若 S > T，则返回值 > 0；若 S = T，则返回值 = 0；若 S < T，则返回值 < 0
    for (int i = 0; i < S.length && i < T.length; ++i)
	if (S.ch[i] != T.ch[i]) return S.ch[i] - T.ch[i];
    return S.length - T.length;
}// StrCompare_H

int StrLength_H(HString S) {
    // 返回 S 的元素个数，称为串的长度
    return S.length;
}// StrLength_H

Status ClearString_H(HString *S) {
    // 将 S 清为空串
    if (S->ch) {
        free(S->ch);
	S->ch = NULL;
    }
    S->length = 0;
    return OK;
}// ClearString_H

Status Concat_H(HString *T, HString S1, HString S2) {
    // 用 T 返回由 S1 和 S2 联接而成的新串
    if (T->ch) free(T->ch);    // 释放旧空间
    if (!(T->ch = (char *)malloc((S1.length + S2.length) * sizeof(char)))) exit(OVERFLOW);
    for (int i = 0; i < S1.length; ++i) T->ch[i] = S1.ch[i];
    T->length = S1.length + S2.length;
    for (int i = 0; i < S2.length; ++i) T->ch[i + S1.length] = S2.ch[i];
    return OK;
}// Concat_H

Status SubString_H(HString *Sub, HString S, int pos, int len) {
    // 用 Sub 返回串 S 的第 pos 个字符起长度为 len 的子串
    if (pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1) return ERROR;
    if (Sub->ch) free(Sub->ch);    // 释放旧空间
    if (!len) {    // 空子串
        Sub->ch = NULL;
	Sub->length = 0;
    } else {    // 完整子串
        Sub->ch = (char *)malloc(len * sizeof(char));
	for (int i = 0; i < len; ++i) Sub->ch[i] = S.ch[i + pos - 1];
	Sub->length = len;
    }
    return OK;
}// SubString_H

int Index_H(HString S, HString T, int pos) {
    // 若主串 S 中存放和串 T 值相同的子串，则返回它在主串 S 中第 pos 个字符之后第一次出现的位置；否则函数值为 0
}// Index_H

Status Replace_H(HString *S, HString T, HString V) {
    // 用 V 替换主串 S 中出现的所有与 T 相等的不重叠的子串
}// Replace_H

Status StrInsert_H(HString *S, int pos, HString T) {
    // 在串 S 的第 pos 个字符之前插入串 T
    if (pos < 1 || pos > S->length + 1) return ERROR;    // pos 不合法
    if (T.length) {    // T 非空，则重新分配空间，插入T
        if (!(S->ch = (char *)realloc(S->ch, (S->length + T.length) * sizeof(char)))) exit(OVERFLOW);
	for (int i = S->length - 1; i >= pos - 1; --i) S->ch[i + T.length] = S->ch[i];    // 为插入 T 而腾出位置
        for (int i = 0; i < T.length; ++i) S->ch[i + pos - 1] = T.ch[i];
	S->length += T.length;
    }
    return OK;
}// StrInsert_H

Status StrDelete_H(HString *S, int pos, int len) {
    // 从串 S 中删除第 pos 个字符起长度为 len 的子串
    if (pos < 1 || pos > S->length) return ERROR;    // pos 不合法
    if (pos + len > S->length) {
	S->ch = (char *)realloc(S->ch, (pos - 1) * sizeof(char));
	S->length = pos - 1;
    } else {
        for (int i = pos - 1; i < S->length - len; ++i) S->ch[i] = S->ch[i + len];
        S->ch = (char *)realloc(S->ch, (S->length - len) * sizeof(char));
	S->length -= len;
    }
    return OK;
}// StrDelete_H

Status DestroyString_H(HString *S) {
    // 串 S 被销毁
    if (S->ch) {
        free(S->ch);
	S->ch = NULL;
    }
    S->length = 0;
    return OK;
}// DestroyString_H
