#include "../../include/algorithms/Dijkstra.h"
#include <iostream>
#include <limits>
using namespace std;

int * Dijkstra::run(const AdjacencyList &graph, int startVertex, int endVertex, long long* length, long long* cost) {
    int V=graph.getVertexCount();
    const int inf = numeric_limits<int>::max();

    auto* distance = new long long[V];
    auto* previous = new long long[V];
    bool* visited = new bool[V];

    if (startVertex < 0 || startVertex >= V || endVertex < 0 || endVertex >= V) {
        *length = -1;
        *cost = -1;
        return nullptr;
    }
    if (V <= 0) {
        *length = -1;
        *cost = -1;
        return nullptr;
    }

    for (int i = 0; i < V; ++i) {
        ListNode* node = graph.getAdjList(i);
        while (node) {
            if (node->weight < 0) {
                *length = -2;
                *cost = -2;
                return nullptr;
            }
            node = node->next;
        }
    }

    for (int i = 0; i<V; ++i){
        distance[i] = inf;
        visited[i] = false;
        previous[i] = -1;
    }

    distance[startVertex] = 0;
    while(true){
        long long minDis = inf;
        int u = -1;

        for (int i=0; i<V; ++i){
            if(!visited[i] && distance[i]<minDis){
                minDis = distance[i];
                u = i;
            }
        }

        if (u==-1 || u==endVertex) break;
        visited[u] = true;

        ListNode* neighbour = graph.getAdjList(u);
        while (neighbour!= nullptr){
            int v = neighbour->destination;
            long long weight = neighbour->weight;
            if (!visited[v] && distance[u]!=inf && distance[u]+weight<distance[v]){
                distance[v] = distance[u] + weight;
                previous[v] = u;
            }
            neighbour = neighbour->next;
        }
    }


    if (distance[endVertex] == inf) {
        delete[] distance;
        delete[] visited;
        delete[] previous;
        *length = 0;
        *cost = -1;
        return nullptr;
    }


    long long len =0;
    auto* temp = new long long[V];
    for (long long v=endVertex; v!=-1; v=previous[v]) temp[len++] = v;
    auto* path = new long long[len];
    for (int i=0; i<len; ++i) path[i]=temp[len-1-i];

    *length=len;
    *cost = distance[endVertex];
    delete[] distance;
    delete[] visited;
    delete[] previous;
    delete[] temp;
    return reinterpret_cast<int *>(path);
}

int * Dijkstra::run(const IncidenceMatrix &graph, int startVertex, int endVertex, long long *length, long long *cost) {
    AdjacencyList tmp = graph.toList();
    return run(tmp, startVertex, endVertex, length, cost);
}