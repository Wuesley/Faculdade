#include <iostream>
#include "Grafo.h"

int main() {
    Grafo grafo(5);

    // Adicionar arestas
    grafo.adicionarAresta(0, 1, 2.5);
    grafo.adicionarAresta(0, 2, 1.2);
    grafo.adicionarAresta(1, 3, 3.1);
    grafo.adicionarAresta(3, 4, 0.8);
    grafo.adicionarAresta(2, 4, 2.3);

    // Exibir arestas
    for (int i = 0; i < grafo.getNumVertices(); ++i) {
        const auto& adjacentes = grafo.getAdjacentes(i);
        std::cout << "Vértice " << i << ":\n";
        for (const auto& aresta : adjacentes) {
            std::cout << "  -> " << aresta.getDestino() << " (Peso: " << aresta.getPeso() << ")\n";
        }
    }

    return 0;
}