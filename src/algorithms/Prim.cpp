#include "../../include/algorithms/Prim.h"
#include <iostream>
#include <limits>

using namespace std;

Edge* Prim::run(const AdjacencyList &graph, int startVertex, int* edgeCount) {
    int V = graph.getVertexCount();
    const int inf = numeric_limits<int>::max();

    if (startVertex < 0 || startVertex >= V) {
        *edgeCount = 0;
        return nullptr;
    }
    if (V <= 1) {
        *edgeCount = 0;
        return nullptr;
    }

    bool* visited = new bool[V];
    auto* key = new long long[V];      // minimalne koszty
    auto* parent = new long long[V]; // poprzednik

    for (int i=0; i<V; ++i){
        visited[i] = false;
        key[i] = inf;
        parent[i] = -1;
    }

    key[startVertex] = 0;


    for (int count = 0; count < V-1; ++count) {
        int u=-1;
        int minWeight = inf;

        for (int i=0; i<V; ++i){
            if (!visited[i]&&key[i]<minWeight){
                minWeight=key[i];
                u=i;
            }
        }

        if(u==-1) break;
        visited[u] = true;

        ListNode* neighbour = graph.getAdjList(u);
        while(neighbour!= nullptr){
                int v = neighbour->destination;
                int w = neighbour->weight;
                if (!visited[v] && w<key[v]){
                    key[v] = w;
                    parent[v]=u;
                }
                neighbour=neighbour->next;
            }
        }


    *edgeCount = 0;
    for (int i =0; i<V; ++i){
        if (parent[i]!=-1){
            (*edgeCount)++;
        }
    }

    Edge* mst = new Edge[*edgeCount];
    int index = 0;
    for (int i=0; i < V; ++i){
        if(parent[i]!=-1)
            mst[index++] = Edge(parent[i],i, key[i]);
    }


    delete[] visited;
    delete[] key;
    delete[] parent;
    return mst;
}


Edge* Prim::run(const IncidenceMatrix &graph, int startVertex, int *edgeCount) {
    AdjacencyList temp = graph.toList();
    return run(temp, startVertex, edgeCount);
}