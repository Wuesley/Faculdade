// GraphManager.cpp
#include "GraphManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void GraphManager::generateRandomGraph(Graph& graph, Color& color) {
    std::vector<std::vector<bool>> exists(graph.size(), std::vector<bool>(graph.size(), true));
    srand(static_cast<unsigned int>(time(0)));  // Seed for randomness

    for (int i = 0; i < graph.size(); i++) {
        std::string temp;
        for (int j = 0; j < 4; j++)
            temp += static_cast<char>(65 + rand() % 26);

        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;

        color.setNodeColor(i, r, g, b);
        graph.setLabel(i, temp);
    }

    for (int i = 0; i < graph.size() * graph.size(); i++) {
        int n = rand() % graph.size();
        int m = rand() % graph.size();

        if (exists[m][n] && m != n) {
            exists[m][n] = false;
            exists[n][m] = false;
            graph.addEdge(m, n);
        }
    }
}

void GraphManager::visualizeGraph(const std::string& dotFile) {
    std::cout << "dot " << dotFile << " -Tsvg > graphviz.svg" << std::endl;
    system(("dot " + dotFile + " -Tsvg > graphviz.svg").c_str());
    system("google-chrome graphviz.svg");
}
