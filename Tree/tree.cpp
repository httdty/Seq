//
// Created by 44797 on 2019/10/25.
//
#include <iostream>

#define MaxSize 50


typedef int ElemType;


typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;


typedef struct {
    BiTree data[MaxSize];
    int top;
} SqStack;


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


bool Push(SqStack &S, BiTree x) {
    /*
     * 入栈操作
     */
    if (S.top == MaxSize - 1)
        return false;
    else
        S.data[++S.top] = x;
    return true;
}


bool Pop(SqStack &S, BiTree &x) {
    /*
     * 出栈操作
     */
    if (S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}


bool GetTop(SqStack S, BiTree &x) {
    /*
     * 获取栈顶元素
     */
    if (S.top == -1)
        return false;
    x = S.data[S.top];
    return true;
}


void visit(BiTree T) {
    std::cout << T->data << std::endl;
}


void PreOrder(BiTree T) {
    /*
     * 二叉树的先序遍历
     * 时间复杂度O(n)
     */
    if (T != NULL) {
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}


void InOrder(BiTree T) {
    /*
     * 二叉树的中序遍历
     * 时间复杂度O(n)
     */
    if (T != NULL) {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}


void PostOrder(BiTree T) {
    /*
     * 二叉树的后序遍历
     * 时间复杂度O(n)
     */
    if (T != NULL) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}


void InOrder2(BiTree T) {
    /*
     * 非递归的中序遍历
     */
    SqStack *t = (SqStack *) malloc(sizeof(SqStack));
    SqStack S = *t;
    InitStack(S);
    BiTree p = T;
    while (p || !StackEmpty(S)) {
        if (p) {
            Push(S, p);
            p = p->lchild;
        } else {
            Pop(S, p);
            std::cout << p->data << std::endl;
            p = p->rchild;
        }
    }
}


void PostOrder2(BiTree T) {
    /*
     * 使用栈实现后序遍历
     * 需要小心条件，比中序难很多
     */
    SqStack *t = (SqStack *) malloc(sizeof(SqStack));
    SqStack S = *t;
    InitStack(S);
    BiTree p = T, r = NULL;
    while (p || !StackEmpty(S)) {
        if (p) {
            Push(S, p);
            p = p->lchild;
        } else {
            GetTop(S, p);
            if (p->rchild && p->rchild != r) {  // 存在右子节点，且该点没被访问过（关键易错）
                p = p->rchild;
                Push(S, p);
                p = p->lchild;
            } else {
                Pop(S, p);
                visit(p);
                r = p;
                p = NULL;
            }
        }
    }
}


typedef BiTree BType;

typedef struct {
    /*
     * 定义队列
     */
    BType data[MaxSize];
    int front, rear;
} SqQueue;


void InitQueue(SqQueue &Q) {
    /*
     * 初始化队列
     */
    Q.rear = Q.front = 0;
}


bool isEmpty(SqQueue Q) {
    /*
     * 队列判空
     */
    return Q.rear != Q.front;
}


bool EnQueue(SqQueue &Q, BType x) {
    /*
     * 进队操作
     */
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}


bool DeQueue(SqQueue &Q, BType &x) {
    /*
     * 出队操作
     */
    if (Q.rear == Q.front)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}


void levelOrder(BiTree T) {
    SqQueue *t = (SqQueue *) malloc(sizeof(BiTNode));
    SqQueue Q = *t;
    InitQueue(Q);
    BiTree p = T;
    EnQueue(Q, p);
    while (!isEmpty(Q)) {
        DeQueue(Q, p);
        visit(p);
        if (p->lchild != NULL)
            EnQueue(Q, p->lchild);
        if (p->rchild != NULL)
            EnQueue(Q, p->rchild);
    }
}


typedef struct ThreadNode {
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;  // 0表示孩子节点，1表示线索节点
} ThreadNode, *ThreadTree;


void InThread(ThreadTree &p, ThreadTree &pre) {
    if (p != NULL) {
        InThread(p->lchild, pre);
        if (p->lchild == NULL) {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        InThread(p->rchild, pre);
    }
}


void createInThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {
        InThread(T, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}


void visit(ThreadNode *T) {
    std::cout << T->data << std::endl;
}


ThreadNode *FirstNode(ThreadNode *p) {
    while (p->ltag == 0)
        p = p->lchild;
    return p;
}


ThreadNode *NextNode(ThreadNode *p) {
    if (p->rtag == 0)
        return FirstNode(p->rchild);
    else
        return p->rchild;
}


void InOrder(ThreadNode *T) {
    for (ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p))
        visit(p);
}


void InvertLevel(BiTree bt) {
    /*
     * 按照从上至下从右到左的顺序遍历树
     * 同时使用一个栈和一个队列，主义入队和入栈的顺序关系
     */
    SqStack s;
    SqQueue q;
    BiTree p;
    if (bt != NULL) {
        InitStack(s);
        InitQueue(q);
        EnQueue(q, bt);
        while (!isEmpty(q)) {
            DeQueue(q, p);
            Push(s, p);
            if (p->lchild)  // 注意顺序
                EnQueue(q, p);
            if (p->rchild)
                EnQueue(q, p);
        }
        while (!StackEmpty(s)) {
            Pop(s, p);
            visit(p);
        }
    }
}


int BtLevel(BiTree T) {
    /*
     * 非递归算法实现层次计算
     * 使用了队列进行求算，通过更新下标来计算
     */
    if (!T)
        return 0;
    int front = -1, rear = -1;
    int last = 0, level = 0;
    BiTree Q[MaxSize];
    Q[++rear] = T;
    BiTree p;
    while (front < rear) {
        p = Q[++front];
        if (p->lchild)
            Q[++rear] = p->lchild;
        if (p->rchild)
            Q[++rear] = p->rchild;
        if (front == last) {  // 注意，什么时候更新level和last
            level++;
            last = rear;
        }
    }
    return level;
}


int Btdepth2(BiTree T) {
    /*
     * 递归算法求算数的深度
     */
    if (T == NULL)
        return 0;
    int ldepth, rdepth;
    ldepth = Btdepth2(T->lchild);
    rdepth = Btdepth2(T->rchild);
    return ldepth > rdepth ? (ldepth + 1) : (rdepth + 1);
}


BiTree PreInCreat(ElemType A[], ElemType B[], int l1, int l2, int r1, int r2) {
    /*
     * 先序遍历+中序遍历还原树结构
     * 使用递归的办法进行操作
     * 小心参数的传递：位置信息
     */
    BiTree root = (BiTree) malloc(sizeof(BiTNode));
    int i;
    root->data = A[l1];
    for (i = l2; B[i] != root->data; i++);
    int llen = i - l2;
    int rlen = r2 - i;
    if (llen)
        root->lchild = PreInCreat(A, B, l1 + 1, l2, l1 + llen, i - 1);  // 小心下标的值
    else
        root->lchild = NULL;
    if (rlen)
        root->rchild = PreInCreat(A, B, r2 - rlen + 1, i + 1, r1, r2);  // 小心下标的值
    else
        root->rchild = NULL;
    return root;
}


bool IsComplete(BiTree T) {
    /*
     * 完全树的判定
     * 使用队列实现
     * 技巧在于不论如何都将子节点进队，发现队里有NULL时若后续节点中存在非空节点，则不完全
     */
    if (!T)
        return true;
    SqQueue *t = (SqQueue *) malloc(sizeof(SqQueue));
    SqQueue Q = *t;
    InitQueue(Q);
    EnQueue(Q, T);
    BiTree p;
    while (!isEmpty(Q)) {
        DeQueue(Q, p);
        if (p) {
            EnQueue(Q, p->lchild);
            EnQueue(Q, p->rchild);
        } else {
            while (!isEmpty(Q)) {
                DeQueue(Q, p);
                if (p)
                    return false;
            }
        }
    }
    return true;
}


int DsonNodes(BiTree b) {
    /*
     * 求所有具有两个子节点的节点
     * 递归是一种精妙的东西，尽管它的效率不好
     */
    if (b == NULL)
        return 0;
    else if (b->lchild != NULL && b->rchild != NULL)
        return DsonNodes(b->lchild) + DsonNodes(b->rchild) + 1;
    else
        return DsonNodes(b->lchild) + DsonNodes(b->rchild);
}


void Swap(BiTree b) {
    /*
     * 两个子树交换
     * 递归实现
     */
    if (b) {
        Swap(b->lchild);
        Swap(b->rchild);
        BiTree temp = b->lchild;
        b->lchild = b->rchild;
        b->rchild = temp;
    }
}


ElemType PreOrder(BiTree b, int k) {
    /*
     * 返回先序遍历的第k个元素
     * 我这里使用了static变量，应该是对的，是为了避免使用全局变量
     */
    static int i = 1;
    if (b == NULL)
        return '#';
    if (i == k)
        return b->data;
    i++;
    ElemType ch = PreOrder(b->lchild, k);
    if (ch != '#')
        return ch;
    ch = PreOrder(b->rchild, k);
    return ch;  // 这里不需要再判定#字符，因为k个肯定存在
}


typedef struct {
    /*
     * 双亲表示法-节点
     */
    ElemType data;
    int parent;
} PTNode;

typedef struct {
    /*
     * 双亲表示法-树
     */
    PTNode nodes[MaxSize];
    int n;
} PTree;

typedef struct CNode {
    /*
     * 孩子表示法-孩子节点
     */
    int child;
    struct CNode *next;
} CNode;

typedef struct {
    /*
     * 孩子表示法-双亲节点
     */
    ElemType data;
    struct CNode *next;
} PNode;

typedef struct {
    /*
     * 孩子表示法-树
     */
    PNode nodes[MaxSize];
    int n;
} CTree;

typedef struct CSNode{
    /*
     * 孩子兄弟表示法
     * 左孩子右兄弟
     */
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;


BiTNode *BST_Search(BiTree T, ElemType key, BiTNode *&p){
    /*
     * 二叉排序树的查找操作
     * 时间复杂度O(h)
     */
    p = NULL;  // p用来记录查找到的节点的父节点
    while (T!=NULL && key!=T->data){
        p = T;
        if (key < T->data)
            T = T->lchild;
        else
            T = T->rchild;
    }
    return T;
}


bool BST_Insert(BiTree &T, ElemType k){
    /*
     * 二叉排序树的插入
     */
    if (T == NULL){
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = k;
        T->lchild = NULL;
        T->rchild = NULL;
        return true;
    } else if (k == T->data)
        return false;
    else if (k > T->data)
        return BST_Insert(T->rchild, k);
    else
        return BST_Insert(T->lchild, k);
}


void Create_BST(BiTree &T, ElemType str[], int n){
    /*
     * 创建一棵二叉排序树
     */
    T = NULL;
    for (int i = 0; i < n; i ++)
        BST_Insert(T, str[i]);
}


void Judge_AVL(BiTree bt, int &balance, int &h){
    /*
     * AVL树的判定
     */
    int bl = 0, br = 0, hl = 0, hr = 0;
    if (bt == NULL) {
        h = 0;
        balance = 1;
    } else if (bt->lchild == NULL && bt->rchild == NULL){
        h = 1;
        balance = 1;
    } else {
        Judge_AVL(bt->lchild, bl, hl);
        Judge_AVL(bt->rchild, br, hr);
        h = ((hl > hr)?hl:hr) + 1;
        if (abs(hl - hr) < 2 && bl == 1 && br == 1)
            balance = 1;
        else
            balance = 0;
    }
}