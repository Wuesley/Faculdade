#ifndef ARESTA_H
#define ARESTA_H

class Aresta {
private:
    int origem;
    int destino;
    double peso;

public:
    Aresta(int origem, int destino, double peso);

    int getOrigem() const;
    int getDestino() const;
    double getPeso() const;
};

#endif 