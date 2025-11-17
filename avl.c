#include "avl.h"

int obterAltura(No* no){
    if(no == NULL){
        return 0;
    }

    return no->altura;
}

No* criarNo(char *p, int li, int ci, int lf, int cf){
    No* no = (No*)malloc(sizeof(No));

    strcpy(n->palavra, p);
    no->linha_i = li; 
    no->col_i = ci;
    no->linha_f = lf; 
    no->col_f = cf;

    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 1;

    return no;
}

int max(int a, int b){ 
    return (a > b) ? a : b; 
}

int obterFatorBalanceamento(No* no){
    if(no == NULL){
        return 0;
    }

    return obterAltura(no->esquerdo) - obterAltura(no->direito);
}

No* rotacaoDireita(No* no){
    No* filhoEsquerdo = no->esquerdo;
    No* temp = filhoEsquerdo->direito;

    filhoEsquerdo->direito = no;
    no->esquerdo = temp;

    no->altura = max(obterAltura(no->esquerdo), obterAltura(no->direito)) + 1;
    filhoEsquerdo->altura = max(obterAltura(filhoEsquerdo->esquerdo), obterAltura(filhoEsquerdo->direito)) + 1;

    return filhoEsquerdo;
}

No* rotacaoEsquerda(No* no){
    No* filhoDireito = no->direito;
    No* temp = filhoDireito->esquerdo;

    filhoDireito->esquerdo = no;
    no->direito = temp;

    no->altura = max(obterAltura(no->esquerdo), obterAltura(no->direito)) + 1;
    filhoDireito->altura = max(obterAltura(filhoDireito->esquerdo), obterAltura(filhoDireito->direito)) + 1;

    return filhoDireito;
}

No* rotacaoDuplaEsquerdaDireita(No* no){
    no->esquerdo = rotacaoEsquerda(no->esquerdo);
    return rotacaoDireita(no);
}

No* rotacaoDuplaDireitaEsquerda(No* no){
    no->direito = rotacaoDireita(no->direito);
    return rotacaoEsquerda(no);
}

No* inserir(No* no, char *p, int li, int ci, int lf, int cf){
    if(no == NULL){
        return criarNo(p, li, ci, lf, cf);
    }

    int cmp = strcmp(p, r->palavra);

    if(cmp < 0){
        no->esquerdo = inserir(no->esquerdo, p, li, ci, lf, cf);
    }
    else if(cmp > 0){
        no->direito = inserir(no->direito, p, li, ci, lf, cf);
    }
    else{
        return no;
    }

    no->altura = 1 + max(obterAltura(no->esquerdo), obterAltura(no->direito));
    int fb = obterFatorBalanceamento(no);

    if(fb > 1 && strcmp(p, r->esquerdo->palavra) < 0){
        return rotacaoDireita(no);
    }
    if(fb < -1 && strcmp(p, r->direito->palavra) > 0){
        return rotacaoEsquerda(no);
    }
    if(fb > 1 && strcmp(p, r->esquerdo->palavra) > 0){
        return rotacaoDuplaEsquerdaDireita(no);
    }
    if(fb < -1 && strcmp(p, r->direito->palavra) < 0){
        return rotacaoDuplaDireitaEsquerda(no);
    }

    return no;
}

No* min_no(No *raiz){
    while(raiz->esquerdo != NULL){
        raiz = raiz->esquerdo;
    }

    return raiz;
}

No* remover(No* raiz, char *p){
    if(raiz == NULL){
        return raiz;
    }

    int cmp = strcmp(p, r->palavra);

    if(cmp < 0){
        raiz->esquerdo = remover(raiz->esquerdo, p);
    }
    else if(cmp > 0){
        raiz->direito = remover(raiz->direito, p);
    }
    else{
        if((raiz->esquerdo == NULL) || (raiz->direito == NULL)){
            No *temp = raiz->esquerdo ? raiz->esquerdo : raiz->direito;

            if(temp == NULL){
                temp = raiz;
                raiz = NULL;
            }
            else{
             *raiz = *temp;
            }

            free(temp);
        }
        else{
            No* temp = min_no(raiz->direito);

            strcpy(raiz->palavra, temp->palavra);
            raiz->linha_i = temp->linha_i;
            raiz->col_i = temp->col_i;
            raiz->linha_f = temp->linha_f;
            raiz->col_f = temp->col_f;

            raiz->direito = remover(raiz->direito, temp->palavra);
        }
    }

    if(raiz == NULL){
        return raiz;
    }

    raiz->altura = 1 + max(obterAltura(raiz->esquerdo), obterAltura(raiz->direito));
    int fb = obterFatorBalanceamento(raiz);

    if(fb > 1 && obterFatorBalanceamento(raiz->esquerdo) >= 0){
        return rotacaoDireita(raiz);
    }
    if(fb < -1 && obterFatorBalanceamento(raiz->direito) <= 0){
        return rotacaoEsquerda(raiz);
    }
    if(fb > 1 && obterFatorBalanceamento(raiz->esquerdo) < 0){
        return rotacaoDuplaEsquerdaDireita(raiz);
    }
    if(fb < -1 && obterFatorBalanceamento(raiz->direito) > 0){
        return rotacaoDuplaDireitaEsquerda(raiz);
    }

    return raiz;
}

void listarEmOrdem(No* raiz){
    if(raiz != NULL){
        listarEmOrdem(raiz->esquerdo);
        printf("%s (%d,%d) -> (%d,%d)\n", r->palavra, r->linha_i, r->col_i, r->linha_f, r->col_f);
        listarEmOrdem(raiz->direito);
    }
}

void liberar(AVLNo *raiz){
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
}