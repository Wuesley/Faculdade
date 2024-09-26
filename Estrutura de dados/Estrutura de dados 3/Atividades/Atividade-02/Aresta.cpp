#include "Aresta.h"

Aresta::Aresta(int origem, int destino, double peso) : origem(origem), destino(destino), peso(peso) {}

int Aresta::getOrigem() const {
    return origem;
}

int Aresta::getDestino() const {
    return destino;
}

double Aresta::getPeso() const {
    return peso;
}