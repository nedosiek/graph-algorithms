#ifndef AIZO_2_KRUSKAL_H
#define AIZO_2_KRUSKAL_H

#include "../graph/IncidenceMatrix.h"
#include "../graph/AdjacencyList.h"

class Kruskal {
public:
    static Edge * run(const IncidenceMatrix& graph);
    static Edge* run(const AdjacencyList& graph);

};


#endif //AIZO_2_KRUSKAL_H
