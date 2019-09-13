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


int main() {
    cout << "Hello, World!" << endl;
    return 0;
}