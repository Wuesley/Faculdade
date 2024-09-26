#include "Grafo.h"

Grafo::Grafo(int numVertices) : numVertices(numVertices), adjacencia(numVertices) {}

void Grafo::adicionarAresta(int origem, int destino, double peso) {
    Aresta novaAresta(origem, destino, peso);
    adjacencia[origem].push_back(novaAresta);
}

const std::vector<Aresta>& Grafo::getAdjacentes(int vertice) const {
    return adjacencia[vertice];
}

int Grafo::getNumVertices() const {
    return numVertices;
}