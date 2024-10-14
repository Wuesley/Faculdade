#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXIMO_USUARIOS 100
#define TAMANHO_MAXIMO_DE_CADA_NOME 50

//##################### structs
typedef struct Amizade {
    int destino;
    int peso;
    struct Amizade* Proximo;
} Amizade;

typedef struct Usuario {
    char NomeUsuario[TAMANHO_MAXIMO_DE_CADA_NOME];
    Amizade* ListaAdjacenteacencia;
} Usuario;

typedef struct FriendFace {
    Usuario usuarios[MAXIMO_USUARIOS];
    int NumeroDeUsuarios;
} FriendFace;

//#################################


//##################### functions
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
        RedeSocial->usuarios[RedeSocial->NumeroDeUsuarios].ListaAdjacenteacencia = NULL;
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
    
    Amizade* NovaAmizade = (Amizade*)malloc(sizeof(Amizade));
    NovaAmizade->destino = EnderecoDestino;
    NovaAmizade->peso = peso;
    NovaAmizade->Proximo = RedeSocial->usuarios[EnderecoOrigem].ListaAdjacenteacencia;
    RedeSocial->usuarios[EnderecoOrigem].ListaAdjacenteacencia = NovaAmizade;
}

void GeraGraphviz(FriendFace* RedeSocial, const char* NomeUsuario_arquivo) {
    FILE* file = fopen(NomeUsuario_arquivo, "w");
    if (file == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    fprintf(file, "digraph FriendFace {\n");
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        Amizade* Adjacente = RedeSocial->usuarios[i].ListaAdjacenteacencia;
        while (Adjacente) {
            fprintf(file, "  \"%s\" -> \"%s\" [label=\"%d\"];\n",
                    RedeSocial->usuarios[i].NomeUsuario, 
                    RedeSocial->usuarios[Adjacente->destino].NomeUsuario, 
                    Adjacente->peso);
            Adjacente = Adjacente->Proximo;
        }
    }
    fprintf(file, "}\n");
    fclose(file);
}

// Algoritmo DFS
void Dfs_util(FriendFace* RedeSocial, int idx, int visitados[]) {
    visitados[idx] = 1;
    printf("%s ", RedeSocial->usuarios[idx].NomeUsuario);
    
    Amizade* Adjacente = RedeSocial->usuarios[idx].ListaAdjacenteacencia;
    while (Adjacente) {
        if (!visitados[Adjacente->destino]) {
            Dfs_util(RedeSocial, Adjacente->destino, visitados);
        }
        Adjacente = Adjacente->Proximo;
    }
}

void Dfs(FriendFace* RedeSocial, const char* NomeUsuarioInicial) {
    int idx = EncontrarUsuario(RedeSocial, NomeUsuarioInicial);
    if (idx == -1) {
        printf("Erro: Usuário não encontrado.\n");
        return;
    }
    
    int visitados[MAXIMO_USUARIOS] = {0};
    printf("DFS a partir de '%s': ", NomeUsuarioInicial);
    Dfs_util(RedeSocial, idx, visitados);
    printf("\n");
}

