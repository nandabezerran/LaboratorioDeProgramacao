//
// Created by fbeze on 22/06/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include "AvlTree.hpp"
using namespace std;

Noh* procurar(DicAVL &D, TC c) {
    if (c == null && D.raiz == nullptr)
        return -1;

    if (D.raiz->chave == c && D.raiz == nullptr)
        return D.raiz;
    else if (D.raiz->chave > chave)
        return search(c, D.raiz->esq);
    else
        return search(c,  D.raiz->dir);
}

void inicializar (DicAVL &D){
    D.raiz = nullptr;
}

void terminarRecursivo(Noh *n){
    if(n->esq == nullptr && n->dir == nullptr){
        delete n;
    }
    else{
        if(n->esq != nullptr)
            terminarRecursivo(n->esq);
        if(n->dir != nullptr)
            terminarRecursivo(n->dir);
    }
}

void terminar (DicAVL &D){
    if(D.raiz->esq == nullptr && D.raiz->dir == nullptr){
        delete D.raiz;
    }
    else {
        if (n->esq != nullptr)
            terminarRecursivo(D.raiz->esq);
        if (n->dir != nullptr)
            terminarRecursivo(D.raiz->dir);
    }
}

Noh* rotacaoDireita(Noh *n){
    Noh* x = n->esq;
    Noh* DirX = x->dir;

    x->dir = y;
    y->esq = filhoDirX;

    if(y->esq->h > (y->dir->h + 1))
        y->h = y->esq->h;
    else
        y->h = y->dir->h + 1;

    if(x->esq->h > (x->dir->h + 1))
        x->h = x->esq->h;
    else
        x->h = x->dir->h + 1;
    return x;
}

Noh* rotacaoEsquerda(Noh *x){
    Noh* y = x->dir;
    Noh* EsqY = y->esq;

    x->esq = EsqY;
    y->dir = x;

    if(y->esq->h > (y->dir->h + 1))
        y->h = y->esq->h;
    else
        y->h = y->filhoDireito->h + 1;

    if(x->esq->h > (x->dir->h + 1))
        x->h = x->esq->h;
    else
        x->h = x->dir->h + 1;

    return y;
}

