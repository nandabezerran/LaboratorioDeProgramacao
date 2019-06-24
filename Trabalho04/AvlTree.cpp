//
// Created by fbeze on 22/06/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include "AvlTree.hpp"
using namespace std;

//Noh* procurar(DicAVL &D, TC c) {
//    if (c == null && D.raiz == nullptr)
//        return -1;
//
//    if (D.raiz->chave == c && D.raiz == nullptr)
//        return D.raiz;
//    else if (D.raiz->chave > chave)
//        return search(c, D.raiz->esq);
//    else
//        return search(c,  D.raiz->dir);
//}

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
        if (D.raiz->esq != nullptr)
            terminarRecursivo(D.raiz->esq);
        if (D.raiz->dir != nullptr)
            terminarRecursivo(D.raiz->dir);
    }
}

Noh* rotacaoDireita(Noh *n){
    Noh* x = n->esq;
    Noh* DirX = x->dir;

    x->dir = n;
    n->esq = DirX;

    if(n->esq->h > (n->dir->h + 1))
        n->h = n->esq->h;
    else
        n->h = n->dir->h + 1;

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
        y->h = y->dir->h + 1;

    if(x->esq->h > (x->dir->h + 1))
        x->h = x->esq->h;
    else
        x->h = x->dir->h + 1;

    return y;
}

int maximun(int a, int b){
    return (a > b)? a : b;
}

int balance(int a, int b){
    return a - b;
}

Noh* inserir (DicAVL &D, TC c, TV v){
    Noh* actualNode = D.raiz;
    Noh* actualFather = nullptr;
    int balanceFactor = 0;

    if(actualNode == nullptr){
        actualNode = new Noh;
        actualNode->chave = c;
        actualNode->valor = v;
        actualNode->h = 1;
        actualFather = nullptr;
        return actualNode;
    }
    bool isNull = false;
    while(!isNull){
        if (c < actualNode->chave) {
            actualFather = actualNode;
            actualNode = actualNode->esq;
        }

        else if (c >= actualNode->chave) {
            actualFather = actualNode;
            actualNode = actualNode->dir;

        }

        if (actualNode == nullptr) {
            isNull = true;
            actualNode = new Noh;
            actualNode->chave = c;
            actualNode->valor = v;
            actualNode->h = 1;
            actualNode->pai = actualFather;
            actualFather->h = 1 + maximun(actualFather->dir->h, actualFather->esq->h);
            balanceFactor = balance(actualFather->dir->h, actualFather->esq->h);
            // Left Left Case
            if (balanceFactor > 1 && v < actualFather->esq->valor)
                return rotacaoDireita(actualFather);

            // Right Right Case
            if (balanceFactor < -1 && v > actualFather->dir->valor)
                return rotacaoEsquerda(actualFather);

            // Left Right Case
            if (balanceFactor > 1 && v < actualFather->esq->valor){
                actualFather->esq = rotacaoEsquerda(actualFather->esq);
                return rotacaoDireita(actualFather);
            }

            // Right Left Case
            if (balanceFactor < -1 && v > actualFather->dir->valor){
                actualFather->dir = rotacaoDireita(actualFather->dir);
                return rotacaoEsquerda(actualFather);
            }
        }
    }
    return actualNode;
}
