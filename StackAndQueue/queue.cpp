//
// Created by 44797 on 2019/10/21.
//

#include <malloc.h>

#define MaxSize 50

typedef int ElemType;

typedef struct {
    /*
     * 定义队列
     */
    ElemType data[MaxSize];
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


bool EnQueue(SqQueue &Q, ElemType x) {
    /*
     * 进队操作
     */
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}


bool DeQueue(SqQueue &Q, ElemType &x) {
    /*
     * 出队操作
     */
    if (Q.rear == Q.front)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}


typedef struct LinkNodeQ{
    /*
     * 链队结构节点
     */
    ElemType data;
    struct LinkNodeQ *next;
} LinkNodeQ;


typedef struct{
    /*
     * 链队的指针
     */
    LinkNodeQ *front, *rear;
} LinkQueue;


void InitQueue(LinkQueue &Q){
    /*
     * 初始化队列
     */
    Q.front = (LinkNodeQ *)malloc(sizeof(LinkNodeQ));
    Q.rear = Q.front;
    Q.front->next = NULL;
}


bool isEmpty(LinkQueue &Q){
    /*
     * 判空
     */
    return Q.rear == Q.front;
}


void EnQueue(LinkQueue &Q, ElemType x){
    /*
     * 进队
     */
    LinkNodeQ *s = (LinkNodeQ *)malloc(sizeof(LinkNodeQ));
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}


bool DeQueue(LinkQueue &Q, ElemType &x){
    /*
     * 出队
     */
    if (Q.rear == Q.front)
        return false;
    LinkNodeQ *p = Q.front->next;
    x = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)  // 防止只有一个数据节点
        Q.front = Q.rear;
    free(p);
    return true;
}
