#ifndef AIZO_2_BELLMANFORD_H
#define AIZO_2_BELLMANFORD_H

#include "../graph/IncidenceMatrix.h"
#include "../graph/AdjacencyList.h"

class BellmanFord {
public:
    static int* run(const IncidenceMatrix& graph, int startVertex, int endVertex, long long* length, long long* cost);
    static int* run(const AdjacencyList& graph, int startVertex, int endVertex, long long* length, long long* cost);
};


#endif //AIZO_2_BELLMANFORD_H
