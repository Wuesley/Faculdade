#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct nodo{
    int index;
    struct nodo* next;
    bool visited;
};
typedef struct nodo nodo_adj;


typedef nodo_adj** graph;
typedef char** graphlabels;
typedef unsigned int* colorattr;

struct Grafo{
    nodo_adj** graph;
};

nodo_adj** cria_grafo(int nodes){
    int i;
    nodo_adj** grafo = (nodo_adj**)malloc(nodes * sizeof(nodo_adj*));
    for (i = 0; i < nodes; i++)
    {
        grafo[i] = NULL;
    }
    return grafo;
}

colorattr cria_cores(int nodes)
{
    unsigned int* colort = (unsigned int*)malloc(sizeof(unsigned int) * nodes);
    int i;
    for (i = 0; i < nodes; i++)
        colort[i] = 0;
    return colort;
}

char** initnames(int nodes)
{
    int i;
    char** nomes = (char**)malloc(nodes * sizeof(char*));
    for (i = 0; i < nodes; i++)
    {
        nomes[i] = (char*)malloc(255);
        strcpy(nomes[i], "\0");
    }
    return nomes;
}

void setname(graphlabels names, char* name, int i)
{
    strcpy(names[i], name);
}

nodo_adj* cria_adjacencia(nodo_adj** nod, int ind, int adj)
{
    nodo_adj* newadj = (nodo_adj*)malloc(sizeof(nodo_adj));
    nodo_adj* aux = nod[ind];
    newadj->index = adj;
    newadj->next = NULL;
    newadj->visited = false;
    if (aux != NULL)
    {
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = newadj;
    }
    else
    {
        aux = newadj;
    }
    nod[ind] = aux;
    return aux;
}

nodo_adj* remove_inicio(nodo_adj* plista)
{
    nodo_adj* aux;
    if (plista == NULL)
        return NULL;
    else
    {
        aux = plista;
        plista = plista->next;
        free(aux);
        aux = NULL;
        return plista;
    }
}

void libera_grafo(graph g)
{
    int i;
    nodo_adj* aux;
    graph aux2;
    aux2 = g;
    int c = 0;
    while (*aux2 != NULL)
    {
        aux2++;
        c++;
    }
    for (i = 0; i < c; i++)
    {
        aux = g[i];
        while (aux != NULL)
        {
            aux = remove_inicio(aux);
        }
        g[i] = aux;
    }
    free(g);
}

void liberaNomes(graphlabels nomes, int nodes)
{
    int i;
    for (i = 0; i < nodes; i++)
    {
        free(nomes[i]);
    }
    free(nomes);
}

void salvagrafo(graph grafo, char* nome, graphlabels nomes, unsigned int* fillcolor, unsigned int* fontcolor, int tamanho)
{
    int i, destination;

    float f;
    nodo_adj* temp;
    graph aux2;
    aux2= grafo;

    FILE* saida;
    saida = fopen(nome, "wt");
    fprintf(saida, "graph G {\n ratio = fill;\n node[style=filled];\n");
    for (i = 0; i < tamanho; i++)
    {
        if (nomes != NULL)
            fprintf(saida, "%s [fontcolor=\"#%06x\"fillcolor=\"#%06x\"];\n", nomes[i], fontcolor[i], fillcolor[i]);
        else
            fprintf(saida, "%d [fontcolor=\"#%06x\"fillcolor=\"#%06x\"];\n", i, fontcolor[i], fillcolor[i]);
    }

    for (i = 0; i < tamanho; i++)
    {
        temp = grafo[i];
        destination = i;
        while (temp != NULL)
        {
            if (nomes != NULL)
                fprintf(saida, " \"%s\" -- \"%s\"\n", nomes[destination], nomes[temp->index]);
            else
                fprintf(saida, " \"%d\" -- \"%d\" \n", destination, temp->index);
            if (temp->next != NULL)
                temp = temp->next;
            else
                break;
        }
    }

    fprintf(saida, "}\n");
    fclose(saida);
}

void setnodecolor(colorattr nodecor, colorattr fontcor, int i, int r, int g, int b)
{
    nodecor[i] = b | (g << 8) | (r << 16);
    int luma = sqrt(b * b + g * g + r * r);
    luma = (luma > 240) ? 0 : 255;
    fontcor[i] = luma | (luma << 8) | (luma << 16);
}

void gera_random(graph grafo, graphlabels nomes, unsigned int* fillcolor, unsigned int* fontcolor, int nodes)
{
    char temp[5];
    int r, g, b, luma, i, j, m, n;
    bool** exists = (bool**)malloc(nodes * sizeof(bool*));
    for (i = 0; i < nodes; i++)
    {
        exists[i] = (bool*)malloc(nodes * sizeof(bool));
        for (j = 0; j < nodes; j++)
            exists[i][j] = true;
    }
    for (i = 0; i < nodes; i++)
    {
        for (j = 0; j < 4; j++)
            temp[j] = (char)(65 + rand() % 26);
        temp[4] = '\0';
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;
        setnodecolor(fillcolor, fontcolor, i, r, g, b);
        setname(nomes, temp, i);
    }
    for (i = 0; i < nodes * nodes; i++)
    {
        n = rand() % nodes;
        m = rand() % nodes;

        if (exists[m][n] == true && m != n)
        {
            exists[m][n] = false;
            exists[n][m] = false;
            cria_adjacencia(grafo, m, n);
        }
    }
    for (i = 0; i < nodes; i++)
    {
        free(exists[i]);
    }
    free(exists);
}

int main(void)
{
    int nodes = 20;
    graph grafo = cria_grafo(nodes);
    graphlabels nomes = initnames(nodes);
    colorattr fillcolor = cria_cores(nodes);
    colorattr fontcolor = cria_cores(nodes);
    gera_random(grafo, nomes, fillcolor, fontcolor, nodes);
    salvagrafo(grafo, "graphviz.dot", nomes, fillcolor, fontcolor, nodes);
    printf("dot graphviz.dot -Tsvg > graphviz.svg");
    system("dot graphviz.dot -Tsvg > graphviz.svg");
    system("google-chrome graphviz.svg");
    libera_grafo(grafo);
    liberaNomes(nomes, nodes);
    free(fillcolor);
    free(fontcolor);
    return 0;
}

/// TAREFA: Partindo *deste* codigo, faca o seguinte:
/// 1. Crie uma nova struct ou classe para Grafo e encapsule todos os dados dos
/// grafos dentro deste. As funções deverão trabalhar apenas com o tipo Grafo a partir de agora, nunca com NODE.

/// 2. Crie novas funcoes para criar, remover e modificar nodos e arestas, desalocando apropriadamente quando necessario.

/// 3. Crie uma função para ler um arquivo Graphviz e criar um grafo na memória utilizando as
/// estruturas definidas. Remova todos os vértices pares e salve o grafo novamente, com um nome diferente.