#include "../../include/io/GraphLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

IncidenceMatrix* GraphLoader::loadToMatrix(const string &filename, bool directed) {
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Nie mozna otworzyc pliku " << filename << endl;
        return nullptr;
    }

    int edgeCount = 0, vertexCount = 0;
    string line;
    if (!getline(file, line)) {
        cerr << "Pusty plik!"<<endl;
        return nullptr;
    }

    stringstream ss(line);
    if (!(ss >> edgeCount) || !(ss.ignore()) || !(ss >> vertexCount)) {
        cerr << "Nieprawidlowy format pierwszej linii" << endl;
        return nullptr;
    }


    auto* graph = new IncidenceMatrix(vertexCount, edgeCount+1, directed);
    while(getline(file, line)){
        if(line.empty() ||line[0]=='#') continue;

        int source, destination, weight;
        stringstream edgeStream(line);

        edgeStream >> source;
        edgeStream.ignore();
        edgeStream >> destination;
        edgeStream.ignore();
        edgeStream >> weight;

        if (source < 0 || source >= vertexCount ||
            destination < 0 || destination >= vertexCount) {
            cerr << "Nieprawidlowe wierzcholki: " << source << "->" << destination << endl;
            delete graph;
            return nullptr;
        }
        if (weight <= 0) {
            cerr << "Waga musi byc dodatnia: " << weight << endl;
            delete graph;
            return nullptr;
        }
        graph->addEdge(source, destination, weight);
    }

    return graph;
}


AdjacencyList* GraphLoader::loadToList(const string &filename, bool directed) {
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Nie mozna otworzyc pliku " << filename << endl;
        return nullptr;
    }

    int edgeCount = 0, vertexCount = 0;
    string line;
    if (!getline(file, line)) {
        cerr << "Pusty plik!"<<endl;
        return nullptr;
    }

    stringstream ss(line);
    if (!(ss >> edgeCount) || !(ss.ignore()) || !(ss >> vertexCount)) {
        cerr << "Nieprawidlowy format pierwszej linii" << endl;
        return nullptr;
    }


    auto* graph = new AdjacencyList(vertexCount, directed);
    int source, destination, weight;
    while (getline(file, line)) {
        if(line.empty() ||line[0]=='#') continue;

        stringstream edgeStream(line);
        edgeStream >> source;
        edgeStream.ignore();
        edgeStream >> destination;
        edgeStream.ignore();
        edgeStream >> weight;

        if (source < 0 || source >= vertexCount ||
            destination < 0 || destination >= vertexCount) {
            cerr << "Nieprawidlowe wierzcholki: " << source << "->" << destination << endl;
            delete graph;
            return nullptr;
        }
        if (weight <= 0) {
            cerr << "Waga musi byc dodatnia: " << weight << endl;
            delete graph;
            return nullptr;
        }
        graph->addEdge(source, destination, weight);
    }



    return graph;
}