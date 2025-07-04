#include "../../include/graph/IncidenceMatrix.h"
#include "../../include/graph/AdjacencyList.h"

#include <iostream>
#include <iomanip>
using namespace std;


IncidenceMatrix::IncidenceMatrix(int vertices, int maxEdges, bool directed)
: vertexCount(vertices), edgeCapacity(maxEdges), edgeCount(0), isDirected(directed)
{
    if (vertices<=0 || maxEdges<=0) invalid_argument("Liczba wierzcholkow i krawedzi musi byc dodatnia!");
    matrix = new int*[vertexCount];
    for (int i=0; i<vertexCount; ++i){
        matrix[i] = new int[edgeCapacity];
        for (int j=0; j<edgeCapacity; ++j){
            matrix[i][j]=0; // brak krawedzi domyslnie
        }
    }
    edges = new Edge[edgeCapacity];
}

IncidenceMatrix::~IncidenceMatrix(){
    for (int i=0; i<vertexCount; ++i){
        delete[] matrix[i];
        matrix[i] = nullptr;
    }
    delete[] matrix;
    delete[] edges;
}

void IncidenceMatrix::addEdge(int source, int destination, int weight) {
    if (source<0 || source>=vertexCount || destination<0 || destination>=vertexCount) out_of_range("Niepoprawne wierzcholki krawedzi");
    if (weight<=0) invalid_argument("Waga ma byc dodatnia!");
    if (edgeCount >= edgeCapacity){
        cerr << "Przekroczono maksymalna liczbe krawedzi!" << endl;
        return ;
    }

    edges[edgeCount] = Edge(source, destination, weight);

    if(isDirected){
        matrix[source][edgeCount] = +weight;
        matrix[destination][edgeCount] = - weight;
    } else {
        matrix[source][edgeCount] = +weight;
        matrix[destination][edgeCount] = +weight;
    }
    ++edgeCount;
}

int IncidenceMatrix::getWeight(int source, int destination) const {
    return matrix[source][destination];
}

int IncidenceMatrix::getVertexCount() const {
    return vertexCount;
}

int IncidenceMatrix::getEdgeCount() const {
    return edgeCount;
}

double IncidenceMatrix::getDensity() const {
    int maxEdges = isDirected
            ? vertexCount*(vertexCount-1)
            : vertexCount*(vertexCount-1)/2;
    if (maxEdges==0) return 0.0;
    return static_cast<double>(edgeCount)/maxEdges*100.0;
}

void IncidenceMatrix::display() const {
    cout << "Macierz incydencji:\n";
    for (int i=0; i<vertexCount; ++i){
        for (int j=0; j < edgeCount; ++j){
            cout << setw(4) << matrix[i][j];
        }
        cout << "\n";
    }
}

AdjacencyList IncidenceMatrix::toList() const {
    AdjacencyList list(vertexCount, isDirected);
    for (int i=0; i<edgeCount; ++i){
        list.addEdge(edges[i].source, edges[i].destination, edges[i].weight);
    }
    return list;
}

Edge IncidenceMatrix::getEdge(int index) const {
    if (index < edgeCount)
        return edges[index];
    return {-1, -1, -1};
}
