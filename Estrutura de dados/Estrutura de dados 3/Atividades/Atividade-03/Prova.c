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
Lista* cria_lista(void){
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

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

void imprime_lista(Lista* l) {
    No* aux = l->inicio;
    while (aux != NULL) {
        printf("%d(peso: %d) ", aux->valor, aux->peso);
        aux = aux->proximo;
    }
}

// Estruturas da rede social
typedef struct Usuario{
    char NomeUsuario[TAMANHO_MAXIMO_DE_CADA_NOME];
    Lista* ListaAdjacencia; // agora é do tipo lista encadeada
} Usuario;

typedef struct FriendFace{
    Usuario usuarios[MAXIMO_USUARIOS];
    int NumeroDeUsuarios;
} FriendFace;


// Funções da rede social
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
        RedeSocial->usuarios[RedeSocial->NumeroDeUsuarios].ListaAdjacencia = cria_lista();
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
    insere_inicio(RedeSocial->usuarios[EnderecoOrigem].ListaAdjacencia, EnderecoDestino, peso);
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


// Implementação do algoritmo BFS
void BFS(FriendFace* RedeSocial, int inicio) {

    bool visitado[MAXIMO_USUARIOS] = {false};
    int fila[MAXIMO_USUARIOS];
    int frente = 0, tras = 0;
    
    visitado[inicio] = true;
    fila[tras++] = inicio;

    while (frente < tras) {
        int usuario = fila[frente++];
        printf("Visitando %s\n", RedeSocial->usuarios[usuario].NomeUsuario);

        No* adjacente = RedeSocial->usuarios[usuario].ListaAdjacencia->inicio;
        while (adjacente != NULL) {
            if (!visitado[adjacente->valor]) {
                visitado[adjacente->valor] = true;
                fila[tras++] = adjacente->valor;
            }
            adjacente = adjacente->proximo;
        }
    }
}

// Implementação do algoritmo DFS
void DFS(FriendFace* RedeSocial, int usuario, bool visitado[]) {

    printf("Visitando %s\n", RedeSocial->usuarios[usuario].NomeUsuario);
    visitado[usuario] = true;

    No* adjacente = RedeSocial->usuarios[usuario].ListaAdjacencia->inicio;
    while (adjacente != NULL) {
        if (!visitado[adjacente->valor]) {
            DFS(RedeSocial, adjacente->valor, visitado);
        }
        adjacente = adjacente->proximo;
    }
}

void iniciarDFS(FriendFace* RedeSocial, int inicio) {
    bool visitado[MAXIMO_USUARIOS] = {false};
    DFS(RedeSocial, inicio, visitado);
}

// Implementação do algoritmo de Dijkstra
void Dijkstra(FriendFace* RedeSocial, int origem) {
    int distancia[MAXIMO_USUARIOS];
    bool visitado[MAXIMO_USUARIOS] = {false};

    for (int i = 0; i < MAXIMO_USUARIOS; i++) {
        distancia[i] = INT_MAX;
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
            }
            adjacente = adjacente->proximo;
        }
    }

    // Imprime as distâncias calculadas
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        printf("Distância de %s até %s: %d\n", RedeSocial->usuarios[origem].NomeUsuario, RedeSocial->usuarios[i].NomeUsuario, distancia[i]);
    }
}

// Implementação do algoritmo de Bellman-Ford
void BellmanFord(FriendFace* RedeSocial, int origem) {
    int distancia[MAXIMO_USUARIOS];
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        distancia[i] = INT_MAX;
    }
    distancia[origem] = 0;

    for (int i = 1; i < RedeSocial->NumeroDeUsuarios; i++) {
        for (int u = 0; u < RedeSocial->NumeroDeUsuarios; u++) {
            No* adjacente = RedeSocial->usuarios[u].ListaAdjacencia->inicio;
            while (adjacente != NULL) {
                int v = adjacente->valor;
                int peso = adjacente->peso;
                if (distancia[u] != INT_MAX && distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
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
                printf("Ciclo negativo detectado!\n");
                return;
            }
            adjacente = adjacente->proximo;
        }
    }

    // Imprime as distâncias calculadas
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        printf("Distância de %s até %s: %d\n", RedeSocial->usuarios[origem].NomeUsuario, RedeSocial->usuarios[i].NomeUsuario, distancia[i]);
    }
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

    printf("Busca em Largura (BFS):\n");
    BFS(RedeSocial, 0);

    printf("\nBusca em Profundidade (DFS):\n");
    iniciarDFS(RedeSocial, 0);

    printf("\nAlgoritmo de Dijkstra:\n");
    Dijkstra(RedeSocial, 0);

    printf("\nAlgoritmo de Bellman-Ford:\n");
    BellmanFord(RedeSocial, 0);

    GeraGraphviz(RedeSocial, "friendf.dot");

   
    printf("\nLista de adjacências do grafo:\n");
    ImprimeListaAdjacencias(RedeSocial);

    return 0;
}