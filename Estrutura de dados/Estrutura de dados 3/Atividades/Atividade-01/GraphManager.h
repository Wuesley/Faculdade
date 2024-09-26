// GraphManager.h
#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "Graph.h"
#include "Color.h"

class GraphManager {
public:
    static void generateRandomGraph(Graph& graph, Color& color);
    static void visualizeGraph(const std::string& dotFile);
};

#endif // GRAPHMANAGER_H
