#include "../../include/graph/AdjacencyList.h"

#include <iostream>
using namespace std;

AdjacencyList::AdjacencyList(int vertices, bool directed)
: vertexCount(vertices), edgeCount(0), isDirected(directed)
{
    if (vertices<=0) throw invalid_argument("liczba wierzcholkow ma byc dodania!");
    adjLists = new ListNode * [vertexCount];
    for (int i =0; i< vertexCount; ++i){
        adjLists[i] = nullptr;
    }
}

AdjacencyList::~AdjacencyList(){
    for (int i=0; i< vertexCount; ++i){
        ListNode* current = adjLists[i];
        while(current!= nullptr){
            ListNode* temp = current;
            current = current-> next;
            delete temp;
        }
        adjLists[i]= nullptr;
    }
    delete[] adjLists;
    adjLists= nullptr;
}

void AdjacencyList::addEdge(int source, int destination, int weight) {
    if (source <0 || source >= vertexCount || destination<0 || destination>=vertexCount) throw out_of_range("Niepoprawne wierzcholki");
    if(weight<=0) throw invalid_argument("waga musi byc dodatnia!");
    ListNode* node = new ListNode{destination, weight, adjLists[source]};
    adjLists[source] = node;
    ++edgeCount;
    if(!isDirected){
        ListNode* reverseNode = new ListNode{source, weight, adjLists[destination]};
        adjLists[destination] = reverseNode;
        ++edgeCount;
    }
}

double AdjacencyList::getDensity() const {
    int actualEdges = getEdgeCount();
    int maxEdges = isDirected
            ? vertexCount*(vertexCount-1)
            : vertexCount*(vertexCount-1)/2;

    if (maxEdges==0) return 0.0;
    return static_cast<double>(actualEdges)/maxEdges*100.0;
}

void AdjacencyList::display() const {
    cout << "Lista sasiedztwa:\n";
    for (int i=0; i<vertexCount; ++i){
        cout << i << ":";
        ListNode* current = adjLists[i];
        while (current!= nullptr){
            cout << " -> (" << current->destination << ", " << current -> weight << ")";
            current = current->next;
        }
        cout << "\n";
    }
}

IncidenceMatrix AdjacencyList::toMatrix() const {
    IncidenceMatrix matrix(vertexCount, edgeCount, isDirected);
    for (int u=0; u<vertexCount; ++u){
        ListNode* current= adjLists[u];
        while(current!= nullptr){
            matrix.addEdge(u, current->destination, current->weight);
            current=current->next;
        }
    }
    return matrix;
}

int AdjacencyList::getVertexCount() const {
    return vertexCount;
}

int AdjacencyList::getEdgeCount() const {
    return isDirected? edgeCount : edgeCount/2;
}

bool AdjacencyList::getIsDirected() const {
    return isDirected;
}

ListNode* AdjacencyList::getAdjList(int vertex) const {
    return adjLists[vertex];
}