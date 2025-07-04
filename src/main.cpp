#include <iostream>
#include "../include/utils/Generator.h"
#include "../include/io/GraphLoader.h"
#include "../include/algorithms/Prim.h"
#include "../include/algorithms/Kruskal.h"
#include "../include/algorithms/Dijkstra.h"
#include "../include/algorithms/BellmanFord.h"
#include "../include/utils/CParser.h"
#include "../include/io/ResultWriter.h"
#include "../include/timer/Timer.h"
#include "../include/graph/IncidenceMatrix.h"
#include "../include/graph/AdjacencyList.h"

using namespace std;

int main(int argc, char** argv) {
    CConfig config{};
    if (!CParser::parse(argc, argv, config)) {
        return 1;
    }

    if (config.mode == mode_help) {
        cout << "FILE TEST MODE"
                "Usage:\n"
                "./YourProject --file <algorithm> <inputFile> <outputFile> <representation> [sourceVertex] [endVertex]\n"
                "<algorithm> 0-Prim, 1-Kruskal, 2-Dijkstra, 3-Bellman-Ford\n"
                "<inputFile> input file with data\n"
                "<outputFile> output file with results\n"
                "<representation> 0-adjacency list, 1-incidence matrix\n"
                "[sourceVertex] source vertex in Prim, Dijkstra and Bellman-Ford algorithms\n"
                "[endVertex] end vertex in Dijkstra and Bellman-Fors algorihms\n"

                "BENCHMARK MODE"
                "Usage:\n"
                "./YourProject --test <algorithm> <representation> <density> <vertexCount> <count> <outputFile> [sourceVertex] [endVertex]\n"
                "<algorithm> 0-Prim, 1-Kruskal, 2-Dijkstra, 3-Bellman-Ford\n"
                "<representation> 0-adjacency list, 1-incidence matrix\n"
                "<density> density of edges\n"
                "<vertexCount> number of nodes\n"
                "<count> number of repeats of the test\n"
                "<outputFile> output file with results\n"
                "[sourceVertex] source vertex in Prim, Dijkstra and Bellman-Ford algorithms\n"
                "[endVertex] end vertex in Dijkstra and Bellman-Fors algorihms\n"

                "HELP MODE"
                "Usage:\n"
                "./YourProject --help\n"
                "Displays this message.\n";

        return 0;
    }

    if (config.mode==mode_file) {
        Timer timer;
        bool directed = (config.algorithm==alg_dijkstra || config.algorithm==alg_bellmanFord);
        AdjacencyList* graphList = GraphLoader::loadToList(config.inputFile, directed);
        IncidenceMatrix* graphMatrix = GraphLoader::loadToMatrix(config.inputFile, directed);
        AdjacencyList tmp = graphMatrix->toList();
        if (!graphList || !graphMatrix) return 1;

        timer.reset();
        timer.start();
        if (config.algorithm == alg_prim) {
            int edgeCount = 0;
            Edge* mst = (config.representation==rep_list)
                    ? Prim::run(*graphList, config.sourceVertex, &edgeCount)
                    : Prim::run(*graphMatrix, config.sourceVertex, &edgeCount);
            long long totalWeight = 0;
            for (int i=0; i<edgeCount; ++i) totalWeight+=mst[i].weight;
            ResultWriter::writeMST(config.outputFile, mst, edgeCount, totalWeight, graphList, config.representation);
            delete[] mst;

        } else if (config.algorithm == alg_kruskal) {
            Edge* mst = (config.representation==rep_list)
                        ? Kruskal::run(*graphList)
                        : Kruskal::run(*graphMatrix);
            int edgeCount = graphMatrix->getVertexCount()-1;
            long long totalWeight = 0;
            for (int i=0; i<edgeCount; ++i) totalWeight+=mst[i].weight;
            ResultWriter::writeMST(config.outputFile, mst, edgeCount, totalWeight, &tmp, config.representation);
            delete[] mst;

        } else if (config.algorithm == alg_dijkstra) {
            int* path = nullptr;
            long long length = 0;
            long long cost = 0;
            path = (config.representation==rep_list)
                    ? Dijkstra::run(*graphList, config.sourceVertex, config.destinationVertex, &length, &cost)
                    : Dijkstra::run(*graphMatrix, config.sourceVertex, config.destinationVertex, &length, &cost);
            ResultWriter::writeSP(config.outputFile, path, length, cost, graphList, config.representation);
            delete[] path;

        } else if (config.algorithm == alg_bellmanFord) {
            int* path = nullptr;
            long long length = 0;
            long long cost = 0;
            path = (config.representation==rep_list)
                    ? BellmanFord::run(*graphList, config.sourceVertex, config.destinationVertex, &length, &cost)
                    : BellmanFord::run(*graphMatrix, config.sourceVertex, config.destinationVertex, &length, &cost);
            ResultWriter::writeSP(config.outputFile, path, length, cost, &tmp, config.representation);
            delete[] path;
        };

        timer.stop();
        timer.result();
        delete graphList;
        delete graphMatrix;
    }

    if (config.mode==mode_test){
        for (int run=0; run<config.count; ++run){
            Timer timer;
            bool directed = (config.algorithm==alg_dijkstra||config.algorithm==alg_bellmanFord);
            AdjacencyList graphList(config.vertexCount, directed);
            Generator::generateConnectedGraph(graphList, config.density, directed);
            IncidenceMatrix graphMatrix = graphList.toMatrix();
            AdjacencyList tmp = graphMatrix.toList();

            timer.reset();
            timer.start();
            if (config.algorithm == alg_prim) {
                int edgeCount =0;
                Edge* mst = (config.representation==rep_list)
                            ? Prim::run(graphList, config.sourceVertex, &edgeCount)
                            : Prim::run(graphMatrix, config.sourceVertex, &edgeCount);
                long long totalWeight = 0;
                for (int i=0; i<edgeCount; ++i) totalWeight+=mst[i].weight;
                ResultWriter::writeMST(config.outputFile, mst, edgeCount, totalWeight, &graphList, config.representation);
                delete[] mst;

            } else if (config.algorithm == alg_kruskal) {
                Edge* mst = (config.representation==rep_list)
                            ? Kruskal::run(graphList)
                            : Kruskal::run(graphMatrix);
                int edgeCount = graphMatrix.getVertexCount()-1;
                long long totalWeight = 0;
                for (int i=0; i<edgeCount; ++i) totalWeight+=mst[i].weight;
                ResultWriter::writeMST(config.outputFile, mst, edgeCount, totalWeight, &tmp, config.representation);
                delete[] mst;

            } else if (config.algorithm == alg_dijkstra) {
                int* path = nullptr;
                long long length = 0;
                long long cost = 0;
                path = (config.representation==rep_list)
                        ? Dijkstra::run(graphList, config.sourceVertex, config.destinationVertex, &length, &cost)
                        : Dijkstra::run(graphMatrix, config.sourceVertex, config.destinationVertex, &length, &cost);
                ResultWriter::writeSP(config.outputFile, path, length, cost, &graphList, config.representation);
                delete[] path;

            } else if (config.algorithm == alg_bellmanFord) {
                int* path = nullptr;
                long long length = 0;
                long long cost = 0;
                path = (config.representation==rep_list)
                        ? BellmanFord::run(graphList, config.sourceVertex, config.destinationVertex, &length, &cost)
                        : BellmanFord::run(graphMatrix, config.sourceVertex, config.destinationVertex, &length, &cost);
                ResultWriter::writeSP(config.outputFile, path, length, cost, &tmp, config.representation);
                delete[] path;
            };

            timer.stop();
            timer.result();
        }
    }
    return 0;
}
