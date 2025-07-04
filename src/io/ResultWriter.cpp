#include "../../include/io/ResultWriter.h"
#include "../../include/graph/AdjacencyList.h"
#include "../../include/graph/IncidenceMatrix.h"
#include "../../include/utils/CParser.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;


bool ResultWriter::writeResult(const char *filename, const Edge *edges, int edgeCount, int vertexCount) {
    if (!edges || edgeCount<=0 || vertexCount <=0) return false;
    ofstream file(filename);
    if (!file.is_open())
        return false;

    file << edgeCount << "\t" << vertexCount << "\n";
    for (int i=0; i<edgeCount; ++i){
        file << edges[i].source << "\t" << edges[i].destination << "\t" << edges[i].weight << "\n";
    }

    file.close();
    return true;
}


bool ResultWriter::writeMST(const char *filename, const Edge *edges, int edgeCount, long long totalWeight, const AdjacencyList* graph, Representation rep) {
    if (!edges || edgeCount<=0 || !graph) return false;
    ofstream file(filename);
    if(!file.is_open())
        return false;



    file << "MST Krawedzi (" << edgeCount << " krawedzi, koszt: " << totalWeight << "):\n";
    for (int i=0; i<edgeCount; ++i) {
        file << edges[i].source << "\t" << edges[i].destination << "\t" << edges[i].weight << "\n";
    }
    file << "\n";

    if (rep==rep_list){
        file << "Lista sasiedztwa:\n";
        for (int i=0; i<graph->getVertexCount(); ++i){
            file << i << ":";
            ListNode* node = graph->getAdjList(i);
            while (node){
                file << "-> (" << node->destination << ", " << node->weight << ")";
                node = node->next;
            }
            file << "\n";
        }
    } else if (rep==rep_matrix){
        IncidenceMatrix matrix=graph->toMatrix();
        file << "Macierz incydencji:\n";
        for (int i = 0; i<matrix.getVertexCount(); ++i){
            for (int j=0; j<matrix.getEdgeCount(); ++j){
                file << matrix.getWeight(i, j) << " ";
            }
            file << "\n";
        }
    }

    file.close();
    return true;
}

bool ResultWriter::writeSP(const char *filename, const int *path, int pathLength, long long total, const AdjacencyList* graph, Representation rep) {
    if (!path || pathLength<0 || !graph) return false;
    ofstream file(filename);
    if(!file.is_open())
        return false;


    file << "Najkrotsza sciezka (koszt: " << total << "):\n";
    for (int i=0; i<pathLength; ++i){
        file << path[i];
        if (i!=pathLength-1){
            file << " -> ";
        }
    }
    file << "\n";

    if (rep==rep_list){
        file << "Lista sasiedztwa:\n";
        for (int i=0; i<graph->getVertexCount(); ++i){
            file << i << ":";
            ListNode* node = graph->getAdjList(i);
            while (node){
                file << "-> (" << node->destination << ", " << node->weight << ")";
                node = node->next;
            }
            file << "\n";
        }
    } else if (rep==rep_matrix){
        IncidenceMatrix matrix=graph->toMatrix();
        file << "Macierz incydencji:\n";
        for (int i = 0; i<matrix.getVertexCount(); ++i){
            for (int j=0; j<matrix.getEdgeCount(); ++j){
                file << matrix.getWeight(i, j) << " ";
            }
            file << "\n";
        }
    }


    file.close();
    return true;
}

