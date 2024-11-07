#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAXIMO_USUARIOS 100
#define TAMANHO_MAXIMO_DE_CADA_NOME 50

// Estruturas da lista encadeada
struct no{
    int valor;
    int peso;
    struct no* proximo;
};
typedef struct no No;

struct lista{
    No* inicio;
    No* fim;
    int tamanho;
};
typedef struct lista Lista;

// Funções da lista
Lista* CriaLista(void){
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

void InsereInicio(Lista* l, int valor, int peso) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->peso = peso;
    novo->proximo = l->inicio;
    l->inicio = novo;
    if(l->fim == NULL) {
        l->fim = novo;
    }
    l->tamanho++;
}

void ImprimeLista(Lista* l) {
    No* aux = l->inicio;
    while (aux != NULL) {
        printf("%d(peso: %d) ", aux->valor, aux->peso);
        aux = aux->proximo;
    }
}

// Fila
struct noFila {
    int valor;
    struct noFila* proximo;
};
typedef struct noFila NoFila;

struct fila {
    NoFila* inicio;
    NoFila* fim;
    int tamanho;
};
typedef struct fila Fila;

Fila* CriaFila(void) {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

int FilaVazia(Fila* f) {
    return (f->inicio == NULL);
}

Fila* IserirNaFila(Fila* f, int num) {
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    novo->valor = num;
    novo->proximo = NULL;

    if (FilaVazia(f)) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->proximo = novo;
        f->fim = novo;
    }
    f->tamanho++;
    return f;
}

int RemoverDaFila(Fila* f) {
    NoFila* aux;
    int conteudo;

    if (FilaVazia(f)) {
        printf("\n\tFILA VAZIA\n");
        exit(1);
    } else {
        aux = f->inicio;
        conteudo = aux->valor;
        f->inicio = f->inicio->proximo;

        if (f->tamanho == 1) {
            f->fim = NULL;
        }
        f->tamanho--;
        free(aux);
    }
    return conteudo;
}

// Pilha
struct noPilha {
    int valor;
    struct noPilha* proximo;
};
typedef struct noPilha NoPilha;

struct pilha {
    NoPilha* topo;
    int tamanho;
};
typedef struct pilha Pilha;

Pilha* CriaPilha(void) {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

int PilhaVazia(Pilha* p) {
    return (p->topo == NULL);
}

void PushEmpilha(Pilha* p, int num) {
    NoPilha* novo = (NoPilha*)malloc(sizeof(NoPilha));
    novo->valor = num;
    novo->proximo = p->topo;
    p->topo = novo;
    p->tamanho++;
}

int PopDesempilha(Pilha* p) {
    NoPilha* aux;
    int v;
    if (PilhaVazia(p)) {
        printf("\nPILHA VAZIA\n");
        exit(1);
    } else {
        aux = p->topo;
        v = aux->valor;
        p->topo = aux->proximo;
        free(aux);
        p->tamanho--;
        return v;
    }
}

// Estruturas e funções da rede social 
struct usuario{
    char NomeUsuario[TAMANHO_MAXIMO_DE_CADA_NOME];
    Lista* ListaAdjacencia; // agora é do tipo lista encadeada
};
typedef struct usuario Usuario;

struct friendface{
    Usuario usuarios[MAXIMO_USUARIOS];
    int NumeroDeUsuarios;
};
typedef struct friendface FriendFace;

FriendFace* CriaFriendFace() {
    FriendFace* RedeSocial = (FriendFace*)malloc(sizeof(FriendFace));
    RedeSocial->NumeroDeUsuarios = 0;
    return RedeSocial;
}

int EncontrarUsuario(FriendFace* RedeSocial, const char* NomeUsuario) {
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        if (strcmp(RedeSocial->usuarios[i].NomeUsuario, NomeUsuario) == 0)
            return i;
    }
    return -1;
}

void AdicionarUsuario(FriendFace* RedeSocial, const char* NomeUsuario) {
    if (RedeSocial->NumeroDeUsuarios < MAXIMO_USUARIOS) {
        strcpy(RedeSocial->usuarios[RedeSocial->NumeroDeUsuarios].NomeUsuario, NomeUsuario);
        RedeSocial->usuarios[RedeSocial->NumeroDeUsuarios].ListaAdjacencia = CriaLista();
        RedeSocial->NumeroDeUsuarios++;
    } else {
        printf("Erro: Limite de usuários atingido.\n");
    }
}

