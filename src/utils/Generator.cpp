#include "../../include/utils/Generator.h"
#include <random>
#include <climits>
#include <iostream>

using namespace std;

namespace {
    random_device rd;
    mt19937 rng(rd());

    struct EdgePair{
        int source, destination;
    };

    bool isEdgeUsed(EdgePair* edges, int size, int source, int destination, bool directed){
        for (int i=0; i<size; ++i){
            if (edges[i].source==source && edges[i].destination==destination)
                return true;
            if (!directed && edges[i].source == destination && edges[i].destination==source)
                return true;
        }
        return false;
    }

    int randBigInt(){
        uniform_int_distribution<int> dist(1, INT_MAX);
        return dist(rng);
    }

    void shuffle(int* array, int size){
        for (int i=size-1; i> 0; --i){
            int j=rng()%(i+1);
            int temp = array[i];
            array[i]=array[j];
            array[j]=temp;
        }
    }

    int calculateMaxEdges(int vertices, bool directed){
        return directed ? vertices*(vertices-1)
                        : vertices*(vertices-1)/2;
    }

    int calculateTargetEdges(int vertices, int density, bool directed){
        int maxEdges = calculateMaxEdges(vertices, directed);
        return (density*maxEdges)/100;
    }
}


void Generator::generateConnectedGraph(AdjacencyList &graph, int density, bool directed) {
    if (density < 1 || density > 100) {
        throw invalid_argument("Gestosc musi byc w zakresie 1-100%");
    }
    if (graph.getVertexCount() <= 0) {
        throw invalid_argument("Graf musi miec przynajmniej jeden wierzcholek");
    }
    int V = graph.getVertexCount();
    int edgeTarget = calculateTargetEdges(V, density, directed);

    auto* used = new EdgePair[edgeTarget];
    int usedCount = 0;

    // drzewo rozpinajace
    int* vercites = new int [V];
    for (int i=0; i<V; ++i)
        vercites[i]=i;
    shuffle(vercites, V);

    for (int i=1; i< V; ++i){
        uniform_int_distribution<int> dist(0, i-1);
        int source = vercites[dist(rng)];
        int destination = vercites[i];
        if(!isEdgeUsed(used, usedCount, source, destination, directed)){
            int weight = randBigInt();
            graph.addEdge(source, destination, weight);
            used[usedCount++] = {source, destination};
        }
    }

    // losowe krawiedzie
    while (graph.getEdgeCount()<edgeTarget){
        int source = rng()%V;
        int destination = rng()%V;
        if (source==destination) continue;
        if(isEdgeUsed(used, usedCount, source, destination, directed)) continue;
        int weight = randBigInt();
        graph.addEdge(source, destination, weight);
        used[usedCount++]={source, destination};
    }
    delete[] used;
    delete[] vercites;
}
