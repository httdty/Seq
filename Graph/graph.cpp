//
// Created by 44797 on 2019/11/5.
//

#include <iostream>

#define MaxVertexNum 100
#define MAX 99999;


typedef char VertexType;

typedef int EdgeType;

// 图的邻接矩阵法存储
typedef struct {
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;  // 节点数量和边的数量
} MGrpah;

// 图的邻接矩阵法表示——邻接表法
typedef struct ArcNode {
    int adjvex;
    struct ArcNode *next;
    // 权值部分可加入
} ArcNode;

// 图的邻接矩阵法表示——顶点表
typedef struct VNode {
    VertexType data;
    ArcNode *first;
} VNOode, AdjList[MaxVertexNum];

// 图的邻接矩阵法表示——邻接表
typedef struct {
    AdjList vetices;
    int vexnum, arcnum;
} ALGraph;

// 图的十字链表法——边表
typedef struct ArcNodeC {
    int tailvex, headvex;
    struct ArcNode *hlink, *tlink;
    // InfoType info;
} ArcNodeC;

// 图的十字链表法——顶点表
typedef struct VNodeC {
    VertexType data;
    ArcNodeC *firstin, *firstout;
} VNodeC;

// 图的十字链表法——十字链表
typedef struct {
    VNodeC xlist[MaxVertexNum];
    int vexnum, arcnum;
} GLGraph;

// 图的邻接多重表法——边表
typedef struct ArcNodeM {
    int ivex, jvex;
    struct ArcNodeM *ilink, *jlink;
    // InfoType info
    // bool mark
} ArcNodeM;

// 图的邻接多重表法——顶点表
typedef struct VNodeM {
    VertexType data;
    ArcNodeM *firstedge;
} VNodeM;

// 图的邻接多重表法——邻接多重表
typedef struct {
    VNodeM adjmulist[MaxVertexNum];
    int vexnum, arcnum;
} AMLGraph;


// 图的BFS算法实现
// 空间复杂度O(|V|)
// 时间复杂度：邻接矩阵O(|V|^2)
// 时间复杂度：邻接表O(|V|+|E|)

bool visited[MaxVertexNum];
Queue Q = NULL;

void BFSTraverse(Graph G) {
    int i;
    for (i = 0; i < G.vexnum; ++i)
        visited[i] = false;
    InitQueue(Q);
    for (i = 0; i < G.vexnum; ++i)
        if (!visited[i])
            BFS(G, i);
}

void BFS(Graph G, int v) {
    visit(v);
    visited[v] = true;
    EnQueue(Q, v);
    while (!isEmpty(Q)) {
        DeQueue(Q, v);
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
            if (!visited[w]) {
                visit(w);
                visited[w] = true;
                EnQueue(Q, w);
            }
    }
}

// 无权图单源最短路径算法

void BFS_MIN_Distance(Graph G, int u) {
    int d[MaxVertexNum];
    for (int i = 0; i < G.vexnum; i++)
        d[i] = MAX;
    visited[u] = true;
    d[u] = 0;
    EnQueue(Q, u);
    while (!isEmpty(Q)) {
        DeQueue(Q, u);
        for (int w = FirstNeighbor(G, u); w >= 0; w = NextNeighbor(G, u, w))
            if (!visited[w]) {
                visited[w] = true;
                d[w] = d[u] + 1;
                EnQueue(Q, w);
            }
    }
}


// 图的DFS算法实现
// 空间复杂度O(|V|)
// 时间复杂度：邻接矩阵O(|V|^2)，邻接表O(|V|+|E|)

//bool visited[MaxVertexNum];
void DFSTraverse(Graph G) {
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for (int i = 0; i < G.vexnum; i++)
        if (!visited[i])
            DFS(G, i);
}

void DFS(Graph G, int v) {
    visit(v);
    visited[v] = true;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
        if (!visited[w])
            DFS(G, w);
}


// Prim算法实现
// 时间复杂度O(|V|^2)，适合稠密图

