//
// Created by fbeze on 22/06/2019.
//

#ifndef TRABALHO04_AVLTREE_HPP
#define TRABALHO04_AVLTREE_HPP
typedef double TC;
typedef float TV;
struct Noh {
    TC chave;
    TV valor;
    Noh *esq, *dir, *pai;
    int h;
};

struct DicAVL {
    Noh *raiz;
}; // Nulo quando árvore vazia.

void inicializar (DicAVL &D); // Inicializa D como uma ´arvore vazia// .

Noh* inserir (DicAVL &D, TC c, TV v); // Retorna um ponteiro para o novo
                                      // nó, ou nulo se erro de alocação

Noh* procurar (DicAVL &D, TC c); // Retorna um ponteiro para o nó da
                                 // chave procurada, ou nulo se a chave
                                 // não estiver em D.

void remover (DicAVL &D, Noh *n); // ’n’ aponta para o nó a ser removido

void terminar (DicAVL &D); // Desaloca os nós da árvore
#endif //TRABALHO04_AVLTREE_HPP
