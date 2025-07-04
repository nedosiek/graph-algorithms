#ifndef AIZO_2_DIJKSTRA_H
#define AIZO_2_DIJKSTRA_H

#include "../graph/AdjacencyList.h"

class Dijkstra {
public:
    static int * run(const AdjacencyList& graph, int startVertex, int endVertex, long long* length, long long* cost);
    static int * run(const IncidenceMatrix& graph, int startVertex, int endVertex, long long* length, long long* cost);

};


#endif //AIZO_2_DIJKSTRA_H
