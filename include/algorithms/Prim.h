#ifndef AIZO_2_PRIM_H
#define AIZO_2_PRIM_H

#include "../graph/AdjacencyList.h"
#include "../graph/IncidenceMatrix.h"

class Prim {
public:
    static Edge* run(const AdjacencyList& graph, int startVertex, int* edgeCount);
    static Edge* run(const IncidenceMatrix& graph, int startVertex, int* edgeCount);
};


#endif //AIZO_2_PRIM_H
