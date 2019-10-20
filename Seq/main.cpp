#include <iostream>

#define MaxSize 50

using namespace std;

typedef int ElemType;

typedef struct {
    /*
     * 顺序表
     */
    ElemType data[MaxSize];
    int length;
} SqList;

typedef struct LNode {
    /*
     * 单链表
     */
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

typedef struct DNode {
    /*
     * 双链表
     */
    ElemType data;
    struct DNode *prior, *next;
} DNodel, *DLinkList;

typedef struct SNode {
    /*
     * 静态链表
     */
    ElemType data;
    int next;
} SLinkList[MaxSize];


bool ListInsert(SqList &L, int i, ElemType e) {
    if (i < 1 || i > L.length)  // i位置限制
        return false;
    if (L.length >= MaxSize)  // 长度限制
        return false;
    for (int j = L.length; j >= i; j--)  // 循环后移
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;  // 插入
    L.length++;  // 更新长度
    return true;
}


bool ListDelete(SqList &L, int i, ElemType &e) {
    if (i < 0 || i > L.length)  // i位置限制
        return false;
    e = L.data[i];  // 获得被删除元素
    for (int j = i; j <= L.length; j++)  // 循环左移
        L.data[j - 1] = L.data[j];
    L.length--;  // 更新长度
    return true;
}


int LocateElem(SqList L, ElemType e) {
    int i;
    for (i = 0; i < L.length; i++)  // 循环查找
        if (L.data[i] == e)
            return i;
    return 0;  // 未找到，返回0
}


bool DelMin(SqList &L, ElemType &value) {
    // 删除最小元素，交换最小元素和最后元素的位置，通过引用型参数value传递最小值
    // 成功返回true，失败返回false
    if (L.length == 0)  // 空表
        return false;
    value = L.data[0];  // 从0号元素开始查找
    int pos = 0;  // 位置标记
    for (int i = 0; i < L.length; i++)
        if (value < L.data[i]) {  // find smaller value, change value, update pos
            value = L.data[i];
            pos = i;
        }
    L.data[pos] = L.data[L.length - 1];  // exchange min and last number
    L.length--;  // length --
    return true;
}


void RevSeq(SqList &L) {
    // reverse the seq list
    // Space complexity O(1)
    int mid = L.length / 2;  // middle index
    for (int i = 0; i < mid; i++) {
        ElemType tmp = L.data[i];  // temp var, used for exchange data
        L.data[i] = L.data[L.length - i - 1];
        L.data[L.length - i - 1] = tmp;
    }
}

void DelX(SqList &L, ElemType x) {
    /*
     * 这么做破坏了相对位置，在DelX_1和DelX_2的做法中则可以对相对位置关系进行保存
     */
    // Delete all element valued x
    // Time Complexity O(n); Space Complexity O(1)
    for (int i = 0; i < L.length; i++) {  // Find value x
        if (L.data[i] == x)  // Find x, set the element.value = the final element.value
            L.data[i] = L.data[L.length - 1];
        L.length--;  // length --
        i--;
    }
}


void DelX_1(SqList &L, ElemType x) {
    /*
     * 遍历顺序表，记录非x的个数为k，对于非x元素：L.data[k] = L.data[i]
     */
    int k = 0;  // record the number value != x
    for (int i = 0; i < L.length; i++)
        if (L.data[i] != x) {  // L.data[i] != x, L.data[k] = L.data[i]
            L.data[k] = L.data[i];
            k++;
        }
    L.length = k;
}


void DelX_2(SqList &L, ElemType x) {
    /*
     * 遍历顺序表，记录x的个数为k，对于非x的元素，L.data[i - k]=L.data[i]
     */
    int k = 0, i = 0;
    while (i < L.length) {
        if (L.data[i] == x)  // record number == x
            k++;
        else
            L.data[i - k] = L.data[i];  // L.data[i - k] = L.data[i]
        i++;
    }
    L.length = L.length - k;  // set new length
}


bool DelST(SqList &L, ElemType s, ElemType t) {
    /*
     * 分两次循环完成，虽然代码组织不好但是功能可以完成
     */
    if (!L.length || (s >= t))  // not sat
        return false;
    int mark = L.length, i = 0;
    for (; i < L.length; i++) {  // find the first pos and the last pos
        if (L.data[i] >= s && mark == L.length)
            mark = i;
        if (L.data[i] > t)
            break;
    }
    int j = 0;
    for (; j < i - mark; j++) {  // move the element
        if (i < L.length)
            L.data[mark + j] = L.data[i];
        else
            break;
    }
    L.length -= j;  // update the length
    return true;
}


bool DelST_1(SqList &L, ElemType s, ElemType t) {
    /*
     * 充分利用循环语句，在循环语句中使用多重判断和多重改变，又充分利用循环变量作为其他值的数据来源
     */
    int i, j;
    if (s >= t || L.length == 0)  // not sat
        return false;
    for (i = 0; i < L.length && L.data[i] < s; i++);  // find start
    if (i >= L.length)
        return false;
    for (j = i; j < L.length && L.data[j] <= t; j++);  // find end
    for (; j < L.length; i++, j++)  // move data
        L.data[i] = L.data[j];
    L.length = j;  // set new length
    return true;
}


bool DelSTN(SqList &L, ElemType s, ElemType t) {
    /*
     * 每找到一个不合适的值就将表尾的元素放入该位置进行替换，同时表长度减
     * 缺点是破坏了表中元素的相对位置
     */
    if (!L.length || s >= t)  // not sat
        return false;
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] >= s && L.data[i] <= t) {  // find the number in [s, t]
            L.data[i] = L.data[L.length - 1];  // set with the last number
            L.length--;
        }
    }
    return true;
}


