#ifndef AIZO_2_INCIDENCEMATRIX_H
#define AIZO_2_INCIDENCEMATRIX_H

#include "Edge.h"
//#include "AdjacencyList.h"
class AdjacencyList;

class IncidenceMatrix {
public:
    IncidenceMatrix(int vertices, int maxEdges, bool directed);
    ~IncidenceMatrix();

    void addEdge(int source, int destination, int weight);
    int getWeight(int source, int edgeIndex) const;
    void display() const;
    int getVertexCount() const;
    int getEdgeCount() const;
    double getDensity() const;
    Edge getEdge(int index) const;
    AdjacencyList toList() const;

private:
    int** matrix;
    Edge* edges;
    int vertexCount;
    int edgeCapacity;
    int edgeCount;
    bool isDirected;
};


#endif //AIZO_2_INCIDENCEMATRIX_H
