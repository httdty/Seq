#include <iostream>

#define MaxSize 50

using namespace std;

typedef int ElemType;

typedef struct{
    ElemType data[MaxSize];
    int length;
}SqList;


bool ListInsert(SqList &L, int i, ElemType e){
    if (i < 1 || i > L.length)  // i位置限制
        return false;
    if (L.length >= MaxSize)  // 长度限制
        return false;
    for (int j = L.length; j >= i; j--)  // 循环后移
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;  // 插入
    L.length ++;  // 更新长度
    return true;
}


bool ListDelete(SqList &L, int i, ElemType &e){
    if (i < 0 || i > L.length)  // i位置限制
        return false;
    e = L.data[i];  // 获得被删除元素
    for (int j = i; j <= L.length; j++)  // 循环左移
        L.data[j - 1] = L.data[j];
    L.length --;  // 更新长度
    return true;
}


int LocateElem(SqList L, ElemType e){
    int i;
    for (i = 0; i < L.length; i++)  // 循环查找
        if (L.data[i] == e)
            return i;
    return 0;  // 未找到，返回0
}


bool DelMin(SqList &L, ElemType &value){
    // 删除最小元素，交换最小元素和最后元素的位置，通过引用型参数value传递最小值
    // 成功返回true，失败返回false
    if (L.length == 0)  // 空表
        return false;
    value = L.data[0];  // 从0号元素开始查找
    int pos = 0;  // 位置标记
    for (int i = 0; i < L.length; i++)
        if (value < L.data[i]){  // find smaller value, change value, update pos
            value = L.data[i];
            pos = i;
        }
    L.data[pos] = L.data[L.length - 1];  // exchange min and last number
    L.length --;  // length --
    return true;
}


void RevSeq(SqList &L){
    // reverse the seq list
    // Space complexity O(1)
    int mid = L.length / 2;  // middle index
    for (int i = 0; i < mid; i ++){
        ElemType tmp = L.data[i];  // temp var, used for exchange data
        L.data[i] = L.data[L .length - i - 1];
        L.data[L.length - i - 1] = tmp;
    }
}

void DelX(SqList &L, ElemType x){
    /*
     * 这么做破坏了相对位置，在DelX_1和DelX_2的做法中则可以对相对位置关系进行保存
     */
    // Delete all element valued x
    // Time Complexity O(n); Space Complexity O(1)
    for (int i=0; i<L.length; i++){  // Find value x
        if (L.data[i] == x)  // Find x, set the element.value = the final element.value
            L.data[i] = L.data[L.length - 1];
        L.length --;  // length --
        i --;
    }
}


void DelX_1(SqList &L, ElemType x){
    /*
     * 遍历顺序表，记录非x的个数为k，对于非x元素：L.data[k] = L.data[i]
     */
    int k = 0;  // record the number value != x
    for (int i=0; i<L.length; i++)
        if (L.data[i] != x){  // L.data[i] != x, L.data[k] = L.data[i]
            L.data[k] = L.data[i];
            k ++;
        }
    L.length = k;
}


void DelX_2(SqList &L, ElemType x){
    /*
     * 遍历顺序表，记录x的个数为k，对于非x的元素，L.data[i - k]=L.data[i]
     */
    int k = 0, i = 0;
    while (i < L.length){
        if (L.data[i] == x)  // record number == x
            k ++;
        else
            L.data[i - k] = L.data[i];  // L.data[i - k] = L.data[i]
        i++;
    }
    L.length = L.length - k;  // set new length
}

bool DelST(SqList &L, ElemType s, ElemType t){
    /*
     * 分两次循环完成，虽然代码组织不好但是功能可以完成
     */
    if (!L.length || (s >= t))  // not sat
        return false;
    int mark = L.length, i = 0;
    for (; i<L.length; i++) {  // find the first pos and the last pos
        if (L.data[i] >= s && mark == L.length)
            mark = i;
        if (L.data[i] > t)
            break;
    }
    int j = 0;
    for (; j<i-mark; j++){  // move the element
        if (i < L.length)
            L.data[mark + j] = L.data[i];
        else
            break;
    }
    L.length -= j;  // update the length
    return true;
}

bool DelST_1(SqList &L, ElemType s, ElemType t){
    /*
     * 充分利用循环语句，在循环语句中使用多重判断和多重改变，又充分利用循环变量作为其他值的数据来源
     */
    int i, j;
    if (s >= t || L.length == 0)  // not sat
        return false;
    for (i=0; i<L.length&&L.data[i]<s; i++);  // find start
    if (i >= L.length)
        return false;
    for (j=i; j<L.length&&L.data[j]<=t; j++);  // find end
    for (; j<L.length;i++, j++)  // move data
        L.data[i] = L.data[j];
    L.length = j;  // set new length
    return true;
}

