#include <iostream>
#include "AvlTree.hpp"
#include "AvlTree.cpp"


int main() {
    DicAVL dictTest;
    Noh* no;
    inicializar(dictTest);
    no = inserir(dictTest, 1, 10);
    no = inserir(dictTest, 1, 20);
    no = inserir(dictTest, 1, 30);
    no = inserir(dictTest, 1, 40);
    no = inserir(dictTest, 1, 50);
    no = inserir(dictTest, 1, 25);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}