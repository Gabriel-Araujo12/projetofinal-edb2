#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_ALFABETO 26

typedef struct TrieNo {
    struct TrieNo *filho[TAM_ALFABETO];
    int fim;
} TrieNo;

TrieNo* criarNoTrie();
void inserirTrie(TrieNo* raiz, const char* p);
int buscarTrie(TrieNo* raiz, const char* p);
void liberarTrie(TrieNo* raiz);

#endif
