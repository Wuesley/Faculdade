// Nodo.h
#ifndef NODO_H
#define NODO_H

class Nodo {
public:
    int index;
    Nodo* next;
    bool visited;

    Nodo(int i);
};

#endif // NODO_H
