#ifndef AIZO_2_GRAPHLOADER_H
#define AIZO_2_GRAPHLOADER_H

#include <string>
#include "../graph/AdjacencyList.h"
#include "../graph/IncidenceMatrix.h"

using namespace std;

class GraphLoader {
public:
    static IncidenceMatrix* loadToMatrix(const string& filename, bool directed);
    static AdjacencyList* loadToList(const string& filename, bool directed);

};


#endif //AIZO_2_GRAPHLOADER_H
