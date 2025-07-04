#ifndef AIZO_2_ADJACENCYLIST_H
#define AIZO_2_ADJACENCYLIST_H

#include "Edge.h"
#include "IncidenceMatrix.h"

struct ListNode{
    int destination;
    int weight;
    ListNode* next;
};

class AdjacencyList {
public:
    AdjacencyList(int vertices, bool directed);
    ~AdjacencyList();

    void addEdge(int source, int destination, int weight);
    void display() const;
    IncidenceMatrix toMatrix() const;

    double getDensity() const;
    int getVertexCount() const;
    int getEdgeCount() const;
    bool getIsDirected() const;
    ListNode* getAdjList(int vertex) const;

private:
    int vertexCount;
    ListNode** adjLists;
    int edgeCount;
    bool isDirected;
};


#endif //AIZO_2_ADJACENCYLIST_H