// Algoritmo BFS
void Bfs(FriendFace* RedeSocial, const char* NomeUsuarioInicial, const char* NomeUsuarioFinal) {
    int EnderecoInicial = EncontrarUsuario(RedeSocial, NomeUsuarioInicial);
    int EnderecoFinal = EncontrarUsuario(RedeSocial, NomeUsuarioFinal);
    
    if (EnderecoInicial == -1 || EnderecoFinal == -1) {
        printf("Erro: Usuário não encontrado.\n");
        return;
    }
    
    int visitados[MAXIMO_USUARIOS] = {0};
    int fila[MAXIMO_USUARIOS], inicio = 0, fim = 0;
    int antecessor[MAXIMO_USUARIOS];
    
    fila[fim++] = EnderecoInicial;
    visitados[EnderecoInicial] = 1;
    antecessor[EnderecoInicial] = -1;
    
    while (inicio < fim) {
        int u = fila[inicio++];
        
        if (u == EnderecoFinal)
            break;
        
        Amizade* Adjacente = RedeSocial->usuarios[u].ListaAdjacenteacencia;
        while (Adjacente) {
            if (!visitados[Adjacente->destino]) {
                visitados[Adjacente->destino] = 1;
                fila[fim++] = Adjacente->destino;
                antecessor[Adjacente->destino] = u;
            }
            Adjacente = Adjacente->Proximo;
        }
    }
    
    if (!visitados[EnderecoFinal]) {
        printf("Não há caminho de '%s' para '%s'.\n", NomeUsuarioInicial, NomeUsuarioFinal);
        return;
    }
    
    int caminho[MAXIMO_USUARIOS], tam = 0;
    for (int v = EnderecoFinal; v != -1; v = antecessor[v])
        caminho[tam++] = v;
    
    printf("BFS de '%s' para '%s': ", NomeUsuarioInicial, NomeUsuarioFinal);
    for (int i = tam - 1; i >= 0; i--)
        printf("%s%s", RedeSocial->usuarios[caminho[i]].NomeUsuario, i == 0 ? "\n" : ", ");
}

// Algoritmo de Dijkstra
void Dijkstra(FriendFace* RedeSocial, const char* NomeUsuarioInicial, const char* NomeUsuarioFinal) {
    int EnderecoInicial = EncontrarUsuario(RedeSocial, NomeUsuarioInicial);
    int EnderecoFinal = EncontrarUsuario(RedeSocial, NomeUsuarioFinal);
    
    if (EnderecoInicial == -1 || EnderecoFinal == -1) {
        printf("Erro: Usuário não encontrado.\n");
        return;
    }
    
    int dist[MAXIMO_USUARIOS], visitados[MAXIMO_USUARIOS], antecessor[MAXIMO_USUARIOS];
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        dist[i] = INT_MAX;
        visitados[i] = 0;
        antecessor[i] = -1;
    }
    
    dist[EnderecoInicial] = 0;
    
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        int u = -1;
        for (int j = 0; j < RedeSocial->NumeroDeUsuarios; j++) {
            if (!visitados[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }
        
        if (dist[u] == INT_MAX)
            break;
        
        visitados[u] = 1;
        
        Amizade* Adjacente = RedeSocial->usuarios[u].ListaAdjacenteacencia;
        while (Adjacente) {
            if (dist[u] + Adjacente->peso < dist[Adjacente->destino]) {
                dist[Adjacente->destino] = dist[u] + Adjacente->peso;
                antecessor[Adjacente->destino] = u;
            }
            Adjacente = Adjacente->Proximo;
        }
    }
    
    if (dist[EnderecoFinal] == INT_MAX) {
        printf("Não há caminho de '%s' para '%s'.\n", NomeUsuarioInicial, NomeUsuarioFinal);
        return;
    }
    
    int caminho[MAXIMO_USUARIOS], tam = 0;
    for (int v = EnderecoFinal; v != -1; v = antecessor[v])
        caminho[tam++] = v;
    
    printf("Dijkstra de '%s' para '%s': Frequência: %d, Caminho: ", NomeUsuarioInicial, NomeUsuarioFinal, dist[EnderecoFinal]);
    for (int i = tam - 1; i >= 0; i--)
        printf("%s%s", RedeSocial->usuarios[caminho[i]].NomeUsuario, i == 0 ? "\n" : ", ");
}

