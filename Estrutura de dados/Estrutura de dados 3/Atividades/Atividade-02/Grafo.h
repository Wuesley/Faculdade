#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include "Aresta.h"

class Grafo {
private:
    int numVertices;
    std::vector<std::vector<Aresta>> adjacencia;

public:
    Grafo(int numVertices);

    void adicionarAresta(int origem, int destino, double peso);
    const std::vector<Aresta>& getAdjacentes(int vertice) const;
    int getNumVertices() const;
};


#endif 