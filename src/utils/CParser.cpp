#include "../../include/utils/CParser.h"
#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

bool CParser::parse(int argc, char **argv, CConfig &config) {
    config.mode = mode_none;
    config.algorithm = alg_none;
    config.representation = rep_list;
    config.inputFile = nullptr;
    config.outputFile = nullptr;
    config.sourceVertex = -1;
    config.destinationVertex = -1;
    config.density = 0;
    config.vertexCount = 0;
    config.count = 1;

    if (argc<2){
        cerr << "Brak argumentow. Uzyj --help\n";
        return false;
    }

    if (config.destinationVertex >= config.vertexCount){
        cerr << "Wierzcholek koncowy ma nalezec do zbioru wierzcholkow grafu!";
        return false;
    }

    if (strcmp(argv[1], "--help")==0){
        config.mode = mode_help;
        return true;
    }

    if (config.mode==mode_file && config.outputFile== nullptr){
        cerr << "Nalezy podac plik wyjsciowy\n";
        return false;
    }

    if (strcmp(argv[1], "--file")==0){
        if (argc<6){
            cerr << "Brak wszystkich argumentow dla trybu --file\n";
            return false;
        }

        config.mode = mode_file;

        if (strcmp(argv[2], "0")==0) config.algorithm = alg_prim;
        else if (strcmp(argv[2], "1")==0) config.algorithm = alg_kruskal;
        else if (strcmp(argv[2], "2")==0) config.algorithm = alg_dijkstra;
        else if (strcmp(argv[2], "3")==0) config.algorithm = alg_bellmanFord;
        else {
            cerr << "Nieznany algorytm " << argv[2] << "\n";
            return false;
        }

        config.inputFile = argv[3];
        config.outputFile = argv[4];
        if (strcmp(argv[5], "0")==0) config.representation = rep_list;
        else if (strcmp(argv[5], "1")==0) config.representation = rep_matrix;
        else {
            cerr << "Nieznana reprezentacja " << argv[5] << "\n";
            return false;
        }

        if ((config.algorithm==alg_dijkstra || config.algorithm==alg_bellmanFord)){
            if (argc < 8){
                cerr << "Podaj dodatkowo dla problemu najkrotszej sciezki wierzcholki poczatky i koncowy!\n";
                return false;
            }
            config.sourceVertex = atoi(argv[6]);
            config.destinationVertex = atoi(argv[7]);
        }

        if (config.algorithm==alg_prim){
            if (argc<7){
                cerr << "Podaj dodatkowo wierzcholek poczatkowy!\n";
                return false;
            }
            config.sourceVertex=atoi(argv[6]);
        }
        return true;
    }

    // -- test mode
    if (strcmp(argv[1], "--test")==0){
        if (argc<8){
            cerr << "Brak wszystkich argumentow dla trybu --test\n";
            return false;
        }

        config.mode = mode_test;

        if (strcmp(argv[2], "0")==0) config.algorithm = alg_prim;
        else if (strcmp(argv[2], "1")==0) config.algorithm = alg_kruskal;
        else if (strcmp(argv[2], "2")==0) config.algorithm = alg_dijkstra;
        else if (strcmp(argv[2], "3")==0) config.algorithm = alg_bellmanFord;
        else {
            cerr << "Nieznany algorytm " << argv[2] << "\n";
            return false;
        }

        if (strcmp(argv[3], "0")==0) config.representation = rep_list;
        else if (strcmp(argv[3], "1")==0) config.representation = rep_matrix;
        else {
            cerr << "Nieznana reprezentacja " << argv[3] << "\n";
            return false;
        }

        config.density = atoi(argv[4]);
        config.vertexCount = atoi(argv[5]);
        if (config.density<1 || config.density>100 || config.vertexCount<=1){
            cerr << "Niepoprawna gestosc badz liczba wierzcholkow\n";
            return false;
        }

        config.count = atoi(argv[6]);
        config.outputFile = argv[7];

        if ((config.algorithm==alg_dijkstra || config.algorithm==alg_bellmanFord)){
            if (argc < 10){
                cerr << "Podaj dodatkowo dla problemu najkrotszej sciezki wierzcholki poczatky i koncowy!\n";
                return false;
            }
            config.sourceVertex = atoi(argv[8]);
            config.destinationVertex = atoi(argv[9]);
        }

        if (config.algorithm==alg_prim){
            if (argc<9){
                cerr << "Podaj dodatkowo wierzcholek poczatkowy!\n";
                return false;
            }
            config.sourceVertex=atoi(argv[8]);
        }
        return true;
    }

    cerr << "Nieznany tryb " << argv[1] << "\n";
    return false;
}