// Graph.cpp
#include "Graph.h"
#include <fstream>
#include <iostream>

Graph::Graph(int nodeCount) : nodes(nodeCount, nullptr), labels(nodeCount, "") {}

Graph::~Graph() {
    clearGraph();
}

void Graph::addEdge(int from, int to) {
    Nodo* newAdj = new Nodo(to);
    if (nodes[from] == nullptr) {
        nodes[from] = newAdj;
    } else {
        Nodo* aux = nodes[from];
        while (aux->next != nullptr) {
            aux = aux->next;
        }
        aux->next = newAdj;
    }
}

void Graph::setLabel(int index, const std::string& label) {
    labels[index] = label;
}

void Graph::clearGraph() {
    for (auto& node : nodes) {
        while (node != nullptr) {
            Nodo* aux = node;
            node = node->next;
            delete aux;
        }
    }
    nodes.clear();
}

void Graph::saveToFile(const std::string& filename, const Color& color) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    file << "graph G {\n ratio = fill;\n node[style=filled];\n";
    for (size_t i = 0; i < nodes.size(); i++) {
        file << (labels[i].empty() ? std::to_string(i) : labels[i]) 
             << " [fontcolor=\"#"
             << std::hex << color.fontColors[i] 
             << "\" fillcolor=\"#"
             << std::hex << color.fillColors[i] << "\"];\n";
    }

    for (size_t i = 0; i < nodes.size(); i++) {
        Nodo* temp = nodes[i];
        while (temp != nullptr) {
            file << " \"" << (labels[i].empty() ? std::to_string(i) : labels[i])
                 << "\" -- \"" << (labels[temp->index].empty() ? std::to_string(temp->index) : labels[temp->index]) 
                 << "\"\n";
            temp = temp->next;
        }
    }

    file << "}\n";
    file.close();
}

int Graph::size() const {
    return nodes.size();
}
