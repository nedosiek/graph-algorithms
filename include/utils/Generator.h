#ifndef AIZO_2_GENERATOR_H
#define AIZO_2_GENERATOR_H

#include "../graph/AdjacencyList.h"
#include "../graph/IncidenceMatrix.h"

class Generator {
public:
    static void generateConnectedGraph(IncidenceMatrix& graph, int density, bool directed);
    static void generateConnectedGraph(AdjacencyList& graph, int density, bool directed);

};


#endif //AIZO_2_GENERATOR_H