bool DelSTN_1(SqList &L, ElemType s, ElemType t) {
    /*
     * 删除表中所有大于等于s小于等于t的元素
     * 保持了原来线性表的相对顺序不变
     */
    if (!L.length && s >= t)  // not sat
        return false;
    int k = 0, i = 0;
    for (; i < L.length; i++) {
        if (L.data[i] >= s || L.data[i] <= t)  // count the sat number
            k++;
        else
            L.data[i - k] = L.data[i];  // set the data[i - k] = data[i]
    }
    L.length -= k;
    return true;
}


bool DisDel(SqList &L) {
    /*
     * 删除有序顺序表中重复的元素
     * 记录上一次的值并设定一个偏移量，循环偏移完成
     */
    if (!L.length)
        return false;
    int k = 0, i;
    ElemType last = L.data[0];
    for (i = 1; i < L.length; i++) {
        if (last == L.data[i]) {  // same element, k++
            k++;
        } else {
            L.data[i - k] = L.data[i];  // different element, data[i - k] = data[i]
        }
        last = L.data[i];
    }
    L.length -= k;
    return true;
}


bool DisDel_1(SqList &L) {
    /*
     * 删除有序顺序表中重复的元素
     * j增长速度远快于i，故对前面元素的修改不会影响到后面的效果，即重置data[i]即可
     */
    if (L.length == 0)
        return false;
    int i, j;
    for (i = 0, j = 1; j < L.length; j++) {
        if (L.data[j] != L.data[i])  // new value appeared, add into data[i++]
            L.data[++i] = L.data[j];
    }
    L.length = i + 1;  // set new length = i + 1
    return true;
}


bool Merge(SqList a, SqList b, SqList &c) {
    /*
     * 两个顺序表合成一个
     * 类似归并排序的合并操作，注意不要发生数组越界或者丢下一部分没有合并
     * 可以增加一个局部变量k，减少c.length++的操作数量
     */
    if (a.length + b.length > MaxSize)
        return false;
    int i = 0, j = 0;
    while (i < a.length && j < b.length) {  // point move and set the smaller value into c
        c.length++;
        if (a.data[i] < b.data[j]) {
            c.data[c.length - 1] = a.data[i];
            i++;
        } else {
            c.data[i + j] = b.data[j];
            j++;
        }
    }
    while (i < a.length) {  // set the spare value into c
        c.length++;
        c.data[c.length - 1] = a.data[i];
    }
    while (j < b.length) {
        c.length++;
        c.data[c.length - 1] = b.data[j];
    }
    return true;
}


