//
// Created by fbeze on 01/04/2019.
//
#include <stdlib.h>
#include "QuickSortRandomPivot.h"
#include <iostream>
#include <time.h>

using namespace std;


QuickSortRandomPivot::QuickSortRandomPivot() = default;

void QuickSortRandomPivot::QuickSort_(int *init, int *fin){
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

void QuickSortRandomPivot::Swap_(int *p, int *p_){
    int aux;
    aux = *p;
    *p = *p_;
    *p_ = aux;
}

void QuickSortRandomPivot::LomutoPartitioning_(int *init, int *fin, int *&pivot) {
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

void QuickSortRandomPivot::PrintVector_(int* vector, int* fin){
    for (vector; vector !=fin ; ++vector) {
        std::cout << *vector << " ";
    }
    std::cout << std::endl;
}

int* QuickSortRandomPivot::ChoosePivot_(int* first, int* last){
    srand((unsigned)time(nullptr));
    int *aux = first + (rand() % (last - first + 1));
    int *pivot = aux;
    return pivot;
}