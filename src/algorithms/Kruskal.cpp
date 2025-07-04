#include "../../include/algorithms/Kruskal.h"
#include <iostream>

using namespace std;

class DisjointSet{
private:
    int* parent;
    int* rank;
    int size;

public:
    DisjointSet(int n){
        size = n;
        parent= new int[n];
        rank = new int[n];
        for (int i=0; i< n; ++i){
            parent[i]=i;
            rank[i]=0;
        }
    }

    int find(int u){
        if (parent[u]!= u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v){
        u = find(u);
        v = find(v);
        if (u==v) return;

        if (rank[u]<rank[v]){
            parent[u] = v;
        } else if (rank[u]>rank[v]){
            parent[v] = u;
        } else {
            parent[v] = u;
            rank[u]++;
        }
    }

    ~DisjointSet(){
        delete[] parent;
        delete[] rank;
    }
};


void bubbleSort(Edge* edges, int count){
    for (int i=0; i<count-1; ++i){
        for (int j=0; j<count-i-1; ++j){
            if (edges[j].weight > edges[j+1].weight){
                Edge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }
}

Edge * Kruskal::run(const IncidenceMatrix &graph) {
    int V = graph.getVertexCount();
    int E = graph.getEdgeCount();


    Edge* edges = new Edge[E];
    Edge* result = new Edge[V-1];
    for (int i=0; i<E; ++i){
        edges[i] = graph.getEdge(i);
    }

    bubbleSort(edges, E);
    DisjointSet ds(V);


    int edgeCount = 0;
    for (int i=0; i<E && edgeCount<V-1; ++i){
        int u = edges[i].source;
        int v = edges[i].destination;
        if (ds.find(u) != ds.find(v)){
            result[edgeCount++] = edges[i];
            ds.unite(u, v);
        }
    }
    delete[] edges;
    return result;
}


Edge* Kruskal::run(const AdjacencyList &graph) {
    IncidenceMatrix tmp = graph.toMatrix();
    return run(tmp);
}