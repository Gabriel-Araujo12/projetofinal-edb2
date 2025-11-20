#include "trie.h"

TrieNo* criarNoTrie(){
    TrieNo* no = (TrieNo*) malloc(sizeof(TrieNo));
    
    if(!no){
        return NULL;
    }

    no->fim = 0;
    for(int i = 0; i < TAM_ALFABETO; i++){
        no->filho[i] = NULL;
    }

    return no;
}

void inserirTrie(TrieNo* raiz, const char* p){
    TrieNo* atual = raiz;

    for(int i = 0; p[i] != '\0'; i++){
        if(!isalpha(p[i])){
            continue;
        }
        
        char c = toupper(p[i]);
        int indice = c - 'A';

        if(indice < 0 || indice >= 26){
            continue;
        }

        if(!atual->filho[indice]){
            atual->filho[indice] = criarNoTrie();
        }

        atual = atual->filho[indice];
    }

    atual->fim = 1;
}

int buscarTrie(TrieNo* raiz, const char* p){
    TrieNo* atual = raiz;

    for(int i = 0; p[i] != '\0'; i++){
        if(!isalpha(p[i])){
            return 0;
        }

        char c = toupper(p[i]);
        int indice = c - 'A';

        if(indice < 0 || indice >= 26){
            return 0;
        }

        if(!atual->filho[indice]){
            return 0;
        }
        
        atual = atual->filho[indice];
    }

    return atual->fim;
}

void liberarTrie(TrieNo* raiz){
    if(!raiz){
        return;
    }

    for(int i = 0; i < TAM_ALFABETO; i++){
        liberarTrie(raiz->filho[i]);
    }

    free(raiz);
}