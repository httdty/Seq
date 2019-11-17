//
// Created by 44797 on 2019/11/13.
//

#include <iostream>

typedef int ElemType;

typedef struct {
    ElemType *elem;
    int TableLen;
} SSTable;

// 顺序查找
int Search_Seq(SSTable ST, ElemType key) {
    ST.elem[0] = key;
    for (int i = ST.TableLen; ST.elem[0] != key; i--);
    return i;
}

// 二分查找（折半查找）
int Binary_Search(SSTable L, ElemType key) {
    int low = 0, high = L.TableLen - 1; mid;
    while (low <= high){  // 这里有等号
        mid = (low + high) / 2;
        if (L.elem[mid] == key)
            return mid;
        if (L.elem[mid] > key)
            high = mid - 1;  // 省去一个
        else
            low = mid + 1;  // 省去一个
    }
    return -1;
}
