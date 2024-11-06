#include <stdio.h>
#include <stdlib.h>

struct no {
    int valor;
    int peso;
    struct no* proximo;
};
typedef struct no No;

struct lista {
    No* inicio;
    No* fim;
    int tamanho;
};
typedef struct lista Lista;

// Função para criar uma lista de adjacências vazia
Lista* cria_lista(void) {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

// Função para inserir no início da lista (útil para a lista de adjacências)
void insere_inicio(Lista* l, int valor, int peso) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->peso = peso;
    novo->proximo = l->inicio;
    l->inicio = novo;
    if (l->fim == NULL) {
        l->fim = novo;
    }
    l->tamanho++;
}

// Função para imprimir a lista de adjacências
void imprime_lista(Lista* l) {
    No* aux = l->inicio;
    while (aux != NULL) {
        printf("%d(peso: %d) ", aux->valor, aux->peso);
        aux = aux->proximo;
    }
}

// Função para criar o grafo como um vetor de listas de adjacências
Lista** cria_grafo(int vertices) {
    Lista** grafo = (Lista**)malloc(vertices * sizeof(Lista*));
    for (int i = 0; i < vertices; i++) {
        grafo[i] = cria_lista();
    }
    return grafo;
}

// Função para adicionar uma aresta ao grafo
void adiciona_aresta(Lista** grafo, int origem, int destino, int peso) {
    insere_inicio(grafo[origem], destino, peso);
}

// Função DFS auxiliar
void dfs_visit(Lista** grafo, int v, int* visitado) {
    visitado[v] = 1;
    printf("Visitando vértice %d\n", v);

    No* adj = grafo[v]->inicio;
    while (adj != NULL) {
        if (!visitado[adj->valor]) {
            dfs_visit(grafo, adj->valor, visitado);
        }
        adj = adj->proximo;
    }
}

// Função principal de DFS
void dfs(Lista** grafo, int vertices, int vertice_inicial) {
    int* visitado = (int*)calloc(vertices, sizeof(int));
    dfs_visit(grafo, vertice_inicial, visitado);
    free(visitado);
}

// Função para imprimir a lista de adjacências do grafo
void imprime_grafo(Lista** grafo, int vertices) {
    for (int i = 0; i < vertices; i++) {
        printf("Vértice %d:", i);
        No* aux = grafo[i]->inicio;
        while (aux != NULL) {
            printf(" -> %d(peso: %d)", aux->valor, aux->peso);
            aux = aux->proximo;
        }
        printf("\n");
    }
}



int main() {
    int vertices = 5;
    Lista** grafo = cria_grafo(vertices);

    adiciona_aresta(grafo, 0, 1, 1);
    adiciona_aresta(grafo, 0, 2, 1);
    adiciona_aresta(grafo, 1, 3, 1);
    adiciona_aresta(grafo, 1, 4, 1);
    adiciona_aresta(grafo, 2, 4, 1);

    printf("DFS a partir do vértice 0:\n");
    dfs(grafo, vertices, 0);

    printf("Lista de adjacências do grafo:\n");
    imprime_grafo(grafo, vertices);

    // Liberando memória das listas de adjacências
    for (int i = 0; i < vertices; i++) {
        No* atual = grafo[i]->inicio;
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        free(grafo[i]);
    }
    free(grafo);



    return 0;
}