void AdicionarConexao(FriendFace* RedeSocial, const char* NomeUsuario_origem, const char* NomeUsuario_destino, int peso) {
    int EnderecoOrigem = EncontrarUsuario(RedeSocial, NomeUsuario_origem);
    int EnderecoDestino = EncontrarUsuario(RedeSocial, NomeUsuario_destino);
    if (EnderecoOrigem == -1 || EnderecoDestino == -1) {
        printf("Erro: Usuário não encontrado.\n");
        return;
    }
    InsereInicio(RedeSocial->usuarios[EnderecoOrigem].ListaAdjacencia, EnderecoDestino, peso);
}

void GeraGraphviz(FriendFace* RedeSocial, const char* NomeUsuario_arquivo) {
    FILE* file = fopen(NomeUsuario_arquivo, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    fprintf(file, "digraph FriendFace {\n");
    
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        No* adjacente = RedeSocial->usuarios[i].ListaAdjacencia->inicio;
        while (adjacente != NULL) {
            fprintf(file, "  \"%s\" -> \"%s\" [label=\"%d\"];\n",
                    RedeSocial->usuarios[i].NomeUsuario,
                    RedeSocial->usuarios[adjacente->valor].NomeUsuario,
                    adjacente->peso);
            adjacente = adjacente->proximo;
        }
    }

    fprintf(file, "}\n");
    fclose(file);
}

void ImprimirCaminho(int predecessores[], int destino, FriendFace* RedeSocial){
    if (destino == -1) {
        printf("Não há caminho entre o usuário de origem e destino.\n");
        return;
    }
    if (predecessores[destino] != -1) {
        ImprimirCaminho(predecessores, predecessores[destino], RedeSocial);
    }
    printf("%s ", RedeSocial->usuarios[destino].NomeUsuario);
}

void ImprimeListaAdjacencias(FriendFace* RedeSocial) {
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        printf("Vértice %s:", RedeSocial->usuarios[i].NomeUsuario);
        No* aux = RedeSocial->usuarios[i].ListaAdjacencia->inicio;
        while (aux != NULL) {
            printf(" -> %s(peso: %d)", RedeSocial->usuarios[aux->valor].NomeUsuario, aux->peso);
            aux = aux->proximo;
        }
        printf("\n");
    }
}


//GRAFOS
void DFS(FriendFace* RedeSocial, int inicio) {
    bool visitado[MAXIMO_USUARIOS] = {false};
    char resultado[500] = ""; // Armazena a sequência dos usuários visitados

    Pilha* pilha = CriaPilha();  // Criamos uma pilha
    PushEmpilha(pilha, inicio);  // Colocamos o usuário inicial na pilha

    while (!PilhaVazia(pilha)) {
        int usuario = PopDesempilha(pilha);  // Retiramos um usuário da pilha

        if (!visitado[usuario]) {
            visitado[usuario] = true;
            // Adiciona o usuário ao resultado
            strcat(resultado, RedeSocial->usuarios[usuario].NomeUsuario);
            strcat(resultado, ", ");

            // Colocamos os vizinhos não visitados na pilha
            No* adjacente = RedeSocial->usuarios[usuario].ListaAdjacencia->inicio;
            while (adjacente != NULL) {
                if (!visitado[adjacente->valor]) {
                    PushEmpilha(pilha, adjacente->valor);  // Empilhamos o vizinho
                }
                adjacente = adjacente->proximo;
            }
        }
    }

    // Removemos a vírgula final
    if (strlen(resultado) > 2) resultado[strlen(resultado) - 2] = '\0';

    printf("DFS a partir de '%s': %s\n", RedeSocial->usuarios[inicio].NomeUsuario, resultado);

    free(pilha);  // Libera a memória da pilha
}

void BFS(FriendFace* RedeSocial, int inicio, int destino) {
    bool visitado[MAXIMO_USUARIOS] = {false};
    int predecessores[MAXIMO_USUARIOS];
    for (int i = 0; i < MAXIMO_USUARIOS; i++) predecessores[i] = -1;

    Fila* fila = CriaFila();  // Criando uma fila
    visitado[inicio] = true;
    IserirNaFila(fila, inicio);

    while (!FilaVazia(fila)) {
        int usuario = RemoverDaFila(fila);  // Retiramos um usuário da fila

        if (usuario == destino) break;

        No* adjacente = RedeSocial->usuarios[usuario].ListaAdjacencia->inicio;
        while (adjacente != NULL) {
            if (!visitado[adjacente->valor]) {
                visitado[adjacente->valor] = true;
                predecessores[adjacente->valor] = usuario;
                IserirNaFila(fila, adjacente->valor);  // Inserimos na fila
            }
            adjacente = adjacente->proximo;
        }
    }

    printf("BFS de '%s' para '%s': ", RedeSocial->usuarios[inicio].NomeUsuario, RedeSocial->usuarios[destino].NomeUsuario);
    ImprimirCaminho(predecessores, destino, RedeSocial);
    printf("\n");

    free(fila);  // Libera a memória da fila
}

