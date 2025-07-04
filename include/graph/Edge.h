#ifndef AIZO_2_EDGE_H
#define AIZO_2_EDGE_H


struct Edge {
    int source;
    int destination;
    int weight;

    bool operator<(const Edge& other) const {
        return weight<other.weight;
    }

    Edge(): source(0), destination(0), weight(0){}

    Edge(int source_, int destination_, int weight_):
        source(source_), destination(destination_), weight(weight_){}
};


#endif //AIZO_2_EDGE_H
