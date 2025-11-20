#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include "avl.h"

void ler_tabuleiro(const char *arq);
void ler_palavras(const char *arq, TrieNo *no);
AVLNo* buscar_palavras(TrieNo *trie);
void imprimir_resultados(AVLNo *raiz);

int main() {
    TrieNo *trie = criarNoTrie();
    AVLNo *arvore = NULL;
    int opcao;

    do{
        printf("1 - Ler tabuleiro\n");
        printf("2 - Ler palavras\n");
        printf("3 - Buscar palavras no tabuleiro\n");
        printf("4 - Listar palavras encontradas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                ler_tabuleiro("tabuleiro.txt");
                printf("\n---> Tabuleiro carregado.\n\n");
                break;

            case 2:
                ler_palavras("palavras.txt", trie);
                printf("\n---> Palavras carregadas na Trie.\n\n");
                break;

            case 3:
                arvore = buscar_palavras(trie);
                printf("\n---> Busca concluída.\n\n");
                break;

            case 4:
                imprimir_resultados(arvore);
                break;

            case 0:
                printf("\n---> Encerrando programa...\n\n");
                break;

            default:
                printf("\n---> Opção inválida.\n\n");
        }

    } while(opcao != 0);

    liberarAVL(arvore);
    liberarTrie(trie);

    return 0;
}