void Dijkstra(FriendFace* RedeSocial, int origem, int destino) {

    int distancia[MAXIMO_USUARIOS];
    bool visitado[MAXIMO_USUARIOS] = {false};
    int predecessores[MAXIMO_USUARIOS];
    for (int i = 0; i < MAXIMO_USUARIOS; i++) {
        distancia[i] = INT_MAX;
        predecessores[i] = -1;
    }
    distancia[origem] = 0;

    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        int minDistancia = INT_MAX, u = -1;

        for (int j = 0; j < RedeSocial->NumeroDeUsuarios; j++) {
            if (!visitado[j] && distancia[j] < minDistancia) {
                minDistancia = distancia[j];
                u = j;
            }
        }

        if (u == -1) break;
        visitado[u] = true;

        No* adjacente = RedeSocial->usuarios[u].ListaAdjacencia->inicio;
        while (adjacente != NULL) {
            int v = adjacente->valor;
            int peso = adjacente->peso;
            if (distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
                predecessores[v] = u;
            }
            adjacente = adjacente->proximo;
        }
    }

    printf("Dijkstra de '%s' para '%s': Frequência: %d, Caminho: ", 
           RedeSocial->usuarios[origem].NomeUsuario, 
           RedeSocial->usuarios[destino].NomeUsuario, 
           distancia[destino]);
    ImprimirCaminho(predecessores, destino, RedeSocial);
    printf("\n");
}

void BellmanFord(FriendFace* RedeSocial, int origem, int destino) {
    int distancia[MAXIMO_USUARIOS];
    int predecessores[MAXIMO_USUARIOS];
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        distancia[i] = INT_MAX;
        predecessores[i] = -1;
    }
    distancia[origem] = 0;

    // Relaxamento das arestas
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios - 1; i++) {
        for (int u = 0; u < RedeSocial->NumeroDeUsuarios; u++) {
            No* adjacente = RedeSocial->usuarios[u].ListaAdjacencia->inicio;
            while (adjacente != NULL) {
                int v = adjacente->valor;
                int peso = adjacente->peso;
                if (distancia[u] != INT_MAX && distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                    predecessores[v] = u;
                }
                adjacente = adjacente->proximo;
            }
        }
    }

    // Verificação de ciclos negativos
    for (int u = 0; u < RedeSocial->NumeroDeUsuarios; u++) {
        No* adjacente = RedeSocial->usuarios[u].ListaAdjacencia->inicio;
        while (adjacente != NULL) {
            int v = adjacente->valor;
            int peso = adjacente->peso;
            if (distancia[u] != INT_MAX && distancia[u] + peso < distancia[v]) {
                printf("O grafo contém um ciclo negativo!\n");
                return;
            }
            adjacente = adjacente->proximo;
        }
    }

    printf("Bellman-Ford de '%s' para '%s': Frequência: %d, Caminho: ", 
           RedeSocial->usuarios[origem].NomeUsuario, 
           RedeSocial->usuarios[destino].NomeUsuario, 
           distancia[destino]);
    ImprimirCaminho(predecessores, destino, RedeSocial);
    printf("\n");
}




int main() {
    
    
    FriendFace* RedeSocial = CriaFriendFace();


    AdicionarUsuario(RedeSocial, "Alice");
    AdicionarUsuario(RedeSocial, "Bob");
    AdicionarUsuario(RedeSocial, "Diana");
    AdicionarUsuario(RedeSocial, "Carlos");

    AdicionarConexao(RedeSocial, "Alice", "Bob", 4);
    AdicionarConexao(RedeSocial, "Alice", "Carlos", 2);
    AdicionarConexao(RedeSocial, "Bob", "Carlos", 5);
    AdicionarConexao(RedeSocial, "Bob", "Diana", 10);
    AdicionarConexao(RedeSocial, "Carlos", "Diana", 3);

    DFS(RedeSocial, EncontrarUsuario(RedeSocial, "Alice"));

    BFS(RedeSocial, EncontrarUsuario(RedeSocial, "Alice"), EncontrarUsuario(RedeSocial, "Diana"));

    Dijkstra(RedeSocial, EncontrarUsuario(RedeSocial, "Alice"), EncontrarUsuario(RedeSocial, "Diana"));

    BellmanFord(RedeSocial, EncontrarUsuario(RedeSocial, "Alice"), EncontrarUsuario(RedeSocial, "Diana"));

    GeraGraphviz(RedeSocial, "friendface.dot");
   
    printf("\nLista de adjacências do grafo:\n");
    ImprimeListaAdjacencias(RedeSocial);

 // Comando para gerar a imagem : dot -Tpng NomeDoArquivoCriado.dot -o NomeDoArquivoASerGerado.png

    return 0;
}