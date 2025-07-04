#ifndef AIZO_2_CPARSER_H
#define AIZO_2_CPARSER_H

enum Algorithm{
    alg_none,
    alg_prim,
    alg_kruskal,
    alg_dijkstra,
    alg_bellmanFord
};

enum Representation{
    rep_list,
    rep_matrix
};

enum Mode{
    mode_none,
    mode_help,
    mode_file,
    mode_test
};

struct CConfig{
    Mode mode;
    Algorithm algorithm;
    Representation representation;

    const char* inputFile;
    const char* outputFile;
    int sourceVertex;
    int destinationVertex;

    int density;
    int vertexCount;
    int count;
};


class CParser {
public:
    static bool parse(int argc, char** argv, CConfig& config);
};


#endif //AIZO_2_CPARSER_H