bool DelSTN(SqList &L, ElemType s, ElemType t){
    /*
     * 每找到一个不合适的值就将表尾的元素放入该位置进行替换，同时表长度减
     * 缺点是破坏了表中元素的相对位置
     */
    if (!L.length || s >= t)  // not sat
        return false;
    for (int i=0; i<L.length; i++){
        if (L.data[i] >= s && L.data[i] <= t){  // find the number in [s, t]
            L.data[i] = L.data[L.length - 1];  // set with the last number
            L.length --;
        }
    }
    return true;
}


bool DelSTN_1(SqList &L, ElemType s, ElemType t){
    /*
     * 删除表中所有大于等于s小于等于t的元素
     * 保持了原来线性表的相对顺序不变
     */
    if (!L.length && s >= t)  // not sat
        return false;
    int k = 0, i = 0;
    for (; i<L.length; i++){
        if (L.data[i] >= s || L.data[i] <= t)  // count the sat number
            k ++;
        else
            L.data[i - k] = L.data[i];  // set the data[i - k] = data[i]
    }
    L.length -= k;
    return true;
}


bool DisDel(SqList &L){
    /*
     * 删除有序顺序表中重复的元素
     * 记录上一次的值并设定一个偏移量，循环偏移完成
     */
    if (!L.length)
        return false;
    int k=0, i;
    ElemType last = L.data[0];
    for (i = 1; i < L.length; i++){
        if (last == L.data[i]){  // same element, k++
            k ++;
        }
        else{
            L.data[i - k] = L.data[i];  // different element, data[i - k] = data[i]
        }
        last = L.data[i];
    }
    L.length -= k;
    return true;
}


bool DisDel_1(SqList &L){
    /*
     * 删除有序顺序表中重复的元素
     * j增长速度远快于i，故对前面元素的修改不会影响到后面的效果，即重置data[i]即可
     */
    if (L.length == 0)
        return false;
    int i, j;
    for (i=0, j=1; j < L.length; j++){
        if (L.data[j] != L.data[i])  // new value appeared, add into data[i++]
            L.data[++i] = L.data[j];
    }
    L.length = i + 1;  // set new length = i + 1
    return true;
}


bool Merge(SqList a, SqList b, SqList &c){
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
    while (i < a.length){  // set the spare value into c
        c.length ++;
        c.data[c.length - 1] = a.data[i];
    }
    while  (j < b.length){
        c.length ++;
        c.data[c.length - 1] = b.data[j];
    }
    return true;
}


bool ReverseArray(ElemType A[], int s, int t, int arraySize){
    /*
     * 数组逆序，为交换两个数组块准备
     */
    if (s >= t || t >= arraySize)
        return false;
    ElemType temp;
    int mid = (s + t) / 2;  // get mid
    for (int i = 0; i <= mid; i++){  // exchange the A[i] and A[t - i]
        temp = A[i];
        A[i] = A[t - i];
        A[t - i] = temp;
    }
    return true;
}


void ExchangeList(ElemType A[], int n, int m, int arraySize){
    /*
     * 交换两个数组块的顺序
     * 逆序总数组-逆序前n个-逆序后m个
     */
    ReverseArray(A, 0, n + m - 1, arraySize);
    ReverseArray(A, 0, n - 1, arraySize);
    ReverseArray(A, n, n + m - 1, arraySize);
}


void FindExchangeInsert(ElemType A[], ElemType searchNum, int arraySize){
    /*
     * 在递增顺序表中找到目标值，找到则将该值与后继节点交换，找不到则在正确位置插入目标值
     * 使用二分查找，充分利用low和high的性质判断是否成功找到元素值，并据此获得移动的长度
     */
    int low = 0, high = arraySize - 1, mid = 0;
    while (low <= high){  // binary search
        mid = (low + high) / 2;
        if (A[mid] == searchNum)
            break;
        else if (A[mid] < searchNum)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (A[mid] == searchNum && mid < arraySize - 1){  // A[mid] is the number, exchange value if mid is not the last num
        ElemType temp = A[mid];
        A[mid] = A[mid + 1];
        A[mid + 1] = temp;
    }
    if (low > high){  // 404, insert searchValue into A[low]
        for (int i = arraySize - 1; i > high; i --){
            A[i + 1] = A[i];
        }
        A[low] = searchNum;
    }
}


int main() {
    cout << "Hello, World!" << endl;
    return 0;
}