//
// Created by 44797 on 2019/10/20.
//

#include <iostream>

#define MaxSize 50

typedef int ElemType;

typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} *LiStack;

void InitStack(SqStack &S) {
    /*
     * 初始化栈
     */
    S.top = -1;
}


bool StackEmpty(SqStack S) {
    /*
     * 判断栈空
     */
    return S.top == -1;
}


bool Push(SqStack &S, ElemType x) {
    /*
     * 入栈操作
     */
    if (S.top == MaxSize - 1)
        return false;
    else
        S.data[++S.top] = x;
    return true;
}


bool Pop(SqStack &S, ElemType &x) {
    /*
     * 出栈操作
     */
    if (S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}


bool GetTop(SqStack S, ElemType &x) {
    /*
     * 获取栈顶元素
     */
    if (S.top == -1)
        return false;
    x = S.data[S.top];
    return true;
}


bool PossibleOrder(char A[]) {
    /*
     * 判定一系列进出栈操作是否合理
     */
    int i = 0, flag = 0;
    while (A[i] != '\0') {
        if (A[i] == 'I')
            flag++;
        else
            flag--;
        if (flag < 0)
            return false;
    }
    return flag == 0;
}


bool Centrosymmetric(LiStack &L, int n) {
    /*
     * 判断一个字符串是不是中心对称的
     */
    char s[n / 2];
    int i;
    bool flag = true;

    LinkNode *p = L->next;
    for (i = 0; i < n / 2; i++) {
        s[i] = p->data;
        p = p->next;
    }
    if (n % 2 != 0)
        p = p->next;

    while (p) {
        if (p->data != s[--i])
            return false;
        p = p->next;
    }
    return true;
}


typedef struct {
    ElemType stack[MaxSize];
    int top[2];
} shareStk;

shareStk stk;

int SharePush(int i, ElemType x) {
    /*
     * 共享栈的入栈
     */
    if (i < 0 || i > 1) {
        std::cout << "输入错误" << std::endl;
        exit(0);
    }

    if (stk.top[1] - stk.top[0] == 1) {
        std::cout << "栈满" << std::endl;
        return 0;
    }

    switch (i) {
        case 0:
            stk.stack[++stk.top[0]] = x;
            return 1;
            break;
        case 1:
            stk.stack[--stk.top[1]] = x;
            return 1;
    }
}


int SharePop(int i, ElemType &x) {
    /*
     * 共享栈的出栈
     */
    if (i < 0 || i > 1) {
        std::cout << "输入错误" << std::endl;
        exit(0);
    }

    switch (i) {
        case 0:
            if (stk.top[0] == -1) {
                std::cout << "栈空" << std::endl;
                return 0;
            } else {
                x = stk.stack[stk.top[0]--];
                return 1;
            }
        case 1:
            if (stk.top[1] == MaxSize) {
                std::cout << "栈空" << std::endl;
                return 0;
            } else {
                x = stk.stack[stk.top[1]++];
                return 1;
            }
    }
}
