//
// Created by fbeze on 01/04/2019.
//

#include "QuickSortPointer.h"
#include <iostream>
using namespace std;

QuickSortPointer::QuickSortPointer() = default;

void QuickSortPointer::QuickSort_(int *init, int *fin){
    int *initR;
    int *finL;
    int *pivot;

    if (fin <= init){
        return;
    }
    pivot = ChoosePivot_(init, fin);
    LomutoPartitioning_(init, fin, pivot);

    if(pivot != init || pivot == fin){
        finL = pivot - 1;
        QuickSort_(init, finL);
    }

    if(pivot == init || pivot != fin ){
        initR = pivot + 1;
        QuickSort_(initR, fin);

    }
}

void QuickSortPointer::Swap_(int *p, int *p_){
    int aux;
    aux = *p;
    *p = *p_;
    *p_ = aux;
}

void QuickSortPointer::LomutoPartitioning_(int *init, int *fin, int *&pivot) {
    Swap_(init, pivot);

    int *i = init;
    int *j = i + 1;

    for (j; j <= fin; ++j) {
        if(*j < *init){
            i = i + 1;
            Swap_(i,j);
        }
    }
    Swap_(i, init);
    pivot = i;
}

void QuickSortPointer::PrintVector_(int* vector, int* fin){
    for (vector; vector !=fin ; ++vector) {
        std::cout << *vector << " ";
    }
    std::cout << std::endl;
}

int* QuickSortPointer::ChoosePivot_(int* first, int* last){
    int *pivot = first + (last - first)/2;
    return pivot;
}