// Algoritmo Bellman-Ford
void BellmanFord(FriendFace* RedeSocial, const char* NomeUsuarioInicial, const char* NomeUsuarioFinal) {
    int EnderecoInicial = EncontrarUsuario(RedeSocial, NomeUsuarioInicial);
    int EnderecoFinal = EncontrarUsuario(RedeSocial, NomeUsuarioFinal);
    
    if (EnderecoInicial == -1 || EnderecoFinal == -1) {
        printf("Erro: Usuário não encontrado.\n");
        return;
    }
    
    int dist[MAXIMO_USUARIOS], antecessor[MAXIMO_USUARIOS];
    for (int i = 0; i < RedeSocial->NumeroDeUsuarios; i++) {
        dist[i] = INT_MAX;
        antecessor[i] = -1;
    }
    
    dist[EnderecoInicial] = 0;
    
    for (int i = 1; i < RedeSocial->NumeroDeUsuarios; i++) {
        for (int u = 0; u < RedeSocial->NumeroDeUsuarios; u++) {
            Amizade* Adjacente = RedeSocial->usuarios[u].ListaAdjacenteacencia;
            while (Adjacente) {
                if (dist[u] != INT_MAX && dist[u] + Adjacente->peso < dist[Adjacente->destino]) {
                    dist[Adjacente->destino] = dist[u] + Adjacente->peso;
                    antecessor[Adjacente->destino] = u;
                }
                Adjacente = Adjacente->Proximo;
            }
        }
    }
    
    // Verificar ciclos de interação negativa
    for (int u = 0; u < RedeSocial->NumeroDeUsuarios; u++) {
        Amizade* Adjacente = RedeSocial->usuarios[u].ListaAdjacenteacencia;
        while (Adjacente) {
            if (dist[u] != INT_MAX && dist[u] + Adjacente->peso < dist[Adjacente->destino]) {
                printf("Há um ciclo de interação negativa.\n");
                return;
            }
            Adjacente = Adjacente->Proximo;
        }
    }
    
    if (dist[EnderecoFinal] == INT_MAX) {
        printf("Não há caminho de '%s' para '%s'.\n", NomeUsuarioInicial, NomeUsuarioFinal);
        return;
    }
    
    int caminho[MAXIMO_USUARIOS], tam = 0;
    for (int v = EnderecoFinal; v != -1; v = antecessor[v])
        caminho[tam++] = v;
    
    printf("Bellman-Ford de '%s' para '%s': Frequência: %d, Caminho: ", NomeUsuarioInicial, NomeUsuarioFinal, dist[EnderecoFinal]);
    for (int i = tam - 1; i >= 0; i--)
        printf("%s%s", RedeSocial->usuarios[caminho[i]].NomeUsuario, i == 0 ? "\n" : ", ");
}


int main() {


    FriendFace* RedeSocial = CriaFriendFace();
  
    
    AdicionarUsuario(RedeSocial, "Alice");
    AdicionarUsuario(RedeSocial, "Bob");
    AdicionarUsuario(RedeSocial, "Carlos");
    AdicionarUsuario(RedeSocial, "Diana");
    
    AdicionarConexao(RedeSocial, "Alice", "Bob", 4);
    AdicionarConexao(RedeSocial, "Alice", "Carlos", 2);
    AdicionarConexao(RedeSocial, "Bob", "Carlos", 5);
    AdicionarConexao(RedeSocial, "Bob", "Diana", 10);
    AdicionarConexao(RedeSocial, "Carlos", "Diana", 3);
    
    Dfs(RedeSocial, "Alice");
    Bfs(RedeSocial, "Alice", "Diana");
    Dijkstra(RedeSocial, "Alice", "Diana");
    BellmanFord(RedeSocial, "Alice", "Diana");
    GeraGraphviz(RedeSocial, "friendface.dot");
    
/*

      FriendFace* Redepolitica = CriaFriendFace();
    AdicionarUsuario(Redepolitica, "thielo");
    AdicionarUsuario(Redepolitica, "bolsonaro");
    AdicionarUsuario(Redepolitica, "marçal");
    AdicionarConexao(Redepolitica, "thielo", "marcal", 4);
    AdicionarConexao(Redepolitica, "thielo", "Bolsonaro", 5);
    AdicionarConexao(Redepolitica, "bolsonaro", "marcal", 2);
    Bfs(Redepolitica, "thielo", "marcal");
    GeraGraphviz(Redepolitica, "politica.dot");
    */
    return 0;
}