void MST_Prim(Graph G) {
    int min_weight[G.vexnum];
    int adjvex[G.vexnum];
    for (int i = 0; i < G.vexnum; i++) {
        min_weight[i] = G.Edge[0][i];
        adjvex[i] = 0;
    }

    int min_arc;
    int min_vex = 0;
    for (int i = 1; i < G.vexnum; i++) {
        min_arc = MAX;
        for (int j = 0; j < G.vexnum; j++) {
            if (min_weight[j] != 0 && min_weight[j] < min_arc) {
                min_arc = min_weight[j];
                min_vex = j;
            }
        }
        min_weight[min_vex] = 0;
        for (int j = 0; j < G.vexnum; j++) {
            if (min_weight[j] != 0 && G.Edge[min_vex][j] < min_weight[j]) {
                min_weight[j] = G.Edge[min_vex][j];
                adjvex[j] = min_vex;
            }
        }
    }
}


// Kruskal算法实现
// 时间复杂度O(|E|log|E|)，适合稀疏图


typedef struct Edge {
    int a, b;
    int weight;
} Edge;

void MST_Kruscal(Graph G, Edge *edges, int *parent) {
    heap_sort(edges);
    Initial(parent);
    for (int i = 0; i < G.arcnum; i++) {
        int a_root = Find(parent, edges[i].a);
        int b_root = Find(parent, edges[i].b);
        if (a_root != b_root)
            Union(parent, a_root, b_root);
    }
}


// Dijkstra算法实现
// 时间复杂度为O(|V|^2)
// 限制：不能有负边

void Dijkstra(Graph G, int v) {
    // 初始化
    int s[G.vexnum];
    int path[G.vexnum];
    int dist[G.vexnum];

    for (int i = 0; i < G.vexnum; i++) {
        dist[i] = G.edge[v][i];
        s[i] = 0;
        if (G.edge[v][i] < MAX)
            path[i] = G.edge[v][i];
        else
            path[i] = -1;
    }
    s[v] = 1;
    path[v] = -1;

    // 求解
    for (int i = 0; i < G.vexnum; i++) {
        int min = MAX;
        int u = 0;
        for (int j = 0; j < G.vexnum; j++) {
            if (s[i] == 0 && dist[j] < min){
                min = dist[j];
                u = j;
            }
        }
        s[u] = 1;
        for (int j = 0; j < G.vexnum; j++){
            if (s[j] == 0 && dist[u] + G.edge[u][j] < dist[j]){
                dist[j] = dist[u] + G.edge[u][j];
                path[j] = u;
            }
        }
    }
}


// Floyd算法实现
// 时间复杂度O(|V|^3)

void Floyd(Graph G){
    int A[G.vexnum][G.vexnum];
    for (int i = 0; i < G.vexnum; i ++)
        for (int j = 0; j < G.vexnum; j++)
            A[i][j] = G.Edge[i][j];
    for (int k = 0; k < G.vexnum; k++)
        for (int i = 0; i < G.vexnum; i++)
            for (int j = 0; j < G.vexnum; j++)
                if (A[i][j] > A[i][k] + A[k][j])
                    A[i][j] = A[i][k] + A[k][j];
}


// 拓扑排序算法实现
// 时间复杂度O(|V|+|E|)
// 可以用DFS实现

int indegree[G.vexnum];

bool TopologicalSort(Graph G){
    // 初始化
    Stack S = NULL;
    InitStack(S);
    int i;
    int printArray[G.vexnum];
    for (i = 0; i < G.vexnum; i++)
        if (indegree[i] == 0)
            Push(S, i);
    int count = 0;

    // 操作
    while (!isEmpty(S)){
        Pop(S, i);
        printArray[count++] = i;
        for (edge *p = G.Vertices[i].firstarc; p; p=p->nextarc){
            int v = p->adjvex;
            if (!(--indegree[v]))
                Push(S, v);
        }
    }
    return count >= G.vexnum;
}