bool ReverseArray(ElemType A[], int s, int t, int arraySize) {
    /*
     * 数组逆序，为交换两个数组块准备
     */
    if (s >= t || t >= arraySize)
        return false;
    ElemType temp;
    int mid = (s + t) / 2;  // get mid
    for (int i = 0; i <= mid; i++) {  // exchange the A[i] and A[t - i]
        temp = A[i];
        A[i] = A[t - i];
        A[t - i] = temp;
    }
    return true;
}


void ExchangeList(ElemType A[], int n, int m, int arraySize) {
    /*
     * 交换两个数组块的顺序
     * 逆序总数组-逆序前n个-逆序后m个
     */
    ReverseArray(A, 0, n + m - 1, arraySize);
    ReverseArray(A, 0, n - 1, arraySize);
    ReverseArray(A, n, n + m - 1, arraySize);
}


void FindExchangeInsert(ElemType A[], ElemType searchNum, int arraySize) {
    /*
     * 在递增顺序表中找到目标值，找到则将该值与后继节点交换，找不到则在正确位置插入目标值
     * 使用二分查找，充分利用low和high的性质判断是否成功找到元素值，并据此获得移动的长度
     */
    int low = 0, high = arraySize - 1, mid = 0;
    while (low <= high) {  // binary search
        mid = (low + high) / 2;
        if (A[mid] == searchNum)
            break;
        else if (A[mid] < searchNum)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (A[mid] == searchNum &&
        mid < arraySize - 1) {  // A[mid] is the number, exchange value if mid is not the last num
        ElemType temp = A[mid];
        A[mid] = A[mid + 1];
        A[mid + 1] = temp;
    }
    if (low > high) {  // 404, insert searchValue into A[low]
        for (int i = arraySize - 1; i > high; i--) {
            A[i + 1] = A[i];
        }
        A[low] = searchNum;
    }
}


LinkList Link_HeadInsert(LinkList &L) {
    /*
     * 头插法建立单链表
     */
    LNode *s;
    ElemType x;
    L = (LinkList) malloc(sizeof(LNode));
    L->next = NULL;

    cin >> x;
    while (x != 9999) {
        s = (LNode *) malloc(sizeof(LNode));
        s->data = x;
        s->next = L->next;
        L->next = s;
        cin >> x;
    }
    return L;
}


LinkList Link_TailInsert(LinkList &L) {
    /*
     * 尾插法建立单链表
     */
    ElemType x;
    L = (LinkList) malloc(sizeof(LNode));
    LNode *s, *r = L;
    cin >> x;
    while (x != 9999) {
        s = (LNode *) malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
        cin >> x;
    }
    r->next = NULL;  // 小心这里，不要忘记
    return L;
}


LNode *GetElem(LinkList L, int i) {
    /*
     * 在单链表中获取第i个元素
     */
    int j = 1;
    LNode *p = L->next;
    if (i == 0)
        return L;
    if (i < 1)
        return NULL;
    while (p && (j < i)) {
        p = p->next;
        j++;
    }
    return p;
}


LNode *LocateElem(LinkList L, ElemType e) {
    /*
     * 定位值为e的元素位置
     */
    LNode *p = L->next;
    while (p && (e != p->data)) {
        p = p->next;
    }
    return p;
}


LNode *RecurisveDeleteX(LinkList L, ElemType x) {
    /*
     * 对单链表进行递归删除
     */
    LNode *temp = NULL;
    if (L->next) {
        temp = RecurisveDeleteX(L->next, x);
    }
    if (L->data == x) {
        free(L);
    } else {
        L->next = temp;
        temp = L;
    }
    return temp;
}


void RecurisveDeleteX_1(LinkList &L, ElemType x) {
    /*
     * 递归删除所有值为x的节点
     * 需要注意的是，函数中使用了引用，这种类型不会导致链表断裂
     */
    LNode *p;
    if (L == NULL)
        return;
    if (L->data == x) {
        p = L;
        L = L->next;
        free(p);
        RecurisveDeleteX_1(L, x);
    } else {
        RecurisveDeleteX_1(L->next, x);
    }
}


void DeleteX(LinkList L, ElemType x) {
    /*
     * 带头结点的单链表中删除所有值为x的节点
     */
    LNode *prev = L, *now = L->next, *temp;
    while (now) {
        if (now->data == x) {
            temp = now;
            now = now->next;
            prev->next = now;
            free(temp);
        } else {
            prev = now;
            now = now->next;
        }  // else
    }  // while
}


void ReverseOutput(LinkList L) {
    /*
     * 逆序输出单链表中的元素
     * 采用递归实现
     */
    if (L == NULL)
        return;
    ReverseOutput(L->next);
    cout << L->data << endl;
}


void DeleteMinNode(LinkList L) {
    /*
     * 删除最小元素所在的节点
     */
    LNode *p = L->next, *min = L->next, *prev = L, *minprev = L;
    while (p != NULL) {
        if (p->data < min->data) {
            min = p;
            minprev = prev;
        } else {
            prev = p;
            p = p->next;
        }
    }
    minprev->next = min->next;
    free(min);
}


LinkList ReverseLinkList(LinkList &L) {
    /*
     * 逆转单链表
     * 时间：O(n)，空间O(1)
     */
    LNode *prev = NULL, *p = L->next, *temp;
    while (p->next != NULL) {
        temp = p->next;
        p->next = prev;
        prev = p;
        p = temp;
    }
    L->next = p;

    return L;
}


LinkList ReverseLinkList_1(LinkList &L) {
    /*
     * 使用头插法进行链表的逆转
     * 逻辑很巧妙，但是不是正常思路，讨巧办法
     */
    LNode *p = L->next, *r;
    L->next = NULL;
    while (p) {
        r = p->next;
        p->next = L->next;
        L->next = p;
        p = r;
    }
    return L;
}


LinkList SortLinkListByInsertSort(LinkList &L) {
    /*
     * 单链表元素递增排序，使用插排
     * 需要注意的是，由于链表的性质，使用插排格外的方便，在这里并未要求排序的时间复杂度，故使用此方法
     */
    LNode *nl = L->next, *p, *prev, *maxprev, *max;
    while (nl) {
        max = nl;
        maxprev = prev = NULL;
        p = nl;
        while (p->next) {
            prev = p;
            p = p->next;
            if (p->data > max->data) {
                maxprev = prev;
                max = p;
            }
        }
        if (maxprev)
            maxprev->next = max->next;
        else
            nl->next = max->next;
        LNode *temp = L->next;
        L->next = max;
        max->next = temp;
    }
    return L;
}


void DeleteFromXToY(LinkList &L, ElemType x, ElemType y) {
    /*
     * 删除单链表中值位于范围x到y之间的节点
     */
    LNode *prev = L, *p = L->next, *temp;
    while (p) {
        if (p->data < y && p->data > x) {
            prev->next = p->next;
            free(p);
            p = prev->next;
        } else {
            prev = p;
            p = p->next;
        }
    }
}


LinkList *FindPublicNode(LinkList &L1, LinkList &L2) {
    /*
     * 找到两个链表的公共节点
     * 时间O(m+n)，很强的一个复杂度
     */
    LNode *p1 = L1, *p2 = L2;
    int len1 = 0, len2 = 0, dis;
    while (p1) {
        len1++;
        p1 = p1->next;
    }
    while (p2) {
        len2++;
        p2 = p2->next;
    }
    if (len1 < len2) {
        p2 = L2;
        p1 = L1;
        dis = len2 - len1;
    } else {
        p1 = L2;
        p2 = L1;
        dis = len1 - len2;
    }
    while (dis--)  // good statement
        p2 = p2->next;
    while (p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return (LinkList *) p1;
}


void IncreasinglyFreeNode(LinkList &head) {
    /*
     * 按递增的顺序输出并释放单链表
     */
    LNode *p, *prev, *min, *minPrev;
    while (head->next) {
        min = p = head->next;
        minPrev = prev = head;
        while (p) {
            if (p->data < min->data) {
                min = p;
                minPrev = prev;
            }
            prev = p;
            p = p->next;
        }
        cout << min->data << endl;
        minPrev->next = min->next;
        free(min);
    }
    free(head);
}


void IncreasinglyFreeNode_1(LinkList &head) {
    /*
     * 按递增的顺序输出并释放单链表
     * 有趣的是，这段代码只用了两个变量+一个额外的临时变量就解决了问题，充分使用prev指针
     * 这是因为代码并不需要真实记录p的前驱，而最小节点也并不需要记录，可由其前驱直接推得
     */
    LNode *pre, *p, *temp;
    while (head->next != NULL) {
        pre = head;
        p = head->next;
        while (p->next != NULL) {
            if (p->next->data < pre->next->data)
                pre = p;
            p = p->next;
        }
        cout << pre->next->data << endl;
        temp = pre->next;
        pre->next = temp->next;
        free(temp);
    }
}


LinkList DisCreate(LinkList &A) {
    /*
     * 拆分一个单链表变为两个链表，其中奇数位置的节点在A中，偶数位置的节点在B中
     */
    LinkList B;
    B = (LinkList) malloc(sizeof(LNode));
    B->next = NULL;
    LNode *ra = A, *rb = B;
    bool flag = false;
    while (ra->next) {
        if (flag) {
            rb->next = ra->next;
            ra->next = ra->next->next;
            rb = rb->next;
            rb->next = NULL;
        } else {
            ra = ra->next;
        }
        flag = !flag;
    }
    return B;
}


LinkList DisCreate_1(LinkList &A) {
    /*
     * 拆分一个单链表变为两个链表，其中奇数位置的节点在A中，偶数位置的节点在B中
     * 这样写的优势是更为清晰，虽然增加了一点点不必要的操作和空间，但是并未从数量级上造成威胁
     */
    int i = 0;
    LinkList B = (LinkList) malloc(sizeof(LNode));
    B->next = NULL;
    LNode *ra = A, *rb = B, *p;
    p = A->next;
    A->next = NULL;
    while (p) {
        i++;
        if (i % 2 != 0) {
            rb->next = p;
            rb = p;
        } else {
            ra->next = p;
            ra = p;
        }
        p = p->next;
    }
    ra->next = NULL;
    rb->next = NULL;
    return B;
}


LinkList DisCreateReverseB(LinkList &A) {
    /*
     * 拆分一个单链表变为两个链表，其中奇数位置的节点在A中，偶数位置的节点在B中，同时逆置B
     * 充分利用头插法的效果直接逆置B
     */
    LinkList B = (LinkList) malloc(sizeof(LNode));
    B->next = NULL;
    bool flag = false;
    LNode *ra = A, *temp;
    while (ra->next) {
        if (flag) {
            temp = B->next;
            B->next = ra->next;
            ra->next = ra->next->next;
            B->next->next = temp;
        } else {
            ra = ra->next;
        }
        flag = !flag;
    }
}


LinkList DisCreate_2(LinkList &A) {
    /*
     * 拆分一个单链表变为两个链表，其中奇数位置的节点在A中，偶数位置的节点在B中，同时逆置B
     * 充分利用头插法的效果直接逆置B
     * 有趣的是，这里的循环做了循环展开，一次完成两个节点
     */
    LinkList B = (LinkList) malloc(sizeof(LNode));
    B->next = NULL;
    LNode *p = A->next, *q;
    LNode *ra = A;
    while (p) {
        ra->next = p;
        ra = p;
        p = p->next;
        q = p->next;
        p->next = B->next;
        B->next = p;
        p = q;
    }
    ra->next = NULL;
    return B;
}


void DeleteSameInIncreaseing(LinkList &L) {
    /*
     * 删除递增单链表中的相同数据值节点
     */
    LNode *p = L->next, *prev = L;
    ElemType x = p->data;
    while (p->next) {
        prev = p;
        p = p->next;
        if (p->data == x) {
            prev->next = p->next;
            free(p);
            p = prev;
        } else {
            x = p->data;
        }
    }
}


void ReverseMerge(LinkList &A, LinkList &B) {
    /*
     * 归并并且逆序存放数据
     */
    LNode *pa = A->next, *pb = B->next, *temp;
    A->next = NULL;
    while (pa && pb) {
        if (pa->data > pb->data) {
            temp = pa->next;
            pa->next = A->next->next;
            A->next = pa;
            pa = temp;
        } else {
            temp = pb->next;
            pb->next = A->next->next;
            A->next = pb;
            pb = temp;
        }
    }
    while (pa) {
        temp = pa->next;
        pa->next = A->next->next;
        A->next = pa;
        pa = temp;
    }
    while (pb) {
        temp = pb->next;
        pb->next = A->next->next;
        A->next = pb;
        pb = temp;
    }
    B = A;
}


int main() {
    cout << "Hello, World!" << endl;
    return 0;
}