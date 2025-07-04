#include "../../include/algorithms/BellmanFord.h"
#include <iostream>
#include <limits>

using namespace std;

int* BellmanFord::run(const IncidenceMatrix &graph, int startVertex, int endVertex, long long* length, long long* cost) {
    int V = graph.getVertexCount();
    int E = graph.getEdgeCount();
    const int inf = numeric_limits<int>::max();

    auto* distance = new long long[V];
    auto* predecessor = new long long[V];


    if (startVertex < 0 || startVertex >= V || endVertex < 0 || endVertex >= V) {
        *length = -1;
        *cost = -1;
        return nullptr;
    }
    if (V <= 0 || E <= 0) {
        *length = -1;
        *cost = -1;
        return nullptr;
    }

    for (int i=0; i<V; ++i){
        distance[i]=inf;
        predecessor[i] = -1;
    }
    distance[startVertex] = 0;

    bool changed;
    for (int i =0; i<V-1; ++i){
        changed= false;
        for (int j=0; j<E; ++j){
            Edge edge = graph.getEdge(j);
            int u = edge.source;
            int v = edge.destination;
            long long w = edge.weight;

            if (distance[u]!=inf && distance[u]+w<distance[v]){
                distance[v] = distance[u]+w;
                predecessor[v] = u;
                changed=true;
            }
        }
        if (!changed) break;
    }

    for (int j=0; j<E; ++j){
        Edge edge = graph.getEdge(j);
        int u = edge.source;
        int v = edge.destination;
        long long w = edge.weight;
        if (distance[u]!=inf && distance[u]+w<distance[v]){
            delete[] distance;
            delete[] predecessor;
            *length = -1;
            *cost = -1;
            return nullptr;
        }
    }

    if (distance[endVertex] == inf) {
        delete[] distance;
        delete[] predecessor;
        *length = 0;
        *cost = -1;
        return nullptr;
    }


    auto* temp = new long long[V];
    long long len=0;
    for (long long v=endVertex; v!=-1; v=predecessor[v]) temp[len++]=v;
    auto* path = new long long[len];
    for (int i=0; i<len; ++i) path[i]=temp[len-1-i];
    *length=len;
    *cost = distance[endVertex];

    delete[] temp;
    delete[] distance;
    delete[] predecessor;
    return reinterpret_cast<int *>(path);
}


int* BellmanFord::run(const AdjacencyList &graph, int startVertex, int endVertex, long long *length, long long *cost) {
    IncidenceMatrix temp = graph.toMatrix();
    return run(temp, startVertex, endVertex, length, cost);
}