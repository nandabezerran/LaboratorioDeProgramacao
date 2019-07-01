//
// Created by fbeze on 22/06/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "avl.hpp"
using namespace std;

Noh* procurar(DicAVL &D, TC c) {
    Noh* nohAtual = D.raiz;
    if (nohAtual == nullptr)
        return nullptr;

    while(nohAtual->chave != c){
        if(nohAtual->chave > c) {
            nohAtual = nohAtual->esq;
        }
        else if(nohAtual->chave < c){
            nohAtual = nohAtual->dir;
        }

        if(nohAtual == nullptr){
            cout << "Noh nao encontrado" << endl;
            return nullptr ;
        }
    }
    return nohAtual;
}

void inicializar (DicAVL &D){
    D.raiz = nullptr;
}

void terminarRecursivo(Noh *n){
    if(n->esq == nullptr && n->dir == nullptr){
        free(n);
    }
    else{
        if(n->esq != nullptr)
            terminarRecursivo(n->esq);
        if(n->dir != nullptr)
            terminarRecursivo(n->dir);
    }
}

void terminar (DicAVL &D){
    if(D.raiz == nullptr){
        return;
    }
    if(D.raiz->esq == nullptr && D.raiz->dir == nullptr){
        free(D.raiz);
        D.raiz = nullptr;
        return;
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

    if(n->pai != nullptr) {
        if(n->pai->dir == n) {
            n->pai->dir = x;
        } else {
            n->pai->esq = x;
        }
    }

    x->dir = n;
    n->esq = DirX;
    if(DirX != nullptr) {
        DirX->pai = n;
    }
    x->pai = n->pai;
    n->pai = x;

    int nEsqH = n->esq != nullptr ? n->esq->h  : 0;
    int nDirH = n->dir != nullptr ? n->dir->h  : 0;
    n->h = 1 + max(nDirH, nEsqH);

    int xEsqH = x->esq != nullptr ? x->esq->h : 0;
    int xDirH = x->dir != nullptr ? x->dir->h : 0;
    x->h = 1 + max(xDirH, xEsqH);
    return x;
}

Noh* rotacaoEsquerda(Noh *x){
    Noh* y = x->dir;
    Noh* EsqY = y->esq;

    if(x->pai != nullptr) {
        if(x->pai->dir == x) {
            x->pai->dir = y;
        } else {
            x->pai->esq = y;
        }
    }

    x->dir = EsqY;
    if(EsqY != nullptr) {
        EsqY->pai = x;
    }
    y->esq = x;
    y->pai = x->pai;
    x->pai = y;

    int xEsqH = x->esq != nullptr ? x->esq->h + 1 : 1;
    int xDirH = x->dir != nullptr ? x->dir->h + 1 : 1;
    x->h = max(xDirH, xEsqH);

    int yEsqH = y->esq != nullptr ? y->esq->h + 1 : 1;
    int yDirH = y->dir != nullptr ? y->dir->h + 1 : 1;
    y->h = max(yEsqH, yDirH);

    return y;
}
void ajustarAlturaArvore(Noh* paiAtual){
    if(!paiAtual){
        return;
    }
    int hEsq;
    int hDir;
    hEsq = paiAtual->esq != nullptr ? paiAtual->esq->h : 0;
    hDir = paiAtual->dir != nullptr ? paiAtual->dir->h : 0;
    if((hEsq+1) != paiAtual->h && (hDir+1) != paiAtual->h) {
        paiAtual->h = 1 + max(hEsq, hDir);
    }
    ajustarAlturaArvore(paiAtual->pai);
}
Noh* inserir (DicAVL &D, TC c, TV v){
    Noh* nohAtual = D.raiz;
    Noh* paiAtual = nullptr;

    // First node insertion
    if(nohAtual == nullptr){
        nohAtual = new Noh();
        nohAtual->chave = c;
        nohAtual->valor = v;
        nohAtual->h = 1;
        nohAtual->dir = nullptr;
        nohAtual->esq = nullptr;
        nohAtual->pai = nullptr;
        D.raiz = nohAtual;
        return nohAtual;
    }

    // Search the tree position;
    bool praEsq;
    while(nohAtual != nullptr) {
        paiAtual = nohAtual;
        praEsq = nohAtual->chave > c;
        if(praEsq) {
            nohAtual = nohAtual->esq;
        } else {
            nohAtual = nohAtual->dir;
        }
    }

    // Create the new node
    Noh* novoNoh = new Noh();
    novoNoh->h = 1;
    novoNoh->chave = c;
    novoNoh->valor = v;
    novoNoh->pai = paiAtual;
    novoNoh->dir = nullptr;
    novoNoh->esq = nullptr;

    // Insert in the tree;
    if(praEsq) {
        paiAtual->esq = novoNoh;
        ajustarAlturaArvore(paiAtual);
    } else {
        paiAtual->dir = novoNoh;
        ajustarAlturaArvore(paiAtual);
    }

    int hEsq;
    int hDir;
    // Percorrendo a árvore de baixo pra cima pra achar o desbalanceamento;
    do {
        hEsq = paiAtual->esq != nullptr ? paiAtual->esq->h : 0;
        hDir = paiAtual->dir != nullptr ? paiAtual->dir->h : 0;

        paiAtual->h = 1 + max(hEsq, hDir);

        //Esquerda maior que a direita
        if(hEsq - hDir > 1) {
            // Esq pre esq rot
            if(paiAtual->esq != nullptr) {
                hEsq = paiAtual->esq->esq != nullptr ? paiAtual->esq->esq->h : 0;
                hDir = paiAtual->esq->dir != nullptr ? paiAtual->esq->dir->h : 0;
                if(hDir > hEsq) {
                    rotacaoEsquerda(paiAtual->esq);
                }
            }
            // Rotacao direita;
            paiAtual = rotacaoDireita(paiAtual);
            if(paiAtual->pai == nullptr) {
                D.raiz = paiAtual;
            }
        }
            //Direita maior que a esquerda
        else if (hEsq - hDir < -1) {
            // Direita Pre esquerda rot
            if(paiAtual->dir != nullptr) {
                hEsq = paiAtual->dir->esq != nullptr ? paiAtual->dir->esq->h : 0;
                hDir = paiAtual->dir->dir != nullptr ? paiAtual->dir->dir->h : 0;
                if(hEsq > hDir) {
                    rotacaoDireita(paiAtual->dir);
                }
            }
            // Rotacao esquerda;
            paiAtual = rotacaoEsquerda(paiAtual);
            if(paiAtual->pai == nullptr) {
                D.raiz = paiAtual;
            }
        } else {
            paiAtual = paiAtual->pai;
        }
    } while(paiAtual != nullptr);

    return novoNoh;
}

Noh* acharSucessor(Noh* n){
    Noh* nohAtual = n->dir;
    while (nohAtual->esq != nullptr)
        nohAtual = nohAtual->esq;
    return nohAtual;
}

void remover (DicAVL &D, Noh *n){
    Noh* nohAtual = D.raiz;
    Noh* paiAtual = nullptr;

    if(!nohAtual){
        cout << "Arvore vazia" << endl;
        return;
    }

    nohAtual = procurar(D, n->chave);
    if(!nohAtual){
        cout << "Noh nao encontrado" << endl;
        return;
    }

    paiAtual = nohAtual->pai;
    bool esquerda = true;
    bool raiz = false;
    if(!nohAtual->pai){
        raiz = true;
        esquerda = false;
    }
    else if(paiAtual->dir == nohAtual){
        esquerda = false;
    }
    if(nohAtual->dir == nullptr && nohAtual->esq == nullptr){
        free(nohAtual);
        if(raiz){
            D.raiz = nullptr;
        }
        else{
            if(esquerda){
                paiAtual->esq = nullptr;
            }
            else{
                paiAtual->dir = nullptr;
            }
            ajustarAlturaArvore(paiAtual);
        }
    }

    else if(nohAtual->dir == nullptr){
        if(!raiz){
            if(esquerda){
                paiAtual->esq = nohAtual->esq;
            }
            else{
                paiAtual->dir = nohAtual->esq;
            }
            nohAtual->esq->pai = paiAtual;
            ajustarAlturaArvore(paiAtual);
            free(nohAtual);
        }
        else{
            nohAtual->esq->pai = paiAtual;
            D.raiz = nohAtual->esq;
            free(nohAtual);
        }
    }
    else if(nohAtual->esq == nullptr) {
        if(!raiz) {
            if (esquerda) {
                paiAtual->esq = nohAtual->dir;
            } else {
                paiAtual->dir = nohAtual->dir;
            }
            nohAtual->dir->pai = paiAtual;
            ajustarAlturaArvore(paiAtual);
            free(nohAtual);
        }
        else{
            nohAtual->dir->pai = paiAtual;
            D.raiz = nohAtual->dir;
            free(nohAtual);
        }
    }
    else {
        Noh *sucessor = acharSucessor(nohAtual);
        Noh *auxEsq;
        Noh *auxDir;
        int auxH;
        Noh *auxPai;


        auxPai = sucessor->pai;
        auxEsq = nohAtual->esq;
        auxDir = nohAtual->dir;
        auxH = nohAtual->h;

        nohAtual->dir->pai = sucessor;
        nohAtual->esq->pai = sucessor;
        auxPai->esq = sucessor->dir;

        sucessor->pai->esq = nohAtual;
        sucessor->dir = auxDir;
        sucessor->esq = auxEsq;
        sucessor->pai = paiAtual;
        sucessor->h = auxH;
        if(sucessor == auxDir){
            auxPai = sucessor->pai;
            sucessor->dir= nullptr;
        }
        else{
            auxPai->esq = nullptr;
        }
        if(!raiz) {
            if (esquerda) {
                paiAtual->esq = sucessor;
            } else {
                paiAtual->dir = sucessor;
            }
            free(nohAtual);
            ajustarAlturaArvore(auxPai);
        }
        else {
            D.raiz = sucessor;
            D.raiz->pai = nullptr;
            free(nohAtual);
            ajustarAlturaArvore(auxPai);
        }
    }

    int hEsq;
    int hDir;
    // Percorrendo a árvore de baixo pra cima pra achar o desbalanceamento;
    while(paiAtual != nullptr) {
        hEsq = paiAtual->esq != nullptr ? paiAtual->esq->h : 0;
        hDir = paiAtual->dir != nullptr ? paiAtual->dir->h : 0;

        if((hEsq + 1) != paiAtual->h && (hDir + 1) != paiAtual->h) {
            paiAtual->h = max(hEsq + 1, hDir + 1);
        }

        if(hEsq - hDir > 1) {
            // Esquerda pre Esquerda rot
            if(paiAtual->esq != nullptr) {
                hEsq = paiAtual->esq->esq != nullptr ? paiAtual->esq->esq->h : 0;
                hDir = paiAtual->esq->dir != nullptr ? paiAtual->esq->dir->h : 0;
                if(hDir > hEsq) {
                    rotacaoEsquerda(paiAtual->esq);
                }
            }
            // Rotacao direita;
            paiAtual = rotacaoDireita(paiAtual);
            if(paiAtual->pai == nullptr) {
                D.raiz = paiAtual;
            }
        } else if (hEsq - hDir < -1) {
            // Direita Pre esquerda rot
            if(paiAtual->dir != nullptr) {
                hEsq = paiAtual->dir->esq != nullptr ? paiAtual->dir->esq->h : 0;
                hDir = paiAtual->dir->dir != nullptr ? paiAtual->dir->dir->h : 0;
                if(hEsq > hDir) {
                    rotacaoDireita(paiAtual->dir);
                }
            }
            // Rotacao esquerda;
            paiAtual = rotacaoEsquerda(paiAtual);
            if(paiAtual->pai == nullptr) {
                D.raiz = paiAtual;
            }
        } else {
            paiAtual = paiAtual->pai;
        }
    }
    if(raiz && D.raiz != nullptr){
        paiAtual = D.raiz;
        hEsq = paiAtual->esq != nullptr ? paiAtual->esq->h : 0;
        hDir = paiAtual->dir != nullptr ? paiAtual->dir->h : 0;
        if(hEsq - hDir > 1) {
            // Esquerda pre Esquerda rot
            if(paiAtual->esq != nullptr) {
                hEsq = paiAtual->esq->esq != nullptr ? paiAtual->esq->esq->h : 0;
                hDir = paiAtual->esq->dir != nullptr ? paiAtual->esq->dir->h : 0;
                if(hDir > hEsq) {
                    rotacaoEsquerda(paiAtual->esq);
                }
            }
            // Rotacao direita;
            paiAtual = rotacaoDireita(paiAtual);
            if(paiAtual->pai == nullptr) {
                D.raiz = paiAtual;
            }
        } else if (hEsq - hDir < -1) {
            // Direita Pre esquerda rot
            if(paiAtual->dir != nullptr) {
                hEsq = paiAtual->dir->esq != nullptr ? paiAtual->dir->esq->h : 0;
                hDir = paiAtual->dir->dir != nullptr ? paiAtual->dir->dir->h : 0;
                if(hEsq > hDir) {
                    rotacaoDireita(paiAtual->dir);
                }
            }
            // Rotacao esquerda;
            paiAtual = rotacaoEsquerda(paiAtual);
            if(paiAtual->pai == nullptr) {
                D.raiz = paiAtual;
            }
        }
    }
}