#include <iostream>
#include <iomanip>
#include <c++/cmath>
#include "avl.hpp"
#include "avl.cpp"

int tamValor = 2;
int distancia = 2;

TC pegarValorPraImpressao(DicAVL &D, int profundidade, int indice) {
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
    return nohAtual->chave;

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
            TC valor = pegarValorPraImpressao(D, i, j);
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
    Noh* no2;
    Noh* no3;
    Noh* no4;

    inicializar(dictTest);
    no = inserir(dictTest, 12.75, -64.5);
    imprimirArvore(dictTest);
    no1 = inserir(dictTest, -155.75, 59.5);
    imprimirArvore(dictTest);
    no2 = inserir(dictTest, 139.5, 31);
    imprimirArvore(dictTest);
    no3 = inserir(dictTest, 280.25, 27.5);
    imprimirArvore(dictTest);
//    no3 = inserir(dictTest, -133.25, 10.5);
//    imprimirArvore(dictTest);
//    no4 = inserir(dictTest, -133.28, 10.5);

    remover(dictTest, no);
    imprimirArvore(dictTest);
//    remover(dictTest, no1);
//    imprimirArvore(dictTest);
//    remover(dictTest, no3);
//    imprimirArvore(dictTest);
//    remover(dictTest, no);
//    imprimirArvore(dictTest);
    terminar(dictTest);
    std::cout << "" << std::endl;
    return 0;
}