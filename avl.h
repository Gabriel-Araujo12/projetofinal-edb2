#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    char palavra[50];
    int linha_i, col_i;
    int linha_f, col_f;
    struct No *esquerdo, *direito;
    int altura;
};

No* inserir(int capacidade);
No* remover(int capacidade);
void imprimir(Heap* h, int n);
void liberarAVL(Heap *h);

#endif