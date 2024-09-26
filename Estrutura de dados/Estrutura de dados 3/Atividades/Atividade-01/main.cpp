// main.cpp
#include "Graph.h"
#include "Color.h"
#include "GraphManager.h"

int main() {
    int nodes = 20;
    Graph graph(nodes);
    Color color(nodes);

    GraphManager::generateRandomGraph(graph, color);
    graph.saveToFile("graphviz.dot", color);
    GraphManager::visualizeGraph("graphviz.dot");

    return 0;
}
