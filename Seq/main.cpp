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


int main() {
    cout << "Hello, World!" << endl;
    return 0;
}