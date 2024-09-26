// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include "Nodo.h"
#include "Color.h"

class Graph {
private:
    std::vector<Nodo*> nodes;
    std::vector<std::string> labels;

public:
    Graph(int nodeCount);
    ~Graph();
    void addEdge(int from, int to);
    void setLabel(int index, const std::string& label);
    void clearGraph();
    void saveToFile(const std::string& filename, const Color& color) const;
    int size() const;
};

#endif // GRAPH_H
