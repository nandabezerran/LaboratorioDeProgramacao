#include <iostream>
#include <iomanip>
#include <c++/cmath>
#include "AvlTree.hpp"
#include "AvlTree.cpp"

int tamValor = 2;
int distancia = 2;

TV pegarValorPraImpressao(DicAVL &D, int profundidade, int indice) {
    Noh* nohAtual = D.raiz;

    for(int i = profundidade - 1; i >= 0; i--) {
        if((indice >> i) & 1) {
            nohAtual = nohAtual->dir;
        } else {
            nohAtual = nohAtual->esq;
        }
        if(nohAtual == nullptr) {
            return 0;
        }
    }
    return nohAtual->valor;

}

void imprimirArvore(DicAVL &D) {
    if(D.raiz == nullptr) {
        cout << "[" << std::string( tamValor, ' ' ) << "]" << endl << endl;
        return;
    }
    for(int i = 0; i < D.raiz->h; i++) {
        int nohs = (int)pow(2, (D.raiz->h-1) - i);
        int colunas = nohs * (tamValor + 2) + (nohs - 1) * distancia;
        int espacoInicial = (colunas / 2) - ((tamValor + 2) / 2);
        int espacoEntre = distancia + ((distancia + tamValor + 2) * ((int)(pow(2, (D.raiz->h-1) - i)) - 1));
        cout << std::string(espacoInicial, ' ');
        int nosNessaLinha = (int)pow(2, i);
        for(int j = 0; j < nosNessaLinha; j++) {
            if(j != 0) {
                cout << std::string(espacoEntre, ' ');
            }
            TV valor = pegarValorPraImpressao(D, i, j);
            if(valor == 0) {
                cout << "[" << std::string(tamValor, ' ') << "]";
            } else {
                cout << "[" << setfill('0') << setw(tamValor) << valor << "]";
            }
        }
        cout << endl;
    }
    cout << endl << "---------" << endl;
}

int main() {
    DicAVL dictTest;
    Noh* no;
    Noh* no1;

    inicializar(dictTest);
    no = inserir(dictTest, 1, 2);
    imprimirArvore(dictTest);
    no1 = inserir(dictTest, 2, 1);
    imprimirArvore(dictTest);
    no = inserir(dictTest, 3, 4);
    imprimirArvore(dictTest);
    no = inserir(dictTest, 4, 3);
    imprimirArvore(dictTest);
    no = inserir(dictTest, 5, 5);
    imprimirArvore(dictTest);
//    no = inserir(dictTest, 6, 48);
//    imprimirArvore(dictTest);
//    no = inserir(dictTest, 7, 62);
//    imprimirArvore(dictTest);
//    no = inserir(dictTest, 8, 78);
//    imprimirArvore(dictTest);
//    no = inserir(dictTest, 9, 88);
//    imprimirArvore(dictTest);
//    no = inserir(dictTest, 10, 92);
//    imprimirArvore(dictTest);
//    no = inserir(dictTest, 10, 80);
//    imprimirArvore(dictTest);
//    no1 = inserir(dictTest, 10, 82);
//    imprimirArvore(dictTest);
//    no = inserir(dictTest, 10, 84);
//    imprimirArvore(dictTest);


    remover(dictTest, no1);
    imprimirArvore(dictTest);
    std::cout << "" << std::endl;
    return 0;
}