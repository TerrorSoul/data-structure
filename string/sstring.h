// - - - - - 串的定长顺序存储表示 - - - - -
#define MAXSTRLEN 255    // 用户可在 255 以内定义最大串长
typedef unsigned char SString[MAXSTRLEN + 1];    // 0 号单元存放串的长度

// - - - - - 基本操作的算法描述 - - - - -
Status StrAssign_S(SString *T, char *chars) {
    // 生成一个其值等于串常量 chars 的串 T
    int i = 0;
    for (; chars[i] && i <= MAXSTRLEN; ++i) (*T)[i + 1] = chars[i];
    (*T)[0] = i;
    return OK;
}// StrAssign_S

Status StrCopy_S(SString *T, SString S) {
    // 由串 S 复制得串 T
    for (int i = 0; i <= S[0]; ++i) (*T)[i] = S[i];
    return OK;
}// StrCopy_S

Status StrEmpty_S(SString S) {
    // 若 S 为空串，则返回 TRUE，否则返回 FALSE
    return S[0] == 0 ? TRUE : FALSE;
}// StrEmpty_S

int StrCompare_S(SString S, SString T) {
    // 若 S > T，则返回值 > 0；若 S = T，则返回值 = 0；若 S < T，则返回值 < 0
    for (int i = 1; i <= S[0] && i <= T[0]; ++i) {
        if (S[i] > T[i]) return 1;
	else if (S[i] < T[i]) return -1;
    }
    return S[0] > T[0] ? 1 : S[0] == T[0] ? 0 : -1;
}// StrCompare_S

int StrLength_S(SString S) {
    // 返回 S 的元素个数，称为串的长度
    return S[0];
}// StrLength_S

Status ClearString_S(SString *S) {
    // 将 S 清为空串
    (*S)[0] = 0;
    return OK;
}// ClearString_S

Status Concat_S(SString *T, SString S1, SString S2) {
    // 用 T 返回由 S1 和 S2 联接而成的新串
    int uncut;
    if (S1[0] + S2[0] <= MAXSTRLEN) {    // 未截断
        for (int i = 1; i <= S1[0]; ++i) (*T)[i] = S1[i];
	for (int i = 1; i <= S2[0]; ++i) (*T)[S1[0] + i] = S2[i];
	(*T)[0] = S1[0] + S2[0];
	uncut = TRUE;
    } else if (S1[0] < MAXSTRLEN) {    // 截断
        for (int i = 1; i <= S1[0]; ++i) (*T)[i] = S1[i];
	for (int i = 1; S1[0] + i <= MAXSTRLEN; ++i) (*T)[S1[0] + i] = S2[i];
        (*T)[0] = MAXSTRLEN;
        uncut = FALSE;
    } else {    // 截断（仅取 S1）
	for (int i = 0; i <= MAXSTRLEN; ++i) (*T)[i] = S1[i];
	(*T)[0] = MAXSTRLEN;
	uncut = FALSE;
    }
    return uncut;
}// Concat_S

Status SubString_S(SString *Sub, SString S, int pos, int len) {
    // 用 Sub 返回串 S 的第 pos 个字符起长度为 len 的子串
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1) return ERROR;
    for (int i = 1; i <= len; ++i) (*Sub)[i] = S[pos + i - 1];
    (*Sub)[0] = len;
    return OK;
}// SubString_S

int Index_S(SString S, SString T, int pos) {
    // 若主串 S 中存放和串 T 值相同的子串，则返回它在主串 S 中第 pos 个字符之后第一次出现的位置；否则函数值为 0
}// Index_S

Status Replace_S(SString *S, SString T, SString V) {
    // 用 V 替换主串 S 中出现的所有与 T 相等的不重叠的子串
}// Replace_S

Status StrInsert_S(SString *S, int pos, SString T) {
    // 在串 S 的第 pos 个字符之前插入串 T
    if (pos < 1 || pos > (*S)[0] + 1) return ERROR;
    if ((*S)[0] + T[0] > MAXSTRLEN) {
        if (pos + T[0] > MAXSTRLEN) {
	    for (int i = 1; i + pos - 1 <= MAXSTRLEN && i <= T[0]; ++i) (*S)[i + pos - 1] = T[i];
	} else {
	    for (int i = MAXSTRLEN - T[0]; i >= pos; ++i) (*S)[i + T[0]] = (*S)[i];
	    for (int i = 1; i <= T[0]; ++i) (*S)[i + pos - 1] = T[i];
	}
	(*S)[0] = MAXSTRLEN;
    } else {
        for (int i = (*S)[0]; i >= pos; --i) (*S)[i + T[0]] = (*S)[i];    // 为插入 T 而腾出位置
        for (int i = 1; i <= T[0]; ++i) (*S)[i + pos - 1] = T[i];
        (*S)[0] += T[0];
    }
    return OK;
}// StrInsert_S

Status StrDelete_S(SString *S, int pos, int len) {
    // 从串 S 中删除第 pos 个字符起长度为 len 的子串
    if (pos < 1 || pos > (*S)[0]) return ERROR;
    for (int i = pos; i + len <= (*S)[0]; ++i) (*S)[i] = (*S)[i + len];
    (*S)[0] -= len;
    return OK;
}// StrDelete_S

Status DestroyString_S(SString *S) {
    // 串 S 被销毁
    (*S)[0] = 0;
    return OK;
}// DestroyString_S
