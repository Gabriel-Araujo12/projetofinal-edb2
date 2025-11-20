#include "avl.h"

int obterAltura(AVLNo* no){
    if(no == NULL){
        return 0;
    }

    return no->altura;
}

AVLNo* criarNoAVL(char *p, int li, int ci, int lf, int cf){
    AVLNo* no = (AVLNo*)malloc(sizeof(AVLNo));

    strcpy(no->palavra, p);
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

int obterFatorBalanceamento(AVLNo* no){
    if(no == NULL){
        return 0;
    }

    return obterAltura(no->esquerdo) - obterAltura(no->direito);
}

AVLNo* rotacaoDireita(AVLNo* no){
    AVLNo* filhoEsquerdo = no->esquerdo;
    AVLNo* temp = filhoEsquerdo->direito;

    filhoEsquerdo->direito = no;
    no->esquerdo = temp;

    no->altura = max(obterAltura(no->esquerdo), obterAltura(no->direito)) + 1;
    filhoEsquerdo->altura = max(obterAltura(filhoEsquerdo->esquerdo), obterAltura(filhoEsquerdo->direito)) + 1;

    return filhoEsquerdo;
}

AVLNo* rotacaoEsquerda(AVLNo* no){
    AVLNo* filhoDireito = no->direito;
    AVLNo* temp = filhoDireito->esquerdo;

    filhoDireito->esquerdo = no;
    no->direito = temp;

    no->altura = max(obterAltura(no->esquerdo), obterAltura(no->direito)) + 1;
    filhoDireito->altura = max(obterAltura(filhoDireito->esquerdo), obterAltura(filhoDireito->direito)) + 1;

    return filhoDireito;
}

AVLNo* rotacaoDuplaEsquerdaDireita(AVLNo* no){
    no->esquerdo = rotacaoEsquerda(no->esquerdo);
    return rotacaoDireita(no);
}

AVLNo* rotacaoDuplaDireitaEsquerda(AVLNo* no){
    no->direito = rotacaoDireita(no->direito);
    return rotacaoEsquerda(no);
}

AVLNo* inserirAVL(AVLNo* no, char *p, int li, int ci, int lf, int cf){
    if(no == NULL){
        return criarNoAVL(p, li, ci, lf, cf);
    }

    int cmp = strcmp(p, no->palavra);

    if(cmp < 0){
        no->esquerdo = inserirAVL(no->esquerdo, p, li, ci, lf, cf);
    }
    else if(cmp > 0){
        no->direito = inserirAVL(no->direito, p, li, ci, lf, cf);
    }
    else{
        return no;
    }

    no->altura = 1 + max(obterAltura(no->esquerdo), obterAltura(no->direito));
    int fb = obterFatorBalanceamento(no);

    if(fb > 1 && strcmp(p, no->esquerdo->palavra) < 0){
        return rotacaoDireita(no);
    }
    if(fb < -1 && strcmp(p, no->direito->palavra) > 0){
        return rotacaoEsquerda(no);
    }
    if(fb > 1 && strcmp(p, no->esquerdo->palavra) > 0){
        return rotacaoDuplaEsquerdaDireita(no);
    }
    if(fb < -1 && strcmp(p, no->direito->palavra) < 0){
        return rotacaoDuplaDireitaEsquerda(no);
    }

    return no;
}

AVLNo* min_no(AVLNo *no){
    while(no->esquerdo != NULL){
        no = no->esquerdo;
    }

    return no;
}

AVLNo* removerAVL(AVLNo* raiz, char *p){
    if(raiz == NULL){
        return raiz;
    }

    int cmp = strcmp(p, raiz->palavra);

    if(cmp < 0){
        raiz->esquerdo = removerAVL(raiz->esquerdo, p);
    }
    else if(cmp > 0){
        raiz->direito = removerAVL(raiz->direito, p);
    }
    else{
        if((raiz->esquerdo == NULL) || (raiz->direito == NULL)){
            AVLNo *temp = raiz->esquerdo ? raiz->esquerdo : raiz->direito;

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
            AVLNo* temp = min_no(raiz->direito);

            strcpy(raiz->palavra, temp->palavra);
            raiz->linha_i = temp->linha_i;
            raiz->col_i = temp->col_i;
            raiz->linha_f = temp->linha_f;
            raiz->col_f = temp->col_f;

            raiz->direito = removerAVL(raiz->direito, temp->palavra);
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

void listarAVL(AVLNo* raiz){
    if(raiz != NULL){
        listarAVL(raiz->esquerdo);
        printf("%s (%d,%d) -> (%d,%d)\n", raiz->palavra, raiz->linha_i, raiz->col_i, raiz->linha_f, raiz->col_f);
        listarAVL(raiz->direito);
    }
}

void liberarAVL(AVLNo* raiz){
    if(!raiz){
        return;
    }

    liberarAVL(raiz->esquerdo);
    liberarAVL(raiz->direito);
    free(raiz);
}