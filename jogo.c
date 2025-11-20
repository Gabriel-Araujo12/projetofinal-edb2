#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "avl.h"

static int N;
static char **tab;

void ler_tabuleiro(const char *arq){
    FILE *arquivo = fopen(arq, "r");
    if(!arquivo){
        printf("\nERRO: Não foi possível abrir o arquivo.\n\n");

        return;
    }

    fscanf(arquivo, "%d %d", &N, &N);
    tab = malloc(N * sizeof(char*));

    for(int i = 0; i < N; i++){
        tab[i] = malloc(N + 1);

        for(int j = 0; j < N; j++){
            fscanf(arquivo, " %c", &tab[i][j]);
        }
    }

    fclose(arquivo);
}

void ler_palavras(const char *arq, TrieNo *no){
    FILE *arquivo = fopen(arq, "r");
    if(!arquivo){
        printf("\nERRO: Não foi possível abrir o arquivo.\n\n");

        return;
    }

    char palavra[50];
    while(fscanf(arquivo, "%s", palavra) != EOF){
        inserirTrie(no, palavra);
    }

    fclose(arquivo);
}

static void buscar_direcoes(TrieNo *trie, AVLNo **avl, int x, int y){
    int dx[8] = { 0, 0, 1, -1, 1, -1,  1, -1 };
    int dy[8] = { 1, -1, 0,  0, 1,  1, -1, -1 };

    char palavra[50];

    for(int d = 0; d < 8; d++){
        int i = x, j = y;
        int k = 0;

        while(i >= 0 && i < N && j >= 0 && j < N){
            palavra[k++] = tab[i][j];
            palavra[k] = '\0';

            if(buscarTrie(trie, palavra)){
                *avl = inserirAVL(*avl, palavra, x, y, i, j);
            }

            i += dx[d];
            j += dy[d];
        }
    }
}

AVLNo* buscar_palavras(TrieNo *trie){
    AVLNo *arvore = NULL;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            buscar_direcoes(trie, &arvore, i, j);
        }
    }

    return arvore;
}

void imprimir_resultados(AVLNo *raiz){
    if(raiz == NULL){
        printf("\n---> Nenhuma palavra encontrada.\n\n");
        return;
    }

    printf("\n========== PALAVRAS ENCONTRADAS ==========\n");
    listarAVL(raiz);
    printf("==========================================\n\n");
}