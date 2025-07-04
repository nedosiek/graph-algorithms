#ifndef AIZO_2_RESULTWRITER_H
#define AIZO_2_RESULTWRITER_H

#include "../graph/Edge.h"
#include "../utils/CParser.h"
#include "../graph/AdjacencyList.h"

class ResultWriter {
public:
    static bool writeResult(const char* filename, const Edge* edges, int edgeCount, int vertexCount);
    static bool writeMST(const char* filename, const Edge* edges, int edgeCount, long long totalWeight, const AdjacencyList* graph, Representation rep);
    static bool writeSP(const char* filename, const int* path, int pathLength, long long total, const AdjacencyList* graph, Representation rep);
};


#endif //AIZO_2_RESULTWRITER_H
