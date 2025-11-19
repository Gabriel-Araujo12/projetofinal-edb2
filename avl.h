#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLNo {
    char palavra[50];
    int linha_i, col_i;
    int linha_f, col_f;
    struct AVLNo *esquerdo, *direito;
    int altura;
} AVLNo;

AVLNo* inserirAVL(AVLNo* no, char *p, int li, int ci, int lf, int cf);
AVLNo* removerAVL(AVLNo* raiz, char *p);
void listarAVL(AVLNo* raiz);
void liberarAVL(AVLNo *raiz);

#endif